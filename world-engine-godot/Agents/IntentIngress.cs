using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Godot;

namespace NltWorldEngine.Agents;

/// <summary>
/// The engine's scene transition, as ingress sees it (AGENT-LOOP-002 T3). <c>use</c> on a doorway
/// anchor is checked with <see cref="CanTransit"/> before the avatar walks, and
/// <see cref="Transit"/> runs when it arrives. Implemented by the composition root, which owns the
/// view and the scenes.
/// </summary>
public interface IPortalTransit
{
    /// <summary>Why the avatar cannot go through this doorway now, or null when it can.</summary>
    string? CanTransit(AvatarCharacter avatar, PortalLink link);

    /// <summary>Move the avatar through the doorway: show the scene, then place it there.</summary>
    void Transit(AvatarCharacter avatar, PortalLink link);
}

/// <summary>
/// Engine-side intent ingress: the path from a Fusion <see cref="SemanticIntent"/>
/// to <see cref="AvatarCharacter.ApplyIntent"/>, in contract order:
/// protocol validation → ASFDK governance (explains denials) → execution re-check → apply.
/// The model moves around and interacts with the environment. It never writes the
/// physical layer: no coordinates, no velocity, no teleport, no object-state mutation.
/// Every physical effect is resolved and owned here.
/// </summary>
public sealed class IntentIngress
{
    private readonly IGovernanceGate _gate;
    private readonly Func<string, Vector3?> _resolveTarget;
    private readonly Func<string, IReadOnlyList<TaskAnchor>> _anchorsFor;
    private readonly Func<Func<IntentExecutionResult>, Task<IntentExecutionResult>> _runOnMainThread;
    private readonly IPortalTransit? _transit;

    /// <param name="gate">ASFDK-backed governance. Never null — pass
    /// <see cref="OpenGovernanceGate.Instance"/> only where the gate is unavailable.</param>
    /// <param name="resolveTarget">Engine scene lookup: target id → world position now.</param>
    /// <param name="anchorsFor">Task anchors in the agent's scene for affordance checks.</param>
    /// <param name="runOnMainThread">Run scene-tree reads and avatar mutations on Godot's main thread.</param>
    /// <param name="transit">The engine's scene transition. Without one, <c>use</c> on a doorway is
    /// rejected (fail closed) rather than walked to with nothing happening on arrival.</param>
    public IntentIngress(
        IGovernanceGate gate,
        Func<string, Vector3?>? resolveTarget = null,
        Func<string, IReadOnlyList<TaskAnchor>>? anchorsFor = null,
        Func<Func<IntentExecutionResult>, Task<IntentExecutionResult>>? runOnMainThread = null,
        IPortalTransit? transit = null)
    {
        _transit = transit;
        _gate = gate;
        _resolveTarget = resolveTarget ?? (_ => null);
        _anchorsFor = anchorsFor ?? (_ => Array.Empty<TaskAnchor>());
        _runOnMainThread = runOnMainThread
            ?? throw new ArgumentNullException(nameof(runOnMainThread),
                "Intent ingress requires a main-thread dispatcher for scene access.");
    }

    /// <summary>
    /// Submit one intent for one avatar. Runs the full ingress path and returns the
    /// result envelope. The engine is the "user" here: governance evaluates under the
    /// engine's TOI, physical checks run against the engine's live world, and the model
    /// only ever moves around and interacts — never writes physics.
    /// </summary>
    public async Task<IntentExecutionResult> SubmitAsync(
        AvatarCharacter avatar,
        AgentPerceptionSnapshot perception,
        SemanticIntent intent,
        int currentTick)
    {
        var reject = (string reason) => new IntentExecutionResult
        {
            MessageId = $"result-{intent.MessageId}",
            IntentMessageId = intent.MessageId,
            AgentId = intent.AgentId,
            Tick = currentTick,
            Status = "rejected",
            Reason = reason,
        };

        // 1. Protocol validation: correlation, verb allowlist, target-in-perception.
        var problem = AgentLoopProtocol.ValidateIntent(perception, intent);
        if (problem != null)
            return reject($"protocol: {problem}");

        // 2. Governance (ASFDK): explains denials with interventions, never bare-rejects.
        GovernanceDecision decision;
        try
        {
            decision = await _gate.EvaluateAsync(intent);
        }
        catch (Exception e)
        {
            decision = new GovernanceDecision
            {
                Allowed = false,
                Code = "gate-unavailable",
                Explanation = $"Governance gate errored ({e.GetType().Name}); intent rejected. " +
                    "No physical action was applied.",
            };
        }

        return await _runOnMainThread(() =>
            ApplyDecisionOnMainThread(avatar, perception, intent, currentTick, decision, reject));
    }

