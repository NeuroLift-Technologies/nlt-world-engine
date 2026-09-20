# Escalation Record — UE WorldEngine open-world expansion + third-party asset integration

> Copied from `templates/escalation.md`. A tracking GitHub issue will be filed via
> `ISSUE_TEMPLATE/agent-escalation.md`.

---

## Escalation Record

**Date:** 2026-09-20
**Agent:** OpenCode (Poolside)
**Session:** ses_f42eb19bdffeoge74S1sWybvX4
**OTOI Version:** ORG-DEV-OTOI-1.0.3
**WORLD-ENGINE-OTOI Version:** NLT-WORLDENGINE-OTOI-1.0.0
**Escalation Target:** Joshua W. Dorsey, Sr.
**Priority:** high

---

### Trigger

The user requested pivoting the UE WorldEngine from its current **indoor Sims-like
scenario simulation** toward a **full open-world engine** (matching the Three.js
`openworld-engine` project), and asked whether free UE5 assets from Epic's Fab
marketplace would help. This triggers **two** guardrails:

1. **"No architecture decisions"** (AGENTS.md §Guardrails) — Expanding from 4 indoor
   scenario levels (Workplace, Personal, Social, Academic) to an open world is an
   architectural direction change requiring human sign-off.
2. **"No external integrations"** (AGENTS.md §Guardrails) — Importing third-party
   assets from Fab (Epic Games marketplace) is a third-party content integration
   requiring Joshua's approval.

Additionally, the user labeled this "Path B — Full UE5 Port," but **no "Path B"
open-world direction is documented** anywhere in the repo. The existing "Path A/B"
labels are for training (Path A = UE5 runtime, Path B = Python standalone) and
engine reference (Path A = UE5.8 authoritative, Path B = Python ECS). This labeling
ambiguity requires clarification.

---

### Situation

This workspace contains **three** distinct engine projects:

| Project | Path | Engine | Current State |
|--------|------|--------|---------------|
| **UE WorldEngine** | `WorldEngine/` | Unreal Engine 5.8 | Indoor Sims-like AI simulation (4 scenario `.umap` levels). C++ core subsystems (16 subsystems), Mass Entity, Learning Agents, PCG, Niagara, MCP server. Character system uses custom `SimBody` low-poly mesh with emotion-driven animation pipeline (active **CHAR-001 thread**). |
| Python ECS | `world-engine/` | Python | Reference implementation only (stubs raise `NotImplementedError`). |
| LT OpenWorld | `openworld-engine/` | Three.js 0.170 | Procedural open-world island (terrain, water, sky, vegetation, settlement). Uses procedural generation, no build step, CDN-dependent. |

**What the user wants:** The UE WorldEngine to *also* have an **open-world outdoor layer**
— terrain, water, sky, vegetation, settlement — where **buildings are portals to the existing
indoor scenario levels** (Workplace, Personal, Social, Academic). The outdoor world is the
traversal layer; entering a building loads the corresponding indoor `.umap` level. This mirrors
the Three.js `openworld-engine` AGENTS.md description: "A realistic 3D habitat where AI agents
live" with terrain, water, sky, vegetation, and settlement — but implemented *inside* UE5 rather
than Three.js.

**Key insight:** `NLTWorldGeneratorSubsystem` already produces the *semantic data* for this
architecture — districts (Residential/Commercial/Industrial/Park), buildings (Office/Apartment/
Shop/Factory/Park), and roads. The outdoor world's layout is procedurally defined; the indoor
levels are the pre-built `.umap` scenario maps. The missing piece is the outdoor rendering layer
(terrain, water, sky, vegetation, building shells) and the level-streaming bridge that connects
outdoor building entrances to indoor levels.

**Current WorldEngine state relevant to open-world expansion:**

