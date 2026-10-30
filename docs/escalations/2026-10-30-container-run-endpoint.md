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

### Resolution

*(To be filled in after Joshua responds)*
