using System;
using System.Collections.Generic;
using System.IO;
using Godot;

namespace NltWorldEngine.Observer.Trace;

/// <summary>
/// Decides whether this run writes an observer trace, and opens it.
///
/// Off unless asked for, in one of two ways:
/// <list type="bullet">
/// <item><c>-- --trace [path]</c> on the command line (after Godot's bare <c>--</c>).</item>
/// <item><c>NLT_OBSERVER_TRACE=1</c> for the default path, or <c>NLT_OBSERVER_TRACE=&lt;path&gt;</c>.</item>
/// </list>
/// The default path is <c>user://traces/&lt;runId&gt;.jsonl</c>. Kept apart from
/// <see cref="ObserverTraceWriter"/> because it reads Godot's OS and project settings, and the
/// writer must stay loadable outside the engine.
/// </summary>
public static class ObserverTraceLauncher
{
    /// <summary>The trace this run asked for, or the no-op sink. Never throws: a trace that cannot
    /// be opened is reported and the run continues untraced.</summary>
    public static ITraceSink FromCommandLine(IReadOnlyList<string> agentRoster, float cadenceHz)
    {
        var requested = RequestedPath(OS.GetCmdlineUserArgs(), OS.GetEnvironment("NLT_OBSERVER_TRACE"));
        if (requested == null)
            return NullTraceSink.Instance;

        var now = DateTime.UtcNow;
        var header = new TraceHeader
        {
            RunId = TraceHeader.NewRunId(now),
            EngineCommit = EnvOr("NLT_ENGINE_COMMIT", "unknown"),
            GodotVersion = Engine.GetVersionInfo()["string"].AsString(),
            StartTime = now.ToString("yyyy-MM-dd'T'HH:mm:ss'Z'"),
            AgentRoster = agentRoster,
            CadenceHz = cadenceHz,
        };
        var path = requested.Length == 0 ? $"user://traces/{header.RunId}.jsonl" : requested;
        if (path.StartsWith("res://", StringComparison.Ordinal) || path.StartsWith("user://", StringComparison.Ordinal))
            path = ProjectSettings.GlobalizePath(path);
        try
        {
            var writer = ObserverTraceWriter.Open(path, header);
            GD.Print($"[ObserverTrace] writing {ObserverTraceVocabulary.SchemaVersion} to {path} (run {header.RunId})");
            return writer;
        }
        catch (Exception e) when (e is IOException or UnauthorizedAccessException or ArgumentException
            or NotSupportedException)
        {
            GD.PushError($"[ObserverTrace] could not open {path}: {e.Message}. Running without a trace.");
            return NullTraceSink.Instance;
        }
    }

    /// <summary>
    /// The path asked for: null when tracing is off, empty for the default path. A flag that
    /// follows <c>--trace</c> is not taken as its path, so <c>--trace --capture out.png</c> means
    /// "default path".
    /// </summary>
    public static string? RequestedPath(string[] userArgs, string? env)
    {
        int at = Array.IndexOf(userArgs, "--trace");
        if (at >= 0)
        {
            var next = at + 1 < userArgs.Length ? userArgs[at + 1] : "";
            return next.StartsWith("--", StringComparison.Ordinal) ? "" : next;
        }
        if (string.IsNullOrWhiteSpace(env) || env.Trim() == "0")
            return null;
        return env.Trim() == "1" ? "" : env.Trim();
    }

    private static string EnvOr(string name, string fallback)
    {
        var value = OS.GetEnvironment(name).Trim();
        return value.Length == 0 ? fallback : value;
    }
}
