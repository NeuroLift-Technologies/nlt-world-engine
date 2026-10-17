using Godot;
using System;
using System.Collections.Generic;

namespace NltWorldEngine;

/// <summary>
/// One silhouette per <see cref="SettlementBuilder.BuildingKind"/>, so an observer can tell a home
/// from an office from a shop from a school across the settlement before reading any label — shape,
/// colour and word together, never colour alone (AGENTS.md §2).
///
/// Each builder adds meshes to a building-local node (origin at ground level, front face toward +Z)
/// and returns the Z of that front face, where <see cref="SettlementBuilder.Build"/> puts the shared
/// door and portal marker. Bodies stay inside the plan's footprint (Rad*1.5 × Rad*1.25); the small
/// front details (canopy, awning, café tables, portico) fit inside the 1.5 × Rad clearance radius
/// that <see cref="SettlementBuilder.BuildPlans"/> already reserves, and leave the door axis clear
/// so <see cref="Portal.EntryPoint"/> stays reachable.
///
/// These are still engine primitives — Stage 1 of the art plan replaces each builder's body with an
/// authored model while keeping this contract (local origin, +Z front, returned front Z).
/// </summary>
public static class BuildingArchetypes
{
    private static readonly Color[] HomeWalls = { new(0xd9cdb8FF), new(0xc9bfa9FF), new(0xe0d4c0FF), new(0xbfae96FF), new(0xcfc4aeFF), new(0xc4b49cFF) };
    private static readonly Color[] HomeRoofs = { new(0x7a4a3cFF), new(0x6b5340FF), new(0x8a5a44FF), new(0x5f4a3eFF), new(0x74503fFF) };
    private static readonly Color[] ShopWalls = { new(0xe8d6b0FF), new(0xd98f6aFF), new(0xf0e4cfFF), new(0xc9a27eFF) };

    private static readonly Color Stone = new(0x7d776dFF);
    private static readonly Color WarmGlass = new(0xffe0b0FF);
    private static readonly Color WarmGlow = new(0xffc478FF);
    private static readonly Color Trim = new(0xe8e2d4FF);

    // Materials are shared across buildings: 19 buildings × a dozen parts would otherwise make
    // hundreds of identical StandardMaterial3D instances and break draw-call batching.
    private static readonly Dictionary<string, StandardMaterial3D> Mats = new();

    private static StandardMaterial3D Mat(Color albedo, float rough = 0.85f, Color? glow = null, float glowEnergy = 0.85f)
    {
        string key = $"{albedo.ToHtml()}|{rough}|{glow?.ToHtml()}|{glowEnergy}";
        if (Mats.TryGetValue(key, out var cached))
            return cached;
        var m = new StandardMaterial3D { AlbedoColor = albedo, Roughness = rough };
        if (glow.HasValue)
        {
            m.EmissionEnabled = true;
            m.Emission = glow.Value;
            m.EmissionEnergyMultiplier = glowEnergy;
        }
        Mats[key] = m;
        return m;
    }

    private static MeshInstance3D Box(Node3D parent, Vector3 size, Vector3 pos, Material mat, float rotX = 0f)
    {
        var mi = new MeshInstance3D
        {
            Mesh = new BoxMesh { Size = size },
            MaterialOverride = mat,
            Position = pos,
            Rotation = new Vector3(rotX, 0f, 0f),
        };
        parent.AddChild(mi);
        return mi;
    }

    private static void Cylinder(Node3D parent, float top, float bottom, float height, Vector3 pos, Material mat, int segments = 12)
    {
        parent.AddChild(new MeshInstance3D
        {
            Mesh = new CylinderMesh { TopRadius = top, BottomRadius = bottom, Height = height, RadialSegments = segments },
            MaterialOverride = mat,
            Position = pos,
        });
    }

