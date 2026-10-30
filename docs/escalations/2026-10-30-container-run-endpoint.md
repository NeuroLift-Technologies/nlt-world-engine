# Escalation: container `/run` endpoint and Vercel hosting

## Escalation Record

**Date:** 2026-10-30  
**Agent:** Claude (Anthropic) via Claude Code  
**Session:** ccr-cfb13a59-j499a5 (PR #134)  
**OTOI Version:** ORG-DEV-OTOI-1.0.3  
**Escalation Target:** Joshua W. Dorsey, Sr.  
**Priority:** medium

### Trigger

Production deployment and architecture decisions: a public HTTP endpoint on the engine, and a new hosting target.

### Situation

Joshua asked to run the Dockerfile on Vercel containers. Vercel Container Runtime (beta) needs a long-running HTTP server on `$PORT`. PR #134 adds `container-host/`, which supervises headless Godot and serves `/health` and a token-gated `/run`. The engine has no request ingress, so `/run` returns 501. The image contains no ML model and Vercel has no GPU. Instances scale to zero after 5 minutes idle (30 seconds in preview), losing in-memory simulation state.

### Decision Required

1. What should `/run` do (drive a scenario, forward an intent to `IntentIngress`, return a feed slice), and through what engine-owned ingress?
2. Deploy on Vercel Container Runtime, Vercel Daemons, or a GPU/container host called from Vercel?
3. May a separate Vercel project be created for the container?

### Options Considered

1. **Vercel Container Runtime**
   - Description: request-oriented functions from the root Dockerfile.
   - Trade-offs: simple, but cold starts and scale to zero lose state.

2. **Vercel Daemons**
   - Description: container that runs continuously.
   - Trade-offs: keeps the simulation alive, but receives no inbound traffic, so a relay is needed.

3. **Other container host**
   - Description: Vercel calls a service hosted elsewhere.
   - Trade-offs: GPU and persistence available, adds an external service integration.

### Recommendation

Merge #134 as a deployable skeleton only. No strong recommendation on hosting until the `/run` contract is defined.

### Blockers

`/run` behaviour and any deployment.

### Resolution (partial)

**Date:** 2026-10-30  
**Decided by:** Joshua W. Dorsey, Sr. (in session)

- **Hosting: Vercel Sandbox.** A "run" is one sandbox started from the engine image, with headless Godot as its process. The human observer starts and stops it from a button in the viewer (`vercel/viewer`, `/api/run`). Chosen over Vercel Container Runtime (cannot guarantee start and stop reach the same instance), Daemons (production only, no inbound traffic) and Cloudflare Containers (new host).
- **`/run` on the container host:** no longer the control path. The `world-engine-container` Vercel project and `container-host/` stay as a test harness until Joshua says otherwise.

**Still open (Joshua)**

1. ~~**Who may press the button.**~~ **Resolved 2026-10-30 (Joshua): Vercel team only.** `NLT_RUN_CONTROL=enabled` is set only for the **Preview** environment of `world-engine-viewer`, which sits behind Vercel Auth, so only people on the Vercel team can open the page and press the button. Production stays off. Anything wider (named observers, a shared password, a public viewer) is a new decision.
2. ~~**ASFDK governance gate** at this control boundary.~~ **Resolved 2026-10-30 (Joshua): keep ASFDK in the engine, add an audit log.** ASFDK-C# checks agent *intents* (prompt injection, RRT crisis, Sleepwalker distress, TOI/OTOI policy) in `AsfdkGovernanceGate`; a human Start/Stop press has no content for it to evaluate, so there is no ASFDK call at the button. Inside a run, the engine's gate is unchanged (the sandbox sets `NLT_AGENT_LOOP_ENABLED=0`, so today's run has no intents). `/api/run` now writes one JSON audit line to the function logs for every start, stop and refusal (`event`, `action`, `outcome`, `status`, `runId`, `at`). It cannot record *who*: Vercel Auth gates the page but does not identify the person to the function. GET polling is not logged.
3. ~~**Live feed.**~~ **Decided 2026-10-30 (Joshua): near-live by polling the trace file; not built yet.** The sandbox exposes no port. The run is started with `NLT_OBSERVER_TRACE=<path>`; the engine flushes `nlt.observer-trace.v1` after every line (`ObserverTrace.cs`). A viewer route (`/api/run/trace?from=<offset>`) will read new bytes from the running sandbox and the viewer appends them to the Recording, with the same Vercel-team-only access as the controls. Latency of seconds; nothing stored on our side. Still to verify: that `--trace` works headless inside a sandbox. The stored-relay and public-SSE options in `2026-10-29-observer-live-transport.md` are not taken.
4. ~~**Maximum run length and sandbox size.**~~ **Resolved 2026-10-30 (Joshua): 15 minutes and 2 vCPU / 4 GB.** Both are settable (`NLT_RUN_MAX_MINUTES`, never above 60; `NLT_SANDBOX_VCPUS`, 1 to 4, at 2048 MB per vCPU). There is no automatic extension: a run ends at the cap and Stop works at any time. The size is a starting point; Godot's real memory use in a sandbox has not been measured and should be checked on the first real run. Cost per minute has not been looked up; the Vercel plan's own sandbox maximum applies on top of the 60-minute code ceiling.
5. ~~**Enablement.**~~ **Decided 2026-10-30 (Joshua): Joshua pushes the image; the agent sets the Preview variables.** Joshua runs `vercel vcr build docker . world-engine:<tag> --push --project world-engine-viewer` (the image must live in the registry of the project whose function creates the sandboxes) and tells the agent the tag. The agent then sets `NLT_SANDBOX_IMAGE` and `NLT_RUN_CONTROL=enabled` on the viewer's **Preview** environment only, and checks the first preview. No CI automation and no new secret. Production stays off.

**Status:** all five items are decided. Built: start/stop button, `/api/run`, audit log, size and length settings. **Not built yet:** the near-live trace polling from item 3. **Not done:** the first real run against a sandbox (needs the pushed image).
