# NLT Fusion → Unreal Engine: Architecture Assessment

**Date:** 2026-09-01  
**Agent:** Hermes  
**Handoff source:** GPT-5.6 Luna Technical Handoff (2026-09-01)  
**Status:** Milestone 0 deliverable  

---

## 1. Repository State Summary

### Unreal Engine Project (`WorldEngine/`)

| Aspect | State |
|--------|-------|
| UE version | 5.8.2 (`~/Documents/NLT/Engine/`) |
| Project file | `WorldEngine.uproject` (433 bytes, minimal) |
| C++ sources | `Source/WorldEngine/` — empty game module stub only |
| Build | ✅ `make configure` and `make WorldEngineEditor` both succeed |
| Content | `Content/Untitled.umap` (empty test level), one PCG asset |
| Plugins enabled | ModelingToolsEditorMode, ModelContextProtocol, AllToolsets |
| Toolchain | Clang 20.1.8, ISPC 1.24.0, UBA enabled |

### Prior Unreal Attempts

| Project | Location | Notes |
|---------|----------|-------|
| `MyProject/` | repo root | UE 5.8, default FirstPerson template, no custom code |
| `MyProject2/` | repo root | UE 5.8, FirstPerson template + MassAI/LearningAgents/HTNPlanner/MassCrowd/MetaHuman plugins, no custom code |

### Existing Fusion World Engine (Babylon.js)

| Component | Location | Status |
|-----------|----------|--------|
| sim.jsx | `world-engine/sim.jsx` | Full tick loop, needs, coaching, events |
| data.js | `world-engine/data.js` | 19 avatars, 12 scenarios, 6 rooms, NPCs |
| world-view.jsx | `world-engine/world-view.jsx` | Babylon.js rendering |
| Python engine | `world-engine/src/` | Stubs only (NotImplementedError) |
| Live sim | `world-engine/sim-live.jsx` | WebSocket-driven live mode |

### Cloudflare Workers Layer

| Component | Location | Status |
|-----------|----------|--------|
| Workers API | `cloudflare-pairs/` | Durable Object per pair |
| Frontend | `world-engine-v2/` | Vercel-deployed pairlist + viewer |

---

## 2. Existing Domain Model Inventory

### Fusion Concepts (from ARCHITECTURE.md + sim.jsx)

| Concept | Current Representation | Notes |
|---------|----------------------|-------|
| Pair | Durable Object | 1 Avatar + 1 Aide |
| Avatar | JS object / DO state | 19 ADHD-trait profiles |
| Aide | JS object / DO state | 1:1 with avatar, coaching strategies |
| Advocate | Post-fusion role | Helps other pairs |
| Room | Grid rect (24×18 iso) | office, meeting, home, phone, lounge |
| Scenario | Task with cog/stress params | 12 scenarios across workplace/personal/social/academic |
| Need | Derived from stress/cogLoad/focus | Implicit — no explicit need field |
| Intent | State machine states | idle, working, drifting, hyperfocus, overwhelmed, coached |
| Tick | 1Hz DO alarm | Broadcast via WebSocket |
| Event | Event feed (TASK_START, FOCUS_DRIFT, COACHING_INTERVENTION, etc.) | 16 event kinds |
| Fusion | Progress metric (0→100%) | Bond + skills threshold |

### Key Metrics in Babylon Sim

```
focus, cogLoad, stress, burnout, independence, fusionReady, successRate
```

---

## 3. Proposed Unreal Mapping

### 3.1 Fusion → Unreal Concept Mapping

