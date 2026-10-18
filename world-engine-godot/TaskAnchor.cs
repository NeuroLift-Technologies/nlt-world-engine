using Godot;
using System;
using System.Collections.Generic;
using System.Linq;

namespace NltWorldEngine;

// ---------------------------------------------------------------------------
// TaskAnchor — Phase C.3
//
// Port of the location model in
//   WorldEngine/Source/WorldEngine/Public/World/NLTSmartObjectWorldSubsystem.h
//   WorldEngine/Source/WorldEngine/Private/World/NLTSmartObjectWorldSubsystem.cpp
//
// WHY THIS IS RENDERER-SIDE
//   Per docs/contracts/state-feed-v1.md §4.3, the world engine and Fusion are
//   responsible for different things and the earlier design conflated them:
//
//     Agent needs           quiet, rest, social, stimulation   — Fusion, in the feed
//     Location affordances  noiseLevel, socialDensity, privacy  — the renderer
//
//   Godot owns the locations, so their affordance axes are renderer-side and are
//   deliberately NOT in nlt.state-feed.v1. This class is the renderer half.
//
// WHAT IS DELIBERATELY NOT PORTED
//   NLTSmartObjectWorldSubsystem.cpp:129-130 and :152-153 keep match/score
//   branches for ENLTAgentNeed::Privacy that can never fire — no agent ever holds
//   a Privacy need. UE declares seven ENLTAgentNeed values but
//   FNLTScenarioNeedsFragment carries state for only four; Food, Movement and
//   Privacy are enum-only, declared and never held.
//
//   Those branches are NOT reproduced here. Copying them forward would import a
//   known dead path and invite re-deriving a five-need model. Privacy survives
//   here as a *location axis* (Rest and Stim both read it), which is the role the
//   contract says it actually has.
//
//   If Fusion's schema later defines a privacy need, that is a state-feed
//   schema-version bump — see contract §4.3 — and AgentNeed gains a member here.
// ---------------------------------------------------------------------------

/// <summary>
/// The four agent needs. Fusion owns these; the renderer consumes them and
/// resolves each against the affordance axes of the anchors in the scene.
/// </summary>
public enum AgentNeed
{
    Quiet,
    Rest,
    Social,
    Stimulation,
}

/// <summary>
/// What a place offers. Renderer-owned — see the contract note above.
/// </summary>
public sealed class AffordanceAxes
{
    /// <summary>0 = silent, 1 = loud.</summary>
    public float NoiseLevel { get; init; }

    /// <summary>0 = empty, 1 = crowded.</summary>
    public float SocialDensity { get; init; }

    /// <summary>0 = exposed, 1 = screened from others.</summary>
    public float Privacy { get; init; }

    public static readonly AffordanceAxes Neutral = new() { NoiseLevel = 0.5f, SocialDensity = 0.5f, Privacy = 0.5f };

    /// <summary>Throws if any axis is outside [0,1]. Called on construction.</summary>
    public void Validate()
    {
        Require01(NoiseLevel, nameof(NoiseLevel));
        Require01(SocialDensity, nameof(SocialDensity));
        Require01(Privacy, nameof(Privacy));
    }

    private static void Require01(float v, string name)
    {
        if (v < 0f || v > 1f)
            throw new ArgumentOutOfRangeException(
                name, v, $"TaskAnchor: affordance axis '{name}' must be in [0,1]");
    }
}

/// <summary>
/// A place an agent can go to do something. The renderer-side counterpart to
/// UE's FNLTWorldLocation.
/// </summary>
public sealed class TaskAnchor
{
    /// <summary>Stable id, unique within the scene.</summary>
    public string Id { get; }

    /// <summary>Plain-language label. Surfaced verbatim in observer UI.</summary>
    public string DisplayName { get; }

    /// <summary>What this place affords — see <see cref="AgentNeed"/>.</summary>
    public AffordanceAxes Axes { get; }

    /// <summary>Where an agent stands to use it.</summary>
    public Vector3 Position { get; init; }

    /// <summary>
    /// Activities this anchor supports. An agent need is satisfied by an anchor
    /// when the axes match — activities are a separate, activity-driven filter
    /// (UE's FindLocationsByActivity), not a need match.
    /// </summary>
    public IReadOnlyList<string> AvailableActivities { get; init; } = Array.Empty<string>();

