# Agent Log — nlt-fusion

> **Governance:** `ORG-DEV-OTOI-1.0.0`
> This directory is a required governance artifact. It must not be deleted,
> renamed, or restructured without explicit approval from Joshua W. Dorsey, Sr.

---

## Purpose

The `agent-log/` directory is the **institutional memory** of all coding agent activity in this repository. It provides:

1. **Auditability** — a record of who (which agent) worked on what, when, and under what scope
2. **Continuity** — handoff records so the next agent can resume without losing context
3. **Accountability** — registration records linking each session to a specific agent identity and task commitment

This log is required by `ORG-DEV-OTOI-1.0.0` and is read during governance reviews.

---

## Directory Structure

```
docs/agent-log/
├── README.md               ← this file
├── registrations/          ← one file per agent session (agent-registration.json)
│   └── .gitkeep
└── handoffs/               ← one file per completed session (handoff-record.json)
    └── .gitkeep
```

---

## `registrations/` — Session Registration Records

**When:** At the start of every agent session (OTOI §4.1, Step 5).

**What:** A completed copy of `templates/agent-registration.json`, saved as:
```
registrations/<AGENT_NAME>-<YYYY-MM-DD>-<short-scope>.json
```

**Required fields (per OTOI §3):**

| Field | Description |
|---|---|
| `agent_name` | The name of the coding agent (e.g., `CLAUDE`, `COPILOT`) |
| `platform` | The platform running the agent (e.g., `GitHub Copilot`, `Claude Code`) |
| `session_id` | Unique session identifier |
| `session_start` | ISO 8601 timestamp |
| `working_repo` | `NeuroLift-Technologies/nlt-fusion` |
| `working_branch` | The git branch for this session |
| `task_scope` | One-paragraph description of the task, as confirmed with the human |
| `otoi_version` | Must be exactly `ORG-DEV-OTOI-1.0.0` |
| `human_authority` | Must be `Joshua W. Dorsey, Sr.` |
| `escalation_contact` | Must be `info@neuroliftsolutions.com` |

---

## `handoffs/` — Session Handoff Records

**When:** At the end of every agent session, before the agent terminates (OTOI §5).

**What:** A completed copy of `templates/handoff-record.json`, saved as:
```
handoffs/<AGENT_NAME>-<YYYY-MM-DD>-<short-scope>-handoff.json
```

**Required fields (per OTOI §5):**

| Field | Description |
|---|---|
| `agent_name` | The agent completing the handoff |
| `session_id` | Matches the registration session ID |
| `session_end` | ISO 8601 timestamp |
| `task_scope` | Restated from registration |
| `work_completed` | Bullet list of what was actually done |
| `work_not_completed` | Anything in scope that was NOT finished |
| `blockers` | Anything that prevented completion |
| `next_steps` | Recommended actions for the next agent or human |
| `files_changed` | List of files created, modified, or deleted |
| `branch` | The git branch used |
| `pr_url` | URL of the pull request, if one was opened |
| `escalations_filed` | Any escalations raised during the session |
| `otoi_version` | Must be exactly `ORG-DEV-OTOI-1.0.0` |

---

## Governance Notes

- **Agents must not** edit or delete existing registration or handoff records.
- **Agents must not** backdate records — use real timestamps.
- **Records are append-only** — add new files, never overwrite old ones.
- If a session ends abnormally (crash, timeout), the next agent should note the missing handoff in their registration under `notes`.
- For the handoff template, see `templates/handoff-record.json`.
- For the registration template, see `templates/agent-registration.json`.

---

## Quick Reference: Session Lifecycle

```
Session Start                          Session End
─────────────                          ───────────
1. Read NLT-DEV-OTOI.md                1. Write handoff-record.json → handoffs/
2. Read AGENTS.md                      2. Commit all changes
3. Read CLAUDE.md                      3. Open PR (if applicable)
4. Read docs/active-threads.md         4. Update docs/active-threads.md
5. Write agent-registration.json       5. Self-terminate cleanly
   → registrations/
```

---

*This file is governed by `ORG-DEV-OTOI-1.0.0`. Human authority: Joshua W. Dorsey, Sr.*
