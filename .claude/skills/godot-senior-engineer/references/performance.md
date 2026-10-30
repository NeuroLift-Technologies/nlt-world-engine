# Performance and low-spec hardware

## Measure first
- Debugger → Profiler (script time per function), Visual Profiler (CPU/GPU per render pass), Monitors (FPS, draw calls, objects, physics, memory). Ask what the monitors say before prescribing fixes.
- Distinguish CPU-bound (script/physics/draw-call submission) from GPU-bound (fill rate, shaders, shadows). The fix is completely different.
- Profile release/exported builds for final numbers; the editor adds overhead.

## Renderer choice
- **Forward+**: full feature set, needs a Vulkan/D3D12/Metal-capable GPU; heaviest.
- **Mobile**: Vulkan-based, cheaper, fewer features.
- **Compatibility**: OpenGL 3.3 / OpenGL ES 3.0 / WebGL 2. The only option for old or weak iGPUs and for the web. Fewer features (e.g. no SDFGI/volumetric fog; check the feature table for the version), but it runs where others don't.
- Very old Intel iGPUs (pre-Skylake HD Graphics) generally lack usable Vulkan drivers, especially on Linux — use Compatibility. Run `godot --rendering-driver opengl3` to test without changing project settings.

## CPU-side wins
- Fewer nodes doing per-frame work: disable `_process` (`set_process(false)`) on idle nodes; use timers/signals instead of polling.
- Draw calls: `MultiMeshInstance3D` for many identical meshes; merge static geometry; share materials (identical material resources batch better).
- Physics: tight collision layers/masks; simple shapes (box/capsule/sphere) over trimesh for moving bodies; consider lowering `physics/common/physics_ticks_per_second` with interpolation on; put sleeping RigidBodies to sleep.
- Large worlds: visibility ranges (HLOD), automatic mesh LOD, occlusion culling (`OccluderInstance3D`), chunk streaming via `ResourceLoader.load_threaded_request`.
- Thousands of entities: bypass nodes with `RenderingServer` / `PhysicsServer3D` directly.
- Navigation: bake navmeshes offline/at load, not every frame; throttle path requests.

## GPU-side wins
- Shadows are usually the biggest cost: fewer shadow-casting lights, lower shadow atlas size, shorter directional shadow distance.
- Lower 3D resolution scale (`rendering/scaling_3d/scale`) with FSR upscaling where supported.
- Avoid overdraw from large transparent surfaces and particles.
- Bake lighting (LightmapGI) instead of real-time GI on weak GPUs.

## Memory
- Compress textures (VRAM compression in import settings), sensible max sizes, mipmaps for 3D.
- Free scenes you're done with; watch for orphan nodes (Monitors → Object → Orphan Nodes) — leaked nodes not in the tree.
