using System;
using Godot;

namespace NltWorldEngine.Agents;

/// <summary>
/// The seam a model is evaluated across — one per agent per tick.
///
/// This is the interface named in the migration plan's controller section, kept as the single
/// substitution point for cognition. It is deliberately synchronous and allocation-light: the
/// out-of-band LLM implementation satisfies it by returning the last decision it managed to
/// produce, because inference takes far longer than a tick.
/// </summary>
public interface IAgentController
{
    /// <summary>Called once at attach, before the first <see cref="Act"/>.</summary>
    void Attach(string agentId);

    /// <summary>
    /// Called when another controller replaces this one, so it can give back what it holds (an
    /// anchor it reserved on the way to it). Most controllers hold nothing.
    /// </summary>
    void Detach(string agentId) { }

    /// <summary>Produce this tick's decision from what the model can see.</summary>
    AgentAction Act(AgentObservation observation);

    /// <summary>Called when a decision is rejected, so an LLM can be told why.</summary>
    void OnActionRejected(in AgentObservation observation, in AgentAction action, string reason);
}

/// <summary>
/// The movement authority. It is the <b>only</b> thing that writes position and velocity.
///
/// Locomotion realism lives here and nowhere else — acceleration and deceleration caps, turn-rate
/// limits, friction and inertia. A model can ask to go north; it cannot ask to be 40 m away next
/// tick. That is the entire point of keeping this separate from <see cref="IAgentController"/>.
///
/// Two execution paths use this class:
/// <list type="bullet">
///   <item>
///     <b>Harness / test path</b> — no physics body. <see cref="Step"/> integrates
///     <see cref="Position"/> directly and <see cref="SyncFromPhysics"/> is never called.
///     This is what <c>ActionAssertions</c> uses.
///   </item>
///   <item>
///     <b>Live physics path</b> — <c>AgentBrain._PhysicsProcess</c> calls
///     <see cref="SyncFromPhysics"/> before each <see cref="Step"/> to bring the XZ velocity
///     back from the Jolt <c>CharacterBody3D</c> after collision resolution.
///     <see cref="Position"/> drifts in this path and must not be used for authoritative placement;
///     <c>AgentBrain.GlobalPosition</c> is authoritative instead.
///   </item>
/// </list>
/// </summary>
public sealed class LocomotionController
{
    /// <summary>Straight-line top speed, m/s. Matches the walk-cycle clip's nominal pace.</summary>
    public float MaxSpeed { get; set; } = 1.4f;

    /// <summary>Acceleration cap, m/s². This is what makes a direction change ramp instead of snap.</summary>
    public float Acceleration { get; set; } = 6f;

    /// <summary>Deceleration cap, m/s². Separate from acceleration so stopping settles cleanly.</summary>
    public float Deceleration { get; set; } = 8f;

    /// <summary>Turn rate cap, rad/s. Facing eases toward the heading instead of snapping.</summary>
    public float TurnRate { get; set; } = 6f;

    /// <summary>Speed below which the agent counts as standing still (drives the idle animation).</summary>
    public float StopSpeed { get; set; } = 0.05f;

    /// <summary>
    /// Integrated position for the harness/test path. Not authoritative in the live physics path —
    /// use <c>AgentBrain.GlobalPosition</c> there.
    /// </summary>
    public Vector3 Position { get; private set; }

    public Vector3 Velocity { get; private set; }

    /// <summary>Heading in radians, eased toward the movement direction.</summary>
    public float Yaw { get; private set; }

    /// <summary>True while moving fast enough to animate a walk.</summary>
    public bool IsMoving => new Vector2(Velocity.X, Velocity.Z).Length() > StopSpeed;

