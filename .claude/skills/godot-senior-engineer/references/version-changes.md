# Godot 4.x version changes and how to stay current

Godot ships a feature release roughly every 4–6 months, and point releases in between. Your training data lags behind the engine, so treat this file as a starting map, not the final word. When an answer depends on version-specific behavior, check it (see "Verifying against the real engine" at the bottom).

As of late 2026, the current stable line is **4.7** (4.7.2, August 2026). 4.8 may be in development, so check before you claim anything about it.

## Highlights by release (what tends to matter in answers)

**4.3**
- `TileMapLayer` replaces the multi-layer `TileMap`, which is deprecated.
- `Parallax2D` replaces `ParallaxBackground`/`ParallaxLayer`.
- Single-threaded web export (no SharedArrayBuffer/COOP-COEP headers needed).
- Interactive music (`AudioStreamInteractive`, `AudioStreamSynchronized`, `AudioStreamPlaylist`).
- Physics interpolation for 2D (3D followed in 4.4).

**4.4**
- Jolt Physics is built in as an option for 3D.
- Physics interpolation for 3D.
- Typed dictionaries (`Dictionary[K, V]`).
- `.uid` files sit next to scripts and shaders. Commit them, and move files inside the editor so references survive.
- Ubershaders reduce pipeline-compilation stutter.
- Embedded game window in the editor.
- `@export_tool_button`.

**4.5**
- GDScript: `abstract` classes and methods, variadic arguments.
- Script backtraces and custom loggers, including in release builds.
- Stencil buffer support in `StandardMaterial3D` and shaders.
- The shader baker precompiles shaders at export, a big startup win on Apple and D3D12.
- Experimental screen reader and accessibility support.
- Chunked physics for TileMap.
- Async navigation region updates, plus a dedicated 2D navigation server.
- WebAssembly SIMD, native visionOS, and an SDL3 gamepad driver.

**4.6**
- **Jolt is the default physics engine for new 3D projects.** Existing projects keep their setting.
- New IK framework on `SkeletonModifier3D`: `IKModifier3D`, with solvers `TwoBoneIK3D`, `SplineIK3D`, `FABRIK3D`, `CCDIK3D` and `JacobianIK3D`.
- SSR overhaul with a half-resolution mode. Glow now blends before tonemapping. AgX tonemapper parameters. Octahedral reflection probes.
- **Direct3D 12 is the default for new Windows projects.**
- Unique node IDs keep references across renames and moves. Re-save scenes with Project → Tools → Upgrade Project Files.
- `Control.pivot_offset_ratio`.
- Debugger: ObjectDB snapshots and diffing (useful for leak hunting).
- Signals whose names start with `_` are hidden from autocomplete and docs.
- C#: `Tr()`/`TrN()` calls are extracted for POT generation.
- GDExtension: required (non-nullable) params/returns, a JSON interface definition, and tracing profiler support (Tracy, Perfetto, Instruments).
- Patch PCKs with delta encoding.
- OpenXR 1.1 and spatial entities.
- **LibGodot** lets you embed the engine in your own app (Linux, Windows and macOS initially).
- The "Modern" editor theme is the default.

**4.7**
- **HDR output** for Windows, macOS, iOS, visionOS and Linux (Wayland only).
- `AreaLight3D` for rectangular lights.
- The new **Asset Store** replaces the Asset Library.
- Built-in `VirtualJoystick` node, gyro aiming and accelerometer support.
- Tweens can wait for signals with `Tween.tween_await()`.
- One-way collision for `CollisionShape2D`.
- `DrawableTexture2D`.
- 3D vertex snapping. `Path3D` can snap to colliders.
- Offset Transform on Control.
- wasm64 web export. Web export is still WebGL 2 only (no WebGPU).
- A stable Godot Android Build Environment with full Gradle support.
- Steam Frame and Android XR support.
- 4.7 includes some breaking changes, so read the migration guide before upgrading a project.

## Upgrade advice
- Read the official migration guide for each minor version you cross ("Upgrading from Godot 4.x to 4.y" in the docs). Upgrade one minor version at a time on a branch.
- After upgrading, run Project → Tools → Upgrade Project Files (4.6+), then re-save scenes and resources.
- Delete the `.godot/` folder if imports behave strangely. It's a cache and gets regenerated.
- Godot 3 → 4 is a port, not an upgrade. The built-in converter (Project Manager → Convert) handles renames but not design changes. Expect to rewrite physics bodies, tweens, shaders, networking and file I/O by hand.
- Very old hardware: the Godot lead maintainer has said Godot 3.x, which is still maintained, is the better choice when supporting very old GPUs is the primary goal. On Godot 4, use the Compatibility renderer.

## Verifying against the real engine
Do these in order of authority:
1. **The local binary is the ground truth for its own version.**
   - `godot --version` prints the exact build.
   - `godot --headless --dump-extension-api` writes `extension_api.json`, listing every class, method, property, signal and enum in that build. Grep it.
   - `godot --headless --doctool <dir>` writes the class reference XML with descriptions.
2. **Versioned online docs.** Use `https://docs.godotengine.org/en/<version>/` (for example `en/4.7/`, or `en/stable/`), and the class reference at `.../classes/class_<lowercasename>.html`. Fetch the page when you have web access.
3. **Release notes and the interactive changelog** on godotengine.org, for when a feature appeared.
4. **The engine source** (github.com/godotengine/godot, at the matching tag), for behavior the docs don't cover.

If none of these are available and you aren't sure an API exists in the target version, say so. Don't present a guess as fact.
