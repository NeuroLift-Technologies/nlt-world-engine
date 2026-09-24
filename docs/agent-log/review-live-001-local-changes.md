# Local Changes Review — nlt-world-engine (LIVE-001)

**Reviewer:** Hermes
**Review Date:** 2026-09-18
**Review Type:** Code
**Scope:** All uncommitted local changes (modified + untracked files) on `main`
**OTOI Version:** ORG-DEV-OTOI-1.0.3

---

## Pre-Review Checklist

- [x] Read NLT-DEV-OTOI.md and understood governance requirements
- [x] Identified the review scope and what is being evaluated
- [x] Checked active threads in `docs/active-threads.md` (LIVE-001)
- [x] Verified the review format matches this template
- [x] Actually ran all tests to verify agent claims (see Factual Accuracy below)

---

## Review Findings

### Summary

The uncommitted changes implement LIVE-001 ("Live Sims world: Python ECS + Agent API + three.js viewer"). The design is clean and the architecture is sound: a new `server.py` wraps the existing Python ECS kernel with WebSocket + REST, a `live-client.js` bridges live state onto the existing three.js viewer, `connectors/` provide scripted and LLM-driven bot entry points, and `src/simulation/training/` adds a gymnasium-compatible RL environment with a faithful port of the UE cognitive model.

However, the agent claimed "9/9 server tests passing" in `active-threads.md`. Reality is **8/9** — `test_live_server_end_to_end` fails on this machine. This is a factual inaccuracy that must be corrected before commit. There are also CRLF line endings introduced across multiple files, and the viewer JS (`main.js` / `iso-world.js`) was rewritten wholesale rather than diffed — making review harder and raising the risk of regressions in offline mode.

### Strengths

- **Zero engine reuse debt** — `server.py` correctly drives the existing `WorldEngine` through its public seams (`AgentInterface`, `UtilityAgent`, `emit_contract_snapshot`) rather than duplicating logic. ADR-001 is well-justified.
- **Clean separation of concerns** — `LiveWorld` owns the sim thread + sessions, `WorldServer` owns the network layer, `WorldSession` wraps one avatar. The threading boundary is respected (engine mutation only on the sim thread).
- **Protocol design is solid** — WS protocol with `join` / `perceive` / `act` / `status` / `observe` / `ping` + REST snapshots is language-agnostic and matches the contract-v1 boundary.
- **Connectors are well-factored** — `scripted_bot.py` mirrors `UtilityAgent` behavior remotely; `llm_connector.py` separates `PromptBuilder` from `decide()` so model swaps are trivial.
- **RL layer is faithful** — `cognitive.py` ports the 7-dim cognitive model, 10 coaching strategies, decay rates, and reward weights verbatim from the UE C++ source. The `WorldEnv` accepts dict/list/tuple actions and auto-detects gymnasium availability.
- **Tests are thorough** — `test_server.py` covers permissions, validation, WS flow, contract shape, and a live e2e round-trip. `test_training_env.py` covers determinism, burnout/independence termination, max-steps truncation, and the `make_env` factory.
- **Docs are present** — `adr-live-world.md` records three ADRs concisely; `requirements-training.txt` keeps RL deps clearly separated from the stdlib kernel.

### Issues

#### 🔴 Critical (must fix before merge/publish)

| # | File:Line | Issue | Recommended Fix |
|---|-----------|-------|-----------------|
| 1 | `tests/test_server.py:316` | `test_live_server_end_to_end` **fails** — agent claimed "9/9 passing" in `active-threads.md`. Actual run: `8/9 passed`. The `broadcast_pump` sends `you` messages only for controlled avatars, but the test's `got_you` check may race against tick delivery, or the spectator `observe` path may not trigger `you` broadcasts. | Fix the race / broadcast logic so `you` messages are reliably received. Then re-run and confirm 9/9 green before updating `active-threads.md`. |
| 2 | `docs/active-threads.md:12` | The "Delivered" line claims "9/9 server tests passing incl. live end-to-end round-trip." This is **false** — see Issue #1. | Update to reflect actual test status, or fix the tests first. |

#### 🟡 High Priority (should fix soon)

