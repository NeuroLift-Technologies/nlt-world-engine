using System;
using Godot;

namespace NltWorldEngine.Agents;

/// <summary>
/// One agent whose position is owned by the Jolt physics engine via <see cref="CharacterBody3D"/>.
///
/// AgentBrain is the CharacterBody3D scene root for a live avatar. It:
///   1. Runs the decision loop (poll IAgentController, validate, apply).
///   2. Translates the accepted AgentAction into a physics velocity.
///   3. Calls MoveAndSlide() each physics tick so Jolt resolves collisions.
///   4. Keeps LocomotionController in sync for direction/speed math (accel/decel ramps),
///      but no longer lets it write Position directly — the physics body owns position.
///
/// The IAgentController seam is unchanged: Fusion, LLM, utility, or RL all drop in.
/// </summary>
public partial class AgentBrain : CharacterBody3D
{
    // --- Gravity ------------------------------------------------------------------
    // Standard Godot approach: cache gravity once from project settings.
    private static readonly float Gravity =
        (float)ProjectSettings.GetSetting("physics/3d/default_gravity");

    // --- State --------------------------------------------------------------------
    private IAgentController? _controller;
    private LocomotionController _locomotion = null!;
    private AgentObservation _observation;
    private DecisionHold _decision;
    private float _sinceDecision;

    /// <summary>Which way round the obstacle in front is being walked: 0 none, ±1 a side.</summary>
    private int _detourSide;
    private int _tick;

    // --- Events -------------------------------------------------------------------
    /// <summary>Raised each tick with the action actually applied, for HUD/debug and the observer.</summary>
    public event Action<AgentAction>? Acted;

    /// <summary>Raised when a decision was rejected by validation, with the reason.</summary>
    public event Action<string>? Rejected;

    // --- Public API ---------------------------------------------------------------
    /// <summary>The locomotion state (velocity/yaw). Resident reads this for visuals.</summary>
    public LocomotionController Locomotion => _locomotion;

    public string AgentId { get; private set; } = "";

    /// <summary>Scene the agent is currently deciding in. Set by Observe, read by ingress.</summary>
    public string SceneId => _observation.SceneId;

    /// <summary>
    /// Seconds between decisions. Inference is far slower than a tick, so the last accepted
    /// decision is held and re-applied between decisions (motor-latency technique). The hold lives
    /// in <see cref="DecisionHold"/>; this interval only governs how often the controller is polled.
    /// </summary>
    [Export] public float DecisionInterval { get; set; } = 0.5f;

    [Export] public float MaxSpeed { get; set; } = 1.4f;

    // --- Controller wiring --------------------------------------------------------
    /// <summary>Attach the cognition that supplies decisions. May be null — the agent holds still.</summary>
    public void Attach(IAgentController controller)
    {
        // The outgoing controller gives back what it holds first: a tour replaced mid-route
        // otherwise kept its anchor reserved for good.
        if (_controller != null && !ReferenceEquals(_controller, controller))
            _controller.Detach(AgentId);
        _controller = controller;
        controller.Attach(AgentId);
    }

    /// <summary>
    /// Seed the observation this agent decides from. Called by the owner when surrounding state
    /// changes, so the model sees the world rather than a frozen first frame.
    /// </summary>
    public void Observe(Vector3 position, float[] needs, string sceneId)
    {
        _observation = new AgentObservation(AgentId, position, Velocity, needs, sceneId, _tick);
    }

    // --- Godot lifecycle ----------------------------------------------------------
    public override void _Ready()
    {
        AgentId = string.IsNullOrEmpty(Name) ? "avatar_0" : Name.ToString();
        _locomotion = new LocomotionController { MaxSpeed = MaxSpeed };

        // Grounded movement mode: walls/floors/ceilings are distinguished, slopes apply.
        MotionMode = MotionModeEnum.Grounded;
        UpDirection = Vector3.Up;
        FloorMaxAngle = Mathf.DegToRad(46f);
    }

    // --- Engine-owned placement (AGENT-LOOP-002 T3) ------------------------------
    // "Models clamp, never teleport" (world-engine-godot/AGENTS.md §3): no intent can place this
    // body. The engine itself has exactly two reasons to, both routed through PlaceAt so there is one
    // placement path: the kill-plane recovery below, and the scene transition when an avatar uses a
    // door or a room's exit (TransitionTo) — the one engine-owned discontinuity Joshua approved on
    // 2026-10-17. Neither is reachable from an intent payload: ingress only ever names a target.

    private bool _held;

    /// <summary>
    /// Where a fall inside a room recovers to: the spot the avatar entered the room at. Set by the
    /// transition; null in the open world, where recovery uses the terrain.
    /// </summary>
    public Vector3? InteriorRecoveryPoint { get; set; }

    /// <summary>True between <see cref="HoldForTransition"/> and the placement (or release) that ends it.</summary>
    public bool InTransition => _held;

    /// <summary>
    /// Freeze the body while the engine swaps scenes: no decisions, no gravity, no movement, no
    /// kill-plane. The scene it stood in may have its collision switched off under it.
    /// </summary>
    public void HoldForTransition()
    {
        _held = true;
        Velocity = Vector3.Zero;
        _decision = default;
    }

    /// <summary>Let a held body go where it stands, for a transition that failed before placing it.</summary>
    public void ReleaseHold() => _held = false;

    /// <summary>
    /// Put this body in <paramref name="sceneId"/> at <paramref name="position"/>, facing
    /// <paramref name="facing"/> (AGENT-LOOP-002 T3). Only the engine's scene transition calls this.
    /// </summary>
    public void TransitionTo(Vector3 position, string sceneId, Vector3 facing)
    {
        PlaceAt(position);
        _observation = new AgentObservation(AgentId, position, Vector3.Zero, _observation.Needs, sceneId, _tick);
        _held = false;
        OnPlaced(facing);
    }

