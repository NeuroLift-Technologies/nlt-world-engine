using Godot;
using System;
using System.Collections.Generic;

namespace NltWorldEngine;

/// <summary>
/// Dresses the imported interiors so an observer can read the room at a glance.
///
/// The UE export flattened every object to one material per level (<c>MI_Wall_Light</c> in the
/// home, <c>MI_Carpet</c> in the office, café and classroom), so sofas, desks, fridges and walls all
/// rendered the same flat colour. Objects keep their imported names (<c>Sofa_Base</c>,
/// <c>WF_Monitor_3</c>, <c>Cafe_Table_2</c>, <c>Bookshelf_400</c>…), so materials are assigned by name
/// prefix at load time — the scene files and FBX stay untouched, and
/// <see cref="InteriorPhysicalBoundary"/>'s collision is unaffected.
///
/// Each building gets one of a few colour schemes, chosen from the scene id's number
/// (<c>workplace_7</c> → scheme 7), so stepping into a different building of the same kind looks like
/// a different place while the layout stays the one the agents know.
/// </summary>
public static class InteriorStyle
{
    /// <summary>Meshes in this group are scenery around the room and are left out of camera framing.</summary>
    public const string FrameSkipGroup = "interior_frame_skip";

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

    private static Color C(uint rgb) => new((rgb << 8) | 0xFF);

    // Shared palette.
    private static StandardMaterial3D Walnut => Mat(C(0x6b4a32), 0.6f);
    private static StandardMaterial3D Oak => Mat(C(0xb08a5a), 0.65f);
    private static StandardMaterial3D Laminate => Mat(C(0xe8e6e1), 0.5f);
    private static StandardMaterial3D Stone => Mat(C(0x3d3d40), 0.35f);
    private static StandardMaterial3D Steel => Mat(C(0xc9ccd1), 0.35f, 0.6f);
    private static StandardMaterial3D Black => Mat(C(0x1d1f22), 0.4f);
    private static StandardMaterial3D Charcoal => Mat(C(0x2b2d31), 0.6f);
    private static StandardMaterial3D Porcelain => Mat(C(0xf4f4f2), 0.15f);
    private static StandardMaterial3D Brass => Mat(C(0xb08d57), 0.35f, 0.8f);
    private static StandardMaterial3D WarmGlow => Mat(C(0xf3e6c8), 0.6f, 0f, C(0xffd9a0), 1.2f);
    private static StandardMaterial3D Screen => Mat(C(0x15171a), 0.15f, 0f, C(0x2a4a75), 0.9f);
    private static StandardMaterial3D Whiteboard => Mat(C(0xf8f8f6), 0.1f);
    private static StandardMaterial3D Glass => Mat(C(0x9fc4d8), 0.05f, 0.2f);
    private static StandardMaterial3D Terracotta => Mat(C(0xb8643f), 0.85f);
    private static StandardMaterial3D Foliage => Mat(C(0x4f7a3a), 0.9f);
    private static StandardMaterial3D Lawn => Mat(C(0x6d8a4a), 0.95f);
    private static StandardMaterial3D Paving => Mat(C(0xa8a39a), 0.95f);

    /// <summary>Dress <paramref name="levelRoot"/> for <paramref name="sceneId"/>. Safe to call again with another id.</summary>
    public static void Apply(Node levelRoot, string sceneId)
    {
        int n = SchemeNumber(sceneId);
        if (Has(sceneId, "personal"))
            Dress(levelRoot, HomeRules(n), slab: Lawn, grounds: null, roomFloor: Mat(C(0xa0703f), 0.55f));
        else if (Has(sceneId, "workplace"))
            Dress(levelRoot, OfficeRules(n), slab: null, grounds: Paving, roomFloor: null);
        else if (Has(sceneId, "social"))
            Dress(levelRoot, CafeRules(n), slab: Paving, grounds: null, roomFloor: null);
        else if (Has(sceneId, "academic"))
            Dress(levelRoot, SchoolRules(n), slab: null, grounds: Lawn, roomFloor: null);
    }

    private static bool Has(string sceneId, string prefix) => sceneId.StartsWith(prefix, StringComparison.OrdinalIgnoreCase);

