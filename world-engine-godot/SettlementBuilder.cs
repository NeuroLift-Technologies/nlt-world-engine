using Godot;
using System;
using System.Collections.Generic;

namespace NltWorldEngine;

public static class SettlementBuilder
{
    public sealed record Plan(float X, float Z, float Rad, float R, float Rot, float Kind);

    public enum BuildingKind { Apartment, Office, Shop, School }

    // Deterministic spread across 19 buildings — all four kinds present, homes the most common.
    private static readonly BuildingKind[] KindPattern =
    {
        BuildingKind.Apartment, BuildingKind.Office, BuildingKind.Shop, BuildingKind.School,
        BuildingKind.Apartment, BuildingKind.Apartment, BuildingKind.Office, BuildingKind.Shop,
        BuildingKind.Apartment, BuildingKind.School, BuildingKind.Apartment, BuildingKind.Office,
        BuildingKind.Apartment, BuildingKind.Shop, BuildingKind.Apartment, BuildingKind.Office,
        BuildingKind.Apartment, BuildingKind.School, BuildingKind.Apartment,
    };

    /// <summary>
    /// Radius of the plaza disc at the settlement centre, in metres.
    /// <see cref="BuildPlans"/> places buildings outside this radius, and <see cref="Build"/> draws
    /// the disc at exactly this size. They must stay derived from the same constant: when the
    /// placement ring started at 7 m while the plaza was 13 m across, buildings were generated
    /// standing on the plaza and their portals were unreachable through solid geometry.
    /// </summary>
    public const float PlazaRadius = 13f;

    /// <summary>Widest half-extent a building reaches from its centre: Rad (max 6.4) * 1.5.</summary>
    private const float MaxBuildingHalfExtent = 9.6f;

    /// <summary>Radial roads drawn from the plaza out past the building ring.</summary>
    public const int RoadCount = 5;

    /// <summary>Angular offset of the first road, matching <see cref="Build"/>.</summary>
    private const float RoadAngleOffset = 0.4f;

    /// <summary>Road width in metres; half of it is the clearance a building needs.</summary>
    public const float RoadWidth = 2.5f;

    /// <summary>Road length: the fraction of <c>SettleR</c> each road spans.</summary>
    private const float RoadLengthFraction = 0.9f;

    /// <summary>
    /// Height of the road and plaza paving above the terrain surface, in metres. The paving lies on
    /// the ground rather than being a raised deck: avatars stand on the terrain body, so a deck
    /// floated above it sank their feet 0.2–0.5 m into the plaza, and flat road boxes ran up to
    /// 4.3 m into the hillsides. The plaza sits a centimetre above the roads, so the strip where
    /// they overlap draws the plaza instead of both flickering.
    /// </summary>
    public const float RoadLift = 0.03f, PlazaLift = 0.04f;

    /// <summary>Where each road's paving starts: just inside the plaza edge, so no grass shows between.</summary>
    public const float RoadPavingStart = PlazaRadius - 0.5f;

    /// <summary>Distance from the settlement centre to each road's far end.</summary>
    public const float RoadLength = WorldConstants.SettleR * RoadLengthFraction;

    /// <summary>
    /// Is a building footprint at (x, z) clear of every radial road?
    /// </summary>
    /// <remarks>
    /// Roads run from the settlement centre outwards, so they cross the whole building ring. The
    /// test is the perpendicular distance from the building centre to each road's axis, compared
    /// against the road's half-width plus <paramref name="buildingHalfExtent"/>. Treating the
    /// footprint as a circle of that radius is conservative: it can reject a placement that would
    /// have just missed at some rotations, but it can never let a building overlap a road.
    /// </remarks>
    private static bool ClearOfRoads(float x, float z, float buildingHalfExtent)
    {
        var dx = x - WorldConstants.SettleX;
        var dz = z - WorldConstants.SettleZ;
        var reach = RoadWidth * 0.5f + buildingHalfExtent;

        for (int i = 0; i < RoadCount; i++)
        {
            var a = i / (float)RoadCount * Mathf.Pi * 2f + RoadAngleOffset;
            var ax = MathF.Sin(a);
            var az = MathF.Cos(a);

            // Component along the road axis, clamped to the road's length: past the far end a
            // building is beyond the road, before the centre it is inside the plaza instead.
            var along = dx * ax + dz * az;
            if (along < 0f || along > RoadLength) continue;

            // Perpendicular distance from the building centre to the road axis.
            var lateral = MathF.Abs(dx * az - dz * ax);
            if (lateral < reach) return false;
        }

        return true;
    }

