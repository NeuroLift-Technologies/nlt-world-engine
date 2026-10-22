using Godot;
using System;
using System.Collections.Generic;

namespace NltWorldEngine;

public static class VegetationBuilder
{
    private sealed record Spot(float X, float Z, float Y, float Scale, float Rot, float Tint);
    public static readonly List<ShaderMaterial> WindMats = new();

    /// <summary>The trunk mesh every tree instances, before its per-tree scale.</summary>
    public const float TrunkHeight = 2.6f, TrunkTopRadius = 0.16f, TrunkBottomRadius = 0.30f;

    /// <summary>
    /// A tree trunk's collision cylinder in world space. <see cref="Centre"/> is the cylinder's
    /// middle: Godot's <see cref="CylinderShape3D"/> is centred on its node.
    /// </summary>
    public readonly record struct TrunkCollider(Vector3 Centre, float Radius, float Height);

    private static List<Spot> TreeSpots(List<SettlementBuilder.Plan> plans) => SeededPlacement(620, (x, z, r) =>
    {
        float h = WorldGeometry.HeightAt(x, z);
        return h > WorldConstants.Water + 1.6f && WorldGeometry.SlopeAt(x, z) < 0.42f && ClearOfSettlement(x, z, plans, 1.5f);
    });

    /// <summary>Where one tree's trunk mesh is drawn: its size, some height variation, and a turn about Y.</summary>
    private static Transform3D TrunkTransform(Spot t)
    {
        float sc = 0.72f + t.Scale * 0.85f;
        return new Transform3D(new Basis(Quaternion.FromEuler(new Vector3(0, t.Rot * Mathf.Pi * 2f, 0))).Scaled(new Vector3(sc, sc * (0.85f + t.Tint * 0.4f), sc)),
            new Vector3(t.X, t.Y - 0.2f + 1.3f * sc, t.Z));
    }

    /// <summary>
    /// Every tree's trunk as drawn, the collider built for it, and the terrain surface under it.
    /// For the harness; <see cref="Build"/> uses the same functions.
    /// </summary>
    public static List<(Transform3D Visual, TrunkCollider Body, float GroundY)> Trunks(List<SettlementBuilder.Plan> plans)
    {
        var trunks = new List<(Transform3D, TrunkCollider, float)>();
        foreach (var t in TreeSpots(plans))
        {
            var visual = TrunkTransform(t);
            float ground = TerrainBuilder.SurfaceHeightAt(t.X, t.Z);
            trunks.Add((visual, ColliderFor(visual, ground), ground));
        }
        return trunks;
    }

    /// <summary>
    /// The collision cylinder for one trunk. <paramref name="trunk"/> places the trunk mesh: a
    /// <see cref="TrunkHeight"/> cylinder tapering from <see cref="TrunkBottomRadius"/> at its base
    /// to <see cref="TrunkTopRadius"/>, centred on <c>trunk.Origin</c> and scaled by
    /// <c>trunk.Basis.Scale</c> (X and Z equal, Y varies per tree). <paramref name="groundY"/> is
    /// the terrain surface under the tree; the trunk's base can float up to ~0.1 m above it. Jolt
    /// does not take non-uniform scale on shapes, so the size is baked into the cylinder.
    /// </summary>
    private static TrunkCollider ColliderFor(Transform3D trunk, float groundY)
    {
        // Joshua, 2026-10-22: the base radius the whole way up, from the ground to the trunk's
        // visual top. Avatars never clip the bark; higher up, where the trunk tapers, they stop a
        // few centimetres short of it. Starting at the ground closes the gap under a floating base.
        var scale = trunk.Basis.Scale;
        float top = trunk.Origin.Y + TrunkHeight * 0.5f * scale.Y;
        float height = top - groundY;
        return new TrunkCollider(new Vector3(trunk.Origin.X, groundY + height * 0.5f, trunk.Origin.Z),
            TrunkBottomRadius * scale.X, height);
    }

