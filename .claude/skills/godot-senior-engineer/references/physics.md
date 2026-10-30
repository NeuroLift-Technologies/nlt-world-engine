# Physics (2D and 3D, Jolt and Godot Physics)

## Engines
- **3D:** Jolt has been the default for new projects since 4.6 (built in since 4.4). Godot Physics is still available. Check `physics/3d/physics_engine` in `project.godot` before reasoning about behavior. Projects created before 4.6 keep whatever they had.
- Jolt is generally faster and more stable for stacking and many bodies. Known differences from Godot Physics:
  - Some joint parameters behave differently or aren't supported.
  - `SoftBody3D` behavior differs.
  - There are edge cases in contact reporting. In 4.7.2, Jolt Areas are sensors created with `mCollideKinematicVsNonDynamic = true` (`modules/jolt_physics/objects/jolt_area_3d.cpp`), so they **do** detect static bodies. Older advice about an "areas detect static bodies" project setting is out of date: that setting doesn't exist in 4.7.2.
  - Shape margins behave differently.
  - When migrating, retest joints, areas and anything tuned by hand.
- **2D:** Godot Physics 2D, the only built-in option. Rapier 2D/3D is available as an extension.

## Jolt project settings worth knowing (4.7.2 defaults, from `ProjectSettings.xml`)
All of these live under `physics/jolt_physics_3d/`.
- `simulation/velocity_steps` = 10 and `simulation/position_steps` = 2: solver iterations. Raise them for stiff stacks and joints; lower them on a weak CPU.
- `simulation/allow_sleep` = true, with `sleep_velocity_threshold` 0.03 and `sleep_time_threshold` 0.5. If a RigidBody "won't move when it should", disable sleep temporarily to check.
- `simulation/generate_all_kinematic_contacts` = false. A RigidBody frozen in **kinematic** mode doesn't generate contacts against other kinematic or static bodies unless this is on, and turning it on is expensive against concave or heightmap shapes. This matters when you carry objects by freezing them.
- `simulation/penetration_slop` 0.02, `speculative_contact_distance` 0.02, `baumgarte_stabilization_factor` 0.2, `continuous_cd_movement_threshold` 0.75.
- `collisions/collision_margin_fraction` 0.08, `collisions/active_edge_threshold`, and `*/use_enhanced_internal_edge_removal` (on for simulation and motion queries) for snagging on internal edges.
- `motion_queries/recovery_iterations` 4 and `recovery_amount` 0.4. These affect `move_and_slide()` depenetration in CharacterBody3D.
- `limits/max_linear_velocity` 500 m/s, `max_angular_velocity`, `max_bodies` 10240, `max_body_pairs` 65536, `max_contact_constraints` 20480, `temporary_memory_buffer_size` 32 MB. Hitting a limit shows up as dropped contacts or errors in very large scenes.
- `joints/world_node` = 0 controls which joint node stands for "the world". In Godot Physics only `node_b` can represent the world, so joint setups can differ between the two engines.
- `queries/enable_ray_cast_face_index` = false. Turn it on if you need `face_index` from ray hits on concave shapes.

Look up any setting with `scripts/godot_api_check.py --show ProjectSettings | grep jolt`. For exact behavior, read `modules/jolt_physics/` at the matching tag.

## Body types
- **CharacterBody (2D/3D):** kinematic and controlled by code. Set `velocity`, then `move_and_slide()`. Read `is_on_floor()`/`get_slide_collision(i)` afterwards.
  - Tune `floor_snap_length`, `floor_max_angle`, `wall_min_slide_angle`, `max_slides` and `platform_on_leave`.
  - For gravity, use `get_gravity()` (4.3+), which respects `Area` gravity overrides.
- **RigidBody:** simulated. Drive it with `apply_force`/`apply_central_impulse`/`apply_torque`, or override `_integrate_forces(state)` for direct control.
  - **Never set `position`/`global_transform` every frame** on an unfrozen RigidBody; it teleports and fights the solver.
  - To hold or carry one, set `freeze = true` with `freeze_mode = FREEZE_MODE_KINEMATIC` and move it by transform.
- **StaticBody:** doesn't move. Use **AnimatableBody** for moving platforms that push other bodies; `sync_to_physics` carries riders.
- **Area:** overlap detection (`body_entered`, `area_entered`), gravity, damping and audio bus overrides. `monitoring`/`monitorable` toggles help performance.

## Collision setup
- Layers = "what I am", masks = "what I scan for". Name layers in Project Settings → Layer Names. Most "it doesn't collide" bugs are layer/mask mistakes or a missing `CollisionShape`.
- Shape cost, cheapest first: sphere/circle < capsule < box < cylinder < convex < concave (trimesh). Concave shapes go only on static bodies. Prefer compound primitive shapes for dynamic bodies.
- Don't scale collision shapes non-uniformly on physics bodies. Change the shape's size instead.
- Fast objects tunnel: enable `continuous_cd` on RigidBodies, use raycasts or shapecasts for bullets, or raise the tick rate.

## Queries
- `RayCast3D`/`ShapeCast3D` nodes are for persistent checks, updated each physics frame. Use `force_raycast_update()` for an immediate result.
- `get_world_3d().direct_space_state` with `intersect_ray(PhysicsRayQueryParameters3D.create(from, to, mask, exclude))`, `intersect_shape` or `cast_motion` for one-off queries. Only call these in `_physics_process`. Outside it, the space may be locked or stale.

## Timing and smoothing
- `physics/common/physics_ticks_per_second` (default 60). Physics interpolation smooths rendering between ticks: 2D since 4.3, 3D since 4.4. Turn it on when the tick rate differs from the refresh rate. Call `reset_physics_interpolation()` after teleports.
- `max_physics_steps_per_frame` caps catch-up steps on slow frames, which prevents a "spiral of death" on weak CPUs.
- Physics is not deterministic across machines. Don't build networked lockstep on it.

## Common bugs, by symptom
- Jitter: the camera or visuals update in `_process` while the body moves in `_physics_process` (enable interpolation), or the Camera follows with smoothing in the wrong process mode.
- Sliding down slopes: `floor_stop_on_slope`, snap length, or applying gravity while on the floor without the snap.
- An Area doesn't detect: monitoring off, a mask mismatch, or the other side isn't `monitorable`.
- A body falls through the floor after spawning: it was spawned overlapping, or with a huge velocity, or the floor is a thin trimesh. Use a thicker box, or turn on CCD.
