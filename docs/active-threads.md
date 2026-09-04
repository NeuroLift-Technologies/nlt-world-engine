# Active Threads — nlt-fusion

> This file tracks active work threads. Agents must read this at session start and update it during and at the end of each session.

**Last updated:** 2026-09-04

---

## Active Threads

### 🔐 Secret-purge + code-scanning fixes 🟡 AWAITING MERGE
- **Agent:** Codex (Poolside) · **Opened:** 2026-09-04 · **Branch:** `fix/security-code-scanning`
- **Scope:** Purge 3 leaked API keys (Cloudflare/OpenRouter/Groq) from the committed `Makefile.bin` build artifact + resolve the 7 open code-scanning alerts.
- **Delivered:**
  - Purged `WorldEngine/Intermediate/Build/Linux/x64/WorldEngine/Development/Makefile.bin` (commit `908defd` on the v2 build branch) from git history via `git filter-repo`; `git gc --aggressive --prune=now` dropped packed blob `fb05a89b…` from all objects. Remote v2 branch force-pushed (purged tip `3476f75c`); since it was later deleted, no reachable ref holds the secret. All 3 provider keys revoked; GitHub secret-scanning alerts #1–#3 dismissed as `revoked`.
  - PR #36: added `permissions: contents: read` to both CI workflows; added same-origin guard + replaced `*` postMessage targets with `window.location.origin` in 5 `world-engine/_drafts/*.jsx` handlers. Branch from `origin/main`; disjoint from PR #33's C++ graphics work (no conflicts).
