#!/usr/bin/env python3
"""
LLM Avatar Controller — reference loop for driving a WorldEngine avatar.

Architecture
------------
The LLM is the *brain*, never the *muscle*: it picks high-level semantic
commands (move_to, move_by, move_to_object, stop, release) and the UE side
executes them through AAvatarAIController -> nav path-following ->
CharacterMovementComponent. The avatar's physical locomotion stays with the CMC.

The script is **provider-agnostic** (no LLM provider lock-in guardrail):
it speaks the OpenAI-compatible `POST /v1/chat/completions` HTTP contract and
takes the endpoint + key + model from the environment. It works against a local
Ollama/llama.cpp server, or any hosted OpenAI-compatible API.

Quick start
-----------
    # 1. Run the headless UE sim (web server on :8765) or open the editor.
    # 2. Point this script at any OpenAI-compatible chat-completions endpoint:
    LLM_BASE_URL=http://127.0.0.1:11434/v1 \\
    LLM_API_KEY=        \\
    LLM_MODEL=qwen2.5:7b \\
    python3 llm_avatar_agent.py --task "Walk to the break room and stop."

Notes
-----
- Stdlib only (`urllib`) so there are no new runtime dependencies.
- Every action is appended to llm_avatar_session.jsonl — an action log that
  can feed the deterministic replay stream later.
"""

from __future__ import annotations

import argparse
import json
import os
import socket
import sys
import time
import urllib.request
from typing import Any, Optional

# --------------------------------------------------------------------------- #
# Configuration (env-driven, provider-agnostic)
# --------------------------------------------------------------------------- #

WE_BASE = os.environ.get("WE_BASE", "http://127.0.0.1:8765").rstrip("/")
LLM_BASE_URL = os.environ.get("LLM_BASE_URL", "http://127.0.0.1:11434/v1").rstrip("/")
LLM_API_KEY = os.environ.get("LLM_API_KEY", "")
LLM_MODEL = os.environ.get("LLM_MODEL", "qwen2.5:7b")
LLM_MAX_TURNS = int(os.environ.get("LLM_MAX_TURNS", "20"))
AVATAR_ID = os.environ.get("AVATAR_ID", "")
ARRIVE_TOLERANCE = float(os.environ.get("ARRIVE_TOLERANCE", "20.0"))
ARRIVE_TIMEOUT = float(os.environ.get("ARRIVE_TIMEOUT", "30.0"))

SESSION_LOG = os.environ.get("SESSION_LOG", "llm_avatar_session.jsonl")


# --------------------------------------------------------------------------- #
# WorldEngine HTTP client
# --------------------------------------------------------------------------- #

def _http(method: str, path: str, body: Optional[dict] = None) -> dict:
    """Minimal HTTP/1.1 client for the UE web server.

    Older WorldEngine builds served some endpoints (status/scene/snapshot/CORS)
    with `HTTP/1.1 0` because their responses never set the HTTP status code;
    strict clients (curl, http.client, requests) reject that. Fixed builds emit
    `HTTP/1.1 200`. This client still treats a status code of 0 as success (200)
    so it works against both old and new hosts.
    """
    base = WE_BASE[len("http://"):]
    host, _, port_str = base.partition(":")
    port = int(port_str or 80)

    payload = json.dumps(body).encode("utf-8") if body is not None else None
    headers = [
        f"{method} {path} HTTP/1.1",
        f"Host: {host}",
        "Connection: close",
        "Accept: application/json",
    ]
    if payload is not None:
        headers.append("Content-Type: application/json")
        headers.append(f"Content-Length: {len(payload)}")

    request = ("\r\n".join(headers) + "\r\n\r\n").encode("utf-8") + (payload or b"")
    try:
        with socket.create_connection((host, port), timeout=10) as sock:
            sock.sendall(request)
            raw = b""
            while True:
                chunk = sock.recv(65536)
                if not chunk:
                    break
                raw += chunk
    except OSError as exc:
        return {"ok": False, "error": f"unreachable: {exc}"}

    head, _, body_bytes = raw.partition(b"\r\n\r\n")
    status_line = head.split(b"\r\n", 1)[0].decode("iso-8859-1", "replace")
    code = 0
    parts = status_line.split(" ", 2)
    if len(parts) >= 2:
        try:
            code = int(parts[1])
        except ValueError:
            code = 0

    if code not in (200, 0):
        return {"ok": False, "error": f"HTTP {code}: {body_bytes.decode('utf-8', 'replace')}"}
    if not body_bytes:
        return {"ok": True}
    try:
        return json.loads(body_bytes.decode("utf-8"))
    except json.JSONDecodeError:
        return {"ok": False, "error": f"non-JSON body: {body_bytes.decode('utf-8', 'replace')[:200]}"}


def get_status() -> dict:
    return _http("GET", "/api/status")


def get_snapshot() -> dict:
    return _http("GET", "/api/snapshot")


def send_command(command: str, args: Optional[dict] = None) -> dict:
    payload: dict = {"command": command, "args": args or {}}
    if AVATAR_ID:
        payload["avatar_id"] = AVATAR_ID
    return _http("POST", "/api/avatar/command", payload)


