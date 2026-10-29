## Escalation Record — live observer transport (Godot → Vercel viewer)

**Date:** 2026-10-29T14:00:00Z
**Agent:** Claude (Anthropic) via Claude Code
**Session:** `ccr-997c14ca-p1mbps`
**OTOI Version:** ORG-DEV-OTOI-1.0.3
**Escalation Target:** Joshua W. Dorsey, Sr.
**Priority:** low (nothing is blocked; this is the next decision when live viewing is wanted)

---

### Trigger

New external service and network exposure (OTOI §4.4). Watching a run **live** from the Vercel
viewer needs one of them, and the deployment delivery method is already recorded as undecided
(GRAPH-002, 2026-10-17: "deployment target is a cloud VM viewed in the browser (delivery method
undecided)").

### Situation

Joshua chose **file first, live later** on 2026-10-29, and Phase 1 is done (OBS-TRACE-001). Godot
writes `nlt.observer-trace.v1` JSONL (`--trace`, also from the headless script), and the viewer opens
it locally. Nothing new is exposed or hosted.

The constraint for live viewing: the viewer is served by Vercel, and the engine runs on a dev PC or a
future cloud VM. A page served from Vercel cannot reach `127.0.0.1`. The agent-loop endpoint
(`POST /agent-loop/perception`) is loopback-only and must stay that way. Whatever goes live must
carry **observer records only**, one way, read-only.

### Decision Required

1. Is live viewing wanted, and when?
2. If so, which transport (below)? Each needs approval for what it adds.

### Options Considered

1. **Vercel relay + store.** The engine (or a small sidecar that tails the trace file) POSTs signed
   batches of records to a Vercel function. The function stores them in Vercel Blob or Redis
   (Upstash), and the viewer polls the run by id.
   - Works with the engine behind NAT; no inbound ports; latency of seconds.
   - Adds: a storage service, an ingest secret (Vercel env var, never in VCS), retention and
     deletion rules for stored traces (privacy: today traces never leave the machine), a function
     to maintain. Vercel functions do not hold WebSockets, so this is polling or short-lived SSE.

2. **Direct stream from the engine host.** The engine (or a sidecar) serves the same records as
   Server-Sent Events on a read-only observer port. It is reached through a tunnel (e.g. Cloudflare
   Tunnel) from the dev PC, or directly on the cloud VM with TLS. Vercel keeps serving only the
   static viewer, and the viewer's CSP `connect-src` names that one origin.
   - Lowest latency; no stored copy, so retention stays "while the run is up".
   - Adds: an exposed endpoint with its own auth (Cloudflare Access or a token), a tunnel or VM
     networking decision, and ties live viewing to the engine host being reachable.

3. **Stay file-based.** Upload or share finished trace files by hand.
   - Adds nothing. Not live.

### Recommendation

Option 2 when the cloud VM decision is made. The VM is already the intended deployment target, SSE
over the existing record format needs no new storage or retention policy, and the read-only observer
port is separate from the loopback agent-loop endpoint. Until then, stay on option 3. If live
viewing is wanted from the dev PC before the VM exists, option 2 through a tunnel with Cloudflare
Access in front is the smallest step.

### Blockers

None now. Live viewing is blocked on this decision. Phase 1 (file traces) is complete without it.

---

### Resolution

*(To be filled in after Joshua responds)*

**Date resolved:**
**Decision:**
**Decided by:**
**Actions taken:**
