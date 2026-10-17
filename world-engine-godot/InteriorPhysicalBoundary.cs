using Godot;
using System;

namespace NltWorldEngine;

/// <summary>
/// Converts an imported interior's UCX collision meshes into static collision shapes: floor,
/// walls, partitions and furniture. All four UE-exported levels (personal, workplace, social,
/// academic) ship a <c>UCX_*</c> proxy for nearly every object; Godot hides them in the room view
/// (<c>WorldView.StripInteriorClutter</c>), so collision is generated from their source meshes and
/// transforms. Attach one as a child of a level root.
///
/// The floor comes from the level's own <c>UCX_*Floor</c> proxy. An earlier hand-placed box was
/// centred on the personal level's 80 m slab, not its room, and missed the north third of it.
///
/// Skipped: doors and entry mats (the doorway stays open), rugs and mats (flat, nothing to collide
/// with), ceiling fixtures (out of reach, and hidden by <c>InteriorStyle</c>), foliage, the sky
/// sphere, and the UE placeholder character meshes.
/// </summary>
public sealed partial class InteriorPhysicalBoundary : StaticBody3D
{
    private const uint WorldLayer = 1;

    private static readonly string[] Skip =
    {
        "Door", "Rug", "EntryMat", "Ceiling_Light", "CeilingLight", "Lamp_", "Foliage",
        "SkySphere", "Character", "Keyboard", "Docs",
    };

    public override void _Ready()
    {
        CollisionLayer = WorldLayer;
        CollisionMask = 0;

        int collisionCount = 0;
        foreach (Node child in GetParent().GetChildren())
        {
            string nodeName = child.Name.ToString();
            if (child is not MeshInstance3D meshNode
                || !nodeName.StartsWith("UCX_", StringComparison.Ordinal)
                || meshNode.Mesh == null
                || Array.Exists(Skip, s => nodeName.Contains(s, StringComparison.Ordinal)))
                continue;

            // UCX meshes are scaled/unit-box authoring proxies in these FBX files. Bake their full
            // node transform into the generated trimesh; a direct shape assignment loses scale.
            Transform3D sourceTransform = meshNode.Transform;
            ConcavePolygonShape3D collision = meshNode.Mesh.CreateTrimeshShape();
            if (collision == null)
                continue;

            Transform3D bodyTransform = Transform.Inverse() * sourceTransform;
            Vector3[] transformedFaces = collision.GetFaces();
            for (int face = 0; face < transformedFaces.Length; face++)
                transformedFaces[face] = bodyTransform * transformedFaces[face];
            collision.SetFaces(transformedFaces);

            AddChild(new CollisionShape3D { Name = $"{meshNode.Name}_Collision", Shape = collision });
            meshNode.Visible = false;
            collisionCount++;
        }

        string level = GetParent().Name.ToString();
        if (collisionCount == 0)
            GD.PushWarning($"InteriorPhysicalBoundary: no UCX_* collision meshes in {level}; it has no generated collision.");
        else
            GD.Print($"InteriorPhysicalBoundary: generated collision from {collisionCount} UCX meshes in {level}.");
    }
}