| Fusion Concept | Unreal Representation | Owner |
|----------------|----------------------|-------|
| Agent (Avatar/Aide/Advocate) | `FMassEntity` with fragments | Fusion Runtime |
| Agent identity | `FNLTAgentIdentityFragment` | Fusion Runtime |
| Physical location | `FNLTAgentLocationFragment` (or Mass fragment) | Unreal |
| Need | `FNLTAgentNeedsFragment` | Fusion Runtime |
| Intent | `FNLTAgentIntentFragment` | Fusion Runtime |
| Cognitive state | `FNLTAgentCognitiveFragment` | Fusion Runtime |
| Physical movement | `FMassMovementFragment` + NavMesh | Unreal |
| World environment | World Partition cells + PCG | Unreal |
| Smart Object | `FSmartObjectDefinition` + slot annotations | Unreal |
| Simulation tick | `UNLTSimulationSubsystem` | Fusion Runtime |
| Event bus | `UNLTEventBus` (custom) | Fusion Runtime |
| Cognition | `ICognitionProvider` → gateway | Fusion Runtime |
| Governance | `UNLTGovernanceSubsystem` → TOI/OTOI/ASFDK | Fusion Runtime |
| Persistence | `UNLTPersistenceSubsystem` → snapshots | Fusion Runtime |

### 3.2 What Stays in Babylon

The existing Cloudflare Workers + Babylon.js layer **remains the presentation/observer layer**. Unreal becomes an **optional high-fidelity simulation frontend** that connects to the same Fusion state.

```
                    FUSION RUNTIME
                         │
          ┌──────────────┼──────────────┐
          │              │              │
     Cloudflare       Unreal        Analytics
     Workers +       Simulation     Pipeline
     Babylon.js      (new)
     (existing)         │
          │              │
          └──────────────┼──────────────┘
                         │
                    WebSocket
                         │
                    Human Observer
```

### 3.3 Migration Decision

| Babylon Component | Migration Path |
|-------------------|----------------|
| sim.jsx tick loop | Port to `UNLTSimulationSubsystem` C++ |
| data.js (avatars, scenarios, rooms) | Port to UE Data Assets / Data Tables |
| sim-live.jsX WebSocket | Keep — Unreal connects via WebSocket proxy |
| world-view.jsx | Keep for web; Unreal replaces 3D rendering |
| Python engine | Remains separate; Fusion Runtime bridges |

---

## 4. Architectural Conflicts & Risks

### 4.1 Critical: Mass Entity Is the Population Foundation

**Risk:** UE 5.8 Mass Entity + StateTree are not yet production-proven at massive scale. Epic's own demos show ~10k entities comfortably; 50k requires careful LOD management.

**Mitigation:** Follow the handoff's LOD strategy rigorously:
- LOD 0: Full Actor (500 near player)
- LOD 1: Reduced representation (5k nearby)
- LOD 2: Mass simulation (20k regional)
- LOD 3: Abstract simulation (24.5k remote, no physical rep)

### 4.2 Critical: No Actor-Centric Architecture

**Risk:** UE tutorials and most community code assume ACharacter-based AI. Every standard AI Controller, Behavior Tree, and PawnSensing component assumes an Actor exists.

**Mitigation:** 
- Use MassEntity as the simulation layer
- Use StateTree for behavior execution (not cognitive intelligence)
- Actors only for LOD 0 embodied agents
- Smart Objects for world affordances

### 4.3 Important: LLM/Model Coupling

**Risk:** Directly calling LLM APIs from the simulation tick will destroy performance and create non-determinism.

**Mitigation:** 
- Cognition Gateway interface (`ICognitionProvider`)
- Async cognition — requests don't block ticks
- Deterministic mock provider for testing

### 4.4 Important: Determinism vs Unreal

**Risk:** Unreal's physics, garbage collection, and rendering are inherently non-deterministic. Promising perfect determinism is a trap.

**Mitigation:**
- Use seeded RNG for simulation decisions
- Track `RandomSeed + SimulationTick + EventSequence` for reproducibility
- Accept approximate determinism (same seed → same decisions, not same frame times)

### 4.5 Moderate: Linux Build Toolchain

**Risk:** Linux UE development is less documented than Windows. Some plugins (MetaHuman, some ML tools) have limited Linux support.

