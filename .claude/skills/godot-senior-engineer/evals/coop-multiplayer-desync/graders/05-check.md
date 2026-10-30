---
type: llm
focus: trace
weight: 1
---

Addresses the client jitter cause (e.g. synchronizing raw position every frame with no interpolation, or fighting between local simulation and sync) with a concrete fix such as interpolation/buffering or syncing only from the authority
