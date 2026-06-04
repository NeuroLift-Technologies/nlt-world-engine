## Intent Log Entry

**Date:** 2026-06-04
**Agent:** Codex
**Action:** Adopt the supplied NLT Fusion Studio design as a new prototype shell, wire it to the existing canonical browser engine, and document research-backed architecture options.
**Rationale:** The earlier World Engine export is already canonical in the repository. The newer Studio export adds valuable product views without requiring engine replacement or an architecture decision.
**Risks:** The prototype still relies on CDN React/Babel and a browser-local simulation; research references could be mistaken for approved dependencies if their status is unclear.
**Alternatives considered:** Keep the design only in the zip; duplicate the exported engine under `studio/`; overwrite the canonical World Engine; immediately select a game engine or learned world model.
**Escalation needed:** no - no framework, provider, external integration, deployment, or transport architecture is selected.
