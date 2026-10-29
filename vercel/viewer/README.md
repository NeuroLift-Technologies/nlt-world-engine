# World Engine Viewer

The human-facing replay viewer for the NLT World Engine. It is a separate Vercel deployment from the
public `web/` site.

**What it does:** opens an observer trace (`nlt.observer-trace.v1`, contract:
[`docs/contracts/observer-trace-v1.md`](../../docs/contracts/observer-trace-v1.md)) that the Godot
engine recorded, and replays it. It shows a top-down plot per scene, the intent → result log with
the stage that decided each one, a summary, and a timeline of scene transitions and failed
decisions.

**What it is not:** a live view or a simulation. The viewer only observes. It has no network code
(CSP `connect-src 'self'`), and a trace you open is read in the browser and sent nowhere. Live
streaming is a separate, undecided step. See
[`docs/escalations/2026-10-29-observer-live-transport.md`](../../docs/escalations/2026-10-29-observer-live-transport.md).

Stack: Vite + vanilla TypeScript, Canvas 2D for the plot, no runtime dependencies.

## Record a run, then open it

1. **Record.** Headless (Linux/WSL, no GPU), with a local Fusion:

   ```bash
   GODOT=/path/to/Godot_v4.7.2-stable_mono_linux.x86_64 FUSION_REPO=/path/to/nlt-ai-fusion \
     tools/headless-loop.sh --trace --iterations 8000
   ```

   The trace is written to `observer-trace.jsonl` in the run's output folder, and the summary
   validates it. Details: [`docs/headless-loop.md`](../../docs/headless-loop.md).

   From the Godot editor or a windowed run, pass `-- --trace [path]` after Godot's own arguments,
   or set `NLT_OBSERVER_TRACE=1` (default path `user://traces/<runId>.jsonl`). Tracing records the
   Fusion agent loop, so it needs `NLT_AGENT_LOOP_ENABLED=1`.

2. **Check it** (optional; the headless script already does):
   `python3 tools/validate_observer_trace.py --summary <file>.jsonl`

3. **Open it.** Use "Open trace…" or drop the `.jsonl` file anywhere on the page. With no file
   loaded, the viewer shows the built-in sample, a real headless run
   ([`fixtures/observer-trace/`](../../fixtures/observer-trace/README.md)).

## Develop

```bash
cd vercel/viewer
npm ci
npm run dev          # http://localhost:5173
npx tsc --noEmit     # typecheck
npm run build        # static output in dist/
```

The built-in sample is imported from `fixtures/observer-trace/sample.jsonl`, outside this folder.
`vite.config.ts` lets the dev server read that one folder only.

## Deploy (Vercel)

`vercel.json` sets the build and sends the CSP and related headers as real HTTP headers (a `<meta>`
CSP cannot set `frame-ancestors`). Settings for the Vercel project:

- **Root Directory:** `vercel/viewer`
- **Include files outside the Root Directory:** on (the default). The build reads the sample from
  `fixtures/observer-trace/`.

Creating the Vercel project and any production deployment are Joshua's to approve (OTOI §4.4).

## Controls

Space plays or pauses. ← and → step to the previous or next tick that has a record. The engine's
tick is a frame and ticks are sampled at `cadenceHz`, so playback moves one recorded tick per
1/`cadenceHz` at 1×. Click a timeline marker to jump to it. Agent identity is shown by shape plus
label, and stage by shape plus text, never by colour alone.
