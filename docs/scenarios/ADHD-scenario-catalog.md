# ADHD Scenario Catalog

> Maps the 13 training scenarios to ADHD cognitive traits and mechanisms.

## Overview

Each scenario in `neurolift-ai-fusion/src/simulation/environment/scenarios.py`
targets specific ADHD challenges. This document explains the mapping so
developers and reviewers can verify **authenticity** (not just realism).

## The ADHD Challenge Matrix

| Scenario ID | Name | Category | ADHD Trait Tested | Cognitive Dim Affected | Avversiveness | Cognitive Demand |
|-------------|------|----------|-------------------|----------------------|---------------|---------------------|
| wp_1 | Email Processing | Workplace | Task-switching, distractibility | Focus, Stress | 0.4 | 0.5 |
| wp_2 | Report Writing | Workplace | Sustained attention, procrastination | Focus, Burnout | 0.6 | 0.8 |
| wp_3 | Meeting Participation | Workplace | Social anxiety, executive dysfunction | Stress, SuccessRate | 0.3 | 0.6 |
| wp_4 | Code Review | Workplace | Hyperfocus trap, perfectionism | Focus, CognitiveLoad | 0.4 | 0.85 |
| wp_5 | Deadline Crunch | Workplace | Urgency/adrenaline cycle, overwhelm | Stress, Burnout | 0.8 | 0.9 |
| pers_1 | Household Cleaning | Personal | Task avoidance, initiation difficulty | Independence, Focus | 0.7 | 0.3 |
| pers_2 | Grocery Shopping | Personal | Planning, decision fatigue | CognitiveLoad, Stress | 0.5 | 0.6 |
| pers_3 | Bill Paying | Personal | Avoidance, boring tasks | Independence, Stress | 0.8 | 0.7 |
| pers_4 | Morning Routine | Personal | Executive function, time blindness | Independence, SuccessRate | 0.4 | 0.4 |
| soc_1 | Phone Conversation | Social | Rejection sensitivity, anxiety | Stress, Focus | 0.6 | 0.5 |
| soc_2 | Social Event | Social | Overstimulation, social exhaustion | Burnout, CognitiveLoad | 0.7 | 0.8 |
| acad_1 | Study Session | Academic | Sustained attention, task initiation | Focus, CognitiveLoad | 0.5 | 0.8 |
| acad_2 | Project Work | Academic | Long-term planning, deadline pressure | Independence, Burnout | 0.6 | 0.9 |

## How Each Scenario Tests ADHD Traits

### wp_1 — Email Processing (Workplace)
- **ADHD mechanism:** External interruptions → task-switching penalty
- **Trait tested:** Ability to return to task after interruption
- **UE5 connection:** `requires_sustained_focus: True` → cognitive decay rate is
  higher, focus drops faster during the scenario
- **Expected pattern:** Focus drops on each interruption spike; Aide should use
  "AttentionAnchor" (strategy 8) or "BodyDouble" (strategy 2)

### wp_2 — Report Writing (Workplace)
- **ADHD mechanism:** Long, uninteresting, high-cognitive-demand task →
  procrastination and hyperfocus-burnout cycle
- **Trait tested:** Initiating without urgency/adrenaline
- **UE5 connection:** `aversiveness: 0.6` → slower stress accumulation;
  `cognitive_demand: 0.8` → higher base cognitive load
- **Expected pattern:** Avatar starts with low engagement, stress rises; Aide
  should use "LadderStep" (strategy 1) to break it down

### wp_3 — Meeting Participation (Workplace)
- **ADHD mechanism:** Social processing + verbal processing mismatch
- **Trait tested:** Contributing ideas under social pressure
- **UE5 connection:** `social_elements: True` → stress spikes when
  `Interaction == Help` (asking for help carries rejection risk)
- **Expected pattern:** Stress spikes early, then plateaus; Aide should use
  "MindfulRefocus" (strategy 6) or "Pomodoro" (strategy 0)

### wp_4 — Code Review (Workplace)
- **ADHD mechanism:** Hyperfocus trap — deep dive into details while
  losing sight of the bigger picture
- **Trait tested:** Balancing thoroughness with time management
- **UE5 connection:** `interactive: False` → no external interruptions possible;
  cognitive load grows monotonically
- **Expected pattern:** Focus climbs (hyperfocus) while independence drops;
  Aide should use "BodyDouble" (strategy 2) to provide gentle accountability

### wp_5 — Deadline Crunch (Workplace)
- **ADHD mechanism:** Urgency/adrenaline cycle — only works under time pressure
- **Trait tested:** Starting work early without artificial crisis
- **UE5 connection:** `urgency: critical`, `pressure: high` → stress starts
  high, rises faster; `interruptions: True` → focus drops on each
