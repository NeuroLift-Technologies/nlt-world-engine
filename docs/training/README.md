# Training README — PPO for Avatar/Aide Pairs

> **Status:** ✅ Complete. UE5 infrastructure in `WorldEngine/Source/WorldEngine`.
> Python training script live at `neurolift-ai-fusion/src/simulation/training/train_nlt.py`.

## How Training Works

### Dual-Policy PPO

Two policies train simultaneously:

1. **Avatar Policy** — learns movement and task-initiation decisions
2. **Aide Policy** — learns when to apply which coaching strategy

They train as paired agents: each Aide observes its paired Avatar's cognitive
state and chooses one of 10 coaching strategies.

### Training Loop (in UE5)

Inside `NLTTrainingManager::Tick()`:

```
every 0.1s (TickInterval):
  └─ Tick cognitive decay (stress rises, focus drops, without coaching)
  └─ Run inference (both policies act)
  └─ Avatar moves + acts (via AvatarInteractor)
  └─ Aide picks strategy → applies to Avatar (via AideInteractor)
  └─ Every 1.0s (TrainingTimer):
     └─ PPOTrainer.RunTraining() — 1 iteration
        - Collects episode records
        - Updates policy + critic networks
        - Logs reward to TensorBoard (via communicator)
  └─ Episode ends when:
     - Independence ≥ 0.8  (Avatar learned!)
     - Burnout ≥ 0.9  (Avatar overwhelmed — fail)
     - 512 steps elapsed (truncation)
```

### PPO Settings

| Parameter | Value | Notes |
|-----------|-------|-------|
| Hidden layers | 1 × 128 | ELU activation |
| Learning rate (policy) | 1e-4 | Slow = stable |
| Learning rate (critic) | 1e-3 | Faster value learning |
| Discount factor (γ) | 0.99 | Long-term reward |
| GAE lambda | 0.95 | Smooth advantage |
| Epsilon clip | 0.2 | PPO trust region |
| Max episode steps | 512 | 51.2 seconds of sim time |
| Fixed timestep | 60 Hz | Deterministic |

### Reward Function

**Avatar reward** (in `NLTTrainingEnvironment::GatherAgentReward`):
```
reward = +1.0 × Independence
         − 1.0 × Burnout
         − 0.5 × Stress
         + 0.3 × Focus
         + 0.5 × SuccessRate
```

**Aide reward** is the same formula applied to the paired Avatar — the Aide
is rewarded when its coaching improves the Avatar's cognitive state.

### Episode Completion

In `NLTEpisodeManager::CheckCognitiveCompletion`:
- **Independence ≥ 0.8** → episode succeeds (Avatar learned to work independently)
- **Burnout ≥ 0.9** → episode fails early (too much pressure)
- **512 steps** → truncation (scenario ran to time limit)

### Neural Network Assets

Learning Agents requires pre-created NN assets in the Editor. These must be
created via the **Learning Agents Editor** panel:

| Asset name | Input dims | Hidden | Output dims | Role |
|------------|-----------|--------|-------------|------|
| `NN_AvatarPolicy` | 13 | 128×1 ELU | 3 cont + 4 disc | Avatar action selection |
| `NN_AvatarCritic` | 13 | 128×1 ELU | 1 | Avatar value estimate |
| `NN_AidePolicy` | 13 | 128×1 ELU | 10 discrete | Aide strategy selection |
| `NN_AideCritic` | 13 | 128×1 ELU | 1 | Aide value estimate |

Location: `WorldEngine/Saved/LearningAgents/Assets/`

### Training Modes

| Flag | Behavior |
|------|----------|
| `bRunInference = true` | Policies run every tick (Avatar/Aide act) |
| `bRunTraining = true` | PPO updates run every 1.0s |
| Both true | Full training: act + learn |
| Inference only | Play back trained policies (no updates) |

### Python Side (TODO — Phase 3)

The Python training orchestrator needs to be built at:
`neurolift-ai-fusion/src/simulation/training/train_nlt.py`

It will:
1. Connect to UE's shared-memory communicator on port 5555
2. Receive observations (13-dim float arrays per agent)
3. Send action probabilities + sampled actions back
4. Send rewards (computed by `NLTTrainingEnvironment::GatherAgentReward`)
5. Log to TensorBoard at `Saved/LearningAgents/TensorBoard/`

### Running Training

**Step 1 — Build:**
```bash
cd WorldEngine && make WorldEngineEditor && make WorldEngine
```

**Step 2 — Launch headless training:**
```bash
~/Documents/NLT/Engine/Binaries/Linux/UnrealEditor \
  WorldEngine.uproject \
  -nullrhi -game -server -log \
  -MAP=/Game/Scenarios/Levels/Workplace_Level.Workplace_Level
```

**Step 3 — Run PPO (when Python script exists):**
```bash
python3 ../../neurolift-ai-fusion/src/simulation/training/train_nlt.py \
  --port 5555 --agents 1 --iterations 500
```

**Step 4 — Monitor:**
```bash
python3 -m tensorboard --logdir=Saved/LearningAgents/TensorBoard --port 6006
```

Open http://localhost:6006 → look for:
- `Reward/Avatar` and `Reward/Aide`
- `Independence/Avatar` (should trend upward over iterations)
- `EpisodeLength` (should increase as Avatar learns)

---

## Files to Know

| File | Role |
|------|------|
| `WorldEngine/Source/WorldEngine/Public/Agents/NLTTrainingManager.h` | Orchestrator — spawns pairs, owns trainers |
| `WorldEngine/Source/WorldEngine/Private/Agents/NLTTrainingManager.cpp` | BeginPlay/Tick — sets up everything |
| `WorldEngine/Source/WorldEngine/Public/Agents/NLTAvatarInteractor.h` | 13-dim obs + 3+4 action schema |
| `WorldEngine/Source/WorldEngine/Public/Agents/NLTAideInteractor.h` | 13-dim obs + 10 strategy action schema |
| `WorldEngine/Source/WorldEngine/Public/Agents/NLCognitiveStateComponent.h` | 7-dim cognitive state, coaching effects |
| `WorldEngine/Source/WorldEngine/Public/Agents/NLTEpisodeManager.h` | Step tracking, cognitive completion check |
| `WorldEngine/Source/WorldEngine/Public/Agents/NLTTrainingEnvironment.h` | Reward + completion computation |
| `WorldEngine/Source/WorldEngine/Public/Scenarios/UScenarioDataAsset.h` | Scenario definitions (.uasset) |
| `neurolift-ai-fusion/src/simulation/environment/scenarios.py` | 13 Python scenario definitions |
