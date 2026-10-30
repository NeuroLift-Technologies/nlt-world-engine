# 3D, rendering, lighting, materials

## Renderers (pick deliberately, and early)
| Renderer | Backend | Use when |
|---|---|---|
| Forward+ | Vulkan / D3D12 (default on new Windows projects since 4.6) / Metal | Desktop, full features: SDFGI, VoxelGI, volumetric fog, many lights |
| Mobile | Vulkan / Metal | Mobile, XR, mid-range GPUs |
| Compatibility | OpenGL 3.3 / GLES3 / WebGL 2 | Old or weak GPUs, web, the widest reach |

Features differ between renderers. Check the docs' "Rendering features by renderer" table for the project's version before recommending something like SDFGI or volumetric fog. You can override the driver at the command line (`--rendering-driver opengl3|vulkan|d3d12|metal`) or per platform in Project Settings.

## Lighting and GI
- Lights: `DirectionalLight3D`, `OmniLight3D` and `SpotLight3D`, plus `AreaLight3D` (4.7+) for rectangular light such as windows, screens and panels.
- Shadows are usually the biggest GPU cost. Tune the directional shadow distance and splits, the shadow atlas size, and how many lights cast shadows.
- Global illumination options, from cheapest to most dynamic:
  1. **LightmapGI**: baked, best quality per cost, static geometry only. Needs UV2 (generate it on import).
  2. **VoxelGI**: baked probes that allow dynamic objects. Forward+ only.
  3. **SDFGI**: fully real-time and large scale. Forward+ only and costly.
  4. **ReflectionProbe** for local reflections. Since 4.6 probes use octahedral maps.
- `WorldEnvironment` + `Environment` covers sky, ambient, tonemap (Filmic, ACES, AgX), glow, SSAO, SSIL, SSR, fog, volumetric fog and adjustments. Use `CameraAttributes` for exposure and DOF.
- HDR output (4.7+) is opt-in. It needs an HDR display, OS support, and on Linux, Wayland.

## Materials
- Use `StandardMaterial3D` (or `ORMMaterial3D` for packed occlusion/roughness/metallic) until you actually need a shader.
- Share material resources between meshes so they batch, and don't create materials per instance at runtime. For per-instance variation, use instance uniforms (`instance uniform` in shaders) or `MultiMesh` custom data.
- Transparency is expensive and sorts per object. Prefer alpha scissor or alpha hash for foliage. Use `depth_draw_mode` deliberately.
- Stencil (4.5+): outlines, x-ray and portal effects through `StandardMaterial3D` stencil modes or shader `stencil_mode`.

## Meshes and import
- Use glTF 2.0 (`.glb`/`.gltf`) as the interchange format. Godot can also import `.blend` directly if Blender is configured, and FBX through ufbx.
- Import settings carry real decisions: generated LODs (on by default), shadow meshes, light baking mode / UV2, root type, and per-node physics. Advanced Import Settings lets you set collision shapes per mesh, extract materials and adjust animations.
- Import hints: name suffixes like `-col`, `-convcolonly` and `-navmesh` tell the importer to build collision and navigation from those meshes.
- Use simple collision shapes for dynamic bodies. Trimesh (concave) shapes are only for static geometry. Since 4.6 you can generate `CollisionShape3D` from primitive meshes in the Mesh menu.

## Large worlds and many objects
- `MultiMeshInstance3D` for foliage and crowds of identical meshes.
- Automatic mesh LOD plus `visibility_range_begin/end` (HLOD) per node.
- `OccluderInstance3D` for occlusion culling (enable it in Project Settings first).
- Precision: past roughly 8 km from the origin, float32 jitter appears. Either rebase the world origin or build Godot with `precision=double` (needs a custom build).
- `GridMap` + `MeshLibrary` for modular level kits.
