# Intent Log Entry

**Date:** 2026-06-09T00:00:00Z
**Agent:** Claude Code
**Session:** claude/brave-darwin-5hxolo
**OTOI Version:** ORG-DEV-OTOI-1.0.2
**Working repo:** NeuroLift-Technologies/nlt-fusion

---

### Action

Implement Josh's directly stated scope decision (this session, 2026-06-09): **nlt-fusion is the
environment-only repo** — "put AI in an environment like the Sims game." ADHD traits and fusion
mechanics move to the `neurolift-ai-fusion` repo.

Two parts:

1. **Separate the training-side code out of `world-engine/src/`:**
   - Remove `src/avatars/`, `src/aides/`, `src/fusion/`, `src/database/` (all stub
     implementations from 2026-06-04 that raise `NotImplementedError`, plus ADHD trait
     config JSON that belongs with the trait work in `neurolift-ai-fusion`).
   - Remove `src/simulation/session_orchestrator.py` and `src/simulation/training_session.py`
     (the training loop — Avatar/Aide pairing, coaching, fusion readiness — all sibling-repo
     concerns).
   - Keep `src/core/` (event bus, state machine — generic infrastructure) and everything
     under `src/simulation/environment/` and `src/simulation/npcs/`.
   - Git history preserves everything removed; the PR description will note that the removed
     stubs and configs are the starting point for `neurolift-ai-fusion`.

2. **Make the environment actually run** (no architectural decisions beyond what Josh stated):
   - `Collider` and `Needs` components; richer `Interactable` (use duration, need effects).
   - `MovementSystem`, `InteractionSystem`, `NeedsSystem` — the missing systems flagged by
     the placeholder comment in `world_engine.py`.
   - Spatial index in `GridManager` (current queries are linear scans inside A*).
   - Deterministic sim clock and seeded RNG on `WorldEngine` (aligns with contracts/v1
     replay philosophy).
   - A `world_builder` that instantiates a small home world (rooms + props with affordances).
   - A runnable demo (`world-engine/demo.py`) where a simple utility-based agent perceives,
     decides, and acts through `AgentInterface` — the "AI living in the world" proof, with a
     documented seam where an LLM controller can replace the rule-based one.
   - Tests for pathfinding, movement, interaction, needs, and determinism.

---

### Rationale

Josh stated the scope directly in this session ("i wanted to separate the 2 … this repo is
supposed to only focus on the world engine creating the environment that the training will
take place in"). The 2026-05-29 escalation's open question — where do the four missing
modules come from — is thereby answered: they belong to `neurolift-ai-fusion`. Keeping the
stubs here would keep misleading future sessions (it already misled three). The systems work
is environment-internal and was identified as requiring no new architecture decisions.

---

### Risks

- The removed config JSON (`avatar_configs/`, `aide_configs/`) may be wanted verbatim in the
  sibling repo — mitigated by git history and an explicit note in the PR description.
- `src/core/events.py` defines training-flavored signal types; kept as-is for now to avoid
  churn — may need pruning later.
- Default sim start time changes from `datetime.now()` to a fixed epoch (overridable via
  config) for determinism; nothing currently depends on wall-clock start.

---

### Alternatives Considered

1. **Keep the stubs in place and only add environment systems** — rejected: contradicts the
   separation Josh just asked for, and the stubs keep confusing agents about repo scope.
2. **Move the training code into a `_attic/` folder instead of deleting** — rejected: git
   history already preserves it; an attic invites the same scope confusion.

---

### Escalation Needed

**no** — the decision-maker (Josh) stated the direction directly in this session. All work
lands on a draft PR for his review before merge.

---

### Outcome

*(To be filled in after the action is taken)*

**Date completed:**
**Result:**
**Deviations from plan:**
