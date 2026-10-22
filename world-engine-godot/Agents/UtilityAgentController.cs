using System;
using System.Collections.Generic;
using Godot;

namespace NltWorldEngine.Agents;

/// <summary>
/// The control condition: a deterministic, model-free controller.
///
/// This is not a placeholder. Without it there is no way to tell "the LLM is playing" from "the
/// character is drifting on its own", because a wander loop would look identical on screen. Running
/// this side by side with <see cref="LlmAgentController"/> is what makes the comparison honest —
/// it is the same seam, the same locomotion, the same needs, with the cognition swapped out.
///
/// It also serves as the fallback when no model is attached, so the scene still moves.
/// </summary>
public sealed class UtilityAgentController : IAgentController
{
    private readonly SimulationRng _rng;
    private float _wanderTimer;
    private AgentAction _held = AgentAction.Idle;

    /// <summary>Places this agent tours between, or empty for need-driven movement only.</summary>
    public IReadOnlyList<TaskAnchor> Anchors { get; set; } = System.Array.Empty<TaskAnchor>();

    /// <summary>Anchor the agent is currently walking toward, or null when wandering.</summary>
    private TaskAnchor? _target;

    /// <summary>The anchor last reached, passed over by the next choice while another is free.</summary>
    private TaskAnchor? _lastReached;

    /// <summary>Distance at which an anchor counts as reached and the agent picks another.</summary>
    private const float ArrivalRadius = 2.5f;

    /// <summary>Needs as <c>FeedVocabulary.Needs</c>: quiet, rest, social, stimulation.</summary>
    public float[] Thresholds { get; } = { 0.3f, 0.3f, 0.6f, 0.5f };

    public UtilityAgentController(uint seed, string agentId = "avatar_0")
    {
        _rng = new SimulationRng(seed);
    }

    public void Attach(string agentId) { }

    /// <summary>
    /// Replaced before arriving (a Fusion intent, a halt): release the anchor this tour reserved,
    /// or the claim outlives the controller and the anchor reads as full to everyone, this agent's
    /// own later tours included.
    /// </summary>
    public void Detach(string agentId)
    {
        _target?.Release(agentId);
        _target = null;
    }

    public AgentAction Act(AgentObservation observation)
    {
        // When the world offers real destinations, seek the nearest reachable one instead of
        // heading off on a fixed bearing. Fixed bearings look like purposeful motion but converge
        // on the map edge and stay there, which is indistinguishable from a stuck agent.
        if (Anchors.Count > 0)
            return Tour(observation);

        // Re-decide on a slow cadence so the agent commits to a heading instead of jittering. The
        // underlying locomotion then smooths whatever it picks, which is the division of labour:
        // this decides intent, LocomotionController decides motion.
        if (observation.Tick % 60 == 0)
            _wanderTimer = 0f;

        if (_wanderTimer <= 0f)
        {
            _wanderTimer = 1f;
            _held = Choose(observation);
        }
        else
        {
            _wanderTimer -= (float)WorldConstants.Tick;
        }

        return _held;
    }

    /// <summary>
    /// Walk to the nearest anchor this agent is allowed to claim, then choose another on arrival.
    /// This is the behaviour that makes an avatar traverse the world between Fusion decisions,
    /// rather than standing where the last intent left it.
    /// </summary>
    private AgentAction Tour(in AgentObservation observation)
    {
        if (_target != null)
        {
            var toTarget = _target.Position - observation.Position;
            toTarget.Y = 0f;
            if (toTarget.Length() > ArrivalRadius)
                return AgentAction.Move(toTarget.Normalized(), 1f);

            // Reached. Release the claim so a later cycle is free to revisit it, and re-decide.
            _target.Release(observation.AgentId);
            _lastReached = _target;
            _target = null;
        }

        _target = NearestUnclaimed(observation);
        if (_target == null)
            return Wander();

        _target.Reserve(observation.AgentId);
        var direction = _target.Position - observation.Position;
        direction.Y = 0f;
        return direction.LengthSquared() > 0.0001f
            ? AgentAction.Move(direction.Normalized(), 1f)
            : Wander();
    }

    /// <summary>
    /// Closest anchor with room for this agent, excluding the one already held. The one just
    /// reached is chosen only when nothing else is free: released on arrival, it is also the
    /// nearest, and re-picking it parked the agent there for good.
    /// </summary>
    private TaskAnchor? NearestUnclaimed(in AgentObservation observation)
        => Nearest(observation, _lastReached) ?? Nearest(observation, null);

    private TaskAnchor? Nearest(in AgentObservation observation, TaskAnchor? skip)
    {
        TaskAnchor? best = null;
        var bestDistance = float.MaxValue;
        foreach (var anchor in Anchors)
        {
            if (anchor == skip || anchor.IsOccupiedBy(observation.AgentId))
                continue;
            if (anchor.IsFull)
                continue;

            var delta = anchor.Position - observation.Position;
            delta.Y = 0f;
            var distance = delta.Length();
            if (distance >= bestDistance)
                continue;

            bestDistance = distance;
            best = anchor;
        }
        return best;
    }

    public void OnActionRejected(in AgentObservation observation, in AgentAction action, string reason)
    {
        // A deterministic controller never emits an invalid action, so reaching here means a bug in
        // this class rather than bad model output. Recorded rather than thrown so a headless run
        // still reports it.
        Console.Error.WriteLine($"[utility] rejected own action: {reason}");
    }

    /// <summary>
    /// Pick an action from the dominant unmet need. Thresholds mirror <c>TaskAnchor.cs</c> /
    /// RENDERER-PLAN.md C.3 so the two agree on what "unmet" means.
    /// </summary>
    private AgentAction Choose(in AgentObservation observation)
    {
        var n = observation.Needs;
        if (n == null || n.Length < 4)
            return Wander();

        // Highest level wins; the 0.05 band keeps near-ties from flip-flopping between two needs.
        var best = 0;
        for (var i = 1; i < 4; i++)
            if (n[i] > n[best] + 0.05f)
                best = i;

        // Nothing is pressing — wander rather than freeze.
        if (n[best] < Thresholds[best])
            return Wander();

        // Each need maps to a stable world heading. Fixed bearings rather than random ones, so an
        // unmet need reliably reads as "walked that way" to someone watching.
        switch (best)
        {
            case 0: // quiet — away from the settlement
                return AgentAction.Move(new Vector3(0f, 0f, -1f));
            case 1: // rest — hold still
                return new AgentAction(Vector3.Zero, AgentInteraction.Rest);
            case 2: // social — toward the middle of the world
                return AgentAction.Move(new Vector3(1f, 0f, 0f));
            default: // stimulation
                return AgentAction.Move(new Vector3(-1f, 0f, 1f));
        }
    }

    private AgentAction Wander()
    {
        var a = _rng.Range(0f, Mathf.Tau);
        return AgentAction.Move(new Vector3(Mathf.Cos(a), 0f, Mathf.Sin(a)), 0.5f);
    }
}