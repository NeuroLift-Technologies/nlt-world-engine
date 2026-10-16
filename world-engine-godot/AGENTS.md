# AGENTS.md — world-engine-godot (project guide for coding agents)

> **Scope:** this folder only — the authoritative Godot 4.7.2 (.NET / C#) runtime.
> **Purpose:** conventions, graphics-focused plan, and workflow every coding agent follows when
> changing files here.
> **Authority chain (do not invert):** `../NLT-DEV-OTOI.md` (org contract) → `../AGENTS.md`
> (repo contract) → `../CLAUDE.md` → **this file** (project conventions). Nothing here overrides
> the contracts above. Final authority: **Joshua W. Dorsey, Sr. — escalate, do not guess.**

---

## 1. Session start (every session)

1. `../NLT-DEV-OTOI.md` — org governance (registration, escalation, commit format).
2. `../AGENTS.md` — repo contract, guardrails, vision.
3. `../CLAUDE.md` — project context, mandatory reading order.
4. `../docs/active-threads.md` — **claim your thread before starting work**; do not touch work
   already claimed by another agent.
5. This file.
6. The subsystem doc for what you are changing: `AGENT-SYSTEM.md` (agents/loop),
   `ART-PIPELINE.md` + `ASSET-MANIFEST.md` (assets/graphics), `agent-loop.md` (protocol),
   `README.md` (layout/status), `RENDERER-PLAN.md` / `MIGRATION-PLAN.md` — **superseded
   historical records**, reference only, never current instructions.

---

## 2. The visual target — what "done" looks like

**The dashboard vision image** (the "NeuroLift Coastal Simulation Dashboard" concept Joshua
provided, 2026-10-09) is the bar for this project's graphics. Reference copies live in
**`Images/Vision/`** (`NeuroLift Coastal Simulation Dashboard.png`,
`NLT World Engine_ Living City Simulation.png`) — the folder carries a `.gdignore` so Godot
never imports these as runtime textures. The dashboard concept is a dark-glass operator
dashboard laid over a believable photoreal coastal city. Work in this folder is judged against
it in three layers:

| Layer | The dashboard shows | Current state here |
|---|---|---|
| **1. World rendering** | Aerial coastal city — mountains, marina, roads with cars, parks, multi-storey buildings, pool/luxury interiors, atmospheric haze | Procedural from engine primitives (`TerrainBuilder`, `SettlementBuilder`, `VegetationBuilder`, `WaterBuilder`) — reads as a blockout (`ART-PIPELINE.md` §1.1) |
| **2. Characters** | Articulated residents walking streets and inhabiting cutaway interiors, with role pins (Avatar / Aide / Advocate) and name labels | `Resident`/`ResidentLayer` render state-feed agents; `Agents/AvatarCharacter.cs` exists; walk cycles + full population per `RENDERER-PLAN.md` B.2/B.4, blocked on GRAPH-001 G1 decisions |
| **3. Observer dashboard HUD** | Left district nav rail · environment header (top-right) · world-space POI labels · agent role pins · bottom-left agent card with need bars and goals · recent-events feed · right control cluster (Spectator / Follow Agent / Free Camera / Time Control / speed slider / Scenario) · bottom-right minimap · bottom status bar + clock | Phase D delivered six observer panels, three reading levels, transport controls, accessibility (`Observer/*.cs`). Several dashboard elements do not exist yet — see §5, Phase GP-3 |

**Standing rules for all three layers:**

- **Godot renders; it never decides.** The renderer is not the source of truth
  (`RENDERER-PLAN.md` §1). Fusion owns semantic reality; this engine owns physical reality.
  Graphics work must never introduce simulation logic into rendering code, or vice versa.
- **Accessibility is a renderer constraint, not a later pass.** The observer audience is people
  with ADHD; colour is never the only channel (Okabe–Ito palette in `Observer/Ui.cs`, glyph
  shapes, three reading levels: Simple / Coach / Technical). Any new indicator ships colour +
  shape + text. Respect the reduced-motion toggle (`SkyPaused`, `Resident` reduced-motion path).
- **Performance targets are inherited and fixed:** 60 FPS, <16 ms frame time, 10–20 animated
  characters (`ART-PIPELINE.md` §2).
- **Screenshot evidence.** No graphics change is "done" without a captured screenshot compared
  against the dashboard target. Save under **`Images/Screenshots/`** (not `screenshots/`, the
  legacy folder) and cite it in the handoff.

---

## 3. Non-negotiable boundaries

| Rule | Source |
|---|---|
| Fusion owns semantic (goals, needs, coaching, intent); the engine owns physical (position, velocity, collision, consequences). Fusion sends **intent**, never coordinates/velocity. | `agent-loop.md`, `AGENT-SYSTEM.md` |
| `LocomotionController` is the **only** writer of position/velocity. Models clamp, never teleport. | `Agents/LocomotionController.cs` |
| No LLM provider lock-in; no autonomous architecture decisions; third-party plugins are Joshua's call (OTOI §4.4). | `../AGENTS.md` guardrails |
| **No asset lands without an `ASSET-MANIFEST.md` row** (source URL, licence, licence text, retrieval date, author). Do not commit unexamined files blind (`RenderStripped.*`, `SK_SimBody_Base.fbx` stay untracked). Mixamo redistribution licence is an **open risk (G1.1)** — do not assume CC0. | `ART-PIPELINE.md` G2.1, `ASSET-MANIFEST.md` |
| Import art where art is genuinely required (characters, near-camera hero props) — **not** as blanket replacement of procedural terrain/water/vegetation/buildings. | `ART-PIPELINE.md` §4 |
| The UE tree `../WorldEngine/` is frozen and non-authoritative. Do not change it; do not treat it as a conformance oracle. | ENG-002 |
| PR ≤ 100 changed files (CodeRabbit skips review above it). | `MIGRATION-PLAN.md` §10 |

---

## 4. Code standards

**Stack:** Godot **4.7.2 .NET (mono)** + .NET 8 (`Godot.NET.Sdk/4.7.2`, `net8.0`,
`<Nullable>enable</Nullable>`, root namespace `NltWorldEngine`). The standard (non-.NET) Godot
build will not run this project's C#.

**C# conventions (match the existing code):**

- **File-scoped namespaces**, exactly the four in use: `NltWorldEngine`, `NltWorldEngine.Agents`,
  `NltWorldEngine.Feed`, `NltWorldEngine.Observer`.
- 4-space indent, UTF-8, LF line endings, trailing whitespace trimmed, final newline
  (`.editorconfig` at repo root).
- **XML doc comments that explain *why*, not just *what*.** `Agents/LocomotionController.cs` is
  the exemplar: it documents the two execution paths, what is authoritative where, and the
  reasoning behind each constant. If a constraint is non-obvious, write it down in the comment —
  this codebase treats rationale as part of the change.
- `sealed` by default for classes that are not extension points; `in` parameters for readonly
  value types; `null!` only where initialization is provably guaranteed before use.
- **No TODO/FIXME/WIP markers in committed code** — either done, or documented in
  `docs/active-threads.md` / a handoff.
- `AgentHarness/` and `AgentLoopEndpoint/` are excluded from the Godot project's compile glob in
  `world-engine-godot.csproj`. Do not move files into them (or add `<Compile>` items) without
  understanding that boundary — each has its own entry point.
- The build has a `ProjectReference` to `../../asfdk-csharp/src/Asfdk/Asfdk.csproj`. A build
  failure on that reference is environmental, not yours to "fix" by deleting it.
- **Plan-vs-code naming divergences exist on purpose** (e.g. `UtilityAgentController` on disk vs
  `DeterministicUtilityController` in `MIGRATION-PLAN.md` §2.6b). Do not drive-by rename;
  renaming is Joshua's call (`AGENT-SYSTEM.md` banner).

**Scene/file conventions:**

- One behaviour ≙ one `.cs` file named for its class; `.uid` files are tracked — commit them
  alongside new scripts (see repo commit `88f3bd4`).
- Runtime-built world content (builders) is intentional for the open world; interiors are
  `assets/levels/*.fbx` wrapped by `<Name>_level.tscn` (`workplace_level.tscn` is canonical;
  `workplace.tscn` is orphaned — do not instance it).

---

## 5. The graphics plan (dashboard-first)

The dashboard image is the destination; this is the order of march. Each phase lists what it
delivers for the dashboard look and its gate. Check `../docs/active-threads.md` for the live
status of `GRAPH-001` and `RENDERER-001` before starting a phase — some gates are human-owned.

### Phase GP-0 — Unblock the art decisions *(human-owned, blocks GP-2)*
The `GRAPH-001` G1 decisions are Joshua's: G1.1 asset source & Mixamo redistribution answer,
G1.2 character count + LOD budget, G1.3 animation source, G1.4 hero-prop policy, G1.5 budget.
Agents may prepare options and evidence, but **may not start GP-2 pipeline work until G1.1 and
G1.5 land**. Escalate, do not guess.

### Phase GP-1 — World fidelity from primitives *(agent-executable now)*
Raise the procedural world toward the dashboard's believability without importing art wholesale:
- **Terrain:** PBR material with normal/roughness detail instead of flat vertex colours;
  re-enable shadow casting (currently `CastShadow = Off`) once frame time is measured.
- **Buildings:** richer `SettlementBuilder` vocabulary — window insets, varied rooflines,
  façade materials, façade lighting at night — the dashboard shows multi-storey varied
  architecture, not grey boxes.
- **Vegetation:** LOD policy for `MultiMesh` instances (billboard/static beyond N m) and
  canopy density variation; wind shader stays but must honour reduced-motion.
- **Water/shoreline:** the dashboard's marina and shoreline are a signature element — extend
  `WaterBuilder` (shallow-water colour ramp, shoreline foam) before adding new districts.
- **Lighting/grade:** the dashboard's warm late-afternoon key light and atmospheric depth —
  tune Sky3D time defaults, fog, and the Compositor colour-grading effects
  (`Compositor/Color grading/`) rather than hard-coding per-material tweaks.
- **Gate:** screenshot capture at dashboard-matched camera angles; no frame-time regression
  beyond §2 targets; no new assets without manifest rows.

### Phase GP-2 — Characters & animation *(after GP-0 gates)*
- Articulated rigged humanoid import (glTF preferred; FBX via built-in ufbx works) with the
  axis/scale/bone-naming validation from `MIGRATION-PLAN.md` 5c.1.
- Procedural walk cycle driven by authoritative velocity/state (5c.2 pattern) — animation
  reflects the simulation's movement, never a model's opinion.
- `Label3D` name labels + role indication (Avatar / Aide / Advocate pins like the dashboard's
  coloured markers) — colour-safe, no flashing (`RENDERER-PLAN.md` B.4).
- Performance gate: 10–20 animated characters at 60 FPS.

### Phase GP-3 — The dashboard HUD *(agent-executable; the visual centerpiece)*
Close the gap between the current observer (six panels, transport controls) and the dashboard
image's layout. Existing building blocks: `Observer/Ui.cs` (`Palette`, `Glyph`, `Ui` helpers),
`AccessibilitySettings`, `WorldViewHud`, `ObserverRoot` (top bar), and the panel classes in
`Observer/`. Target elements:

| Dashboard element | Plan |
|---|---|
| **Left district nav rail** (Downtown / Campus / Residential / Park / Waterfront) | New anchored rail panel; selecting a district drives camera fly-to. Built with `Ui` helpers so high-contrast and reading levels still apply. |
| **Environment header** (top-right: Persistent World / Multi-Agent / Real-Time Physics / Meaningful Scenarios) | Extend `ObserverRoot` top bar with status chips — status only, no fabricated data. |
| **World-space district/POI labels** (Campus · Study · Learn · Grow, etc.) | `Label3D` billboards on world anchors, colour-safe, culled by camera distance; placement via `WorldAnchors.cs`. |
| **Agent role pins** (Avatar / Aide / Advocate over interiors) | Ships with GP-2 labels; pin = shape + colour + role text. |
| **Bottom-left agent card** (portrait, Focus / Energy / Mood / Wellness bars, Current Goals, icon row) | Extend `AvatarStatePanel`: need bars exist per `state-feed-v1` vocabulary; add goals list from feed data. **Never invent values the feed does not carry.** |
| **Recent-events feed** (timestamped rows) | New panel fed by the same `FeedTransport` events — plain language per `PlainLanguage.cs`, respecting reading level. |
| **Right control cluster** (Spectator / Follow Agent / Free Camera / Time Control / speed slider / Scenario selector) | Transport (pause/resume/step/speed) exists from Phase D; add Follow Agent + Free Camera as camera modes in `WorldView`. Scenario selector wires to existing scenario data — **supervisor actions that change outcomes require Joshua's approval** (Observer is read-only plus transport, per the human-role standard). |
| **Bottom-right minimap** | New `SubViewport` minimap or a `Control._Draw` top-down plot; zoom controls; North indicator. |
| **Bottom status bar** (engine name · Godot 4.x · Local Processing · Privacy First · clock) | Add to `ObserverRoot`; footer reflects real engine/feed state honestly. |

**HUD standards:** panels use `Palette` colours only (no ad-hoc hex); overlays that must not
block camera orbit set `MouseFilter = Ignore` (see `WorldViewHud`), interactive controls use
`Stop`; no panel may cover >1/3 of the viewport at default size; text uses the `Ui` font-scale
constants; every new panel works at all three reading levels and in high-contrast mode; no
flashing indicators.

### Phase GP-4 — Verification & performance gate *(agent-executable)*
- Frame-time capture at 20 animated residents (`ART-PIPELINE.md` G3.1).
- Asset-manifest audit — no licence-incompatible asset committed (G3.2).
- Full screenshot matrix: dashboard-matched camera angles × reading levels × high contrast.
- Reduced-motion pass: sky rotation paused, wind sway honoured, walk cycles still driven by sim
  state.

---

## 6. Verification (run before claiming any task done)

```powershell
# 1. Compile the Godot project — expect 0 errors.
#    (2 pre-existing nullable warnings in WorldView.cs are tolerated; do not add more.)
dotnet build world-engine-godot.csproj

# 2. Build + run the out-of-engine agent assertion harness — expect all assertions passed.
dotnet build AgentHarness/AgentHarness.csproj
dotnet run --project AgentHarness/AgentHarness.csproj
```

- **In-scene opt-in loop:** set `NLT_AGENT_LOOP_ENABLED=1` to run the local-avatar test path
  (`NLT_AGENT_LOOP_ENDPOINT` overrides the endpoint). Default runs are unchanged. Never make the
  loop enabled-by-default.
- **Headless scene boot:** the GDA flow documented in `../docs/active-threads.md` boots the main
  scene and reports structured diagnostics — use it for startup regressions.
- **Visual changes:** launch `Main.tscn` in the editor, capture a screenshot into
  `Images/Screenshots/`, compare against §2. Record the evidence in the handoff. "Looks right to
  me" is not verification.
- If you change FBX import settings: delete `.godot/imported/*Level*` and re-import once via the
  editor's Import dock — not by raw file edits.

---

## 7. Workflow & coordination

- **Claim first:** update `../docs/active-threads.md` before starting; check it for peers'
  in-flight work. `WorldView.cs` and `Main.cs` are hot hubs — coordinate before editing.
- **Commits:** `[AGENT_NAME] type(scope): description`, type ∈
  `feat | fix | docs | refactor | chore | test | ci`. House-style example:
  `[OPENCODE] fix(settlement): keep buildings off the radial roads`.
- **PR ≤ 100 changed files.** Split larger work.
- **Handoff before ending a significant session:** update `../docs/active-threads.md`, write a
  record to `../docs/agent-log/handoffs/` using `../templates/handoff-record.json`, file
  blockers in `../docs/escalations/`.
- **Escalate immediately when:** scope is unclear or conflicts with claimed work; an
  architecture / plugin / asset-budget decision is needed (all GP-0 items); a licence question
  arises; an ethical concern surfaces; or a blocker is unresolvable. Use
  `../templates/escalation.md`. Escalation is correct protocol, not failure.

---

## 8. Quick reference

| I want to… | Start here |
|---|---|
| Change agent behaviour / movement | `AGENT-SYSTEM.md`, `Agents/` — `LocomotionController` is the only position writer |
| Improve world graphics | §5 GP-1, `ART-PIPELINE.md`, builders (`TerrainBuilder`, `SettlementBuilder`, `VegetationBuilder`, `WaterBuilder`) |
| Improve the HUD / dashboard look | §5 GP-3, `Observer/` (`Ui.cs` palette, `ObserverRoot`, panels) |
| Import an asset | `ART-PIPELINE.md` G2 — **manifest row first**; GP-0 gates apply to character/hero art |
| Touch the Fusion loop / protocol | `agent-loop.md`, `../docs/contracts/agent-loop-v1.md` + schema, `Agents/AgentLoopProtocol.cs` |
| Verify my change | §6 |
| Something is unclear | Escalate to Joshua — do not guess |