    /// <summary>
    /// A stone base sunk below the ground line. Buildings sit at the terrain height of their centre,
    /// so on a slope one side would otherwise float; the plinth fills that gap.
    /// </summary>
    private static void Plinth(Node3D g, float w, float d)
        => Box(g, new Vector3(w + 0.25f, 1.4f, d + 0.25f), new Vector3(0f, -0.55f, 0f), Mat(Stone, 0.95f));

    /// <summary>Build the body for <paramref name="kind"/> into <paramref name="g"/>; returns the front face Z.</summary>
    public static float Build(Node3D g, SettlementBuilder.BuildingKind kind, SettlementBuilder.Plan plan, int index)
    {
        float w = plan.Rad * 1.5f, d = plan.Rad * 1.25f;
        var accent = SettlementBuilder.KindColour(kind);
        return kind switch
        {
            SettlementBuilder.BuildingKind.Office => Office(g, w, d, plan.R, accent),
            SettlementBuilder.BuildingKind.Shop => Shop(g, w, d, index, accent),
            SettlementBuilder.BuildingKind.School => School(g, w, d, accent),
            _ => Home(g, w, d, plan.R, index),
        };
    }

    /// <summary>Home: a one- or two-storey house under a gabled roof, with a chimney and a front step.</summary>
    private static float Home(Node3D g, float w, float d, float r, int i)
    {
        float wallH = 3.2f + r * 2.6f, roofH = 2.0f + r * 1.2f;
        Plinth(g, w, d);
        Box(g, new Vector3(w, wallH, d), new Vector3(0f, wallH / 2f, 0f), Mat(HomeWalls[i % HomeWalls.Length]));

        // PrismMesh's ridge runs along its local Z; turned a quarter so the ridge runs along X and the
        // slope faces the street, which reads as "house" from the observer's high camera.
        var roofMat = Mat(HomeRoofs[i % HomeRoofs.Length], 0.78f);
        g.AddChild(new MeshInstance3D
        {
            Mesh = new PrismMesh { Size = new Vector3(d + 0.7f, roofH, w + 0.5f) },
            MaterialOverride = roofMat,
            Position = new Vector3(0f, wallH + roofH / 2f, 0f),
            Rotation = new Vector3(0f, Mathf.Pi / 2f, 0f),
        });
        Box(g, new Vector3(0.7f, roofH + 0.4f, 0.7f), new Vector3(w * 0.28f, wallH + roofH * 0.5f, -d * 0.18f), roofMat);

        var glass = Mat(WarmGlass, 0.3f, WarmGlow);
        int floors = wallH > 4.6f ? 2 : 1;
        for (int f = 0; f < floors; f++)
        for (int s = -1; s <= 1; s += 2)
            Box(g, new Vector3(1.0f, 0.9f, 0.1f), new Vector3(s * w * 0.3f, 1.7f + f * 2.6f, d / 2f + 0.02f), glass);

        Box(g, new Vector3(1.8f, 0.2f, 0.9f), new Vector3(0f, 0.1f, d / 2f + 0.45f), Mat(Stone, 0.95f));
        return d / 2f;
    }