def compact_observation(snapshot: dict) -> str:
    """Shrink a full snapshot JSON into the LLM-visible observation."""
    sim = snapshot.get("simulation", {})
    lines = [f"simulation tick={sim.get('tick')} state={sim.get('state')} pace={sim.get('pace')}"]

    avatars = snapshot.get("avatars", {})
    for aid, av in avatars.items():
        pos = av.get("position", {})
        metrics = av.get("metrics", {})
        lines.append(
            f"avatar id={aid} pos=({pos.get('x', 0.0):.1f}, {pos.get('y', 0.0):.1f}) "
            f"moving_to=({pos.get('target_x', 0.0):.1f}, {pos.get('target_y', 0.0):.1f}) "
            f"focus={metrics.get('focus', 0.0):.2f} stress={metrics.get('stress', 0.0):.2f} "
            f"cognitive_load={metrics.get('cognitive_load', 0.0):.2f}"
        )
    if not avatars:
        lines.append("(no avatar actors found in snapshot)")
    return "\n".join(lines)


def avatar_position(snapshot: dict) -> Optional[tuple[float, float, float]]:
    avatars = snapshot.get("avatars", {})
    if not avatars:
        return None
    aid = AVATAR_ID or next(iter(avatars))
    pos = avatars[aid].get("position", {})
    return (float(pos.get("x", 0.0)), float(pos.get("y", 0.0)), float(pos.get("z", 0.0) or 0.0))


def wait_for_arrival(target_xy: Optional[tuple[float, float]]) -> str:
    """Poll the snapshot until the avatar reaches the destination."""
    if target_xy is None:
        return "no destination to wait for"
    deadline = time.monotonic() + ARRIVE_TIMEOUT
    dist = float("inf")
    while time.monotonic() < deadline:
        snap = get_snapshot()
        pos = avatar_position(snap)
        if pos is None:
            time.sleep(0.5)
            continue
        dist = ((pos[0] - target_xy[0]) ** 2 + (pos[1] - target_xy[1]) ** 2) ** 0.5
        if dist <= ARRIVE_TOLERANCE:
            return f"arrived at ({target_xy[0]:.1f}, {target_xy[1]:.1f}) (dist={dist:.1f})"
        time.sleep(0.5)
    return f"arrival wait timed out (last dist={dist:.1f})"


# --------------------------------------------------------------------------- #
# Tool definitions (OpenAI-style function calling)
# --------------------------------------------------------------------------- #

TOOLS: list[dict[str, Any]] = [
    {
        "type": "function",
        "function": {
            "name": "get_snapshot",
            "description": "Get the current compact world observation (avatar positions, cognitive metrics, sim tick).",
            "parameters": {"type": "object", "properties": {}, "required": []},
        },
    },
    {
        "type": "function",
        "function": {
            "name": "move_to",
            "description": "Navigate the avatar to an absolute world-space waypoint (nav-mesh path following).",
            "parameters": {
                "type": "object",
                "properties": {"x": {"type": "number"}, "y": {"type": "number"}},
                "required": ["x", "y"],
            },
        },
    },
    {
        "type": "function",
        "function": {
            "name": "move_by",
            "description": "Navigate the avatar a relative offset from its current position (clamped to 2000 units/command).",
            "parameters": {
                "type": "object",
                "properties": {"dx": {"type": "number"}, "dy": {"type": "number"}},
                "required": ["dx", "dy"],
            },
        },
    },
    {
        "type": "function",
        "function": {
            "name": "move_to_object",
            "description": "Navigate the avatar to the actor whose name equals object_id (discover ids via get_snapshot).",
            "parameters": {
                "type": "object",
                "properties": {"object_id": {"type": "string"}},
                "required": ["object_id"],
            },
        },
    },
    {
        "type": "function",
        "function": {
            "name": "face_towards",
            "description": "Rotate the avatar to face an absolute world-space point without moving.",
            "parameters": {
                "type": "object",
                "properties": {"x": {"type": "number"}, "y": {"type": "number"}},
                "required": ["x", "y"],
            },
        },
    },
    {
        "type": "function",
        "function": {
            "name": "stop",
            "description": "Stop all movement immediately (LLM control is retained).",
            "parameters": {"type": "object", "properties": {}, "required": []},
        },
    },
    {
        "type": "function",
        "function": {
            "name": "release",
            "description": "Stop and hand control back to the autonomous wander AI.",
            "parameters": {"type": "object", "properties": {}, "required": []},
        },
    },
]


