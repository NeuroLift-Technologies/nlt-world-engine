using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using Godot;

namespace NltWorldEngine.Agents;

/// <summary>
/// The engine side of <c>nlt.observer-trace.v1</c> (<c>docs/contracts/observer-trace-v1.md</c>):
/// samples each roster avatar's physical state at the trace cadence and records the agent loop's
/// events, all from Godot-owned state. It carries no Fusion state.
///
/// Opt-in: <see cref="TryCreateFromEnvironment"/> returns null unless <c>NLT_OBSERVER_TRACE</c> names
/// a file, and with no recorder the loop runs exactly as before. Writing happens on
/// <see cref="ObserverTraceWriter"/>'s own thread, so nothing here waits on the disk.
/// </summary>
public sealed class ObserverTraceRecorder : IAgentLoopTrace, IDisposable
{
    public const double DefaultHz = 10;
    public const long DefaultMaxBytes = 64L * 1024 * 1024;

    private readonly ObserverTraceWriter _writer;
    private readonly IReadOnlyList<TraceAgent> _agents;
    private readonly double _period;
    private double _sinceSample;
    private int _tick;
    private bool _warnedStop;

    private ObserverTraceRecorder(ObserverTraceWriter writer, TraceHeader header)
    {
        _writer = writer;
        _agents = header.Agents;
        _period = 1.0 / header.TraceHz;
        _sinceSample = _period; // the first frame is sampled: the spawn position
        _writer.TryWrite(ObserverTraceFormat.Header(header));
    }

    /// <summary>The file the trace is written to.</summary>
    public string Path { get; private init; } = "";

    /// <summary>
    /// A recorder for the roster in <paramref name="agents"/>, configured from the environment, or
    /// null when <c>NLT_OBSERVER_TRACE</c> is unset or the file cannot be opened.
    /// <list type="bullet">
    ///   <item><c>NLT_OBSERVER_TRACE</c>: output path (an OS path, or <c>user://</c>/<c>res://</c>).</item>
    ///   <item><c>NLT_OBSERVER_TRACE_HZ</c>: tick-record cadence, 0.1–120 (default 10).</item>
    ///   <item><c>NLT_OBSERVER_TRACE_MAX_MB</c>: size cap in MiB (default 64).</item>
    ///   <item><c>NLT_OBSERVER_TRACE_RUN_ID</c>: run id (default generated).</item>
    ///   <item><c>NLT_ENGINE_COMMIT</c>: engine commit (default read from the checkout's .git).</item>
    /// </list>
    /// </summary>
    public static ObserverTraceRecorder? TryCreateFromEnvironment(IReadOnlyList<TraceAgent> agents)
    {
        string raw = OS.GetEnvironment("NLT_OBSERVER_TRACE").Trim();
        if (raw.Length == 0)
            return null;
        string path = raw.Contains("://", StringComparison.Ordinal) ? ProjectSettings.GlobalizePath(raw) : raw;

        double hz = DefaultHz;
        string rawHz = OS.GetEnvironment("NLT_OBSERVER_TRACE_HZ").Trim();
        if (rawHz.Length > 0 && !(double.TryParse(rawHz, System.Globalization.NumberStyles.Float,
                System.Globalization.CultureInfo.InvariantCulture, out hz) && hz >= 0.1 && hz <= 120))
        {
            GD.PushWarning($"[ObserverTrace] NLT_OBSERVER_TRACE_HZ '{rawHz}' is not 0.1-120; using {DefaultHz}.");
            hz = DefaultHz;
        }

        long maxBytes = DefaultMaxBytes;
        string rawMb = OS.GetEnvironment("NLT_OBSERVER_TRACE_MAX_MB").Trim();
        if (rawMb.Length > 0)
        {
            if (long.TryParse(rawMb, out long mb) && mb >= 1 && mb <= 4096)
                maxBytes = mb * 1024 * 1024;
            else
                GD.PushWarning($"[ObserverTrace] NLT_OBSERVER_TRACE_MAX_MB '{rawMb}' is not 1-4096; using 64.");
        }

        string runId = OS.GetEnvironment("NLT_OBSERVER_TRACE_RUN_ID").Trim();
        DateTime start = DateTime.UtcNow;
        if (runId.Length == 0)
            runId = $"run-{start:yyyyMMdd'T'HHmmss'Z'}-{Guid.NewGuid().ToString("N")[..8]}";

        var header = new TraceHeader(runId, EngineCommit(), (string)Engine.GetVersionInfo()["string"],
            start, hz, maxBytes, agents);
        try
        {
            string? dir = System.IO.Path.GetDirectoryName(System.IO.Path.GetFullPath(path));
            if (!string.IsNullOrEmpty(dir))
                Directory.CreateDirectory(dir);
            var writer = new ObserverTraceWriter(path, maxBytes);
            var recorder = new ObserverTraceRecorder(writer, header) { Path = path };
            GD.Print($"[ObserverTrace] writing {ObserverTraceFormat.SchemaVersion} to {path} " +
                $"(run {runId}, {hz} Hz, cap {maxBytes / (1024 * 1024)} MiB, {agents.Count} agent(s))");
            return recorder;
        }
        catch (Exception e) when (e is IOException or UnauthorizedAccessException or ArgumentException
            or NotSupportedException)
        {
            GD.PushWarning($"[ObserverTrace] cannot open {path} ({e.GetType().Name}: {e.Message}); no trace.");
            return null;
        }
    }

