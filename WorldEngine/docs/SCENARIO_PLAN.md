# NLT Fusion World Engine — Scenario Levels Plan

## Overview

Port the 13 scenarios from `neurolift-ai-fusion-org` to UE 5.8 scenario levels.
Each scenario = one DataAsset + one .umap level + Mass Entity behavior.

## Agent Assignments

### Phase 1: Data Model (Cline)
**Goal:** Create `UScenarioDataAsset` that maps Python scenario definitions to UE DataAssets.

**Tasks:**
1. Create `UScenarioDataAsset` UCLASS with:
   - ScenarioId (FName)
   - DisplayName (FText)
   - Description (FText)
   - Category (enum: Workplace/Personal/Social/Academic)
   - Duration (float, minutes)
   - Complexity (enum: Low/Medium/High)
   - Aversiveness (float 0-1)
   - CognitiveDemand (float 0-1)
   - BaseSuccessRate (float 0-1)
   - bRequiresSustainedFocus (bool)
   - ContextParams (TMap<FName, FString>)
   - Soft reference to the level (.umap)

2. Create `UScenarioLibrary` UFUNCTION library:
   - GetAllScenarios()
   - GetScenarioById(FName)
   - GetScenariosByCategory(ECategory)
   - LoadAllScenariosFromDisk()

3. Create migration script to auto-generate 13 DataAssets from Python definitions.

**Output:** `Source/WorldEngine/Public/Scenarios/UScenarioDataAsset.h` + `.cpp`, 13 `.uasset` files in `Content/Scenarios/`

---

### Phase 2: Level Design (OpenCode)
**Goal:** Author .umap level for each scenario category.

**Tasks:**
1. Create base level template with:
   - Ground plane
   - Lighting (hemispheric + directional)
   - Player start
   - NavMesh bounds

2. Author 4 category levels:
   - **Workplace** — Office with desks, chairs, computers, meeting room
   - **Personal** — Home with kitchen, bedroom, living room
   - **Social** — Cafe/lounge with tables, chairs, social spaces
   - **Academic** — Classroom/library with desks, bookshelves, whiteboard

3. Each level needs:
   - Spawn points for agents (at least 10 per level)
   - Smart Object slots (desk, chair, computer, etc.)
   - NavMesh for pathfinding
   - Lighting setup

**Output:** 4 `.umap` files in `Content/Scenarios/Levels/`

---

### Phase 3: Systems (Cline)
**Goal:** Wire Mass Entity behavior per scenario type.

**Tasks:**
1. Create `UScenarioManagerSubsystem`:
   - Load scenario by ID
   - Configure agents for scenario
   - Track success/failure metrics
   - Report results

2. Create `UScenarioAgentBehavior`:
   - Map scenario type → StateTree behavior
   - Configure needs decay rate per scenario
   - Set success criteria per scenario

3. Create per-scenario processors:
   - Workplace: Focus decay + interruption events
   - Personal: Motivation decay + routine tracking
   - Social: Anxiety decay + interaction events
   - Academic: Cognitive load + deadline pressure

4. Wire `UNLTDemoGameMode` to use scenarios:
   - Load scenario from DataAsset
   - Spawn configured agents
   - Start scenario-specific simulation

**Output:** `Source/WorldEngine/Public/Scenarios/UScenarioManagerSubsystem.h` + `.cpp`, scenario-specific processors

---

### Phase 4: Integration (Hermes)
**Goal:** Pull it all together and verify it works.

**Tasks:**
1. Verify DataAssets load correctly
2. Verify levels open without crashes
3. Verify agents spawn and behave per scenario
4. Verify headless sim runs 600+ ticks
5. Verify web viewer shows scenario state

---

### Phase 5: QA (Pi)
**Goal:** Test all 13 scenarios in headless sim.

**Tasks:**
1. For each scenario:
   - Load the scenario level
   - Spawn agents
   - Run 600 ticks headless
   - Check for crashes
   - Log agent count, positions, intents
   - Verify determinism (same seed = same result)

2. Write QA report with:
   - Pass/fail per scenario
   - Performance metrics
   - Bug list

---

### Phase 6: Validation (Kilo + Pool)
**Goal:** Verify build, cook, and assets.

**Tasks (Kilo):**
- Build Development Editor
- Cook all scenario content
- Verify load times <30s
- Check for build warnings

**Tasks (Pool):**
- Verify all DataAsset references valid
- Check level geometry is valid
- Validate no missing textures/materials
- Check spawn points are valid locations

---

## Execution Order

```
Phase 1 (Cline) ──→ Phase 2 (OpenCode) ──→ Phase 3 (Cline)
                                         │
                                         ↓
                    Phase 4 (Hermes) ←──┘
                           │
                           ↓
                    Phase 5 (Pi) + Phase 6 (Kilo + Pool)
                           │
                           ↓
                    Phase 4 (Hermes) — Final Validation
```

## Current Status

- [x] Python scenario definitions exist (`neurolift-ai-fusion-org/src/simulation/environment/scenarios.py`)
- [x] C++ Mass Entity fragments exist (`WorldEngine/Source/WorldEngine/Public/Agents/`)
- [x] Simulation subsystems exist (`NLTSimulationSubsystem`, `NLTAgentSpawnerSubsystem`)
- [x] Web viewer exists (`Content/Web/index.html`)
- [ ] **DataAsset system** — needs creation (Phase 1)
- [ ] **Scenario levels** — need authoring (Phase 2)
- [ ] **Scenario behavior** — needs implementation (Phase 3)
- [ ] **Integration** — needs wiring (Phase 4)
- [ ] **QA** — needs execution (Phase 5)
- [ ] **Validation** — needs execution (Phase 6)