| # | File:Line | Issue | Recommended Fix |
|---|-----------|-------|-----------------|
| 3 | `.gitignore` (all lines) | CRLF line endings (`\r\n`) introduced. Repo previously used LF. This will cause noise in future diffs and may trip Windows/Unix cross-dev workflows. | Run `dos2unix .gitignore` or `git add --renormalize .gitignore`. |
| 4 | `world-engine/requirements.txt` | Same CRLF issue as above. | Same fix. |
| 5 | `world-engine-3d/index.html`, `iso-world.js`, `main.js`, `live-client.js`, `assets.js` | CRLF endings on all new/modified JS/HTML files. | `dos2unix` or renormalize all affected files. |
| 6 | `world-engine-3d/main.js` | The diff is a **full rewrite** (574 → 679 lines). Offline-mode rendering changes (new furniture meshes, new materials, walk-cycle animation, live/offline branching) are bundled together, making it impossible to review the offline path in isolation. | Consider splitting offline vs. live rendering changes into separate commits, or at minimum flag this in the commit message so reviewers know the entire viewer was touched. |

#### 🟢 Low Priority / Observations

- `server.py:300` — `engine.current_state.name == "RUNNING"` check on every tick adds a tiny bit of string comparison overhead. Not a bug, but worth noting.
- `server.py:303` — `engine._pending_events` is accessed directly (private). Consider a public drain method on the engine if this pattern is used elsewhere.
- `server.py:352` — `from websockets.datastructures import Headers` inside a hot path (`_json_response`) — import should move to module top.
- `live-client.js:143` — `startPoller()` runs even on WS connect failure, so REST polls may hit a server that never comes up. Minor; the `catch` is silent.
- `connectors/scripted_bot.py:106` — `self.busy = bool(msg.get("submitted"))` is set on every `act_result`, even when the action was rejected. The next perception will re-decide, so this is fine, but the naming is slightly misleading.
- `src/simulation/training/train_ppo.py:96` — `progress_bar=False` hides SB3 progress. Fine for headless, but a `--verbose` flag would help.
- `requirements-training.txt:7` — Python 3.14 venv command shown in comments. The repo is on 3.11/3.14; no issue, but worth standardizing.

### Factual Accuracy

- [x] Agent claim "9/9 server tests passing" — **FALSE**. Actual: `8/9 passed`, `test_live_server_end_to_end` fails (see Issue #1).
- [x] Agent claim "2/2 viewer node tests" — **TRUE**. `node --test world-engine-3d/live-client.test.js` passes both.
- [x] Agent claim "17 training tests" — not explicitly stated, but `tests/test_training_env.py` runs 17 tests and all pass.
- [x] No hallucinated organizations, numbers, or URLs in the code or docs.
- [x] ADRs and active-threads entries are internally consistent with the code that was written.

### Governance Compliance

- [x] No credentials or secrets exposed
- [x] No external integrations added without approval (websockets is the only new dep, and it's clearly documented)
- [x] No architecture decisions made without approval — ADRs explicitly defer C# port and GLB asset pipeline to later
- [x] `docs/active-threads.md` updated (though with a factual error — see Issue #2)
- [ ] Commit format not yet applied (uncommitted changes) — ensure `[CLINE] feat(live): ...` format is used
- [ ] Handoff record not yet written — required per OTOI before ending the session

---

## Verdict

**Status:** CHANGES REQUESTED

**Rationale:** The architecture and implementation are solid, but the agent's test-pass claim is inaccurate (8/9, not 9/9). Before committing, the `test_live_server_end_to_end` failure must be fixed or the claim in `active-threads.md` corrected, and CRLF line endings should be normalized across all changed files. The full-rewrite nature of `main.js` / `iso-world.js` should be called out explicitly in the commit message so reviewers understand the scope of viewer changes. Once the test is green and line endings are fixed, this is ready to commit.

---

## Handoff Notes

**Next reviewer / agent needs to know:**
- The `test_live_server_end_to_end` failure is a real race/broadcast issue in `server.py` — not a flaky test. The agent should investigate why `you` messages aren't reaching the test client within the broadcast loop.
- CRLF endings need normalization across ~8 files before commit.
- Offline-mode viewer changes in `main.js` should be smoke-tested (`python -m http.server` + open `index.html`) to confirm the non-live path still renders correctly.
- `docs/active-threads.md` needs the "Delivered" line corrected to reflect actual test status.
- A handoff record should be written to `docs/agent-log/handoffs/` per OTOI Section 5 before the session ends.

---

*This review was conducted following the format defined in `REVIEW.md` under ORG-DEV-OTOI-1.0.3.*