    /// <summary>
    /// The kind of the building at <paramref name="index"/> in <see cref="BuildPlans"/> order. The one
    /// source of truth for "what is this building": the renderer (<see cref="Build"/>) and the agents'
    /// perception anchors (<c>WorldAnchors</c>) must both read it, or agents perceive a different town
    /// from the one observers see.
    /// </summary>
    public static BuildingKind KindAt(int index) => KindPattern[index % KindPattern.Length];

    /// <summary>Plain word for the doorway label.</summary>
    public static string KindLabel(BuildingKind k) => k switch
    {
        BuildingKind.Apartment => "Home",
        BuildingKind.Office => "Office",
        BuildingKind.Shop => "Shop",
        BuildingKind.School => "School",
        _ => "Building",
    };

    /// <summary>Feed-style scene id; the prefix is what <c>WorldView.ShowScene</c> maps to a level.</summary>
    public static string SceneIdFor(BuildingKind k) => k switch
    {
        BuildingKind.Apartment => "personal_1",
        BuildingKind.Office => "workplace_1",
        BuildingKind.Shop => "social_1",
        BuildingKind.School => "academic_1",
        _ => "personal_1",
    };

    /// <summary>
    /// Scene id for building <paramref name="index"/>'s doorway: the kind's prefix plus the
    /// building's own number (<c>personal_3</c>, <c>workplace_7</c>…), so each building opens an
    /// interior dressed in its own colour scheme (<see cref="InteriorStyle"/>). The prefix still maps
    /// every building of a kind to that kind's level.
    /// </summary>
    public static string SceneIdFor(BuildingKind k, int index)
    {
        string id = SceneIdFor(k);
        return $"{id[..id.LastIndexOf('_')]}_{index + 1}";
    }

    /// <summary>Meta key on each building's collision body: its index into the portal list.</summary>
    public const string PortalIndexMeta = "portal_index";

    /// <summary>Okabe–Ito hues, one per kind; the label carries the meaning and colour reinforces it.</summary>
    public static Color KindColour(BuildingKind k) => k switch
    {
        BuildingKind.Apartment => new Color("56b4e9"),
        BuildingKind.Office => new Color("009e73"),
        BuildingKind.Shop => new Color("e69f00"),
        BuildingKind.School => new Color("cc79a7"),
        _ => Colors.White,
    };

    /// <summary>
    /// The plaza's paving as a triangle list (three vertices per triangle, faces up), every vertex
    /// <see cref="PlazaLift"/> above <see cref="TerrainBuilder.SurfaceHeightAt"/>. Pure geometry, so
    /// the harness can check it lies on the ground; <see cref="Build"/> turns it into the mesh.
    /// </summary>
    public static List<Vector3> PlazaPaving()
    {
        // About a metre between rings, and 1.7 m between spokes at the rim: fine enough that the
        // terrain's own triangles cannot rise through the paving between its vertices.
        const int rings = 13, sectors = 48;
        Vector3 At(int ring, int sector)
        {
            float r = PlazaRadius * ring / rings, a = sector / (float)sectors * Mathf.Tau;
            return OnGround(WorldConstants.SettleX + MathF.Cos(a) * r, WorldConstants.SettleZ + MathF.Sin(a) * r, PlazaLift);
        }

        var tris = new List<Vector3>();
        for (int k = 0; k < rings; k++)
            for (int s = 0; s < sectors; s++)
                AddQuad(tris, At(k, s), At(k, s + 1), At(k + 1, s + 1), At(k + 1, s));
        return tris;
    }