- **Expected pattern:** Stress and burnout climb rapidly; independence drops;
  Aide must intervene early with "TwoMinuteStart" (strategy 4)

### pers_1 — Household Cleaning (Personal)
- **ADHD mechanism:** Task avoidance — boring, non-stimulating chore
- **Trait tested:** Starting a task with no external deadline
- **UE5 connection:** `motivation_challenge: True` → base SuccessRate is 0.5;
  `aversiveness: 0.7` → strong avoidance tendency
- **Expected pattern:** Avatar starts with very low engagement; needs "LadderStep"
  or "ShrinkTheTask" to overcome initiation barrier

### pers_2 — Grocery Shopping (Personal)
- **ADHD mechanism:** Planning deficit + decision fatigue in stimulating
  environment (store with many choices)
- **Trait tested:** Executing a multi-step plan under sensory load
- **UE5 connection:** `ingredients: 8`, `meal_complexity: medium` →
  8 decision points; `cognitive_demand: 0.6`
- **Expected pattern:** Cognitive load rises with each decision; "TaskChunking"
  (strategy 5) helps reduce per-decision load

### pers_3 — Bill Paying (Personal)
- **ADHD mechanism:** Avoidance of boring, anxiety-provoking tasks
- **Trait tested:** Initiating and completing routine maintenance tasks
- **UE5 connection:** `avoidance_tendency: True` → very low initial focus;
  `aversiveness: 0.8` → high stress even at start
- **Expected pattern:** Avatar resists starting for 50+ ticks; "TwoMinuteStart"
  or "ImplementationIntent" (strategy 3) needed to break inertia

### pers_4 — Morning Routine (Personal)
- **ADHD mechanism:** Executive dysfunction — multiple sequential tasks,
  time pressure, low morning dopamine
- **Trait tested:** Sequencing multiple low-priority tasks to meet a deadline
- **UE5 connection:** `time_limit: True`, `components: [shower, breakfast,
  getting_ready]` → 3 sequential subtasks; `motivation: moderate`
- **Expected pattern:** Independence starts low, task-switching between the 3
  subtasks drains focus; "ImplementationIntent" (strategy 3) helps with sequencing

### soc_1 — Phone Conversation (Social)
- **ADHD mechanism:** Rejection sensitivity + verbal processing deficit
- **Trait tested:** Initiating and sustaining a phone conversation
- **UE5 connection:** `anxiety_level: 0.6` → stress starts medium;
  `caller: unknown` → social uncertainty penalty
- **Expected pattern:** Stress spikes at start, Focus drops; Aide should use
  "MindfulRefocus" (strategy 6) early, then "BodyDouble" (strategy 2)

### soc_2 — Social Event (Social)
- **ADHD mechanism:** Sensory overstimulation + social exhaustion
- **Trait tested:** Managing energy and attention in a high-stimulation
  environment
- **UE5 connection:** `group_size: large`, `structured: False` → maximum
  cognitive drain; `aversiveness: 0.7`
- **Expected pattern:** Cognitive load and burnout climb steadily; Aide should
  use "Pomodoro" with breaks, "AttentionAnchor" to refocus

### acad_1 — Study Session (Academic)
- **ADHD mechanism:** Sustained attention on abstract material
- **Trait tested:** Maintaining focus on material with delayed reward
- **UE5 connection:** `deadline: 5` (days) → urgency is distant;
  `requires_sustained_focus: True`
- **Expected pattern:** Focus degrades after 100 ticks; "AttentionAnchor"
  (strategy 8) or "MindfulRefocus" (strategy 6) needed to sustain

### acad_2 — Project Work (Academic)
- **ADHD mechanism:** Long-term planning deficit + deadline pressure
- **Trait tested:** Breaking a large project into actionable steps
- **UE5 connection:** `project_phase: mid`, `deadline_days: 7` → moderate
  urgency, high cognitive demand; `dependencies: True`
- **Expected pattern:** CognitiveLoad rises from dependencies; Independence
  stays low until Aide applies "LadderStep" or "ShrinkTheTask"

## Validation Checklist

For each scenario, verify:

- [ ] `aversiveness` reflects the **emotional** burden of the task
- [ ] `cognitive_demand` reflects the **mental** resources needed
- [ ] `requires_sustained_focus` matches real ADHD experience
- [ ] The scenario's `context` dict includes **at least one** ADHD-relevant
  key (`avoidance_tendency`, `anxiety_level`, `motivation`, `time_limit`,
  `interruptions`)
- [ ] A recommended Aide strategy is documented above for initial guidance

## Sources

- Barkley, R.A. *Taking Charge of Adult ADHD* (2020)
- Hallowell, E.M. *Driven to Distraction at Work* (2015)
- ADHD coaching techniques: ADD Coach Academy, CHADD
