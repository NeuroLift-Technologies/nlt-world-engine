using Godot;

namespace NltWorldEngine;

public static class TerrainBuilder
{
    /// <summary>
    /// Grid cells per side of the terrain mesh, and so of the trimesh body built from it
    /// (<see cref="TerrainBuilderPhysics.TerrainBody"/>). <see cref="SurfaceHeightAt"/> assumes it.
    /// </summary>
    public const int Segments = 208;

    /// <summary>
    /// Height of the terrain mesh's surface at (x, z): what an avatar on the terrain body stands on.
    /// <see cref="WorldGeometry.HeightAt"/> is the smooth field <see cref="Build"/> samples at grid
    /// vertices; between them the mesh is flat triangles, centimetres off the field. Anything laid
    /// on the ground (the settlement's paving) follows this surface, or the terrain shows through it.
    /// </summary>
    public static float SurfaceHeightAt(float x, float z)
    {
        // The same float arithmetic as Build's Vertex, so grid points land on identical heights.
        const float size = WorldConstants.World;
        float step = size / Segments;
        float gx = (x + size / 2f) / step, gz = (z + size / 2f) / step;
        if (gx < 0f || gz < 0f || gx >= Segments || gz >= Segments)
            return WorldGeometry.HeightAt(x, z);

        int i = (int)gx, j = (int)gz;
        float fx = gx - i, fz = gz - j;
        float H(int ci, int cj) => WorldGeometry.HeightAt(-size / 2f + ci * step, -size / 2f + cj * step);
        float a = H(i, j), b = H(i + 1, j), c = H(i + 1, j + 1), d = H(i, j + 1);
        // Build splits each cell along its a-c diagonal into triangles (a, b, c) and (a, c, d).
        return fx >= fz
            ? a + (b - a) * fx + (c - b) * fz
            : a + (d - a) * fz + (c - d) * fx;
    }

    public static MeshInstance3D Build(int seg = Segments)
    {
        var st = new SurfaceTool();
        st.Begin(Mesh.PrimitiveType.Triangles);

        const float size = WorldConstants.World;
        float step = size / seg;
        Vector3 Vertex(int i, int j)
        {
            float x = -size / 2f + i * step;
            float z = -size / 2f + j * step;
            return new Vector3(x, WorldGeometry.HeightAt(x, z), z);
        }

        Color ColorAt(float x, float z, float h)
        {
            float slope = WorldGeometry.SlopeAt(x, z);
            float grain = SimulationRng.Fbm(x * 0.06f, z * 0.06f, 3, WorldConstants.Seed + 991);

            // NOTE: Godot C#'s Color(uint) reads the value as 0xRRGGBBAA, so every literal
            // carries an explicit FF alpha byte — without it R is 0x00 and the world turns blue/green.
            Color sand = new(0xc9b48cFF), grass = new(0x5c7444FF), grass2 = new(0x48603aFF),
                  rock = new(0x7b7468FF), dark = new(0x4c4740FF);

            Color c;
            if (h < WorldConstants.Water - 2.6f) c = dark;
            else if (h < WorldConstants.Water + 1.5f) c = sand;
            else
            {
                c = grass.Lerp(grass2, grain);
                c = c.Lerp(rock, Mathx.Smoothstep(0.28f, 0.72f, slope));
                c = c.Lerp(sand, Mathx.Smoothstep(2.4f, 0.9f, h) * 0.25f);
                c *= 0.86f + grain * 0.30f;
            }
            float shade = 0.94f + SimulationRng.Fbm(x * 0.012f, z * 0.012f, 2, WorldConstants.Seed + 77) * 0.14f;
            return c * shade;
        }

        for (int j = 0; j < seg; j++)
        for (int i = 0; i < seg; i++)
        {
            Vector3 a = Vertex(i, j), b = Vertex(i + 1, j), c = Vertex(i + 1, j + 1), d = Vertex(i, j + 1);
            // two triangles: a, c, d  /  a, b, c. Godot's front face is clockwise as seen by the
            // camera; seen from above (+X right, +Z toward the screen bottom) these run clockwise, so
            // the faces point up. The earlier a, d, c / a, c, b order ran counter-clockwise: every
            // terrain face pointed down and was back-face culled, so from the observer's camera the
            // ground was invisible and the water plane below it showed through as "ground".
            AddTri(st, a, c, d);
            AddTri(st, a, b, c);
        }

        void AddTri(SurfaceTool s, Vector3 p0, Vector3 p1, Vector3 p2)
        {
            s.SetColor(ColorAt(p0.X, p0.Z, p0.Y)); s.AddVertex(p0);
            s.SetColor(ColorAt(p1.X, p1.Z, p1.Y)); s.AddVertex(p1);
            s.SetColor(ColorAt(p2.X, p2.Z, p2.Y)); s.AddVertex(p2);
        }

        st.GenerateNormals();
        // No UVs on this mesh — tangents not needed (vertex colour only).
        var mat = new StandardMaterial3D
        {
            VertexColorUseAsAlbedo = true,
            // ColorAt's palette is authored as sRGB hex. Without this flag Godot reads vertex
            // colours as linear, which lifts and greys them: grass rendered a pale blue-grey that
            // matched the water's fog colour, and observers could not tell land from lake.
            VertexColorIsSrgb = true,
            Roughness = 0.97f,
            Metallic = 0f,
        };
        st.SetMaterial(mat);

        return new MeshInstance3D { Mesh = st.Commit(), CastShadow = GeometryInstance3D.ShadowCastingSetting.Off };
    }
}
