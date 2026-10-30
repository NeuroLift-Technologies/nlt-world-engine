---
tags: [skill-creator]
max_turns: 20
timeout_seconds: 600
allowed_tools: [Read, Glob, Grep, Skill, Write, Edit, Bash]
---

quick one, godot 4.7.2 gdscript. two things:
1. i have a tween sequence for a door: slide open, then i want it to WAIT until the player emits `interacted` before sliding closed. whats the cleanest way to do that in the tween itself
2. im porting to android and need a virtual thumbstick for movement that feeds my existing input actions (move_left/move_right/move_forward/move_back). do i need a plugin for that?
