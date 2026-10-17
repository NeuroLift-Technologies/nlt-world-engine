using Godot;
using System;
using System.Collections.Generic;

namespace NltWorldEngine;

/// <summary>
/// Dresses the imported interiors so an observer can read the room at a glance.
///
/// The UE export gave every object in <c>Personal_Level.fbx</c> the same <c>MI_Wall_Light</c>
/// material, so the sofa, bed, fridge and walls all rendered the same off-white and the home read
/// as an empty white box. Objects keep their imported names (<c>Sofa_Base</c>, <c>Kit_Fridge</c>,
/// <c>Bath_Tub</c>…), so materials are assigned by name prefix at load time — the scene file and the
/// FBX stay untouched, and <c>HomePhysicalBoundary</c>'s collision is unaffected.
///
/// Each home gets one of a few colour schemes, chosen from the scene id's number
/// (<c>personal_3</c> → scheme 3), so stepping into a different house looks like a different family's
/// home while the layout stays the one the agents know.
/// </summary>
public static class InteriorStyle
{
    /// <summary>Meshes in this group are scenery around the room and are left out of camera framing.</summary>
    public const string FrameSkipGroup = "interior_frame_skip";

    private sealed record HomeScheme(Color Walls, Color Sofa, Color Blanket, Color LivingRug, Color BedroomRug);

    private static readonly HomeScheme[] HomeSchemes =
    {
        new(new Color(0xefe6d6FF), new Color(0x3f7f8cFF), new Color(0x5b7fa6FF), new Color(0xb5523bFF), new Color(0x6a5a9cFF)),
        new(new Color(0xe4ece6FF), new Color(0x8c5a3cFF), new Color(0xc98b6bFF), new Color(0x4f6d7aFF), new Color(0x7a8c5bFF)),
        new(new Color(0xf1e3dcFF), new Color(0x5b6b8cFF), new Color(0x8a6aa6FF), new Color(0xc9a24fFF), new Color(0x4f7a8cFF)),
        new(new Color(0xe6e9f0FF), new Color(0x7a8c5bFF), new Color(0x6aa68aFF), new Color(0x8c4f6dFF), new Color(0xb5733bFF)),
    };

    private static readonly Dictionary<string, StandardMaterial3D> Mats = new();

    private static StandardMaterial3D Mat(Color albedo, float rough = 0.8f, float metal = 0f, Color? glow = null, float glowEnergy = 1f)
    {
        string key = $"{albedo.ToHtml()}|{rough}|{metal}|{glow?.ToHtml()}|{glowEnergy}";
        if (Mats.TryGetValue(key, out var cached))
            return cached;
        var m = new StandardMaterial3D { AlbedoColor = albedo, Roughness = rough, Metallic = metal };
        if (glow.HasValue)
        {
            m.EmissionEnabled = true;
            m.Emission = glow.Value;
            m.EmissionEnergyMultiplier = glowEnergy;
        }
        Mats[key] = m;
        return m;
    }

    /// <summary>Dress <paramref name="levelRoot"/> for <paramref name="sceneId"/>. Safe to call again with another id.</summary>
    public static void Apply(Node levelRoot, string sceneId)
    {
        if (sceneId.StartsWith("personal", StringComparison.OrdinalIgnoreCase))
            DressHome(levelRoot, SchemeIndex(sceneId));
    }

    /// <summary>The number after the last underscore (<c>personal_3</c> → 3), or 1 when there is none.</summary>
    private static int SchemeIndex(string sceneId)
    {
        int us = sceneId.LastIndexOf('_');
        return us >= 0 && int.TryParse(sceneId.AsSpan(us + 1), out int n) ? Math.Max(n, 0) : 1;
    }