**Mituation:** The existing WorldEngine project already builds on Linux (Clang 20.1.8, UBA). We're greenfield — no Windows-specific code needed.

---

## 5. Plugin & Dependency Strategy

### Required UE 5.8 Modules (Build.cs)

```
Core, CoreUObject, Engine, InputCore, EnhancedInput
MassEntity
MassGameplay
MassMovement
MassCrowd
StateTree
SmartObjectsModule
PCG
PCGGeometryScriptNavigation
NavigationSystem
GameplayTags
EngineSettings
```

### Project Plugins (already available)

| Plugin | Purpose |
|--------|---------|
| MassAI | Mass + AI integration |
| LearningAgents | RL/training agents |
| HTNPlanner | Hierarchical task network planning |
| MassCrowd | Crowd simulation |
| MetaHuman | High-fidelity characters (LOD 0 only) |
| ModelContextProtocol | MCP server integration |

### Custom Plugin Structure

```
Plugins/NLTFusion/
├── NLTFusionCore/          # Shared interfaces, types
├── NLTSimulation/          # Clock, scheduler, event bus
├── NLTAgents/              # Mass fragments, processors
├── NLTWorld/               # World state, semantic metadata
├── NLTCognition/           # AI gateway, intent handling
├── NLTGovernance/          # TOI/OTOI/ASFDK boundary
├── NLTPersistence/         # Snapshots, replay
├── NLTNetworking/          # Future replication
└── NLTEditor/              # Editor tools, visualization
```

---

## 6. Unresolved Questions

| # | Question | Impact | Recommended Resolution |
|---|----------|--------|----------------------|
| 1 | Should the existing Cloudflare DO remain authoritative, or does Unreal take over simulation? | Architectural fork | DO remains source of truth; Unreal is a high-fidelity visualization + optional simulation node |
| 2 | How many agents must the system actually support? | Scale design | Start with 1k, profile, scale to 10k, defer 50k |
| 3 | Is real-time (30Hz+) simulation required, or is tick-based (1-10Hz) sufficient? | Architecture complexity | Tick-based (1-10Hz) with interpolation for rendering |
| 4 | What is the budget for cloud compute (if headless servers are used)? | Headless architecture | Not yet constrained; profile on consumer hardware first |
| 5 | How does the existing Python engine stub relate to the Unreal implementation? | Duplicate effort | Python remains offline/training; Unreal is runtime. Bridge via gRPC or shared data |
| 6 | Is there a specific gamefeel/visual quality bar for LOD 0 agents? | Art pipeline | Start with primitive shapes; MetaHuman only for final demo |

---

## 7. Recommended First Steps

1. **Build the NLT plugin skeleton** — C++ modules with proper dependency graph
2. **Implement UNLTSimulationSubsystem** — tick clock, lifecycle, event bus
3. **Create first Mass agent** — identity + location + intent fragments
4. **Build semantic world** — one room, Smart Object, navigation
5. **Connect to Fusion** — deterministic mock cognition, real event flow

---

## 8. Conclusion

The handoff architecture is **sound and achievable**. The key insight — Fusion owns semantic reality, Unreal owns physical reality — is correct and should be defended rigorously.

The existing WorldEngine UE project is a clean empty shell. The toolchain works. The prior attempts (MyProject, MyProject2) are disposable scaffolding.

The Babylon.js prototype is the reference implementation for simulation logic. Its domain model (19 avatars, 12 scenarios, needs/intent/coaching) maps cleanly to UE Data Assets.

**The riskiest element is Mass Entity + StateTree at scale.** We should prove the architecture with 1-10 agents first, then scale aggressively with profiling at every step.

The deliverables in Section 40 of the handoff are achievable in this order:
1. Architecture Assessment ← (this document)
2. Unreal Architecture ← (next)
3. Domain Mapping ← (next)
4. Initial Technical Prototype ← (Milestones 1-3)
5. Build Documentation ← (alongside)