    private static List<Spot> SeededPlacement(int count, Func<float, float, SimulationRng, bool> test)
    {
        var out_ = new List<Spot>();
        var r = new SimulationRng((uint)(WorldConstants.Seed + 4242));
        int guard = 0;
        while (out_.Count < count && guard++ < count * 60)
        {
            float a = r.Next() * Mathf.Pi * 2f;
            float rad = MathF.Sqrt(r.Next()) * (WorldConstants.World * 0.42f);
            float x = MathF.Cos(a) * rad, z = MathF.Sin(a) * rad;
            if (!test(x, z, r)) continue;
            bool ok = true;
            foreach (var o in out_)
                if ((o.X - x) * (o.X - x) + (o.Z - z) * (o.Z - z) < 16f) { ok = false; break; }
            if (ok) out_.Add(new Spot(x, z, WorldGeometry.HeightAt(x, z), r.Next(), r.Next(), r.Next()));
        }
        return out_;
    }

    private static MultiMeshInstance3D Instanced(Mesh mesh, Material mat, List<Spot> spots, Func<Spot, Transform3D> makeT, bool customData = false)
    {
        var mm = new MultiMesh
        {
            TransformFormat = MultiMesh.TransformFormatEnum.Transform3D,
            UseCustomData = customData,   // must be set before InstanceCount
            Mesh = mesh,
            InstanceCount = spots.Count,
        };
        for (int i = 0; i < spots.Count; i++)
        {
            mm.SetInstanceTransform(i, makeT(spots[i]));
            if (customData)
            {
                float v = 0.82f + spots[i].Tint * 0.36f;
                var tint = new Color(v * (0.94f + spots[i].Scale * 0.12f), v, v * (0.94f + spots[i].Scale * 0.10f));
                mm.SetInstanceCustomData(i, tint);
            }
        }
        return new MultiMeshInstance3D { Multimesh = mm, MaterialOverride = mat };
    }

    private static ShaderMaterial WindMat(Color albedo, float sway)
    {
        var shader = new Shader
        {
            Code = @"
shader_type spatial;
uniform vec3 u_albedo : source_color;
uniform float u_sway;
uniform float u_time;
varying vec3 v_tint;
void vertex() {
    vec3 ip = MODEL_MATRIX[3].xyz;
    float ph = ip.x * 0.35 + ip.z * 0.41;
    float w = sin(u_time * 1.6 + ph) + 0.6 * sin(u_time * 2.7 + ph * 1.7);
    float h = clamp(VERTEX.y, 0.0, 4.0) / 4.0;
    VERTEX += vec3(w, 0.0, w * 0.6) * u_sway * h;
    v_tint = INSTANCE_CUSTOM.rgb;
}
void fragment() {
    ALBEDO = u_albedo * v_tint;
    ROUGHNESS = 1.0;
}
"
        };
        var m = new ShaderMaterial { Shader = shader };
        m.SetShaderParameter("u_albedo", albedo);
        m.SetShaderParameter("u_sway", sway);
        m.SetShaderParameter("u_time", 0f);
        WindMats.Add(m);
        return m;
    }

    private static bool ClearOfSettlement(float x, float z, List<SettlementBuilder.Plan> plans, float pad = 0f)
    {
        if (MathF.Sqrt((x - WorldConstants.SettleX) * (x - WorldConstants.SettleX) + (z - WorldConstants.SettleZ) * (z - WorldConstants.SettleZ)) < 15f + pad) return false;
        foreach (var b in plans)
            if (MathF.Sqrt((x - b.X) * (x - b.X) + (z - b.Z) * (z - b.Z)) < b.Rad + 3.5f + pad) return false;
        return true;
    }

