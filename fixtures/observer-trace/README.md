# Observer trace sample (`nlt.observer-trace.v1`)

`sample.jsonl` is a **real recording**, not hand-written. It was taken from one headless engine run on
2026-10-29 (OBS-TRACE-001):

```bash
GODOT=…/Godot_v4.7.2-stable_mono_linux.x86_64 FUSION_REPO=…/nlt-ai-fusion \
  tools/headless-loop.sh --trace --iterations 8000 --seconds 300
```

- Godot 4.7.2 .NET, `--headless` (no GPU, no window), Linux container.
- Fusion's **rule-based fallback** (no GGUF model), agent `stay_alert_001`.
- 8000 main-loop iterations, clean exit (`--quit-after`). 647 records: 30 perceptions, 30 intents
  (approach 4, sit 17, use 9), 30 results (all accepted), 1 scene transition
  (`open_world` → `workplace_2`), 554 sampled ticks at 10 Hz.
- `engineCommit` in the header is `c7d545e`, the base commit. The run was taken from the working
  tree that adds the trace writer, before it was committed.

It is used as:
- the trace viewer's built-in demo (`vercel/viewer/src/trace-main.ts` imports this file), so it is
  always shown against what the engine really writes;
- a validator fixture: `python3 tools/validate_observer_trace.py fixtures/observer-trace/sample.jsonl`.

To refresh it, re-run the command above and copy `observer-trace.jsonl` from the output folder over
this file. Then update the counts above. Contract: `docs/contracts/observer-trace-v1.md`.

**What this sample does not show:** rejections and `decision_failed`. The rule-based fallback
picks only valid targets, so nothing is refused. A run with `--agent-id __local_avatar__` (an id
Fusion did not register) exercises the fail-closed path: every decision is a `decision_failed`
with HTTP 404.
