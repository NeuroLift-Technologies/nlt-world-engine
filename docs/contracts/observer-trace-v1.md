# Observer Trace Contract — `nlt.observer-trace.v1`

**Status:** draft · **Decided by:** Joshua, 2026-10-29 (observer trace + replay viewer handoff)
**Direction:** world engine → file → read-only viewers. Nothing flows back.
**Schema:** [`observer-trace-v1.schema.json`](observer-trace-v1.schema.json) (one JSONL line)
**Checker:** `tools/check_observer_trace.py`

## 1. Purpose and authority

A record of what the engine did, written so a run can be replayed and looked at afterwards. It is
the input for a read-only replay viewer. It is **not** a control channel and adds nothing to the agent loop.

- **Physical fields come from Godot only.** Positions, velocities, scenes, transitions and the
  engine's accept/reject decisions are read from engine state at the moment they happen. The trace
  carries **no Fusion state**: no needs, goals, cognitive state, coaching or readiness. A later
  Fusion overlay joins on `agentId`, `tick` and the intent `messageId` (§6); it is not part of this
  contract.
- **Separate from the other two contracts.** [`state-feed-v1`](state-feed-v1.md) runs Fusion → Godot
  and is fixture data. It is neither reversed nor extended here. [`agent-loop-v1`](agent-loop-v1.md)
  is unchanged. The `stage` and `governanceCode` of a `result` record (§4.5) exist only in this trace.
- **Opt-in and inert by default.** With no trace configured, the engine runs exactly as before. With
  a trace configured, it records what the loop does and changes none of it (§8).

## 2. File format

- UTF-8 JSON Lines: one JSON object per line, each ending in `\n`. Keys appear in the order shown in
  this document. Every record starts with `"type"`.
- **Line 1 is the `header`**, and no other line is a header.
- **Numbers.** Positions and velocities are metres and metres/second in the Godot world frame (y up).
  They are the engine's 32-bit floats written in shortest round-trip form; compare them as 32-bit
  floats. If the engine holds a non-finite value (NaN or infinity), the component is written as
  `null`.
- **A trace is a gap-free prefix of the run.** If the writer stops early (§7), the last line is one
  `truncated` record and nothing follows it. A trace with no `truncated` record either ended normally
  or was killed, for example by the SIGHUP that `tools/headless-loop.sh` uses. Every line up to the
  last flush is complete. A reader should drop a final line with no newline.

## 3. Ticks and ordering

- **`tick`** is `AgentLoopDriver`'s frame counter. It goes up by one per `_Process` frame while the
  loop runs, and it is the same number the engine puts in `nlt.agent-loop.v1` `perception.tick`. It
  is not a physics-step count and not wall time. At the default cadence, consecutive `tick` records
  are about 0.1 s of game time apart, but the number of frames between them depends on the frame
  rate.
- **`atTick`** (on `intent`, `result` and `decision_failed`) is the driver tick when the engine
  recorded the event. `tick` and `observedTick` on those records name the perception the event
  answers. A decision that took 3 s of inference therefore has `atTick` well after `tick`.
- **File order is emission order.** Records are not sorted by tick. An `intent` and its `result`
  can appear after later `tick` records. A viewer places a record on the timeline by `atTick` (or
  `tick` where it has no `atTick`), not by line number.

## 4. Records

### 4.1 `header` (line 1)

```json
{"type":"header","schemaVersion":"nlt.observer-trace.v1","runId":"run-20261029T082728Z-56cd5a7f",
 "engineCommit":"44ddd6f7b4fbc4f56d67a072c11ccc703b0c57f7","godotVersion":"4.7.2-stable (official)",
 "startTime":"2026-10-29T08:27:28.033Z","traceHz":10,"maxBytes":67108864,
 "agents":[{"agentId":"stay_alert_001","engineId":"__local_avatar__","displayName":"Local Model","driver":"fusion-agent-loop"}]}
```

(Shown wrapped; in the file it is one line.)

| Field | Meaning |
|---|---|
| `runId` | `NLT_OBSERVER_TRACE_RUN_ID`, else `run-<UTC start>-<8 hex>` |
| `engineCommit` | `NLT_ENGINE_COMMIT` if set (`tools/headless-loop.sh` passes `git rev-parse HEAD`, with `-dirty` added for a modified tree), else the HEAD read from the checkout's `.git`, else `unknown` |
| `godotVersion` | `Engine.GetVersionInfo()["string"]` |
| `startTime` | UTC, millisecond precision, when the recorder started |
| `traceHz` | the cadence of `tick` records |
| `maxBytes` | the size cap (§7) |
| `agents` | the roster this trace records. `agentId` is the id on the wire (the roster id Fusion registered, e.g. `stay_alert_001`); `engineId` is the engine's node name for it (`__local_avatar__`) |

