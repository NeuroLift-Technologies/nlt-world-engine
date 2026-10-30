---
type: llm
focus: trace
weight: 1
---

The review flags the per-frame GetNodesInGroup + LINQ scan as O(n^2) across ~200 crates with per-frame allocations
