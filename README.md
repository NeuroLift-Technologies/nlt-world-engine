# NLT Fusion — World Engine

NeuroLift Technologies Simulation Environment (the game/simulation **engine**)

```yaml
ai_assistant_directive:
  priority: 1
  instruction: "Before performing any development or coding tasks, read NLT-DEV-OTOI.md."
  description: "NLT-DEV-OTOI.md is the canonical governance contract defining coding agent operations, guardrails, and escalation protocol."
  required_file: "NLT-DEV-OTOI.md"
```

A Sims/RPG-style **simulation environment** — the deterministic runtime that AI Avatars (with ADHD traits) and AI Aides live inside. This repo owns the **environment only**: world state, space, time, objects, sims-style needs, NPCs, and scenario instantiation. The Avatar/Aide/Advocate *intelligence* — ADHD trait modeling, Aide coaching expertise, the training loop, and fusion into Advocates — lives in the sibling platform `neurolift-ai-fusion` and connects to this engine through the agent interface.

## ℹ️ What nlt-fusion is / is not

**nlt-fusion IS** the **World Engine**: a deterministic, Sims-style simulation environment, a provider-neutral transport + deterministic replay contract (`world-engine/contracts/v1/`), an agent interface (perceive → submit intent → poll result), browser/Studio prototypes that visualize the world, and the **Unreal Engine 5.8 physical substrate** that renders the world at human scale.

**nlt-fusion is NOT** the Avatar/Aide/Advocate AI stack. ADHD trait modeling, Aide coaching intelligence, the experiential-learning training loop, and fusion-into-Advocate mechanics are **not** implemented here.

**For the full platform built around this engine** — the web (Next.js), mobile (Expo), and API (FastAPI) surfaces plus the Cloudflare Worker and Supabase backend that turn the Avatar → Aide → Advocate simulation into a deployable product — see the **`neurolift-ai-fusion`** repository, NeuroLift's Full-Stack Avatar-Aide-Advocate Training Platform. (The platform embeds its own self-contained simulation engine; this repo is the standalone engine implementation of the same concept.)

🎯 Project Vision
Mission: "Nothing About Us Without Us" - neurodivergent voices lead development

This engine exists to make experiential learning *possible* for AI systems, not to perform it. It supplies the authentic environment — struggles, stress, mistakes, and real consequences — that Avatars live through and Aides coach within. The Avatar's learning and the Aide's coaching expertise are owned by `neurolift-ai-fusion`; this repo provides the deterministic world they run in.

Core Innovation
Nobody else is training AI this way. While the industry has solved infrastructure (MCP, A2A protocols), two critical gaps remain:

User preference enforcement: UNSOLVED ← OTOI addresses this
AI capability reliability: UNSOLVED (38.1% computer use accuracy, 85% agentic AI failure rate)
The broader simulation approach addresses both gaps through authentic experiential learning. nlt-fusion's role in that approach is the environment layer: it produces the realistic, consequence-bearing scenarios that learning depends on. The learning/coaching/fusion logic itself lives in `neurolift-ai-fusion`.

