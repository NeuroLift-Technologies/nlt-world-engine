using System.Collections.Generic;
using System;
using System.Threading.Tasks;
using Godot;
using NltWorldEngine.Observer.Trace;

namespace NltWorldEngine.Agents;

/// <summary>
/// Drives the async HTTP loop for live avatars: builds a perception per avatar at
/// the decision cadence, POSTs it via <see cref="FusionHttpLink"/>, and applies the
/// correlated intent through <see cref="IntentIngress"/> (protocol → ASFDK governance
/// → live-world re-check → locomotion). Off by default; enable alongside
/// Main.EnableLiveAvatars. Physics/render threads never block on inference.
/// </summary>
public partial class AgentLoopDriver : Node
{
    private FusionHttpLink _link = null!;
    private IntentIngress _ingress = null!;
    private readonly Dictionary<string, float> _sincePost = new();
    private int _tick;
    private int _messageSeq;
    private string? _unknownSceneReported;
    private double _sinceTickRecord = double.MaxValue;
    private readonly Dictionary<string, string> _tracedScene = new();

    /// <summary>Seconds between perception posts per avatar. Matches the low-frequency cycle.</summary>
    [Export] public float DecisionCadenceSeconds { get; set; } = 2f;

    /// <summary>When false the driver posts nothing; avatars keep their local controllers.</summary>
    [Export] public bool Enabled { get; set; } = false;

    /// <summary>
    /// Observer trace for this run (docs/contracts/observer-trace-v1.md). Set before the driver
    /// enters the tree. Off by default; the driver disposes it on exit.
    /// </summary>
    public ITraceSink Trace { get; set; } = NullTraceSink.Instance;

    /// <summary>How often <c>tick</c> records are sampled, per second of engine time.</summary>
    [Export] public float TraceCadenceHz { get; set; } = 10f;

    /// <summary>Only this avatar receives decisions; defaults to the dedicated local test avatar.</summary>
    [Export] public string TargetAgentId { get; set; } = "__local_avatar__";

    /// <summary>
    /// The roster id Fusion registered for <see cref="TargetAgentId"/>, sent as the perception's
    /// <c>agentId</c> (AGENT-LOOP-003 F0; e.g. <c>stay_alert_001</c>). Empty sends the internal key,
    /// which Fusion does not serve, so no intent is ever applied.
    /// </summary>
    [Export] public string PerceptionAgentId { get; set; } = "";

    /// <summary>Fusion endpoint; may be overridden from the composition root for local testing.</summary>
    [Export] public string FusionEndpoint
    {
        get => _fusionEndpoint;
        set
        {
            _fusionEndpoint = value;
            if (_link != null)
                _link.FusionEndpoint = value;
        }
    }

    private string _fusionEndpoint = "http://127.0.0.1:8001/agent-loop/perception";

    /// <summary>
    /// Task anchors in a given scene, for perception + affordance checks (AGENT-LOOP-002 T2). Asked
    /// with the avatar's own scene id, so an avatar in a room never sees open-world places.
    /// </summary>
    public Func<string, IReadOnlyList<TaskAnchor>> AnchorsFor { get; set; } = _ => System.Array.Empty<TaskAnchor>();

    /// <summary>
    /// The engine's scene transition, for <c>use</c> on a doorway (AGENT-LOOP-002 T3). Null means
    /// doorways are rejected at ingress.
    /// </summary>
    public IPortalTransit? Transit { get; set; }

    public override void _Ready()
    {
        _link = new FusionHttpLink { Name = "FusionHttpLink" };
        _link.FusionEndpoint = _fusionEndpoint;
        _link.Trace = Trace;
        _link.TickNow = () => _tick;
        AddChild(_link);
        _ingress = new IntentIngress(
            new AsfdkGovernanceGate(),
            ResolveTarget,
            sceneId => AnchorsFor(sceneId),
            RunOnMainThreadAsync,
            Transit,
            Trace);
    }

    public override void _ExitTree()
    {
        // A clean exit (--quit-after) closes the file; SIGHUP skips this, which is why the writer
        // flushes every line.
        (Trace as IDisposable)?.Dispose();
        base._ExitTree();
    }

    private static Task<IntentExecutionResult> RunOnMainThreadAsync(
        Func<IntentExecutionResult> action)
    {
        var completion = new TaskCompletionSource<IntentExecutionResult>(
            TaskCreationOptions.RunContinuationsAsynchronously);
        Callable.From(() =>
        {
            try
            {
                completion.TrySetResult(action());
            }
            catch (Exception e)
            {
                completion.TrySetException(e);
            }
        }).CallDeferred();
        return completion.Task;
    }

