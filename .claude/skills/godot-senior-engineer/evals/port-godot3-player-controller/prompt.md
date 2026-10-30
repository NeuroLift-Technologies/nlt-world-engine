---
tags: [skill-creator]
max_turns: 20
timeout_seconds: 600
allowed_tools: [Read, Glob, Grep, Skill, Write, Edit, Bash]
---

i grabbed this player script off an old tutorial and godot 4.7 is throwing a bunch of errors at me, can you fix it so it works? its a 3d third person thing

```gdscript
extends KinematicBody

export var speed = 8
export var jump_strength = 12
export var gravity = 30

var velocity = Vector3.ZERO
onready var pivot = $Pivot

func _physics_process(delta):
    var dir = Vector3.ZERO
    if Input.is_action_pressed("move_right"):
        dir.x += 1
    if Input.is_action_pressed("move_left"):
        dir.x -= 1
    if Input.is_action_pressed("move_back"):
        dir.z += 1
    if Input.is_action_pressed("move_forward"):
        dir.z -= 1
    if dir != Vector3.ZERO:
        dir = dir.normalized()
        pivot.look_at(translation + dir, Vector3.UP)
    velocity.x = dir.x * speed
    velocity.z = dir.z * speed
    velocity.y -= gravity * delta
    if is_on_floor() and Input.is_action_just_pressed("jump"):
        velocity.y = jump_strength
    velocity = move_and_slide(velocity, Vector3.UP)

func take_hit():
    $AnimationPlayer.play("hit")
    yield($AnimationPlayer, "animation_finished")
    emit_signal("hit_finished")
```
