---
tags: [skill-creator]
max_turns: 20
timeout_seconds: 600
allowed_tools: [Read, Glob, Grep, Skill, Write, Edit, Bash]
---

making a 4 player co-op game in godot 4.7 (gdscript). players jitter like crazy on clients, sometimes the host sees enemies the clients dont, and one of my testers figured out he can kill bosses instantly. heres the relevant stuff:

```gdscript
# player.gd  (each player scene has a MultiplayerSynchronizer syncing position + rotation, replication "Always")
extends CharacterBody3D
const SPEED = 6.0
func _physics_process(delta):
    var input = Input.get_vector("left","right","forward","back")
    velocity = Vector3(input.x, 0, input.y) * SPEED
    move_and_slide()
```

```gdscript
# enemy_spawner.gd (autoload)
extends Node
var enemy_scene = preload("res://enemy.tscn")
func spawn_wave(count):
    for i in count:
        var e = enemy_scene.instantiate()
        e.position = Vector3(randf_range(-20,20), 0, randf_range(-20,20))
        get_tree().current_scene.add_child(e)
```

```gdscript
# enemy.gd
extends CharacterBody3D
var health = 100
@rpc("any_peer")
func take_damage(amount):
    health -= amount
    if health <= 0:
        queue_free()
```

the host calls spawn_wave when a round starts. clients call `enemy.take_damage.rpc(dmg)` when they hit something. whats wrong and how do i fix it