    /// <summary>Office: a 4–7 storey tower with ribbon windows, a glass lobby, an entrance canopy and roof plant.</summary>
    private static float Office(Node3D g, float w, float d, float r, Color accent)
    {
        float tw = w * 0.8f, td = d * 0.85f;
        int floors = 4 + (int)(r * 4f);
        const float floorH = 3.2f;
        float h = floors * floorH;
        var concrete = Mat(new Color(0xb8bcc2FF), 0.8f);
        var dark = Mat(new Color(0x4a4f57FF), 0.6f);
        var glass = Mat(new Color(0x6f9fc4FF), 0.15f, new Color(0x9fc9ecFF), 0.55f);

        Plinth(g, tw, td);
        Box(g, new Vector3(tw, h, td), new Vector3(0f, h / 2f, 0f), concrete);

        // One glass ribbon per upper floor, slightly proud of every face so it wraps the tower.
        for (int f = 1; f < floors; f++)
            Box(g, new Vector3(tw + 0.06f, 1.7f, td + 0.06f), new Vector3(0f, f * floorH + 1.6f, 0f), glass);

        Box(g, new Vector3(tw * 0.75f, 2.4f, 0.1f), new Vector3(0f, 1.3f, td / 2f + 0.03f), glass);
        Box(g, new Vector3(3.2f, 0.18f, 1.8f), new Vector3(0f, 2.75f, td / 2f + 0.9f), dark);
        Box(g, new Vector3(3.2f, 0.25f, 0.12f), new Vector3(0f, 2.98f, td / 2f + 1.78f), Mat(accent, 0.5f, accent, 0.6f));

        Box(g, new Vector3(tw + 0.3f, 0.5f, td + 0.3f), new Vector3(0f, h + 0.25f, 0f), dark);
        Box(g, new Vector3(tw * 0.35f, 1.2f, td * 0.3f), new Vector3(-tw * 0.15f, h + 1.1f, -td * 0.1f), concrete);
        Cylinder(g, 0.05f, 0.08f, 3.5f, new Vector3(tw * 0.3f, h + 2.2f, -td * 0.25f), dark, 6);
        return td / 2f;
    }

    /// <summary>Shop: a single-storey storefront with big windows, a sign, a striped awning and café tables.</summary>
    private static float Shop(Node3D g, float w, float d, int i, Color accent)
    {
        float sw = w, sd = d * 0.8f;
        const float h = 4.2f;
        var trim = Mat(new Color(0x5a4636FF), 0.7f);
        var white = Mat(Trim, 0.8f);
        var accentMat = Mat(accent, 0.7f);

        Plinth(g, sw, sd);
        Box(g, new Vector3(sw, h, sd), new Vector3(0f, h / 2f, 0f), Mat(ShopWalls[i % ShopWalls.Length]));
        Box(g, new Vector3(sw + 0.3f, 0.45f, sd + 0.3f), new Vector3(0f, h + 0.2f, 0f), trim);

        // Storefront panes either side of the door.
        float paneW = sw / 2f - 1.2f;
        var glass = Mat(WarmGlass, 0.25f, WarmGlow, 1.0f);
        for (int s = -1; s <= 1; s += 2)
            Box(g, new Vector3(paneW, 2.2f, 0.1f), new Vector3(s * (0.75f + paneW / 2f), 1.6f, sd / 2f + 0.03f), glass);

        Box(g, new Vector3(sw * 0.6f, 0.8f, 0.12f), new Vector3(0f, h - 0.55f, sd / 2f + 0.08f), Mat(accent, 0.5f, accent, 0.4f));

        // Striped awning, tilted so its outer edge drops toward the street.
        const int stripes = 8;
        float span = sw * 0.9f, stripeW = span / stripes;
        for (int k = 0; k < stripes; k++)
            Box(g, new Vector3(stripeW, 0.06f, 1.7f),
                new Vector3(-span / 2f + (k + 0.5f) * stripeW, 3.0f, sd / 2f + 0.75f),
                k % 2 == 0 ? accentMat : white, rotX: 0.35f);

        // Two café tables with umbrellas, kept off the door axis.
        for (int s = -1; s <= 1; s += 2)
        {
            var at = new Vector3(s * sw * 0.32f, 0f, sd / 2f + 2.3f);
            Cylinder(g, 0.45f, 0.45f, 0.06f, at + new Vector3(0f, 0.75f, 0f), white);
            Cylinder(g, 0.05f, 0.05f, 2.3f, at + new Vector3(0f, 1.15f, 0f), trim, 6);
            Cylinder(g, 0f, 1.1f, 0.5f, at + new Vector3(0f, 2.3f, 0f), accentMat, 8);
        }
        return sd / 2f;
    }

