# CLAUDE.md — nlt-fusion Coding Agent Context

> **Governance:** This repository operates under `ORG-DEV-OTOI-1.0.0`.
> All coding agents must read `NLT-DEV-OTOI.md` in `.github-private` before
> beginning any session. See OTOI Section 4.1 for the full session-start protocol.

---

## Repository Identity

| Field | Value |
|---|---|
| **Repo** | `NeuroLift-Technologies/nlt-fusion` |
| **Purpose** | AI-Fusion simulation training environment for neurodivergent (ADHD) support |
| **Architecture** | AI Avatar → Aide → Advocate (experiential learning pipeline) |
| **Primary Language** | Python 3.10+ |
| **Governance Contract** | `ORG-DEV-OTOI-1.0.0` |
| **Human Authority** | Joshua W. Dorsey, Sr. (`info@neuroliftsolutions.com`) |

---

## What This Repo Does

`nlt-fusion` is a **Sims/RPG-style simulation training environment** where:

- **Avatars** embody specific ADHD traits (e.g., time blindness, impulsivity, working memory deficits) and live through authentic struggle scenarios.
- **Aides** operate inside the simulation as coaches, therapists, and assistants, drawing on therapeutic knowledge and real-world ADHD expertise.
- **Advocates** are the fusion product — combining an Avatar's experiential understanding of ADHD struggle with an Aide's proven expertise — generated after the Avatar demonstrates consistent independence.

The system trains **19 Avatar-Aide-Advocate pairs** across executive-function and non-executive-function ADHD domains. This is experiential AI learning, not data-pattern training.

**Mission principle:** *"Nothing About Us Without Us"* — neurodivergent voices lead development.

---

## Tech Stack & CI

| Component | Detail |
|---|---|
| Runtime | Python 3.10+ |
| Lint | `flake8` (E9/F63/F7/F82 errors are hard failures) |
| Tests | `pytest` |
| CI Pipelines | `shared-ci.yml` (org-standard via `.github-private`) + `python-app.yml` (local baseline) |
| PR Hygiene | `pr-cleanup.yml` (stale PRs at 30 days, auto-close at +7 days) |
| Agent Prompts | `.github/agents/*.agent.md` |

To reproduce CI locally:
```bash
python -m pip install --upgrade pip
pip install flake8 pytest
pip install -r requirements.txt
flake8 . --count --select=E9,F63,F7,F82 --show-source --statistics
pytest
```

---

## Agent Session Protocol (OTOI §4.1)

Before writing any code, every agent **must** complete all five steps:

1. **Read** `NLT-DEV-OTOI.md` in `.github-private` (Sections 1, 4, 4.4, 5, 8)
2. **Read** `AGENTS.md` (coordination protocol, guardrails, internal file map)
3. **Read** this file (`CLAUDE.md`) ← you are here
4. **Read** `docs/active-threads.md` (do not duplicate or conflict with active work)
5. **Self-register** using `templates/agent-registration.json`, then confirm scope with the human

---

## Commit Format (OTOI §6)

All commits must follow:

```
[AGENT_NAME] type(scope): description
```

Valid types: `feat`, `fix`, `docs`, `refactor`, `chore`, `test`, `ci`

Example: `[CLAUDE] feat(avatar): add StayAlert scenario seed data (ORG-DEV-OTOI-1.0.0)`

---

## Escalation — When to Stop and Ask

Escalate to **Joshua W. Dorsey, Sr.** (`info@neuroliftsolutions.com`) immediately if:

- Task scope is unclear or conflicts with `docs/active-threads.md`
- An architectural decision is required (e.g., adding a new AI pair, changing fusion logic)
- A new external service or LLM provider integration is proposed
- A production deployment path is being considered
- An ethical concern arises (this repo directly impacts neurodivergent users)
- Any amendment to a governance document is being proposed

Use `templates/escalation.md` or the GitHub issue form at `ISSUE_TEMPLATE/agent-escalation.md`.

---

## Key Domain Guardrails

- **Do not** add Avatar-Aide pairs beyond the established 19 without explicit approval.
- **Do not** alter the Avatar→Aide→Advocate fusion trigger criteria unilaterally.
- **Do not** introduce new LLM providers or external AI APIs without escalation.
- **Do not** store any user/patient-adjacent data in this repo — it is a simulation/training environment only.
- All simulation scenario content must reflect authentic ADHD lived experience. When in doubt, escalate rather than guess.

---

## Directory Map

```
nlt-fusion/
├── CLAUDE.md                          ← this file (agent context)
├── README.md                          ← project overview
├── AGENT-ORCHESTRATION-GUIDE.md       ← how agents coordinate and communicate
├── HUMAN-OVERSIGHT-PROTOCOLS.md       ← human control and oversight guidelines
├── TOI-OTOI-INTEGRATION.md            ← TOI-OTOI framework documentation
├── requirements.txt
├── src/                               ← core simulation modules
│   ├── avatars/                       ← Avatar implementations
│   ├── aides/                         ← Aide support systems
│   ├── advocates/                     ← Fused Advocate intelligences
│   └── fusion/                        ← TOI-OTOI fusion algorithms
├── scripts/                           ← setup and training loop scripts
│   ├── setup_environment.py
│   └── test_training_loop.py
├── tests/                             ← test suite
├── config/                            ← configuration files
│   ├── avatars.yaml
│   ├── fusion.yaml
│   └── privacy.yaml
├── cloudflare/                        ← Cloudflare integration
│   ├── connector.py
│   ├── workers/
│   ├── config/
│   └── utils/
├── assets/
│   ├── diagrams/
│   ├── mockups/
│   └── presentations/
├── docs/
│   ├── active-threads.md              ← ALWAYS read before starting work
│   ├── architecture.md
│   ├── implementation_summary.md
│   ├── cloudflare/
│   │   └── CLOUDFLARE_SETUP.md
│   └── agent-log/                     ← session registrations and handoff records
│       ├── README.md
│       ├── registrations/
│       └── handoffs/
└── .github/
    ├── agents/                        ← agent prompt definitions (.agent.md)
    ├── workflows/                     ← CI/CD pipelines
    └── ISSUE_TEMPLATE/                ← escalation and governance proposal forms
```

---

*This file is governed by `ORG-DEV-OTOI-1.0.0`. Amendments require explicit approval from Joshua W. Dorsey, Sr.*