    /// <summary>
    /// Advance one tick. <paramref name="dt"/> is seconds; callers own the clock.
    /// </summary>
    public void Step(in AgentAction action, float dt)
    {
        if (dt <= 0f)
            return;

        // 1. Derive a desired velocity from the semantic intent. Magnitude is clamped to MaxSpeed
        //    here — the model's effort value is advisory and never becomes a speed write.
        var heading = new Vector3(action.MoveDirection.X, 0f, action.MoveDirection.Z);
        var effort = Mathf.Clamp(heading.Length(), 0f, 1f);
        var desired = effort > 0f ? heading.Normalized() * (MaxSpeed * effort) : Vector3.Zero;

        // 2. Move actual velocity toward desired under the accel/decel caps. Exponential-free and
        //    frame-rate independent in the usual way: the cap is a rate, multiplied by dt.
        var flat = new Vector3(Velocity.X, 0f, Velocity.Z);
        var delta = desired - flat;
        var rate = (desired.Length() < flat.Length() ? Deceleration : Acceleration) * dt;
        var step = delta.Length() <= rate ? delta : delta.Normalized() * rate;
        var next = flat + step;
        if (next.Length() > MaxSpeed)
            next = next.Normalized() * MaxSpeed;

        Velocity = new Vector3(next.X, Velocity.Y, next.Z);
        Position += Velocity * dt;

        // 3. Ease facing toward the movement direction. Standing agents hold their heading, so a
        //    resident that stops does not spin to face the camera.
        if (Velocity.Length() > StopSpeed)
        {
            var want = Mathf.Atan2(Velocity.X, Velocity.Z);
            var maxTurn = TurnRate * dt;
            var diff = Mathf.Wrap(want - Yaw, -Mathf.Pi, Mathf.Pi);
            Yaw += Mathf.Clamp(diff, -maxTurn, maxTurn);
        }
    }

    /// <summary>
    /// How squarely a heading must press into an obstacle before <see cref="AroundObstacle"/> turns
    /// it: the cosine of the angle from straight in, so 0.85 is within about 32°. Shallower than
    /// that, the physics slide along the obstacle is already quick enough to carry the agent round.
    /// </summary>
    public const float HeadOnThreshold = 0.85f;

    /// <summary>
    /// Turn a heading that runs into an obstacle along it instead. <c>MoveAndSlide</c> slides along
    /// anything met at an angle, but met head-on (a tree trunk or a wall dead ahead) the slide has
    /// no sideways part, and every controller here steers in straight lines, so the agent pushed in
    /// place for good. Pressing in nearly head-on, the heading keeps its effort and points along
    /// the obstacle, on the side it already leans toward. <paramref name="side"/> carries that
    /// choice between ticks so the agent commits to one way round, and resets once nothing is in
    /// the way. <paramref name="wallNormal"/> is the obstacle's normal toward the agent, or zero.
    /// </summary>
    public static AgentAction AroundObstacle(in AgentAction action, Vector3 wallNormal, ref int side)
    {
        var heading = new Vector3(action.MoveDirection.X, 0f, action.MoveDirection.Z);
        var normal = new Vector3(wallNormal.X, 0f, wallNormal.Z);
        float effort = heading.Length();
        if (normal.LengthSquared() < 1e-6f || effort < 1e-4f)
        {
            side = 0;
            return action;
        }

        normal = normal.Normalized();
        var direction = heading / effort;
        float into = -direction.Dot(normal);
        if (into < HeadOnThreshold)
            return action;

        // Perpendicular to the normal on the ground plane; side picks which way along it. Dead-on
        // the heading leans neither way, and the first perpendicular is taken.
        var perpendicular = new Vector3(-normal.Z, 0f, normal.X);
        if (side == 0)
            side = (direction + normal * into).Dot(perpendicular) >= 0f ? 1 : -1;
        return new AgentAction(perpendicular * (side * effort), action.Interaction, action.TargetId);
    }

    /// <summary>Place the agent without going through the accel ramp (scene load, teleport, replay seek).</summary>
    public void Teleport(Vector3 position)
    {
        Position = position;
        Velocity = Vector3.Zero;
    }

    /// <summary>
    /// Sync the XZ velocity back from the physics body so the accel/decel ramps start from the
    /// actual post-collision speed each tick. Called by <c>AgentBrain._PhysicsProcess</c> before
    /// <see cref="Step"/> in the live physics path.
    ///
    /// In the harness/test path (no CharacterBody3D) this is never called and the controller
    /// integrates its own <see cref="Position"/> — both modes are valid and intentional.
    /// </summary>
    public void SyncFromPhysics(Vector3 physicsVelocity)
    {
        // Only the XZ plane is locomotion-owned. Y (gravity) belongs to the physics body.
        Velocity = new Vector3(physicsVelocity.X, Velocity.Y, physicsVelocity.Z);
    }
}