    /// <summary>
    /// Called once per <see cref="AgentLoopDriver"/> frame, after it advances its tick. Samples the
    /// roster avatars when a trace period has passed. Main thread only.
    /// </summary>
    public void OnFrame(int tick, double delta, IReadOnlyList<AvatarCharacter> avatars)
    {
        Volatile.Write(ref _tick, tick);
        ReportStopOnce();
        _sinceSample += delta;
        if (_sinceSample < _period)
            return;
        _sinceSample -= _period;
        if (_sinceSample >= _period)
            _sinceSample = 0;
        foreach (var agent in _agents)
            foreach (var avatar in avatars)
                if (avatar.AgentId == agent.EngineId)
                {
                    TickRecord(tick, agent.AgentId, avatar);
                    break;
                }
    }

    private void TickRecord(int tick, string agentId, AvatarCharacter avatar)
    {
        string sceneId = avatar.SceneId ?? "";
        string kind = SceneCatalog.TryKindFor(sceneId, out string k) ? k : "unknown";
        Vector3 p = avatar.GlobalPosition;
        Vector3 v = avatar.Velocity;
        Write(() => ObserverTraceFormat.Tick(tick, agentId, sceneId, kind, p.X, p.Y, p.Z, v.X, v.Y, v.Z));
    }

    /// <summary>The avatar went through a doorway. Main thread, after it was placed.</summary>
    public void SceneTransition(AvatarCharacter avatar, string from, string to)
    {
        string agentId = WireIdFor(avatar.AgentId);
        int tick = Volatile.Read(ref _tick);
        Write(() => ObserverTraceFormat.SceneTransition(agentId, from, to, tick));
    }

    public void PerceptionSent(AgentPerceptionSnapshot perception)
        => Write(() => ObserverTraceFormat.PerceptionSent(perception.Tick, perception.AgentId, perception.MessageId));

    public void IntentReceived(SemanticIntent intent)
    {
        int at = Volatile.Read(ref _tick);
        Write(() => ObserverTraceFormat.Intent(intent.MessageId, intent.AgentId, intent.ObservedTick,
            intent.Verb, intent.TargetId, at));
    }

    public void DecisionFailed(string agentId, int tick, int? httpStatus, string error, string? detail)
    {
        int at = Volatile.Read(ref _tick);
        Write(() => ObserverTraceFormat.DecisionFailed(agentId, tick, httpStatus, error, detail, at));
    }

    public void IntentResult(IntentExecutionResult result, string stage, string? governanceCode)
    {
        int at = Volatile.Read(ref _tick);
        Write(() => ObserverTraceFormat.Result(result.IntentMessageId, result.AgentId, result.Tick,
            result.Status, stage, governanceCode, result.Reason, at));
    }

    private string WireIdFor(string engineId)
    {
        foreach (var a in _agents)
            if (a.EngineId == engineId)
                return a.AgentId;
        return engineId;
    }

    // The trace must never change what the loop does, so a record that cannot be built is skipped.
    private void Write(Func<string> build)
    {
        string line;
        try
        {
            line = build();
        }
        catch (Exception e) when (e is ArgumentException or InvalidOperationException or FormatException)
        {
            return;
        }
        _writer.TryWrite(line);
    }

    private void ReportStopOnce()
    {
        if (_warnedStop || _writer.StopReason is not string reason)
            return;
        _warnedStop = true;
        GD.PushWarning($"[ObserverTrace] trace stopped ({reason}) after {_writer.BytesWritten} bytes; " +
            "the file ends with a truncated record and nothing more is written.");
    }

    public void Dispose() => _writer.Dispose();

    /// <summary>NLT_ENGINE_COMMIT, else the checkout's HEAD commit read from .git, else "unknown".</summary>
    private static string EngineCommit()
    {
        string fromEnv = OS.GetEnvironment("NLT_ENGINE_COMMIT").Trim();
        if (fromEnv.Length > 0)
            return fromEnv;
        try
        {
            // res:// is world-engine-godot/; the repository root is its parent.
            string root = System.IO.Path.GetFullPath(System.IO.Path.Combine(ProjectSettings.GlobalizePath("res://"), ".."));
            string git = System.IO.Path.Combine(root, ".git");
            if (File.Exists(git)) // a worktree: "gitdir: <path>"
            {
                string pointer = File.ReadAllText(git).Trim();
                if (pointer.StartsWith("gitdir:", StringComparison.Ordinal))
                    git = System.IO.Path.GetFullPath(System.IO.Path.Combine(root, pointer[7..].Trim()));
            }
            string head = File.ReadAllText(System.IO.Path.Combine(git, "HEAD")).Trim();
            if (!head.StartsWith("ref:", StringComparison.Ordinal))
                return head;
            string refName = head[4..].Trim();
            string loose = System.IO.Path.Combine(git, refName);
            if (File.Exists(loose))
                return File.ReadAllText(loose).Trim();
            string packed = System.IO.Path.Combine(git, "packed-refs");
            if (File.Exists(packed))
                foreach (string line in File.ReadLines(packed))
                    if (line.EndsWith(" " + refName, StringComparison.Ordinal))
                        return line[..line.IndexOf(' ')];
        }
        catch (Exception e) when (e is IOException or UnauthorizedAccessException or ArgumentException)
        {
        }
        return "unknown";
    }
}