### 4.2 `tick` — sampled physical state

```json
{"type":"tick","tick":1,"agentId":"stay_alert_001","scene":{"id":"open_world","kind":"open_world"},
 "position":{"x":2.5,"y":7.375,"z":-1.25},"velocity":{"x":0,"y":-0.5,"z":0}}
```

One per roster agent at `traceHz` of game time, including the first loop frame (the spawn). Read
from the avatar's `GlobalPosition`, `Velocity` and `SceneId` in the same frame the driver advanced
the tick. `scene.kind` is `open_world` or `interior` from `SceneCatalog`, or `unknown` for an id the
catalog does not name.

### 4.3 `perception_sent`

```json
{"type":"perception_sent","tick":1,"agentId":"stay_alert_001","messageId":"obs-1-__local_avatar__-0"}
```

A perception was actually POSTed to Fusion. A perception the driver built but did not send, because
a request was already in flight or the link was backing off after a transport error, has no record.
`messageId` is the perception's agent-loop `messageId`.

### 4.4 `intent`

```json
{"type":"intent","messageId":"intent-1-stay_alert_001","agentId":"stay_alert_001","observedTick":1,
 "verb":"approach","targetId":"plaza","atTick":4}
```

Fusion answered with an intent that parsed and correlated with its perception. `targetId` is `null`
when the verb has none. These are the agent-loop intent's own fields, copied as received.

### 4.5 `result` — where the engine decided

```json
{"type":"result","intentMessageId":"intent-9-stay_alert_001","agentId":"stay_alert_001","tick":9,
 "status":"rejected","stage":"physical","governanceCode":"clean","reason":"target 'well' is occupied","atTick":12}
```

`intentMessageId`, `agentId`, `tick`, `status` and `reason` are copied from the engine's agent-loop
result envelope. `reason` is `null` when the envelope has none. `stage` is where `IntentIngress`
decided:

| `stage` | `status` | Decided by (`world-engine-godot/Agents/IntentIngress.cs`) |
|---|---|---|
| `protocol` | rejected | `AgentLoopProtocol.ValidateIntent` at ingress, before governance. `governanceCode` is `null` |
| `governance` | rejected | the ASFDK gate denied (`decision.Allowed == false`), including a gate exception (`gate-unavailable`) |
| `physical` | rejected | engine state refused it after governance allowed it: the avatar is gone or between scenes, a stale target, out of reach, the target does not afford the verb or is occupied, or a doorway cannot be used |
| `accepted` | accepted | accepted for execution, which does not mean the outcome has happened yet (agent-loop-v1 §4) |

`governanceCode` is the gate's decision code (`clean`, `injection`, `crisis`, `distress`,
`gate-unavailable`) whenever governance ran.

**On the live HTTP path `protocol` does not occur.** `FusionHttpLink` validates the intent against
its perception before ingress, and an answer that fails that check becomes a `decision_failed` record
with `error: "invalid_intent"`, not a `result`. The stage is defined for completeness, in case ingress
is called from another path.

### 4.6 `decision_failed`

```json
{"type":"decision_failed","agentId":"stay_alert_001","tick":17,"httpStatus":429,"error":"http_status","detail":null,"atTick":18}
```

The exchange for the perception at `tick` produced no intent, and no physical action followed:

| `error` | `httpStatus` | When |
|---|---|---|
| `http_status` | the status (e.g. 404, 429, 503) | Fusion answered non-2xx |
| `invalid_intent` | `null` | 2xx, but the body was not a valid intent for that perception; `detail` is the validation message |
| `timeout` | `null` | no answer within `FusionHttpLink.RequestTimeoutSeconds` |
| `transport` | `null` | the request failed (e.g. connection refused); `detail` names the exception and, where .NET reports one, the `HttpRequestError` |
| `invalid_response` | `null` | the response could not be read as JSON at the transport level |
| `engine_error` | `null` | an unexpected engine exception while processing the decision |

### 4.7 `scene_transition`

```json
{"type":"scene_transition","agentId":"stay_alert_001","from":"open_world","to":"workplace_2","tick":2741}
```

Written when the engine has placed the avatar in the destination scene (`Main.RunTransit`, after
`AvatarCharacter.TransitionTo`). `tick` is the driver tick at that moment. A transit that fails and
leaves the avatar where it was has no record.

### 4.8 `truncated` (last line, only when the writer stopped early)

```json
{"type":"truncated","reason":"size_cap","bytesWritten":67108608,"recordsWritten":300417}
```

`reason` is `size_cap`, `queue_full` or `io_error` (§7). `bytesWritten` is the file size before this
record. `recordsWritten` counts every line in the file, this one included.

