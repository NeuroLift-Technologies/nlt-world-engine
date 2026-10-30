# Export, build, CI, editor plugins, GDExtension, embedding

## Exporting
- Install export templates that exactly match the editor version. A mismatch is the #1 export error.
- `export_presets.cfg` holds the presets. Commit it, but keep secrets (keystore passwords, signing credentials) in environment variables or `.godot/export_credentials.cfg`, which is not committed.
- Command line: `godot --headless --export-release "Linux" build/game.x86_64` (also `--export-debug`, or `--export-pack` for a `.pck`). Use `--import` (or `--headless --editor --quit`) first on a fresh checkout so the `.godot/` import cache exists.
- Feature tags (`OS.has_feature("web")`, custom tags per preset) for per-platform code paths and project-setting overrides (`setting.web=...`).
- Resource filters: exclude dev-only folders. Also make sure resources that are loaded by string path are included ("export all" or explicit filters). The classic "works in editor, missing in export" bug is `load()` with a computed path to a resource the exporter didn't include.
- PCK and patches: `ProjectSettings.load_resource_pack()` loads DLC and mods. Since 4.6, patch PCKs support delta encoding.
- The shader baker (4.5+) precompiles shaders at export. Turn it on for Apple and D3D12 targets.

## Platform notes
- **Web:**
  - WebGL 2, so the Compatibility renderer only.
  - Single-threaded export (4.3+) avoids the SharedArrayBuffer/COOP-COEP header requirement. Threaded export needs those headers.
  - wasm64 since 4.7, which allows more than 4 GB of memory.
  - C# web export has historically not been supported in Godot 4; check the current docs.
  - Browser audio needs a user gesture before it plays.
- **Android:**
  - Needs the SDK, JDK and a debug keystore. Use the Gradle build for plugins and custom manifests.
  - 4.6+: Android editor Gradle builds through a companion app, plus scrcpy mirroring of exported games.
  - 4.7: stable Android Build Environment.
- **iOS/macOS:** export from macOS with Xcode. Sign and notarize macOS builds for distribution.
- **Windows:** new projects default to D3D12 since 4.6, with a Vulkan fallback. rcedit sets icons and metadata. Code-sign to avoid SmartScreen warnings.
- **Linux:** ships as an x86_64 binary plus `.pck` (or embedded pck). Test on both Wayland and X11. HDR output only works under Wayland.
- **Steam:** use GodotSteam (a module or GDExtension) for achievements, networking and the overlay. Test the Steam overlay on every renderer and platform you ship; its compatibility varies.

## CI
- Run headless Godot in CI:
  1. Cache the editor binary and templates.
  2. `godot --headless --import`.
  3. Run tests: GUT (`-s addons/gut/gut_cmdln.gd`), gdUnit4 (its CLI runner), or `dotnet test`.
  4. Export.
- Community GitHub Actions and Docker images (for example barichello/godot-ci) exist. Pin the exact Godot version.
- Gate merges on the import step plus tests, because import errors catch broken references.

## Editor plugins and tools
- `@tool` scripts run in the editor. Guard runtime code with `Engine.is_editor_hint()`. A crashing `@tool` script can corrupt scenes on save, so commit before experimenting.
- `EditorPlugin` (in `addons/<name>/plugin.cfg` + script) adds docks, inspector plugins (`EditorInspectorPlugin`), custom importers (`EditorImportPlugin`), gizmos, export plugins (`EditorExportPlugin`) and custom node types.
- `@export_tool_button` (4.4+) gives quick inspector buttons without writing a plugin.
- Asset distribution: the Asset Store (4.7+) replaces the Asset Library. Addons live in `addons/`, and you enable them under Project Settings → Plugins.

## GDExtension (native code)
- Use it when profiling proves GDScript/C# is the bottleneck, or to bind a C/C++/Rust library.
- Bindings: godot-cpp (C++, SCons or CMake), godot-rust `gdext` (Rust), and others (Swift, Zig, …).
- The `.gdextension` file maps platforms to libraries and sets `compatibility_minimum`. An extension built against an older API generally works on newer minor versions, but not the other way round.
- Get the API for a specific build with `godot --dump-extension-api` (the `extension_api.json` that bindings generate from). 4.6 adds a JSON interface definition and required (non-nullable) argument metadata.
- Hot reload works for GDExtension in the editor, with caveats; restart if behavior looks stale.
- Modules (C++ compiled into a custom engine build) instead of GDExtension: only when you need engine-internal access or a custom build anyway, for example `precision=double` or stripping features for size.

## Embedding: LibGodot (4.6+)
- Godot can run as a library inside another application, which controls startup and the main loop. Initial support is Linux, Windows and macOS.
- Consider it when Godot is one component of a larger app, such as a simulation viewer inside a tool. For a normal game, it's unnecessary complexity.
