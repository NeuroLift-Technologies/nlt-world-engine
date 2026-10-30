# Engine systems: input, audio, save/load, resources, scene management, threading

## Input
- Define actions in the Input Map and reference them by name: `Input.is_action_pressed(&"jump")`, `Input.get_vector(&"left", &"right", &"up", &"down")` (normalized, with deadzone), and `get_axis`. Never hardcode keycodes in gameplay code.
- Polling (`Input.*` in `_physics_process`) suits continuous movement. Events (`_unhandled_input(event)` + `event.is_action_pressed(&"x")`) suit discrete actions. Use `get_viewport().set_input_as_handled()` to stop propagation.
- Remapping: change the bindings with the `InputMap` API at runtime, and save them to a user config file.
- Gamepads: since 4.5 Godot uses an SDL3-based driver. Since 4.7 there's built-in gyro and accelerometer support, plus a virtual joystick for touch.
- Mouse look: use `Input.mouse_mode = MOUSE_MODE_CAPTURED` and read `InputEventMouseMotion.relative` (or `screen_relative`) in `_unhandled_input`, never in `_process` polling.

## Audio
- Buses (`AudioBusLayout`): Master → Music/SFX/UI/Voice, with effects (reverb, compressor, limiter). Volume sliders map to `AudioServer.set_bus_volume_db` via `linear_to_db`.
- Players: `AudioStreamPlayer` (non-positional), `AudioStreamPlayer2D/3D` (positional, with attenuation and `Area3D` reverb buses).
- Use `max_polyphony` instead of spawning a player per shot. `AudioStreamRandomizer` handles pitch and volume variation.
- Interactive music (4.3+): `AudioStreamInteractive` (clips with transitions), `AudioStreamSynchronized` (stems), `AudioStreamPlaylist`.
- Import: use OGG for music and long sounds, and WAV for short, frequent SFX (lower CPU to decode). Set loop points in import.

## Saving and loading
- Simple settings: `ConfigFile` saved to `user://settings.cfg`.
- Game saves:
  - JSON is human-readable, but it loses types (ints become floats, no Vector3), so convert explicitly.
  - Or a custom `Resource` saved with `ResourceSaver.save(res, "user://save.tres")`, which keeps types and is easy.
  - **Security:** loading a `.tres`/`.res` can run embedded scripts, so never load Resource files from untrusted sources such as downloaded saves or mods. Use JSON or `var_to_bytes` with `allow_objects=false` for anything a user could swap.
- Saving a level: save a list of dicts, each with the scene path and state, and rebuild from them. Don't pack live nodes.
- Always write to `user://`. `res://` is read-only in exported games.

## Resources
- `Resource` is the unit of data: it's ref-counted, serializable and inspector-editable. A `class_name` resource with `@export` fields makes a clean data definition (items, stats, dialogue).
- **Shared by default:** two nodes that load the same `.tres` get the same instance. Use `duplicate()` (shallow), or `duplicate_deep()` for nested resources (in the 4.7.2 class reference; deep-copy semantics changed in 4.5, so check the version) or enable `resource_local_to_scene` for per-instance state.
- Cache: `load()` returns cached instances. `ResourceLoader.load(path, "", ResourceLoader.CACHE_MODE_IGNORE)` forces a fresh copy.
- `preload()` loads at parse time (constant paths only, and it slows startup). `load()` loads at runtime. Use `ResourceLoader.load_threaded_request`/`_get_status`/`_get` for loading screens.
- UIDs: since 4.4, scripts and shaders get `.uid` sidecar files. Commit them. Move or rename files inside the editor, not the OS file manager, or references break.

## Scene management
- `get_tree().change_scene_to_file()`/`change_scene_to_packed()` swap the current scene. The swap is deferred, and the old scene is freed.
- For persistent HUDs, music or the player, use a root "Main" scene that swaps child level scenes itself, or an autoload. Loading screens use threaded loading and then `add_child`.
- `PackedScene.instantiate()`, then configure, then `add_child`. Set properties before adding when `_ready` depends on them.
- `queue_free()` is deferred. `free()` is immediate and dangerous mid-iteration or mid-signal.
- `process_mode` (`PAUSABLE`, `WHEN_PAUSED`, `ALWAYS`, `DISABLED`) plus `get_tree().paused` handles pause menus.

## Threading
- `WorkerThreadPool.add_task`/`add_group_task` for parallel jobs; `Thread` for long-lived workers; `Mutex`/`Semaphore` for synchronization.
- **The scene tree is not thread-safe.** Compute off-thread, then hand results back with `call_deferred` or a thread-safe queue that you drain in `_process`. Servers (`RenderingServer`, `PhysicsServer3D`) have thread-safe settings in Project Settings, but default to the main thread.
- Turn on `physics/3d/run_on_separate_thread` only after profiling. It changes callback timing.

## Debugging toolkit
- Remote scene tree (Debugger → Remote) to inspect the running game. "Visible Collision Shapes" and "Visible Navigation" debug toggles.
- Monitors, Profiler, Visual Profiler, Network Profiler, Video RAM list. 4.6+: ObjectDB snapshots and diffing for leaks.
- `print_debug`, `push_warning`, `push_error`, `assert()` (stripped in release builds). 4.5+: script backtraces and custom loggers in release builds, for crash reports.
- `--verbose` and `--debug-collisions` command-line flags. `--headless` for CI.
