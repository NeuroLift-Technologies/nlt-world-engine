using Godot;

namespace NltWorldEngine;

/// <summary>
/// Open-world Jolt collision (PHYS-001).
///
/// Why this exists: the avatar is a Jolt <c>CharacterBody3D</c> that moves with
/// <c>MoveAndSlide()</c>, but the world it walks on had no physics bodies at all — the terrain,
/// buildings and water were visual meshes only, and the single <c>AvatarGround</c> plane in
/// <c>Main</c> is a flat sheet at y=0 while the town sits at y≈7.2. Without bodies here the avatar
/// falls to the wrong level, walks through walls, and can leave the 460 m world entirely.
///
/// What lives here: a trimesh terrain body exact-matched to the visual mesh, four edge walls so
/// agents cannot leave the island, and the kill-plane constant the avatar resets below. Building
/// bodies live in <c>SettlementBuilder.Build</c> (one box per building, sized by
/// <c>BuildingArchetypes.CollisionInfo</c>) so each box inherits its building's transform.
/// Interiors are out of scope: FBX levels still stand on the flat <c>AvatarGround</c> safety plane
/// until their own collision pass lands.
/// </summary>
public static class TerrainBuilderPhysics
{
    /// <summary>
    /// Fell through the world (missed every body). Below the lowest terrain (≈−15 m in the ocean
    /// trench) with margin, and below the bounds walls (which reach −20 m), so reaching it means
    /// physics genuinely has nothing to stand on rather than a steep slope.
    /// </summary>
    public const float KillY = -25f;

    /// <summary>
    /// Static terrain body exact-matched to the visual mesh. The shape is cut from the same
    /// <c>ArrayMesh</c> the renderer draws, so feet and eyes never disagree about where the ground
    /// is — a separately sampled heightfield would drift wherever its resolution differs.
    /// </summary>
    public static StaticBody3D TerrainBody(MeshInstance3D visual)
    {
        var body = new StaticBody3D { Name = "TerrainCollision" };
        body.AddChild(new CollisionShape3D { Shape = visual.Mesh.CreateTrimeshShape() });
        return body;
    }

    /// <summary>
    /// Four invisible walls around the 460 m world. They span −20 m to +40 m: high enough to stop
    /// an avatar on the tallest ridge (≈29 m), low enough that the kill-plane below them still
    /// catches anything that tunnels under the terrain instead of trapping it inside a wall.
    /// </summary>
    public static Node3D WorldBounds()
    {
        var root = new Node3D { Name = "WorldBounds" };
        float half = WorldConstants.World * 0.5f + 5f;
        float wallH = 60f, thick = 10f, len = WorldConstants.World + 40f;
        const float centreY = 10f;
        AddWall(root, new Vector3(len, wallH, thick), new Vector3(0f, centreY, -half));
        AddWall(root, new Vector3(len, wallH, thick), new Vector3(0f, centreY, half));
        AddWall(root, new Vector3(thick, wallH, len), new Vector3(-half, centreY, 0f));
        AddWall(root, new Vector3(thick, wallH, len), new Vector3(half, centreY, 0f));
        return root;
    }

    private static void AddWall(Node3D root, Vector3 size, Vector3 position)
    {
        var wall = new StaticBody3D { Name = "WorldEdge", Position = position };
        wall.AddChild(new CollisionShape3D { Shape = new BoxShape3D { Size = size } });
        root.AddChild(wall);
    }
}