    /// <summary>The number after the last underscore (<c>personal_3</c> → 3), or 1 when there is none.</summary>
    private static int SchemeNumber(string sceneId)
    {
        int us = sceneId.LastIndexOf('_');
        return us >= 0 && int.TryParse(sceneId.AsSpan(us + 1), out int n) ? Math.Max(n, 1) : 1;
    }

    private static T Pick<T>(T[] options, int n) => options[(n - 1) % options.Length];

    // --- Per-level rules. First match wins: a longer name must precede its prefix. ---------------

    private static (string, Material)[] HomeRules(int n)
    {
        var walls = Mat(Pick(new[] { C(0xefe6d6), C(0xe4ece6), C(0xf1e3dc), C(0xe6e9f0) }, n), 0.9f);
        var sofa = Mat(Pick(new[] { C(0x3f7f8c), C(0x8c5a3c), C(0x5b6b8c), C(0x7a8c5b) }, n), 0.9f);
        var blanket = Mat(Pick(new[] { C(0x5b7fa6), C(0xc98b6b), C(0x8a6aa6), C(0x6aa68a) }, n), 0.95f);
        var livingRug = Mat(Pick(new[] { C(0xb5523b), C(0x4f6d7a), C(0xc9a24f), C(0x8c4f6d) }, n), 0.95f);
        var bedroomRug = Mat(Pick(new[] { C(0x6a5a9c), C(0x7a8c5b), C(0x4f7a8c), C(0xb5733b) }, n), 0.95f);
        return new (string, Material)[]
        {
            ("Wall_", walls), ("Corridor_Wall", walls), ("MidWall", walls), ("BathBathDiv", walls),
            ("Front_Door", Walnut),
            ("Hall_Rug", Mat(C(0x8a6d4f), 0.95f)), ("Living_Rug", livingRug), ("Bedroom_Rug", bedroomRug),
            ("Coatrack", Brass),
            ("Sofa_", sofa), ("Coffee_", Walnut), ("TV_Stand", Walnut),
            ("TV", Mat(C(0x15171a), 0.15f, 0f, C(0x1e2a3c), 0.6f)),
            ("Lamp_Pole", Brass), ("Lamp_Shade", WarmGlow),
            ("Kit_Counter_Top", Stone), ("Kit_Stove_Top", Black),
            ("Kit_Counter", Laminate), ("Kit_Cabinet", Laminate),
            ("Kit_Fridge", Steel), ("Kit_Stove", Steel),
            ("Kit_Island", Oak), ("Island_Leg", Black),
            ("Stool_Seat", Oak), ("Stool_Pole", Black),
            ("Dining_Chair", Walnut), ("Dining_", Oak),
            ("Bed_Headboard", Mat(C(0x7a6a5a), 0.9f)), ("Bed_Mattress", Mat(C(0xf2efe8), 0.9f)),
            ("Bed_Blanket", blanket), ("Bed_Frame", Walnut),
            ("Pillow", Mat(C(0xfafafa), 0.95f)),
            ("Nightstand", Walnut), ("Night_Lamp", WarmGlow),
            ("Wardrobe", Oak), ("Dresser", Oak),
            ("Toilet", Porcelain), ("Bath_Sink", Porcelain), ("Bath_Tub", Porcelain),
            ("Bath_Mirror", Mat(C(0xd8e2e8), 0.05f, 1f)),
            ("Office_Monitor", Screen), ("Office_Chair", Black), ("Office_Leg", Black), ("Office_Desk", Oak),
            ("Washer_Door", Glass), ("Washing_Machine", Laminate),
        };
    }

