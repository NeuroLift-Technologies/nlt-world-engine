# AGENTS.md — NeuroLift Technologies Organization-Wide Internal Gateway

> **Internal use only.** This is the private governance gateway for all coding agents operating within NeuroLift Technologies repositories. For public-facing principles, see the public [`NeuroLift-Technologies/.github`](https://github.com/NeuroLift-Technologies/.github) repository.

---

## You Are Here

You are a coding agent operating within the **NeuroLift Technologies** organization. This document is your internal coordination gateway.

**Mandatory reading order:**
1. `NLT-DEV-OTOI.md` — Full org-level coding agent contract (this repo, root level)
2. Repo-level `CLAUDE.md` — Project-specific context (in the repo you are working in)
3. `docs/active-threads.md` — Current work state (in the repo you are working in)

> **Can't access `.github-private`?** If links to this repository return 404, key governance
> docs are mirrored publicly:
> - NLT-DEV-OTOI.md → https://github.com/NeuroLift-Technologies/.github/blob/main/governance/NLT-DEV-OTOI.md
> - AGENTS.md → https://github.com/NeuroLift-Technologies/.github/blob/main/governance/AGENTS.md
>
> Ask your org admin to grant the GitHub App access to `.github-private`. See
> `docs/troubleshooting/github-app-access.md` in this repo for instructions.

**Final authority:** Joshua W. Dorsey, Sr. Escalate. Do not guess.

---

## Solidarity Framework Principles (Public)

The ethical foundation of all NLT work is publicly documented in the **Solidarity Framework** and **HAIEF** (Human-AI Ethical Integration Framework):

- Public governance principles: [`NeuroLift-Technologies/.github`](https://github.com/NeuroLift-Technologies/.github)
- HAIEF reference: https://elevaitionfoundation.org

The principles are public. The operational machinery is in this private repository.

---

## Coordination Protocol

### Session Start (Every Session)

```
1. Read NLT-DEV-OTOI.md (this repo)
2. Read repo-level CLAUDE.md (working repo)
3. Read docs/active-threads.md (working repo)
4. Self-register per OTOI Section 3
5. Confirm task scope before beginning
```

### Commit Format

All agent commits must follow:

```
[AGENT_NAME] type(scope): description
```

Types: `feat`, `fix`, `docs`, `refactor`, `chore`, `test`, `ci`

### Escalation Triggers

Escalate to Joshua immediately when:
- Task scope is unclear or conflicts with existing work
- An architectural or deployment decision is required
- A blocker cannot be resolved by the agent
- An ethical concern arises
- LLM provider or external service selection is needed

Use the escalation template: `templates/escalation.md`

---

## Guardrails

These are **non-negotiable**. No exceptions without explicit Joshua approval:

| Guardrail | Details |
|---|---|
| No LLM provider lock-in | Do not hardcode or commit to a specific LLM provider |
| No architecture decisions | Database, deployment, framework choices require human sign-off |
| No production deployments | Human must explicitly approve all production actions |
| No credential storage | Never store secrets, tokens, or credentials in code or VCS |
| No external integrations | Third-party service connections require Joshua's approval |
| No OTOI self-amendment | This governance doc cannot be changed by agents |

---

## Internal File Map

All files below live in this repository (`NeuroLift-Technologies/.github-private`):

```
NLT-DEV-OTOI.md                        ← Canonical org-level agent contract
AGENTS.md                               ← This file
nltotoi.json                            ← Discovery manifest

.nltotoi/
├── README.md                           ← Namespace overview
├── index/governance-files.md          ← File registry
├── contracts/README.md                ← Contract namespace
├── proposals/validation-roadmap.md    ← Validation roadmap
└── scripts/validate-governance.sh     ← Governance validation

templates/
├── agent-registration.json            ← OTOI Section 3 registration format
├── handoff-record.json                ← OTOI Section 5 handoff format
├── escalation.md                      ← OTOI Section 4.3 escalation format
└── intent-log.md                      ← Intent logging template

ISSUE_TEMPLATE/
├── agent-escalation.md                ← GitHub escalation issue form
└── governance-proposal.md             ← OTOI amendment proposal form

PULL_REQUEST_TEMPLATE/
└── agent-contribution.md              ← Agent PR checklist

workflows/
└── validate-governance.yml            ← CI: runs validate-governance.sh

SOPs/
├── new-agent-onboarding.md            ← How to onboard a new coding agent
├── repo-governance-setup.md           ← How to add governance to a new NLT repo
└── incident-response.md               ← What to do when an agent goes off-rails
```

---

## Multi-Agent Coordination

When multiple agents may be active:

1. **Check active-threads.md first** — do not begin work already in progress
2. **Claim your thread** — update active-threads.md when starting a task
3. **Write handoff records** — never leave a session without a handoff document
4. **Do not overwrite peer work** — if conflict is detected, escalate

---

## Handoff Protocol

Before ending any significant session:

1. Update `docs/active-threads.md` in the working repo
2. Write a handoff record to `docs/agent-log/handoffs/` using `templates/handoff-record.json`
3. Document any open escalations in `docs/escalations/`
4. Summarize decisions made and decisions pending

---

## Cursor Cloud specific instructions

### Codebase overview

This repo has two runnable components — the React frontend prototype and the governance validation script — plus a Python simulation engine that is **not yet runnable end-to-end**:

| Component | Location | How to run |
|---|---|---|
| **React frontend prototype** | `world-engine/` (index.html + JSX) | `cd world-engine && python3 -m http.server 8765` then open `http://127.0.0.1:8765/` |
| **Python simulation engine** | `world-engine/src/` | Not yet runnable end-to-end — core modules (`src/avatars/base_avatar.py`, `src/aides/base_aide.py`, `src/fusion/readiness_assessor.py`, `src/database/supabase_client.py`) are missing from this repo |
| **Governance validation** | `.nltotoi/scripts/validate-governance.sh` | `bash .nltotoi/scripts/validate-governance.sh` |

### Lint and test

- **Flake8 (critical):** `flake8 world-engine/src/ --count --select=E9,F63,F7,F82 --show-source --statistics`
- **Flake8 (style):** `flake8 world-engine/src/ --count --exit-zero --max-complexity=10 --max-line-length=127 --statistics`
- **Syntax check:** `python3 -m compileall world-engine/src/`
- **pytest:** `pytest` — no tests directory exists yet; pytest will collect zero tests
- The only CI workflow is `.github/workflows/validate-governance.yml` (`on: [push, pull_request]`), which runs `bash .nltotoi/scripts/validate-governance.sh` on every push and pull request — there is no branch filter, so it runs on feature branches too. (There are no `python-app.yml` or `shared-ci.yml` workflows in this repo.)

### Gotchas

- The frontend prototype has **no build step** and **no package.json**. It loads React 18 + Babel from CDN. Any static file server works.
- Python source under `world-engine/src/` uses explicit relative imports (`from ..core.events import ...`), so the modules must be imported with the correct package context (e.g., as a `python -m` module from a configured root), not executed as standalone scripts. The absence of `__init__.py` files is not itself the blocker — modern Python imports these directories as namespace packages.
- `session_orchestrator.py` and `training_session.py` import modules that don't exist in this repo (`base_avatar`, `base_aide`, `readiness_assessor`, `supabase_client`). They compile fine but cannot be executed.
- `$HOME/.local/bin` must be on `PATH` for `flake8` and `pytest` to be found (the update script installs them via `pip install --user`).

---

*Internal governance document — NeuroLift Technologies | ORG-DEV-OTOI-1.0.2*
