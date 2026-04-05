# Agent Orchestration Guide

> This document describes how AI agents coordinate and communicate within the NeuroLift AI-Fusion system.
>
> **Status:** Stub — full content to be developed. See `README.md` for context.

---

## Agent Hierarchy

### Executive Level (3 Agents)
- **CFO Agent** — Financial strategy, planning, and oversight
- **CTO Agent** — Technical strategy, architecture, and innovation
- **CMO Agent** — Brand strategy, marketing, and growth

### Department Level (12 Agents)

**Business Development (4):**
- Sales Agent
- Marketing Agent
- Partnership Agent
- Investor Relations Agent

**Operations (4):**
- Legal Agent
- HR Agent
- Project Management Agent
- Customer Success Agent

**Technical (4):**
- Product Manager Agent
- QA Agent
- DevOps Agent
- Security Agent

---

## Simulation Agent Roles

Within the simulation training environment:

| Agent Role | Function |
|---|---|
| **Avatar** | Embodies a specific ADHD trait; experiences authentic struggle scenarios |
| **Aide** | Coaches the Avatar in real-time within the simulation |
| **Advocate** | Fusion product — combines Avatar's lived understanding + Aide's expertise |

---

## Communication Protocol

All agents:
1. Register at session start (`docs/agent-log/registrations/`)
2. Read `docs/active-threads.md` before any action
3. Escalate blocked or out-of-scope decisions to Joshua W. Dorsey, Sr.
4. File a handoff record at session end (`docs/agent-log/handoffs/`)

---

## Governance Reference

All agents operate under `ORG-DEV-OTOI-1.0.0`. See `CLAUDE.md` for the full session protocol and escalation triggers.

---

*For orchestration questions, escalate to Joshua W. Dorsey, Sr. (`info@neuroliftsolutions.com`).*
