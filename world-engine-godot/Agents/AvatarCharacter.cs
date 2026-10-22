using Godot;
using System;
using System.Collections.Generic;
using System.Threading;
using NltWorldEngine.Agents;

namespace NltWorldEngine;

/// <summary>
/// The live avatar: a Jolt-backed <see cref="CharacterBody3D"/> (via <see cref="AgentBrain"/>)
/// with a <see cref="Resident"/> visual body attached.
///
/// Responsibilities:
/// <list type="bullet">
///   <item>Own the collision capsule (added as a child in the scene).</item>
///   <item>Wire <see cref="Resident"/> so the visual follows the physics body every frame.</item>
///   <item>Wire the default <see cref="UtilityAgentController"/> so the avatar walks on spawn.</item>
///   <item>Expose <see cref="ApplyIntent"/> as the engine-side entry point for
///     <c>nlt.agent-loop.v1</c> semantic intents — this is where a validated Fusion intent
///     translates into an <see cref="IAgentController"/> command.
///   </item>
/// </list>
///
/// Scene structure (built in avatar.tscn):
/// <code>
///   AvatarCharacter (CharacterBody3D) &lt;— this script (extends AgentBrain)
///     CollisionShape3D  (CapsuleShape3D, 0.4 r × 1.8 h)
///     Resident          (visual + walk animation + name label)
/// </code>
///
/// This scene is instantiated into a level. The level must have at least one <c>StaticBody3D</c>
/// with collision so gravity gives Jolt something to stand on.
public partial class AvatarCharacter : AgentBrain
{
    private Resident _resident = null!;

    [Export] public string DisplayName { get; set; } = "Avatar";
    [Export] public bool ReducedMotion { get; set; } = false;

    public override void _Ready()
    {
        base._Ready();

        // Locate children wired in the scene.
        _resident = GetNode<Resident>("Resident");
        _resident.Name = $"{Name}_Visual";

        // Default controller: deterministic wandering so the avatar moves immediately.
        // Fusion (or LLM) can replace this at runtime via Attach().
        _spawnFallback = new UtilityAgentController(WorldConstants.Seed, AgentId) { Anchors = Anchors };
        Attach(_spawnFallback);
    }

    /// <summary>
    /// The controller <see cref="_Ready"/> attaches. The composition root sets <see cref="Anchors"/>
    /// only after the avatar is in the tree, so the setter hands them on to it. Without that it
    /// never had destinations and walked its need's fixed bearing (with Main's even needs, due
    /// south) out of town until Fusion's first intent replaced it.
    /// </summary>
    private UtilityAgentController? _spawnFallback;

    public override void _Process(double delta)
    {
        // Sync the visual to the physics body's authoritative position and velocity.
        // Resident is a child so it already inherits position — Sync drives walk
        // animation, facing, and label, not placement.
        _resident.Sync(
            Vector3.Zero,
            Velocity,
            DisplayName,
            _activity,
            ReducedMotion);
        // While interacting, face the object even as the last of the walk decelerates: Sync turns
        // the visual to the direction of travel while there is any.
        if (_facePoint is { } face)
            FaceToward(face);
    }

    // --- Interaction (AGENT-LOOP-002 T6) ---------------------------------------------------------
    // reserve on accept -> walk -> on arrival face the object and hold -> release -> autonomy.
    // Nothing here writes position: the avatar stays where it arrived, beside the object (the
    // anchor's approach point). There are no seated or lying animations yet (character animation is
    // blocked on GRAPH-001 G1), so the pose shows as facing, holding still, and the label's word.

    /// <summary>How long each interaction holds, in seconds of simulation time.</summary>
    public const float SitSeconds = 8f, RestSeconds = 12f, UseSeconds = 5f, LookSeconds = 2f;

    private string _activity = "active";
    private TaskAnchor? _heldAnchor;
    private string? _heldVerb;
    private Vector3? _facePoint;
    private bool _enRoute;

