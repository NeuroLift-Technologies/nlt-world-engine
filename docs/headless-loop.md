# Headless agent-loop run

`tools/headless-loop.sh` runs the closed loop from `docs/agent-loop.md` with no GPU and no window.
It starts a local Fusion endpoint and Godot, runs for a fixed time, stops both, and prints a short
summary. It runs on Linux (or WSL). It is how the AGENT-LOOP-003 headless results were taken. It is
not a CI job.

## Prerequisites

- **Godot 4.7.2 .NET (mono)** editor binary, set as `GODOT`. You also need a .NET 8 SDK on `PATH`
  (with `DOTNET_ROOT` set if it is not system-wide).
- **`asfdk-csharp` checked out beside this repo** (`../asfdk-csharp`). `world-engine-godot.csproj`
  references it; without it the build fails and the script refuses to start.
- **An nlt-ai-fusion checkout**, set as `FUSION_REPO`, plus a Python that has its requirements
  (`FUSION_PYTHON`, default `python3`). To have a model decide, set `FUSION_GGUF_MODEL` to a local
  GGUF file. The Python then also needs `llama-cpp-python`; if that lives in a separate venv, point
  `FUSION_PYTHONPATH` at its `site-packages`. Without a model, Fusion uses its rule-based fallback.
- **`--frames` only:** `xvfb-run` and Mesa (the `llvmpipe` software rasteriser).

## Usage

```bash
export GODOT=/path/to/Godot_v4.7.2-stable_mono_linux.x86_64
export FUSION_REPO=/path/to/nlt-ai-fusion
tools/headless-loop.sh --seconds 120                    # rule-based fallback, 2 minutes
FUSION_GGUF_MODEL=/models/Qwen3-0.6B-Q8_0.gguf \
  tools/headless-loop.sh --iterations 6000 --seconds 600  # model, clean exit after 6000 iterations
tools/headless-loop.sh --frames --seconds 60            # also write software-rendered frames
tools/headless-loop.sh --trace --iterations 8000        # also record an observer trace for the viewer
```

| Option | Meaning |
|---|---|
| `--seconds N` | Stop Godot after N seconds (default 120). With `--iterations`, this is the upper bound. |
| `--iterations N` | Godot quits by itself after N main-loop iterations (`--quit-after`). This is the only clean engine exit; see the shutdown section below. |
| `--agent-id ID` | Roster id sent as the perception's `agentId` (default `stay_alert_001`). Any id Fusion did not register is refused with 404, so `__local_avatar__` here shows the fail-closed path. |
| `--frames` | Render through Xvfb with the Compatibility renderer and write two PNGs per second. |
| `--trace` | Record an observer trace (`nlt.observer-trace.v1`) to `observer-trace.jsonl` in the output folder, validate it, and print record counts. Open it in the World Engine Viewer (`vercel/viewer`). Contract: `docs/contracts/observer-trace-v1.md`. |
| `--skip-build` | Skip `dotnet build` and the asset import, for a second run on the same tree. |
| `--out DIR` | Output folder (default `${TMPDIR:-/tmp}/nlt-headless-loop/<UTC timestamp>`). |

`FUSION_AGENT_LOOP_PORT` changes the endpoint port (default 8001). If something already answers on
that port, the script refuses to start: that server would receive this run's perceptions.

## Outputs

Everything goes to the output folder:

- `godot.log` (colour codes stripped) and `godot.raw.log`.
- `fusion.log`.
- `build.log` and `import.log`, unless `--skip-build` was given.
- `frames-software-rendered/` (`--frames` only).
- `observer-trace.jsonl` (`--trace` only). The writer flushes after every line, so a run stopped
  with SIGHUP still leaves a complete trace up to its last record. Only the final line can be cut,
  and the validator reports that as a warning. Measured 2026-10-29: a 25 s SIGHUP-stopped run left
  198 whole records.

The summary shows:
- how Godot ended (the script exits 1 if Godot exited by itself with a nonzero status);
- the startup line (endpoint, agent id sent, anchor count);
- the number of perceptions posted;
- with `--trace`, the trace's record counts by type and the validator's verdict (the script exits 1
  if the trace is missing or invalid);
- accepted and rejected intents by verb;
- refusal and transport warnings.

**Frames are software-rendered** (Mesa llvmpipe, Compatibility renderer, no GPU). That is why the
folder name says so. Use them to check where the avatar went and what it did. They are not
representative of GPU output, so do not use them for visual judgements (lighting, shadows,
materials, performance). Tag any screenshot taken from them as software-rendered.

**`--frames` also changes the loop's timing.** With `--write-movie` and `--fixed-fps 2`, each
rendered frame advances simulated time by 0.5 s however long it took to render. The agent loop
posts a perception every 2 s of simulated time (`DecisionCadenceSeconds`), so that is one every
four frames. How many arrive per wall-clock second depends on how fast the software renderer is.
Perception counts and cadence from a `--frames` run are therefore not comparable with a headless
run.

## Process handling

Each process runs in its own process group (`setsid`). Its PID goes to `fusion.pid` or `godot.pid`
in the output folder, and the script stops it by signalling that group. It never matches process
names (`pkill -f`): a name pattern can kill the shell that runs the script, or another run's
processes. The script refuses an output folder that already holds PID files, which another run
may own. Any exit, including a failed start, stops both groups. Stopping the group also stops
children: `xvfb-run` and Godot under `--frames`, uvicorn under Fusion's Python.

## Shutdown: Godot ignores SIGINT and SIGTERM

Measured on 2026-10-28 with Godot 4.7.2 .NET, headless, on this project:
- **SIGINT, SIGTERM, SIGQUIT:** Godot keeps running for 40 s or more, with the agent loop enabled
  and without it. The loop driver is not the cause.
- **SIGHUP:** Godot exits at once. That is a termination, not a clean shutdown.
- **`--quit-after N`:** Godot exits by itself with status 0.

An earlier note that SIGINT stops it came from a test whose PID was wrong (job control made `setsid`
fork), so disregard it. The likely cause is that the embedded .NET runtime installs handlers for
those signals and they never end Godot's main loop. That has not been confirmed in the Godot source.

So the script stops Godot with SIGHUP, then SIGKILL if it is still alive after 5 s, and Fusion with
SIGINT (uvicorn's clean stop), then SIGKILL. When you need a clean engine exit (shutdown logs,
anything written on exit), use `--iterations`. On Linux, `Ctrl+C` in a terminal sends SIGINT, so it
does not stop a foreground Godot either. Close the window, or send SIGHUP to its PID.

## Known issues

- The rule-based fallback approaches the first free visible anchor. Its target is usually the
  plaza, where the avatar spawns, so it arrives at once and repeats. The AGENT-LOOP-003 F3/F4 work
  addresses this on the Fusion side.
- Godot logs a warning for every refused perception (unregistered `agentId`). Rate-limiting it is
  an open item under AGENT-LOOP-003.
- On a clean exit, Godot logs `ERROR: Capture not registered: 'beehave'` from the debugger. This
  happens at shutdown and does not affect the run.
