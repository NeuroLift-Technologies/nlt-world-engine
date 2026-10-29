# World Engine Viewer (`vercel/viewer`)

A browser spectator for the NLT World Engine: the Godot island and its interiors, rebuilt in the
browser from the engine's own builders and assets, with AI agents placed where an
`nlt.state-feed.v1` feed says they are.

It is a **projection**, not a simulation. Godot owns physical reality, AI-Fusion owns semantic
reality, and this viewer only draws what a feed source hands it. Separate Vercel project
(`world-engine-viewer`); the public site in `web/` is untouched.

```
npm ci
npm run dev        # syncs Godot assets, then Vite on :5173
npm run build      # syncs assets, tsc --noEmit, vite build -> dist/
npm run preview    # serve dist/ on :4173
```

URL parameters (handy for demos and captures): `?replay=stayalert-day|open-world-day|rescue-only|collapse-only`,
`&scene=open_world|workplace_7|…`, `&frame=N`, `&play=0`, `&about=1`.
The `nlt.observer-trace.v1` replay viewer is at `trace.html`: it opens traces the Godot engine
records (see §8).

---

## 1. Audit (2026-10-29)

| Looked at | Finding |
|---|---|
| `vercel/viewer/` (before) | Vite + vanilla TS replay viewer for the *draft* `nlt.observer-trace.v1` JSONL: a 2D top-down canvas plot, driven by an **embedded invented trace** (`agent_alfa`, "plaza", made-up coordinates). No world rendering. |
| `world-engine-godot/Images/Screenshots/` | 29 captures of the native Godot observer: low orbit camera over a pine-covered island, a 19-building settlement around a paved plaza (homes, office tower, brick school with portico, shops with striped awnings), a lake, four furnished interiors, primitive white resident figures with name labels, dark observer panels. Every shot is badged *"REPLAY — NOT A LIVE SIMULATION"*. These were the visual reference. |
| `world-engine-godot/*.cs` | The open world is **procedural and deterministic**: `WorldGeometry` (seeded fbm heightfield), `TerrainBuilder`, `WaterBuilder`, `SettlementBuilder` + `BuildingArchetypes` (seeded plan sampler → four silhouettes), `VegetationBuilder` (seeded trees/rocks/grass). Seed `20260401`. Interiors are four project-owned FBX levels restyled by `InteriorStyle`. Residents use a self-authored Blender probe character with a walk clip. |
| Transport | **None reachable from a browser.** Godot 4 cannot export C# to the web (`DEPLOYMENT.md`). The planned Python sidecar (HTTP 8765 / WS 8766) is loopback; `POST /agent-loop/perception` is loopback-only by design. |
| Data | `world-engine-godot/fixtures/replay/*.json` — four `nlt.state-feed.replay.v1` bundles. All are **authored fixtures** (their `provenance` says so); no policy produced them. |
| Vercel | Project `world-engine-viewer` (team NeuroLift Technologies, framework Vite, Node 24, SSO protection on previews). Recent previews built from `feature/viewer-godot-world` (PRs #123/#125) contain a separate Canvas-2D *approximation* of the island (`world3d.ts`: "in the spirit of `WorldGeometry.HeightAt`", palette "tuned to the screenshots"). This work does not build on that branch; see §6. |
| Repo hygiene | `vercel/viewer/node_modules/` has 93 tracked files (committed in `63aa0df`). Left as found; a `.gitignore` is added so nothing new is tracked. Recommend `git rm -r --cached vercel/viewer/node_modules`. |

**Screenshot vs implementation discrepancies found**

1. `Personal_Level.fbx` contains a UE placeholder mesh named `Hermes`. `InteriorStyle.cs` hides
   `SimBody_Character*` and `AvatarCharacter` but not `Hermes`, so Godot draws a figure in the
   Home interior that reads as an extra person. The viewer hides it (it must not show people the
   feed doesn't contain). **Godot-side fix:** add `Hermes` to the hide rule in `InteriorStyle.Dress`.
2. `interior-workplace_1.png` / `_2.png` carry a HUD reading *"WORLD VIEW / Home"*: the file names
   say Workplace, the observer said Home. The implementation (scene ids → levels in `WorldView.InnerScenes`) was used as the reference.
3. Atmosphere: Godot's Sky3D haze is heavier and greyer than the viewer's sky/fog stand-in. Geometry,
   layout and palette come from the C#; the sky model does not (§3).

## 2. What is on screen and where it comes from

| Layer | Kind | Source |
|---|---|---|
| Island terrain, water, settlement, trees, rocks, grass | **Static scene data** | TypeScript ports of the Godot builders (`src/world/*`), same seed, constants, RNG order and float32 rounding at decision points. Building placement matches Godot's captures building-for-building (compare `settlement-archetypes.png` at tick 711). |
| Interiors (Home, Workplace, Social, School) | **Static scene data** | The project-owned FBX levels Godot loads, converted the way Godot's ufbx importer does (Z-up cm → Y-up m), dressed by a port of `InteriorStyle` — so building *N* opens in scheme *N* (`workplace_7`, …). |
| Agents, named states, needs, goals, events, fusion readiness | **Feed data** — currently *authored fixture* | `nlt.state-feed.v1` frames from `world-engine-godot/fixtures/replay`. Validated per contract §9; rejected frames are listed under "Feed diagnostics", never drawn. |
| Resident figure + walk cycle | Static asset | `nlt_resident_walk.glb` (self-authored probe, ASSET-MANIFEST row). Walks only while the feed's velocity says the agent moves (contract §4.4); stands on frame 0 otherwise. |
| Live simulation | **Unavailable** | `LiveRelaySource` reports itself unavailable and says why (§5). |

The top bar always says *Replay · authored fixture · not live*; the HUD says *Static scene* when the
observer looks at a scene with no feed agents in it. Nothing is labelled live that isn't.

## 3. Design and architecture decisions

- **Rebuild the world, don't paint it.** The screenshots have Godot's observer UI baked in, and C#
  cannot be web-exported, so neither images nor a Godot export could be the viewport. The world
  is procedural and small (~1,200 lines of builders), so porting the builders gives the *actual*
  island — any spot, any angle, agent positions landing on the same ground — instead of an
  impression of it. If the C# changes, these files must follow (each names its source).
- **three.js** is the one runtime dependency (WebGL, instancing, GLTF/FBX loaders). FBXLoader is
  code-split and only fetched when an interior opens. No backend, database or relay was added.
- **Spectator camera** is `WorldView.cs`'s: FOV 52, orbit target on the plaza, yaw 0.6, pitch 0.42,
  78 m; drag to orbit (same rates), wheel/pinch zoom 8–340 m, WASD/arrows pan at 24 m/s; interiors
  framed by `FrameInterior`'s rule. Follow mode tracks the selected agent.
- **Feed boundary** (`src/feed/source.ts`): every source declares `kind` (`replay` | `live`),
  status and plain-language provenance, which the UI shows verbatim. Positions are interpolated
  between ~1 Hz frames, as the engine does; nothing else is derived. Fusion-owned numbers
  (independence, readiness) are displayed as received and marked as such; a blocked pair reads
  "Not ready yet", never "failed" (contract §5 presenter obligation).
- **Vocabulary** is a port of `Observer/PlainLanguage.cs` (state words, glyphs, need words), and the
  palette is `Observer/Ui.cs`'s Okabe–Ito set. State is always glyph + word + colour, never colour alone.
- **Reduced motion** (checkbox, defaults to the OS setting) gates wind sway only; walk cycles always
  play while an agent moves (Joshua, 2026-10-28, GRAPH-001).
- **Layout:** the world is full-bleed; agent roster/inspector (left, collapsible), event feed
  (right, collapsible), minimap, and a replay transport with event markers. Under 700 px the
  roster becomes a chip strip above the transport and details collapse by default.
- **Assets are synced, not copied into git.** `scripts/sync-godot-assets.mjs` copies the fixtures,
  resident and levels from `world-engine-godot/` into `public/godot/` (gitignored) before dev/build,
  and fails loudly if any are missing, so the viewer can't drift from the engine's files.
- **CSP** stays strict on scripts (`script-src 'self'`); `style-src` allows inline style attributes
  (bar widths, label positions) and `img-src`/`connect-src` allow `blob:` for loader textures.

### Look and render quality (`src/scene/look.ts`)

Presentation only: these settings change how the same world is lit and finished, never its
geometry, positions or state, and they add nothing the engine doesn't have.

- **Looks** (switch in the transport bar, or `?look=golden|midday`): *Golden hour* (default) puts a
  low warm sun to the left of the default camera, with a matching sky dome (sun disc and glow),
  haze, and image-based light from that sky; *Midday* is close to the original noon stand-in.
  Neither is Godot's Sky3D model, and neither drives time from the feed.
- **Quality** (`?quality=high|fast`): *High* adds ground-truth ambient occlusion, subtle bloom
  (lit windows, sun glint), tone mapping and SMAA edge smoothing, with 4096² soft shadows. *Fast*
  renders directly with 2048² shadows. Touch devices start in Fast.
- **Surface detail:** fine world-space noise on the terrain and a base-to-tip shading gradient on
  trees and grass, so the 2.2 m terrain grid and flat-coloured cones don't read as flat patches.
  Palette colours stay Godot's.
- **Layout:** compact agent list (top left), selected-agent card (bottom left), events (bottom
  right), island map (corner), role-coloured map pins on agent labels (Avatar green, Aide blue,
  Advocate purple; the role word is always shown too).

## 4. Verification (run 2026-10-29)

| Command | Result |
|---|---|
| `npm ci` | ok, 0 vulnerabilities |
| `npm run build` (= sync + `tsc --noEmit` + `vite build`) | ok, no warnings · `main` 436 kB (118 kB gz) + `three.core` 237 kB (65 kB gz) + lazy `FBXLoader` 47 kB · assets 2.2 MB |
| Headless Chromium (SwiftShader WebGL), 18 interaction checks | 18/18 pass, no console errors: autoplay, pause, step, scrub, agent labels, selection → inspector, follow, building click → tooltip → interior (`personal_1`), static-scene note, follow-the-feed returns to open world, live-relay dialog, StayAlert follows the feed into `personal_1`, 5 events at final frame, 17 timeline markers, drag orbit, wheel zoom |
| Visual comparison | Viewer at tick 711 vs `settlement-archetypes.png` (same tick): same buildings, same positions, agents on the same spot of the plaza. Four interiors checked against Godot captures. Desktop 1152×648 and mobile 390×844 checked. |

## 5. What live viewing still needs

1. **Observer relay** — a read-only, authenticated service that carries `nlt.state-feed.v1`
   documents from the Godot/Fusion runtime to browsers (SSE or WebSocket). It must not proxy the
   loopback agent-loop endpoint. Then implement `FeedSource` for it; the UI needs no other change.
2. **Producer** — the Python sidecar / Fusion bridge emitting conforming feed documents at the
   tick (contract §10 leaves transport open). Stable `eventId`/`occurredAt` are still contract-only.
3. **Godot ↔ viewer parity check** — a headless Godot run that dumps `BuildPlans`, tree spots and a
   height sample to JSON, checked against `src/world/*` in CI, so a C# builder change can't silently
   diverge. (Placement already matches the captures; this makes it enforceable.)
4. **AI-Fusion** — agent intelligence, ADHD trait modelling, coaching and learning stay in Fusion;
   the viewer only needs its outputs in the feed. Supervised interaction (Advocate actions,
   training control) needs a separate, authorised control surface — never a write path into the feed.
5. **Vercel** — the build reads `../../world-engine-godot`, so the project needs *Include files
   outside the Root Directory* enabled (default for new projects) with Root Directory `vercel/viewer`.

## 6. Relationship to `feature/viewer-godot-world` (PRs #123/#125)

That branch adds `world3d.ts`, a Canvas-2D drawing of an island "in the spirit of" the Godot world
(approximate heightfield, tuned palette, illustrative houses) on top of the trace viewer. This
implementation replaces that approach rather than merging with it: here the heightfield,
settlement, vegetation and interiors are the engine's own, and agents come from state-feed frames
instead of the invented demo trace. Decide which line continues before merging either.

## 7. Files

`index.html` · `src/main.ts` (app, controls, panels) · `src/style.css` ·
`src/scene/world.ts` (renderer, camera, scenes, residents) · `src/scene/interiorStyle.ts` ·
`src/scene/minimap.ts` · `src/world/{geometry,terrain,settlement,vegetation}.ts` (Godot ports) ·
`src/feed/{types,source,replay,live,plain}.ts` · `scripts/sync-godot-assets.mjs` ·
`trace.html` + `src/trace-main.ts` + `src/trace.css` + `src/trace/*` (observer-trace replay, §8).

**Known limitations:** sky/day-night is a fixed stand-in for Sky3D (two looks, no clock); Label3D building words are
drawn at twice Godot's size for legibility; no LOD (19 buildings, ~1,000 instanced plants — fine on
desktop and recent phones).

## 8. Observer traces (`trace.html`)

`trace.html` replays an **observer trace** (`nlt.observer-trace.v1`, contract:
[`docs/contracts/observer-trace-v1.md`](../../docs/contracts/observer-trace-v1.md)) recorded by the
Godot engine. It shows each scene from above, the intent → result log with the stage that decided
each one (protocol / governance / physical / accepted), a summary, and a timeline of scene
transitions and failed decisions. Like the spectator, it only observes: a trace you open is read
in the browser and sent nowhere (CSP `connect-src 'self'`).

1. **Record.** Headless (Linux/WSL, no GPU), with a local Fusion:
   `GODOT=… FUSION_REPO=… tools/headless-loop.sh --trace --iterations 8000`. This writes
   `observer-trace.jsonl` to the run's output folder and validates it
   ([`docs/headless-loop.md`](../../docs/headless-loop.md)). From a windowed or editor run, pass
   `-- --trace [path]` or set `NLT_OBSERVER_TRACE=1` (needs `NLT_AGENT_LOOP_ENABLED=1`).
2. **Check** (optional; the headless script already does):
   `python3 tools/validate_observer_trace.py --summary <file>.jsonl`.
3. **Open.** Use "Open trace…" or drop the file on the page. With no file loaded, it shows the
   built-in sample: a real headless run imported from
   [`fixtures/observer-trace/`](../../fixtures/observer-trace/README.md). `vite.config.ts` lets the
   dev server read that one folder outside the app root.

Controls: Space plays or pauses; ← and → step between ticks that have a record. The engine's tick
is a frame and ticks are sampled at `cadenceHz`, so playback moves one recorded tick per
1/`cadenceHz` at 1×. Agent identity is shape plus label, and stage is shape plus text, never colour
alone. Live streaming is not built; the options are in
[`docs/escalations/2026-10-29-observer-live-transport.md`](../../docs/escalations/2026-10-29-observer-live-transport.md).