    /// <summary>What the avatar is doing: active, sitting, resting, using or looking. Shown on its label.</summary>
    public string Activity => _activity;

    /// <summary>The anchor this avatar holds while sitting, resting or using it, or null.</summary>
    public TaskAnchor? HeldAnchor => _heldAnchor;

    /// <summary>
    /// Sit on, rest on or use <paramref name="anchor"/>: reserve it now, walk to its approach point,
    /// then hold there facing the object. Returns false, changing nothing, if someone else holds it.
    /// Called by ingress after its affordance and occupancy re-check.
    /// </summary>
    public bool ApplyInteraction(string verb, TaskAnchor anchor)
    {
        // The same interaction again (a model repeating itself each decision) carries on rather than
        // restarting the walk or the hold.
        if (_heldAnchor == anchor && _heldVerb == verb)
            return true;
        EndInteraction();
        _heldVerb = verb;
        if (!anchor.Reserve(AgentId))
            return false;
        _heldAnchor = anchor;
        var toTarget = anchor.Position - GlobalPosition;
        toTarget.Y = 0f;
        const float ArrivalRadius = 1f;
        if (toTarget.LengthSquared() > ArrivalRadius * ArrivalRadius)
            Attach(new IntentMoveController(anchor.Position, verb, ArrivalRadius, _ => BeginHold(verb, anchor)));
        else
            BeginHold(verb, anchor);
        // The controller just replaced may have been a tour walking to this same anchor. Claims are
        // per agent, not per controller, so the tour's Detach released this one: claim it again.
        anchor.Reserve(AgentId);
        return true;
    }

    private void BeginHold(string verb, TaskAnchor anchor)
    {
        if (_heldAnchor != anchor)
            return;
        _facePoint = anchor.FacePoint ?? anchor.Position;
        _activity = verb switch { "sit" => "sitting", "rest" => "resting", _ => "using" };
        float seconds = verb switch { "sit" => SitSeconds, "rest" => RestSeconds, _ => UseSeconds };
        DropHeldDecision();
        Attach(new InteractionController(HoldTicks(seconds), () =>
        {
            EndInteraction();
            Attach(WanderFallback());
        }));
    }

    /// <summary>
    /// Release whatever the avatar holds, stop facing it, and forget any walk to a target: every
    /// caller is about to replace the controller that walk ran on. Safe to call when idle.
    /// </summary>
    private void EndInteraction()
    {
        _enRoute = false;
        _heldAnchor?.Release(AgentId);
        _heldAnchor = null;
        _heldVerb = null;
        _facePoint = null;
        _activity = "active";
    }

    /// <summary>
    /// End any interaction and hold still, freeing what it held. Ingress calls this when
    /// governance denies an intent; without the release, a chair reserved by the denied
    /// interaction would stay occupied for good.
    /// </summary>
    public void Halt()
    {
        EndInteraction();
        Attach(new IdleController());
    }

    /// <summary>A removed avatar frees what it holds, so nobody else is turned away from it.</summary>
    public override void _ExitTree()
    {
        EndInteraction();
        base._ExitTree();
    }

    private void FaceToward(Vector3 point)
    {
        var to = point - GlobalPosition;
        if (new Vector2(to.X, to.Z).LengthSquared() > 0.0001f)
            _resident.Rotation = new Vector3(0f, Mathf.Atan2(to.X, to.Z), 0f);
    }

    private static int HoldTicks(float seconds) => Mathf.Max(1, Mathf.RoundToInt(seconds * Engine.PhysicsTicksPerSecond));