def execute_tool(name: str, args: dict) -> dict:
    """Execute a tool call against the WorldEngine API; returns a result dict."""
    if name == "get_snapshot":
        snap = get_snapshot()
        if not snap.get("ok", True):
            return snap
        return {"ok": True, "observation": compact_observation(snap)}

    if name == "move_to":
        res = send_command("move_to", {"x": float(args["x"]), "y": float(args["y"])})
        if res.get("ok"):
            res["arrival"] = wait_for_arrival((float(args["x"]), float(args["y"])))
        return res

    if name == "move_by":
        res = send_command("move_by", {"dx": float(args.get("dx", 0.0)), "dy": float(args.get("dy", 0.0))})
        if res.get("ok"):
            snap = get_snapshot()
            pos = avatar_position(snap)
            if pos:
                res["arrival"] = wait_for_arrival((pos[0], pos[1]))
        return res

    if name == "move_to_object":
        return send_command("move_to_object", {"object_id": args["object_id"]})

    if name == "face_towards":
        return send_command("face_towards", {"x": float(args["x"]), "y": float(args["y"])})

    if name in ("stop", "release"):
        return send_command(name)

    return {"ok": False, "error": f"unknown tool: {name}"}


# --------------------------------------------------------------------------- #
# LLM client (OpenAI-compatible)
# --------------------------------------------------------------------------- #

def chat(messages: list[dict], tools: list[dict]) -> dict:
    payload = {"model": LLM_MODEL, "messages": messages, "tools": tools, "tool_choice": "auto"}
    headers = {"Content-Type": "application/json"}
    if LLM_API_KEY:
        headers["Authorization"] = f"Bearer {LLM_API_KEY}"
    req = urllib.request.Request(
        f"{LLM_BASE_URL}/chat/completions",
        data=json.dumps(payload).encode("utf-8"),
        method="POST",
        headers=headers,
    )
    with urllib.request.urlopen(req, timeout=120) as resp:
        return json.loads(resp.read().decode("utf-8"))


# --------------------------------------------------------------------------- #
# Main loop
# --------------------------------------------------------------------------- #

def log_action(entry: dict) -> None:
    with open(SESSION_LOG, "a", encoding="utf-8") as fh:
        fh.write(json.dumps(entry, ensure_ascii=False) + "\n")


def run_agent(task: str, dry_run: bool = False) -> int:
    if dry_run:
        print("== dry-run: validating sim endpoints (no LLM calls) ==")
        status = get_status()
        print("status:", json.dumps(status, indent=2))
        snap = get_snapshot()
        print("observation:\n" + compact_observation(snap))
        print("dry-run: ok")
        return 0

    # Warm-up: verify sim is reachable before paying for LLM tokens.
    status = get_status()
    if status.get("ok") is False or "running" not in status:
        print(f"WorldEngine unreachable at {WE_BASE}: {status}", file=sys.stderr)
        return 2
    print(f"connected: {WE_BASE} (sim running={status.get('running')})")

    messages: list[dict] = [
        {
            "role": "system",
            "content": (
                "You control an avatar inside the NeuroLift WorldEngine simulation. "
                "You are its brain: you pick high-level commands and a UE AIController "
                "handles the walking. Choose actions from the provided tools to complete "
                "the user's goal. Prefer get_snapshot periodically to observe your position. "
                "When the goal is complete, use stop or release and explain what you did."
            ),
        },
        {
            "role": "user",
            "content": (
                f"Goal: {task}\n\n"
                "World coordinates are UE world units. Move in small steps; call "
                "get_snapshot between movements to confirm progress."
            ),
        },
    ]

    for turn in range(1, LLM_MAX_TURNS + 1):
        try:
            response = chat(messages, TOOLS)
        except Exception as exc:  # noqa: BLE001 - provider errors surface cleanly
            print(f"LLM call failed: {exc}", file=sys.stderr)
            return 3

        choice = response["choices"][0]
        message = choice.get("message", {})

        # Record the model's turn for the replay/action log.
        log_action({"turn": turn, "role": "assistant", "message": message})

        if not message.get("tool_calls"):
            print(f"[turn {turn}] LLM finished without a tool call.")
            print(json.dumps(message, indent=2))
            return 0

        for tool_call in message["tool_calls"]:
            name = tool_call["function"]["name"]
            try:
                args = json.loads(tool_call["function"]["arguments"] or "{}")
            except json.JSONDecodeError:
                args = {}
            print(f"[turn {turn}] tool: {name}({json.dumps(args)})")
            result = execute_tool(name, args)
            print(f"[turn {turn}] result: {json.dumps(result, ensure_ascii=False)[:400]}")
            log_action({"turn": turn, "tool": name, "args": args, "result": result})
            messages.append({"role": "tool", "tool_call_id": tool_call["id"], "content": json.dumps(result)})

        # Keep the assistant message (with tool_calls) in the history.
        messages.append(
            {
                "role": "assistant",
                "content": message.get("content"),
                "tool_calls": message.get("tool_calls"),
            }
        )

    print("max turns reached; ending session.", file=sys.stderr)
    return 1


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--task",
        default="Explore the environment using the available tools.",
        help="Natural-language goal for the LLM.",
    )
    parser.add_argument("--dry-run", action="store_true", help="Validate sim endpoints without calling an LLM.")
    args = parser.parse_args()
    return run_agent(args.task, dry_run=args.dry_run)


if __name__ == "__main__":
    sys.exit(main())