    /// <summary>How many agents can use this anchor at once.</summary>
    public int MaxOccupants { get; init; } = 1;

    /// <summary>
    /// Set when this anchor is a doorway: a building's door in the open world, or a room's exit.
    /// Doorways afford <c>use</c> by this flag rather than by their axes, and are never occupied
    /// (see <see cref="AnchorAffordances"/>). Null for every other anchor.
    /// </summary>
    public PortalLink? Link { get; init; }

    /// <summary>True when this anchor is a doorway (<see cref="Link"/> is set).</summary>
    public bool IsPortal => Link != null;

    /// <summary>
    /// Verbs this anchor affords beyond approach and look_at, stated outright (AGENT-LOOP-002 T5):
    /// a chair affords <c>sit</c> because it is a chair, not because of its axes. Null means derive
    /// them from <see cref="Axes"/>, as open-world places do.
    /// </summary>
    public IReadOnlyList<string>? Affords { get; init; }

    /// <summary>Perception entity kind: <c>place</c> (the default) or <c>object</c> for furniture.</summary>
    public string Kind { get; init; } = "place";

    /// <summary>
    /// Where an agent using this anchor should face — the object's own centre, for furniture whose
    /// <see cref="Position"/> is the approach point beside it. Null for places.
    /// </summary>
    public Vector3? FacePoint { get; init; }

    private readonly List<string> _occupants = new();

    public IReadOnlyList<string> CurrentOccupants => _occupants;

    public bool IsFull => _occupants.Count >= MaxOccupants;

    public TaskAnchor(string id, string displayName, AffordanceAxes axes)
    {
        if (string.IsNullOrWhiteSpace(id))
            throw new ArgumentException("TaskAnchor: id must be non-empty", nameof(id));
        if (string.IsNullOrWhiteSpace(displayName))
            throw new ArgumentException("TaskAnchor: DisplayName must be non-empty", nameof(displayName));

        axes.Validate();
        Id = id;
        DisplayName = displayName;
        Axes = axes;
    }

    public bool IsOccupiedBy(string agentId) => _occupants.Contains(agentId);

    /// <summary>
    /// Claim the anchor. Returns false if it is already full or the agent
    /// already holds it — reserving twice is a no-op, not an error, because the
    /// reservation is re-asserted every tick by the caller's intent.
    /// </summary>
    public bool Reserve(string agentId)
    {
        if (IsOccupiedBy(agentId)) return true;
        if (IsFull) return false;
        _occupants.Add(agentId);
        return true;
    }

    public void Release(string agentId) => _occupants.Remove(agentId);

    public override string ToString()
        => $"{Id} ({DisplayName}) noise={Axes.NoiseLevel:0.00} social={Axes.SocialDensity:0.00} privacy={Axes.Privacy:0.00}";
}

/// <summary>
/// Where a doorway anchor leads (AGENT-LOOP-002 T2). <paramref name="TargetSceneId"/> is the scene
/// on the other side: the building's interior for a door, <see cref="SceneCatalog.OpenWorldId"/> for
/// a room's exit. <paramref name="BuildingIndex"/> is the settlement building the doorway belongs to,
/// which is also its index into the world portal list — the building entered through a door, or the
/// one an exit returns to.
/// </summary>
public sealed record PortalLink(string TargetSceneId, int BuildingIndex);

/// <summary>
/// What an anchor affords and whether it is free, for perception and for the execution re-check
/// alike, so the two cannot disagree. Ordinary anchors derive <c>sit</c> and <c>use</c> from their
/// axes (quiet/screened places afford sit; busy ones afford use). Doorways afford <c>use</c> by flag
/// — a home door is private and quiet, so the axes would offer <c>sit</c> and never <c>use</c> — and
/// are never occupied: anyone may walk through a door someone else is heading for.
/// </summary>
public static class AnchorAffordances
{
    private static readonly string[] PortalAffordances = { "use", "approach", "look_at" };

    /// <summary>The verbs perception lists for <paramref name="anchor"/>, in a stable order.</summary>
    public static IReadOnlyList<string> For(TaskAnchor anchor)
    {
        if (anchor.IsPortal)
            return PortalAffordances;
        var list = new List<string>();
        if (anchor.Affords != null)
        {
            list.AddRange(anchor.Affords);
            list.Add("approach");
            list.Add("look_at");
            return list;
        }
        if (anchor.Axes.Privacy > 0.5f)
            list.Add("sit");
        if (anchor.Axes.SocialDensity > 0.5f || anchor.Axes.NoiseLevel > 0.5f)
            list.Add("use");
        list.Add("approach");
        list.Add("look_at");
        return list;
    }

