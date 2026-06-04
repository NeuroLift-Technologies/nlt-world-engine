# World Engine Research and Architecture Options

**Research snapshot:** 2026-06-04
**Status:** Research brief and implementation options; architecture choices require Joshua's approval.

## Local Design Read

The supplied Claude Design exports describe two compatible layers:

1. `World egine (1).zip` contains the canonical browser World Engine plus Python simulation concepts. Its canonical `uploads/world-engine/` files are already present in this repository under `world-engine/`.
2. `nlt-fusion.zip` contains the stronger product shell: Live Sim, Fleet, Fusion, telemetry, and a brighter game-oriented visual system.

The new `studio/` shell now reuses the canonical `world-engine/data.js`, `world-engine/sim.jsx`, and `world-engine/tweaks-panel.jsx`. No Python engine files or canonical browser engine files were overwritten.

## What the Linked Papers Suggest

### Lumine: Agent Controller Pattern

[Lumine](https://huggingface.co/papers/2511.08892) separates fast action from slower reasoning: it observes raw pixels at 5 Hz, produces keyboard/mouse actions at 30 Hz, and invokes reasoning only when needed.

Useful NLT Fusion lesson: treat an intelligent Avatar controller as an adapter with distinct perception, reasoning, and action rates. Do not put model calls inside the deterministic simulation tick. The paper page links a project page, but not an open source repository, so Lumine is currently a research reference rather than an implementation dependency.

### Cosmos-Predict2.5: Optional Learned World Model

[Cosmos-Predict2.5](https://huggingface.co/papers/2511.00062) predicts future world states in video form and supports action-conditioned simulation. NVIDIA publishes [source code](https://github.com/nvidia-cosmos/cosmos-predict2.5) and [2B](https://huggingface.co/nvidia/Cosmos-Predict2.5-2B) / [14B](https://huggingface.co/nvidia/Cosmos-Predict2.5-14B) checkpoints.

Useful NLT Fusion lesson: a learned world model could later generate synthetic rollouts, visualize possible futures, or evaluate policies. It should not replace the inspectable state engine used for therapeutic scenarios, scoring, replay, and auditability.

## Closest Hugging Face Research

| Reference | Why it matters to NLT Fusion |
|---|---|
| [Game-TARS](https://huggingface.co/papers/2510.23691) | Generalist multimodal game agent with a unified keyboard/mouse action space and sparse reasoning. |
| [GameWorld](https://huggingface.co/papers/2604.07429) | Verifiable evaluation of multimodal game agents; useful model for scenario success criteria and replay tests. |
| [World Craft](https://huggingface.co/papers/2601.09150) | Text-to-executable, visualizable agent worlds; relevant to future scenario authoring. |
| [Agent World Model](https://huggingface.co/papers/2602.10090) | Code-driven synthetic environments and state transitions for agent training. |
| [MineWorld](https://huggingface.co/papers/2504.08388) | Real-time, action-conditioned interactive world model. |
| [Matrix-Game 3.0](https://huggingface.co/papers/2604.08995) | Long-horizon memory for real-time interactive world models. |
| [LingBot-World](https://huggingface.co/robbyant/lingbot-world-fast) | Apache-2.0 interactive world-model checkpoints; useful for later visual-world experiments. |
| [HY-World 2.0](https://huggingface.co/papers/2604.14268) | Interactive 3D world reconstruction/generation; relevant only if NLT Fusion moves into generated 3D spaces. |
| [Survey on LLM-Based Game Agents](https://huggingface.co/papers/2404.02039) | Organizes the field around memory, reasoning, perception/action, and multi-agent coordination. |

## GitHub Landscape

The [game-development topic](https://github.com/topics/game-development) is dominated by general engines and tooling. Relevant options include [Phaser](https://github.com/phaserjs/phaser) for a richer 2D browser playfield, [Babylon.js](https://github.com/BabylonJS/Babylon.js) or [PlayCanvas](https://github.com/playcanvas/engine) for browser 3D, and [SpacetimeDB](https://github.com/clockworklabs/SpacetimeDB) for shared multiplayer state. Choosing any of them would be an architecture decision and is not recommended until the simulation contract is stable.

More directly comparable repositories:

| Repository | Reusable idea |
|---|---|
| [AI Town](https://github.com/a16z-infra/ai-town) | JS/TS multi-agent world with shared state, transactions, simulation, and LLM adapters. |
| [Generative Agents](https://github.com/joonspk-research/generative_agents) | Memory, reflection, planning, and believable social behavior. |
| [Agentshire](https://github.com/Agentshire/Agentshire) | Agent-as-NPC product metaphor, tiered decision modes, status cards, and observable work. |
| [Voyager](https://github.com/MineDojo/Voyager) | Interpretable skill library, automatic curriculum, environment feedback, and self-verification. |
| [Mesa](https://github.com/mesa/mesa) | Deterministic Python agent-based modeling, browser visualization, and analysis tools. |
| [SimWorld Studio](https://github.com/SimWorld-AI/SimWorld-Studio) | AI-native 3D environment authoring and embodied-agent testbed if a future 3D research track is approved. |

## Recommended Boundary

This is a proposal, not an approved architecture decision.

1. **Deterministic simulation kernel** owns world state, time, scenarios, Avatar/Aide state transitions, scoring, and fusion readiness.
2. **Typed contract** exposes snapshots, events, observations, actions, interventions, and replay records.
3. **Controller adapters** support rule-based baselines first, then optional LLM/VLM/game-agent controllers.
4. **Evaluation and replay** make every scenario reproducible and compare controllers against the same evidence.
5. **Renderer shells** such as `world-engine/` and `studio/` subscribe to state and events without owning simulation truth.
6. **Learned world models** remain optional offline or experimental sidecars until they can meet auditability and safety requirements.

## Near-Term Backlog

| Priority | Work | Decision status |
|---|---|---|
| P0 | Preserve and run the supplied Studio shell against the canonical browser engine. | Implemented |
| P1 | Define versioned snapshot, event, action, intervention, and replay schemas. | Draft implemented in `world-engine/contracts/v1/` |
| P1 | Add deterministic replay fixtures and scenario-level evaluation metrics. | First replay fixture and validation tests implemented |
| P2 | Reconcile the browser simulation with the Python engine through an explicit transport. | Human architecture decision required |
| P3 | Add optional rule-based, LLM, and multimodal controller adapters. | Provider/integration approval required |
| P4 | Explore Cosmos, LingBot, or other learned world models for synthetic rollout visualization. | Research track approval required |

## Human-Centered Constraint

The simulation should not present generated ADHD behavior as clinical ground truth. Avatar behavior, coaching effectiveness, and fusion-readiness measures need traceable evidence, expert review, uncertainty labels, and explicit human control.