🏗️ Architecture Overview
This repo implements the **environment** layer of the Avatar-Aide-Advocate process. The full four-phase process below is documented here for context, but only the simulation environment (Phase 3's world, and the seams that connect to it) is owned by this repo. Avatar creation, Aide intelligence, and fusion live in `neurolift-ai-fusion`.

The Avatar-Aide-Advocate Process (context — owned by `neurolift-ai-fusion`)
Phase 1: Avatar Creation *(owned by `neurolift-ai-fusion`)*
Each Avatar embodies a specific ADHD trait/executive function deficit
Experiences authentic stress, frustration, and failure patterns
Lives through simulated everyday scenarios where their specific trait creates challenges
Makes real mistakes with real consequences in the virtual environment
Phase 2: Aide Development *(owned by `neurolift-ai-fusion`)*
Foundation Components:

RRT (Rapid Response Team) Core - Pre-existing therapeutic knowledge with dormant burnout response
PhD-Level Expertise - Deep academic research on specific executive functions
Real-World Feedback - Input from people with ADHD who've mastered that specific area
Role: Coach, therapist, and assistant operating IN the simulation environment alongside the Avatar

Phase 3: Simulation Training *(the environment is owned by THIS repo; the training/learning logic is owned by `neurolift-ai-fusion`)*
Environment: Sims/RPG-style virtual world with realistic consequences — **this is what nlt-fusion provides.**

Scenario Categories:

Workplace: HR compliance, meetings, project management, performance reviews
Personal: Household management, social relationships, financial tasks, self-care
Social Dynamics: Rejection sensitivity, emotional regulation, social cues
Key Environmental Features:

Neurotypical NPCs: Complete same tasks easily, creating realistic social comparison
Biased NPCs: Exhibit workplace discrimination, microaggressions, ableism
Random Dysfunction Injection: Suddenly adds new executive function challenges
Real Consequences: Failed tasks have meaningful impact, creating authentic learning pressure
Phase 4: Fusion into Advocate *(owned by `neurolift-ai-fusion`)*
When: After Avatar demonstrates consistent independence across scenarios
How: Combine Avatar's experiential struggle awareness with Aide's proven expertise
Result: An Advocate that both understands what ADHD struggles feel like AND knows what actually works

🎮 The 19 Avatar-Aide-Advocate Pairs (data references, not implementations)
The trait/coaching *intelligence* for these pairs lives in `neurolift-ai-fusion`. Within this repo, avatar IDs appear only as **data stubs** that the browser/Studio prototypes use to populate the world (see `world-engine/data.js`). The list below documents the roster those stubs reference:

Executive Function Focused (16 pairs):
StayAlert - Sustained attention deficit
ImpulseGuard - Impulsivity control
FocusFlow - Hyperfocus management
Timely - Time blindness
MemoryMate - Working memory deficits
MoodEase - Emotional regulation
TaskKickstart - Task initiation difficulty
CalmCore - Low frustration tolerance
Planner Pro - Prioritization and planning
SmoothSwitch - Transition difficulties
AwareMate - Self-monitoring challenges
SteadyMind - Poor impulse control
FocusRecharge - Effortful focus fatigue
EffortAlign - Effort vs. productivity perception
Non-Executive Function (3 pairs):
StressShield - Stress sensitivity
SensoryBalance - Sensory sensitivity
SocialSync - Social challenges
SensorySeeker - Sensory seeking behavior
ConfidenceCoach - Self-esteem and identity
## Quick Start

### 🎮 Unreal Engine 5.8 World Engine (physical substrate)

The UE 5.8 project is the physical substrate for the NLT Fusion simulation. It renders the world at human scale with deterministic simulation.

**Prerequisites:** UE 5.8 installed at `~/Documents/NLT/Engine/`, Linux (Clang 20.1.8)

```bash
cd WorldEngine

# Build editor target (85s)
make WorldEngineEditor

# Build game target (22s)
make WorldEngine

# Run headless sim (no GPU needed)
~/Documents/NLT/Engine/Binaries/Linux/UnrealEditor-Cmd \
  -project=WorldEngine.uproject \
  -nullrhi -game -unattended -log \
  -MAP=/Game/Scenarios/Levels/Workplace_Level.Workplace_Level
```

**Project structure:**
```
WorldEngine/
├── Source/WorldEngine/          # All C++ source (Public + Private)
│   ├── Public/                  # Headers for all NLT subsystems
│   │   ├── Agents/              # NLTAgentTrait, NLTAgentSpawnerSubsystem
│   │   ├── Core/                # NLTEventBus, NLTFusionCore, NLTSimulationClock
│   │   ├── Simulation/          # NLTSimulationSubsystem, NLTDeterministicSeedSubsystem
│   │   ├── Scenarios/           # UScenarioDataAsset, UScenarioManagerSubsystem
│   │   ├── Audio/               # SoundscapeSubsystem
│   │   └── World/               # NLTSmartObjectWorldSubsystem, NLTWorldGenerator
│   └── Private/                 # Implementation files
├── Content/
│   ├── Scenarios/
│   │   ├── Levels/              # Workplace_Level, Personal_Level, Social_Level, Academic_Level
│   │   ├── Workplace/           # 5 scenario DataAssets (Wor_wp_1..5)
│   │   ├── Personal/            # 4 scenario DataAssets (Per_pers_1..4)
│   │   ├── Social/              # 2 scenario DataAssets (Soc_soc_1..2)
│   │   └── Academic/            # 2 scenario DataAssets (Aca_acad_1..2)
│   ├── Environment/Materials/   # 12 shared materials (MI_Wood_Desk, MI_Chair_Teal, etc.)
│   ├── Audio/Soundscape/        # Ambient WAV beds (HVAC, Fridge, Clock, Murmur)
│   ├── Kits/Workplace/          # Blender-exported FBX kits
│   └── Web/                     # 2D canvas viewer
├── Config/                      # DefaultEngine.ini, DefaultGame.ini, MCP settings
├── Scripts/                     # Python scripts for scenario creation, QA, lighting
├── Skills/                      # Skill definitions
└── docs/                        # WEB_VIEWER.md, SCENARIO_PLAN.md, DEMO_SETUP.md
```

**Key subsystems (C++):**
- `NLTSimulationClockSubsystem` — authoritative clock, timestep, time-of-day
- `UNLTEventBus` — 256-entry ring buffer, multicast delegates, env events
- `NLTDeterministicSeedSubsystem` — per-category RNG streams from master seed
- `NLTRoomStateSubsystem` — room-state persistence + serialize
- `UNLTAgentSpawnerSubsystem` — Mass Entity agent spawning
- `UScenarioManagerSubsystem` — scenario runtime manager
- `SoundscapeSubsystem` — 4 ambient audio beds tied to scenario stress

**Environment-only work completed:**
- 4 human-scale observation cameras (160cm) per map + CaptureViewport QA pipeline
- Time-of-day lighting: 08:00 (fluorescents + monitor glow) vs 21:00 (evening practicals)
- Soundscape beds: HVAC hum, fridge murmur, clock tick, distant murmur
- Niagara ambient VFX: dust motes, HVAC airflow, steam, rain (22 systems)
- Environmental storytelling: 128 props + 11 stateful systems
- Seeded micro-variation: 8 moods, per-domain sub-seeds
- Per-map polish: 98 items, NavMesh updated, 80 furniture pieces
- Blender desk kit: 3 visual states (clean/cluttered/after-hours)

### 🌐 World Engine v2 — Babylon.js viewer

The **v2 frontend prototype** is a Babylon.js + Vite + TypeScript set of scenes that visualizes a pair's simulated world in real time.

```bash
cd world-engine-v2
npm install
npm run dev          # -> http://localhost:5173
npm run build        # production build (runs `tsc && vite build`)
```

Architecture & deployment are documented in [`ARCHITECTURE.md`](./ARCHITECTURE.md) and [`DEPLOYMENT.md`](./DEPLOYMENT.md) (per-pair Durable Objects, WebSocket fan-out, Vercel + Cloudflare split).

### 🐍 v1 Python ECS engine

**Prerequisites:** Python 3.10+, Git

The environment engine uses only the Python standard library; the only `requirements.txt` (in `world-engine/`) lists dev tools (`flake8`, `pytest`).

```bash
cd world-engine
pip install -r requirements.txt
python3 demo.py
python3 -m unittest discover tests
```

**Installation** (clone):
```bash
# Clone the repository
git clone <repository-url>
cd nlt-fusion

# (Optional) install dev tooling used by tests/lint
pip install -r world-engine/requirements.txt
```

Running the simulation engine
The actual engine runs from `world-engine/`:

```bash
cd world-engine

# Watch an agent autonomously live a full day (eat, chat, sleep, shower, watch TV)
python3 demo.py

# Run the engine test suite
python3 -m unittest discover tests
```

`demo.py`'s `UtilityAgent.decide()` is the seam where an LLM controller (from `neurolift-ai-fusion`) replaces the rule-based one without touching the engine. Decision logic stays outside the tick.

Running the browser / Studio prototypes
No build step — any static file server works:

```bash
# Browser world-engine prototype
cd world-engine
python3 -m http.server 8765
# then open http://127.0.0.1:8765/

# Product-facing Studio shell (run from the repository root)
python -m http.server 8765
# then open http://127.0.0.1:8765/studio/
```

The browser prototype and Studio are **visualization shells**: they tick a simulation locally in the browser and are **not wired** to the Python engine yet. See `world-engine/README.md` and `studio/README.md`.

Running the Babylon.js v2 prototype (world-engine-v2)
A second-generation viewer built with Babylon.js + Vite + TypeScript. Same visualization-shell caveat as above — it is **not wired** to the Python engine yet.

```bash
cd world-engine-v2
npm install
npx tsc --noEmit   # type-check
npm run dev        # Vite dev server
```

Design docs for the v2 direction (pair-per-world MMO topology, Cloudflare Workers + Durable Objects backend, deployment split): see `ARCHITECTURE.md` and `DEPLOYMENT.md`.

🔁 CI and Repository Automation Workflows (GitHub Actions)
Intent and architecture
This repository currently has three automation workflows in .github/workflows/:

Workflow file	Actions UI name	Role	Job flow
.github/workflows/shared-ci.yml	Shared CI	Organization-standard checks via reusable workflows in NeuroLift-Technologies/nlt-fusion	lint -> (test, security)
.github/workflows/python-app.yml	Python application	Local baseline checks defined in this repository	single build job (checkout -> setup python -> install -> flake8 -> pytest)
.github/workflows/pr-cleanup.yml	PR Cleanup	Repository hygiene: marks stale PRs, auto-closes stale PRs, and deletes merged source branches	stale-prs + delete-merged-branches
Both CI workflows currently use Python 3.10.

Trigger behavior and constraints
shared-ci.yml and python-app.yml run on:

push to master
pull_request targeting master
workflow_dispatch (manual run from the Actions tab)
pr-cleanup.yml runs on:

a daily schedule (cron: 0 6 * * *, 06:00 UTC)
workflow_dispatch with optional inputs:
days_before_stale (default 30)
days_before_close (default 7)
Important constraints:

A push to a non-master branch does not auto-run CI unless you open a PR to master or trigger manually.
Because both CI workflows subscribe to the same events, a PR to master runs both pipelines.
PR cleanup staleness currently uses defaults of 30 inactive days before stale, then 7 more days before auto-close (overridable via manual dispatch inputs).
Draft PRs are explicitly exempt from staleness in pr-cleanup.yml (exempt-draft-pr: true).
PR cleanup only targets pull requests (issue staleness is disabled via days-before-issue-stale: -1 and days-before-issue-close: -1).
Branch deletion only applies to branches merged from this repository (not forks), and skips protected/default branches.
Agent automation definitions (.github/agents/*.agent.md)
This repository also includes agent prompt definitions under .github/agents/:

Agent file	Purpose	Current status
.github/agents/pr-cleanup.agent.md	Prompt/spec for PR cleanup reporting behavior (stale PR + merged branch hygiene context)	Active prompt asset
.github/agents/my-agent.agent.md	Generic starter template for defining additional custom agents	Template only
Important constraint:

No workflow in .github/workflows/ currently imports or executes .agent.md files directly. Runtime automation behavior is defined by workflow YAML (plus external automation tooling), while .agent.md files define prompt/behavior expectations.
PR Cleanup runbook (.github/workflows/pr-cleanup.yml)
Subsystems covered:

Stale PR lifecycle (actions/stale@v9)
Marks inactive PRs with stale after configured inactivity.
Closes stale PRs after configured grace period with auto-closed label.
Exempts draft PRs (exempt-draft-pr: true).
Merged branch deletion (actions/github-script@v7)
Scans closed PRs and keeps only merged PRs from this repository (not forks).
Skips protected/default branches (master, main, develop, dev, release) and any branch returned by repos.listBranches(protected: true).
Deletes refs/heads/<branch> and treats HTTP 422 as "already deleted."
Codepath map (source-verified):

Behavior	Workflow codepath	Notes
Stale threshold input	github.event.inputs.days_before_stale || 30	Manual dispatch can override default 30.
Close threshold input	github.event.inputs.days_before_close || 7	Manual dispatch can override default 7.
PR-only scope	days-before-issue-stale: -1, days-before-issue-close: -1	Issues are explicitly excluded.
Merged PR branch filter	pr.merged_at !== null + pr.head.repo.full_name === <current repo>	Excludes fork-origin branches.
Protected branch skip	static set + repos.listBranches(protected: true)	Includes both default names and API-protected branches.
Branch deletion API call	github.rest.git.deleteRef({ ref: "heads/<branch>" })	HTTP 422 is logged as already deleted and not fatal.
Operational constraints and pitfalls:

Branch deletion requires contents: write; stale/close operations require pull-requests: write and issues: write.
The merged-branch cleanup loop reads up to per_page: 100 closed PRs per run.
Fork-origin PR branches are not deleted by design.
Schedule times are UTC; if cleanup appears "late", verify timezone conversion before changing cron.
Manual usage
From GitHub UI:

Open Actions.
Select Shared CI, Python application, or PR Cleanup.
Click Run workflow.
Choose the branch and (for PR Cleanup) optionally override stale/close thresholds.
For manual PR cleanup tuning (PR Cleanup only):

Open Actions -> PR Cleanup -> Run workflow.
Set days_before_stale (default 30) and days_before_close (default 7) if needed.
Run and inspect logs for the stale-prs and delete-merged-branches jobs.
PR cleanup verification checklist:

Confirm the run used the expected days_before_stale and days_before_close values.
In stale-prs logs, verify labels/actions align with the current policy (stale, auto-closed, draft PR exemption).
In delete-merged-branches logs, verify each skip/delete outcome is expected (fork PR, protected branch, or already deleted).
If merged branches remain, check whether the relevant PRs fall outside the current per_page: 100 query window.
To reproduce python-app.yml locally:

python -m pip install --upgrade pip
pip install flake8 pytest
if [ -f requirements.txt ]; then pip install -r requirements.txt; fi
flake8 . --count --select=E9,F63,F7,F82 --show-source --statistics
flake8 . --count --exit-zero --max-complexity=10 --max-line-length=127 --statistics
pytest
Maintenance checklist
Update Python version in both CI workflows together to avoid drift:
.github/workflows/shared-ci.yml -> with.python-version
.github/workflows/python-app.yml -> with.python-version
Keep branch trigger filters aligned in both CI files when changing branch policy.
Treat shared-ci.yml behavior as externally defined: it calls reusable workflows from nlt-fusion at @main.
Do not remove security-events: write from shared-ci.yml unless the reusable security workflow no longer needs upload permissions.
When changing PR retention policy, update both code and docs together:
.github/workflows/pr-cleanup.yml (days-before-stale, days-before-close)
this README section (trigger behavior + runbook defaults)
Protect long-lived branches in GitHub settings so delete-merged-branches can safely skip them using the protected-branch API check.
Do not reduce PR Cleanup write permissions unless stale labeling/closing and branch deletion behavior is intentionally being disabled.
Keep cleanup intent aligned in two places when requirements change:
.github/workflows/pr-cleanup.yml (enforced behavior)
.github/agents/pr-cleanup.agent.md (agent runbook + reporting expectations)
Troubleshooting and common pitfalls
CI did not run: confirm the event targets master, or run with workflow_dispatch.
Shared CI fails before local tests run: inspect reusable workflow logs from nlt-fusion; failures there can occur without changes in this repository.
Security/test ordering confusion: in shared-ci.yml, both test and security depend on lint and can run in parallel after lint passes.
python-app.yml lint behavior seems inconsistent: the first flake8 command fails on syntax/name errors; the second uses --exit-zero and is informational for style/complexity reporting.
PR branch was not deleted after merge: check whether the PR came from a fork, whether the branch is protected, or whether it was already deleted (422 is treated as non-fatal in workflow logs).
PR expected to stay open got marked stale: add any activity (comment/commit/review) or convert to draft if it is actively in progress but intentionally paused.
Local runtime troubleshooting (engine)
For the deterministic smoke path, run from `world-engine/`:
`python3 -m unittest discover tests` (engine test suite) and `python3 demo.py` (a-day-in-the-life agent).
The engine uses only the Python standard library; `world-engine/requirements.txt` adds dev tooling (`flake8`, `pytest`) only.
Note: the training-side scripts (e.g. an interactive training loop / coaching-context runner) are **not part of this repo** — that code lives in `neurolift-ai-fusion`. The 2026-06-09 environment-only scope decision (`docs/active-threads.md`) removed training-side code from nlt-fusion. If you are looking for the training loop, fusion engine, or Avatar/Aide implementations, work in `neurolift-ai-fusion`.

📁 Repository Structure
The real top-level layout of **this** repo (environment engine + visualization shells + governance scaffolding):

```
nlt-fusion/
├── README.md                     # This file
├── NLT-DEV-OTOI.md               # Canonical OTOI governance contract (read first)
├── AGENTS.md                     # Agent guidance
├── CLAUDE.md                     # Repo-specific Claude Code guidance
├── file-structure.md             # File layout reference
├── links.md                      # Reference links
├── mcp-config.yaml               # MCP configuration
├── nltotoi.json / .nltotoi/      # OTOI config + scaffolding
├── SOPs/                         # Standard operating procedures
├── ISSUE_TEMPLATE/               # GitHub issue templates
├── PULL_REQUEST_TEMPLATE/        # GitHub PR templates
├── .github/                      # GitHub workflows + custom agent prompt definitions
│
├── WorldEngine/                  # ★ UE 5.8 PHYSICAL SUBSTRATE
│   ├── WorldEngine.uproject      # UE 5.8 project file
│   ├── Makefile                  # UBT build config
│   ├── Source/WorldEngine/       # All C++ source
│   │   ├── Public/               # Headers (Agents, Core, Simulation, Scenarios, Audio, World)
│   │   └── Private/              # Implementation files
│   ├── Content/
│   │   ├── Scenarios/
│   │   │   ├── Levels/           # 4 level templates (.umap)
│   │   │   ├── Workplace/        # 5 DataAssets (Wor_wp_1..5)
│   │   │   ├── Personal/         # 4 DataAssets (Per_pers_1..4)
│   │   │   ├── Social/           # 2 DataAssets (Soc_soc_1..2)
│   │   │   └── Academic/         # 2 DataAssets (Aca_acad_1..2)
│   │   ├── Environment/Materials/ # 12 shared materials
│   │   ├── Audio/Soundscape/     # Ambient WAV beds
│   │   ├── Kits/Workplace/       # Blender-exported FBX kits
│   │   └── Web/                  # 2D canvas viewer
│   ├── Config/                   # DefaultEngine.ini, MCP settings
│   ├── Scripts/                  # Python scripts (scenario creation, QA, lighting)
│   ├── Skills/                   # Skill definitions
│   └── docs/                     # WEB_VIEWER.md, SCENARIO_PLAN.md, DEMO_SETUP.md
│
├── world-engine/                 # ★ THE ENGINE — deterministic Sims-style runtime
│   ├── README.md                 # Engine + prototype docs (scope: environment only)
│   ├── demo.py                   # "A day in the life" utility-agent demo
│   ├── requirements.txt          # Dev tooling (flake8, pytest); engine is stdlib-only
│   ├── src/
│   │   ├── core/                 # events.py, state_machine.py
│   │   └── simulation/
│   │       ├── environment/      # ecs.py, systems.py, world_builder.py,
│   │       │                     #   world_engine.py, world_map.py, scenarios.py,
│   │       │                     #   agent_interface.py (perceive → intent → result)
│   │       └── npcs/             # base_npc.py
│   ├── tests/                    # test_contracts.py, test_environment.py
│   ├── contracts/                # Provider-neutral transport + deterministic replay
│   │   ├── v1/                   # common/snapshot/action/event/intervention/replay schemas
│   │   └── examples/             # stay-alert-coaching.replay.json fixture
│   ├── app.jsx / sim.jsx / world-view.jsx / hud.jsx / tweaks-panel.jsx
│   ├── data.js                   # Static data: avatar IDs, paired aides, scenarios, rooms, NPCs
│   ├── world.css / index.html    # No-build React/Babel browser prototype
│   └── _drafts/                  # Preserved earlier single-file drafts
│
├── studio/                       # Product-facing Claude Design shell over the world
│   ├── README.md                 # Reuses world-engine/{data.js, sim.jsx, tweaks-panel.jsx}
│   ├── app.jsx / fleet.jsx / fusion.jsx / live-sim.jsx / telemetry.jsx / iso.jsx
│   ├── helpers.jsx / layout.css / nlt.css / index.html
│
├── agents/                       # NLT governance agent prompt definitions
│   ├── nlt-governance-steward.md
│   └── nlt-onboarding-assistant.md
│
├── docs/                         # Working docs
│   ├── active-threads.md         # Records the 2026-06-09 environment-only scope decision
│   ├── python-engine-stub-summary.md
│   ├── agent-log/                # registrations/, handoffs/, intent/
│   ├── escalations/
│   └── research/
│
└── templates/                    # OTOI governance/session templates
    ├── agent-registration.json
    ├── commit-message.md
    ├── escalation.md
    ├── handoff-record.json
    └── intent-log.md
```

The Avatar/Aide/Advocate intelligence directories (`src/avatars/`, `src/aides/`, `src/advocates/`, `src/fusion/`), the business-agent framework, and Cloudflare deploy tooling are **not** in this repo — they live in `neurolift-ai-fusion` (and related platform repos). They were deliberately removed from nlt-fusion in the environment-only refactor (see `docs/active-threads.md`).

🔬 Development Phases
This repo's deliverable is the **environment**. The phases below describe the broader Avatar-Aide-Advocate effort for context; only the environment items are owned here.

Phase 1: Foundation ✅
 Repository structure
Documentation framework
Base classes implementation
Configuration schemas
Phase 2: Simulation Core ✅ *(owned by THIS repo)*
 World engine (deterministic ECS tick loop, seeded RNG, A* pathfinding)
 Time, needs, and consequence systems
 NPC base classes
 Agent interface (perceive → intent → result)
 Provider-neutral transport + deterministic replay contract (`contracts/v1/`)
 **UE 5.8 physical substrate** (headless sim, Mass Entity, scenario levels)
Phase 3: Environment-Only Work ✅ *(owned by THIS repo)*
 Human-scale observation cameras + CaptureViewport QA
 Time-of-day lighting (08:00 vs 21:00)
 Soundscape beds (HVAC, fridge, clock, murmur)
 Niagara ambient VFX (dust, steam, rain, airflow)
 Environmental storytelling props + stateful systems
 Seeded micro-variation (8 moods)
 Per-map polish (circulation, NavMesh, furniture kits)
 Blender desk kit (3 visual states)
Phase 4: Avatar/Aide/Fusion *(owned by `neurolift-ai-fusion`, not this repo)*
 First Avatar-Aide pair prototype, remaining pairs, training loop, scenario library
 RRT burnout response, fusion engine, Advocate validation
 Real-world testing with the neurodivergent community

🛡️ Privacy-First Design
Local Processing: All processing happens locally (exempt during development/training)
No Data Collection: No external data transmission without explicit consent
No Monetization: User data never monetized
Transparent: Clear about what data exists and where
⚠️ Production Requirements: The above 4 principles are non-negotiable for production and end-user use. "Local Processing" may be relaxed during development and training phases only.

🤝 Contributing
This project follows "Nothing About Us Without Us" principles. We welcome contributions from:

Neurodivergent developers and researchers
ADHD specialists and therapists
AI/ML researchers interested in experiential learning
Anyone committed to authentic representation
Formal CONTRIBUTING.md guidance is being drafted; for now, follow the CI workflow and documentation standards in this README, and the OTOI governance contract (`NLT-DEV-OTOI.md`). Note the scope boundary: environment changes belong here; Avatar/Aide/Advocate intelligence changes belong in `neurolift-ai-fusion`.

📚 Documentation
World Engine overview & scope: `worldEngine/docs/WEB_VIEWER.md`
UE 5.8 build & run: `WorldEngine/docs/DEMO_SETUP.md`
Transport + replay contract: `world-engine/contracts/v1/README.md`
Studio shell: `studio/README.md`
Active threads (incl. environment-only scope decision): `docs/active-threads.md`
Python engine stub summary: `docs/python-engine-stub-summary.md`
Governance: `NLT-DEV-OTOI.md`, `AGENTS.md`, `CLAUDE.md`

🌐 Infrastructure & the Full Platform
Production hosting and deployment (Cloudflare Workers/Pages, Supabase, etc.) are **not** part of this repo. There is no `cloudflare/` directory or deploy tooling here; nlt-fusion is a local simulation engine, not a deployed end-product.

Deployment infrastructure for the productized Avatar → Aide → Advocate experience lives in `neurolift-ai-fusion` (and related NLT platform repos such as `neurolift-solutions`). See that repository for the web/mobile/API surfaces and the Cloudflare/Supabase backend.

🏆 Success Criteria
For **this engine**, we'll know we've succeeded when:

Deterministic Ticks: Same seed + same inputs reproduce the same run (to be validated by the draft `contracts/v1/` replay fixtures)
World State Faithful: Space, time, objects, sims-style needs, and NPCs behave consistently across runs
Scenarios Instantiate: The environment authentically represents ADHD challenges as consequence-bearing situations
Agent Interface Stable: A controller can perceive, submit intents, and poll results without touching the tick — and an LLM controller can swap in at the `decide()` seam
Contracts Hold: The provider-neutral transport + replay contract round-trips snapshots, actions, events, and interventions
Documented for Contributors: Any neurodivergent developer can run `demo.py` and the test suite and understand the engine
Human-Scale Rendering: The world is viewable at human eye-height (160cm) with time-of-day lighting, ambient sound, and motion
Environment Feels Occupied: Empty world with no agents still feels lived-in through lighting, sound, VFX, and storytelling props

(Avatar-Aide training success, Avatar learning, and validated fusion/Advocate empathy are success criteria of `neurolift-ai-fusion`, not this engine.)

📞 Contact
Founder: Joshua W. Dorsey, Sr. (ADHD cognitive profile)
Email: neuro.edge24@gmail.com
Website: neuroliftsolutions.com
Previous Domains: neurolifttechnologies.com, .org, .info

Multi-threaded thinker - may switch contexts frequently
Prefers iterative development with frequent check-ins
Values authentic neurodivergent representation

📄 License
[License TBD - Open Source]

This repository is the **environment engine** for a new paradigm in AI training — learning through experience, not just data. The world is here; the learner and the coach connect from `neurolift-ai-fusion`.

🎯 Current Status
Scope: World Engine (environment only). Last Updated: September 2026.
Current focus: UE 5.8 physical substrate with human-scale rendering, time-of-day lighting, ambient soundscape, Niagara VFX, environmental storytelling, and seeded micro-variation. All environment-only work is in progress across 6 agents (Pi, OpenCode, Cline, Kilo, Pool, NLT Agent).
Note: Avatar/Aide/Advocate intelligence, the training loop, and fusion mechanics live in `neurolift-ai-fusion` per the 2026-06-09 environment-only scope decision (`docs/active-threads.md`).
