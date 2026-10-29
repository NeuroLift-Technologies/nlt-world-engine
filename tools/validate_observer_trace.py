#!/usr/bin/env python3
"""Validate a nlt.observer-trace.v1 JSONL file (docs/contracts/observer-trace-v1.md).

Usage:
    python3 tools/validate_observer_trace.py fixtures/observer-trace/sample.jsonl
    python3 tools/validate_observer_trace.py --summary run/observer-trace.jsonl   # also print counts

Fails on: a header that is missing, unparseable, or not exactly nlt.observer-trace.v1; a missing
required key; a per-agent tick going backwards; a result naming an intent never written; a bad
stage or status. Warns on: unknown record types (consumers must surface them, so they are legal) and
a truncated final line (headless Godot is stopped with SIGHUP, which can cut the last write).
Unknown keys are ignored: the format is open to additive change.
"""

from __future__ import annotations

import argparse
import json
import sys
from collections import Counter
from pathlib import Path
from typing import Any

SCHEMA_VERSION = "nlt.observer-trace.v1"

HEADER_REQUIRED = (
    "schemaVersion",
    "runId",
    "engineCommit",
    "godotVersion",
    "startTime",
    "agentRoster",
    "cadenceHz",
)

RECORD_REQUIRED: dict[str, tuple[str, ...]] = {
    "tick": ("tick", "agentId", "scene", "position", "velocity"),
    "perception_sent": ("tick", "agentId"),
    "intent": ("messageId", "agentId", "observedTick", "verb"),
    "result": ("intentMessageId", "status", "stage"),
    "decision_failed": ("agentId", "tick"),
    "scene_transition": ("agentId", "from", "to", "tick"),
    "scene_entities": ("scene", "entities"),
}

STAGES = {"protocol", "governance", "physical", "accepted"}
STATUSES = {"accepted", "rejected"}
VECTOR_KEYS = ("x", "y", "z")


def is_number(value: Any) -> bool:
    return isinstance(value, (int, float)) and not isinstance(value, bool)


def check_vector(value: Any, where: str, errors: list[str]) -> None:
    if not isinstance(value, dict) or not all(is_number(value.get(k)) for k in VECTOR_KEYS):
        errors.append(f"{where}: must be an object with numeric x, y, z")


def validate(lines: list[str]) -> tuple[list[str], list[str], Counter[str]]:
    errors: list[str] = []
    warnings: list[str] = []
    counts: Counter[str] = Counter()

    # A file ending without a newline after a cut write leaves a last line that does not parse.
    while lines and lines[-1].strip() == "":
        lines.pop()
    if not lines:
        return ["trace is empty: line 1 must be the header"], warnings, counts

    try:
        header = json.loads(lines[0])
    except json.JSONDecodeError as e:
        return [f"line 1: header is not valid JSON ({e.msg})"], warnings, counts
    if not isinstance(header, dict):
        return ["line 1: header must be a JSON object"], warnings, counts
    for key in HEADER_REQUIRED:
        if key not in header:
            errors.append(f"line 1: header is missing required key '{key}'")
    if header.get("schemaVersion") != SCHEMA_VERSION:
        errors.append(
            f"line 1: schemaVersion is {header.get('schemaVersion')!r}, expected {SCHEMA_VERSION!r}"
        )
    if "agentRoster" in header and not (
        isinstance(header["agentRoster"], list)
        and all(isinstance(a, str) for a in header["agentRoster"])
    ):
        errors.append("line 1: agentRoster must be a list of strings")
    if "cadenceHz" in header and not is_number(header["cadenceHz"]):
        errors.append("line 1: cadenceHz must be a number")

    intents: set[str] = set()
    last_tick: dict[tuple[str, str], int] = {}

    for index, line in enumerate(lines[1:], start=2):
        if line.strip() == "":
            continue
        try:
            record = json.loads(line)
        except json.JSONDecodeError as e:
            if index == len(lines):
                warnings.append(f"line {index}: final line is truncated ({e.msg}); ignored")
                continue
            errors.append(f"line {index}: not valid JSON ({e.msg})")
            continue
        if not isinstance(record, dict):
            errors.append(f"line {index}: record must be a JSON object")
            continue

        kind = record.get("type")
        counts[str(kind)] += 1
        if kind not in RECORD_REQUIRED:
            warnings.append(f"line {index}: unknown record type {kind!r} (must be surfaced, not dropped)")
            continue
        missing = [k for k in RECORD_REQUIRED[kind] if k not in record]
        if missing:
            errors.append(f"line {index}: {kind} is missing required key(s) {', '.join(missing)}")
            continue

        where = f"line {index} ({kind})"
        if kind == "tick":
            scene = record["scene"]
            if not isinstance(scene, dict) or not isinstance(scene.get("id"), str) or not isinstance(scene.get("kind"), str):
                errors.append(f"{where}: scene must have string id and kind")
            check_vector(record["position"], f"{where}.position", errors)
            check_vector(record["velocity"], f"{where}.velocity", errors)
        if kind in ("tick", "perception_sent", "decision_failed", "scene_transition"):
            tick = record["tick"]
            if not isinstance(tick, int) or isinstance(tick, bool):
                errors.append(f"{where}: tick must be an integer")
            else:
                key = (kind, str(record["agentId"]))
                if tick < last_tick.get(key, tick):
                    errors.append(f"{where}: tick {tick} goes backwards for {record['agentId']}")
                last_tick[key] = tick
        if kind == "intent":
            intents.add(str(record["messageId"]))
        if kind == "result":
            if record["intentMessageId"] not in intents:
                errors.append(f"{where}: intentMessageId {record['intentMessageId']!r} has no earlier intent")
            if record["stage"] not in STAGES:
                errors.append(f"{where}: stage {record['stage']!r} is not one of {sorted(STAGES)}")
            if record["status"] not in STATUSES:
                errors.append(f"{where}: status {record['status']!r} is not one of {sorted(STATUSES)}")
            if (record["status"] == "accepted") != (record["stage"] == "accepted"):
                errors.append(f"{where}: status {record['status']!r} contradicts stage {record['stage']!r}")
        if kind == "scene_entities":
            entities = record["entities"]
            if not isinstance(entities, list):
                errors.append(f"{where}: entities must be a list")
                continue
            for n, entity in enumerate(entities):
                if not isinstance(entity, dict) or not all(k in entity for k in ("id", "kind", "position", "affordances")):
                    errors.append(f"{where}: entities[{n}] needs id, kind, position, affordances")
                    continue
                check_vector(entity["position"], f"{where}.entities[{n}].position", errors)

    return errors, warnings, counts


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("path", type=Path)
    parser.add_argument("--summary", action="store_true", help="print record counts by type")
    args = parser.parse_args()

    try:
        text = args.path.read_text(encoding="utf-8")
    except OSError as e:
        print(f"FAIL {args.path}: {e}", file=sys.stderr)
        return 1

    errors, warnings, counts = validate(text.split("\n"))
    for w in warnings:
        print(f"WARN {w}")
    for e in errors:
        print(f"FAIL {e}")
    if args.summary or not errors:
        total = sum(counts.values())
        detail = ", ".join(f"{k}={v}" for k, v in sorted(counts.items()))
        print(f"records: {total} ({detail})" if total else "records: 0")
    if errors:
        print(f"FAIL {args.path}: {len(errors)} error(s)")
        return 1
    print(f"PASS {args.path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
