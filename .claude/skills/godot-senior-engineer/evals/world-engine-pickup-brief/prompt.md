---
tags: [skill-creator]
max_turns: 20
timeout_seconds: 600
allowed_tools: [Read, Glob, Grep, Skill, Write, Edit, Bash]
---

ok next thing for the world engine. right now the agent loop works for movement, the fusion model gives an intent, ASFDK gate approves it, IntentMoveController walks the character there through jolt. now i want NPCs to be able to pick up items when the model says to. like "pick up the red crate". think through how this should work architecturally and then give me something i can hand to claude code to build it
