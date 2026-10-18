# AGENT-LOOP-002 — Scene transitions and interior interaction: agent briefs

**Author:** Claude (spec only; no code changed) · **Date:** 2026-10-17, revised 2026-10-18 · **For:** coding agents (Codex, OpenCode, Cline, Hermes, CC) · **Authority:** Joshua W. Dorsey, Sr.
**Repo state read:** `NeuroLift-Technologies/nlt-world-engine` @ `3dce1a8`. Everything below was read from code and docs. **Nothing was built or run**, so every "risk" is a prediction until an agent measures it.
**Revision 2026-10-18:** a second session re-read the code at the same commit and corrected §1, §2 and every task. The changes are listed at the end of this file. "Fusion" in this file means the `NeuroLift-Technologies/neurolift-ai-fusion` repo.

---

## 0. Goal (Joshua, 2026-10-17)

A model, through the existing agent loop, makes the avatar:

1. walk to a building and **go inside it** (the avatar is transported to that building's interior scene),
2. **move around inside**, and then **interact** with objects there (sit, use, look at),
3. with the observer camera **following the avatar or not** (free orbit/zoom).

Order of work: **T1 → T2 → T3 → T4** deliver 1 and 3. **T5 → T6** deliver 2. Ship and verify in that order. T1–T4 do not depend on T5–T6.

### Decisions already made (Joshua, 2026-10-17)

| Decision | Choice |
|---|---|
| How the model enters a building | `use` on the building's **door target**. No new verbs, **no schema bump**. |
| Scenes live at once | **One.** Entering an interior disables the open world's physics (existing behaviour). Accepted for a single avatar. |
| "Without the camera following" | **Free look inside the avatar's current scene.** Not "view a different scene than the avatar's". |
| Transport | Avatar is placed in the interior by the **engine**, not Fusion. |

Not decided, do not assume:
- Whether `use` on an object changes world state (T6). Default if unanswered: occupy only.
- Which perception `kind` interior furniture reports (T5). The schema allows `agent`, `object` and `place`; today every anchor reports `place`. Default if unanswered: `object` for furniture, `place` for doors and exits.
- Whether perception should report the avatar's pose and facing (T6). v1 has no field for it: `self` allows only `position` and `velocity`, and the schema forbids extra fields, so this would be a schema/version change agreed with Fusion. Default if unanswered: not reported to the model; pose and facing are shown on screen only.
- Fusion-side prompt/policy changes (they live in `neurolift-ai-fusion`, not this repo).

---

## 1. Rules that apply to every task (from `AGENTS.md`, `world-engine-godot/AGENTS.md`)

- **Fusion owns semantics, the engine owns physics.** Fusion sends intent only. No coordinates, velocity, teleport, or object-state fields in any intent.
- `world-engine-godot/AGENTS.md` §3 says `LocomotionController` is the only writer of position/velocity. **That is already not true in the live path:** `AgentBrain` sets `Velocity` every physics tick and resets `GlobalPosition` at the kill plane (`Agents/AgentBrain.cs:146-153`), and `Main` sets `GlobalPosition` at spawn (`Main.cs:250`). T3 adds an engine-owned scene transition. It must be **one clearly named method on `AgentBrain`**, documented in a comment, unreachable from intent payloads, and the kill-plane reset should go through the same method so there is one placement path. Do not add any other way to set position.
- Keep ingress **fail-closed**, keep the loop **opt-in** (`NLT_AGENT_LOOP_ENABLED=1`), keep ASFDK governance at ingress unchanged.
- **Claim the thread** in `docs/active-threads.md` before starting. `WorldView.cs` and `Main.cs` are hot hubs, and GRAPH-002 is claimed by **OPENCODE**. Its status line still reads "claimed, not yet started" (out of date), and the last five commits to those two files are `[CLAUDE]` commits from 2026-10-16/17. Confirm with Joshua whether OPENCODE is active, coordinate if so, and keep edits small and additive either way.
- No asset lands without an `ASSET-MANIFEST.md` row. No third-party plugins. No TODO/FIXME in committed code.
- Accessibility: no flashing. If you add a fade or any transition effect it must respect reduced motion (`ReducedMotion` / `SkyPaused`). Any new HUD indicator ships colour + shape + text.
- Commits `[AGENT_NAME] type(scope): description`. PR ≤ 100 changed files. Write a handoff record to `docs/agent-log/handoffs/` using `templates/handoff-record.json`.
- Build prerequisite: `world-engine-godot.csproj` references `..\..\asfdk-csharp\src\Asfdk\Asfdk.csproj` and `AgentHarness/AgentHarness.csproj` references `..\..\..\asfdk-csharp\src\Asfdk\Asfdk.csproj`. Both point at the same **sibling checkout that is not in this repo**. A build failure there is environmental. Do not delete the reference.

**Verification commands** (from `world-engine-godot/AGENTS.md` §6):
```powershell
dotnet build world-engine-godot.csproj                     # expect 0 errors (2 known WorldView.cs nullable warnings)
dotnet build AgentHarness/AgentHarness.csproj; dotnet run --project AgentHarness/AgentHarness.csproj   # all assertions pass
& $exe --path "$PWD" -- --capture "res://Images/Screenshots/<name>.png" --frames 120 --level simple    # screenshot
# capture flags: --fixture <name> --hour <0-24> --focus <x>,<z>[,<dist>] --scene <id> --selftest
```
Fennara `runtime_session` cannot boot the scene on the dev PC and `screenshot_scene` returns a black frame. **Use the CLI path above.**

---

## 2. What the code does today (verified by reading)

**Scenes and the viewer**
- **Scene changes are a viewer action.** `WorldView.ShowScene(sceneId, kind)` swaps the one displayed world. `Portal.cs` says doors are "the spectator's way in and out" (click or `E`) and keeps the data for residents "when B.2 lands".
- `SetOpenWorldActive(false)` sets the open world's `ProcessMode` to Disabled, which **removes its terrain/building/wall bodies from physics**. `AvatarGround` (flat y=0 floor) is enabled only while an interior shows, as a backstop. The avatar is a child of `Main`, not of the open world. Interiors are instanced at the world origin.
- **`ShowScene` returns nothing and fails unsafely.** It turns the open world off (`WorldView.cs:226`) before it tries to load the level (`:233`), so a failed load leaves no open-world physics and no interior. `InteriorPathFor` matches on the id prefix only, so any `personal_N`, `workplace_N`, … resolves to a level.
- **The `--scene` pin** (`_fixedScene`) silently swallows requests for any other scene (`WorldView.cs:200`) and re-pins its scene every frame (`:895`).
- **Spectator doors call `ShowScene` directly:** clicking a building (`TryActivateBuildingAtScreen`, `WorldView.cs:683`), pressing `E` (`EnterOrExit`, `:699`), and the portal itself (`Activate`, `:724`). None of them knows about a live avatar.
- `Main.OnDocumentChanged` calls `ShowScene(doc.Scene.Id, doc.Scene.Kind)` **when the feed's scene id changes** (guarded at `Main.cs:136`). The default replay `stayalert-day` (`ObserverRoot.ReplayFixture`), `collapse-only`, `rescue-only` and `fixtures/state-feed.sample.json` say `personal_1`/`interior`; `open-world-day` says `open_world`/`open_world`. The open-world scene id is `open_world`. A pinned scene (`_fixedScene`) already overrides the feed. That is the precedent for T1.
- `PerceptionBuilder.SceneKindFor` guesses with `sceneId.Contains("open")`.

**The loop avatar**
- **Its scene and spawn come from the feed.** `AgentBrain.SceneId` is set once, by `Observe(..., doc.Scene.Id)` at spawn (`Main.cs:251`), and the spawn position is the feed's primary avatar position + (2, 1, 0) (`:250`). With the default replay the loop avatar spawns at (6.2, 1, −1.8) in the interior's coordinates, with the open world's physics already off and `SceneId = personal_1`. The settlement is at (−66, 46), about 80 m away, so no open-world anchor is within perception range. Which fixture the 2026-10-17 AGENT-LOOP-001 run used is not recorded (most likely `--fixture open-world-day`).
- `AvatarCharacter.ApplyIntent`: `approach`/`use`/`sit` become `IntentMoveController` (straight line, 1 m `ArrivalRadius`). **On arrival it installs an `IdleController`** (`AvatarCharacter.cs:166`). The comment in `ApplyIntent` says it hands back to wander, but wandering only resumes on the *next* intent (`:109`). If the avatar is already within `ArrivalRadius` when the intent arrives, it goes straight to wander with **no arrival event**. Comments say interaction and facing are **not implemented**.
- The kill plane (`KillY = −25`) resets a fallen avatar to `WorldGeometry.HeightAt(x, z) + 1.5`, the **open-world terrain height**, which is wrong inside an interior.
- Execution recheck `ReachRadius` = 30 m; perception range = 25 m. Building centres are placed up to 32 m from the plaza centre (`SettleR − 6`) and their doors sit further out, so from the plaza many doors are outside perception or reach.

**Anchors and targets**
- **Door anchors exist** in `WorldAnchorBuilder.BuildOpenWorld`: id `door_{index}_{label}`, where label is `home`, `office`, `shop` or `school` (`SettlementBuilder.KindLabel`, lower-cased), **not** the scene prefix. They are placed `FrontOffset + 1.7 m` outside the door (inside the building's collision box was unreachable, fixed 10-17). Door index equals portal index; the interior scene id is `SettlementBuilder.SceneIdFor(kind, index)` = `<prefix>_<index+1>`. So `door_0_home` → `personal_1` and `door_1_office` → `workplace_2`.
- **Affordances are derived from axes** (`PerceptionBuilder.AffordancesFor`: `sit` if privacy > 0.5, `use` if social or noise > 0.5; `IntentIngress.NeedsAffordance` mirrors it). Concretely, **every home door affords `sit` and never `use`** (Apartment axes: privacy 0.75, noise 0.2, social 0.25). Office, shop and school doors afford `use`.
- **There is no per-scene anchor lookup yet.** `IntentIngress` calls `_anchorsFor(avatar.SceneId)`, but `AgentLoopDriver` wires it as `_ => Anchors` (`Agents/AgentLoopDriver.cs:57`), which ignores the scene, and perception is built from the same single list (`:101`). Only an open-world anchor builder exists; interiors have none. Because interiors sit at the world origin, open-world anchors near the origin would be perceived "inside" a room.
- **`AgentLoopDriver.ResolveTarget` checks scene-tree node names before anchors** (`:129`). A target id that matches a node name resolves to that node's position.
- Perception reports every anchor as `kind: "place"` (`PerceptionBuilder.cs:33`).

**Contract and exits**
- Contract §4: a `result` of `accepted` means accepted for execution; **the next perception is the physical truth**. So the transition needs **no new result field**: the next perception's `scene` is the outcome. Contract §3: `rest` may carry an optional `targetId`.
- The interior "Exit" `Portal` is built in `DecorateInteriorExit` from the level's own door node, the café's cut doorway, or a fallback. `DoorFacing` derives the outward axis from where the door sits relative to the room centre (`WorldView.cs:600`), so `Portal.EntryPoint` (= Position + Facing·1.6) points **out of the room** and the inside spawn is `Position − Facing·~1.6`. **Verify before relying on it.**

---

## T1 — Per-avatar scene authority

**Status: delivered 2026-10-18.** The fusion-tour fix merged on 2026-10-18 already made the loop spawn the avatar at the plaza in `open_world` and keep open-world physics on while avatars exist, so §2's "spawn comes from the feed" no longer holds on `main`. T1 added `SceneCatalog` (scene id → kind, unknown ids rejected), the view following the loop avatar's own scene, and spectator doors locked while the loop runs. Verification is in the AGENT-LOOP-002 thread entry.

**Why:** today the feed decides the displayed scene and the avatar's scene; the avatar has no scene of its own that the viewer obeys.

**Do**
- Make `AvatarCharacter.SceneId` engine-owned state. When the loop is enabled, the viewer displays the loop avatar's scene, and `doc.Scene` from the feed does **not** override it (model it on `_fixedScene`). With the loop disabled, behaviour is unchanged.
- **Own the loop avatar's spawn.** With the loop enabled it spawns in `open_world` at a defined open-world point (for example near the `plaza` anchor) with `SceneId = open_world`, not at the feed's position in the feed's scene.
- Precedence for the displayed scene: `--scene` capture pin > loop avatar's scene > feed.
- While the loop owns the displayed scene, the spectator door paths (`TryActivateBuildingAtScreen`, `EnterOrExit`, `Activate`) must not switch scenes. Otherwise one click turns off the open world's physics under a live avatar.
- Replace `SceneKindFor` with a real source of truth: one place that maps scene id → `open_world`/`interior`, with `open_world` as the open-world id constant.

**Files:** `Agents/AvatarCharacter.cs`, `Agents/PerceptionBuilder.cs`, `Main.cs` (small), `WorldView.cs` (small).

**Acceptance**
1. Harness assertions: kind for `open_world`, `workplace_3`, `personal_1`, `social_9`, `academic_2` is right; an unknown id is rejected, not guessed.
2. Loop enabled with the default replay (`personal_1`): the avatar spawns in the open world, the open world stays displayed with working collision, and perception reports `scene = open_world / open_world` and lists open-world places.
3. Loop enabled: clicking a building or pressing `E` does not change the displayed scene.
4. Loop disabled: existing `--selftest` results unchanged (LAYOUT OK on all bundles), existing harness passes, and spectator doors work as before.

---

## T2 — Doors (and interior exits) as explicit usable targets

**Status: delivered 2026-10-18.** `TaskAnchor.Link` (`PortalLink`: target scene, building index) marks doors and exits; `AnchorAffordances` is now the single rule set for perception and the ingress re-check (doorways afford `use`, never `sit`, never occupied); `SceneAnchorSets` serves each scene its own anchors (open world: the existing set; a loaded room: its exit, `exit_<sceneId>`, 1.6 m inside the doorway); the loop driver asks by the avatar's scene and resolves anchors before node names. The origin building needs no extra state: the room's id encodes it (`personal_4` is building 3, `SceneCatalog.TryBuildingIndexFor`).

**Found while verifying (for T3):**
- Each room's exit anchor was probed against the level's real collision: the avatar capsule fits at all four with no hits.
- **The home level's floor collision is at y = −4.01**, four metres below the visible floor (office floor: 0.00). Only `AvatarGround` (y = 0) would hold an avatar there. T3 must not trust the home level's UCX floor for spawn height until this is fixed.
- **The café's north wall is still solid.** `WorldView.AddSocialExitDoorway` hides `UCX_Social_Wall_N` after `InteriorPhysicalBoundary` has already built collision from it, so the cut doorway is visual only. The academic doorway is also blocked about 0.1 m before the door plane. Neither matters to T3's design (the avatar stops at the anchor inside the room and the engine places it outside), but an agent walking through a doorway would be stopped.
- With the loop on, `OpenWorldBodiesLive` keeps the open world's bodies live and makes a shown interior display-only, so an avatar placed in a room today would have no room collision. T3 has to change that split for the avatar's own scene.

**Do**
- Give `TaskAnchor` an optional **portal link** (target scene id and which side it leads to). Door anchors get it from the building's portal (`door_{i}_{label}` → `SceneIdFor(kind, i)`). Prefer linking to the portal list `WorldView` actually built over re-running `BuildPlans`, so anchor and portal cannot drift apart.
- Portal anchors **always afford `use`** by explicit flag, not by axis thresholds, in both `PerceptionBuilder.AffordancesFor` and `IntentIngress.NeedsAffordance`. They do not afford `sit`. They are never "occupied". This flag is what fixes home doors, which afford `sit` but not `use` today.
- **Make the anchor set per scene.** `AgentLoopDriver` must hand perception and `_anchorsFor` the anchors of the avatar's current scene: the open-world set outside, that interior's set inside.
- Add an **exit anchor per interior scene** (affords `use`; links back to the originating building's open-world `Portal.EntryPoint`). The exit anchor's approach point must be **inside the room, clear of collision** (the same trap as the door anchors).
- Remember the origin: when an avatar enters via building *i*, record *i* so the exit returns to the same building.

**Files:** `TaskAnchor.cs`, `WorldAnchors.cs`, `Agents/PerceptionBuilder.cs`, `Agents/IntentIngress.cs`, `Agents/AgentLoopDriver.cs`, `WorldView.cs` (read-only accessor for the world portal list; `_worldPortals` is private and the exit needs `Portal.EntryPoint`).

**Acceptance (harness)**
1. Perception from an open-world avatar within 25 m of a door lists `door_N_*` with `use`, home doors included.
2. Ingress accepts `use door_N_*`; still **rejects** `use` on a non-portal anchor lacking the affordance, and `use` on an occupied non-portal anchor (existing behaviour intact).
3. Perception from an interior-scene avatar lists the exit target and **no open-world anchor**.

---

## T3 — Engine-owned scene transition

**Do**
- **Arrival hook.** Add a verb-aware arrival hook: when a `use` on a portal anchor arrives, run one transition. `IntentMoveController` today only installs an `IdleController` on arrival. Cover the case where the avatar is **already within `ArrivalRadius`** when the intent comes in (transition immediately; today that path goes straight to wander).
- **Make `ShowScene` safe first.** It must return success or failure, load the level *before* switching the open world off, and report when the `--scene` pin blocks the request. On failure the open world stays active.
- Run the transition in this order:
  1. `WorldView.ShowScene(...)` (loads the level, toggles open-world physics). Stop here on failure.
  2. **Wait for a physics frame** so the interior's `InteriorPhysicalBoundary` bodies are in the physics space. Placing the body earlier can drop it through the floor.
  3. Place the avatar through a single method on **`AgentBrain`** (name suggestion: `TransitionTo(Vector3 position, string sceneId)`). Only `AgentBrain` owns the authoritative position in the live path; `LocomotionController.Position` drifts there by design. The method sets `GlobalPosition`, zeroes `Velocity`, calls the existing `LocomotionController.Teleport`, **clears the held decision** (`DecisionHold`, otherwise the last move keeps playing), sets `SceneId`, and reattaches the fallback controller (`WanderFallback`).
  4. Pick spawn height by **ray-casting down onto the interior collision**, never a hard-coded Y. Keep `AvatarGround` as the backstop.
- Exit does the reverse: `ShowScene("", "open_world")`, place at the originating building's `Portal.EntryPoint`, facing away from the door.
- Route the kill-plane reset through the same placement method, and make it scene-aware: inside an interior, recover to the interior spawn, not open-world terrain height.
- Failure is safe: if the level fails to load, **do not move the avatar**; report a rejection with a reason.
- Do **not** add result fields. The next perception reports the new `scene`.
- Document in a comment that this is the engine-owned discontinuity permitted alongside "models clamp, never teleport" (`world-engine-godot/AGENTS.md` §3), approved by Joshua 2026-10-17.
- Known limit (accepted): with the open world's physics off, any other physical agent left outside will fall. Assert/log a warning if one exists; do not try to solve it here.

**Files:** `Agents/AvatarCharacter.cs`, `Agents/AgentBrain.cs`, `Agents/IntentIngress.cs`, `Main.cs` (small: the composition root connects arrival to the view), `WorldView.cs` (small, coordinate per §1).

**Acceptance**
1. **Round trip (in-scene, opt-in loop, after T1's spawn fix):** start outside near a door → intent `use door_N_*` → avatar walks to the door and is placed inside → next perception: `scene.kind = interior`, `scene.id = <prefix>_<N+1>` → avatar is standing on the floor (not falling, `y` stable for ≥ 2 s) → intent `use` the exit → avatar is outside the same building at its entry point and the open world is displayed and has working collision again. (Before T1, perception already reports `interior` for the default replay, so this check means nothing until T1 lands.)
2. Repeat the round trip for **each of the four kinds** (`personal`, `workplace`, `social`, `academic`).
3. `use door_N_*` sent while the avatar already stands at the door transitions without another walk.
4. Rejections: door out of reach → rejected with reason; level load failure → rejected, avatar not moved, open world still active. A real door always resolves to a level, so trigger the failure through a test hook (for example an injectable level-path resolver).
5. **Reachability sweep (a measurement, not a fix):** for every `door_*` anchor, record whether it is reached within `ArrivalRadius` in a time limit or stalls. Many doors are outside perception (25 m) and reach (30 m) from the plaza, so drive the movement directly in a script, bypassing ingress, or start within range of each door. Output a table into the handoff. (Movement is a straight line with sliding and no pathfinding, so some doors may snag on other buildings. Report, do not invent a pathfinder without escalating.)
6. Evidence: screenshots outside-before and inside-after under `Images/Screenshots/`. `--scene` re-pins every frame, so use it only for still interior shots, not for the round trip.

---

## T4 — Camera: follow or free look

Follow already exists (`WorldView.Follow(Func<Vector3?>)`, `PollFollow`, observer follow-target picker, orbit/zoom by mouse). This task makes it behave across a scene change. **Do not build the full GP-3 control cluster** (that is GRAPH-002).

**Do**
- Follow **on**: after the transition the camera re-targets the avatar at interior framing distance (`ShowScene` already re-frames with `FrameInterior`; make sure the follow source keeps working in the interior's coordinate frame, and that `FocusOn` does not snap back to the open-world target). On exit, `ShowScene("", "open_world")` resets the camera target to the settlement and `PollFollow` re-targets the avatar on the next frame.
- Follow **off**: the scene still switches (the displayed scene is the avatar's), the camera is framed on the interior by `FrameInterior`, and orbit/zoom stay free. The avatar moving must not move the camera.
- Transition must not flash (reduced motion respected).

**Acceptance (scripted or selftest)**
1. Follow on: from one frame after entry or exit, the camera target is within a stated distance of the avatar and stays within it while the avatar walks.
2. Follow off: camera target unchanged while the avatar moves 5 m; orbit/zoom inputs still change the camera.
3. Screenshots for both modes.

---

## T5 — Interior anchors (prerequisite for interaction)

**Why:** inside a building the model currently sees only the exit (after T2). There is nothing to sit on or use.

**Do**
- Build `TaskAnchor`s for each interior level from the level's geometry by **object name**, using the same naming rules `InteriorStyle.cs` already applies (office `WF_*`, café `Cafe_*`/`Social_*`, classroom `Academic_*` desks and bookshelves, home furniture). Stable ids per scene. Serve them through T2's per-scene anchor set.
- **Anchor ids must not resolve to meshes.** `ResolveTarget` checks node names before anchors, so an anchor named after its object resolves to the furniture's centre, which is unreachable. Make `ResolveTarget` check the current scene's anchors first, and keep anchor ids distinct from node names anyway.
- Explicit affordances (`sit` for seats/beds → also `rest`, `use` for desks/terminals/counters/shelves), not axis guesses.
- Report furniture with the perception `kind` decided in §0 (default `object`).
- **Anchor position is an approach point clear of collision**, not the object's centre. The interior bodies come from `InteriorPhysicalBoundary` (UCX proxies); an anchor at a furniture centre is unreachable, the same mistake as the original door anchors.

**Files:** new `InteriorAnchors.cs` (or similar), `InteriorStyle.cs` (read only for naming), `TaskAnchor.cs`, `Agents/AgentLoopDriver.cs` (`ResolveTarget`), `Agents/PerceptionBuilder.cs` (`kind`).

**Acceptance**
1. Each of the four level kinds exposes ≥ 3 anchors, including ≥ 1 `sit` and ≥ 1 `use`. Ids stable across loads.
2. **Reachability:** from the interior spawn, the avatar reaches every anchor within `ArrivalRadius` (record any that fail; fix placement, not the collision).
3. Perception inside lists them within range; ingress accepts `approach`/`look_at` on them, and the resolved target is the approach point, not the mesh centre.

*Open for the agent:* the interior node names have not been read. Inspect the four levels first and list the object-name vocabulary in the handoff.

---

## T6 — Interaction execution (`sit`, `use`, `rest`, `look_at`)

Depends on T5. **Needs Joshua's answer first:** should `use` change anything physical (a door opens, a light turns on) or only occupy the object? Default if unanswered: occupy only.

**Do**
- Anchors already model reservation/occupancy (`TaskAnchor`). Add an *in use* lifecycle: reserve on accept → pose at the anchor on arrival (reuse T3's arrival hook) → hold for a duration → release → return to autonomy.
- `sit`/`rest`: snap to a seated/lying pose at the anchor and hold. `use`: stand at the anchor and hold. `look_at`: turn to face the target (cheap, and visibly shows the model "seeing" the object).
- **`rest` with and without a target.** The contract lets `rest` carry an optional target, but `ApplyIntent` treats `rest` as standing still and ingress does not recheck it. Targeted `rest` goes to the anchor and gets the same affordance and occupancy recheck as `sit`; untargeted `rest` keeps today's behaviour.
- The holder's next perception shows its position at the anchor; other avatars' perceptions show the anchor `occupied: true` (the holder's own perception reports `false` by design, `PerceptionBuilder.cs:41`). Perception cannot show pose or facing: v1's `self` has only `position` and `velocity`, and the schema forbids extra fields. Show pose and facing on screen instead. Do not add perception fields; reporting pose to the model is the open decision in §0. A second avatar's `sit` on an occupied anchor is rejected (existing check).
- Keep placement on `AgentBrain`'s single documented method; any snap to a pose goes through an explicit, documented interaction method (same caution as T3).

**Acceptance**
1. Avatar sits on a chair: its next perception places it at the chair; a second avatar's perception lists the chair `occupied: true`, and that avatar's `sit` on the same chair is rejected "occupied".
2. After the hold, the anchor releases and the avatar resumes.
3. `look_at` visibly turns the avatar toward the target; facing is screenshot-evidenced (v1 perception has no facing field).
4. A model-driven run (the opt-in Qwen 0.6B path) chooses and completes at least one `sit` or `use` inside an interior. Prompt/policy tuning for this lives on the **Fusion side** (`neurolift-ai-fusion`, not visible from this repo). If the model never picks valid targets, record that as a finding rather than changing the contract.

---

## 3. Contract and docs impact

- `docs/contracts/agent-loop-v1.md` gains **a clarification, not a schema change**: `use` on a portal target causes an engine-owned scene transition, and the next perception's `scene` reports it. The contract is shared with Fusion: **tell Joshua and flag it for the Fusion side** before merging the wording. T6 needs no schema change either, unless Joshua decides perception should report pose and facing (§0); that would be a schema/version change, not a clarification.
- ASFDK: the intent-specific TOI policy mapping is still marked pending. Log scene transitions as a new class of physical effect at ingress. Do not change the gate's policy without escalation.
- Stale text found while reading, fix opportunistically:
  - `world-engine-godot/AGENTS.md` §3 says character collision is not implemented, and its "only writer" rule should name `AgentBrain`'s placement method once T3 lands.
  - `world-engine-godot/AGENT-SYSTEM.md` §8.1 says no `AgentBrain` is instantiated; §8.6 correctly describes the physics body but says interiors stand on `AvatarGround` until their own collision lands (`InteriorPhysicalBoundary` exists).
  - `docs/active-threads.md` has duplicated ENG-002/DIV-001/PHYS-001 sections, and GRAPH-002's status line is out of date.
  - `docs/agent-log/README.md`, `.nltotoi/` and `docs/world-engine/DESIGN.md` call this repo `nlt-fusion`, its old name. Do not read that as Fusion (`neurolift-ai-fusion`).

## 4. Thread entry in `docs/active-threads.md`

Added 2026-10-18 as the AGENT-LOOP-002 entry (unclaimed). Claim it there before starting.

## 5. Out of scope here

Residents/NPC population, role pins, art and asset work (GRAPH-001 G1), the training environment (step/reset/reward), running interiors and the open world side by side, pathfinding, and the full GP-3 control cluster.

---

## Revision log

**2026-10-18 (second read of the code at `3dce1a8`; nothing built or run):**
- Repo name corrected to `nlt-world-engine`; "Fusion" defined as `neurolift-ai-fusion`.
- §1: the "only writer" rule is already broken by `AgentBrain` and `Main`; the placement method belongs on `AgentBrain`. GRAPH-002 coordination note updated. csproj paths corrected.
- §2 corrections: one of four replay fixtures is `open_world`; `ShowScene` runs on scene-id change, not every document; door ids use `home|office|shop|school`; home doors never afford `use`; arrival installs `IdleController`, not wander.
- §2 additions: no per-scene anchor lookup in `AgentLoopDriver`; node names resolve before anchors; `ShowScene` fails unsafely and the `--scene` pin swallows requests; spectator doors bypass the avatar; the avatar's scene and spawn come from the feed; the kill plane is open-world only; many doors are out of range from the plaza; every anchor reports `kind: place`; `rest` may carry a target.
- Tasks: T1 owns spawn, display precedence and spectator doors; T2 makes anchors per scene; T3 adds the arrival hook, the safe `ShowScene`, the `DecisionHold` reset, the scene-aware kill plane and a scripted sweep; T4 notes the exit re-target; T5 fixes target resolution and `kind`; T6 defines targeted `rest`.
- T6 (after PR review): the "pose/state in the next perception" requirement removed, since v1's `self` has only `position` and `velocity` and forbids extra fields; pose and facing are shown on screen, and reporting them is a new open decision in §0. Occupancy checks now use a second avatar's view, because the holder's own perception reports `occupied: false`.
