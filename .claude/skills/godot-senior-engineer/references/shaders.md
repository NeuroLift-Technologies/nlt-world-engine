# Shaders (Godot Shading Language, visual shaders, compute)

## Basics
- The language is GLSL-like. Start every shader with `shader_type spatial;`, `canvas_item;`, `particles;`, `sky;` or `fog;`.
- Entry points are `vertex()`, `fragment()` and `light()`, plus `start()`/`process()` for particles. You write to built-ins (`ALBEDO`, `ROUGHNESS`, `NORMAL_MAP`, `EMISSION`, `ALPHA`, `COLOR`, `VERTEX`, …) instead of declaring outputs.
- `render_mode` sets blend, cull, depth, shading and so on: for example `render_mode unshaded, cull_disabled, blend_add;`.
- Uniforms: use `uniform` plus hints (`source_color`, `hint_range(0,1)`, `filter_nearest`, `repeat_enable`, `hint_normal`, `hint_screen_texture`, `hint_depth_texture`). Set them from code with `material.set_shader_parameter("name", v)`.
- `global uniform`: project-wide values you set via `RenderingServer.global_shader_parameter_set`. `instance uniform`: per-instance values without duplicating the material.
- Screen-reading effects: declare `uniform sampler2D screen_tex : hint_screen_texture, filter_linear_mipmap;`. `SCREEN_TEXTURE` is gone in Godot 4. Same for depth: `hint_depth_texture`, then linearize with the inverse projection matrix.
- Godot 3 → 4 traps:
  - `hint_color` became `source_color`.
  - `WORLD_MATRIX` became `MODEL_MATRIX`.
  - `CAMERA_MATRIX` became `INV_VIEW_MATRIX`.
  - `TIME` is unchanged, but the screen and depth textures are now uniforms.
- Includes: `#include "res://shaders/common.gdshaderinc"`. Godot also has a preprocessor (`#define`, `#ifdef`).

## Performance
- Every unique shader and render-mode combination is a pipeline. Ubershaders (4.4+) hide the compile stutter. The shader baker (4.5+, an export option) precompiles shaders for faster startup, which matters most on Apple and D3D12.
- Avoid branching on per-pixel data in heavy shaders. Prefer `mix`/`step`.
- Avoid screen and depth reads in many overlapping materials. Each one forces a copy.
- On the Compatibility renderer, some built-ins and features are missing. Test on the target renderer.

## Visual shaders and other uses
- `VisualShader` is the node-based shader editor, good for artists. It's fine to convert to text later. Since 4.7, text shaders also have inline preview.
- Post-processing:
  - A full-screen quad with a spatial shader (`render_mode unshaded`, `POSITION = vec4(VERTEX.xy, 1.0, 1.0)`), or a `ColorRect` on a `CanvasLayer` with a canvas_item shader.
  - Or a `CompositorEffect` (Forward+/Mobile), which hooks into the render pipeline.
- Compute shaders: GLSL files (`#[compute]`) run through `RenderingDevice`, either a local device or the main one. They're for GPU simulation and data processing. Not available on Compatibility.
- Particles: `GPUParticles3D/2D` with `ParticleProcessMaterial`, or a custom `shader_type particles`. Use `CPUParticles` on Compatibility and very weak GPUs.