- `NLTWorldGeneratorSubsystem` (`Source/WorldEngine/{Public,Private}/World/NLTWorldGenerator.cpp|h`)
  already generates **semantic data** for districts (Residential, Commercial, Industrial, Park),
  buildings (Office, Apartment, Shop, Factory, Park), and roads — but it does **not** spawn
  any UE geometry or levels. It's a data-only world generator.
- `NLTWorldObjectRenderer.cpp` exists to visually render the generated world, but its
  integration status is unclear.
- `NLTAtmosphereSubsystem` has time-of-day control (sun, sky light, height fog, color grading)
  but uses **hardcoded FLinearColor values** — no HDRI skybox textures are referenced.
- The PCG plugin is enabled for environment scatter, but the `EnvironmentScatter.uasset`
  is the only PCG asset present.
- 4 scenario levels are `.umap` files with door rows and PlayerStarts — designed for indoor
  navigation, not open-world traversal.
- The character system (CHAR-001 thread) is mid-implementation of rigged SkeletalMesh
  replacement for SimBody static mesh.
- No terrain, landscape, water, or large-scale outdoor assets exist in `Content/`.

**Free UE5 asset list provided by user** covers: Terrain, Vegetation, Water, Sky/Atmosphere,
Characters/NPCs, Buildings/Architecture, Roads/Paths, Lighting/Post-Processing, VFX.

---

### Decision Required

1. **Architectural direction:** Should the UE WorldEngine add an **outdoor open-world layer**
   (procedural terrain, water, sky, vegetation, settlement) where buildings are **level portals**
   to the existing 4 indoor scenario `.umap` files? This adds level-streaming architecture
   (outdoor world ↔ indoor scenario transition) — an integration-gate concern (Codex + Poolside).
   How does this relate to the Three.js `openworld-engine` — should the UE5 outdoor layer replace
   it, run alongside it, or inform it?

2. **Asset vendoring / external integration:** Should free UE5 assets from Epic's Fab marketplace
   be imported into `WorldEngine/Content/`? Which categories are approved? (Fab requires a free
   Epic account; commercial-use verification needed per AGENTS.md.) Categories with the clearest
   fit: Sky/Atmosphere HDRIs, terrain/landscape, water, vegetation/foliage, post-process LUTs.
   Categories needing lane coordination: Characters/NPCs (Pool), buildings (Kilo/architecture).

