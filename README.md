# NLT World Engine — UE 5.8 Authoritative Simulation

NeuroLift Technologies Simulation Environment — the deterministic runtime where AI Avatars (with ADHD traits) and AI Aides live inside. This repo owns the **physical simulation layer**: world state, space, time, objects, needs, NPCs, scenario instantiation, and the Unreal Engine 5.8 authoritative simulation. Avatar/Aide/Advocate *intelligence* — ADHD trait modeling, coaching expertise, training loop, fusion — lives in [`neurolift-ai-fusion`](https://github.com/NeuroLift-Technologies/neurolift-ai-fusion) and connects through the agent interface.

## Architecture

```text
Fusion Runtime (neurolift-ai-fusion)
  ├── Avatar/Aide/Advocate intelligence
  ├── ADHD trait modeling (26-dim)
  ├── Coaching strategies
  ├── Training (PPO via Learning Agents)
  └── Fusion + Advocate logic
        │
        │  WebSocket / HTTP API
        ▼
NLT World Engine (this repo)
  ├── UE 5.8 C++ simulation (WorldEngine/)
  │   ├── Mass Entity population
  │   ├── StateTree behavior
  │   ├── Learning Agents RL training
  │   ├── Smart Objects + NavMesh
  │   ├── Deterministic tick (1Hz)
  │   └── EventBus (256-entry ring buffer)
  ├── Babylon.js v2 viewer (world-engine-v2/)
  └── Python ECS engine (world-engine/) — reference only
```

## Quick Start — Unreal Engine 5.8

**Prerequisites:** UE 5.8 at `~/Documents/NLT/Engine/`, Linux (Clang 20.1.8)

```bash
cd WorldEngine
make configure          # Generate project files
make WorldEngineEditor  # Build editor (~85s)
```

**Run headless simulation:**
```bash
~/Documents/NLT/Engine/Binaries/Linux/UnrealEditor-Cmd \
  -project=WorldEngine.uproject \
  -nullrhi -game -unattended -log \
  -MAP=/Game/Scenarios/Levels/Workplace_Level.Workplace_Level
```

**Run editor:**
```bash
make WorldEngineEditor
# Open WorldEngine.uproject in UE Editor
```

## Project Structure

```text
nlt-world-engine/
├── WorldEngine/
│   ├── WorldEngine.uproject      # Project file
│   ├── Source/WorldEngine/       # C++ module (57 files, 11 subsystems)
│   │   ├── Public/               # Headers
│   │   │   ├── Agents/           # Fragments, spawner, AI controller, character
│   │   │   ├── Core/             # EventBus, FusionCore, SimulationState
│   │   │   ├── Simulation/       # Clock, deterministic seed, room state, atmosphere
│   │   │   ├── Scenarios/        # Data assets, scenario manager, demo game mode
│   │   │   ├── Audio/            # Soundscape subsystem
│   │   │   ├── Persistence/      # Save/load snapshots
│   │   │   ├── World/            # World generator, smart objects, environment
│   │   │   ├── Roles/            # Fusion role manager
│   │   │   ├── Scaling/          # Population LOD scaler
│   │   │   └── Web/              # WebSocket control server
│   │   └── Private/              # Implementation
│   ├── Content/                  # UE assets
│   │   ├── Scenarios/            # 4 level maps + 16 scenario DataAssets
│   │   ├── Environment/Materials/ 12 shared materials
│   │   ├── Audio/Soundscape/      4 ambient WAV beds
│   │   ├── Kits/SimBody/          SimBody skeletal mesh
│   │   ├── Kits/Workplace/        Blender-exported desk kits (3 states)
│   │   ├── PCG/                   Environment scatter
│   │   └── Web/                   2D canvas viewer (index.html)
│   ├── Scripts/                  # Python automation scripts (QA, VFX, scenarios)
│   ├── Skills/                   # Skill definitions
│   ├── Config/                   # DefaultEngine/Game/Input.ini
│   └── docs/architecture/        # Architecture documentation
│       ├── unreal-architecture-assessment.md
│       ├── unreal-simulation-architecture.md
│       ├── fusion-unreal-domain-mapping.md
│       ├── build-documentation.md
│       └── TECHNICAL_DIAGRAM.md
├── world-engine-v2/              # Babylon.js + Vite + TypeScript viewer
├── world-engine/                 # Python ECS engine (reference, not authoritative)
├── ARCHITECTURE.md               # MMO architecture overview
├── DEPLOYMENT.md                 # Cloudflare + Vercel deployment
└── .github/workflows/            # CI (governance + v2 build)
```

## Key Subsystems (C++)

| Subsystem | Purpose |
|-----------|---------|
| `UNLTSimulationSubsystem` | Main tick, mode control (Realtime/Paused/FastForward/SlowMotion/Headless/Replay) |
| `UNLTSimulationClockSubsystem` | Authoritative simulation clock |
| `UNLTEventBus` | 256-entry ring buffer, multicast delegates, 28 event types |
| `UNLTDeterministicSeedSubsystem` | Seeded RNG for reproducibility |
| `UNLTPersistenceSubsystem` | Snapshot save/load |
| `UNLTSmartObjectWorldSubsystem` | Smart object availability + world locations |
| `UNLTRoomStateSubsystem` | Room occupancy + cell state |
| `UNLTAgentSpawnerSubsystem` | Mass Entity agent spawning |
| `UNLTPopulationScaler` | LOD 0-3 population management |
| `UNLTAideInteractor` | Coaching interventions |
| `UNLTAvatarInteractor` | Avatar-world interaction |
| `UNLTTrainingManager` | RL training via Learning Agents plugin |
| `UNLTWebServerSubsystem` | WebSocket + HTTP control API |
| `UNLTAtmosphereSubsystem` | Weather, lighting, time of day |
| `ANLTScenarioManagerSubsystem` | Scenario runtime + DataAsset management |

## UE Plugins Enabled

| Plugin | Purpose |
|--------|---------|
| MassEntity, MassCore, MassSignals, MassEngine, MassCommon | Mass ECS |
| MassSimulation, MassMovement, MassCrowd, MassActors | Mass simulation |
| MassRepresentation, MassSpawner, MassSmartObjects, MassLOD, MassReplication, MassAIBehavior | Mass subsystems |
| LearningAgents, LearningAgentsTraining, Learning, LearningTraining | RL training (PPO) |
| StateTree | Behavior execution |
| SmartObjects | Interactive objects |
| PCG | Procedural content generation |
| Niagara, NiagaraCore | VFX |
| ModelContextProtocol | MCP server |
| ModelingToolsEditorMode, AllToolsets | Editor tools |
| WebSocketNetworking | WebSocket support |
| MetaHumanGenerator, MetaHumanCharacter, MetaHumanCoreML, MetaHumanLiveLink | MetaHuman (optional) |

## Character & Mesh

- `BP_AvatarCharacter` — Blueprint character + SimBody skeletal mesh
- `SM_SimBody_Base` — low-poly humanoid (~179.5cm, Nanite off)
- `AAvatarAIController` — navmesh-based wandering, RL training foundation

## Web Viewer

```bash
cd world-engine-v2
npm install
npm run dev      # http://localhost:5173
npm run build    # production
```

## Python ECS Engine (Reference)

The Python engine in `world-engine/` is a **reference implementation**, not the authoritative simulation. It's retained for data pipeline use and the Babylon.js viewer connection.

```bash
cd world-engine
pip install -r requirements.txt
python3 demo.py              # Watch an agent live a full day
python3 -m unittest discover tests  # Run tests
```

## CI

| Workflow | Triggers | Purpose |
|----------|----------|---------|
| `validate-governance.yml` | push/PR to any branch | Governance validation |
| `world-engine-v2-build.yml` | push/PR touching `world-engine-v2/` | TypeScript + Vite build |

## Documentation

| Document | Location |
|----------|----------|
| Architecture Assessment | `WorldEngine/docs/architecture/unreal-architecture-assessment.md` |
| Unreal Simulation Architecture | `WorldEngine/docs/architecture/unreal-simulation-architecture.md` |
| Fusion → Unreal Domain Mapping | `WorldEngine/docs/architecture/fusion-unreal-domain-mapping.md` |
| Build Documentation | `WorldEngine/docs/architecture/build-documentation.md` |
| Technical Diagram | `WorldEngine/docs/architecture/TECHNICAL_DIAGRAM.md` |
| Demo Setup | `WorldEngine/docs/DEMO_SETUP.md` |
| Scenario Plan | `WorldEngine/docs/SCENARIO_PLAN.md` |
| Web Viewer | `WorldEngine/docs/WEB_VIEWER.md` |
| Architecture Overview | `ARCHITECTURE.md` |
| Deployment | `DEPLOYMENT.md` |
| NLT OTOI | `NLT-DEV-OTOI.md` |
| Onboarding | `ONBOARDING.md` |
| Active Threads | `docs/active-threads.md` |

## License

License TBD — Open Source. See `LICENSE` for details when available.

---

## Contact

**NeuroLift Technologies**

- Website: https://neurolifttech.com
- Founder: Joshua W. Dorsey — joshua.dorsey@neurolifttech.com

- `NLTGovernanceSubsystem` — TOI/OTOI/ASFDK boundary (planned)
- StateTree behavior trees on Mass entities
- Cross-level navigation (rooms → world cells)
- Full Fusion ↔ Unreal WebSocket protocol
- Replay deterministic verification
- LOD transition logic for avatar actors
- Headless server build configuration
- UE5 unit tests (AutomationDriver /AutomationTest framework)
- Build validation in CI