- **Verification:** `validate-governance.sh` 29/29 (fix branch + PR #33); PR #33 & #36 checks SUCCESS (CodeQL + GitGuardian + Governance + CodeRabbit). No secret prefixes in tree; blob `fb05a89b…` returns `fatal`.
- **WIP backups:** 3 secret-free WIP snapshots preserved as local branches `bkp-wip-babylon`, `bkp-wip-char-gfx`, `bkp-wip-worldv2pr`.
- **Next baton:** A human (Josh or reviewer) must approve + merge PR #36 to clear the 7 code-scanning alerts on `main`. Decide whether to keep the `bkp-wip-*` branches.

### M2/M3 Follow-up — VFX alignment + security fix 🟡 IN PROGRESS
- **Agent:** OpenCode · **Opened:** 2026-09-02 · **Branch:** `feat/world-engine-m1-timeoflight-m6-circulation`
- **Scope:** Follow-up to commit `177cc6a` (M1 lighting + M6 polish + VFX + soundscape + sim infra). Resolves uncommitted changes and script/asset consistency gaps.
- **Delivered:**
  - Removed `SecurityToken` from `DefaultEngine.ini` (🔴 credential guardrail violation — was removed in `3dea023` but re-added as uncommitted change; now reverted to clean state)
  - Fixed `niagara_vfx.py` (M2) naming/path alignment: `SteamCoffee`→`CoffeeSteam`, `RainWindows`→`RainOnWindow`, `/Game/VFX/Niagara`→`/Game/VFX/Workplace` to match actual on-disk `.uasset` filenames
  - Refined `NS_HVACAirflow.uasset` (+56 bytes, particle tuning from previous session)
  - Verified M3 (soundscape) end-to-end: `generate_workplace_soundscape.py` → 4 WAV beds → `SoundscapeDataAsset` (4 layers: HVAC/Fridge/Clock/Murmur) → `SoundscapeSubsystem` (stress-modulated volume/pitch, fade in/out, mute/unmute), all names consistent
- **Commit:** `a1a9768` `[OPENCODE] fix(world-engine): M2 ambient VFX asset name/path alignment + NS_HVACAirflow refinement`
- **Next baton:** If opening a PR, verify the PR Review Hermes bot passes all checks (OSSAR-Scan, credential scan, governance validation) before requesting review.

### PR #24 Review — world-engine-v2-release-pr 🟡 IN REVIEW
- **Agent:** Codex Agent (Poolside) · **Opened:** 2026-09-02 · **Branch:** `world-engine-v2-release-pr`
- **Scope:** Full code/governance/security review of PR #24 (100 text files + 36 binary assets, 6 commits from `102d344` through `5850786`).
- **Review posted:** 2026-09-02 — posted as COMMENT review on PR #24. Verdict: **CHANGES REQUESTED** (2 🔴 blocking, 3 🟡 high).
- **Blockers:**
  1. 🔴 `REVIEW.md:21,98` — OTOI version `1.0.3` should be `1.0.2` (canonical per `NLT-DEV-OTOI.md` line 4)
  2. 🔴 `WorldEngine/Scripts/verify_bindings.py:16` — hardcoded expired MCP session ID; violates "No credential storage" guardrail (NLT-DEV-OTOI.md)
- **Should-fix:** `DefaultGame.ini:15` AssetManager scans `/Game/Maps/` but levels at `/Game/Scenarios/Levels/`; `create_scenario_assets.py` & `test_headless_sim.py` use non-functional UE Python APIs
- **Bot corroboration:** CodeRabbit="Merge Ready, minimal risk"; GitGuardian="no secrets"; Kilo Code flagged same OTOI mismatch
- **Next baton:** Resolve 2 🔴 blockers + 3 🟡 high items, then PR ready for approval

### PR #28 — Web server (SSE/REST) subsystem + real-world SimBody kit 🟡 IN REVIEW
- **Agent:** OpenCode · **Opened:** 2026-09-03 · **Branch:** `feat/world-engine-webserver-simbody`
- **Scope:** Adds the v1 Core Loop transport (DESIGN.md §3) as an engine-subsystem-hosted HTTP server, plus a real-world cm-scale SimBody kit.
- **Adds:** `UNLTWebServerSubsystem` (EngineSubsystem) with `/api/snapshot`, `/api/scene`, `/api/status`, `/api/control`; CORS enabled; hosted at engine boot (decoupled from PIE; same host carries the MCP endpoint on :8000). SimBody kit assets under `WorldEngine/Content/Kits/SimBody/`.
- **Changes:** NLTAgentVisualizer → SimBody mesh at `AgentScale` (1.0 = life size), engine-cube fallback; Build.cs + HTTPServer/HTTP/Sockets deps; WorldEngine.uproject + WebSocketNetworking & MetaHuman plugins; NLTRoomStateSubsystem.h forward-decl ordering fix; NLTDemoGameMode.cpp comment; Workplace_Level.umap update.
- **Review:** Kilo review (2026-09-03) requested changes — 4 critical + 1 high C++ blockers. **All resolved in `f3dea58`**: `OnPostEngineInit` no-arg wrapper via `GetOnPostEngineInit()`+`FDelegateHandle`; `/api/control` no longer hardcodes `{ok:true}` nor exposes no-op `assign_scenario`/`reset` (unknown actions → error); `assign_scenario`/`reset` stubs removed; `/api/stream` (single SSE event, non-streaming) renamed to `/api/snapshot` (one-shot JSON); snapshot read uses read-only `GetEntityManager()` + non-deprecated `ForEachEntityChunk`. Reply comment posted; re-review pending.
- **Security note:** A `SecurityToken` was re-added to `DefaultEngine.ini` as an uncommitted change (credential-guardrail violation per NLT-DEV-OTOI / earlier `3dea023`); **excluded** from this PR — reverted from the branch.
- **Next baton:** re-review/merge PR #28; true SSE streaming (draining `EventBuffer`/`BroadcastEvent` via SPSC `StreamingBodyQueue`) is deferred follow-up; scenario assignment/reset control handlers belong in `neurolift-ai-fusion` seam per environment-only scope decision.

### World Engine v1 Core Loop — implementation 🟡 IN PROGRESS
- **Agent:** Cursor · **Opened:** 2026-06-22 · **Branch:** `cursor/world-engine-v1-core-loop`
- **Scope:** v1 Core Loop slice per `docs/world-engine/DESIGN.md` (Josh-approved 2026-06-22).
- **Delivered this session:**
  - Canonical scene JSON at `world-engine/data/scenes/default_home.v1.json` + loader (`src/simulation/scene/`).
  - `AgentState` ECS component; `get_snapshot()` / `load_snapshot()` emit `contracts/v1` shape (`snapshot_contract.py`).
  - `ScenarioSystem` wiring `pers_4` Morning Routine with scheduled stressor + Aide intervention.
  - `ScenarioAgent` + `core_loop.py` bootstrap; headless `WorldRunner` (`runner.py`).
  - SSE+REST service (`world-engine/service/server.py`) — stream, scene, control endpoints.
  - Studio live viewer (`sim-live.jsx`) projecting kernel snapshots; `world-view.jsx` reads `WE_SCENE`.
  - 24 tests passing (incl. new `test_core_loop.py`).
- **Run:** `python3 world-engine/service/server.py` then open `world-engine/index.html?live=1`.
- **Next baton:** PR review/merge; v2 items (playback scrubbing, WebSocket controllers, LLM controllers).

### World Engine — direction set, handed to Cursor 🟢 DECIDED
- **Agent:** Claude Code (architect) · **Opened:** 2026-06-22 · **Branch:** `docs/world-engine-design`
- **Decision (Josh, 2026-06-22):** build the actual world engine on the existing **headless, deterministic Python ECS kernel** (`world-engine/src/`) — not the browser tick loop, and not a human-player game engine — because **AI agents live in the world; humans only watch**. The studio (`world-view.jsx`/`hud.jsx`) becomes a **read-only live viewer** fed by a `contracts/v1` snapshot/event stream over SSE.
- Wrote `docs/world-engine/DESIGN.md`: architecture (scene JSON, existing ECS, headless scheduler w/ pace, A\*/perception reuse, new `ScenarioSystem` wiring the orphaned `scenarios.py`, real `get_snapshot`/`load_snapshot` + SSE/REST transport, studio as projection), the 4 settled follow-on calls (SSE+REST transport, deterministic kernel + recorded controllers, Python scene JSON canonical, v1 = Core Loop slice), v1 acceptance criteria, file layout, traps, and OTOI guardrails.
- Resolves the **Next baton** of the "Environment-only" thread below (scenario→world instantiation, `contracts/v1` emission, transport decision).
- **Implementation handed to Cursor** (Cursor = implementation per `senior-dev-hub`); baton + decision recorded in `senior-dev-hub` (`active-thread.md` + `decisions.md`).
- **Next baton:** Cursor builds the v1 Core Loop slice per the brief — PR-only, `[CURSOR]` commits, escalate architecture/safety to Josh.

### Environment-only scope — engine core implemented 🟢 IN REVIEW
- **Agent:** Claude Code · **Opened:** 2026-06-09 · **Branch:** `claude/brave-darwin-5hxolo`
- **Scope decision (Josh, 2026-06-09):** nlt-fusion is the environment-only repo — "put AI
  in an environment like the Sims game." ADHD traits and fusion mechanics move to
  `neurolift-ai-fusion`. This also closes the 2026-05-29 escalation's open question: the
  four "missing modules" belong to the sibling repo, not here.
- Removed training-side code (`src/avatars|aides|fusion|database`, `session_orchestrator`,
  `training_session`) — git history preserves it as the starting point for the sibling repo.
- Implemented the environment core: `Collider`/`Needs`/`Descriptor` components,
  `NeedsSystem`/`MovementSystem`/`InteractionSystem`, spatial grid index, deterministic
  clock + seeded RNG, `world_builder` (default home world), richer `AgentInterface`,
  `demo.py` (utility agent autonomously living a full day), 12 new tests (16 total passing).
- **Next baton:** review/merge the PR; then NPC behavior (BaseNPC is still abstract),
  scenario→world instantiation, contracts/v1 snapshot/event emission from the Python
  engine, and the transport decision for how `neurolift-ai-fusion` agents connect.

### Repo housekeeping — sync threads, prune duplicates/branches, triage PR #1 🟡 IN PROGRESS
- **Agent:** Claude Code · **Opened:** 2026-05-29
- Removed the duplicate `world-engine/uploads/` tree (46 unreferenced mirror files of the
  root governance docs + frontend); kept `_drafts/`.
- Triaged and **closed PR #1** (stale skeleton base, conflicts with now-canonical
  governance, stub inaccuracies); its useful config/docs to be salvaged once engine
  direction is set.
