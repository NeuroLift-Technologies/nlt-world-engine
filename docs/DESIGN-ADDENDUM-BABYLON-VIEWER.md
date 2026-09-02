# World Engine — Design Addendum: Babylon.js as a Second Viewer

**Status:** Proposed — pending Joshua's sign-off (see §7)
**Amends:** `docs/world-engine/DESIGN.md` (2026-06-22, approved)
**For:** whichever agent picks up the `world-engine-v2` rewire.
**Governed by:** ORG-DEV-OTOI-1.0.2.

---

## 0. Why this document exists

Between the last recorded handoff (`docs/agent-log/handoffs/2026-06-22-cursor-world-engine-v1.json`)
and now, an agent identified in commit trailers as **HERMES** built a second,
independent world engine at `world-engine-v2/` (Babylon.js + TypeScript), with no
registration, no handoff record, and no `active-threads.md` entry. It is not
mentioned in any prior governance document.

Inspection of `world-engine-v2/src/main.ts` and `simulation.ts` shows this is not
a renderer for the Python kernel — it is a **second, self-contained simulation**
with its own tick loop (`sim.step()`), its own avatar state, and no connection to
the kernel's SSE stream. This is the exact pattern DESIGN.md §1/§5 retired
("the browser `sim.jsx` `setInterval` loop... is retired *as a simulation*").

This addendum does not re-litigate the 2026-06-22 decision. It resolves the gap:
**Babylon.js is kept, but demoted to a second projection of the same kernel truth**
— exactly the role `sim-live.jsx` already has, just with a richer renderer.

---

## 1. The decision this addendum proposes

> **One simulation authority (the Python kernel). Two viewers of it: `sim-live.jsx`
> and `world-engine-v2` (Babylon.js). Neither viewer simulates anything.**

Nothing about the kernel, contracts, or v1 scope in DESIGN.md changes. This
addendum only defines how `world-engine-v2` must be rewired to comply with the
existing decision, since it currently doesn't.

---

## 2. Current state of `world-engine-v2` (as found)

- `main.ts` constructs a local `Simulation` (`simulation.ts`) with its own
  `tickHz` / `timeScale` / `dysfunctionOn` / `urgencyThreshold` config, and
  drives the Babylon scene from `sim.state` on every local tick.
- Avatars are currently empty ("world is environmental only") but the local
  sim loop is fully wired up and running — it is not a stub, it works, it's
  just simulating nothing yet.
- Scene geometry (rooms/props) is built by `WorldScene.buildWorld()` from its
  own hardcoded layout, not from `world-engine/data/scenes/default_home.v1.json`.
- No connection to `world-engine/service/server.py`'s SSE/REST endpoints exists
  anywhere in the `world-engine-v2` source.
- Branch/PR sprawl: `babylon-v2`, `babylon-v2-clean`, `babylon-world-engine`,
  `babylon-world-engine-v2`, `feat/world-engine-v2-babylon-mmo`,
  `hermes/3d-world-engine-v1`, `hermes/utility-agent-refactor`,
  `world-engine-v2-pr(-final)?(-pr)?`, `world-engine-v2-release(-pr)?` — at
  least 13 branches carrying variations of this same work. These should be
  pruned once the canonical branch is identified and merged (see §8).

---

## 3. Target architecture for `world-engine-v2`

Same shape as `sim-live.jsx`, ported to Babylon.js:

- **Remove `simulation.ts`'s local sim entirely.** No `sim.step()`, no local
  `tickHz`/`timeScale` state, no `Math.random` anywhere on this path (same
  determinism guardrail as DESIGN.md §8, extended explicitly to this renderer).
- **New `KernelStream` class** (replaces `Simulation`): opens an `EventSource`
  against the kernel's SSE endpoint (`world-engine/service/server.py`), parses
  incoming `contracts/v1` snapshot/event payloads, and exposes the latest
  parsed snapshot — nothing else. No local state mutation beyond "last snapshot
  received."
- **`main.ts`'s render loop reads snapshots, not sim state.**
  `worldScene.updateAvatarPositions(...)` and `hud.render(...)` take the parsed
  SSE snapshot (`avatars/entities/extensions` per
  `world-engine/contracts/v1/snapshot.schema.json`) instead of `sim.state`.
