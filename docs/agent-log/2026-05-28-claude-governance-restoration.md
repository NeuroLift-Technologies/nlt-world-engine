# Governance Restoration — 2026-05-28

**Agent:** Claude (claude/governance-docs-restore-yB5sI)
**Action:** Restore org-level governance framing over-trimmed by Copilot baseline
**Supersedes:** PR #2 (`governance/otoi-compliance`, Copilot, 2026-05-28)
**Out of scope:** PR #1 (April scaffolding) — unrelated; left alone.

## Context

`nlt-fusion` is part of a coordinated 11-repo cleanup (reference:
[nlt-agent-1 PR #4](https://github.com/NeuroLift-Technologies/nlt-agent-1/pull/4)).
Copilot's PR #2 applied an over-trimmed governance baseline that rewrote
org-level canonical documents to be repository-scoped. This change restores the
canonical org-wide framing while preserving Copilot's valid additions.

Because `main` was a bare skeleton (README only), this branch is based on
Copilot's PR #2 head (`origin/governance/otoi-compliance`) and fixes in place.

## Restored canonical content (from `.github-private`)

- `NLT-DEV-OTOI.md` — reverted to "Organization-Wide" scope, canonical body
- `AGENTS.md` — reverted to "Organization-Wide Internal Gateway", with public
  fallback block (`.github` mirrors)
- `file-structure.md` — three-tier architecture references restored
  (`NeuroLift-Technologies/.github`, `.github-private`)
- `SOPs/repo-governance-setup.md` — canonical v1.1.0
- `SOPs/incident-response.md`, `SOPs/new-agent-onboarding.md` — canonical
- `agents/nlt-governance-steward.md`,
  `agents/nlt-onboarding-assistant.md` — canonical

## Kept from Copilot PR #2

- `README.md` `ai_assistant_directive` block
- `CLAUDE.md` (repo-pointer style; correct pattern for consumer repos)
- `.nltotoi/*` (scoped to local `nlt-fusion`)
- `docs/agent-log/*` additions, `docs/escalations/README.md`
- Templates, ISSUE_TEMPLATE, PULL_REQUEST_TEMPLATE (already canonical)
- `.github/workflows/validate-governance.yml`
- `nltotoi.json` — `repository.name` kept as
  `NeuroLift-Technologies/nlt-fusion`; `purpose` kept

## `nltotoi.json` adjustments

- `repository.visibility`: `repository-local` → `private`
- `ethical_framework.public_governance`:
  `https://github.com/NeuroLift-Technologies/nlt-fusion` →
  `https://github.com/NeuroLift-Technologies/.github`

## Validator

`bash .nltotoi/scripts/validate-governance.sh` — **29 passed, 0 failed,
0 warned**.

## Governance

OTOI: `ORG-DEV-OTOI-1.0.0` · Authority: Joshua W. Dorsey, Sr. ·
HAIEF: https://elevaitionfoundation.org