- Branch pruning still pending — remote deletion is blocked in this environment (HTTP 403),
  so the stale branches must be removed via the GitHub UI.

### Governance normalization decision — carried over from Codex 2026-04-25 🟡 NEEDS DECISION
- Codex's 2026-04-25 handoff left pending: *"Whether this repository should be included in
  the next stricter normalization pass."* Untracked for ~5 weeks — resolve or close it.

---

## Resolved Threads

| Thread | Agent | Date | PR | Summary |
|---|---|---|---|---|
| Engine direction — Python simulation engine stub implementation | Claude Code | 2026-06-04 | In progress | Created minimal stub implementations of the four missing modules (base_avatar, base_aide, readiness_assessor, supabase_client) to unblock syntax validation. Engine now compiles cleanly but is not executable end-to-end (stubs raise NotImplementedError). Package structure established. Awaiting architectural decisions. |
| Dev environment setup | Cursor Cloud Agent | 2026-05-29 | [#5](https://github.com/NeuroLift-Technologies/nlt-fusion/pull/5) | Set up Cursor Cloud dev environment, documented lint/test/run commands in AGENTS.md, verified governance validation and frontend prototype |
| Fusion Studio research and replay contracts | Codex | 2026-06-04 | [#8](https://github.com/NeuroLift-Technologies/nlt-fusion/pull/8) | Adopted the supplied Claude Design Studio shell without overwriting the canonical World Engine, documented the Hugging Face and GitHub landscape, and added a draft v1 simulation/replay contract with a passing deterministic fixture. Visual browser smoke testing remains outstanding because the in-app browser runtime was unavailable. |
| World Engine Phase 6: Asset & Build Validation | Poolside Agent | 2026-09-02 | N/A | Created 13 Scenario DataAssets (UScenarioDataAsset with TSoftObjectPtr<UWorld> LevelReference); created 4 .umap levels (Workplace, Personal, Social, Academic) with ≥10 PlayerStarts, NavMesh, and full lighting; verified all 13 DataAsset→Level bindings resolve correctly; cooking via RunUAT.sh completed with 0 errors; load times 0.1–0.2s (well under 30s target). Full report at `WorldEngine/Saved/Phase6ValidationReport.json`. |
