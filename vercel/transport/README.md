# Transport

Explicit, versioned contracts between simulation state and the viewer. Reuse existing
contracts in `docs/contracts/state-feed-v1.md` (observer/projection feed) and
`docs/contracts/agent-loop-v1.md` (physical perception/intent boundary). Keep observer/
presentation data distinct from agent-loop execution requests. Never expose loopback
`POST /agent-loop/perception` publicly; viewer uses an authorized observer feed/relay.

## Current transport (2026-10-29)

**Files.** The engine writes `nlt.observer-trace.v1` JSONL
(`docs/contracts/observer-trace-v1.md`), and the viewer opens it client-side. There is no live
transport yet. The options and the recommendation are in
`docs/escalations/2026-10-29-observer-live-transport.md`, awaiting Joshua's decision.
