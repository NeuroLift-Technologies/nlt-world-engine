# Escalation Record — Python engine missing core modules

> Copied from `templates/escalation.md`. A tracking GitHub issue is filed via
> `ISSUE_TEMPLATE/agent-escalation.md`.

---

## Escalation Record

**Date:** 2026-05-29T00:00:00Z
**Agent:** Claude Code
**Session:** claude/wizardly-lovelace-7Wt7H
**OTOI Version:** ORG-DEV-OTOI-1.0.0
**Escalation Target:** Joshua W. Dorsey, Sr.
**Priority:** high

---

### Trigger

The Python simulation engine under `world-engine/src/` cannot run end-to-end. Making it
runnable touches package structure and dependency management — architectural decisions that
per `CLAUDE.md` and `HUMAN-OVERSIGHT-PROTOCOLS.md` require Joshua's approval, not a guess.

---

### Situation

`world-engine/src/` contains ~10 well-structured modules (event bus, state machine, ECS,
world engine, 13 scenarios, NPC base, `session_orchestrator.py`, `training_session.py`) and
they all compile. But the orchestrator and training loop import four modules that do not
exist anywhere in the tree:

| Imported symbol(s) | Expected path | Referenced from |
|---|---|---|
| `BaseAvatar`, `TaskResult` | `world-engine/src/avatars/base_avatar.py` | `simulation/session_orchestrator.py:18` |
| `BaseAide`, `CoachingContext` | `world-engine/src/aides/base_aide.py` | `simulation/training_session.py:13` |
| `ReadinessAssessor`, `FusionReadiness` | `world-engine/src/fusion/readiness_assessor.py` | `simulation/session_orchestrator.py:20` |
| `SupabaseClient` | `world-engine/src/database/supabase_client.py` | `simulation/training_session.py:15` |

`src/avatars/` and `src/aides/` hold only `*_configs/` JSON; `src/fusion/` and
`src/database/` don't exist. There are no `__init__.py` files and no
`requirements.txt`/`pyproject.toml`. The Cursor 2026-05-29 handoff guessed the missing
modules "likely live in a sibling repo." The React frontend prototype
(`world-engine/index.html` + `.jsx`) is separately fully runnable and is not wired to this engine.

---

### Decision Required

1. Where do the four missing modules come from — (a) **vendor** them from a sibling repo
   (which one?), (b) **implement** them here against the existing call sites, or
   (c) **defer** the engine and treat the React frontend as the near-term deliverable?
2. Should `__init__.py` files be added to the `world-engine/src/` tree (package structure)?
3. Should a `requirements.txt` / `pyproject.toml` be created for the engine's dependencies
   (e.g. the Supabase client)?

Items 2 and 3 are the two decisions Cursor left pending in its 2026-05-29 handoff.

---

### Options Considered

1. **Vendor from a sibling repo**
   - Description: Copy or submodule the four modules from wherever they live (PR #1 referenced
     a private `neurolift-ai-fusion` repo).
   - Trade-offs: Fastest path to a runnable engine *if the code already exists*; introduces a
     cross-repo dependency and requires access to that source.

2. **Implement here from the existing interfaces**
   - Description: Build `BaseAvatar` / `BaseAide` / `ReadinessAssessor` / `SupabaseClient`
     against the call sites already present in the orchestrator and training session.
   - Trade-offs: Self-contained; but it is net-new design work and risks diverging from any
     canonical implementation that exists elsewhere.

3. **Defer — frontend-first**
   - Description: Park the Python engine; invest in the working React prototype as the
     near-term deliverable; update the README to match.
   - Trade-offs: Lowest immediate effort and matches what actually runs today; leaves the
     "training pipeline" narrative unfulfilled for now.

---

### Recommendation

Choose **(1) vendor** if the modules already exist in a sibling repo — cheapest route to a
runnable engine. If no canonical source exists, **(3) defer** and lead with the frontend
rather than author speculative core classes. Once direction is set, resolve (2)/(3) together
by adding `__init__.py` and a `requirements.txt` so the engine is importable and reproducible.
Holding off on guessing per governance.

---

### Blockers

- Python engine cannot run end-to-end until the four modules are present.
- Curated salvage of PR #1's engine-dependent stubs (`scripts/test_training_loop.py`,
  `src/avatars|aides|fusion` placeholders) is blocked on this decision.
- The `__init__.py` and `requirements.txt`/`pyproject.toml` decisions are blocked here.

---

### Resolution

*(To be filled in after Joshua responds)*

**Date resolved:**
**Decision:**
**Decided by:**
**Actions taken:**
