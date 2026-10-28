using System.Collections.Generic;
using Godot;

namespace NltWorldEngine.Agents;

/// <summary>
/// Builds engine-owned perception snapshots from live Jolt state. The engine is the
/// "user": positions come from physics bodies, visibility is filtered per-agent here,
/// and affordances come from the TaskAnchor registry — never from the model or Fusion.
/// </summary>
public static class PerceptionBuilder
{
    /// <param name="rosterAgentId">The id Fusion registered for this avatar, sent as the
    /// perception's <c>agentId</c> (AGENT-LOOP-003 F0). Null or blank sends the avatar's internal
    /// key. Occupancy and everything engine-side keep using the internal key.</param>
    public static AgentPerceptionSnapshot Build(
        AvatarCharacter avatar,
        int tick,
        string messageId,
        IReadOnlyList<TaskAnchor> anchors,
        IReadOnlyList<AvatarCharacter> others,
        string? rosterAgentId = null)
    {
        var pos = avatar.GlobalPosition;
        var vel = avatar.Velocity;
        var entities = VisiblePlaces(avatar.AgentId, pos, anchors);

        foreach (var other in others)
        {
            if (other == avatar)
                continue;
            var toOther = other.GlobalPosition - pos;
            toOther.Y = 0f;
            if (toOther.Length() > PerceptionRange)
                continue;
            entities.Add(new VisibleEntity
            {
                Id = other.AgentId,
                Kind = "agent",
                Position = new PhysicalVector3
                {
                    X = other.GlobalPosition.X,
                    Y = other.GlobalPosition.Y,
                    Z = other.GlobalPosition.Z,
                },
                Affordances = new List<string> { "communicate", "look_at", "approach" },
                Occupied = false,
            });
        }

        return new AgentPerceptionSnapshot
        {
            MessageId = messageId,
            AgentId = WireAgentId(avatar.AgentId, rosterAgentId),
            Tick = tick,
            // Throws for an unknown scene id; AgentLoopDriver checks first and posts nothing.
            Scene = new AgentLoopScene { Id = avatar.SceneId, Kind = SceneCatalog.KindFor(avatar.SceneId) },
            Self = new AgentPhysicalState
            {
                Position = new PhysicalVector3 { X = pos.X, Y = pos.Y, Z = pos.Z },
                Velocity = new PhysicalVector3 { X = vel.X, Y = vel.Y, Z = vel.Z },
            },
            VisibleEntities = entities,
        };
    }

    public const float PerceptionRange = 25f;

    /// <summary>
    /// The <c>agentId</c> a perception carries: the configured roster id when there is one, else the
    /// avatar's internal key. Fusion serves only roster ids it registered, so an unset roster id
    /// makes Fusion refuse every decision for this avatar (fail closed).
    /// </summary>
    public static string WireAgentId(string internalId, string? rosterAgentId)
        => string.IsNullOrWhiteSpace(rosterAgentId) ? internalId : rosterAgentId.Trim();

    /// <summary>
    /// The anchors an agent at <paramref name="position"/> can see: those within
    /// <see cref="PerceptionRange"/> on the ground plane, with affordances and occupancy from
    /// <see cref="AnchorAffordances"/>. Engine-free, so the harness checks it directly.
    /// </summary>
    public static List<VisibleEntity> VisiblePlaces(string agentId, Vector3 position, IReadOnlyList<TaskAnchor> anchors)
    {
        var entities = new List<VisibleEntity>();
        foreach (var anchor in anchors)
        {
            var toAnchor = anchor.Position - position;
            toAnchor.Y = 0f;
            if (toAnchor.Length() > PerceptionRange)
                continue;
            entities.Add(new VisibleEntity
            {
                Id = anchor.Id,
                Kind = anchor.Kind,
                Position = new PhysicalVector3
                {
                    X = anchor.Position.X,
                    Y = anchor.Position.Y,
                    Z = anchor.Position.Z,
                },
                Affordances = AnchorAffordances.For(anchor),
                Occupied = AnchorAffordances.IsOccupiedFor(anchor, agentId),
            });
        }
        return entities;
    }
}