- **Scene geometry loads from the canonical scene file.** `WorldScene.buildWorld()`
  reads room/prop layout from `world-engine/data/scenes/default_home.v1.json` —
  the same file the Python kernel and `sim-live.jsx` both use — instead of its
  own hardcoded layout. One scene file, three consumers (kernel, `sim-live.jsx`,
  Babylon.js).
- **HUD controls call the kernel's REST endpoint.** Pause/step/pace/
  assign-scenario, if/when added to the Babylon HUD, hit the same REST control
  endpoint `sim-live.jsx` uses — never a local mutation.

---

## 4. What does NOT change

- Python kernel: unchanged. Still sole authority, still deterministic, still
  emits `contracts/v1`.
- `sim-live.jsx`: unchanged. Remains the lightweight reference viewer.
- v1 scope (Core Loop slice, StayAlert Morning Routine, 19-avatar fleet
  deferred, LLM controllers deferred): unchanged.
- Contracts: unchanged. No new schema work implied by this addendum.

---

## 5. Why keep Babylon.js at all

Not required for v1 acceptance criteria (DESIGN.md §5 is satisfied by
`sim-live.jsx` alone). The case for keeping it:

- Meaningfully richer visual fidelity for demos, partner outreach, and
  investor-facing material (isometric 3D vs. `sim-live.jsx`'s flatter view) —
  relevant given Josh's active DeepMind/Anthropic/Y Combinator outreach threads
  that benefit from a polished visual.
- Substantial working code already exists (camera, lighting, isometric tile
  rendering, HUD overlay) — the fix is disconnecting a bad wire, not
  rebuilding a renderer from scratch.

If this cost isn't worth it relative to other priorities, the alternative is
to park `world-engine-v2` entirely and let `sim-live.jsx` remain the only
viewer. That's a fair call — flagging it as a real option, not just a
formality (see §7).

---

## 6. Known traps

- `world-engine-v2` currently has **uncommitted local changes** to
  `index.html`, `data.ts`, `hud.ts`, `main.ts`, `scene.ts`, `simulation.ts` on
  branch `world-engine-v2-release-pr` at time of writing — reconcile or
  discard before starting this work, don't build on top of an unknown diff.
- At least 13 branches carry overlapping variations of this same Babylon.js
  work (see §2). Identify which is actually newest/most complete before
  picking a base — don't assume `main`'s merged state is the most current.
- `dysfunctionOn` / `urgencyThreshold` config in the current `Simulation`
  class may encode assumptions about avatar behavior that were never reviewed
  against the "behavior must never be presented as clinical ground truth"
  guardrail (DESIGN.md §8). Confirm before porting any of this logic forward,
  even as inert config.
- `.github/workflows/world-engine-v2-build.yml` already exists — same
  restriction as DESIGN.md §8 applies: do not edit CI workflows in this
  environment; surface CI needs to Joshua.

---

## 7. Open question for Joshua

This addendum assumes "keep Babylon.js as a second viewer" is the right call
per your direction. Before implementation starts, confirm:

1. Keep both viewers (this addendum's plan), or park Babylon.js and go
   `sim-live.jsx`-only for v1?
2. Was HERMES's work directed by you, or should it be treated as
   unauthorized/exploratory work to be salvaged rather than trusted as-is?
   (This affects how much of the existing Babylon.js code is treated as
   reviewed vs. as a rough draft.)
3. Branch cleanup: OK to prune the ~13 stale `babylon-*`/`world-engine-v2-*`
   branches once the canonical one is identified and merged?

---

## 8. Governance guardrails (carried from DESIGN.md §8, apply here too)

- **PR-only.** Branch off `main`, deliver via PR. Never push to `main`.
- **Session records:** register in `docs/agent-log/registrations/`, write a
  handoff in `docs/agent-log/handoffs/`, and add/maintain a
  `docs/active-threads.md` entry. HERMES's work skipped this — don't repeat
  that gap.
- **Escalate to Joshua** for anything beyond this brief, same as DESIGN.md §8.
- **Determinism:** no unseeded `random` on the render/viewer path — same rule,
  explicitly extended to `world-engine-v2`.
- **Do not edit `.github/workflows/*`** in this environment.

---

*Drafted by Claude (Anthropic) at Joshua's request, following review of
`nlt-fusion.zip` contents against `docs/world-engine/DESIGN.md` and git
history. Pending Joshua's decision per §7 before implementation begins.*
