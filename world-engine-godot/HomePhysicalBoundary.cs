using Godot;
using System;

namespace NltWorldEngine;

/// <summary>
/// Converts the imported home's UCX collision meshes into static collision shapes, including the
/// floor, the internal partitions and furniture. Godot hides UCX meshes in the room view, so
/// collision is generated from their source meshes and transforms while the south doorway remains
/// open.
///
/// The floor comes from <c>UCX_Floor</c> like everything else. It was previously a hand-placed
/// 24 × 18 m box centred at z = −5.4 — the 80 m floor slab's centre, not the room's — which left
/// the north third of the room (sofa at z 5.9, kitchen at z 7.55) without floor collision.
/// </summary>
public sealed partial class HomePhysicalBoundary : StaticBody3D
{
    private const uint WorldLayer = 1;

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
                || nodeName.Contains("Front_Door", StringComparison.Ordinal)
                || nodeName.Contains("Rug", StringComparison.Ordinal)
                || nodeName.Contains("Ceiling_Light", StringComparison.Ordinal)
                || nodeName.Contains("Lamp_", StringComparison.Ordinal)
                || nodeName.Contains("Plant_Foliage", StringComparison.Ordinal)
                || meshNode.Mesh == null)
                continue;

            // UCX meshes are scaled/unit-box authoring proxies in this FBX. Bake their full
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

            var collisionShape = new CollisionShape3D
            {
                Name = $"{meshNode.Name}_Collision",
                Shape = collision
            };
            AddChild(collisionShape);
            meshNode.Visible = false;
            collisionCount++;
        }

        if (collisionCount == 0)
            GD.PushWarning("HomePhysicalBoundary: no UCX_* collision meshes found; home has no generated physics collision.");
        else
            GD.Print($"HomePhysicalBoundary: generated collision from {collisionCount} home UCX meshes.");
    }
}
