# NLT world engine: project context

Load this file when the work touches Josh's NLT world engine. Other names for it: `nlt-world-engine`, `world-engine-godot`, Fusion agent loop, ASFDK gate, `IntentMoveController`, `LocomotionController`, Observer/dashboard HUD.

This summary was taken from the repo on 2026-10-29 (`main`, merge of PR #129). The repo is the source of truth. **If you can read it, read it, and don't rely on this file.** Re-check anything structural, because active agents change it daily.

## Read the repo's own rules first
The repo has an authority chain that outranks this skill:
1. `NLT-DEV-OTOI.md`
2. `AGENTS.md`
3. `CLAUDE.md`
4. `world-engine-godot/AGENTS.md`
5. the subsystem docs: `AGENT-SYSTEM.md`, `ART-PIPELINE.md`, `ASSET-MANIFEST.md`, `docs/agent-loop.md`, `docs/contracts/agent-loop-v1.md`

The final authority is Joshua. When scope, architecture, plugins, assets or licences are unclear, the rule is "escalate, do not guess". Don't treat that as a failure; it's the protocol.

Coding-agent workflow requirements:
- **Claim your thread** in `docs/active-threads.md` before starting work, and check that nobody else has claimed it.
- Commit format: `[AGENT_NAME] type(scope): description`, where type is one of feat, fix, docs, refactor, chore, test, ci.
- Keep each PR to 100 changed files or fewer.
- At the end of a session, hand off to `docs/agent-log/handoffs/` using the template, and record blockers in `docs/escalations/`.
- `.claude/agents/godot-*.md` are third-party persona agents imported from "Claude Code Game Studios" (MIT). They aren't NLT-authored, and they do a version check against `docs/engine-reference/godot/VERSION.md`.

## Stack (verified)
- **Godot 4.7.2 .NET (mono)**, C# only. `Godot.NET.Sdk/4.7.2`, target `net8.0`, `<Nullable>enable</Nullable>`, root namespace `NltWorldEngine`. The standard (non-.NET) Godot build won't run it.
- `project.godot`:
  - features: `"4.7", "C#", "Forward Plus"`
  - **renderer: Forward+**
  - `3d/physics_engine="Jolt Physics"`
  - MSAA 2D/3D ×2, debanding, glow on
  - main scene `res://Main.tscn`
- Autoloads:
  - `Audio` (`scripts/audio.gd`)
  - `MCPRuntimeServer` (godot_mcp_toolkit)
  - Beehave metrics/debugger
  - `_fennara_game_capture`
- Editor plugins: Color grading (Compositor effects), Beehave (behavior trees), `fusion_agent_loop`, `godot_mcp_toolkit`, Sky3D.
- The `.csproj` has a `ProjectReference` to `../../asfdk-csharp/src/Asfdk/Asfdk.csproj`. If the build fails on that reference, the cause is the environment (sibling repo missing). Never fix it by deleting the reference.
- `AgentHarness/`, `AgentLoopEndpoint/` and `tools/` are excluded from the Godot compile glob on purpose. Each has its own entry point.
- `WorldEngine/` holds the Unreal 5.8 tree. It is **frozen and non-authoritative**: don't edit it, and don't treat it as a spec.

## Architecture (verified in code)
- **Fusion** (repo `neurolift-ai-fusion`) owns *semantic* reality: goals, needs, intent. **The engine** owns *physical* reality: position, velocity, collision, consequences. Fusion sends **intents, never coordinates or velocities**.
- **Contract `nlt.agent-loop.v1`** (`docs/contracts/agent-loop-v1.md`):
  - The engine sends a perception snapshot.
  - Fusion returns a semantic intent. The allowed verbs are **`approach`, `look_at`, `use`, `sit`, `rest`, `communicate`, `wait`**.
  - The engine correlates the intent, then rejects it or reports a result.
  - Adding a verb is a contract change. It touches both repos and needs Joshua's decision.
- Code in `world-engine-godot/Agents/`:
  - `IAgentController` (in `LocomotionController.cs`): one synchronous, allocation-light `Act(observation)` per agent per tick. The LLM controller returns the **last decision it managed to produce**, because inference takes far longer than a tick.
  - `LocomotionController` (sealed class): **the only writer of position and velocity.** It handles acceleration and turn-rate limits. Models clamp; they never teleport.
  - `AgentBrain : CharacterBody3D` calls `MoveAndSlide()` every physics tick, so Jolt resolves collisions. (The project `AGENTS.md` still describes it as a bare `Node3D`; the code has moved on.)
  - `AvatarCharacter : AgentBrain` holds the internal controllers `IntentMoveController`, `InteractionController` and `IdleController`. Anchors are reserved on the way to a target and released in `Detach`.
  - The intent path is `FusionHttpLink` (async HTTP to Fusion) → `DecisionParser` → `IntentIngress` → `GovernanceGate` (`AsfdkGovernanceGate` calls the real ASFDK PromptDefense, RRT, Sleepwalker and TOI APIs; `OpenGovernanceGate` is the permissive stand-in) → controllers.
  - `PerceptionBuilder` builds what the agent can see. `DecisionHold` is also part of the loop.
- The agent loop is **opt-in**: `NLT_AGENT_LOOP_ENABLED=1`, plus `NLT_AGENT_LOOP_ENDPOINT` and `NLT_AGENT_LOOP_AGENT_ID` (a roster ID; without it Fusion refuses every decision). Never make it on by default.
- The world is built at runtime by C# builders (`TerrainBuilder`, `SettlementBuilder`, `VegetationBuilder`, `WaterBuilder`), so `Main.tscn` is nearly empty in the editor. That's expected. Interiors are `assets/levels/*.fbx` wrapped by `<Name>_level.tscn`.
- Scene transitions go through `SceneCatalog`, `SceneTransit`, `Portal` and anchors.
- **Godot renders; it never decides.** Keep simulation logic out of rendering code and rendering out of simulation.

## Code conventions (match them)
- File-scoped namespaces, only these four: `NltWorldEngine`, `.Agents`, `.Feed`, `.Observer`.
- 4-space indent, LF line endings, final newline.
- **XML doc comments that explain *why*.** `LocomotionController.cs` is the model to follow.
- `sealed` by default; `in` for readonly structs; `null!` only when initialization is provably guaranteed.
- **No TODO/FIXME/WIP in committed code.**
- Don't rename things just because the plan used a different name; plan-vs-code name differences are intentional.
- One behavior per `.cs` file, named after the class. **Commit the `.uid` files.**
- Observer/HUD:
  - Colors come only from the `Palette` in `Observer/Ui.cs`.
  - Every indicator uses color **and** shape **and** text (Okabe–Ito palette).
  - Support three reading levels (Simple, Coach, Technical) and high-contrast mode.
  - Reduced motion only gates *decorative* motion. Walk cycles always play while an agent moves.
  - Overlays use `MouseFilter = Ignore`. No panel covers more than a third of the viewport. Never invent values the feed doesn't carry.
- Assets: **no asset lands without an `ASSET-MANIFEST.md` row** recording source, licence, date and author. Mixamo licensing is an open risk.

## Verification (required before saying anything is done)
```
dotnet build world-engine-godot/world-engine-godot.csproj      # 0 errors; 2 known nullable warnings in WorldView.cs tolerated, add none
dotnet build world-engine-godot/AgentHarness/AgentHarness.csproj
dotnet run --project world-engine-godot/AgentHarness/AgentHarness.csproj   # all assertions pass (113/113 as of 2026-10-22)
```
- AgentHarness runs **outside the engine**. Passing it doesn't prove the live loop works; say so when you report results.
- For visual changes, a screenshot goes in `world-engine-godot/Images/Screenshots/` and is compared against the dashboard vision images in `Images/Vision/`. "Looks right" doesn't count as verification.
- If you change FBX import settings, delete `.godot/imported/*Level*` and re-import through the editor.

## Live editor access: the Godot MCP Toolkit
The vendored `addons/godot_mcp_toolkit` (v1.0.4) plus the `@npgamedev/godot-mcp-server@1.0.4` bridge (forked at `NeuroLift-Technologies/godot-mcp-server`) expose `mcp__godot-mcp-toolkit__*` tools, such as `scene_get_tree`, `project_get_settings`, `script_read` and `game_start`, with more available through `discover_tools`.
- When those tools are present, **read before you write**: start with `scene_get_tree` or `project_get_settings`.
- Mutating tools change the shared checkout, so claim your thread first.
- If you get a connection timeout:
  - Cold starts take 20–41 s; set `MCP_TIMEOUT=90000` in `.claude/settings.local.json`.
  - Or a stale `"port": -1` entry is sitting in `%APPDATA%\godot-mcp-toolkit\projects.json`. Opening the editor clears it. Don't hand-edit the file.

## Hardware reality
- The **dev PC is Windows, with 7.8 GB RAM and Intel UHD 630 integrated graphics.** It runs the mono build on Forward+.
- The binding limit is **memory, not CPU**. With the editor, the game and the local Qwen3-0.6B GGUF all running, Windows pages out the model and decisions take 120–400 s. With the editor closed, they take about 1–3 s. **Run model-driven tests with the editor closed.**
- Performance targets: 60 FPS, under 16 ms per frame, 10–20 animated characters.
- On UHD 630, the costs to watch are shadows, MSAA, glow/SSR, and transparent overdraw from vegetation. Measure before turning terrain shadows back on (they're currently off).
- Older machines (the OptiPlex 3010s with HD 2500, and the Celeron laptop) are not the world engine's target. If someone wants to support them, the answer is the Compatibility renderer, and that's a decision for Joshua.

## Known open issues (as of 2026-10-22; check `active-threads.md`)
- With the shipped prompt, the Qwen model mostly picks `look_at` on whichever entity is listed first. With nothing in perception range, `wait` can freeze the avatar for good. Both need decisions on the Fusion side or from Joshua; they aren't engine bugs.
- The Fennara runtime session can't boot on the dev PC because its 20 s deadline runs out during mono startup. Use the CLI capture path instead.

## Working with Josh
In chat, Claude does architecture, review and synthesis, and coding agents implement. When work is heading for implementation, end with the Handoff brief from SKILL.md. Point the brief at the repo's own documents (claiming, commit format, verification) instead of restating them. Josh values honest pushback; say directly when a design breaks a boundary listed above.