    public override void _Process(double delta)
    {
        if (!Enabled)
            return;
        _tick++;
        var avatars = GetAvatars();
        TraceSample(avatars, delta);
        foreach (var avatar in avatars)
        {
            if (!string.Equals(avatar.AgentId, TargetAgentId, StringComparison.Ordinal))
                continue;
            if (!_sincePost.TryGetValue(avatar.AgentId, out var t))
                t = DecisionCadenceSeconds;
            t += (float)delta;
            if (t < DecisionCadenceSeconds)
            {
                _sincePost[avatar.AgentId] = t;
                continue;
            }
            _sincePost[avatar.AgentId] = 0f;
            // Fail closed on a scene the engine cannot name: post nothing rather than tell Fusion a
            // guessed kind. The avatar keeps its local controller meanwhile.
            if (!SceneCatalog.TryKindFor(avatar.SceneId, out _))
            {
                if (_unknownSceneReported != avatar.SceneId)
                {
                    _unknownSceneReported = avatar.SceneId;
                    GD.PushError($"[AgentLoopDriver] unknown scene id '{avatar.SceneId}' for " +
                        $"{avatar.AgentId}; no perception posted.");
                }
                continue;
            }
            var perception = PerceptionBuilder.Build(
                avatar, _tick, $"obs-{_tick}-{avatar.AgentId}-{_messageSeq++}",
                AnchorsFor(avatar.SceneId), avatars, PerceptionAgentId);
            GD.Print($"[AgentLoopDriver] perception tick={_tick}, agent={perception.AgentId}, " +
                $"scene={perception.Scene.Id}/{perception.Scene.Kind}, " +
                $"position={avatar.GlobalPosition}, visible={perception.VisibleEntities.Count}");
            if (_link.RequestDecision(avatar, perception, _ingress, _tick) && Trace.Enabled)
                Trace.Write(new PerceptionSentRecord
                {
                    Tick = perception.Tick,
                    AgentId = perception.AgentId,
                    MessageId = perception.MessageId,
                    VisibleEntities = perception.VisibleEntities.Count,
                });
        }
    }

    /// <summary>The id an avatar goes by on the wire, so trace ticks line up with its intents.</summary>
    private string TraceAgentId(AvatarCharacter avatar)
        => string.Equals(avatar.AgentId, TargetAgentId, StringComparison.Ordinal)
            ? PerceptionBuilder.WireAgentId(avatar.AgentId, PerceptionAgentId)
            : avatar.AgentId;

    /// <summary>
    /// Observer trace: scene changes every frame (a transition is instantaneous), physical state at
    /// <see cref="TraceCadenceHz"/>. Reads the scene; changes nothing.
    /// </summary>
    private void TraceSample(List<AvatarCharacter> avatars, double delta)
    {
        if (!Trace.Enabled)
            return;
        foreach (var avatar in avatars)
        {
            var sceneId = avatar.SceneId;
            if (string.IsNullOrEmpty(sceneId))
                continue;
            var id = TraceAgentId(avatar);
            if (_tracedScene.TryGetValue(id, out var previous) && previous == sceneId)
                continue;
            if (previous != null)
                Trace.Write(new SceneTransitionRecord { AgentId = id, From = previous, To = sceneId, Tick = _tick });
            _tracedScene[id] = sceneId;
            Trace.Write(SceneEntities(sceneId));
        }

        _sinceTickRecord += delta;
        if (TraceCadenceHz <= 0f || _sinceTickRecord < 1.0 / TraceCadenceHz)
            return;
        _sinceTickRecord = 0;
        foreach (var avatar in avatars)
        {
            if (string.IsNullOrEmpty(avatar.SceneId))
                continue;
            var kind = SceneCatalog.TryKindFor(avatar.SceneId, out var k) ? k : "unknown";
            var p = avatar.GlobalPosition;
            var v = avatar.Velocity;
            Trace.Write(new TickRecord
            {
                Tick = _tick,
                AgentId = TraceAgentId(avatar),
                Scene = new TraceScene { Id = avatar.SceneId, Kind = kind },
                Position = TraceVector.Of(p.X, p.Y, p.Z),
                Velocity = TraceVector.Of(v.X, v.Y, v.Z),
            });
        }
    }

    private SceneEntitiesRecord SceneEntities(string sceneId)
    {
        var entities = new List<TraceEntity>();
        foreach (var anchor in AnchorsFor(sceneId))
            entities.Add(new TraceEntity
            {
                Id = anchor.Id,
                Kind = anchor.Kind,
                Position = TraceVector.Of(anchor.Position.X, anchor.Position.Y, anchor.Position.Z),
                Affordances = AnchorAffordances.For(anchor),
            });
        return new SceneEntitiesRecord { Scene = sceneId, Tick = _tick, Entities = entities };
    }

    private List<AvatarCharacter> GetAvatars()
    {
        var list = new List<AvatarCharacter>();
        var root = GetTree().CurrentScene ?? GetTree().Root;
        CollectAvatars(root, list);
        return list;
    }

    private static void CollectAvatars(Node node, List<AvatarCharacter> into)
    {
        foreach (var child in node.GetChildren())
        {
            if (child is AvatarCharacter avatar)
                into.Add(avatar);
            CollectAvatars(child, into);
        }
    }

    private Vector3? ResolveTarget(string targetId)
    {
        // Anchors first, in the deciding avatar's own scene: an anchor's position is its approach
        // point, and a scene node that happens to share the id (an interior mesh, say) would
        // otherwise resolve to that node's centre, inside its collision.
        var avatars = GetAvatars();
        foreach (var avatar in avatars)
        {
            if (avatar.AgentId != TargetAgentId)
                continue;
            foreach (var anchor in AnchorsFor(avatar.SceneId))
                if (anchor.Id == targetId)
                    return anchor.Position;
        }
        var root = GetTree().CurrentScene ?? GetTree().Root;
        var node = FindByName(root, targetId);
        if (node is Node3D n3)
            return n3.GlobalPosition;
        foreach (var avatar in avatars)
            if (avatar.AgentId == targetId)
                return avatar.GlobalPosition;
        return null;
    }

    private static Node? FindByName(Node node, string name)
    {
        if (node.Name == name)
            return node;
        foreach (var child in node.GetChildren())
        {
            var found = FindByName(child, name);
            if (found != null)
                return found;
        }
        return null;
    }
}
