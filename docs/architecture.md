# Architecture Overview

> **Status:** Stub — full content to be developed. See `README.md` for context.

## System Architecture

The nlt-fusion system implements the **Avatar → Aide → Advocate** experiential learning pipeline:

```
┌─────────────────────────────────────────────────────┐
│                  Simulation Environment              │
│                                                     │
│  ┌─────────┐    coaches    ┌─────────┐              │
│  │  Avatar  │◄────────────►│  Aide   │              │
│  │ (ADHD    │              │(Expertise│              │
│  │  traits) │              │+ RRT)   │              │
│  └────┬─────┘              └────┬────┘              │
│       │                        │                   │
│       └──────────┬─────────────┘                   │
│                  │ after independence               │
│                  ▼                                  │
│           ┌──────────┐                             │
│           │ Advocate  │                             │
│           │(Fused AI) │                             │
│           └──────────┘                             │
└─────────────────────────────────────────────────────┘
```

## Key Components

| Component | Path | Description |
|---|---|---|
| Avatars | `src/avatars/` | ADHD trait embodiments |
| Aides | `src/aides/` | Coaching and therapeutic systems |
| Advocates | `src/advocates/` | Fused Advocate intelligences |
| Fusion Engine | `src/fusion/` | TOI-OTOI fusion algorithms |
| Simulation | `scripts/` | Training loop and environment setup |

## 19 Avatar-Aide-Advocate Pairs

### Executive Function Focused (16 pairs)
1. StayAlert — Sustained attention deficit
2. ImpulseGuard — Impulsivity control
3. FocusFlow — Hyperfocus management
4. Timely — Time blindness
5. MemoryMate — Working memory deficits
6. MoodEase — Emotional regulation
7. TaskKickstart — Task initiation difficulty
8. CalmCore — Low frustration tolerance
9. Planner Pro — Prioritization and planning
10. SmoothSwitch — Transition difficulties
11. AwareMate — Self-monitoring challenges
12. SteadyMind — Poor impulse control
13. FocusRecharge — Effortful focus fatigue
14. EffortAlign — Effort vs. productivity perception

### Non-Executive Function (5 pairs)
15. StressShield — Stress sensitivity
16. SensoryBalance — Sensory sensitivity
17. SocialSync — Social challenges
18. SensorySeeker — Sensory seeking behavior
19. ConfidenceCoach — Self-esteem and identity

---

*For architecture questions, escalate to Joshua W. Dorsey, Sr. (`info@neuroliftsolutions.com`).*
