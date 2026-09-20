# ADRs — Architecture Decision Records for the live Sims-like world

## ADR-001 — Reuse the Python ECS engine, don't rewrite it

- **Status:** Accepted
- **Context:** Three candidate kernels existed: UE C++ (dormant, no local
  toolchain), a deferred C# port, and the working Python ECS (`world-engine/`
  with seeded ticks, SimSim-style `UtilityAgent`, contract-v1 snapshots).
- **Decision:** Keep the Python ECS as the simulation kernel. All new work
  (Agent API, viewer bridge) builds on its existing seams:
  `AgentInterface`, `UtilityAgent`, `snapshot_contract.emit_contract_snapshot`.
- **Consequences:** Zero engine rewrite; the later C# port stays possible
  behind the unchanged contract-v1 boundary.

## ADR-002 — Agent API: WebSocket + REST over stdlib + websockets

- **Status:** Accepted
- **Context:** AI agents need `join`/`perceive`/`act` from any language;
  spectators need world state for renderers.
- **Decision:** `world-engine/server.py` exposes the agent protocol over
  WebSocket (`/ws`) and world snapshots over REST (`/api/world`, `/api/scene`,
  `/api/status`). Only new dependency: `websockets` (added to
  `requirements.txt`).
- **Consequences:** Provider-agnostic LLM plug-in (`connectors/llm_connector.py`)
  and the scripted bot need no engine imports. Decisions stay outside the
  deterministic tick, exactly like `demo.py`.

## ADR-003 — Upgrade the three.js viewer, bridge live state onto sim-core shapes

- **Status:** Accepted
- **Context:** `world-engine-3d/` had a working Sims-like scene but capsule
  characters and an offline JS sim.
- **Decision:** `live-client.js` maps contract-v1 snapshots onto the existing
  sim-core avatar shape (`?live=1` mode); `assets.js` manifests characters
  (procedural articulated humans now, rigged GLB drop-in later);
  `main.js` reconciles meshes with live avatar join/leave/move and swings
  limbs while walking.
- **Consequences:** Offline mode keeps working; live mode needs `server.py`.
  GLB upgrades are config changes in `assets.js`, no renderer code changes.