    private IntentExecutionResult ApplyDecisionOnMainThread(
        AvatarCharacter avatar,
        AgentPerceptionSnapshot perception,
        SemanticIntent intent,
        int currentTick,
        GovernanceDecision decision,
        Func<string, IntentExecutionResult> reject)
    {
        if (!GodotObject.IsInstanceValid(avatar))
            return reject("avatar is no longer in the scene");
        if (avatar.InTransition)
            return reject("avatar is moving between scenes; try again once the next perception arrives");

        if (!decision.Allowed)
        {
            avatar.Attach(new IdleController());
            var reason = string.IsNullOrEmpty(decision.Explanation)
                ? $"governance denied ({decision.Code})"
                : $"governance denied ({decision.Code}): {decision.Explanation}";
            if (decision.RecommendedInterventions.Count > 0)
                reason += " Try instead: " + string.Join("; ", decision.RecommendedInterventions);
            return reject(reason);
        }

        // 3. Execution re-check against live world: visibility at decision time does not
        //    guarantee reachability now. Resolve the target fresh from the scene.
        Vector3? resolved = null;
        if (intent.TargetId != null)
        {
            resolved = _resolveTarget(intent.TargetId);
            if (resolved == null)
                return reject($"stale target '{intent.TargetId}': no longer in the scene");
            var recheck = RecheckTarget(avatar, intent, resolved.Value);
            if (recheck != null)
                return reject(recheck);
        }

        // 3b. A doorway: the engine must be able to take the avatar through before it walks there.
        //     Scene transitions are a new class of physical effect, so each one is logged here.
        Action? onArrival = null;
        if (intent.Verb == "use" && PortalTarget(avatar, intent.TargetId) is { } link)
        {
            var transitProblem = _transit == null
                ? "scene transitions are not available"
                : _transit.CanTransit(avatar, link);
            if (transitProblem != null)
                return reject($"cannot go through '{intent.TargetId}': {transitProblem}");
            var transit = _transit!;
            onArrival = () => transit.Transit(avatar, link);
            GD.Print($"[IntentIngress] scene transition accepted: {avatar.AgentId} use {intent.TargetId} " +
                $"({avatar.SceneId} -> {link.TargetSceneId})");
        }

        // 4. Apply: verb → locomotion only. Speed/accel/collision stay engine-owned; a doorway's
        //    transition runs on arrival.
        avatar.ApplyIntent(intent.Verb, resolved, onArrival);

        var accepted = new IntentExecutionResult
        {
            MessageId = $"result-{intent.MessageId}",
            IntentMessageId = intent.MessageId,
            AgentId = intent.AgentId,
            Tick = currentTick,
            Status = "accepted",
        };
        if (!string.IsNullOrEmpty(decision.Explanation) && decision.Code != "clean")
            accepted = new IntentExecutionResult
            {
                MessageId = accepted.MessageId,
                IntentMessageId = accepted.IntentMessageId,
                AgentId = accepted.AgentId,
                Tick = accepted.Tick,
                Status = accepted.Status,
                Reason = $"governance note: {decision.Explanation}",
            };
        return accepted;
    }

    /// <summary>The doorway link of <paramref name="targetId"/> in the avatar's scene, or null.</summary>
    private PortalLink? PortalTarget(AvatarCharacter avatar, string? targetId)
    {
        foreach (var anchor in _anchorsFor(avatar.SceneId))
            if (anchor.Id == targetId)
                return anchor.Link;
        return null;
    }

    /// <summary>
    /// Execution-time re-check: range, affordance, occupancy. The perception snapshot
    /// said the target was visible; the live world decides if it is still usable.
    /// Returns null when execution may proceed, else the rejection reason.
    /// </summary>
    private string? RecheckTarget(AvatarCharacter avatar, SemanticIntent intent, Vector3 targetPos)
    {
        var toTarget = targetPos - avatar.GlobalPosition;
        toTarget.Y = 0f;
        var dist = toTarget.Length();

        const float ReachRadius = 30f;
        if (dist > ReachRadius)
            return $"target '{intent.TargetId}' out of reach ({dist:F1} m > {ReachRadius} m)";

        // use / sit need a live affordance + a free anchor in the agent's scene; approach /
        // look_at / communicate only need the target to still exist (checked by resolve). The
        // rules are AnchorAffordances', the same ones perception lists, so the two agree.
        return AnchorAffordances.Recheck(_anchorsFor(avatar.SceneId), intent.TargetId!, intent.Verb, avatar.AgentId);
    }
}