    private static (string, Material)[] OfficeRules(int n)
    {
        var walls = Mat(Pick(new[] { C(0xe9edf0), C(0xeef0ea), C(0xf0ece6) }, n), 0.9f);
        var carpet = Mat(Pick(new[] { C(0x5d6670), C(0x4f5f6b), C(0x6b6257) }, n), 0.95f);
        var accent = Mat(Pick(new[] { C(0x2f6f9f), C(0x3f8f6f), C(0xc0603a) }, n), 0.8f);
        return new (string, Material)[]
        {
            ("WF_Floor", carpet), ("WF_Wall_", walls),
            ("WF_DeskTop", Laminate), ("WF_DeskLeg", Black),
            ("WF_Monitor", Screen), ("WF_Keyboard", Charcoal), ("WF_CPU", Charcoal),
            ("WF_Docs", Mat(C(0xf5f5f0), 0.9f)),
            ("WF_ChairSeat", accent), ("WF_ChairBack", accent),
            ("WF_ConfTable", Walnut), ("WF_ConfLeg", Black),
            ("WF_ConfChairSeat", Charcoal), ("WF_ConfChairBack", Charcoal),
            ("WF_Partition", Mat(C(0x7a8a96), 0.95f)),
            ("WF_Whiteboard", Whiteboard),
            ("WF_Door", Mat(C(0x3a3f45), 0.5f)), ("WF_GlassW", Glass), ("WF_EntryMat", Charcoal),
            ("WF_Sofa", accent),
        };
    }

    private static (string, Material)[] CafeRules(int n)
    {
        var walls = Mat(Pick(new[] { C(0xf3e2c7), C(0xe9d5c0), C(0xdfe8e1) }, n), 0.9f);
        var floor = Mat(Pick(new[] { C(0xc08a55), C(0x9c6b43), C(0xb5734a) }, n), 0.6f);
        var chairs = Mat(Pick(new[] { C(0xc0392b), C(0x2f6f6f), C(0xd68a1f) }, n), 0.7f);
        var sofa = Mat(Pick(new[] { C(0x7a3b3b), C(0x3b4f7a), C(0x5b6b3b) }, n), 0.9f);
        return new (string, Material)[]
        {
            ("Social_Floor", floor), ("Social_Wall_", walls),
            ("Cafe_Table", Mat(C(0xf0ede8), 0.2f)), ("Cafe_Chair", chairs),
            ("Cafe_Counter_Top", Stone), ("Cafe_Counter", Walnut),
            ("Cafe_ServiceKiosk", Steel),
            ("Cafe_SofaBack", sofa), ("Cafe_Sofa", sofa), ("Cafe_CoffeeTable", Walnut),
        };
    }

    private static (string, Material)[] SchoolRules(int n)
    {
        var walls = Mat(Pick(new[] { C(0xf4efe3), C(0xe7efe9), C(0xefe8f2) }, n), 0.9f);
        var floor = Mat(Pick(new[] { C(0xc9a46c), C(0x9fb0b8), C(0xa7b89a) }, n), 0.6f);
        var chairs = Mat(Pick(new[] { C(0x2f6f9f), C(0xc0603a), C(0x3f8f6f) }, n), 0.7f);
        return new (string, Material)[]
        {
            ("Academic_Floor", floor), ("Academic_Wall_", walls),
            ("Whiteboard", Whiteboard), ("BulletinBoard", Mat(C(0xb98f5e), 0.95f)),
            ("Teacher_Desk", Walnut), ("Teacher_Chair", Black),
            ("DeskChair_", chairs), ("Desk_", Oak),
            ("BookshelfShelf_", Mat(C(0xa0463c), 0.85f)), ("Bookshelf_", Walnut),
            ("StudyTable_", Oak), ("StudyChair_", chairs),
            ("Academic_FrontDoor", Walnut), ("Academic_EntryMat", Charcoal),
            ("Academic_Clock", Mat(C(0xf5f1e6), 0.5f)),
        };
    }

    // --- Shared dressing pass ----------------------------------------------------------------------

