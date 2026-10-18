using System.Collections.Generic;
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
/// agents cannot leave the island, a shoreline wall so they cannot walk into the lake or the sea,
/// and the kill-plane constant the avatar resets below. Building
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

    /// <summary>
    /// Terrain at or below this height counts as water for the shoreline barrier. A little above the
    /// water plane so the wall stands on the wet sand rather than letting feet into the shallows.
    /// </summary>
    public const float ShoreMargin = 0.3f;

    /// <summary>Grid spacing (m) the shoreline is traced at. 2 m keeps the stair-stepping well under
    /// an avatar's stride while the whole island stays a few thousand triangles.</summary>
    private const float ShoreStep = 2f;

    /// <summary>
    /// Invisible wall along every shoreline — the lake and the sea alike — so avatars cannot walk
    /// into water. The terrain body alone lets them wade down the lakebed (it is just ground), and
    /// the y = 0 safety floor that once stopped them did so by letting them walk on the surface.
    ///
    /// Traced from <see cref="WorldGeometry.HeightAt"/> on a grid: wherever a dry cell borders a
    /// wet one, a vertical face goes up on the shared edge. One concave shape for the lot, with
    /// backface collision on, so the wall blocks from either side.
    /// </summary>
    public static StaticBody3D WaterBarrier()
    {
        float half = WorldConstants.World * 0.5f;
        int n = (int)(WorldConstants.World / ShoreStep);
        var height = new float[n, n];
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            height[i, j] = WorldGeometry.HeightAt(-half + (i + 0.5f) * ShoreStep, -half + (j + 0.5f) * ShoreStep);

        bool Wet(int i, int j) => height[i, j] <= WorldConstants.Water + ShoreMargin;

        var faces = new List<Vector3>();
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            float x0 = -half + i * ShoreStep, z0 = -half + j * ShoreStep;
            if (i + 1 < n && Wet(i, j) != Wet(i + 1, j))
                AddFace(faces, new Vector3(x0 + ShoreStep, 0f, z0), new Vector3(x0 + ShoreStep, 0f, z0 + ShoreStep),
                    Mathf.Max(height[i, j], height[i + 1, j]));
            if (j + 1 < n && Wet(i, j) != Wet(i, j + 1))
                AddFace(faces, new Vector3(x0, 0f, z0 + ShoreStep), new Vector3(x0 + ShoreStep, 0f, z0 + ShoreStep),
                    Mathf.Max(height[i, j], height[i, j + 1]));
        }

        var shape = new ConcavePolygonShape3D { BackfaceCollision = true };
        shape.SetFaces(faces.ToArray());
        var body = new StaticBody3D { Name = "WaterBarrier" };
        body.AddChild(new CollisionShape3D { Shape = shape });
        return body;
    }

    /// <summary>
    /// One wall quad on the edge a→b. It starts below the waterline and rises well above the dry
    /// side's ground, so a shore that is a cliff is walled to the top, not just at sea level.
    /// </summary>
    private static void AddFace(List<Vector3> faces, Vector3 a, Vector3 b, float dryHeight)
    {
        float bottom = WorldConstants.Water - 4f;
        float top = dryHeight + 3f;
        Vector3 a0 = a with { Y = bottom }, b0 = b with { Y = bottom };
        Vector3 a1 = a with { Y = top }, b1 = b with { Y = top };
        faces.AddRange(new[] { a0, b0, b1, a0, b1, a1 });
    }

    private static void AddWall(Node3D root, Vector3 size, Vector3 position)
    {
        var wall = new StaticBody3D { Name = "WorldEdge", Position = position };
        wall.AddChild(new CollisionShape3D { Shape = new BoxShape3D { Size = size } });
        root.AddChild(wall);
    }
}
