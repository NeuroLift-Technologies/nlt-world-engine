#!/usr/bin/env python3
"""Scripted Fusion stand-in for the observer-trace record-type scenario (docs/contracts/observer-trace-v1.md §7).

Listens where Godot posts perceptions and answers the first few with a fixed script, so one run
exercises every record type:

  1. ``approach plaza``           accepted                      -> intent + result (stage accepted)
  2. ``use <occupied anchor>``    rejected by the re-check       -> intent + result (stage physical)
  3. an intent naming a target the perception did not list
                                 refused before ingress         -> decision_failed (invalid_intent)
  4. HTTP 429                                                   -> decision_failed (httpStatus 429)
  5. HTTP 503                                                   -> decision_failed (httpStatus 503)

then forwards every later perception unchanged to a real Fusion endpoint (``--forward``, the F4
goal baseline), whose answers walk the avatar through a door: a scene_transition.

Step 2 needs the anchor full: run Godot with ``-- --trace-occupy <anchor>`` (TraceOccupant). The
stand-in waits until a perception lists that anchor as occupied before playing step 2.

Usage:
    python3 tools/observer_trace_standin.py --port 8002 --forward http://127.0.0.1:8001/agent-loop/perception \
        --occupied plaza --log standin.jsonl
"""

from __future__ import annotations

import argparse
import json
import signal
import sys
import threading
import urllib.error
import urllib.request
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from typing import Any


class Script:
    def __init__(self, occupied: str, forward: str, log_path: str | None) -> None:
        self.occupied = occupied
        self.forward = forward
        self.step = 0
        self.lock = threading.Lock()
        self.log = open(log_path, "a", encoding="utf-8") if log_path else None

    def record(self, entry: dict[str, Any]) -> None:
        if self.log:
            self.log.write(json.dumps(entry) + "\n")
            self.log.flush()

    def answer(self, perception: dict[str, Any], body: bytes) -> tuple[int, dict[str, Any]]:
        def intent(verb: str, target: str | None) -> dict[str, Any]:
            out = {
                "protocolVersion": "nlt.agent-loop.v1",
                "messageType": "intent",
                "messageId": f"intent-{perception['tick']}-standin-{self.step}",
                "agentId": perception["agentId"],
                "observedTick": perception["tick"],
                "verb": verb,
            }
            if target is not None:
                out["targetId"] = target
            return out

        visible = {e["id"]: e for e in perception.get("visibleEntities", [])}
        with self.lock:
            step = self.step
            if step == 0 and "plaza" in visible:
                self.step += 1
                return 200, intent("approach", "plaza")
            if step == 1:
                held = visible.get(self.occupied)
                if not (held and held.get("occupied")):
                    return 200, intent("wait", None)  # not yet full, or out of view: hold still
                verb = next((v for v in ("use", "sit", "rest") if v in held["affordances"]), "use")
                self.step += 1
                return 200, intent(verb, self.occupied)
            if step == 2:
                self.step += 1
                return 200, intent("approach", "standin_not_in_view")
            if step == 3:
                self.step += 1
                return 429, {"error": "decision already in flight (scripted)"}
            if step == 4:
                self.step += 1
                return 503, {"error": "model quarantined (scripted)"}
        request = urllib.request.Request(self.forward, data=body, headers={"content-type": "application/json"})
        try:
            with urllib.request.urlopen(request, timeout=20) as response:
                return response.status, json.loads(response.read())
        except urllib.error.HTTPError as error:
            return error.code, {"error": error.read().decode("utf-8", "replace")}
        except (urllib.error.URLError, TimeoutError) as error:
            return 502, {"error": f"forward failed: {error}"}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--port", type=int, default=8002)
    parser.add_argument("--forward", required=True)
    parser.add_argument("--occupied", default="plaza")
    parser.add_argument("--log")
    args = parser.parse_args()
    script = Script(args.occupied, args.forward, args.log)

    class Handler(BaseHTTPRequestHandler):
        def do_POST(self) -> None:  # noqa: N802 (http.server naming)
            body = self.rfile.read(int(self.headers.get("content-length", "0")))
            try:
                perception = json.loads(body)
                status, answer = script.answer(perception, body)
            except (json.JSONDecodeError, KeyError) as error:
                status, answer, perception = 422, {"error": str(error)}, {}
            payload = json.dumps(answer).encode()
            script.record({"tick": perception.get("tick"), "status": status, "answer": answer})
            self.send_response(status)
            self.send_header("content-type", "application/json")
            self.send_header("content-length", str(len(payload)))
            self.end_headers()
            self.wfile.write(payload)

        def log_message(self, format: str, *args: Any) -> None:  # noqa: A002 (base signature)
            return

    # A background job of a non-interactive shell starts with SIGINT ignored, and Python keeps that;
    # restore the default so the PID-file stop in tools/headless-loop.sh (SIGINT) works.
    signal.signal(signal.SIGINT, signal.default_int_handler)
    signal.signal(signal.SIGTERM, signal.default_int_handler)
    server = ThreadingHTTPServer(("127.0.0.1", args.port), Handler)
    print(f"stand-in on 127.0.0.1:{args.port}, forwarding to {args.forward}", flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    return 0


if __name__ == "__main__":
    sys.exit(main())