    /// <param name="slab">Material for an imported 80 m <c>Floor</c> slab around the room, if the level has one.</param>
    /// <param name="grounds">Material for a ground plane to add around a level that has no slab.</param>
    /// <param name="roomFloor">Material for a floor laid under the outer walls, for a level with no room floor.</param>
    private static void Dress(Node root, (string Prefix, Material Mat)[] rules, Material? slab, Material? grounds, Material? roomFloor)
    {
        foreach (Node child in root.GetChildren())
        {
            if (child is not MeshInstance3D mi)
                continue;
            string name = mi.Name.ToString();
            if (name.StartsWith("UCX_", StringComparison.Ordinal))
                continue;

            // No level has a ceiling mesh, so from the overhead camera the ceiling fixtures float as
            // slabs at ~3.3 m; the rooms are lit by WorldView's interior lights. The UE placeholder
            // character meshes are statues that read as extra people.
            if (name.Contains("CeilingLight", StringComparison.Ordinal) || name.StartsWith("Ceiling_Light", StringComparison.Ordinal)
                || name.StartsWith("SimBody_Character", StringComparison.Ordinal) || name == "AvatarCharacter")
            {
                mi.Visible = false;
                continue;
            }

            if (name == "Floor")
            {
                // An 80 m slab, far larger than the room: keep it as the grounds outside, out of the
                // camera framing.
                if (slab != null)
                    mi.MaterialOverride = slab;
                mi.AddToGroup(FrameSkipGroup);
                continue;
            }

            // Every level names its plants *Plant* (Plant_Pot2, WF_Plant3, Cafe_Plant_1_Foliage…);
            // pots are terracotta, everything else is foliage (WF_Plant is one combined mesh).
            if (name.Contains("Plant", StringComparison.Ordinal))
            {
                mi.MaterialOverride = name.Contains("Pot", StringComparison.Ordinal) ? Terracotta : Foliage;
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

        if (roomFloor != null)
            LayRoomFloor(root, roomFloor);
        if (grounds != null)
            LayGrounds(root, grounds);
    }

    /// <summary>A floor exactly under the outer walls, just above the imported slab.</summary>
    private static void LayRoomFloor(Node root, Material mat)
    {
        if (root.GetNodeOrNull("RoomFloor") is MeshInstance3D existing)
        {
            existing.MaterialOverride = mat;
            return;
        }
        if (!TryWallBounds(root, out Vector3 min, out Vector3 max))
        {
            GD.PushWarning($"InteriorStyle: no Wall_* meshes in {root.Name}; no room floor laid.");
            return;
        }
        ((Node3D)root).AddChild(new MeshInstance3D
        {
            Name = "RoomFloor",
            Mesh = new PlaneMesh { Size = new Vector2(max.X - min.X, max.Z - min.Z) },
            MaterialOverride = mat,
            Position = new Vector3((min.X + max.X) * 0.5f, 0.005f, (min.Z + max.Z) * 0.5f),
            CastShadow = GeometryInstance3D.ShadowCastingSetting.Off,
        });
    }

    /// <summary>Paving or lawn around a level that floats in the void, kept out of camera framing.</summary>
    private static void LayGrounds(Node root, Material mat)
    {
        if (root.GetNodeOrNull("Grounds") is MeshInstance3D existing)
        {
            existing.MaterialOverride = mat;
            return;
        }
        var centre = TryWallBounds(root, out Vector3 min, out Vector3 max) ? (min + max) * 0.5f : Vector3.Zero;
        var grounds = new MeshInstance3D
        {
            Name = "Grounds",
            Mesh = new PlaneMesh { Size = new Vector2(80f, 80f) },
            MaterialOverride = mat,
            Position = new Vector3(centre.X, -0.02f, centre.Z),
            CastShadow = GeometryInstance3D.ShadowCastingSetting.Off,
        };
        ((Node3D)root).AddChild(grounds);
        grounds.AddToGroup(FrameSkipGroup);
    }

    /// <summary>XZ bounds of the outer walls (any mesh whose name contains <c>Wall_</c>).</summary>
    private static bool TryWallBounds(Node root, out Vector3 min, out Vector3 max)
    {
        min = new Vector3(float.PositiveInfinity, 0f, float.PositiveInfinity);
        max = new Vector3(float.NegativeInfinity, 0f, float.NegativeInfinity);
        bool any = false;
        foreach (Node child in root.GetChildren())
        {
            if (child is not MeshInstance3D mi || mi.Mesh == null)
                continue;
            string name = mi.Name.ToString();
            if (name.StartsWith("UCX_", StringComparison.Ordinal) || !name.Contains("Wall_", StringComparison.Ordinal)
                || name.Contains("Corridor", StringComparison.Ordinal) || name.Contains("MidWall", StringComparison.Ordinal))
                continue;
            Aabb box = mi.Transform * mi.GetAabb();
            min = min.Min(box.Position);
            max = max.Max(box.End);
            any = true;
        }
        return any;
    }
}
