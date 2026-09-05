# Neurodivergent Developer Guide — World Engine

> This guide is written for ADHD and autistic developers who want to understand
> the NLT World Engine. It uses plain language, clear structure, and visual
> metaphors. Take breaks — your brain needs them.

---

## What This System Does — In One Paragraph

The **World Engine** is a virtual world where AI Avatars with ADHD-like traits
live through scenarios (like writing an email or grocery shopping). An **Aide**
AI watches the Avatar and offers coaching strategies. They both learn together
through **PPO training** — the Aide learns when to intervene, the Avatar learns
to finish tasks with less help. Your job, as a developer, is to make this world
realistic, understandable, and kind.

---

## The Big Picture (Visual)

```text
┌─────────────────────────────────────────────┐
│  Unreal Engine 5.8  (the World)             │
│                                            │
│  ┌─────────────┐  ┌─────────────┐        │
│  │   Avatar    │  │    Aide     │        │
│  │  (learner)  │  │  (coach)    │        │
│  │             │  │             │        │
│  │ Cognitive   │  │ Observes    │        │
│  │ State       │  │ Avatar's    │        │
│  │ (7 dims)    │  │ state +     │        │
│  │             │  │ picks       │        │
│  │ Moves, acts │  │ strategy    │        │
│  └──────┬──────┘  └──────┬──────┘        │
│         │                │                │
│         ▼                ▼                │
│  ┌────────────────────────────────────┐   │
│  │    LearningAgentsManager +        │   │
│  │    PPOTrainer (runs in UE)         │   │
│  └────────────────────────────────────┘   │
│         │                │                │
│         ├────────────────┤                │
│         │ Shared Mem.    │                │
│         │ Communicator   │                │
│         └──────────────┘                │
└─────────────────┬────────────────────────┘
                  │
                  ▼
┌────────────────────────────────────────┐
│  Python Training Process               │
│  (PyTorch PPO)                        │
│                                        │
│  Reads: observations                   │
│  Writes: actions + rewards             │
│                                        │
│  TensorBoard logs →                  │
│  Saved/LearningAgents/TensorBoard/     │
└────────────────────────────────────────┘
```

---

## Key Concepts — No Jargon

### What is PPO?

**PPO = Proximal Policy Optimization.** Think of it as a very patient teacher:
1. It tries something (an action)
2. It sees if the outcome is good or bad (reward)
3. It does a tiny adjustment to get better next time
4. Repeat 1,000 times

PPO is chosen because it’s stable — it doesn’t forget everything after each
try. It’s like slowly adjusting a recipe instead of starting from scratch each
time.

### What is an "Agent"?

An **Avatar** is the character living the ADHD experience. An **Aide** is the
coaching AI that helps the Avatar. They are both agents — they both learn.

### What is a "Scenario"?

A scenario is a realistic situation — like "Email Processing" (20 emails, 30
min, some interruptions) or "Deadline Crunch" (urgent task, high pressure).
Each scenario has an `aversiveness` score (how stressful it feels) and a
`cognitive_demand` score (how much mental effort it needs).

### What are the 7 Cognitive Dimensions?

These live in `LTCognitiveStateComponent.h`. Each Avatar has all 7, all the
time:

| Dimension | What it means | Range |
|-----------|--------------|-------|
| **Focus** | How locked-in you are | 0.0 – 1.0 |
| **CognitiveLoad** | Mental bandwidth used | 0.0 – 1.0 |
| **Stress** | Pressure/anxiety level | 0.0 – 1.0 |
| **Burnout** | Exhaustion risk | 0.0 – 1.0 |
| **Independence** | How much you need help | 0.0 – 1.0 |
| **FusionReady** | Preparedness to engage | 0.0 – 1.0 |
| **SuccessRate** | Recent completion rate | 0.0 – 1.0 |

### What are the 10 Aide Strategies?

The Aide picks one strategy per decision point. These map to real ADHD
coaching methods:

| ID | Name | ADHD Effect |
|----|------|-------------|
| 0 | Pomodoro | Reduces stress, boosts focus |
| 1 | LadderStep | Breaks down cognitive load |
| 2 | BodyDouble | Reduces stress, boosts independence |
| 3 | ImplementationIntent | Reduces load, boosts focus |
| 4 | TwoMinuteStart | Quick focus boost |
| 5 | TaskChunking | Reduces load, modest focus boost |
| 6 | MindfulRefocus | Big stress reduction, big focus boost |
| 7 | DistractionImmune | Big focus boost |
| 8 | AttentionAnchor | Big focus boost, stress reduction |
| 9 | ShrinkTheTask | Big load reduction, stress reduction |

---

## For ADHD Developers — Your Brain on This Code

- **Hyperfocus periods are assets here.** The `LTCognitiveStateComponent` tracks
  focus state. If you’re in a flow state with this codebase, ride it. Don’t
  fight it.
- **Task-switching penalty:** UE5 builds + Python scripts + docs are 3 different
  contexts. Batch similar work (all C++ edits together, then all docs).
- **Time blindness:** The `NLTTrainingManager` has `TickInterval = 0.1s` and
  `TrainingTimer` throttling. Use timers. Set reminders.
- **Rejection sensitivity:** Code reviews are about code, not you. The bot
  enforces standards, not personal judgment.
- **Executive dysfunction:** Break large tasks into sub-5m steps. See
  `docs/onboarding-checklist.md` for pre-split tasks.

---

## For Autistic Developers — Clear Structure Ahead

- Everything has a place. See `file-structure.md` for the full layout.
- No hidden magic. If it’s not in the code, it doesn’t exist.
- Predictability is built in: deterministic seed, fixed timestep, reproducible.
- `NLT-DEV-OTOI.md` is the contract. `AGENTS.md` is the gateway. Read in order.

---

## Getting Help

1. **Blocked?** Check `docs/active-threads.md` — someone may have been here.
2. **Confused?** Read `docs/onboarding-checklist.md` — it has the exact commands.
3. **Ethical concern?** Escalate immediately to Joshua W. Dorsey.
4. **Just tired?** Stop. Your brain is not a machine. Rest is part of the
   process.