    /// <summary>School: a broad two-storey brick block with a columned portico, a cupola clock and a flag.</summary>
    private static float School(Node3D g, float w, float d, Color accent)
    {
        float bw = w, bd = d * 0.75f;
        const float h = 7.0f;
        var brick = Mat(new Color(0x9c4a3aFF), 0.9f);
        var trim = Mat(Trim, 0.75f);
        var slate = Mat(new Color(0x3f4650FF), 0.7f);
        var glass = Mat(WarmGlass, 0.3f, WarmGlow);

        Plinth(g, bw, bd);
        Box(g, new Vector3(bw, h, bd), new Vector3(0f, h / 2f, 0f), brick);
        Box(g, new Vector3(bw + 0.3f, 0.4f, bd + 0.3f), new Vector3(0f, h + 0.2f, 0f), trim);

        // Two rows of tall windows, leaving the centre bay for the portico.
        int cols = Math.Max(2, (int)(bw / 2.2f));
        for (int row = 0; row < 2; row++)
        for (int c = 0; c < cols; c++)
        {
            float x = -bw / 2f + (c + 0.5f) * bw / cols;
            if (MathF.Abs(x) < 2.6f)
                continue;
            Box(g, new Vector3(1.0f, 1.4f, 0.1f), new Vector3(x, 1.9f + row * 3.0f, bd / 2f + 0.02f), glass);
        }

        // Portico: four columns, an entablature and a triangular pediment. The middle gap is 2.6 m,
        // wide enough that the door axis — and the portal entry point on it — stays open.
        float pz = bd / 2f + 1.0f;
        foreach (float x in new[] { -2.1f, -1.3f, 1.3f, 2.1f })
            Cylinder(g, 0.2f, 0.24f, 5.0f, new Vector3(x, 2.5f, pz), trim);
        Box(g, new Vector3(4.9f, 0.45f, 1.5f), new Vector3(0f, 5.2f, bd / 2f + 0.75f), trim);
        g.AddChild(new MeshInstance3D
        {
            Mesh = new PrismMesh { Size = new Vector3(4.9f, 1.3f, 1.5f) },
            MaterialOverride = trim,
            Position = new Vector3(0f, 6.08f, bd / 2f + 0.75f),
        });
        Box(g, new Vector3(5.2f, 0.3f, 1.8f), new Vector3(0f, 0.15f, bd / 2f + 0.9f), Mat(Stone, 0.95f));

        // Cupola with a clock face, centred on the roof.
        Box(g, new Vector3(1.8f, 1.6f, 1.8f), new Vector3(0f, h + 1.2f, 0f), trim);
        g.AddChild(new MeshInstance3D
        {
            Mesh = new CylinderMesh { TopRadius = 0f, BottomRadius = 1.45f, Height = 1.4f, RadialSegments = 4 },
            MaterialOverride = slate,
            Position = new Vector3(0f, h + 2.7f, 0f),
            Rotation = new Vector3(0f, Mathf.Pi / 4f, 0f),
        });
        g.AddChild(new MeshInstance3D
        {
            Mesh = new CylinderMesh { TopRadius = 0.55f, BottomRadius = 0.55f, Height = 0.08f, RadialSegments = 16 },
            MaterialOverride = Mat(new Color(0xf5f1e6FF), 0.5f, new Color(0xf5f1e6FF), 0.3f),
            Position = new Vector3(0f, h + 1.25f, 0.92f),
            Rotation = new Vector3(Mathf.Pi / 2f, 0f, 0f),
        });

        // Flagpole at the front corner, flag in the school's accent colour.
        var pole = new Vector3(bw * 0.42f, 0f, bd / 2f + 1.6f);
        Cylinder(g, 0.05f, 0.07f, 8.0f, pole + new Vector3(0f, 4.0f, 0f), slate, 6);
        Box(g, new Vector3(1.4f, 0.9f, 0.04f), pole + new Vector3(0.72f, 7.4f, 0f), Mat(accent, 0.7f));
        return bd / 2f;
    }
}