    public static Node3D Build(List<SettlementBuilder.Plan> plans)
    {
        var root = new Node3D();

        // trees: one trunk + 3 canopy cones per spot, four MultiMesh layers
        var treeSpots = TreeSpots(plans);

        var trunkMesh = new CylinderMesh { Height = TrunkHeight, TopRadius = TrunkTopRadius, BottomRadius = TrunkBottomRadius, RadialSegments = 6 };
        root.AddChild(Instanced(trunkMesh, WindMat(new Color(0x5a4534FF), 0.03f), treeSpots, TrunkTransform, true));

        // Trunks stop avatars; canopies (above head height), rocks and grass do not. One static
        // body holds every trunk's cylinder, and Jolt compounds them. It sits under the open world,
        // so it leaves the physics space with the terrain while an interior shows.
        var trunkBody = new StaticBody3D { Name = "Collision_Trees" };
        foreach (var t in treeSpots)
        {
            var c = ColliderFor(TrunkTransform(t), TerrainBuilder.SurfaceHeightAt(t.X, t.Z));
            trunkBody.AddChild(new CollisionShape3D { Shape = new CylinderShape3D { Radius = c.Radius, Height = c.Height }, Position = c.Centre });
        }
        root.AddChild(trunkBody);

        root.AddChild(Instanced(Cone(1.35f, 2.9f, 8), WindMat(new Color(0x3d5c36FF), 0.10f), treeSpots, t => T(t, 3.2f, 0.72f, 0.85f), true));
        root.AddChild(Instanced(Cone(1.05f, 2.4f, 8), WindMat(new Color(0x4a7038FF), 0.13f), treeSpots, t => T(t, 4.5f, 0.72f, 0.85f), true));
        root.AddChild(Instanced(Cone(0.68f, 1.8f, 8), WindMat(new Color(0x5c8440FF), 0.16f), treeSpots, t => T(t, 5.7f, 0.72f, 0.85f), true));

        // rocks
        var rockSpots = SeededPlacement(190, (x, z, r) =>
        {
            float h = WorldGeometry.HeightAt(x, z);
            return h > WorldConstants.Water + 0.6f && WorldGeometry.SlopeAt(x, z) > 0.16f && ClearOfSettlement(x, z, plans, 0.5f);
        });
        var rockMesh = new SphereMesh { Radius = 1f, RadialSegments = 6, Rings = 3 };
        var rockMat = new StandardMaterial3D { AlbedoColor = new Color(0x7d776cFF), Roughness = 0.98f, ShadingMode = BaseMaterial3D.ShadingModeEnum.PerVertex };
        root.AddChild(Instanced(rockMesh, rockMat, rockSpots, t =>
        {
            float sc = 0.5f + t.Scale * 1.5f;
            return new Transform3D(new Basis(Quaternion.FromEuler(new Vector3(t.Tint * 3f, t.Rot * 6f, t.Tint * 2f))).Scaled(new Vector3(sc, sc * (0.6f + t.Rot * 0.5f), sc * (0.8f + t.Tint * 0.4f))),
                new Vector3(t.X, t.Y - 0.25f, t.Z));
        }));

        // grass
        var grassSpots = SeededPlacement(3400, (x, z, r) =>
        {
            float h = WorldGeometry.HeightAt(x, z);
            float dPlaza = MathF.Sqrt((x - WorldConstants.SettleX) * (x - WorldConstants.SettleX) + (z - WorldConstants.SettleZ) * (z - WorldConstants.SettleZ));
            if (dPlaza < 14f && r.Next() < 0.85f) return false;
            return h > WorldConstants.Water + 0.9f && WorldGeometry.SlopeAt(x, z) < 0.45f;
        });
        var grassCone = Cone(0.075f, 0.62f, 3);
        root.AddChild(Instanced(grassCone, WindMat(new Color(0x7d9c4eFF), 0.22f), grassSpots, t =>
        {
            float sc = 0.7f + t.Scale * 0.9f;
            return new Transform3D(new Basis(Quaternion.FromEuler(new Vector3(0, t.Rot * Mathf.Pi * 2f, 0))).Scaled(new Vector3(sc, sc * (0.7f + t.Tint * 0.8f), sc)),
                new Vector3(t.X, t.Y - 0.05f, t.Z));
        }, true));

        return root;
    }

    private static Mesh Cone(float radius, float height, int sides)
        => new CylinderMesh { Height = height, TopRadius = 0f, BottomRadius = radius, RadialSegments = sides };

    private static Transform3D T(Spot t, float yOff, float baseScale, float tintScale)
    {
        float sc = baseScale + t.Scale * 0.85f;
        return new Transform3D(new Basis(Quaternion.FromEuler(new Vector3(0, t.Rot * Mathf.Pi * 2f, 0))).Scaled(new Vector3(sc, sc * (tintScale + t.Tint * 0.4f), sc)),
            new Vector3(t.X, t.Y - 0.2f + yOff, t.Z));
    }
}
