# GDScript (Godot 4) — senior-level notes

## Static typing is the default, not an option
Typed GDScript catches errors at parse time, gives real autocomplete, and runs faster (typed instructions skip runtime type checks). Write typed code unless the project is deliberately untyped.

```gdscript
class_name Enemy
extends CharacterBody3D

signal died(enemy: Enemy)

@export var max_health: int = 100
@export_range(0.0, 20.0, 0.1) var speed: float = 5.0
@export var stats: EnemyStats  # custom Resource

@onready var _nav: NavigationAgent3D = %NavAgent
var _targets: Array[Node3D] = []
var health: int:
	set(value):
		health = clampi(value, 0, max_health)
		if health == 0:
			died.emit(self)

func _ready() -> void:
	health = max_health
	stats = stats.duplicate()  # per-instance copy; resources are shared by default
```

- `:=` infers the type; use it when the type is obvious from the right side.
- Typed arrays `Array[T]`; typed dictionaries `Dictionary[K, V]` exist since 4.4.
- Recommend enabling `debug/gdscript/warnings/untyped_declaration` (as warning or error) on projects that want to stay typed.
- `class_name` registers a global type. Use it for types other scripts reference; don't add it to every script (global namespace clutter, name collisions with addons).

## Idioms
- Signals: `sig.connect(callable)`, `sig.emit(args)`, `await sig`. Bind extra args with `callable.bind(x)`. Use `CONNECT_ONE_SHOT` for one-time listeners.
- Lambdas: `button.pressed.connect(func(): _select(i))` — beware capturing loop variables; GDScript captures by value at lambda creation, which is usually what you want, but say so when it matters.
- `match` for state dispatch; consider a node-based or Resource-based state machine once states carry their own data/logic.
- `@export_group` / `@export_subgroup` / `@export_category` keep the inspector usable on large components.
- `@tool` scripts run in the editor: guard gameplay code with `if Engine.is_editor_hint(): return`, and be careful — a bad `@tool` script can corrupt scenes on save.
- `is_instance_valid(obj)` before touching something that may have been freed; `queue_free()` defers to end of frame.
- `StringName` literals: `&"jump"`; `NodePath` literals: `^"Path/To/Node"`. Input action names are compared as StringName, so `&"jump"` avoids a conversion in hot code.

## Performance notes
- Cache node references in `@onready` vars; never `get_node()` / `$` inside `_process` loops.
- Prefer `PackedVector3Array`, `PackedFloat32Array` etc. for large numeric data — contiguous memory, faster, smaller.
- Built-in engine methods (written in C++) beat equivalent GDScript loops: e.g. `Array.sort_custom`, `Geometry3D`, `PhysicsDirectSpaceState3D` queries.
- Move heavy, non-scene work to `WorkerThreadPool.add_task` — but never touch the scene tree from another thread; use `call_deferred` to hand results back.
- If a GDScript hot path is still too slow after profiling, the escalation ladder is: better algorithm → engine built-ins/servers → C# for that system → GDExtension (C++/Rust).

## Testing
GUT and gdUnit4 are the common test frameworks. Headless runs: `godot --headless --path . -s addons/gut/gut_cmdln.gd` (GUT) — confirm the exact command against the version installed in the repo.
