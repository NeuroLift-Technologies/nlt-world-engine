---
type: llm
focus: trace
weight: 1
---

Identifies the @rpc("any_peer") take_damage as an exploit and moves damage authority to the server with validation (e.g. multiplayer.get_remote_sender_id(), range/rate/sanity checks)
