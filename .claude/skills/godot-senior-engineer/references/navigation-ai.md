# Navigation and AI

## Navigation
- Setup:
  - 3D: `NavigationRegion3D` + `NavigationMesh`, baked from source geometry: meshes, static colliders, or a group.
  - 2D: `NavigationRegion2D` + `NavigationPolygon`, or TileSet navigation layers.
  - 4.5+: region updates and baking are asynchronous, and 2D has its own navigation server.
- Agents: put `NavigationAgent2D/3D` on the moving body.
  - Set `target_position`.
  - Each physics frame, read `get_next_path_position()` and steer velocity toward it.
  - Stop when `is_navigation_finished()`.
  - Wait one physics frame after the scene loads before the first query, because the map syncs at the end of the physics frame. Querying in `_ready` returns empty paths. Use `await get_tree().physics_frame` or the `NavigationServer3D.map_changed` signal.
- Avoidance (RVO) is separate from pathfinding:
  - Enable `avoidance_enabled`, set `radius` and `max_speed`, write your desired velocity to `agent.velocity`, then move with the `safe_velocity` from the `velocity_computed` signal.
  - Avoidance doesn't know about walls, only other agents and obstacles (`NavigationObstacle3D`).
- `NavigationLink3D` for jumps, ladders and teleports. Navigation layers on regions and agents for terrain types.
- Agent radius and height are baked into the navmesh. Agents of a different size need their own navmesh or map.
- Low-end budget: bake at load, not every frame. Throttle path requests (re-path on a timer, or when the target moves past a threshold), and use `NavigationServer` queries directly for bulk work.

## Game AI patterns
- Finite state machines (enum + `match`, or node-per-state) for most NPCs. Behavior trees (addons such as LimboAI or Beehave) once behaviors get deep and reusable. Utility AI for choosing between many scored options.
- Perception: `Area3D` for awareness radius, then a `RayCast3D` or `PhysicsDirectSpaceState3D.intersect_ray` for line of sight. Run perception on a timer, not every frame.
- Keep decision logic out of nodes where you can: pure classes are testable, and the node layer just senses and acts.
- External or ML decision makers (LLM or other models):
  - Run inference off the main thread or out of process.
  - Snapshot the world state for the model.
  - Validate the returned action against the live world at execution time.
  - Feed structured results back to the model.
  - Never block the physics frame waiting on a model.