    private static void DressHome(Node root, int scheme)
    {
        var s = HomeSchemes[(scheme - 1 + HomeSchemes.Length * 8) % HomeSchemes.Length];

        var walnut = Mat(new Color(0x6b4a32FF), 0.6f);
        var oak = Mat(new Color(0xb08a5aFF), 0.65f);
        var cabinet = Mat(new Color(0xece7dcFF), 0.5f);
        var stone = Mat(new Color(0x3d3d40FF), 0.35f);
        var steel = Mat(new Color(0xc9ccd1FF), 0.35f, 0.6f);
        var black = Mat(new Color(0x1d1f22FF), 0.4f);
        var porcelain = Mat(new Color(0xf4f4f2FF), 0.15f);
        var brass = Mat(new Color(0xb08d57FF), 0.35f, 0.8f);
        var warmGlow = Mat(new Color(0xf3e6c8FF), 0.6f, 0f, new Color(0xffd9a0FF), 1.2f);

        // First match wins, so a longer name must come before its prefix (Kit_Counter_Top before
        // Kit_Counter, Washer_Door before Wash…).
        var rules = new (string Prefix, Material Mat)[]
        {
            ("Wall_", Mat(s.Walls, 0.9f)), ("Corridor_Wall", Mat(s.Walls, 0.9f)),
            ("MidWall", Mat(s.Walls, 0.9f)), ("BathBathDiv", Mat(s.Walls, 0.9f)),
            ("Front_Door", walnut),
            ("Hall_Rug", Mat(new Color(0x8a6d4fFF), 0.95f)),
            ("Living_Rug", Mat(s.LivingRug, 0.95f)),
            ("Bedroom_Rug", Mat(s.BedroomRug, 0.95f)),
            ("Coatrack", brass),
            ("Sofa_", Mat(s.Sofa, 0.9f)),
            ("Coffee_", walnut),
            ("TV_Stand", walnut),
            ("TV", Mat(new Color(0x15171aFF), 0.15f, 0f, new Color(0x1e2a3cFF), 0.6f)),
            ("Lamp_Pole", brass), ("Lamp_Shade", warmGlow),
            ("Kit_Counter_Top", stone), ("Kit_Stove_Top", black),
            ("Kit_Counter", cabinet), ("Kit_Cabinet", cabinet),
            ("Kit_Fridge", steel), ("Kit_Stove", steel),
            ("Kit_Island", oak), ("Island_Leg", black),
            ("Stool_Seat", oak), ("Stool_Pole", black),
            ("Dining_Chair", walnut), ("Dining_", oak),
            ("Bed_Headboard", Mat(new Color(0x7a6a5aFF), 0.9f)),
            ("Bed_Mattress", Mat(new Color(0xf2efe8FF), 0.9f)),
            ("Bed_Blanket", Mat(s.Blanket, 0.95f)),
            ("Bed_Frame", walnut),
            ("Pillow", Mat(new Color(0xfafafaFF), 0.95f)),
            ("Nightstand", walnut), ("Night_Lamp", warmGlow),
            ("Wardrobe", oak), ("Dresser", oak),
            ("Toilet", porcelain), ("Bath_Sink", porcelain), ("Bath_Tub", porcelain),
            ("Bath_Mirror", Mat(new Color(0xd8e2e8FF), 0.05f, 1f)),
            ("Office_Monitor", Mat(new Color(0x15171aFF), 0.15f, 0f, new Color(0x2a4a75FF), 0.9f)),
            ("Office_Chair", black), ("Office_Leg", black), ("Office_Desk", oak),
            ("Washer_Door", Mat(new Color(0x9fb0bdFF), 0.1f, 0.3f)),
            ("Washing_Machine", cabinet),
            ("Plant_Pot", Mat(new Color(0xb8643fFF), 0.85f)),
            ("Plant_Foliage", Mat(new Color(0x4f7a3aFF), 0.9f)),
        };

        foreach (Node child in root.GetChildren())
        {
            if (child is not MeshInstance3D mi)
                continue;
            string name = mi.Name.ToString();
            if (name.StartsWith("UCX_", StringComparison.Ordinal))
                continue;

            // The room has no ceiling mesh, so from the overhead camera the ceiling fixtures float as
            // grey slabs at 3.4 m. The room is lit by WorldView's interior lights, not these meshes.
            if (name.StartsWith("Ceiling_Light", StringComparison.Ordinal))
            {
                mi.Visible = false;
                continue;
            }

            if (name == "Floor")
            {
                // The imported floor is one 80 m slab, far larger than the 24 × 18 m house. Keep it
                // as a lawn around the home, out of the camera framing, and lay a wood floor that
                // matches the walls on top of it.
                mi.MaterialOverride = Mat(new Color(0x6d8a4aFF), 0.95f);
                mi.AddToGroup(FrameSkipGroup);
                continue;
            }

            foreach (var (prefix, mat) in rules)
            {
                if (name.StartsWith(prefix, StringComparison.Ordinal))
                {
                    mi.MaterialOverride = mat;
                    break;
                }
            }
        }

        LayRoomFloor(root);
    }

    /// <summary>A wood floor exactly under the outer walls, just above the imported slab.</summary>
    private static void LayRoomFloor(Node root)
    {
        if (root.GetNodeOrNull("RoomFloor") != null)
            return;

        Vector3 min = new(float.PositiveInfinity, 0f, float.PositiveInfinity);
        Vector3 max = new(float.NegativeInfinity, 0f, float.NegativeInfinity);
        bool any = false;
        foreach (Node child in root.GetChildren())
        {
            if (child is not MeshInstance3D mi || mi.Mesh == null || !mi.Name.ToString().StartsWith("Wall_", StringComparison.Ordinal))
                continue;
            Aabb box = mi.Transform * mi.GetAabb();
            min = min.Min(box.Position);
            max = max.Max(box.End);
            any = true;
        }
        if (!any)
        {
            GD.PushWarning("InteriorStyle: no Wall_* meshes found; home has no room floor.");
            return;
        }

        var size = new Vector2(max.X - min.X, max.Z - min.Z);
        ((Node3D)root).AddChild(new MeshInstance3D
        {
            Name = "RoomFloor",
            Mesh = new PlaneMesh { Size = size },
            MaterialOverride = Mat(new Color(0xa0703fFF), 0.55f),
            Position = new Vector3((min.X + max.X) * 0.5f, 0.005f, (min.Z + max.Z) * 0.5f),
            CastShadow = GeometryInstance3D.ShadowCastingSetting.Off,
        });
    }
}
