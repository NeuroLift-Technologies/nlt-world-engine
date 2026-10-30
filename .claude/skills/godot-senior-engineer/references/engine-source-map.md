# Godot engine source map (github.com/godotengine/godot)

Use the source when the docs don't answer the question: what a method actually does, a default value, an edge case, an error message's origin, or why two physics engines behave differently. Always read the tag that matches the project (for example `4.7.2-stable`). `master` may have already changed.

## Getting it cheaply
```
git clone --depth 1 --branch 4.7.2-stable --filter=blob:none --sparse https://github.com/godotengine/godot
cd godot
git sparse-checkout set doc/classes modules            # class reference XML (core + modules), enough for the API checker
git sparse-checkout add scene/3d/physics modules/jolt_physics   # add only the areas you need to read
```
Use `git ls-tree -r --name-only HEAD <dir>` to list files without downloading them. Use `git grep` once the files are checked out.

## Where things live (4.7.2 layout)
| Question | Look in |
|---|---|
| What a node does (`CharacterBody3D.move_and_slide`, `Area3D`, joints) | `scene/3d/physics/`, `scene/2d/physics/` (`character_body_3d.cpp`, `area_3d.cpp`, `joints/`) |
| Other 3D or 2D nodes (lights, cameras, skeleton, IK) | `scene/3d/`, `scene/2d/`. IK in 4.6+: `ik_modifier_3d`, `two_bone_ik_3d`, `fabr_ik_3d`, `ccd_ik_3d`, `jacobian_ik_3d`, `chain_ik_3d`, `skeleton_modifier_3d` |
| UI controls, containers, themes | `scene/gui/`, `scene/theme/` (the default theme is built in code) |
| Resources (materials, meshes, Tween, AnimationLibrary, TileSet) | `scene/resources/`, `scene/animation/` (Tween, AnimationMixer/Player/Tree) |
| SceneTree, Node, Viewport, Window, timers, the main loop | `scene/main/` (`node.cpp`, `scene_tree.cpp`, `viewport.cpp`) |
| Physics engines | `modules/jolt_physics/` (`objects/` bodies and areas, `spaces/` layers and queries, `shapes/`, `joints/`, `jolt_project_settings.cpp`) and `modules/godot_physics_3d/`, `modules/godot_physics_2d/` |
| Physics server API (what both engines implement) | `servers/physics_3d/`, `servers/physics_2d/` |
| Rendering: renderers, shaders, RenderingDevice | `servers/rendering/` (`renderer_rd/` covers Forward+/Mobile, `shader_language.cpp` is the shader parser), `drivers/gles3/` (Compatibility), `drivers/vulkan`, `d3d12`, `metal` |
| Navigation | `servers/navigation_3d|2d/` (API), `modules/navigation_3d|2d/` (implementation), `scene/3d/navigation/` (nodes) |
| GDScript language (parser, analyzer, warnings, VM) | `modules/gdscript/` (`gdscript_parser.cpp`, `gdscript_analyzer.cpp`, `gdscript_warning.cpp`, `gdscript_vm.cpp`) |
| C#/.NET glue, source generators, SDK | `modules/mono/` (`glue/GodotSharp/`, `editor/Godot.NET.Sdk/`, `editor/Godot.NET.Sdk/Godot.SourceGenerators/`) |
| Multiplayer, RPC, Spawner/Synchronizer | `modules/multiplayer/` (`scene_multiplayer.cpp`, `scene_replication_interface.cpp`), `modules/enet/`, `modules/websocket/`, `modules/webrtc/` |
| Import pipeline (glTF, FBX/ufbx, textures) | `modules/gltf/`, `modules/fbx/`, `editor/import/` |
| Variant, Object, signals, ClassDB, StringName | `core/variant/`, `core/object/`, `core/string/` |
| File I/O, ResourceLoader/Saver, PCK, project settings | `core/io/`, `core/config/project_settings.cpp` |
| Input, InputMap, events | `core/input/` |
| GDExtension interface | `core/extension/` (`gdextension_interface.json` since 4.6) |
| Editor: docks, inspector, export, plugins | `editor/` (`export/`, `inspector/`, `plugins/`, `import/`, `project_upgrade/`) |
| Platform specifics (Android Gradle, web shell, Windows, Wayland) | `platform/<os>/` |
| Command-line flags (`--headless`, `--doctool`, `--export-release`, …) | `main/main.cpp` |

## Files that answer "what changed?"
- `CHANGELOG.md`: release-by-release changes (4.7 starts around line 266 at the 4.7.2 tag).
- `misc/extension_api_validation/<from>_<to>/*.txt`: every intentional API break, with the PR number. A summary for 4.4→4.7 is in `references/api-changes-4.4-4.7.md`.
- `*.compat.inc` (78 files at 4.7.2): old method signatures kept for binary compatibility. If a method has an entry here, its signature changed at some point.
- `editor/project_upgrade/renames_map_3_to_4.cpp`: the Godot 3→4 rename tables, summarized in `references/godot3-renames.md`.
- `doc/classes/ProjectSettings.xml`: every project setting with its default and description. This is the authority for "what's the default?".

## Reading tips
- Look up a method by its bound name first: `git grep -n '"move_and_slide"' scene/`. The `ClassDB::bind_method(D_METHOD("name"...)` call leads to the C++ implementation.
- Look up an error message by grepping its text. `ERR_FAIL_COND_MSG` and `ERR_FAIL_V_MSG` messages are literal strings in the source, so you can find exactly what condition triggered a user's error.
- Default property values are set in the constructors or `_bind_methods` (`ADD_PROPERTY` plus the member initializer). The class XML `default=` attribute mirrors them.
