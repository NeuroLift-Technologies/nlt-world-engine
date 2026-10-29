# Observer trace contract — `nlt.observer-trace.v1`

**Status:** v1, OBS-TRACE-001 (2026-10-29). Promoted from the draft that `vercel/viewer/` was built
against (`vercel/viewer/src/trace/types.ts`). The only changes from the draft are additive.

**Producer:** the Godot World Engine (`world-engine-godot/Observer/Trace/ObserverTrace.cs`), written
by the agent-loop driver while a run is in progress.
**Consumer:** the World Engine Viewer's trace page (`vercel/viewer/trace.html`), a static page that opens the file locally.
**Validator:** `tools/validate_observer_trace.py`.
**Sample:** `fixtures/observer-trace/sample.jsonl`.

## 1. What this is, and what it is not

An observer trace is a **one-way record** of one engine run: where the avatars were, what Fusion
proposed, and what the engine did about it. It exists so a human can replay a run in a browser.

- It is **not an input** to anything. No simulation, Fusion or governance code reads it.
- It is **not the agent loop.** `agent-loop-v1` is the perception → intent → result exchange between
  Godot and Fusion. This trace only reports on that exchange afterwards. Nothing in it can be sent
  back as an intent.
- It is **not the state feed.** `state-feed-v1` is Fusion's semantic projection (needs, burnout,
  gate reports). This trace carries physical state and agent-loop outcomes only.

Fusion owns semantic reality and the World Engine owns physical reality. This file reports on the
physical side.

## 2. Encoding

