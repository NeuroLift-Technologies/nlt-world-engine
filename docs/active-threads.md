# Active Threads — nlt-world-engine

> This file tracks active work threads. Agents must read this at session start and update it during and at the end of each session.

**Last updated:** 2026-10-22

---

## Active Threads

### 🎨 GRAPH-002 — Dashboard-first graphics execution (GP-1 world fidelity + GP-3 HUD)
- **Status:** open — claimed, baseline captured, not yet started
- **Owner:** **OPENCODE** (claimed 2026-10-10) · **Plan:** `world-engine-godot/AGENTS.md` §5
- **Scope:** the two agent-executable phases of the new dashboard-first graphics plan in
  `world-engine-godot/AGENTS.md` §5. **GP-0 and GP-2 are explicitly out of scope** — GP-2 is blocked
  on Joshua's GRAPH-001 G1 decisions and must not be started.
  - **GP-1** world fidelity from primitives (terrain PBR + shadows, building vocabulary, vegetation
    LOD, water/shoreline, lighting/grade).
  - **GP-3** the dashboard HUD (district rail, environment header, POI labels, agent card goals,
    events feed, right control cluster, minimap, status bar).
- **Baseline captured 2026-10-10** → `world-engine-godot/Images/Screenshots/_boot_probe.png`
  (1152x648, `--capture`, reading level Simple). The observer boots **into an interior**, not the
  aerial open world the dashboard vision shows: every replay fixture under `fixtures/replay/` declares
  `personal_1`, so `Main.OnDocumentChanged` → `WorldView.ShowScene` selects the personal level on the
  first document. The dashboard's hero shot — the aerial coastal city — is therefore never on screen
  at boot, which blocks screenshot comparison for all of GP-1.
- **Open (needs Joshua's call, not an agent's):**
  - **`Main.tscn` still carries a `NobodyWhoModel` node bound to a 639 MB local GGUF.** The escalation
    [`docs/escalations/2026-10-03-addons-external-integration-approval.md`](escalations/2026-10-03-addons-external-integration-approval.md)
    ruled NobodyWho **must not be installed in `world-engine-godot`** (approved for Fusion-side use
    only). `addons/nobodywho/` and `ml-MODELS/` are gitignored and untracked, but the tracked
    `Main.tscn` still references the node type — a fresh clone cannot open the main scene. Reported,
    not touched: not graphics scope.
    **✅ RESOLVED 2026-10-16 (Joshua):** NobodyWho was downloaded for evaluation only; the
    `NobodyWhoModel` node was removed from `Main.tscn`. The untracked addon/model on disk are inert.
  - **✅ RESOLVED 2026-10-10 — the open world is now reachable and screenshot-able. The diagnosis in
    this thread was wrong; see below.**
  - **Verification path is degraded.** `AGENTS.md` §2 requires a captured screenshot for every
    graphics change, but the Fennara `runtime_session` cannot boot the scene (see below) and
    `screenshot_scene` returns a black frame. The working path is a direct CLI run.
- **GP-1 progress 2026-10-17 (CLAUDE, branch `feat/godot-building-archetypes-terrain`):**
  - **Terrain was never rendered.** `TerrainBuilder` wound every triangle counter-clockwise seen from
    above, so all faces pointed down and were back-face culled; the "ground" observers saw was the
    water plane ~7 m below the town. Winding fixed; vertex colours now flagged sRGB.
  - **One silhouette per building kind** (`BuildingArchetypes.cs`): Home (gabled house), Office
    (glass-banded tower), Shop (storefront + awning + café tables), School (brick block, portico,
    cupola, flag).
  - **Agent perception bug:** `WorldAnchors` cast the `[0,1)` random `plan.Kind` to `BuildingKind`,
    so every door was perceived as a Home. Both renderer and anchors now read
    `SettlementBuilder.KindAt(index)` — agents now perceive offices/shops/schools as busier.
  - **Night readability:** Sky3D's REALISTIC moon is usually down or dim, so nights rendered black. A
    renderer-owned shadowless `NightFill` light fades in with sun energy; night ambient draws more
    from Sky3D's tint (`night_sky_contribution` 0.3); the unshaded water dims with it.
  - **Capture flags:** `--hour <0-24>` pins the sky clock; `--focus <x>,<z>[,<dist>]` pins the
    camera. Evidence: `Images/Screenshots/{settlement-archetypes,terrain-fix-h0,terrain-fix-h12,lake-h0,lake-h12}.png`.
  - **Fennara `runtime_session` still cannot boot on the dev PC** — its fixed 20 s startup deadline
    expires during the mono/UHD 630 boot. Not configurable; the CLI capture path is used instead.
  - **Personal (Home) interior, 2026-10-17 (CLAUDE, branch `feat/godot-collision-personal`):**
    `InteriorStyle.cs` dresses `Personal_Level` by object name (the UE export gave every mesh the
    same `MI_Wall_Light`); one of four colour schemes per house (`personal_<n>`); wood room floor,
    lawn outside, ceiling fixtures hidden; steeper (~54°) interior camera. Clicking anywhere on a
    building enters it (ray hit on its collision box → portal index). Reviewed Cline's collision
    work and corrected: open-world bodies now leave the physics space while an interior shows
    (they overlapped the room at the origin); home floor collision now from `UCX_Floor` (the
    hand-placed box was centred on the 80 m slab and missed the north third of the room); removed
    a duplicate, broken `--focus` from `ObserverCapture`. `AvatarGround` (flat y=0 floor in `Main`)
    let avatars walk on the lake/sea surface — **Joshua 2026-10-17: off in the open world**; it now
    stays on only inside interiors as a backstop. An avatar that walks into water now wades down
    onto the lake/sea bed (terrain body); no swim/shoreline rule exists yet.
  - **Fusion tour + server fixes, 2026-10-17 (CLAUDE):** the agent-loop avatar walked off the home
    interior and fell repeatedly — the tour's anchors are open-world, the default feed shows the
    home, and #102 had removed the open world's physics under interiors. Now physics stays where
    the live bodies are (interiors display-only while a tour runs), the tour starts in the open
    world on the plaza, and the kill-plane lands over-water falls on the plaza. Fusion server
    (`addons/fusion_agent_loop`) hung while still listening on 8001: output was piped, the pipe
    read failed (`PeekNamedPipe` errors), the pipe filled and uvicorn blocked. Server output now
    goes to `user://fusion_agent_loop_server.log` (tailed in the dock); Stop kills the whole venv
    process tree. Verified the launch path end-to-end on port 8011.
  - **All four interiors dressed, 2026-10-17 (CLAUDE):** `InteriorStyle` now has rule sets for the
    office (`WF_*`), café (`Cafe_*`/`Social_*`) and classroom (`Academic_*`, desks, bookshelves),
    3–4 colour schemes per kind; every building's portal is `<kind>_<n>` so each building looks
    like its own place. Paving/lawn added around levels that floated in the void; UE placeholder
    character meshes hidden. Collision generalised: `HomePhysicalBoundary` →
    `InteriorPhysicalBoundary`, attached to all four level scenes (79/49/56 UCX meshes for
    workplace/social/academic). New capture flag `--scene <id>` pins an interior. Evidence:
    `Images/Screenshots/interior-{workplace_1,workplace_2,social_1,academic_1}.png`.
  - **Decisions recorded (Joshua, 2026-10-17):** art target is Cities: Skylines + The Sims 4
    (stylised-realistic, start lesser and step up); clicking a building opens its **interior view, not
    a cut-away**; deployment target is a cloud VM viewed in the browser (delivery method undecided).

---

### ✅ Open world reachable — GP-1 unblocked (GRAPH-002, 2026-10-10)

**The correction first, because the entry above recorded the wrong diagnosis.** The open world was
never blocked by renderer behaviour. `WorldView.ShowScene` already handles `open_world` correctly and
the contract (`docs/contracts/state-feed-v1.md` §3) already defines it — the renderer was following
the feed correctly. The actual cause was that **no fixture ever exercised the path**: all four bundles
under `fixtures/replay/` declare `scene.kind: "interior"`, so the observer could only ever boot into a
room. A missing-data problem, not a missing-feature one.

| Piece | Where | Notes |
|---|---|---|
| Open-world replay bundle | `fixtures/replay/open-world-day.json` | 12 frames, `scene.id` and `kind` both `open_world`, an avatar + aide walking out of the settlement. Agent **y values are read from `WorldGeometry.HeightAt`** — the same function the terrain mesh is built from — so residents stand on the ground, not in it. |
| Authoring tool | `tools/make_open_world_fixture/` | Standalone csproj outside the Godot compile glob. Borrows `WorldConstants.cs`/`WorldGeometry.cs` by link rather than copying, so it cannot drift from the renderer. |
| `--fixture <name>` | `Observer/ObserverCapture.cs`, honoured in `ObserverRoot.Attach` | Selects which bundle loads; accepts a bare name or a full `res://` path; inert without it. Names a *fixture* rather than forcing a scene, so it cannot paper over a renderer that ignores the feed. |

**All 12 frames pass `tools/validate_state_feed.py`.** Two schema traps found by reading the loader's
own errors rather than guessing:
- A replay **bundle's** top-level `schemaVersion` must be `nlt.state-feed.replay.v1`, not the document
  schema — `FixtureFeedSource` dispatches on it to decide whether to unwrap `frames[]`. Writing the
  document schema made the reader treat the bundle as one document and reject it for missing `tick`.
- `pairs[]` is a **Fusion gate report** (`overallScore`, `blockingDimensions`, six `dimensions`), not a
  relationship summary. A plausible `{since, focusAgentId, supportLevel}` was rejected for missing
  `overallScore`.

**Two pre-existing bugs fixed, both in the capture/build path:**

1. **`ObserverCapture` argument parsing read the wrong element when a flag was absent.**
   `Array.IndexOf` returns `-1` and `-1 + 1 == 0`, so `if (at + 1 < args.Length)` passed and read
   `args[0]` — an unrelated argument — as the flag's value. A plain `--selftest` run tried to open
   `res://fixtures/replay/--selftest.json`, reported a missing file, and laid the transport toolbar out
   one button wider than the window (2 selftest failures). The same shape sat in the `--capture`,
   `--level` and `--frames` reads, harmless only because those values failed to parse. All four now go
   through one `ValueAfter(args, flag)` helper.
2. **`tools/**/*.cs` was missing from the Godot project's `Compile Remove` glob.** A standalone tool on
   the Godot SDK writes a nested `.godot/mono/temp/obj/` tree *inside* the project; `**/*.cs` swept up
   its generated `AssemblyInfo.cs` and broke the next engine build with CS0579 "duplicate
   `TargetFrameworkAttribute`". Added alongside `AgentHarness` and `AgentLoopEndpoint`.

**Verification:** build 0 errors (`--no-incremental` — an incremental build hides warnings, as it did
here); AgentHarness **40/40**; `--selftest` **LAYOUT OK** on all three bundles (default,
`open-world-day`, `collapse-only`). Screenshots at all three reading levels:
`Images/Screenshots/gp1-openworld-{simple,coach,technical}.png`, beside the GP-3 interior captures.

**GP-1 is unblocked.** The next real GP-1 work is raising the world's fidelity itself: terrain PBR and
the `CastShadow = Off` re-enable, `SettlementBuilder` vocabulary (window insets, rooflines, façade
materials), vegetation LOD, water/shoreline, and lighting/grade.

**Verification tooling defects found 2026-10-10 (pre-existing, both defeat screenshot evidence):**

| Defect | Evidence | Workaround |
|---|---|---|
| **Fennara `runtime_session.start` cannot boot `Main.tscn`** — `startup_timeout`, "Runtime process did not report scene readiness before the startup deadline". Scene start exceeds the daemon's hard 20 s deadline. The process itself is healthy: it logs `StateFeedLoader: loaded …`, writes the capture, and exits 0. | `runtime_session.log`, startup deadline 20062 ms | Direct CLI (below). Not fixed here — daemon timeout policy is not an agent's call. |
| **`screenshot_scene` on `Main.tscn` returns a solid black frame.** A detached editor-side capture never runs C# `_Ready`, so `WorldView._Ready` never builds terrain/settlement/vegetation and the camera sees nothing. Removing the `NobodyWhoModel` node from the detached graph does not help. | 1600px capture, entirely `#0e1116` | Direct CLI. Do not treat a black Fennara capture as a rendering failure — it is a capture-path failure. |
| **`Images/Screenshots/` did not exist** although `AGENTS.md` §2 requires screenshots to land there. | directory listing | Created. |

**Working screenshot command** (the one that produced `_boot_probe.png`):

```powershell
$exe = "$env:LOCALAPPDATA\Godot\Godot_v4.7.2-stable_mono_win64\Godot_v4.7.2-stable_mono_win64_console.exe"
& $exe --path "$PWD" -- --capture "res://Images/Screenshots/<name>.png" --frames 120 --level simple
# exits 0; honours --level {simple|coach|technical} and --selftest
# also: --fixture <replay-name> (e.g. open-world-day), --hour <0-24>, --focus <x>,<z>[,<dist>]
```

**GP-3 delivered 2026-10-10 — three of the dashboard's HUD elements, all three reading levels:**