    /// <summary>True when <paramref name="anchor"/> is held by someone other than <paramref name="agentId"/>.</summary>
    public static bool IsOccupiedFor(TaskAnchor anchor, string agentId)
        => !anchor.IsPortal && anchor.IsFull && !anchor.IsOccupiedBy(agentId);

    /// <summary>
    /// Execution-time check for <c>use</c> and <c>sit</c>: the target must be an anchor in the
    /// agent's scene, afford the verb, and be free. Returns null when execution may proceed, else the
    /// rejection reason. Other verbs only need the target to exist, which the caller checks.
    /// </summary>
    public static string? Recheck(IReadOnlyList<TaskAnchor> sceneAnchors, string targetId, string verb, string agentId)
    {
        if (verb is not ("use" or "sit"))
            return null;
        TaskAnchor? anchor = null;
        foreach (var a in sceneAnchors)
        {
            if (a.Id == targetId)
            {
                anchor = a;
                break;
            }
        }
        if (anchor == null)
            return $"target '{targetId}' offers no '{verb}' affordance here";
        if (!For(anchor).Contains(verb))
            return $"target '{targetId}' does not afford '{verb}'";
        if (IsOccupiedFor(anchor, agentId))
            return $"target '{targetId}' is occupied";
        return null;
    }
}

/// <summary>
/// Need → anchor resolution. Ports MatchesNeed/ScoreLocation from
/// NLTSmartObjectWorldSubsystem.cpp:119-162, minus the dead Privacy branches
/// (see the header note in this file).
///
/// Thresholds and formulas are kept byte-identical to UE so behaviour matches
/// the reference implementation; only the unreachable branch is dropped.
/// </summary>
public static class NeedMatching
{
    /// <summary>
    /// Does this place satisfy the need at all? A hard gate, not a weight — UE
    /// treats a non-match as ineligible regardless of score.
    /// </summary>
    public static bool Matches(in AffordanceAxes axes, AgentNeed need) => need switch
    {
        AgentNeed.Quiet => axes.NoiseLevel < 0.3f,
        AgentNeed.Social => axes.SocialDensity > 0.6f,
        AgentNeed.Rest => axes.Privacy > 0.5f,
        AgentNeed.Stimulation => axes.SocialDensity > 0.5f || axes.NoiseLevel > 0.5f,
        _ => false,
    };

    /// <summary>
    /// How well this place serves the need. Only meaningful when
    /// <see cref="Matches"/> is true. Higher wins.
    /// </summary>
    public static float Score(in AffordanceAxes axes, AgentNeed need) => need switch
    {
        AgentNeed.Quiet => 1f - axes.NoiseLevel,
        AgentNeed.Social => axes.SocialDensity,
        AgentNeed.Rest => axes.Privacy,

        // SocialDensity + NoiseLevel*0.5 can exceed 1.0 — deliberately unclamped,
        // matching UE. Scores are only ever compared to each other.
        AgentNeed.Stimulation => axes.SocialDensity + axes.NoiseLevel * 0.5f,

        _ => 0f,
    };

    /// <summary>
    /// The best eligible anchor for a need, or null.
    ///
    /// Occupancy handling follows UE's FindBestLocationForAgent: an anchor that
    /// is *currently* occupied by someone else is skipped outright rather than
    /// scored down. An agent that already holds its target keeps it — otherwise
    /// an agent whose target fills up mid-approach would thrash every tick.
    /// </summary>
    public static TaskAnchor? FindBest(
        IReadOnlyList<TaskAnchor> anchors, AgentNeed need, string? agentId = null)
    {
        TaskAnchor? best = null;
        var bestScore = float.NegativeInfinity;

        foreach (var anchor in anchors)
        {
            if (!Matches(anchor.Axes, need)) continue;

            // Already ours — keep it, do not re-evaluate against rivals.
            if (agentId is not null && anchor.IsOccupiedBy(agentId))
                return anchor;

            if (anchor.IsFull) continue;

            var score = Score(anchor.Axes, need);
            if (score <= bestScore) continue;

            bestScore = score;
            best = anchor;
        }

        return best;
    }
}