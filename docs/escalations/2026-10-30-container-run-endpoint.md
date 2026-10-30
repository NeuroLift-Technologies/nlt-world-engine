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
2. **ASFDK governance gate** at this new control boundary.
3. **Live feed.** The sandbox exposes no ports, so the viewer cannot watch the run yet. That needs the authenticated, read-only relay described in `vercel/transport/README.md`.
4. **Maximum run length and sandbox size.** Defaults: 15 minutes, capped at 60 by the code; the plan's own maximum applies on top.
5. **Production enablement.** Pushing the image to Vercel Container Registry and setting the environment variables is a human step (see `vercel/viewer/README.md`, "Run control").
