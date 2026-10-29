using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using Godot;

namespace NltWorldEngine.Agents;

/// <summary>
/// Test-only companions to the observer trace, for evidence rather than for the app. Both are inert
/// unless their flag is passed after a bare <c>--</c>, like <see cref="Observer.ObserverCapture"/>:
/// <list type="bullet">
///   <item><c>--trace-truth &lt;file&gt;</c>: <see cref="TraceTruthSampler"/>.</item>
///   <item><c>--trace-occupy &lt;anchorId&gt;</c>: <see cref="TraceOccupant"/>.</item>
/// </list>
/// </summary>
public static class TraceTestTools
{
    /// <summary>Add whichever tools the command line asks for under <paramref name="parent"/>.</summary>
    public static void TryCreate(Node parent, Func<AgentLoopDriver?> driver)
    {
        var args = OS.GetCmdlineUserArgs();
        if (Observer.ObserverCapture.ValueAfter(args, "--trace-truth") is string truth)
            parent.AddChild(new TraceTruthSampler(truth, driver) { Name = "TraceTruthSampler" });
        if (Observer.ObserverCapture.ValueAfter(args, "--trace-occupy") is string anchor)
            parent.AddChild(new TraceOccupant(anchor, driver) { Name = "TraceOccupant" });
    }
}

/// <summary>
/// Reads every avatar's position straight from the scene tree on every driver tick and writes it to
/// its own file, so a trace can be checked against the engine (<c>tools/check_observer_trace.py</c>).
/// Deliberately shares nothing with <see cref="ObserverTraceRecorder"/> but the tick number, which is
/// the join key: it finds avatars by walking the tree itself, formats numbers with
/// <c>float.ToString("R")</c> rather than the trace encoder, and writes through a plain stream. It
/// runs after the driver in each frame (<see cref="Node.ProcessPriority"/>), so it reads the same tick
/// and the same physics state the trace sampled.
/// </summary>
public partial class TraceTruthSampler : Node
{
    private readonly string _path;
    private readonly Func<AgentLoopDriver?> _driver;
    private StreamWriter? _out;
    private int _lastTick = -1;

    public TraceTruthSampler(string path, Func<AgentLoopDriver?> driver)
    {
        _path = path;
        _driver = driver;
        ProcessPriority = 1000;
    }

    public override void _Ready()
    {
        string path = _path.Contains("://", StringComparison.Ordinal) ? ProjectSettings.GlobalizePath(_path) : _path;
        _out = new StreamWriter(path, append: false) { AutoFlush = false };
        GD.Print($"[TraceTruth] sampling avatar positions from the scene tree to {path}");
    }

    public override void _Process(double delta)
    {
        if (_out == null || _driver() is not { } driver || driver.Tick == _lastTick)
            return;
        _lastTick = driver.Tick;
        foreach (var avatar in Collect(GetTree().Root, new List<AvatarCharacter>()))
        {
            Vector3 p = avatar.GlobalTransform.Origin;
            Vector3 v = avatar.Velocity;
            _out.Write("{\"tick\":");
            _out.Write(_lastTick.ToString(CultureInfo.InvariantCulture));
            _out.Write(",\"engineId\":\"" + avatar.Name + "\",\"sceneId\":\"" + avatar.SceneId + "\",\"position\":[");
            _out.Write(F(p.X) + "," + F(p.Y) + "," + F(p.Z) + "],\"velocity\":[");
            _out.Write(F(v.X) + "," + F(v.Y) + "," + F(v.Z) + "]}\n");
        }
        // Every frame: a run stopped by SIGHUP must not lose the tail the trace already flushed.
        _out.Flush();
    }

    private static string F(float f) => float.IsFinite(f) ? f.ToString("R", CultureInfo.InvariantCulture) : "null";

    private static List<AvatarCharacter> Collect(Node node, List<AvatarCharacter> into)
    {
        foreach (var child in node.GetChildren())
        {
            if (child is AvatarCharacter a)
                into.Add(a);
            Collect(child, into);
        }
        return into;
    }

    public override void _ExitTree()
    {
        _out?.Flush();
        _out?.Dispose();
        _out = null;
    }
}

/// <summary>
/// Fills one open-world anchor to capacity with placeholder occupants once the loop is running, so
/// a loop intent on it meets a real "occupied" re-check (the record-type scenario in
/// <c>docs/contracts/observer-trace-v1.md</c>). Goes through <see cref="TaskAnchor.Reserve"/> like any
/// other agent, and releases it after <see cref="HoldSeconds"/> so the rest of the run is unchanged.
/// Never used outside that test.
/// </summary>
public partial class TraceOccupant : Node
{
    public const double HoldSeconds = 30;

    private readonly string _anchorId;
    private readonly Func<AgentLoopDriver?> _driver;
    private bool _done;
    private TaskAnchor? _held;
    private readonly List<string> _occupants = new();
    private double _heldFor;

    public TraceOccupant(string anchorId, Func<AgentLoopDriver?> driver)
    {
        _anchorId = anchorId;
        _driver = driver;
    }

    public override void _Process(double delta)
    {
        if (_held != null && (_heldFor += delta) >= HoldSeconds)
        {
            foreach (var id in _occupants)
                _held.Release(id);
            GD.Print($"[TraceOccupant] {_anchorId} released after {HoldSeconds:F0} s");
            _held = null;
        }
        if (_done || _driver() is not { } driver)
            return;
        foreach (var anchor in driver.AnchorsFor(SceneCatalog.OpenWorldId))
        {
            if (anchor.Id != _anchorId)
                continue;
            int n = 0;
            while (n < 64 && anchor.Reserve($"trace_test_occupant_{n}"))
                _occupants.Add($"trace_test_occupant_{n++}");
            _done = true;
            _held = anchor;
            GD.Print($"[TraceOccupant] {_anchorId} held by {n} placeholder occupant(s); it is now full");
            return;
        }
    }
}