    /// <summary>
    /// Road <paramref name="index"/>'s paving as a triangle list, <see cref="RoadLift"/> above the
    /// terrain surface from <see cref="RoadPavingStart"/> to <see cref="RoadLength"/>, so it climbs
    /// and dips with the ground. Same axis as <see cref="ClearOfRoads"/> tests buildings against.
    /// </summary>
    public static List<Vector3> RoadPaving(int index)
    {
        float a = index / (float)RoadCount * Mathf.Pi * 2f + RoadAngleOffset;
        float ax = MathF.Sin(a), az = MathF.Cos(a);
        // A quarter metre along by 0.31 m across. Out on the hills the terrain's 2.2 m triangles meet
        // at creases between paving vertices, and the paving floats off them in proportion to the
        // spacing: 9 cm at 1 m by 1.25 m, 6 cm at half that.
        const int columns = 8;
        int steps = (int)MathF.Ceiling((RoadLength - RoadPavingStart) / 0.25f);
        Vector3 At(int step, int column)
        {
            float d = RoadPavingStart + (RoadLength - RoadPavingStart) * step / steps;
            float lateral = RoadWidth * (column / (float)columns - 0.5f);
            return OnGround(WorldConstants.SettleX + ax * d + az * lateral, WorldConstants.SettleZ + az * d - ax * lateral, RoadLift);
        }

        var tris = new List<Vector3>();
        for (int k = 0; k < steps; k++)
            for (int c = 0; c < columns; c++)
                AddQuad(tris, At(k, c), At(k, c + 1), At(k + 1, c + 1), At(k + 1, c));
        return tris;
    }

    private static Vector3 OnGround(float x, float z, float lift) => new(x, TerrainBuilder.SurfaceHeightAt(x, z) + lift, z);

    /// <summary>Append quad (p00, p10, p11, p01) as two upward triangles.</summary>
    private static void AddQuad(List<Vector3> tris, Vector3 p00, Vector3 p10, Vector3 p11, Vector3 p01)
    {
        AddUpward(tris, p00, p10, p11);
        AddUpward(tris, p00, p11, p01);
    }

    /// <summary>
    /// Append one triangle wound to face up, as <see cref="TerrainBuilder"/>'s are (Godot's front
    /// face is clockwise seen from above, which gives a negative cross-product Y). Triangles with
    /// no area, at the plaza's centre, are dropped.
    /// </summary>
    private static void AddUpward(List<Vector3> tris, Vector3 a, Vector3 b, Vector3 c)
    {
        float y = (b - a).Cross(c - a).Y;
        if (MathF.Abs(y) < 1e-6f) return;
        if (y > 0f) (b, c) = (c, b);
        tris.Add(a);
        tris.Add(b);
        tris.Add(c);
    }

    private static MeshInstance3D PavingMesh(List<Vector3> tris, Material material)
    {
        var st = new SurfaceTool();
        st.Begin(Mesh.PrimitiveType.Triangles);
        foreach (var v in tris)
            st.AddVertex(v);
        st.GenerateNormals();
        st.SetMaterial(material);
        return new MeshInstance3D { Mesh = st.Commit(), CastShadow = GeometryInstance3D.ShadowCastingSetting.Off };
    }

    public static List<Plan> BuildPlans(SimulationRng rng)
    {
        var placed = new List<Plan>();
        // Roads and the plaza eat a large share of the ring, so rejection sampling needs far more
        // attempts than the 900 the unconstrained ring needed. The guard is a backstop against a
        // degenerate terrain, not a budget: it should never be the reason a town comes out small.
        int count = 19, guard = 0, maxAttempts = 40000;
        while (placed.Count < count && guard++ < maxAttempts)
        {
            float a = rng.Next() * Mathf.Pi * 2f;

            // Centre distance must clear the plaza disc plus this building's own widest
            // half-extent, or the footprint lands on the plaza. sqrt() keeps the ring
            // uniform in area rather than clustering at the inner edge.
            float minR = PlazaRadius + MaxBuildingHalfExtent;
            float maxR = WorldConstants.SettleR - 6f;
            if (maxR <= minR) return placed;

            // Size is drawn before placement so the road test can use this building's real
            // footprint. Using the worst case (9.6 m) for every candidate rejected so much of
            // the ring that only 6 of 19 buildings found a slot.
            float rad = rng.Range(4.2f, 6.4f);
            float halfExtent = rad * 1.5f;

            float r = minR + MathF.Sqrt(rng.Next()) * (maxR - minR);
            float x = WorldConstants.SettleX + MathF.Cos(a) * r;
            float z = WorldConstants.SettleZ + MathF.Sin(a) * r;
            float ds = MathF.Sqrt((x - WorldConstants.SettleX) * (x - WorldConstants.SettleX) + (z - WorldConstants.SettleZ) * (z - WorldConstants.SettleZ));
            if (ds > maxR) continue;
            if (ds - halfExtent < PlazaRadius) continue;
            if (!WorldGeometry.Walkable(x, z)) continue;
            if (!ClearOfRoads(x, z, halfExtent)) continue;

            bool clash = false;
            foreach (var p in placed)
                if (MathF.Sqrt((p.X - x) * (p.X - x) + (p.Z - z) * (p.Z - z)) < p.Rad + rad + 3.4f) { clash = true; break; }
            if (clash) continue;
            placed.Add(new Plan(x, z, rad, rng.Next(), rng.Next() * Mathf.Pi, rng.Next()));
        }
        return placed;
    }