- UTF-8 [JSON Lines](https://jsonlines.org/): one JSON object per line, `\n` separated.
- **Line 1 is the header** (§3). Every later line is one **record** (§4).
- Records are appended in the order the engine observed them. Ticks are non-decreasing per agent,
  but different record kinds can interleave out of tick order: a `result` arrives after its intent,
  possibly many ticks later.
- The producer flushes after every line, so a run killed mid-way (headless Godot is stopped with
  SIGHUP; see `docs/headless-loop.md`) still leaves a readable file. **Only the final line can be
  truncated.** Consumers must tolerate a truncated last line and report it, not reject the file.
- Consumers **must tolerate unknown keys** on any object and **must surface unknown record types**,
  never drop them silently. They **must reject** a header whose `schemaVersion` is not exactly
  `nlt.observer-trace.v1`.

## 3. Header

| Key | Type | Required | Meaning |
|---|---|---|---|
| `schemaVersion` | string | yes | Exactly `nlt.observer-trace.v1`. |
| `runId` | string | yes | Unique per run, e.g. `run-20261029T140512Z-4f2a`. |
| `engineCommit` | string | yes | Git commit of the engine, from `NLT_ENGINE_COMMIT`, else `unknown`. |
| `godotVersion` | string | yes | Godot version string, e.g. `4.7.2.stable.mono.official`. |
| `startTime` | string | yes | ISO-8601 UTC time the trace was opened. |
| `agentRoster` | string[] | yes | Agent ids the run traces, as sent on the wire (§5). |
| `cadenceHz` | number | yes | How often `tick` records are sampled (§4.1), in records per second of engine time. |
| `tickUnit` | string | no | What one tick is. The Godot producer writes `frame`: one main-loop iteration. |
| `synthetic` | boolean | no | `true` when the file was not recorded from a real engine run. |

## 4. Records

Every record has a `type` (string) naming its kind. The viewer calls this field `kind` internally.
Positions and velocities are `{ "x", "y", "z" }` in metres and metres per second, in Godot's
coordinate frame: `y` is up, so the horizontal plane is `x`/`z`.

### 4.1 `tick` — sampled physical state

```json
{"type":"tick","tick":120,"agentId":"stay_alert_001","scene":{"id":"open_world","kind":"open_world"},
 "position":{"x":1.5,"y":0.9,"z":-3.0},"velocity":{"x":0.8,"y":0,"z":0.1}}
```

Required: `tick`, `agentId`, `scene` (`id`, `kind`), `position`, `velocity`. Sampled at `cadenceHz`,
not written every frame. The scene kind comes from `SceneCatalog`, the same source perception uses.

### 4.2 `perception_sent`

```json
{"type":"perception_sent","tick":120,"agentId":"stay_alert_001","messageId":"obs-120-__local_avatar__-3","visibleEntities":6}
```

Required: `tick`, `agentId`. Optional: `messageId` (the perception's `agent-loop-v1` message id),
`visibleEntities` (how many entities the perception listed). Written only when a request was
actually sent. A perception dropped by the one-in-flight guard or by transport backoff writes nothing.

### 4.3 `intent`

```json
{"type":"intent","messageId":"int-7","agentId":"stay_alert_001","observedTick":120,"verb":"approach",
 "targetId":"plaza","ticksBehind":48,"decisionMs":812}
```

Required: `messageId`, `agentId`, `observedTick`, `verb`. Optional: `targetId`; `ticksBehind` (engine
ticks between the perception and the intent's arrival); `decisionMs` (wall-clock round trip of the
HTTP request). Written for every intent that parsed, including ones that are then refused.

### 4.4 `result`

```json
{"type":"result","intentMessageId":"int-7","agentId":"stay_alert_001","tick":120,"status":"rejected",
 "stage":"governance","governanceCode":"distress","reason":"governance denied (distress): ..."}
```

Required: `intentMessageId`, `status` (`accepted` | `rejected`), `stage`. Optional: `reason`,
`governanceCode`, `agentId`, `tick`. `agentId` and `tick` were added in v1 over the draft. The tick
is the one the intent's perception was taken at.

`stage` says **which layer decided**, in ingress order (`Agents/IntentIngress.cs`):

| `stage` | Meaning |
|---|---|
| `protocol` | `agent-loop-v1` validation refused it: correlation, verb allowlist, target not in perception. |
| `governance` | The ASFDK gate denied it, or the gate itself failed (`gate-unavailable`). |
| `physical` | The live world refused it: stale target, target occupied, doorway refused, avatar gone or mid-transition. |
| `accepted` | Applied. `governanceCode` and `reason` are present when the gate attached a note. |

`governanceCode` is the gate's decision code (`injection`, `crisis`, `distress`,
`gate-unavailable`, …). It is omitted when the gate's code was `clean`.

### 4.5 `decision_failed`

```json
{"type":"decision_failed","agentId":"stay_alert_001","tick":122,"httpStatus":404,"error":"agent is not registered"}
```

Required: `agentId`, `tick`. Optional: `httpStatus`, `error`. Means a decision was asked for and
none was applied before ingress: a non-2xx response, an unparseable intent, a stale-tick intent, or
a transport failure (timeout, refused connection; `httpStatus` absent). The engine still fails
closed in every case. This record only reports it.

### 4.6 `scene_transition`

```json
{"type":"scene_transition","agentId":"stay_alert_001","from":"open_world","to":"personal_1","tick":300}
```

Required: `agentId`, `from`, `to`, `tick`. Written when an agent's scene id changes between two
samples, whatever caused the change.

### 4.7 `scene_entities`

```json
{"type":"scene_entities","scene":"open_world","tick":0,"entities":[
 {"id":"plaza","kind":"place","position":{"x":0,"y":0.4,"z":0},"affordances":["approach","look_at"]}]}
```

Required: `scene`, `entities[]`, each with `id`, `kind`, `position`, `affordances[]`. Optional:
`tick`. These are the task anchors an agent in that scene can perceive, with the verbs perception
lists for each (`AnchorAffordances.For`). Written the first time an agent is seen in a scene, and
again each time it re-enters one.

## 5. Agent ids

`agentId` everywhere is the id **as sent on the wire**: the roster id Fusion registered
(`NLT_AGENT_LOOP_AGENT_ID`, e.g. `stay_alert_001`) for the avatar the loop drives, and the engine's
internal id for any other avatar. This is the same rule as `PerceptionBuilder.WireAgentId`. It means
`intent.agentId` and `tick.agentId` match for the same avatar.

## 6. Privacy and retention

- The trace holds positions, velocities, scene ids, anchor ids, verbs, statuses and engine-authored
  reasons. **It never holds prompts, model output text or Fusion's internal reasoning.**
  `agent-loop-v1` intents carry no free text that is copied here except `reason`, which is engine-
  or gate-authored.
- Tracing is **off by default**. It is enabled per run with `--trace` or `NLT_OBSERVER_TRACE`.
- Files are written locally (`user://traces/` or the path given) and are gitignored. Nothing is
  uploaded. Retention is the operator's: delete the file to delete the trace.
- The viewer opens a trace client-side only. Its CSP is `connect-src 'self'`, and it sends the file
  nowhere.

## 7. Versioning

Additive changes (new optional keys, new record types) stay `v1`, because consumers already
tolerate them. Renaming or removing a key, changing a type or changing a meaning needs
`nlt.observer-trace.v2`. Live transport (streaming these records rather than writing a file) is not
part of v1. See `docs/escalations/2026-10-29-observer-live-transport.md`.
