# Active Threads — nlt-fusion

> This file tracks active work threads. Agents must read this at session start and update it during and at the end of each session.

**Last updated:** 2026-06-04

---

## Active Threads

### Engine direction — Python simulation engine is non-runnable 🔴 BLOCKED (awaiting Joshua)
- **Agent:** Claude Code · **Opened:** 2026-05-29
- The orchestrator and training loop import four modules that exist nowhere in the tree
  (`base_avatar`, `base_aide`, `readiness_assessor`, `supabase_client`), so the engine
  cannot run end-to-end. Decision needed: vendor these from a sibling repo, implement
  them here, or defer (treat the React frontend as the near-term deliverable). Also
  pending: whether to add `__init__.py` files and a `requirements.txt`/`pyproject.toml`.
- **Escalation:** `docs/escalations/2026-05-29-python-engine-missing-modules.md`
- Folds in the two decisions Cursor left pending in its 2026-05-29 handoff.

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
| Dev environment setup | Cursor Cloud Agent | 2026-05-29 | [#5](https://github.com/NeuroLift-Technologies/nlt-fusion/pull/5) | Set up Cursor Cloud dev environment, documented lint/test/run commands in AGENTS.md, verified governance validation and frontend prototype |
| Fusion Studio research and replay contracts | Codex | 2026-06-04 | This PR | Adopted the supplied Claude Design Studio shell without overwriting the canonical World Engine, documented the Hugging Face and GitHub landscape, and added a draft v1 simulation/replay contract with a passing deterministic fixture. Visual browser smoke testing remains outstanding because the in-app browser runtime was unavailable. |
