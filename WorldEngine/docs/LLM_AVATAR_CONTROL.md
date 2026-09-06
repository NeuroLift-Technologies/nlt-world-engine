# LLM → Avatar Control (via AAvatarAIController)

**Status:** Implemented (branch `feat/llm-avatar-control`) — build-verified, pending live test after editor restart.
**Date:** 2026-09-05 · **Agent:** Cline
**Governed by:** ORG-DEV-OTOI-1.0.3

---

## 1. Design principle

> The LLM is the brain, never the muscle.

The LLM emits **high-level semantic commands**; `AAvatarAIController` executes
them via nav path-following (`MoveToLocation` / `MoveToActor`); the
`UCharacterMovementComponent` underneath keeps ownership of the avatar's actual
physics (walking, turning, friction, step-up). No raw velocity/teleport writes
enter the movement pipeline from the LLM path.

The LLM control mode is deliberately parallel to the existing Learning Agents
mode: `bLLMControlActive` pauses autonomous wandering on attach and resumes it
on `release`, exactly like `SetLearningAgentsActive`.

## 2. Endpoint

`POST http://127.0.0.1:8765/api/avatar/command` (loopback-only, same guard as
`/api/avatar/action` and `/api/control`).

```json
{
  "avatar_id": "Agent_0",   // optional — defaults to the first avatar actor
  "command":  "move_to",
  "args":     { "x": 1200.0, "y": -3400.0 }
}
```

### Commands

| command          | args                          | effect                                                            |
|------------------|-------------------------------|-------------------------------------------------------------------|
| `move_to`        | `x`, `y` (world units)        | Nav-move to an absolute waypoint (`MoveToLocation`), takes LLM control |
| `move_by`        | `dx`, `dy` (±2000 max each)   | Nav-move a relative offset from the current position              |
| `move_to_object` | `object_id`                   | Nav-move to the first actor whose name matches `object_id`        |
| `face_towards`   | `x`, `y`                      | Rotate (control rotation + focal point) to face a world point     |
| `stop`           | —                             | `StopMovement()`, LLM control retained                            |
| `release`        | —                             | Stop + hand control back to autonomous wander AI                   |

### Response

```json
{ "ok": true, "command": "move_to", "message": "moving to (1200.00, -3400.00)",
  "avatar_id": "Agent_0", "llm_control": true }
```

Errors return `{ "ok": false, "error": "..." }` with reasons such as
`avatar not found`, `only localhost allowed`, or per-command validation failures.

## 3. Code map

| File | Change |
|------|--------|
| `Source/WorldEngine/Public/Agents/AvatarAIController.h` | `bLLMControlActive`, `SetLLMControlActive`, `IsLLMControlActive`, `ExecuteLLMCommand` |
| `Source/WorldEngine/Private/Agents/AvatarAIController.cpp` | Command dispatcher + wander/on-move LLM guards |
| `Source/WorldEngine/Public/NLTWebServerSubsystem.h` | `HandleAvatarCommandRequest` |
| `Source/WorldEngine/Private/NLTWebServerSubsystem.cpp` | `/api/avatar/command` route + handler |
| `Source/WorldEngine/Scripts/llm_avatar_agent.py` | Reference provider-agnostic LLM controller loop |

## 4. Reference controller loop

`WorldEngine/Scripts/llm_avatar_agent.py` is a stdlib-only, OpenAI-compatible
tool-calling client. Configure via environment — **no provider is hardcoded**
(guardrail: no LLM provider lock-in):

| env | default | purpose |
|-----|---------|---------|
| `WE_BASE` | `http://127.0.0.1:8765` | WorldEngine web server |
| `LLM_BASE_URL` | `http://127.0.0.1:11434/v1` | OpenAI-compatible chat completions endpoint |
| `LLM_API_KEY` | *(empty)* | Bearer token when required |
| `LLM_MODEL` | `qwen2.5:7b` | Model id |
| `LLM_MAX_TURNS` | `20` | Hard cap per session |
| `AVATAR_ID` | *(empty)* | Optional avatar id pin |
| `ARRIVE_TOLERANCE` / `ARRIVE_TIMEOUT` | `20.0` / `30.0` | Arrival polling |

```bash
# Validate against a running sim without spending tokens:
python3 WorldEngine/Scripts/llm_avatar_agent.py --dry-run

# Run a goal with a local Ollama-compatible endpoint:
LLM_MODEL=qwen2.5:7b \
python3 WorldEngine/Scripts/llm_avatar_agent.py --task "Walk to the center of the room and stop."
```

Tools exposed to the LLM: `get_snapshot`, `move_to`, `move_by`,
`move_to_object`, `face_towards`, `stop`, `release`.
Every assistant/tool turn is appended to `llm_avatar_session.jsonl` (JSONL
action log — a basis for the deterministic replay stream later).

## 5. Known caveats

- UE's `FHttpServer` responds with a non-standard `HTTP/1.1 0` status line for
  responses created via `FHttpServerResponse::Create`. Strict HTTP clients
  (curl, Python `http.client`) reject it; this script tolerates it. The web
  viewer and the other UE endpoints share this behavior — do not "fix" the
  client side by assuming success codes; treat code `0` as 200.
- The live editor must be restarted after rebuilding to register the new route.
- `move_to_object` matches actors by `GetName()`; the snapshot exposes avatar
  ids such as `Agent_0`, not arbitrary object ids yet.
- Loopback-only: the endpoint is intentionally not reachable from other hosts
  until token-based auth lands (see gap analysis in `fusion-unreal-domain-mapping.md`).