| Element | File | Notes |
|---|---|---|
| Environment header (top-right) | `Observer/EnvironmentHeader.cs` | Four chips — Persistent World · Multi-Agent · Real-Time Physics · Scenario. **Every chip prints the live fact behind its claim** (seed, agent count from the document, the backend read from `ProjectSettings`, the feed's own scene label). No fabricated data, per AGENTS.md. |
| Minimap (bottom-right) | `Observer/Minimap.cs` | Land sampled once from `WorldGeometry.HeightAt` — the same field `TerrainBuilder` builds its mesh from — so it is a real map, not a stylised shape. North-up, zoom `[`/`]`, settlement + agent markers, palette-derived height ramp. |
| Recent events | `Observer/EventFeedPanel.cs` | Rows accumulate rather than replacing per document. Wording/shape/colour all come from the existing `PlainLanguage` vocabulary, so it cannot describe an event the feed has no word for. |

Wiring is additive: three new files under `Observer/`, plus `ObserverRoot` (new fields, `BuildDashboardChrome`, `PlaceDashboardChrome`, one `Wire(...)` line). **`WorldView.cs` and `Main.cs` were not touched** — the hot-hub peer work is untouched.

**Three real bugs found and fixed along the way — all Godot `Control` placement traps, all recorded as comments at the site:**

1. **Anchors without offsets move nothing.** `SetAnchorsPreset(TopRight)` leaves offsets at 0, so a negative `Position` was measured from the *left* edge. Both overlays sat off-screen at global `(-532, 56)` while reporting `Visible = true` and a perfectly reasonable local `Position`.
2. **Moving a `Control`'s anchors also resizes it.** A `Control`'s rect is derived from anchors *and* offsets together, so re-anchoring collapsed the header to `(12, 0)` and the minimap to `(291, 12)`. Sizes are now set explicitly and captured as constants, never read back after a move.
3. **`GetGlobalRect().End.X` is the window edge for a split's last child.** Offsetting the overlays by the right rail's *width* threw both off-screen at Technical; the rail's `Position.X` (873) is the edge that actually moves when the divider is dragged.

Also fixed: `PlainLanguage.Duration` was reused for event *ages*, producing rows reading "started a task for about 12 seconds" — which describes the task, not the row. Added `PlainLanguage.Ago` ("12s ago" / "just now").

**Verification:** `dotnet build` 0 errors (the same 2 pre-existing `WorldView.cs` nullable warnings, no new ones); AgentHarness **40/40**; `--selftest` **LAYOUT OK**, and the one remaining no-shortcut warning is the pre-existing follow-target `OptionButton`, not new. Screenshots at all three levels: `Images/Screenshots/gp3-dashboard-{simple,coach,technical}.png`.

**Not done, and why:**
- **Right control cluster** (Spectator / Follow Agent / Free Camera / Scenario) and **district nav rail** need camera-mode seams in `WorldView.cs` — deliberately deferred under the "keep edits additive and disjoint" decision, since they cannot be done additively.
- **Agent role pins** are GP-2 and blocked on Joshua's GRAPH-001 G1 decisions.
- **Agent-card goals list** needs a goals field on the feed; none exists, and inventing values the feed does not carry is forbidden.

**✅ Resolved 2026-10-16:** the `NobodyWhoModel` node in `Main.tscn` (bound to a 639 MB local GGUF) was removed on Joshua's decision — it was an evaluation download, not an integration.

### 🌐 WEB-001 — Public homepage on GitHub Pages

- **Status:** open — live; content decisions pending with Joshua
- **Owner:** Joshua (content decisions) · Claude Code (session `claude/zealous-newton-9g28lz`)
- **Started / Last updated:** 2026-10-17
- **Summary:** `web/index.html` is the public homepage. Joshua added `.github/workflows/static.yml` (GitHub Pages via Actions) on 2026-10-17 and approved deploying it. The workflow now publishes only `web/` as the site root, so the homepage is served at `https://neurolift-technologies.github.io/nlt-world-engine/`, and it runs only when `web/**` or the workflow changes. Its first run had uploaded the whole repository (~1.49 GB, mostly the frozen UE tree), which left the site root at 404 and served `_archive/` drafts as live pages. The mobile menu was fixed: it opened upward over the hero with no background and stayed open after a tap. The Agent loop status row now reflects the 2026-10-17 human verification. Polish pass (Joshua's brief, 2026-10-17): the hero now uses `web/hero-sunset-bridge.webp`, a clean crop of the `Dashboard-2.png` mockup with no baked-in interface, so the HTML snapshot card is the only HUD; phones get a darker top-down overlay (paragraph contrast ≥ 11:1 at 390px); the primary hero button reads "See the Architecture" (restore "Explore the World" when an explorable build ships); the supervision caption now matches Project Status. Current Build section (Joshua's ask, 2026-10-17): `#progress`, between Architecture and Project Status, shows real observer captures from `world-engine-godot/Images/Screenshots` (open world day/night and the four interiors, cropped to the 3D view, each linking to its full observer screen in `web/progress/`); real engine captures only, never concept art. To fit its nav link, the redundant "Home" link was dropped (the logo links home) and the inline nav now switches to the Menu button below 1180px instead of 900px; it had already been wrapping to two rows over the hero between 901 and ~1100px. Follow-up pass (Joshua's brief, 2026-10-17): hero card renamed "World Snapshot (concept)" so its 24 agents / Workplace can't be read against the observer's real "2 agents"; the six tiles are 4:3 crops framed on agents and furniture (were 560×206 banners); the featured observer image has a visible "Open full size ↗" label, click-through verified; tiles stay two-up on phones (page 10,828 → 10,244px at 390px); the Scenario library row text now matches GRAPH-002.
- **Pending (Joshua):** the Agent loop status percentage (still 40%); the Scenario library status percentage (still 15%; its text was updated 2026-10-17 to match GRAPH-002); higher-resolution originals of the hero and scenario art if they exist (the current images are upscaled crops of mockups).
- **Note for agents:** the Project Status rows in `web/index.html` summarise threads in this file, so a status change here can leave the public page stale (as happened with AGENT-LOOP-001 on 2026-10-17).

### 🔁 AGENT-LOOP-001 — Fusion semantic / Godot physical closed loop

- **Status:** protocol, governance gate, intent ingress, perception builder, async loopback HTTP transport, and an opt-in one-avatar Godot scene path delivered. **The closed loop is verified end to end in an interactive Godot runtime** (see *Human verification*): a model-chosen intent moved the local avatar to the target, it stopped there, and the next perception reported its new position. Fusion `SessionOrchestrator` integration remains separate.
- **Human verification (reported by Joshua 2026-10-17):** in an interactive Godot run of the opt-in loop, a **Qwen 0.6B** model served by Fusion chose an intent that moved the avatar to a target location in the world, and Joshua watched the avatar walk to the target. This is the first observed end-to-end path: engine perception → Fusion model decision → ASFDK-governed ingress → engine-owned locomotion. **Follow-up confirmation (Joshua, 2026-10-17):** the avatar stopped at the target (the 1 m arrival radius is the local `ArrivalRadius` constant in `AvatarCharacter.ApplyIntent`), and the run's logs showed the next perception reporting its new position. All three parts of the gate are now met.
- **Decision:** use a closed loop (engine-owned perception → Fusion semantic intent → engine-owned execution/result). **Transport decided 2026-10-08 (Joshua): asynchronous loopback HTTP request/response** — Godot POSTs each perception to a Fusion endpoint; Fusion returns a correlated intent. Chosen because it fits the single-avatar low-frequency decision cycle, is straightforward across C# and Python, and avoids a persistent WebSocket session. Revisit WebSockets only if later requirements need streaming or multiple high-rate channels. Constraints: model inference stays off the Godot physics/render thread; enforced timeouts; one in-flight request per avatar; stale ticks rejected; fail closed on transport errors. Godot still performs ASFDK governance, live-world validation, and physical execution.
- **Ownership:** Fusion owns semantic decisions; the world engine owns physical facts, target/affordance validation, movement, collision, and consequences; ASFDK-C# governs intents at engine ingress before physical execution.
- **Delivered:** `docs/contracts/agent-loop-v1.md` and its JSON Schema; strict Godot DTO parsing/validation; Fusion-side injectable decision/validation seam; `Agents/GovernanceGate.cs` with real `asfdk-csharp` integration; `Agents/IntentIngress.cs` with contract validation, fail-closed gate errors, live-world revalidation, and locomotion dispatch; `Agents/PerceptionBuilder.cs`; and focused harness assertions. **Transport:** `Agents/FusionHttpLink.cs` (async POST, 30 s timeout (`RequestTimeoutSeconds`, was 5 s), one in-flight request per avatar, correlated response validation, fail-closed transport handling) + `Agents/AgentLoopDriver.cs`; Fusion `src/fusion/agent_loop_http.py` (FastAPI endpoint, inference off the event loop, GGUF or deterministic fallback). **Test composition:** set `NLT_AGENT_LOOP_ENABLED=1` to create only the local test avatar, a visible target marker, and a driver filtered to that avatar; `NLT_AGENT_LOOP_ENDPOINT` overrides the loopback endpoint. Default observer runs are unchanged. The explicit `OpenGovernanceGate` test implementation is fail-open with an audit explanation; the live driver uses `AsfdkGovernanceGate`, and ingress rejects gate exceptions. Previously verified: Fusion tests 19 passed/1 skipped and cross-process HTTP smoke test passed. Latest verification: Godot build succeeded with 0 errors (2 existing `WorldView.cs` nullable warnings), AgentHarness passed 38/38, and GDA 0.22.0 validated and booted the main scene. Its opt-in run against the GGUF-backed Fusion endpoint received HTTP 200; a direct model request returned an `approach` intent for `agent_loop_test_target`. GDA also exposed and the implementation corrected startup sequencing and marker attachment errors.
- **Open:** Fusion's seam is not integrated into `SessionOrchestrator`; the direct HTTP endpoint currently serves the separate world-engine loop. Cross-process smoke automation in CI remains. GDA preflight prints the existing `Capture not registered: 'beehave'` engine error, although its structured result is `started: true` with no recognized diagnostics; this appeared on default and opt-in scene runs.
- **Next gate:** The interactive gate is passed (2026-10-17). The loop's next direction is Joshua's call — candidates include the remaining semantic verbs in the contract, more than one avatar, Fusion `SessionOrchestrator` integration, and automated cross-process smoke coverage in CI. Retain fail-closed ingress behavior, and keep the loop opt-in. **Chosen (Joshua, 2026-10-17):** scene transitions come next, before RL training — see AGENT-LOOP-002.

### 🚪 AGENT-LOOP-002 — Scene transitions and interior interaction

- **Status:** open — **T1 delivered 2026-10-18** (scene catalog, view follows the loop avatar's scene, spectator doors locked while the loop runs; spawn at the plaza came with the earlier fusion-tour fix); **T2 delivered 2026-10-18** (doors and room exits are `use` targets, each scene sees only its own anchors); **T3 delivered 2026-10-18** (`use` on a door or exit moves the avatar between scenes, engine-placed); **T4 delivered 2026-10-18** (camera follows the loop avatar across scenes, or stays free); **T5 delivered 2026-10-18** (furniture anchors in every room: things to sit on and use); **T6 delivered 2026-10-18** (sit, use, rest and look_at execute); **T6 acceptance 4 not met, 2026-10-21** — the model-driven Qwen run was done on the dev PC and the shipped Fusion adapter cannot choose `sit` or `use` (see below; needs a Fusion-side decision); **rerun 2026-10-22 with Fusion#126 and #111, still not met** — Qwen now may choose every verb but picks `look_at` on whichever entity is listed first, and with nothing in perception range `wait` now freezes the avatar for good (see below; needs Joshua) · **Owner:** CLAUDE (T1–T6 done; acceptance 4 blocked on a Fusion goal/policy and on Joshua's call about `wait` with nothing visible) · **Started:** 2026-10-17 · **Spec:** `docs/agent-log/AGENT-LOOP-002-scene-transition-briefs.md`
- **T1 verification (2026-10-18, Linux, Godot 4.7.2 .NET):** build 0 errors (2 known `WorldView.cs` warnings); AgentHarness 59/59 (19 new scene-kind checks); in-engine with the loop on and the default `personal_1` replay, the open world shows, the avatar spawns at the plaza, perception reports `open_world/open_world`, and `E` is refused (on `main` the same press swapped the view into a room under the walking avatar); loop off, the feed's room shows and `E` exits as before; `--selftest` LAYOUT OK on all three levels under Xvfb, identical to `main`.
- **T2 verification (2026-10-18):** build 0 errors (2 known warnings); AgentHarness 79/79 (20 new door/exit checks; breaking the doorway rule fails 6 of them); in-engine, each room's exit anchor fits the avatar capsule with no collision hits. **Found for T3:** the home level's floor collision is at y = −4.01 (only `AvatarGround` holds an avatar there), the café's north wall collision is still solid behind its visual doorway, and with the loop on a shown interior is display-only (`OpenWorldBodiesLive`). Details in the brief's T2 section.
- **T3 verification (2026-10-18):** AgentHarness 91/91 (12 new transition checks). In-engine, against a scripted Fusion stand-in on the real HTTP path, the round trip passed for all four kinds (home, office, shop, school):
  - `use door` → walk → placed inside on the floor, y constant for 2 s, room physics on, open world off;
  - `use exit` → back outside at 0.00 m from the same building's entry point, open world visible with collision on;
  - `use door` while already standing on it transitions with no walk;
  - with a `--scene` pin, `use door` is rejected with a reason and the avatar does not move.
  Reachability sweep from the plaza (straight lines, no pathfinding): 7 of 10 doors reached; `door_2_shop`, `door_3_school` and `door_8_home` stall on other buildings. Screenshots: `Images/Screenshots/t3-outside-before.png`, `t3-inside-after.png`. The contract clarification still needs Joshua and the Fusion side.
- **T4 verification (2026-10-18):** follow on — 0.00 m after entry and exit, at most 0.37 m while walking; follow off — camera still while the avatar walks 4.9 m, zoom and orbit respond. Before the fix, follow sat 8.35 m off (it tracked the replay ghost). Found for GRAPH-002: the observer header and the replay ghosts follow the feed's scene, not the avatar's.
- **T5 verification (2026-10-18):** AgentHarness 106/106 (15 new). In-engine:
  - furniture anchors per room: home 12, office 19, café 28, classroom 39, each with things to sit on and to use; ids stable on rebuild;
  - a loop `approach` ends at the approach point, not the object's centre;
  - straight-line reach from each room's arrival point: home 5/12, office 14/19, café 17/28, classroom 29/39. The approach points are all clear; the rest are blocked by walls and furniture in the way. **Escalation (Joshua):** no pathfinding, and perception has no line-of-sight check, so a model can pick furniture it cannot walk to. **Joshua, 2026-10-18:** leave it for now; revisit after the real-ML run (also raised by CodeRabbit on PR 107).
- **T6 verification (2026-10-18):** AgentHarness 113/113 (7 new). In-engine, office, through the real loop:
  - `sit` holds a chair; a second avatar's `sit` is rejected "occupied"; the chair is released after the hold;
  - `use` holds a desk, then releases it;
  - `look_at` turns the avatar to face the object (0.0°) without moving;
  - the T3 round trip still passes.
- **T6 acceptance 4, model-driven run (2026-10-21, dev PC, CLAUDE): not met — a Fusion-side finding, not an engine defect.** World engine at `e866e75` (build 0 errors, AgentHarness 113/113); Fusion `src.fusion.agent_loop_http` with `Qwen3-0.6B-Q8_0.gguf` on CPU, endpoint on port 8011 so the editor dock's 8001 was untouched.
  - **The shipped adapter cannot pass it.** `gguf_agent_decision.py` (same on Fusion `origin/main` and local `pr-125`) grammar-constrains Qwen to `{"verb":"wait"}` or `approach` + a visible id. `sit`, `use` (including `use` on a door, the only way into a room) and `rest` are unreachable, even though Fusion's own `agent_loop.py` contract allows them.
  - **Shipped path, warm boot, ~4.5 min:** 110 perceptions, 41 decisions — 39 `wait`, 2 `approach`; every perception had at least one visible door or place (106 of 110 had 2–7); the avatar never left the open world. (A first boot right after a fresh build got 3 answers in ~2 min: the first call ran past the 30 s request timeout and Fusion answered 429 until it finished.)
  - **Scratch probe, not shipped:** the same model and Fusion validation with the grammar and prompt widened to the contract's verbs (a local wrapper around `LlamaCppAgentLoopDecision`, committed to neither repo). In-engine, 84 decisions: `look_at` 81 (45 at `plaza`), `wait` 3; `use` was offered on 81 and never chosen, so it never entered a room. Standalone (no Godot), the same probe chose `use door_1_office` on a synthetic 5-door perception, so the choice is sensitive to the scene. At temperature 0, Qwen 0.6B collapses to one safe verb.
  - **Latency on this PC:** ~4–5 s per decision with no test run of the game going, threads 2 or 6 alike (likely llama.cpp's grammar sampling, not compute); during the test runs it varied from ~4 s to 30 s+. Neither figure is an uncontended baseline: a separate editor-launched debug run of the game was using the CPU throughout every timing, so all of them are CPU-contended and pessimistic. Note `FusionHttpLink.RequestTimeoutSeconds` is 30 s (since `5f83520`), not the 5 s AGENT-LOOP-001 records.
  - **Needs Joshua and the Fusion side:** whether the GGUF adapter should emit the contract's other verbs, and with what prompt/policy, before acceptance 4 can be rerun. The contract itself needs no change.
  - **Fusion side addressed (2026-10-21):** NeuroLift-Technologies/neurolift-ai-fusion#126 (merged) lets both local adapters offer `use`, `sit`, `rest` and `look_at` on targets that afford them. With that and the `wait` change below, acceptance 4 can be rerun.
- **First real-ML run (Joshua, 2026-10-21):** the avatar only walked around the world. Two causes:
  - `neurolift-ai-fusion`'s model prompt and parser allowed only `wait` and `approach`, so no door `use`, `sit`, `rest` or `look_at` could ever be chosen. That is fixed on the Fusion side.
  - Here, `wait` and an untargeted `rest` handed the avatar back to the wander tour. **Joshua, 2026-10-21:** `wait` holds still. Now `wait` and untargeted `rest` hold the avatar where it stands until the next intent (label "waiting"/"resting"). A `wait` arriving mid-walk lets the walk finish, as it already let an interaction carry on. In-engine before → after:
    - `wait` moved 3.70 m in 3 s → 0.00 m;
    - a `wait` 0.5 s into a 6 m approach abandoned all four test walks → the walk arrives;
    - untargeted `rest` moved 1.97 m → 0.00 m.
- **Spectator peek (Joshua, 2026-10-21):** with the loop on, clicking a building or pressing `E` was refused and only logged ("it doesn't go to the scene"). Now a click shows that building's room to the spectator. The avatar keeps living outdoors, unseen; physics stays with it, so the room shown is display-only. `E` or the exit returns to the avatar, and the view also goes with the avatar if it changes scene. While the avatar is inside a room, doors are refused with an on-screen note: only one interior can be loaded, and it must be the avatar's. A notice line under the scene strip says which case applies. In-engine (real click path, loop on):
  - click on the office: the room shows; the avatar stays in `open_world` on its own ground (y 7.38 → 7.35, still walking), hidden; the peek holds through 5 s of feed documents;
  - `E` returns to the avatar;
  - an avatar transition during a peek takes the view with it;
  - with the avatar inside, `E` is refused with the note.
  Screenshots: `Images/Screenshots/spectator-peek-inside.png`, `spectator-peek-refused.png`.
- **T6 acceptance 4 rerun (2026-10-22, dev PC, CLAUDE): still not met.** The adapter now offers every verb; the model does not choose them, and the avatar can get stuck. World engine `a728fd7` (`main`, with #111; build 0 errors, AgentHarness 113/113); Fusion `9aa44e9` (`main`, with Fusion#126; its loop tests 35 passed, 1 skipped); the same `Qwen3-0.6B-Q8_0.gguf` on CPU, port 8011, shipped prompt, schema and temperature 0. A pass-through wrapper (scratch, committed to neither repo) logged each decision beside the choices its perception allowed.
  - **Qwen picks `look_at` on the first-listed entity.** Through the shipped endpoint with no game running, 18 of 18 perceptions (office, home and open world, every ordering of three entities) returned `look_at <first entity>`, although `sit desk_chair_1`, `rest bed_1`, `use exit_*` and `use door_*` were allowed. The choice follows list order, not the scene. The perception carries no goal or need, so nothing makes one action better than another. Getting a `sit` or `use` needs a goal or policy on the Fusion side (or other sampling or another model); the contract needs no change.
  - **In-engine (editor closed, game at `--max-fps 20`): 34 decisions, 1 `look_at plaza` then 33 `wait`; the avatar never moved after its third perception.** From the plaza spawn only `plaza` and `well` are within `PerceptionBuilder.PerceptionRange` (25 m); no door is. The first decision took 55 s; meanwhile the wander fallback carried the avatar ~70 m south, out of range of everything. With nothing visible, `wait` is the only legal output, and since #111 `wait` holds still, so the avatar stood at (−64.4, 6.2, −27.9) from then on. Stopped after ~3 min.
  - **New dead end (needs Joshua):** once no entity is in range, the loop can never move the avatar again. Options: `wait` resumes the wander fallback only when nothing is visible; spawn or perceive so a door is always in range; or accept it while Fusion has no explore behaviour.
  - **Latency on this PC is a memory problem, not CPU.** 7.8 GB RAM. With the Godot editor and the game both open, ~1 GB was free and 14.6 GB committed; Windows paged out Qwen's memory-mapped weights and decisions took 120–400 s (4 decisions in 15 min; a 20 fps run never finished booting in 5 min). With the editor closed: 1.2 GB free while the game runs, and decisions after the first took 1.1–3.4 s (median 1.4 s). Run model-driven tests with the editor closed.
  - **Seen during the run (Joshua):** the avatar's feet sink below the plaza; the plaza has no collision. Recorded under PHYS-001.
- **Scope:** T1 per-avatar scene authority (including the loop avatar's spawn) → T2 door/exit targets and per-scene anchors → T3 engine-owned transition → T4 camera follow/free → T5 interior anchors → T6 interaction execution. T1–T4 deliver "go inside a building, camera follow or free"; T5–T6 deliver interior interaction. Builds on the verified AGENT-LOOP-001 path.
- **Decisions (Joshua 2026-10-17):** `use` on a door target (no new verbs, no schema bump); one live scene at a time; "without the camera following" means free look within the avatar's current scene; the engine, not Fusion, places the avatar.
- **Open (Joshua):** does `use` change world state (T6, default occupy only); perception `kind` for interior furniture (T5, default `object`); should perception report the avatar's pose and facing (T6, default no; v1 has no field for it, so yes means a schema/version change agreed with Fusion).
- **Coordinate:** `WorldView.cs`/`Main.cs` with GRAPH-002 (OPENCODE; confirm it is active, its status line is out of date); contract wording with Fusion (`neurolift-ai-fusion`) before merging the §3 clarification.
- **Records:** `docs/agent-log/handoffs/2026-10-17-claude-agent-loop-002-scene-transition-briefs.json` (briefs), `docs/agent-log/handoffs/2026-10-18-claude-agent-loop-002-brief-review.json` (review against `3dce1a8`; nothing built or run).

### 🧭 ENG-002 — Godot replaces UE

- **Status:** decision recorded; current repository docs now aligned.
- **Decision (2026-10-07, Joshua):** Godot replaces UE 5.8 in its entirety as the world engine's authoritative runtime. The UE tree remains frozen, non-authoritative historical reference material, not a conformance oracle.
- **Implementation scope:** Godot owns the complete physical simulation runtime, not just rendering. Fusion continues to own semantic cognition and intents; the transport-neutral boundary is tracked by `AGENT-LOOP-001`.
- **Historical plans:** `world-engine-godot/MIGRATION-PLAN.md` and `RENDERER-PLAN.md` describe superseded decisions and must not be used as current implementation instructions.

### 🧭 DIV-001 — Simulation ownership boundary (SUPERSEDED 2026-10-07)

- **Status:** superseded by Joshua's clarification the same day — the original principle stands: **Fusion owns semantics; `nlt-world-engine` owns the physical.** No joint-ownership rewrite is happening.
- **New requirement (2026-10-07, Joshua):** the AI must **"see" and interact with the physical world.** Concretely: agents need a perception surface (what they can see: nearby people, objects, places) and semantic actions (approach / look_at / use / sit / rest / communicate) whose physical effects — movement, collision, object state — are executed and owned by the world engine. This is the missing layer flagged in AGENT-SYSTEM.md gaps 1, 5, 6 and extends `AgentObservation` beyond its current self-state-only fields.

### 🧭 PHYS-001 — Jolt Physics as the engine's 3D physics backend

- **Status:** open — decision recorded; collision wiring still pending
- **Owner:** **Joshua** (decision), survey by Fledge (2026-10-07)
- **Decision (2026-10-07, Joshua):** the world engine's 3D physics engine is **Jolt**.
- **Survey result:** `world-engine-godot/project.godot` already declares `[physics] 3d/physics_engine="Jolt Physics"` (line ~41). No Jolt addon under `world-engine-godot/addons/` — Joshua confirms Jolt is built into the Godot build in use. Consistent.
- **Known gap this gates:** `AgentBrain` has no `CharacterBody3D`/physics body (AGENT-SYSTEM.md §8.6), `TerrainBuilderPhysics` is an empty placeholder — so movement still has no collision resolution. Wiring that up should target Jolt via `CharacterBody3D` + `move_and_slide()` and static level collision.
- **Update 2026-10-08 (Cline):** `AgentBrain` is now `CharacterBody3D` with `MoveAndSlide()` per-physics-tick + `AvatarCharacter : AgentBrain` capsule scene (`Agents/avatar.tscn`) + `Main.SyncLiveAvatars` spawning live Jolt bodies behind `EnableLiveAvatars=false`. `TerrainBuilderPhysics` still an empty placeholder; `EnsureAvatarGround` flat StaticBody3D covers levels without collision. AGENT-SYSTEM.md §8.6 is now stale and needs a refresh pass.
- **Update 2026-10-17 (Cline, claimed):** open-world collision wired — trimesh terrain body exact-matched to the visual mesh (`TerrainBuilderPhysics.TerrainBody`), one box collider per settlement building + well (`BuildingArchetypes.CollisionInfo`, added in `SettlementBuilder.Build`), four edge walls around the 460 m island (`WorldBounds`), and a kill-plane reset in `AgentBrain` (`KillY = −25 m`) that puts a tunnelled avatar back on the terrain. Door anchors moved from building centres (now inside the boxes) to outside the door (`FrontOffset` + 1.7 m) so the tour target is reachable. Interiors still stand on the flat `AvatarGround` safety plane; vegetation/props have no collision yet; the 0.5 m plaza/road step needs step-up logic. Build green (0 errors), harness 40/40. In-scene verification on the Jolt server still pending before close.
- **Plaza, roads and tree trunks, 2026-10-22 (CLAUDE; Joshua's calls):** during the AGENT-LOOP-002 rerun Joshua saw the avatar's feet below the plaza. The plaza (a 0.22 m disc centred 0.5 m above `SettleY`) and the roads (flat 0.2 m boxes at the same height) were visual only, and measured against the terrain the plaza floated 0.18–0.52 m above the ground avatars walk on, while the roads ran up to 4.3 m into hillsides and floated up to 0.97 m elsewhere. **Joshua chose to drape them on the terrain** rather than add colliders and step-up: the terrain body stays the one walking surface, so the 0.5 m step item above no longer applies to the plaza or roads.
  - `TerrainBuilder.SurfaceHeightAt` is the terrain mesh's own surface (the trimesh avatars stand on), not the smooth `HeightAt` field; `TerrainBuilder.Segments` is the shared grid size.
  - `SettlementBuilder.PlazaPaving` / `RoadPaving` build the paving 4 cm (plaza) and 3 cm (roads) above that surface. Roads use a 0.25 m × 0.31 m grid: coarser, the paving floated up to 9 cm off the terrain's creases on the hills. The well now stands on the ground; the benches, which sat flush in the old deck, are a seat on two legs.
  - **Trees (Joshua):** one `Collision_Trees` static body holds a cylinder per trunk (620), at the trunk's base radius from the ground to its visual top (`VegetationBuilder.ColliderFor`). Rocks, canopies and grass stay walk-through. It lives under the open world, so it leaves the physics space with it while an interior shows.
  - **Verification:** build 0 errors (2 known `WorldView.cs` warnings); AgentHarness 126/126 (13 new `[ground]` checks: surface vs field, paving faces up and lies 1.9–5.1 cm above the surface everywhere, plaza area, road extent, one trunk body per tree reaching the ground and past shoulder height). In-engine on Jolt (temporary probe scene, deleted): avatars dropped on 7 flat plaza/road spots settle within 1 mm of `SurfaceHeightAt` (feet 2.9–3.9 cm under the paving top); on the road hills within 3.5 cm. Walked into a trunk head-on, an avatar stopped at 0.84 m from its axis (radius 0.44 + capsule 0.40) and stayed there, 4.84 m short of its target; 0.3 m off-centre it slid round at touching distance and arrived. Screenshots: `Images/Screenshots/collision-{plaza,road}-{before,after}.png`.
  - **Known consequence:** with no pathfinding, an `approach` whose straight line runs through a trunk now stalls against it (it used to walk through). Trees sit at least 5 m from building footprints and about 16.5 m from the plaza centre, so door and plaza approaches should not meet one; open-world wandering can. Same pathfinding gap as AGENT-LOOP-002 T5, deferred by Joshua 2026-10-18.
- **Next action:** when agent embodiment gains collision, verify against the Jolt server (not GodotPhysics) and note any `CharacterBody3D` behavioural differences.

### 🧭 ENG-002 — Godot replaces UE

- **Status:** decision recorded; current repository docs now aligned.
- **Decision (2026-10-07, Joshua):** Godot replaces UE 5.8 in its entirety as the world engine's authoritative runtime. The UE tree remains frozen, non-authoritative historical reference material, not a conformance oracle.
- **Implementation scope:** Godot owns the complete physical simulation runtime, not just rendering. Fusion continues to own semantic cognition and intents; the transport-neutral boundary is tracked by `AGENT-LOOP-001`.
- **Historical plans:** `world-engine-godot/MIGRATION-PLAN.md` and `RENDERER-PLAN.md` describe superseded decisions and must not be used as current implementation instructions.

### 🧭 DIV-001 — Simulation ownership boundary (SUPERSEDED 2026-10-07)

- **Status:** superseded by Joshua's clarification the same day — the original principle stands: **Fusion owns semantics; `nlt-world-engine` owns the physical.** No joint-ownership rewrite is happening.
- **New requirement (2026-10-07, Joshua):** the AI must **"see" and interact with the physical world.** Concretely: agents need a perception surface (what they can see: nearby people, objects, places) and semantic actions (approach / look_at / use / sit / rest / communicate) whose physical effects — movement, collision, object state — are executed and owned by the world engine. This is the missing layer flagged in AGENT-SYSTEM.md gaps 1, 5, 6 and extends `AgentObservation` beyond its current self-state-only fields.

### 🧭 PHYS-001 — Jolt Physics as the engine's 3D physics backend

- **Status:** open — decision recorded; collision wiring still pending
- **Owner:** **Joshua** (decision), survey by Fledge (2026-10-07)
- **Decision (2026-10-07, Joshua):** the world engine's 3D physics engine is **Jolt**.
- **Survey result:** `world-engine-godot/project.godot` already declares `[physics] 3d/physics_engine="Jolt Physics"` (line ~41). No Jolt addon under `world-engine-godot/addons/` — Joshua confirms Jolt is built into the Godot build in use. Consistent.
- **Known gap this gates:** `AgentBrain` has no `CharacterBody3D`/physics body (AGENT-SYSTEM.md §8.6), `TerrainBuilderPhysics` is an empty placeholder — so movement still has no collision resolution. Wiring that up should target Jolt via `CharacterBody3D` + `move_and_slide()` and static level collision.
- **Next action:** when agent embodiment gains collision, verify against the Jolt server (not GodotPhysics) and note any `CharacterBody3D` behavioural differences.

### 🔭 OBS-001 — Phase D observer (Godot renderer + spectator)

- **Status:** open — D.1–D.5 delivered; **claimed by Kilo 2026-10-04**; mouse input and layout still need a human click-through
- **Owner:** **Kilo** (claimed 2026-10-04, authorised by Joshua — the previous owner could not be identified) · **Forked from:** `MIGRATE-001` · **Branch:** `main` ⚠️ *the thread's `feat/observer-phase-d` was merged (PR #83); uncommitted work now sits on `main`*
- **Started / Last updated:** 2026-10-03 · **claimed 2026-10-04**
- **Plan:** [`world-engine-godot/RENDERER-PLAN.md` §6](../world-engine-godot/RENDERER-PLAN.md)
- **Scope:** the six required panels, three reading levels, transport controls, accessibility, and the four-way burnout reading. Godot is a **renderer** here — it reads state and shows it, and computes no level, burnout verdict or fusion score (contract §2).
  - **Extended 2026-10-04 by Joshua's direction:** reading level now also governs *how much* of the observer exists at once (not only wording depth), and panels are user-resizable by drag or keyboard.
- **Delivered:**
  - `world-engine-godot/Observer/` — six panels, `ObserverRoot` layout, `AccessibilitySettings`, `BurnoutNarrative`, `PlainLanguage`, `Ui` (colour-safe palette + glyph vocabulary), `WorldViewHud`, `ObserverCapture`.
  - `world-engine-godot/Feed/` — a replay-capable reader and transport. **Reuses PR #80's model types unchanged**; adds only what Phase A's single-document loader does not do (a *sequence* of documents, and reporting problems instead of throwing).
  - `tools/make_replay_fixture.py` + `world-engine-godot/fixtures/replay/` — three multi-frame bundles that make the Learning Timeline and all four D.5 readings reachable. The StayAlert bundle's final frame is asserted content-equivalent to `state-feed.sample.json`, so the two fixtures describe one history.
  - Verification: 43-case feed harness (parse/validate against 18 mutated fixtures, every bundle, coherence check), `--selftest` layout assertions, rendered capture at all three reading levels.
- **🔴 Blocker — mouse input is unverified.** Synthetic `Input.ParseInputEvent` does not reach Godot's GUI in this environment: a bare probe `Button` outside the observer is equally unclickable, so a click-based test is a false negative and was discarded. Layout, popup geometry and shortcuts are asserted; **clicking needs a human.** Every control also has a keyboard shortcut (`1`/`2`/`3`, `Space`, `←`/`→`, `End`, `R`, `O`, `F1`–`F4`), so the observer is fully operable without a mouse.
- **Bugs found in existing work, reported not silently absorbed:**
  - `tools/validate_state_feed.py` **failed the shipped fixture** — the contract and fixture spell the assisted-recovery mode `rrt`, the validator accepted only `rt`. Fixed to accept `rrt` and warn on `rt`; which spelling Fusion emits is Joshua's call. See [`docs/escalations/2026-10-03-state-feed-recovery-mode-spelling.md`](escalations/2026-10-03-state-feed-recovery-mode-spelling.md).
  - **The Godot project cannot load its own C# assembly.** `project.godot` declares `dotnet/project/assembly_name="NLT World Engine (Godot)"`, but `world-engine-godot.csproj` never sets `AssemblyName`, so the build emits `world-engine-godot.dll` and Godot reports *"Cannot instantiate C# script … associated class could not be found"*. Present since the prototype landed; worked around for verification with `dotnet build -p:AssemblyName="NLT World Engine (Godot)"`. **The csproj needs the one-line fix** — nobody could run the project from a clean checkout without it.
    - **✅ RESOLVED in the working tree, 2026-10-04 (found during triage, not by the observer thread).** `world-engine-godot.csproj` now carries `<AssemblyName>NLT World Engine (Godot)</AssemblyName>`. The project builds and the C# observer runs, so this blocker can be closed once the change is committed. **A second, stray `NLT World Engine (Godot).csproj` and `NLT World Engine (Godot).sln` are untracked in the project root** — almost certainly editor-generated by accident. They are what makes a bare `dotnet build` fail with **MSB1011** ("folder contains more than one project or solution file"); every build since has had to name the csproj explicitly. Both are unrecoverable if deleted (untracked) and are **not** observer scope — reported, not touched.
  - **Pre-existing Phase B rendering errors**, untouched and out of scope: the wind shader fails (`INSTANCE_TRANSFORM` unknown in 4.7), and `VegetationBuilder` sets `MultiMesh.UseCustomData` *after* `InstanceCount`, which 4.7 rejects (*"Instance count must be 0 to toggle whether custom data is used"*) — every tree logs an error at startup.
- **Next action:** human click-through of the top bar and transport. Then an `experienceVolume` count on the wire if Fusion wants the timeline to show progress against the target of 50 (schema bump, Fusion's call), and B.2/B.4 agent pins in the 3D scene once GRAPH-001's G1 decisions land.

### 🔭 OBS-001 — inherited working tree (triaged 2026-10-04, Kilo)

Claiming this thread surfaced **five** interleaved workstreams in one working tree, not one. Recorded separately so nothing is silently absorbed and nothing is claimed that belongs to another owner.

| Workstream | Files | Owner | Note |
|---|---|---|---|
| **Observer density + resize** | `Observer/ObserverRoot.cs` (+252/−25) | **Kilo** | The reason the claim was needed. Builds clean, 0 warnings. **Unverified on screen** — the resize and the `Coach`/`Technical` layouts still need a visual check |
| **Agent pins + assembly-name fix** | `WorldView.cs`, `Main.cs`, `world-engine-godot.csproj` | unidentified peer | The B.2/B.4 pins named in *Next action* above, plus the csproj `AssemblyName` fix. **Working — left untouched** |
| **Color grading / compositor** | `Compositor/`, `addons/Color grading/`, `assets/characters/PIPELINE-PROBE.md` | **unowned** | Belongs to `GRAPH-001`, which is itself blocked on Joshua's G1 decisions. Overlaps `addons/Color grading/` (an installed addon with its own `plugin.cfg`) with a hand-built `Compositor/Color grading/` — **possible duplication, not resolved here** |
| **godot_ai plugin update** | 26 files under `addons/godot_ai/` | third-party updater | Mid-flight, as already flagged. `.godot_ai_update/` held backups for 3.2.1 and 4.2.3; `plugin.cfg` version-bumped. **Review before committing** — this is vendor code, not project code |
| **Stray duplicates** | `NLT World Engine (Godot).csproj` / `.sln` | accidental | Break bare `dotnet build` (MSB1011). Untracked, so unrecoverable if deleted. **Joshua's call** |

Also uncommitted and unrelated to the observer: the `MIGRATE-PLAN.md` / `RENDERER-PLAN.md` pointers to `NLT-SIM-HUMAN-ROLE-1.0.0` (Kilo), and the `project.godot` fennara autoload line that makes `addons/fennara/` a tracked-file dependency.

**Defects found in the inherited observer, still open:**
- **Status bar contradicts itself** — the title reads `REPLAY — NOT A LIVE SIMULATION` while the timeline header and footer both read `live`. Cause: `StateFeedLoader` loads `fixtures/state-feed.sample.json` while the observer's `Feed/` reader loads `fixtures/replay/stayalert-day.json`, and both sit at tick 1187.
- **Panel content clipping** — several panels cut text mid-line at the old fixed sizes. Reduced by the density change; not re-checked since.
- **World view does not match the scenario** — the fixture is the StayAlert *apartment morning routine*; the rendered world is an outdoor village. `GRAPH-001` scope, not observer scope.
- **`--selftest` cannot check layout headlessly** — it compares absolute control positions against a viewport headless reports as 64×64, so it reports ~15 false failures. Pre-existing; means layout verification needs a real window.

### 🔀 MIGRATE-001 — UE 5.8 → Godot 4.7.2 engine migration (SUPERSEDED)

- **Status:** superseded by Joshua's ENG-002 decision (2026-10-07). Historical record only; no migration/conformance work remains active under this thread.
- **Owner:** Kilo · **Joined by:** Hermes (Phase 1)
- **Started:** 2026-10-02
- **Last updated:** 2026-10-02
- **Branch:** `fix/hash-v2-double-precision` · **Escalation:** [`docs/escalations/2026-10-02-godot-migration.md`](escalations/2026-10-02-godot-migration.md) — ✅ **RESOLVED 2026-10-02** by Joshua (framework change approved under OTOI §4.4) · **Governance proposal:** [#64](https://github.com/NeuroLift-Technologies/nlt-world-engine/issues/64) (core-principle amendment, awaiting written approval per OTOI §9)
- **Historical scope:** The former plan treated Godot as a fidelity port and UE as a frozen behavioral oracle. ENG-002 supersedes both assumptions: Godot replaces UE in its entirety, and UE is not a conformance oracle.
- **Plan:** `.kilo/plans/1790898229735-ue-to-godot-migration-plan.md` (canonical), mirrored at `world-engine-godot/MIGRATION-PLAN.md`
- **Settled terms:** staged validated port · C#/.NET 8 with an engine-agnostic `net8.0` core · training-environment surfaces in scope but PPO deferred · Python sidecar owns ports 8765/8766 · 4 interior scenarios rebuilt procedurally as instanced sub-scenes · governance via in-process `asfdk-csharp` · four-tier validation gate · character embodiment in scope.
- **Delivered:**
  - Phase 1.1–1.2 merged in [#61](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/61) (`ca98e54f`…`248874ea`): `NLTFixtureEmitterSubsystem`, `BuildCanonicalStateTextV2` / `ComputeStateHashV2` (bit-exact IEEE-754 hex, signed-zero and NaN canonicalisation), console command + editor/PIE capture tests, `WITH_DEV_AUTOMATION_TESTS` on both targets. 8/8 `NLT.Simulation` + 4/4 `NLT.VisualLOD.Policy` green.
  - `asfdk-csharp` cloned to a sibling repo and retargeted `net10.0` → `net8.0` (PR [#2](https://github.com/NeuroLift-Technologies/asfdk-csharp/pull/2)); library builds clean, 14/14 xUnit tests pass on net8.0.
  - Four interior level FBX exports obtained from UE (`Workplace`, `Personal`, `Social`, `Academic`) and relocated to `world-engine-godot/assets/levels/`. `OpenWorld_Level` cannot be FBX-exported (World Partition + Landscape + runtime generation) and is rebuilt procedurally instead.
  - **Plan 1.7a complete** (`a0a41d2`): `UNLTFixtureEmitterSubsystem::ValidateNonDegeneracy` — a pure, headlessly-testable assertion over the three per-tick series, with a per-tick agent position trace so "did anything move" is answerable without re-parsing canonical text. Six `NLT.FixtureCapture.NonDegeneracy.*` cases, 6/6 passing. `PROVENANCE.md` now carries a PASS/FAIL verdict.
  - **Three pre-existing crash defects fixed**, each of which independently prevented any capture from completing: a fragment view read before `ForEachEntityChunk` binds it (`b2c487a`, from `d590bcb` 2026-09-25); `EndCapture` silently no-op'ing once the tick cap flips `bCapturing`, so 600 ticks were collected and discarded (`b7cb482`); and the PIE capture test requiring a human to press Play (`7abedc7`). Capture now runs end-to-end headlessly and writes all six files.
- **⛔ Blocker (2026-10-02):** with those fixed, the capture still produces a **degenerate** fixture — 600 tick blocks containing **1 unique**, 0 events, no agent movement. Mass never ticks: `LogNLTAgentSpawner: Warning: DespawnAllAgents: MassEntity not initialized`. This is **SIM-001**, deferred by the plan to Phase 6.6.
  - The 1.7 assertion detects this automatically and reports `Verdict: FAIL`, so the failure is now mechanical rather than a matter of inspection.
  - Plan items **1.5** and **1.7b** cannot complete. Fixing Mass requires changing UE simulation behaviour, which plan §10 forbids after 1.6 ("UE is a frozen oracle") — the same circularity the freeze exists to prevent.
  - Escalation: [`docs/escalations/2026-10-02-ue-cannot-produce-golden-fixture.md`](escalations/2026-10-02-ue-cannot-produce-golden-fixture.md) — **awaiting Joshua's decision**. Tracking issue: [#67](https://github.com/NeuroLift-Technologies/nlt-world-engine/issues/67) (`escalation`, `agent-action-required`, assigned JDUB1216). Recommendation: hold the freeze, land the crash fixes, amend decision 7 to state that Tier 2 is unavailable and what replaces it.
  - **Scope note:** Tier 2 is the gate that retires UE, and decision 7 defines validation in terms of it. That assumption does not hold, so this affects Phase 6 and Phase 10 planning, not only 1.5/1.7b.
  - **Do not commit** the existing `WorldEngine/Saved/Fixtures/seed42/` capture — it is gitignored and degenerate.
- **✅ Resolved 2026-10-02 — SIM-001 fixed, capture now live.** Two defects, both "documented behaviour was not true", both inside the narrowed 1.6 carve-out. PR [#69](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/69) (`f1c3efd`, `b28a027`).
  - (a) **Clock disconnected** — nothing subscribed to `OnSimulationTick`, so `CurrentState.SimulationTick` stayed 0 for whole runs. `StepTick` now publishes tick and time.
  - (b) **Agents frozen** — `NLTAgentSpawnerSubsystem` hardcoded `FNLTStateTreeBehaviorFragment::bEnabled = true`, and both legacy processors skip StateTree-enabled entities. With **0 `.sttree` assets**, ownership passed to a layer that owns nobody. Now defaults to `false`.
  - **My earlier diagnosis was wrong** — "Mass never ticks" came from a `DespawnAllAgents: MassEntity not initialized` line emitted on **teardown**, not spawn. Instrumenting the decision processor showed it running once per tick for all 600 ticks with valid subsystem pointers, yet never reaching `DecideTarget`. Mass was fine; the entity-level flag was the blocker.
  - **Verified:** 600 tick blocks containing **600 unique** (was 1), clock 1 → 600, `WorldTime` 0.0166 → 10.0 min, `Agents move: yes`. Suite 18/19.
- **✅ Three pre-existing crash bugs fixed** — PR [#70](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/70) (`b2c487a`, `b7cb482`, `7abedc7`), plan item 1.11. Each independently prevented any capture from completing: a fragment view read before the query bound it (asserted on every scenario start), `EndCapture` silently discarding 600 collected ticks, and the PIE test requiring a human to press Play.
- **✅ 1.12 done** — §6's fixture risk re-framed and **re-rated High → Medium**. Residual risk is the empty event stream. **Corrected 2026-10-02:** this previously read *"`UNLTEventBus` has zero writers, so … no producers to exercise."* Both halves were wrong — writers exist (`UNLTWorkplaceEnvironmentSubsystem::RefreshRooms` / `PublishTimeOfDay`) and the real cause is an **undriven producer chain**: `StepEnvironmentSimulation` has zero call sites, and it is the only caller of `UNLTSimulationClockSubsystem::AdvanceTick()`, the only broadcaster of `OnAuthoritativeTick`. Same defect class as SIM-001, so **inside** the 1.6 carve-out, not outside it.
- **⏭ Remaining on the UE machine:** 1.4 (VisualLOD vectors need emitter support). **Open decisions:** event-stream scope — gate golden vectors on the three green signals and record the gap, or scope producer wiring as new behaviour outside the carve-out; and **oracle determinism** — see below.
- **⚠️ Fixtures committed but NOT yet Tier-2 trustworthy (plan 1.5).** Four captures — `seed42_{wp_1,pers_1,soc_1,acad_1}`, one per category, seed 42, 2,000 ticks, ≈ 13.8 MB — now live at repo-root `fixtures/` with machine-generated provenance (real UE version/changelist, source commit via `-NltFixtureCommit=`, world name, verbatim `FCommandLine`, and a PIE-vs-editor capture-context field). **But the oracle is not deterministic run-to-run:** re-running the identical command diverges at tick 59 (just before `DecisionIntervalTicks = 60`) and 1941 of 2000 ticks then differ, while ticks 0–58 are byte-identical. `DecideTarget` seeds on `(AgentId, SimulationTick)` so this is not the RNG — it is an ordering race between Mass processors and `ANLTDemoGameMode::Tick`. **These vectors must not be wired into Tier 2 yet**; a port divergence measured against a nondeterministic baseline is uninterpretable. Next step: pin the capture read point in the Mass pipeline and add a capture-twice/assert-byte-equality gate — item 1.7's non-degeneracy check catches a *static* simulation but says nothing about a *nondeterministic* one, which is the gap this exposed.
  - Fixed `double`→`float` narrowing of `Agent.Position` in `BuildCanonicalStateTextV2` — `FVector` is `FVector3d` under UE5 LWC, so v2 was truncating a 53-bit mantissa to 24 bits inside the bit-exact encoding.
  - Untracked 119 committed Godot build-cache files and relocated the level FBX assets.
- **Blockers / human-owned:**
  - **1.5 — fixtures must be committed** under `fixtures/` with `PROVENANCE.md`. **Ownership corrected 2026-10-02** from `[HUMAN]` to `[AGENT — requires a UE-capable machine]`: the constraint is UE access, not a human in the loop. **Phase 1 is not complete, and `MIGRATE-001` must not close, until these land in git** — infrastructure shipping without vectors is a false green.
  - **1.7b — non-degeneracy must be *proven*,** not just asserted. Editor-context capture yields static state, so a fixture can be N byte-identical ticks encoding no behaviour. #69 now yields 600/600 unique blocks with agents moving; the remaining `Verdict: FAIL` is the **event-stream** signal alone, and 1.12 explains why.
  - **1.12 [NEW] — coverage must be scenario-aware.** `UNLTWorkplaceEnvironmentSubsystem` is the only environment-event producer in the module (four raise sites at `NLTWorkplaceEnvironmentSubsystem.cpp:254,257,279,286`). **Personal, Social and Academic have none.** Since 1.3 requires ≥3 scenarios, the event-stream comparison in Tier 2-scenario is meaningful for 1 of 3 — the rest compare two empty streams. Either generalise the environment model or record that event assertions apply only to the Workplace fixture. Most likely the capture ran a non-Workplace level, so re-running on Workplace may clear it with no behavioural change.
  - `asfdk-csharp` is pre-1.0 (v0.3.0, single merged PR) — pin the commit.
  - ~~`addons/godot_ai/` third-party MCP bridge added outside any thread: OTOI §4.4 external-integration approval unrecorded~~ — **closed 2026-10-03.** §4.4 approval recorded for all five third-party addons (`godot_ai`, `sky_3d`, `fennara`, `godotopenxrvendors`, `beehave`) in [`docs/escalations/2026-10-03-addons-external-integration-approval.md`](../escalations/2026-10-03-addons-external-integration-approval.md). NobodyWho approved for **Fusion-side use only** and removed from this project (see that record for the boundary/§4.4/Phase-9 rationale). **Still open on `godot_ai`:** bootstraps Python via `uv`; C#/mono compatibility unverified.
  - ~~**🔴 Fresh-clone blocker (found 2026-10-03, Kilo — same class as the `sky_3d` one below, different addon).** The **uncommitted** `project.godot` adds autoload `_fennara_game_capture` → `res://addons/fennara/runtime/game_capture_helper.gd`, but `addons/fennara/` is **untracked**. `HEAD:world-engine-godot/project.godot` has only the `_mcp_game_helper` autoload (→ `godot_ai`, which *is* tracked), so the committed tree is self-consistent today — but committing `project.godot` without also committing `addons/fennara/` hands every fresh clone an autoload pointing at a missing script. **These two must land in the same commit, or the fennara autoload line must be dropped from `project.godot`.**~~ — **closed 2026-10-07:** `ae5424b` committed `project.godot` and `addons/fennara/` together. **Update 2026-10-17:** fennara is now registered as an MCP server in Claude Code and Claude Desktop (per Joshua); it is local to his machine, so cloud agent sessions still see no fennara tools.
- **Corrected twice on 2026-10-02 — do not repeat:** (1) *"Mass is not initialized / Mass never ticks"* was false, taken from a **teardown** log line; Mass ticked throughout. (2) *"the event bus has zero writers"* was false, taken from grepping `Publish(`, an API that does not exist — the surface is `RaiseEvent`/`RaiseSimpleEvent`/`RaiseEnvironmentEvent`. (3) *"wiring event producers is new behaviour"* followed from (2), so it is void too. **Verify a diagnosis from instrumentation, not from a log line's context.**
- **Named gaps the migration does not close** (unmet in UE too — own threads needed, not inherited): agent↔agent interaction, NPC population (no NPC system exists), realistic graphics.
  - **Realistic graphics → now owned by [`GRAPH-001`](#-graph-001--godot-art--asset-pipeline-realistic-graphics), opened 2026-10-02** (`RENDERER-PLAN.md` §0.3 requires each gap to get its own thread).
  - **NPC population and agent↔agent interaction still have no thread and no owner.** Note these are also in conflict internally: `RENDERER-PLAN.md` §9 lists agent↔agent interaction as **out of scope**, while §0.3 says it **needs its own thread**. Unresolved — Joshua's call.
- **Phase C (interiors) started 2026-10-03.** `RENDERER-PLAN.md` §5. **C.5 resolved** — `workplace_level.tscn` is canonical, `workplace.tscn` is orphaned and left in place (untracked, unrecoverable if deleted). **C.3 model delivered** — `world-engine-godot/TaskAnchor.cs` ports `NLTSmartObjectWorldSubsystem.h/.cpp`: affordance axes, reservation/occupancy, and `NeedMatching.Matches/Score/FindBest` with UE thresholds held byte-identical. `dotnet build` clean, 0 warnings.
  - **Corrected a live contradiction:** §5 previously specified **five** needs and read `Privacy` as an agent need gating at a stricter threshold than `Rest`. That is wrong and contradicts contract §4.3, which establishes **four** needs and `privacy` as a *location affordance axis*. The UE `Privacy` branches (`.cpp:129-130`, `:152-153`) cannot fire and were deliberately not ported.
  - **C.1, C.2, C.4 all blocked on B.2/B.3** — no residents are rendered (B.2, awaiting GRAPH-001 G1 decisions) and no interior scene is ever loaded (B.3 owns the building→interior wiring). C.3a (anchor *placement*) needs the imported FBX geometry read, which needs a Godot-capable session.
  - **🔴 Fresh-clone blocker (raised 2026-10-03, escalated by B.1).** `addons/sky_3d/` is still **untracked** in git, and `WorldView.cs` loads it via `GD.Load<GDScript>` in `_Ready()`. `run/main_scene` (`Main.tscn`) therefore depends on files not in the repository — a fresh clone will not start, and `dotnet build` cannot catch it because the path is a runtime string. The plugin is now ratified and recorded in plan §0.1 with provenance, so the *reference* is legitimate; the *commit* is what is missing.
    - **Correction 2026-10-03 (Kilo):** this blocker appears **already resolved** — `addons/sky_3d/` is now fully tracked (43 files tracked, 43 on disk, no untracked leftovers under the path). @B.1 should confirm and close it rather than re-chase it.
- **⚠️ Concurrent-agent collision observed 2026-10-03.** A second agent session (codex + a live `Godot_v4.7.2-stable_mono_win64` editor) rewrote `world-engine-godot/WorldView.cs` at 01:23 and deleted `SkyBuilder.cs` / `Daylight.cs` to adopt Sky3D, landing concurrently with this Phase C work. The edits are disjoint — Phase C §5 versus B.1/§0.1 — and no peer work was overwritten, but the repo now has two agents mutating `RENDERER-PLAN.md` and the Godot tree at once. Per the multi-agent coordination protocol this warrants a check-in before further parallel work on either thread.
- **Next action:** Phase 2 (`NltWorldEngine.Core` + Tier 1 xUnit gate), unblocked now that #69 and #70 exist — Tier 1 and 2-core were never blocked. Retirement of UE remains gated on 2-scenario, 2b, and a minimum viable RL policy before Phase 10 (see plan 10.1).

### 🎨 GRAPH-001 — Godot art & asset pipeline (realistic graphics)
- **Status:** open — decisions pending with Joshua (Phase G1 blocking)
- **Owner:** Joshua (decisions) · **Plan:** [`world-engine-godot/ART-PIPELINE.md`](../world-engine-godot/ART-PIPELINE.md)
- **Started:** 2026-10-02 · **Last updated:** 2026-10-02
- **Forked from:** `MIGRATE-001`, per `RENDERER-PLAN.md` §0.3 — *"realistic graphics were unmet in UE and remain unimplemented. Each needs its own thread."*
- **Scope:** Close the realistic-graphics gap in the Godot renderer. **Only** the graphics gap — NPC population and agent↔agent interaction are separate threads and out of scope here.
- **Trigger:** the Godot open world renders entirely from runtime primitives (`CylinderMesh`/`ConeMesh`/`BoxMesh`/`SphereMesh`) with **zero imported meshes**; against the three.js spectator (`nlt-world-engine.html`) it reads as a blockout.
- **Key finding — the blockout is partly a real constraint.** `OpenWorld_Level` **cannot** be FBX-exported from UE (World Partition + Landscape + runtime generation), which is why the open world is procedural at all (`RENDERER-PLAN.md` §4). The four FBX files in `assets/levels/` are **interiors only**. That constraint does *not* extend to characters or hero props.
- **The forcing function is `RENDERER-PLAN.md` B.2**, not aesthetics: *"Open world renders residents — the agent population walking between buildings. This is where articulation and walk cycles earn their keep."* Line 44 specifies *"articulated bodies · walk cycles"*, which **cannot** be assembled from primitives. The asset decision lands at B.2 whether or not it is filed under graphics.
- **Recommendation on scope:** import art where art is genuinely required (characters, hero props near camera), **not** as a blanket replacement. Terrain, water, buildings-at-distance and the vegetation wind shader are legitimate as-is; sweeping them would add licensing surface and repo weight for little visual return.
- **Adopted from the stale predecessor** `docs/design/realistic-viewer-architecture.md` (Three.js-era, orphaned — do not implement against): **CC0-only sourcing** (Mixamo/Poly Haven) and **perf targets** 60 FPS · 10–20 animated characters · <16 ms frame time.
- **⚠️ Licence risk flagged, not resolved (G1.1):** Mixamo's terms have historically **not permitted redistribution of the raw assets**. If residents ship in this repo or a build, that needs a real answer. Do not assume CC0.
- **⚠️ Constraint conflict (G2.4):** `RENDERER-PLAN.md` D.4 mandates *reduced motion*; animated walk cycles and the unconditional wind shader in `VegetationBuilder.cs` run against it. Must resolve when animation lands, not after.
- **Historical constraints from the superseded renderer plan:** renderer-only scope and no-determinism assumptions no longer apply after ENG-002. Third-party plugins remain reserved to Joshua; **no asset is committed without provenance**; accessibility remains a system requirement.
- **Next action:** Joshua to answer G1.1–G1.5 (asset source & redistribution, character count + LOD budget, animation source, hero-prop policy, budget authorisation). G2 pipeline work is blocked until G1.1 and G1.5 land.

### 📐 RENDERER-001 — Godot renderer plan (Phase A state feed)
- **Status:** Phase A complete · Phase B–D open
- **Owner:** Cline (handoff from Kiro, 2026-10-08) · **Plan:** [`world-engine-godot/RENDERER-PLAN.md`](../world-engine-godot/RENDERER-PLAN.md)
- **Started:** 2026-10-03 · **Last updated:** 2026-10-08
- **Scope:** Implement the Godot renderer per `RENDERER-PLAN.md`: state feed, open world residents, interior scenes, observer panels.
- **Delivered (2026-10-03):**
  - **Phase A complete (A.1–A.5).** Contract doc `docs/contracts/state-feed-v1.md` published (A.1); envelope with velocity (A.2); burnout episodes (A.3); self-recognition (A.4); all present in `fixtures/state-feed.sample.json`.
  - **A.5 — `world-engine-godot/StateFeedLoader.cs`** (491 lines): loads `fixtures/state-feed.sample.json` at startup, validates schema version, all required keys, four canonical need keys + range, warns on unknown need keys, warns on empty agent list. Wired into `WorldView._Ready()`. Build: 0 errors, 0 warnings.
  - **B.1 sky swap complete (2026-10-03).** Sky3D (`addons/sky_3d/`) adopted; `WorldView.cs` instantiates Sky3D, disables its internal clock, and drives `current_time` from sim time. `SkyBuilder.cs` and `Daylight.cs` are **deleted**. Reduced-motion (D.4) pauses the sim-time write via `SkyPaused`.
  - **C.1 collision enabled (2026-10-03).** All four level FBX `.import` files set `meshes/create_shapes=3` (trimesh). Reimport pending next editor open / `--headless --import`.
  - **Fixed pre-existing `TerrainBuilderPhysics.cs`** — file was a copy of `TerrainBuilder.cs` with the same class name, causing a duplicate-class compile error. Replaced with a placeholder stub reserving the class for Phase C.1 (interior collision).
- **Blockers / human-owned:**
  - **Phase B.2 (residents / walk cycles)** is blocked on GRAPH-001 G1 decisions (character asset source, LOD budget, animation source).
  - **§8 item 0.1 `addons/godot_ai/`** — still unratified (provenance unverified, C#/mono compatibility unconfirmed, `mcp-config.yaml` entry missing). Joshua's decision.
  - ~~Sky3D ratification~~ — resolved 2026-10-03. B.1 implementation (swap `SkyBuilder.cs` → Sky3D) is now unblocked.
  - **Phase C** (interior collision, entry points, task anchors) has no scheduled date.
  - **Phase D** (observer panels) depends on state feed being live from Fusion, which depends on the Python bridge (not yet built; transport for A.5 is undecided per contract §10).
- **Next action:** B.1 swap (`SkyBuilder.cs` → Sky3D) is **complete**; C.5 resolved — the `<Name>_level.tscn` convention wins; `workplace.tscn` is superseded (early-iteration wrapper with a stray offset). B.3 (building→interior mapping) and B.4 (Label3D name labels) remain unblocked.

### 🧪 DET-001 — Deterministic state verification and headless build foundation
- **Status:** open
- **Owner:** Cline
- **Started:** 2026-09-25
- **Last updated:** 2026-09-25
- **Branch:** `cline/d8d52`
- **Summary:** Added a versioned UE-side BLAKE3 canonical state hash, deterministic RNG reset metadata with legacy seed-save compatibility, project AutomationTests, a dedicated server target/config, dedicated-server guards, and a versioned JSON replay record/verifier with action/event integrity and observed final-state comparison.
- **Blockers:** None for the primary UE Editor build/train/watch path. The installed UE 5.8 distribution cannot create `WorldEngineServer`, but Dedicated Server is optional later infrastructure and is not a release blocker. The Editor target builds successfully with `ASFDK_ROOT=D:\nlt-repos\asfdk-cplus`; UE automation tests pass 7/7 using `UnrealEditor-Cmd.exe -DisablePython`.
- **Next action:** Validate the rendered UE Editor/standalone-game training path and live visual LOD transitions. Revisit source-built Dedicated Server compilation and CI only if headless infrastructure is later approved as a separate effort. Add approved action semantics before implementing replay action execution.

### 👁️ LOD-001 — Shared visual LOD policy for Mass and actor residents
- **Status:** open
- **Owner:** Cline
- **Started:** 2026-09-25
- **Last updated:** 2026-09-25
- **Branch:** `cline/d8d52`
- **Summary:** Added a shared configurable visual LOD policy with distance thresholds, hysteresis, viewer fallback, Mesh/HISM/fallback representation selection, and explicit visual-only semantics. Integrated it into Mass HISM visualization and actor-resident mesh visibility without changing simulation fragments, movement, cognition, or update rates.
- **Blockers:** None for the primary UE Editor build/train/watch path. The installed UE 5.8 distribution cannot create the Dedicated Server target, but that target is optional later infrastructure. LOD policy automation passes 4/4 and the Editor build succeeds.
- **Next action:** Validate visual transitions in a representative rendered UE scene with Mass/actor residents, then add a CI job when a UE-capable runner is selected. Simulation-frequency LOD remains out of scope.


### 🔧 BUILD-WIN64-001 — Win64 build repair: ASFDK wiring + hot-reload state
- **Status:** resolved
- **Owner:** Cline
- **Started:** 2026-09-21
- **Last updated:** 2026-09-24
- **Branch:** `fix/win64-asfdk-stubs` · **PR:** [#50](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/50)
- **Blockers:** None for the Win64 editor build. Two decisions remain with Joshua: (1) build a
  real Win64 ASFDK library — the Win64 stubs remain the verified interim; (2) the
  C:-build-tree ↔ canonical-repo sync story. Linux builds are additionally blocked until
  `libasfdk.a` exists in the ASFDK checkout; the module now fails with repair guidance at
  rule-evaluation time instead of a bare linker error.
- **Summary:** User's Visual Studio `WorldEngineEditor Win64 Development` build failed with C1083
  (`asfdk/ASFDK.h`), LNK1104 (`UnrealEditor-WorldEngine-0002.lib.rsp` missing), and MSB3073.
  Root causes: (1) the `ThirdParty/ASFDK` junction in the C: UE build tree pointed at the
  pre-move `C:\...\nlt-repos\asfdk-cplus` location (nlt-repos now on D:); (2) legacy
  hot-reload-from-IDE re-applying a stale, inconsistent `HotReloadState.json` while
  `UnrealEditor.exe` was running. The canonical repo additionally had a dangling gitlink
  (no `.gitmodules` mapping) for the ASFDK submodule.
- **Delivered (verified):** hardened `NLTGovernanceSubsystem.Build.cs` (ASFDK_ROOT override +
  loud BuildException, duplicate-nlohmann guard, and a fatal guard when `libasfdk.a` is
  absent on Linux); `ASFDK_Win64Stubs.cpp` rewritten and proven
  compile/link-clean against the real headers (standalone MSVC probe + full UBT builds);
  `.gitmodules` added and submodule restored at pinned `55b21fe`; forensic write-up at
  `WorldEngine/docs/building/LNK1104-rsp-diagnosis.md`. Both `WorldEngine` and
  `WorldEngineEditor` targets build `Result: Succeeded` in the C: build tree.
- **Handoff:** `docs/agent-log/handoffs/2026-09-21-cline-win64-asfdk-build-repair.json`
- **Next action:** PR [#50](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/50)
  is open with all 8 CodeRabbit review comments addressed (2026-09-24). Awaiting Joshua's
  decisions on a real Win64 ASFDK library build and on the C:-build-tree ↔ canonical-repo
  sync story.

### 🏙️ ESC-001 — UE Open-World Expansion (Fab Modern City assets as outdoor layer)
- **Agent:** OpenCode (Poolside) · **Opened:** 2026-09-20 · **Branch:** `main` (uncommitted)
- **Scope:** Port `openworld-engine` outdoor rendering into UE WorldEngine — buildings as level
  portals to indoor `.umap` scenarios, upgraded building/ground geometry with AI-usable Fab
  `Modern_City_Environment` assets, procedural determinism (seed → world) preserved.
- **Delivered (verified in standalone `-game`, seed 42):**
  - Geometry-only GLB splits imported per mesh (12 portals, **9 city-grid pieces**; 6 original + 3 new: Building_Base plaza, Building_13 podium, Grass cover); merged block aligns all pieces via the shared Fab scene origin.
  - `NLTBuildingPortalActor`: `SceneRoot` added; `UpdateBuildingMesh()` assigns Fab meshes per type with bounds-aware scaling, base-on-spawn anchoring, roof labels, footprint-sized interaction volumes. Cube fallback retained (Hut / load failure).
  - `NLTOpenWorldSubsystem`: `SpawnCityScenery()` + `bPlaceCityScenery` + `ClearOpenWorld` cleanup. Log: `City scenery: placed 9 Fab Modern City grid pieces (scale 0.770, base Z 0, world 20000x20000)`, `Open world generation complete: 12 buildings, 12 residents`; portal overlap → level streaming verified live.
  - **Baked Blender block positions (2026-09-20):** `FNLTOpenWorldConfig.BuildingLayout` (BP-editable list of type + exact location + yaw) now baked from the Fab block in Blender — Building 11 tower center (52.2, -21.7) m → Office at (4020, -1671) cm; Building 12 tower center (118.1, -65.7) m → Apartment at (9094, -5059) cm; shared scenery scale 0.770 (WorldHalf 10000 / max piece half-extent 12985). Default 12 authored buildings spread across enlarged **200×200 m** world, pre-verified footprint-clear (min center distance 2600 cm, min clearance 400 cm — logged at spawn). World size default 5000 → 20000. School + Office always spawn now. Shared `GetTargetHalfExtent()`/`GetFootprintRadius()` tables on the portal actor.
  - **Vegetation HISM upgraded:** `SM_Mobile_Trees` mesh wired (Fab "Mobile Trees" pack); per-instance scale normalized to native mesh bounds (native ~24 m → target 3-6 m) with base-on-terrain anchoring (corrects pivot offset).
  - **Hut mesh wired:** merged WoodenHouse kitbash (Blender temp scene, 391 parts → 436 K verts, 17.2×13.7×6.4 m cottage) imported as `/Game/City/Huts/DoorWoodenHouse/WoodenHouse/StaticMeshes/WoodenHouse.WoodenHouse` — fallback to cube if load fails.
- **Escalation record:** `docs/escalations/2026-09-20-openworld-expansion.md` (Progress Update section).
- **Blocker for PIE:** MCP `control_editor.play` catalog bug (rejects `control` param; console `PIE.Start` blocked as dangerous) — verification done via standalone `-game` instead.
- **Known issues (asset paths, not code):** Path_And_Imperfections and Traffic_Lights GLB imports created assets with different naming conventions (multi-mesh GLBs); WoodenHouse merged GLB re-import asset path needs verification — both are asset registry issues, not code.
- **Next action:** commit; optional follow-ups: vegetation-HISM `ensure` cleanup, NavMesh for imported meshes, texture pass on NLT_Gray geometry.
### 🚪 ENV-002 — Relocate Personal_Level Teleporter Doors (UE WorldEngine)
- **Agent:** OpenCode · **Opened:** 2026-09-20 · **Branch:** `feat/personal-level-door-relocation`
- **Scope:** The three runtime-spawned `NLTDoorActor` teleporters in `Personal_Level` were hidden in PIE — the Academic door sat behind the kitchen cabinet/stove line and the Social door behind the `Corridor_Wall_E4` corner, both hard to see/reach.
- **Delivered:** `SpawnLevelDoors()` in `NLTDemoGameMode.cpp` now spawns the doors as a visible row along the open south wall (Y=-885), clear of `Front_Door` and player starts, with yaw 180 so labels face north into the room. `Social_Level`/`Academic_Level` spawn behavior unchanged.
- **Blocker note:** Doors are code-spawned (not map actors), so the change requires a module rebuild + PIE restart to take effect; `set_transform` is edit-mode-only and cannot move PIE actors.
- **Next action:** Review PR; rebuild module, run PIE, verify door visibility/labels.

### 📄 DOC-MCP-001 — Unreal MCP Integration Documentation
- **Agent:** OpenCode · **Opened:** 2026-09-19 · **Branch:** `main`
- **Scope:** Register the unreal-mcp server config and document the WorldEngine integration. Global OpenCode MCP registration (`http://127.0.0.1:8001/mcp`, ✓ connected).
- **Delivered:** `unreal-mcp` entry + governance note added to `mcp-config.yaml`; `docs/world-engine/UNREAL-MCP-INTEGRATION.md` created.
- **Blockers:** `McpAutomationBridge` plugin not yet installed in `WorldEngine/Plugins/` — its native MCP port must be set to **8001** to match.
- **Next action:** Install plugin into WorldEngine (copy or external plugin dir), set native MCP port to 8001, enable Native MCP, restart editor.

### 🎯 CHAR-001 — Character Animation & Emotion System (UE WorldEngine)
- **Agent:** Claude Code (Poolside) · **Opened:** 2026-09-13 · **Branch:** `feat/character-animation-emotion-system`
- **Scope:** Build emotion-driven character animation system in the UE WorldEngine project. Swap static-mesh SimBody characters for rigged SkeletalMesh characters with an emotion state machine wired to cognitive values (focus/stress/cogLoad/burnout), an animation state machine with smooth transitions, Avatar↔Aide social choreography, and a procedural animation fallback via UAnimInstance.
- **Delivered:** NLTEmotionStateComponent (emotion state machine), UNLTAvatarAnimInstance (procedural pose data provider + facial morph targets), NLTCharacterAnimationComponent (animation state machine with montage + static-mesh fallback), NLTPairChoreographyComponent (Avatar↔Aide social choreography), AvatarCharacter integration (emotion→animation→visuals pipeline).
- **Blockers:** No UE editor runtime available; limited to UBT headless compilation. No SkeletalMesh or AnimAssest assets exist yet — procedural UAnimInstance fallback required.
- **Next action:** Update PLAN.md with emotion-animation phase documentation. Create NLTAideCharacter class. Wire OnSimulationTick delegate for sim-synchronized cognitive decay.

### 📄 ESC-001 — Procedural Open-World Layer (Path B)
- **Agent:** OpenCode · **Opened:** 2026-09-20 · **Status:** In development (Phase 1 complete)
- **Scope:** Outdoor open-world layer where buildings are level portals to existing indoor `.umap` scenario levels (Workplace, Personal, Social, Academic). Procedural approach — ported from Three.js `openworld-engine/src/world/` into UE5 C++.
- **Escalation:** `docs/escalations/2026-09-20-openworld-expansion.md` — ✅ RESOLVED 2026-09-20 by Joshua (Fab assets inaccessible → procedural approach approved).
- **Delivered:** `NLTNoiseLibrary` (mulberry32 + Noise2D + Fbm2D ported from `noise.js`); `NLTAtmosphereSubsystem` enhanced with procedural cloud/star noise + HDRI cubemap support; `PostProcessVolumeActor` LUT support with procedural fallback; Water plugin enabled in `.uproject` + `Build.cs`; Content directory structure created; docs at `WorldEngine/docs/procedural-openworld.md`. Phase 2 (terrain) started by Pool: `ETerrainBiome` enum + `GenerateTerrainHeight`/`ClassifyTerrainBiome` added to `NLTNoiseLibrary`; faithful port of `terrain.js` createHeightField/baseHeight + biome bands; UBT incremental build (UE5.8) — 0 errors in all touched TUs.
- **Next action:** Port `terrain.js` heightfield to PCG/Landscape — IN PROGRESS (C++ heightfield port done & compiles clean; Landscape mesh instantiation deferred — requires UE editor runtime not available on this box). Building-to-level portal streaming bridge — deferred Phase 3 (cross-lane: requires Codex + Poolside coordination per escalation; NOT started by this agent). See `ENV-TEX-001` below for details.

---


### 🛠 AGENT-HARNESS-001 — Agent action-interface harness committed in world-engine-godot

- **Agent:** Solar Mini4 · **Opened:** 2026-10-07
- **Status:** ✅ COMPLETE (merged in PR-equivalent local commit `9735006`)
- **Plan:** option B of the 2026-10-07 plan-mode discussion — commit the
  out-of-engine action-interface harness inside `world-engine-godot/` instead
  of leaving it thrown away or moving it to neurolift-ai-fusion.
- **Delivered:**
  - `world-engine-godot/AgentHarness/AgentHarness.csproj` — standalone
    `Microsoft.NET.Sdk` console project referencing the Godot build's
    `GodotSharp.dll` + `NLT World Engine (Godot).dll` (relative HintPaths).
  - `world-engine-godot/AgentHarness/Program.cs` — drives
    `ActionAssertions.RunAll()`; exits 0 on all-pass.
  - `world-engine-godot/world-engine-godot.csproj` — one-line glob exclusion
    `<Compile Remove="AgentHarness/**/*.cs" />` so the harness sources are
    never compiled into the Godot assembly.
  - `world-engine-godot/AGENT-SYSTEM.md` — §5.2 rewritten: in-repo `dotnet
    build` + `dotnet run --project AgentHarness/AgentHarness.csproj`
    instructions replacing the "keep outside the project" note.
- **Verification:**
  - `dotnet build world-engine-godot.csproj` → 0 errors (2 pre-existing
    CS8601 warnings in WorldView.cs, untouched).
  - `dotnet build AgentHarness/AgentHarness.csproj` → 0 errors, 0 warnings.
  - `dotnet run --project AgentHarness/AgentHarness.csproj` →
    **12 passed, 0 failed — RESULT: all assertions passed**.
- **Note:** the Godot assembly's existing `.gitignore` (`*.dll`, `.godot/`)
  plus root `.gitignore` (`world-engine-godot/**/obj/`) cover the harness
  build output, so only the four source files were committed under
  `world-engine-godot/`. The harness still depends on the Godot build's DLLs
  being produced first (relative HintPaths), same as before.
### 🌋 ENV-TEX-001 — Procedural Terrain Heightfield Port (ESC-001 Phase 2)
- **Agent:** Pool (Poolside) · **Opened:** 2026-09-20 · **Branch:** `fix/win64-asfdk-stubs`
- **Scope:** Port `openworld-engine/src/world/terrain.js` heightfield (`createHeightField`/`baseHeight`) + biome classification (`buildTerrain` bands) into WorldEngine C++, additive on `NLTNoiseLibrary`, deterministic, NO Landscape mesh (headless).
- **Delivered:** `ETerrainBiome` enum; `UNLTNoiseLibrary::GenerateTerrainHeight` (continental island falloff + layered hill/mountain fBm — faithful port of `baseHeight` using `NLTNoiseLibrary::Fbm2D`); `UNLTNoiseLibrary::ClassifyTerrainBiome` (sand/grass/rock/snow bands adapted from `buildTerrain`). Files: `Source/WorldEngine/Public/Core/NLTNoiseLibrary.h`, `Source/WorldEngine/Private/Core/NLTNoiseLibrary.cpp`. **UBT incremental build (UE5.8, `WorldEngine Win64 Development`) — 0 errors / 0 warnings** in all touched TUs (`NLTNoiseLibrary.cpp`; `NLTAtmosphereSubsystem.cpp` recompiled against the changed header). Build overall fails ONLY on pre-existing Phase-3 `NLTBuildingPortalActor.cpp` (`StreamingHandle`) / `NLTOpenWorldSubsystem.cpp` (`GetBuildingTypeFromFName`) — not touched by this agent.
- **Blockers:** No UE editor runtime (headless UBT only) — cannot create Landscape heightmap `.umap`/PCG assets or visually verify terrain. Phase 3 portal-streaming bridge is cross-lane and explicitly out of scope for this agent.
- **Next action:** (Next session, with UE editor access) Wire `GenerateTerrainHeight` into `NLTWorldGeneratorSubsystem` → UE5 Landscape (or PCG heightfield node) → blend materials by `ClassifyTerrainBiome`. Refactor note: `NLTNoiseLibrary`'s static `Perm[512]` + `bPermInitialized`/`CurrentPermSeed` is a latent thread-safety risk if terrain and atmosphere call concurrently (see handoff).

---

### 🔍 SIM-001 — Simulation activation and runtime lifecycle trace
- **Status:** resolved
- **Owner:** Kilo
- **Started:** 2026-09-25
- **Last updated:** 2026-09-25
- **Summary:** Traced default-map startup, open-world generation, indoor scenario activation, Mass Entity spawning, simulation clocks, web/HTTP control, LLM command paths, and PPO training activation. Confirmed the default `OpenWorld_Level` path generates scenery and resident actors but does not start the Mass simulation; indoor levels spawn Mass agents and start the simulation. Identified documentation/code mismatches, including the disconnected authoritative clock, unregistered Mass processors, HTTP-only web server, and separate internal/external LLM control paths.
- **Blockers:** None for the investigation. Runtime verification remains unavailable because no UE editor runtime is present in this session.
- **Next action:** None; findings are ready for integration planning or documentation correction.

### 🌲 ST-001 — StateTree Behavior Layer on Mass Entities (augment)
- **Status:** active (editor build succeeds; deterministic reference tests pass; native runtime StateTree verification pending)
- **Owner:** Claude Code (Poolside)
- **Started:** 2026-09-25
- **Last updated:** 2026-09-25
- **Branch:** `pr/statetree-behavior-layer-clean` · **PR:** [#57](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/57)
- **Summary:** Augment the custom Mass needs/decision/movement processors (`UNLTScenarioNeedsProcessor`, `UNLTScenarioDecisionProcessor`, `UNLTScenarioMovementProcessor`) with a deterministic behavior processor and StateTree task/condition reference definitions. Native Mass StateTree execution and authored `.sttree` assets remain follow-up work.
- **Blockers:** Runtime StateTree execution, `.sttree` authoring, and UE automation coverage remain pending; editor compilation now succeeds.
- **Delivered:**
  - **C++:** `NLTStateTreeFragments.h` (StateTree behavior fragment + state enum); `NLTDemoStateTreeBehavior.h/.cpp` (data asset with default state configs); `NLTStateTreeBehaviorProcessor.h/.cpp` (Mass processor with full state machine: Idle → EvaluateNeeds → SelectTarget → MoveToTarget → Arrived → Idle, FallbackWander branch); `NLTStateTreeTasks.h/.cpp` (custom StateTree task references); `NLTStateTreeSchema.h/.cpp` (schema with typed external-data bindings); `NLTStateTreeBehaviorTest.h` (inline C++ test harness); `NLTDemoScenarioUtils.h` (shared helpers extracted: candidate sort, need ranking, intent mapping, location scoring); `WorldEngine.cpp` updated with module startup; `NLTAgentSpawnerSubsystem.cpp` updated to spawn StateTree fragments; legacy processors marked deprecated + early-out when the behavior layer is active.
  - **Build fixes (UE 5.8 compatibility):**
    - `Build.cs`: `"StateTree"` → `"StateTreeModule"` (module name in `.uplugin`)
    - StateTree tasks/conditions: UCLASS → USTRUCT pattern (`FMassStateTreeTaskBase`/`FMassStateTreeConditionBase`), handle-based external data access
    - Include path fixes: `"NLTStateTreeFragments.h"` → `"Agents/NLTStateTreeFragments.h"` across 4 files
    - Added missing includes (`Agents/NLTAgentFragments.h`)
    - Removed duplicate local utility functions from `NLTDemoScenarioProcessors.cpp` (now uses shared `NLTDemoScenarioUtils.h`)
    - Fixed narrowing conversion C2397 (brace-init → field-by-field assignment) in `NLTStateTreeTasks.cpp`, `NLTStateTreeBehaviorProcessor.cpp`, `NLTDemoScenarioProcessors.cpp`
    - Fixed C3493 lambda capture: added `this` to capture list in `NLTStateTreeBehaviorProcessor.cpp::Execute`
    - Fixed UE 5.8 `TEnumAsByte` static_assert: replaced `UEnum::GetValueAsString<EnumType>()` with `StaticEnum<EnumType>()->GetNameStringByValue((int64)...)` in `NLTEventBus.cpp` and `NLTStateTreeBehaviorProcessor.cpp`
    - Fixed Mass `static_assert` fragment traits: added `TMassFragmentTraits<FNLTStateTreeBehaviorConfigFragment>` specialization (TSoftObjectPtr not trivially copyable)
  - **Fusion/Wire:** `WorldEngine/Scripts/fusion_protocol.py` (versioned envelope codec, action allow-list, atomic multi-tick replay executor, and result comparison); `test_fusion_protocol.py` + `test_fusion_protocol_regression.py` (9 passing reference tests); UE WebSocket listener hardened with safe field access, required action type/target, malformed-JSON rejection, and game-thread dispatch.
  - **Build result:** `WorldEngineEditor Win64 Development` — `Result: Succeeded`, 0 errors (clean PR worktree, verified 2026-09-25).
  - **Build.cs:** Uses the UE 5.8 `StateTreeModule` dependency.
  - **Python reference:** `src/statetree/__init__.py` (enums, constants, `deterministic_hash`, `FRandomStream`); `src/statetree/behavior.py` (full state machine processor); `src/statetree/conditions.py` (3 conditions); `src/statetree/tasks.py` (4 tasks).
  - **Python tests:** 21 tests — 12 deterministic transition tests + 9 fallback/determinism tests. All passing: `cd _archive\world-engine && python -m unittest tests.test_statetree_transitions tests.test_statetree_fallback -v` → 21 passed.
  - **Docs:** `WorldEngine/docs/architecture/statetree-behavior-layer.md` (full design doc); `unreal-simulation-architecture.md` §9 open item #2 → "In progress".
  - **Build script:** `build_statetree.bat` created at repo root for UBT invocation.
- **Build limitations (verified 2026-09-25):** a clean PR worktree build succeeds; native Mass StateTree execution, authored `.sttree` assets, and registered UE Automation coverage remain pending.
- **Next action:** (1) Integrate `UMassStateTreeProcessor` and author a `.sttree` asset; (2) register and run the behavior checks as UE Automation tests; (3) run live Python↔UE wire conformance; (4) collect rendered PIE evidence for Mass/actor LOD transitions.

### 🎯 Next: Integration & Testing

- **Agent:** — · **Opened:** — · **Branch:** `main`
- **Scope:** Wire together the now-merged subsystems into a coherent end-to-end flow: LLM-driven avatar → web server → Mass Entity sim → training loop.
- **Delivered:** —
- **Next baton:** 
  1. Restart editor/headless sim to pick up HTTP status-code fix (`509dc0c`)
  2. Run `python3 llm_avatar_agent.py --task "..."` against local or hosted OpenAI-compatible endpoint
  3. Verify ASFDK governance plugin loads correctly in editor
  4. Test Learning Agents PPO training pipeline with Avatar/Aide pairs

---

## Resolved Threads (2026-09)

### Thread: TRAIN-001
**Status:** resolved
**Owner:** Codex (2026-09-13 session)
**Started:** 2026-09-13
**Last updated:** 2026-09-13
**Summary:** PPO training in `run_nlt_training.sh` failing with `RuntimeError: The size of tensor a (3) must match the size of tensor b (4)` at `ppo.py:99` in `Denormalize.forward`. Root cause: `ppo.py` line 71 had hardcoded `self.act_enc_num = 3`, overriding the schema-derived value of 10 (Interaction=4 + MoveDirection=6). Removed the override so `act_enc_num` correctly reads 10 from `action_schema['EncodedSize']`. Verified end-to-end: first training iteration completed successfully with PPO train profile (5501ms), Iter: 0 stats logged, networks sent/received.
**Blockers:** None — Python crash resolved. Secondary C++ restart issue identified (see TRAIN-002).
**Next action:** Recompile C++ and re-run training to verify the secondary fix (TRAIN-002).

### Thread: TRAIN-002
**Status:** open
**Owner:** Codex (pending verification)
**Started:** 2026-09-13
**Last updated:** 2026-09-13
**Summary:** After the PPO tensor fix, the first training iteration completes successfully but UE's `NLTTrainingManager::Tick()` calls `Trainer->RunTraining()` every 0.1s with `NumberOfIterations=1`. After the first iteration, the Python subprocess exits cleanly ("Done!"). On the next Tick, UE attempts to start a new training session (NLTTraining7/Configs) but the Python process is gone, producing "Error sending policy to trainer: Unexpected communication received" and repeated "Training has failed" spam.
**Fix applied:** Added `bTrainingCompleted` flag to `ANLTTrainingManager`. First Tick with `bTrain=true` (one training step); subsequent Ticks use `bTrain=false` (inference only, no Python communication). Also added `ResetAgentEpisode_Implementation` override to `UNLTTrainingEnvironment` to resolve the "ResetAgentEpisode function must be overridden!" error.
**Blockers:** Cannot recompile/verify on this machine — no UE build environment available. Requires recompilation and re-run of `run_nlt_training.sh`.
**Next action:** Recompile project and re-run training to verify both fixes work end-to-end.

| Thread | Agent | Date | PR | Summary |
|---|---|---|---|---|
| LLM → Avatar Control | Cline | 2026-09-05 | — | `AAvatarAIController` with `bLLMControlActive`, `ExecuteLLMCommand()` dispatcher; `UNLTWebServerSubsystem` `/api/avatar/command` endpoint; `llm_avatar_agent.py` stdlib-only tool-calling controller. HTTP status-code fix in `509dc0c`. |
| Secret-purge + Code Scanning | Codex | 2026-09-05 | [#36](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/36) | Purged 3 leaked API keys from git history; resolved 7 code-scanning alerts (workflow permissions + postMessage origin verification). |
| M2/M3 VFX + Security Fix | OpenCode | 2026-09-05 | [#27](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/27) | Fixed VFX asset name/path alignment; refined NS_HVACAirflow; removed SecurityToken credential violation. |
| Web Server + SimBody | OpenCode | 2026-09-03 | [#28](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/28) | `UNLTWebServerSubsystem` with `/api/snapshot`, `/api/scene`, `/api/status`, `/api/control`; SimBody kit at real-world cm scale. |
| UE 5.8 World Engine + Babylon.js v2 | Hermes | 2026-09-02 | [#24](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/24) | 115 files, 66MB content: C++ simulation kernel, Mass Entity agent system, 13 scenario DataAssets, 4 level templates, Babylon.js v2 viewer. |
| Graphics/Atmosphere/Character Visuals | OpenCode | 2026-09-02 | [#33](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/33) | Atmosphere subsystem, world object renderer, avatar visuals, cinematic post-process. |
| Training Infrastructure | Hermes | 2026-09-05 | [#38](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/38) | Learning Agents plugin integration, RL dependencies, NLTTrainingManager. |
| NLTGovernanceSubsystem + ASFDK-C++ | Hermes | 2026-09-05 | [#39](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/39) | Plugin sources finalized, ThirdParty ASFDK symlink, core module wiring, OTOI compliance. |
| Docs + README + Template Sync | OpenCode / Kilo | 2026-09-05 | [#40](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/40), [#41](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/41) | README updates reflecting in-engine LLM bridge + NLTGovernanceSubsystem; agent-contribution template sync. |
| CodeRabbit Review Fixes | Hermes | 2026-09-05 | [#42](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/42) | Addressed review comments on NLTTrainingManager and plugin build wiring. |

---

## Resolved Threads (2026-06)

| Thread | Agent | Date | PR | Summary |
|---|---|---|---|---|
| Engine direction — Python simulation engine stub implementation | Claude Code | 2026-06-04 | In progress | Created minimal stub implementations of the four missing modules (base_avatar, base_aide, readiness_assessor, supabase_client) to unblock syntax validation. Engine now compiles cleanly but is not executable end-to-end (stubs raise NotImplementedError). Package structure established. Awaiting architectural decisions. |
| Dev environment setup | Cursor Cloud Agent | 2026-05-29 | [#5](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/5) | Set up Cursor Cloud dev environment, documented lint/test/run commands in AGENTS.md, verified governance validation and frontend prototype |
| Fusion Studio research and replay contracts | Codex | 2026-06-04 | [#8](https://github.com/NeuroLift-Technologies/nlt-world-engine/pull/8) | Adopted the supplied Claude Design Studio shell without overwriting the canonical World Engine, documented the Hugging Face and GitHub landscape, and added a draft v1 simulation/replay contract with a passing deterministic fixture. Visual browser smoke testing remains outstanding because the in-app browser runtime was unavailable. |
| World Engine Phase 6: Asset & Build Validation | Poolside Agent | 2026-09-02 | N/A | Created 13 Scenario DataAssets (UScenarioDataAsset with TSoftObjectPtr<UWorld> LevelReference); created 4 .umap levels (Workplace, Personal, Social, Academic) with ≥10 PlayerStarts, NavMesh, and full lighting; verified all 13 DataAsset→Level bindings resolve correctly; cooking via RunUAT.sh completed with 0 errors; load times 0.1–0.2s (well under 30s target). Full report at `WorldEngine/Saved/Phase6ValidationReport.json`. |