3. **Character system across both layers:** The active **CHAR-001 thread** (Pool's lane) is
   building a custom emotion-driven animation pipeline around `SimBody` characters for indoor
   scenarios. The outdoor open world needs characters that walk terrain, enter buildings, and
   transition seamlessly into indoor SimBody avatars. Does the same SimBody aesthetic apply to
   outdoor characters, or are separate outdoor character assets (e.g., City Sample Crowds +
   MassCrowd) needed for the outdoor layer?

4. **"Path B" designation:** The user labeled this "Path B — Full UE5 Port." No such path is
   documented in the repo. Does "Path B" mean: (a) a formal architectural designation for the
   open-world outdoor layer, or (b) porting the Three.js `openworld-engine` concept into UE5?
   Needs documentation clarification.

---

### Options Considered

1. **Open-world outdoor layer with indoor building portals (recommended)**
   - Description: Add a procedural outdoor open-world layer (terrain, water, sky, vegetation,
     settlement with the `NLTWorldGeneratorSubsystem` district/building/road data as layout)
     where each building serves as a level-streaming portal to the corresponding indoor
     `.umap` scenario level. Characters transition between outdoor traversal and indoor
     scenario simulation. Import Fab assets for: sky/atmosphere HDRIs, terrain, water,
     vegetation, post-process LUTs. SimBody aesthetic carries through to outdoor characters.
   - Trade-offs: Preserves all current indoor scenario + CHAR-001 development. Adds
     outdoor rendering layer within OpenCode's environmental-assets lane. Level streaming
     bridge is an integration concern (Codex + Poolside). Requires Joshua approval for
     Fab asset integration and architectural direction.

2. **Full open-world pivot (deprecate indoor scenarios)**
   - Description: Replace indoor Sims-like scenario levels entirely with a pure open-world
     engine. Deprecate/archive the 4 `.umap` levels. Import terrain, water, sky, vegetation,
     settlement, AND character/NPC assets from Fab (City Sample, Creative Characters).
   - Trade-offs: Loses all CHAR-001 character pipeline work and Kilo's scenario levels.
     Massive architectural rewrite. Conflicts with Pool's lane (characters) and Kilo's lane
     (scenarios). Not recommended.

3. **Asset import only (sky/atmosphere + post-processing LUTs, no open-world layer)**
   - Description: Only import skybox HDRIs + post-process LUTs to enhance the existing
     `NLTAtmosphereSubsystem`. No terrain, water, or outdoor world. Defer open-world
     architecture.
   - Trade-offs: Lowest risk, fills 2 identified gaps. Fits OpenCode's lane with zero
     cross-lane impact. Does not achieve the open-world goal but de-risks the asset-import
     process for later phases.

4. **Defer entirely**
   - Description: Keep current indoor-only direction. Add to backlog.
   - Trade-offs: No immediate work; preserves focus on CHAR-001 and DOC-MCP-001. Does not
     satisfy the open-world requirement.

### Asset Categorization (per World Engine OTOI §4.4 lanes)

| Asset Category | Lane impact | Status |
|---|---|---|
| Sky & Atmosphere (HDRIs, skyboxes) | OpenCode — environmental lighting | ✅ Clean, recommend approve |
| Post-Processing (LUTS, night presets) | OpenCode — post-processing materials | ✅ Clean, recommend approve |
| Water (Stylized Water) | OpenCode — environmental assets | ✅ Clean if scoped as environmental |
| Vegetation & Foliage | OpenCode — environmental assets | ✅ Clean if scoped as environmental |
| Terrain & Landscape | OpenCode + Kilo (level streaming bridge) | ⚠️ Needs integration planning |
| VFX & Particles | OpenCode — environmental VFX | ✅ Clean, supplements existing Niagara |
| Buildings & Architecture | Kilo (world-state contracts) + OpenCode | ⚠️ Escalate to both lanes |
| Characters & NPCs | Pool (CHAR-001) + Core (governance boundary) | ⚠️ Escalate — conflicts with SimBody pipeline

---

### Recommendation

**Approve Option 1** (open-world outdoor layer with indoor building portals), but with
staged asset approval:

1. **Phase 1 (within OpenCode's lane, no cross-lane conflict):** Approve sky/atmosphere
   HDRIs + post-process LUTs → directly fills the two biggest identified gaps
   (`NLTAtmosphereSubsystem::SkyDomeMaterial` has no HDRI; color grading is hardcoded
   floats). Can proceed immediately after Joshua sign-off.
2. **Phase 2 (environmental, pending integration planning):** Water + vegetation + terrain
   → needs level-streaming architecture discussion with Codex + Poolside (integration gate).
3. **Phase 3 (cross-lane):** Characters + buildings → coordinate with Pool (characters) and
   Kilo (scenarios/world-state) before any asset imports.

The `NLTWorldGeneratorSubsystem` already produces the procedural layout data (districts,
buildings, roads) — the outdoor layer builds on existing infrastructure, not from scratch.

All imports go into `WorldEngine/Content/{Kits|Environment|Sky|Terrain|Vegetation}/`
following the path conventions in `CharacterGraphicsSetup.md`, and must be verified
for license compliance before commercial use.

---

### Blockers

- **Cannot download/import Fab assets** until architectural direction and license
  verification are confirmed (external integration guardrail).
- **Cannot proceed with open-world level design** until the expansion scope is defined
  (architectural decision guardrail).
- **Cannot introduce terrain/character/building assets** until lane ownership is
  clarified (Pool, Kilo may be affected).

---

### Resolution

*(Originally to be filled in after Joshua responds)*

**Date resolved:** 2026-09-20
**Decision:** Approved open-world outdoor layer direction (buildings as portals to indoor
`.umap` levels). Phase 1 asset imports approved. **BUT** Fab assets are NOT downloadable
(confirmed by Joshua W. Dorsey, Sr. — they are not free/accessible despite listing).
C++ integration code prepared and ready to consume assets if they become available.
Pivoting to alternative approaches (procedural systems or alternative free asset sources).
**Decided by:** Joshua W. Dorsey, Sr.
**Actions taken:**
1. Updated escalation with clarified "building portal" architecture
2. Provided categorized Fab download links to approver
3. Prepared C++ integration code (atmosphere HDRI params, post-process LUT support,
   asset directory structure) — ready but awaiting assets
4. **BLOCKED:** Fab assets are not accessible. Cannot proceed with asset imports.

---

## Blocker: Fab Assets Not Accessible

**Date:** 2026-09-20
**Reported by:** Joshua W. Dorsey, Sr.
**Status:** Active blocker

Joshua confirmed that the free UE5 assets listed from Epic's Fab marketplace **cannot be
downloaded** — they are not accessible despite being labeled "free." The C++ integration
code and directory structure are prepared and ready, but without the actual asset files,
the system cannot render the enhanced sky, LUT color grading, water, vegetation, or terrain.

---

## Pivoting to Procedural Approach

**Date:** 2026-09-20
**Status:** Approved direction

Joshua confirmed that **Fab assets are not accessible** (not free / cannot download). Pivoting
to a **procedural approach** instead — porting the already-working procedural systems from the
Three.js `openworld-engine` into the UE WorldEngine. This is fully self-contained, requires no
external asset dependencies, and fits within OpenCode's authorized lane (environmental assets,
materials, lighting, scene organization).

### Procedural Systems Available for Port

The `openworld-engine/src/world/` directory already contains complete, tested implementations:

| System | Three.js Source | UE5 Port Target |
|--------|-----------------|-----------------|
| **Terrain** | `terrain.js` (procedural heightfield with FBM noise, biomes) | `NLTWorldGeneratorSubsystem` + PCG + Landscape |
| **Sky** | `sky.js` (Rayleigh scattering, golden hour, stars, moon) | Enhance existing `NLTAtmosphereSubsystem` sky dome |
| **Water** | `water.js` (translucent plane, wave normals, vertex displacement) | UE5 Water plugin or custom material |
| **Vegetation** | `vegetation.js` (seeded tree/grass/rock scatter) | PCG + existing `EnvironmentScatter.uasset` |
| **Settlement** | `settlement.js` (camp/huts/campfire) | `NLTWorldGeneratorSubsystem::GenerateBuildings()` |

### UE5 Plugin Changes Needed

| Plugin | Currently Enabled? | Purpose |
|--------|-------------------|---------|
| Water | ❌ Not in .uproject | Native UE5 water bodies (lakes, rivers) |
| Landscape | ✅ Engine core | Procedural terrain via PCG |
| PCG | ✅ Already enabled | Procedural scatter (vegetation, rocks) |
| Niagara | ✅ Already enabled | Water splash, dust, environmental VFX |

### Action Plan (Phase 1 — Procedural Sky + Noise Library)

1. Add procedural noise functions to `NLTAtmosphereSubsystem` (port `noise.js` fbm2D/hash functions)
2. Enhance the existing sky dome material to support HDRI cubemap OR procedural Rayleigh scattering fallback
3. Enable the Water plugin in `WorldEngine.uproject`
4. Prepare terrain generation via `NLTWorldGeneratorSubsystem` + PCG (data already exists)
5. Keep all existing C++ HDRI/LUT integration code — works with procedurally-generated cubemaps if needed

**All Fab asset download links and content directory structure remain prepared as a backup
if access becomes available later.**