    /// <summary>
    /// After a placement: subclasses turn their visual and hand control back to local autonomy.
    /// </summary>
    protected virtual void OnPlaced(Vector3 facing) { }

    /// <summary>
    /// Stop executing the held decision now rather than at the next controller poll (up to
    /// <see cref="DecisionInterval"/> later). The body decelerates through the locomotion ramp as
    /// usual — nothing is placed. Used when an interaction starts holding still (AGENT-LOOP-002 T6).
    /// </summary>
    protected void DropHeldDecision() => _decision = default;

    /// <summary>
    /// The single placement path: position, zero velocity, locomotion reset, and the held decision
    /// cleared so the last move does not keep playing from the new spot.
    /// </summary>
    private void PlaceAt(Vector3 position)
    {
        GlobalPosition = position;
        Velocity = Vector3.Zero;
        _locomotion.Teleport(position);
        _decision = default;
        _sinceDecision = 0f;
    }

    public override void _PhysicsProcess(double delta)
    {
        if (_held)
            return;
        var dt = (float)delta;
        _tick++;

        // 1. Rebuild observation from the physics body's actual position.
        //    This closes the loop: the model sees where it physically is, not where math put it.
        _observation = new AgentObservation(
            _observation.AgentId,
            GlobalPosition,
            Velocity,
            _observation.Needs,
            _observation.SceneId,
            _tick);

        // 2. Decision phase — poll only at the configured interval, and hold the accepted
        //    decision in between. Both inference and this interval are slower than a physics tick,
        //    so the ticks that skip a poll must keep executing the previous decision. Resetting to
        //    Idle here instead would give one frame of acceleration per poll and cancel it on the
        //    next frame, leaving the agent creeping rather than walking.
        _sinceDecision += dt;
        if (_sinceDecision >= DecisionInterval)
        {
            _sinceDecision = 0f;
            if (_controller != null)
            {
                var proposed = _controller.Act(_observation);
                var problem = Validate(proposed);
                if (problem == null)
                    _decision.Accept(proposed);
                else
                {
                    _controller.OnActionRejected(_observation, proposed, problem);
                    Rejected?.Invoke(problem);
                }
            }
        }

        var action = _decision.Current;

        // 3. Compute desired XZ velocity via LocomotionController ramps (accel/decel/turn).
        //    We pass the current physics velocity in so the ramp starts from the correct speed.
        //    A heading that last tick's slide met head-on is turned along the obstacle first, so a
        //    straight-line controller walks round a tree trunk instead of pushing at it for good.
        _locomotion.SyncFromPhysics(Velocity);
        var steered = LocomotionController.AroundObstacle(action, IsOnWall() ? GetWallNormal() : Vector3.Zero, ref _detourSide);
        _locomotion.Step(steered, dt);

        // 4. Build final velocity: XZ from locomotion, Y from gravity (Jolt handles it).
        var newVelocity = new Vector3(
            _locomotion.Velocity.X,
            IsOnFloor() ? 0f : Velocity.Y - Gravity * dt,
            _locomotion.Velocity.Z);

        Velocity = newVelocity;

        // 5. Let Jolt resolve collisions.
        MoveAndSlide();
        if (OS.HasEnvironment("NLT_DEBUG_FALL") && Engine.GetPhysicsFrames() % 30 == 0)
            GD.Print($"FALLDBG f={Engine.GetPhysicsFrames()} pos={GlobalPosition} ground={WorldGeometry.HeightAt(GlobalPosition.X, GlobalPosition.Z):F2} floor={IsOnFloor()} scene={SceneId}");

        // 6. Kill-plane: tunnelling past every body (or a level with no collision at all) must
        //    end standing on the terrain, not falling forever. Same XZ clamped to the island so
        //    the reset cannot land outside the new edge walls — unless that spot is under water,
        //    where the reset used to drop the avatar onto the sea bed; then it goes to the plaza.
        if (GlobalPosition.Y < TerrainBuilderPhysics.KillY)
        {
            float half = WorldConstants.World * 0.5f;
            float sx = Mathf.Clamp(GlobalPosition.X, -half, half);
            float sz = Mathf.Clamp(GlobalPosition.Z, -half, half);
            // Scene-aware: WorldGeometry.HeightAt only knows the procedural island, not UCX
            // interior floors. An interior avatar that falls through recovers to where it entered
            // the room, instead of being teleported onto open-world terrain.
            if (SceneCatalog.IsOpenWorld(SceneId))
            {
                Vector3 landing = WorldGeometry.HeightAt(sx, sz) > WorldConstants.Water + 0.5f
                    ? new Vector3(sx, WorldGeometry.HeightAt(sx, sz), sz)
                    : WorldGeometry.PlazaSpawn();
                PlaceAt(landing + new Vector3(0f, 1.5f, 0f));
            }
            else
            {
                PlaceAt(InteriorRecoveryPoint ?? new Vector3(sx, 1f, sz));
            }
        }

        Acted?.Invoke(action);
    }

    // --- Validation ---------------------------------------------------------------
    private static string? Validate(in AgentAction action)
    {
        var d = action.MoveDirection;
        if (!float.IsFinite(d.X) || !float.IsFinite(d.Y) || !float.IsFinite(d.Z))
            return "non-finite direction";
        if (d.Length() > 1.001f)
            return $"direction magnitude {d.Length():F2} exceeds 1 (effort is 0..1, not a speed)";
        if (Mathf.Abs(d.Y) > 0.001f)
            return "direction has a Y component (locomotion is XZ-only)";
        return null;
    }
}
