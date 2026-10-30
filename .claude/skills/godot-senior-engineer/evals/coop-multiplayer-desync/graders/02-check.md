---
type: llm
focus: trace
weight: 1
---

Identifies that enemies are spawned with add_child outside a MultiplayerSpawner (only on the host, with random positions) and fixes it with MultiplayerSpawner (spawnable scene + spawn_path) or equivalent replicated spawning