    /// <summary>
    /// Engine-side entry point for a validated <c>nlt.agent-loop.v1</c> semantic intent.
    ///
    /// This is the translation layer from Fusion's vocabulary (approach / sit / rest …) into
    /// the locomotion system. It is intentionally thin — the heavy validation lives in
    /// <see cref="AgentLoopProtocol"/> before this is called; here we only map verb → action.
    ///
    /// Targeted verbs (approach, look_at, use, sit, communicate) need a resolved world position
    /// from the engine's perception snapshot. Pass <paramref name="resolvedTargetPosition"/> when
    /// the target was found in the scene; leave it null for non-targeted verbs.
    /// </summary>
    /// <param name="onArrival">Run once when the avatar reaches the target — or at once if it is
    /// already standing there (AGENT-LOOP-002 T3: <c>use</c> on a doorway transitions on arrival).</param>
    public void ApplyIntent(string verb, Vector3? resolvedTargetPosition = null, Action? onArrival = null)
    {
        // 'wait' carries on with whatever is under way — walking to a target, or walking to a chair
        // and sitting on it. Fusion decides every couple of seconds, so a wait would otherwise stop
        // the avatar short of every target and stand it up almost as soon as it sat. Any other
        // intent ends the interaction and frees what it held.
        if (verb == "wait" && (_heldAnchor != null || _facePoint != null || _enRoute))
            return;
        EndInteraction();

        // look_at: turn to face the target where the avatar stands, hold a moment, then carry on.
        if (verb == "look_at" && resolvedTargetPosition.HasValue)
        {
            _facePoint = resolvedTargetPosition.Value;
            _activity = "looking";
            DropHeldDecision();
            Attach(new InteractionController(HoldTicks(LookSeconds), () =>
            {
                EndInteraction();
                Attach(WanderFallback());
            }));
            return;
        }

        // Targeted movement: walk to the resolved target. (sit / use / rest on an object, and use on a
        // doorway, reach here or ApplyInteraction through ingress; look_at is handled above.)
        if (resolvedTargetPosition.HasValue && (verb is "approach" or "use" or "sit"))
        {
            var toTarget = (resolvedTargetPosition.Value - GlobalPosition);
            toTarget.Y = 0f;
            const float ArrivalRadius = 1f;
            if (toTarget.LengthSquared() > ArrivalRadius * ArrivalRadius)
            {
                // On arrival the avatar holds still (the controller handed back) until Fusion's next
                // intent, and anything owed on arrival — a doorway's transition — runs.
                _enRoute = true;
                Attach(new IntentMoveController(
                    resolvedTargetPosition.Value, verb, ArrivalRadius,
                    controller =>
                    {
                        _enRoute = false;
                        Attach(controller);
                        onArrival?.Invoke();
                    }));
                return;
            }
        }

        // 'wait', and 'rest' with nothing to rest on, hold still where the avatar stands until the
        // next intent (Joshua, 2026-10-21). Wandering here made a model-driven avatar look exactly
        // like one with no model: the model's "stay put" played out as a walk around the world.
        if (verb is "wait" or "rest" && !resolvedTargetPosition.HasValue)
        {
            _activity = verb == "rest" ? "resting" : "waiting";
            DropHeldDecision();
            Attach(new IdleController());
            return;
        }

        // Anything else non-targeted, or already standing at the target: return to local autonomy.
        // Already at the target counts as arriving.
        Attach(WanderFallback());
        if (resolvedTargetPosition.HasValue)
            onArrival?.Invoke();
    }

    /// <summary>
    /// After the engine places this avatar in a new scene: face <paramref name="facing"/> (away from
    /// the door it came through) and go back to local autonomy, as on any arrival.
    /// </summary>
    protected override void OnPlaced(Vector3 facing)
    {
        EndInteraction();
        if (new Vector2(facing.X, facing.Z).LengthSquared() > 0.0001f)
            _resident.Rotation = new Vector3(0f, Mathf.Atan2(facing.X, facing.Z), 0f);
        Attach(WanderFallback());
    }

