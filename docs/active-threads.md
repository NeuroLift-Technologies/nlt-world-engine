# Active Threads — nlt-fusion

> This file tracks active work threads. Agents must read this at session start and update it during and at the end of each session.

**Last updated:** 2026-06-09

---

## Active Threads

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
| Fusion Studio research and replay contracts | Codex | 2026-06-04 | This PR | Adopted the supplied Claude Design Studio shell without overwriting the canonical World Engine, documented the Hugging Face and GitHub landscape, and added a draft v1 simulation/replay contract with a passing deterministic fixture. Visual browser smoke testing remains outstanding because the in-app browser runtime was unavailable. |