    public static Node3D Build(List<Plan> plans, out List<Portal> portals)
    {
        portals = new List<Portal>();
        var root = new Node3D();
        var roofMat = new StandardMaterial3D { AlbedoColor = new Color(0x6b5340FF), Roughness = 0.78f };
        var glassMat = new StandardMaterial3D { AlbedoColor = new Color(0xffe0b0FF), EmissionEnabled = true, Emission = new Color(0xffc478FF), EmissionEnergyMultiplier = 0.85f, Roughness = 0.3f };
        var pathMat = new StandardMaterial3D { AlbedoColor = new Color(0x8a8377FF), Roughness = 0.98f };
        var doorMat = new StandardMaterial3D { AlbedoColor = new Color(0x54402fFF), Roughness = 0.8f };

        int i = 0;
        foreach (var plan in plans)
        {
            BuildingKind kind = KindAt(i);
            float y = WorldGeometry.HeightAt(plan.X, plan.Z);
            var g = new Node3D();

            // Each kind has its own silhouette; the door and portal marker are shared and sit on
            // whichever front face the archetype reports.
            float front = BuildingArchetypes.Build(g, kind, plan, i);

            var doorLocal = new Vector3(0, 1.05f, front + 0.02f);
            g.AddChild(new MeshInstance3D
            {
                Mesh = new BoxMesh { Size = new Vector3(1.15f, 2.1f, 0.14f) },
                MaterialOverride = doorMat,
                Position = doorLocal,
            });

            // The doorway affordance: the observer clicks this arch (or presses E) to enter the level.
            var marker = PortalMarker.Build(KindLabel(kind), KindColour(kind));
            marker.Position = new Vector3(0, 0, front + 0.09f);
            g.AddChild(marker);

            g.Position = new Vector3(plan.X, y, plan.Z);
            g.Rotation = new Vector3(0, plan.Rot, 0);
            // The walls the model cannot walk through. One box per building, sized by the
            // archetype so the collider and the silhouette never drift apart; a child of g so it
            // inherits the building's position and rotation for free.
            BuildingArchetypes.CollisionInfo(kind, plan, out Vector3 bodySize, out Vector3 bodyCentre);
            var body = new StaticBody3D { Name = $"Collision_{KindLabel(kind)}_{i}" };
            // The same box is the observer's click target: clicking anywhere on the building
            // enters it (WorldView.TryActivateBuildingAtScreen). Index into the portals list below.
            body.SetMeta(PortalIndexMeta, portals.Count);
            body.AddChild(new CollisionShape3D { Shape = new BoxShape3D { Size = bodySize }, Position = bodyCentre });
            g.AddChild(body);
            root.AddChild(g);

            portals.Add(new Portal(KindLabel(kind), KindLabel(kind), SceneIdFor(kind, i),
                g.Transform * doorLocal, g.Basis.Z.Normalized()));
            i++;
        }

        // Plaza and roads are paving on the ground. Avatars walk on the terrain body beneath, so
        // neither needs a collider of its own. Roads use the same RoadCount/RoadWidth/RoadAngleOffset
        // constants BuildPlans tests against, so a building can never be placed across one.
        root.AddChild(PavingMesh(PlazaPaving(), pathMat));
        for (int r = 0; r < RoadCount; r++)
            root.AddChild(PavingMesh(RoadPaving(r), pathMat));

        // well at plaza edge, standing on the ground
        var wellPos = OnGround(WorldConstants.SettleX + 8f, WorldConstants.SettleZ + 3f, 0f);
        root.AddChild(new MeshInstance3D { Mesh = new CylinderMesh { Height = 1.1f, TopRadius = 1.3f, BottomRadius = 1.45f, RadialSegments = 12 }, MaterialOverride = new StandardMaterial3D { AlbedoColor = new Color(0x8a8078FF), Roughness = 0.95f }, Position = wellPos + new Vector3(0, 0.55f, 0) });
        root.AddChild(new MeshInstance3D { Mesh = new CylinderMesh { Height = 0.1f, TopRadius = 1.05f, BottomRadius = 1.05f, RadialSegments = 12 }, MaterialOverride = new StandardMaterial3D { AlbedoColor = new Color(0x2f6f74FF), Roughness = 0.3f }, Position = wellPos + new Vector3(0, 1.05f, 0) });
        root.AddChild(new MeshInstance3D { Mesh = new CylinderMesh { Height = 2.0f, TopRadius = 0f, BottomRadius = 1.7f, RadialSegments = 4 }, MaterialOverride = roofMat, Position = wellPos + new Vector3(0, 2.4f, 0), Rotation = new Vector3(0, Mathf.Pi / 4f, 0) });
        // The well stands on the plaza walk-line; without a body the avatar tours straight
        // through its masonry. A box approximation is exact enough at this size.
        var wellBody = new StaticBody3D { Name = "Collision_Well", Position = wellPos + new Vector3(0, 0.6f, 0) };
        wellBody.AddChild(new CollisionShape3D { Shape = new BoxShape3D { Size = new Vector3(2.9f, 1.2f, 2.9f) } });
        root.AddChild(wellBody);

        // benches around plaza: a seat on two legs, standing on the paving. (The old seat slab sat
        // flush with the raised plaza deck; on paving at ground level it would have floated.)
        for (int b = 0; b < 6; b++)
        {
            float a = b / 6f * Mathf.Pi * 2f + 0.2f;
            float rr = 10.5f;
            var bench = new Node3D
            {
                Position = OnGround(WorldConstants.SettleX + MathF.Cos(a) * rr, WorldConstants.SettleZ + MathF.Sin(a) * rr, PlazaLift),
                Rotation = new Vector3(0, a + Mathf.Pi / 2f, 0),
            };
            bench.AddChild(new MeshInstance3D { Mesh = new BoxMesh { Size = new Vector3(2.2f, 0.1f, 0.55f) }, MaterialOverride = doorMat, Position = new Vector3(0, 0.45f, 0) });
            foreach (float legX in new[] { -0.85f, 0.85f })
                bench.AddChild(new MeshInstance3D { Mesh = new BoxMesh { Size = new Vector3(0.12f, 0.4f, 0.45f) }, MaterialOverride = doorMat, Position = new Vector3(legX, 0.2f, 0) });
            root.AddChild(bench);
        }

        // desks with emissive monitors
        for (int d = 0; d < 4; d++)
        {
            float a = d / 4f * Mathf.Pi * 2f + 0.9f;
            float rr = 15f;
            float dx = WorldConstants.SettleX + MathF.Cos(a) * rr, dz = WorldConstants.SettleZ + MathF.Sin(a) * rr;
            float dy = WorldGeometry.HeightAt(dx, dz);
            var desk = new Node3D { Position = new Vector3(dx, dy, dz), Rotation = new Vector3(0, a, 0) };
            desk.AddChild(new MeshInstance3D { Mesh = new BoxMesh { Size = new Vector3(2.0f, 0.12f, 0.9f) }, MaterialOverride = doorMat, Position = new Vector3(0, 0.95f, 0) });
            desk.AddChild(new MeshInstance3D { Mesh = new BoxMesh { Size = new Vector3(0.8f, 0.5f, 0.08f) }, MaterialOverride = glassMat, Position = new Vector3(0, 1.35f, -0.25f) });
            root.AddChild(desk);
        }

        return root;
    }
}