    /// <summary>
    /// The controller this avatar falls back to when Fusion's last intent is done: an interaction or
    /// a look has ended, a scene transition has placed it, or an intent was already satisfied where
    /// it stands. 'wait' and 'rest' hold still instead, and a governance denial halts it.
    ///
    /// Given the world's destinations, this tours between them; with none, it degrades to the
    /// need-driven wander the avatar already shipped with. Built fresh each call so the tour
    /// re-evaluates where to go next rather than resuming a stale target.
    /// </summary>
    private IAgentController WanderFallback() =>
        new UtilityAgentController(WorldConstants.Seed, AgentId) { Anchors = Anchors };

    /// <summary>
    /// Places this avatar may walk to. Set by the composition root, which is the only place that
    /// knows the anchor set. Empty means need-driven wander with no fixed destinations. Reaches the
    /// spawn controller if it is still attached, as well as every later fallback.
    /// </summary>
    public IReadOnlyList<TaskAnchor> Anchors
    {
        get => _anchors;
        set
        {
            _anchors = value;
            if (_spawnFallback != null)
                _spawnFallback.Anchors = value;
        }
    }

    private IReadOnlyList<TaskAnchor> _anchors = System.Array.Empty<TaskAnchor>();
}

/// <summary>
/// Controller that moves toward a resolved target, then hands control back to the avatar's
/// fallback so the tour continues instead of parking on arrival.
/// </summary>
internal sealed class IntentMoveController : IAgentController
{
    private readonly Vector3 _targetPosition;
    private readonly string _verb;
    private readonly float _arrivalRadius;
    private Action<IAgentController>? _onArrival;
    private int _handedBack;

    public IntentMoveController(
        Vector3 targetPosition,
        string verb,
        float arrivalRadius,
        Action<IAgentController>? onArrival = null)
    {
        _targetPosition = targetPosition;
        _verb = verb;
        _arrivalRadius = arrivalRadius;
        _onArrival = onArrival;
    }

    public void Attach(string agentId) { }

    public AgentAction Act(AgentObservation observation)
    {
        var toTarget = _targetPosition - observation.Position;
        toTarget.Y = 0f;
        if (toTarget.LengthSquared() <= _arrivalRadius * _arrivalRadius)
        {
            // Hand back exactly once. Act runs every physics tick, and handing back on every frame
            // would thrash the controller the callback just installed. The exchange is the guard:
            // _onArrival is nulled atomically before it is invoked.
            if (Interlocked.Exchange(ref _handedBack, 1) == 0)
                _onArrival?.Invoke(new IdleController());
            return AgentAction.Idle;
        }
        return AgentAction.Move(toTarget.Normalized(), 1f);
    }

    public void OnActionRejected(in AgentObservation observation, in AgentAction action, string reason)
        => GD.PushWarning($"[IntentMoveController:{_verb}] rejected: {reason}");
}

/// <summary>
/// Holds the agent still for a number of physics ticks — sitting, resting, using or looking — then
/// hands back exactly once (AGENT-LOOP-002 T6). Counts from the first tick it is asked about.
/// </summary>
internal sealed class InteractionController : IAgentController
{
    private readonly int _holdTicks;
    private Action? _onDone;
    private int? _startTick;

    public InteractionController(int holdTicks, Action onDone)
    {
        _holdTicks = holdTicks;
        _onDone = onDone;
    }

    public void Attach(string agentId) { }

    public AgentAction Act(AgentObservation observation)
    {
        _startTick ??= observation.Tick;
        if (observation.Tick - _startTick.Value >= _holdTicks && _onDone is { } done)
        {
            _onDone = null;
            done();
        }
        return AgentAction.Idle;
    }

    public void OnActionRejected(in AgentObservation observation, in AgentAction action, string reason) { }
}

/// <summary>Controller that keeps the agent still. Used when a non-targeted intent arrives.</summary>
internal sealed class IdleController : IAgentController
{
    public void Attach(string agentId) { }
    public AgentAction Act(AgentObservation observation) => AgentAction.Idle;
    public void OnActionRejected(in AgentObservation observation, in AgentAction action, string reason) { }
}