## 5. What the trace does not contain

- No Fusion state (§1). No coordinates that came from Fusion: the agent loop has none.
- No perception bodies: `visibleEntities` is not copied.
- No `state-feed-v1` documents and no replay-fixture ghosts.
- Only the agents on the header roster. Today that is the one loop avatar.

## 6. Join keys for a later Fusion overlay (not built)

| Key | Records |
|---|---|
| `agentId` | every record except `header` and `truncated`; the header maps it to `engineId` |
| `tick` (= perception `tick` = intent `observedTick`) | `tick`, `perception_sent`, `intent.observedTick`, `result`, `decision_failed`, `scene_transition` |
| `messageId` | `perception_sent.messageId` (perception), `intent.messageId` = `result.intentMessageId` |

## 7. Writer: opt-in, bounded, never blocks

Configured from the environment (`ObserverTraceRecorder.TryCreateFromEnvironment`). The trace is
written only while the Fusion agent loop runs, because the loop defines `tick`.

| Variable | Default | Meaning |
|---|---|---|
| `NLT_OBSERVER_TRACE` | unset: **no trace** | output file (an OS path, or `user://` / `res://`) |
| `NLT_OBSERVER_TRACE_HZ` | `10` | `tick` record cadence, 0.1 to 120 |
| `NLT_OBSERVER_TRACE_MAX_MB` | `64` | size cap in MiB, 1 to 4096 |
| `NLT_OBSERVER_TRACE_RUN_ID` | generated | `runId` |
| `NLT_ENGINE_COMMIT` | read from `.git` | `engineCommit` |

- **Never blocks the physics thread, or any thread.** Callers build one line and hand it to a queue.
  A dedicated background thread (`ObserverTraceWriter`) writes the queue to the file and flushes it
  whenever the queue drains. No caller waits on the disk.
- **Size cap.** When the next line would push the file past `maxBytes` (minus 256 bytes kept for the
  marker), the writer writes one `truncated` record with `reason: "size_cap"` and accepts nothing
  more. The file never exceeds `maxBytes`. At 10 Hz with one agent, the headless baseline writes
  about 2 KB/s, so the 64 MiB default holds roughly 9 hours.
- **Queue cap (16,384 lines).** If the disk falls that far behind, the trace stops the same way with
  `reason: "queue_full"`: lines queued before the overflow are written, then the marker. The trace
  never skips lines and carries on, so a viewer can trust everything up to the marker.
- **Disk errors** stop the trace (`io_error`) without affecting the loop. The marker may not be
  written if the disk itself has failed.
- **Never changes `FusionHttpLink` or `IntentIngress` behaviour.** Both take an optional
  `IAgentLoopTrace`, `null` by default. Every report is wrapped so that a fault in the trace cannot
  reach the decision path. Request pacing, timeouts, backoff, results and log lines are the same with
  the trace on or off.

## 8. Verification tools (test only, inert unless asked)

Passed after a bare `--` on the Godot command line:

- `--trace-truth <file>` (`TraceTruthSampler`): on every driver tick, reads each avatar's position,
  velocity and scene from the scene tree. It shares nothing with the recorder but the tick number,
  and writes its own file. `tools/check_observer_trace.py --truth` compares every `tick` record
  against it.
- `--trace-occupy <anchorId>` (`TraceOccupant`): fills one open-world anchor to capacity with
  placeholder occupants for 30 s, so a loop intent on it meets a real "occupied" re-check.
- `--capture <prefix> --capture-every <ticks> [--follow]` (`ObserverCapture`): writes
  `<prefix>-tick<NNNNNN>.png` every N driver ticks without quitting, so pictures line up with `tick`
  records.

`tools/headless-loop.sh --trace` writes `trace.jsonl` and `truth.jsonl` and runs the checker.
`--trace-scenario` puts `tools/observer_trace_standin.py` between Godot and Fusion. The stand-in
answers with a scripted accepted intent, an intent on the occupied plaza, an intent whose target is
not in view, a 429 and a 503, then forwards to Fusion's goal baseline. That baseline walks through a
door, so the run contains every record type. The format is pinned by
`world-engine-godot/fixtures/observer-trace/golden-v1.jsonl`, checked byte for byte by
`ObserverTraceAssertions` in the AgentHarness.

## 9. Versioning

A new record type or a new optional field is a compatible change inside v1 only if readers are
told to ignore unknown `type`s and unknown keys. **Readers must ignore them.** The JSON schema is
closed (`additionalProperties: false`) because it checks what this engine writes, not what a reader
may accept. Renaming or removing
a field, changing a unit, or changing the meaning of `tick` requires `nlt.observer-trace.v2`.
