#!/usr/bin/env python3
"""Check an nlt.observer-trace.v1 file (docs/contracts/observer-trace-v1.md).

Usage:
    python3 tools/check_observer_trace.py trace.jsonl
    python3 tools/check_observer_trace.py trace.jsonl --truth truth.jsonl
    python3 tools/check_observer_trace.py trace.jsonl --expect tick,intent,result,decision_failed
    python3 tools/check_observer_trace.py trace.jsonl --json summary.json

Checks every line against docs/contracts/observer-trace-v1.schema.json (needs `jsonschema`) and the
file-level rules the schema cannot express: the header is line 1 and only line 1, a truncated record
is last if present, tick records never go back in time per agent, every agent in a record is on the
header roster, every result answers an intent recorded before it, a scene_entities record precedes an
agent's first tick record and follows each of its scene transitions, and ticksBehind (when present)
is atTick - observedTick.

With --truth (written by the engine's --trace-truth sampler), every tick record is compared with the
position, velocity and scene the sampler read from the scene tree at the same tick, as 32-bit floats,
exactly. Prints record counts by type, file size, and every mismatch. Exits 1 on any problem.
"""

from __future__ import annotations

import argparse
import json
import struct
import sys
from collections import Counter
from pathlib import Path
from typing import Any

SCHEMA = Path(__file__).resolve().parent.parent / "docs" / "contracts" / "observer-trace-v1.schema.json"


def f32(value: float | None) -> float | None:
    """The value as the engine's 32-bit float, so formatting differences cannot hide or fake a mismatch."""
    return None if value is None else struct.unpack("f", struct.pack("f", value))[0]


def load_validator() -> Any:
    try:
        import jsonschema  # type: ignore[import-not-found]
    except ImportError:
        print("note: jsonschema not installed; schema checks skipped, file-level checks still run")
        return None
    schema = json.loads(SCHEMA.read_text(encoding="utf-8"))
    return jsonschema.Draft202012Validator(schema)


def check_trace(path: Path) -> tuple[list[dict[str, Any]], list[str]]:
    problems: list[str] = []
    validator = load_validator()
    records: list[dict[str, Any]] = []
    with path.open(encoding="utf-8") as handle:
        for number, line in enumerate(handle, start=1):
            if not line.endswith("\n"):
                # Contract §2: a run killed mid-write can leave one partial last line; readers drop it.
                print(f"note: line {number} has no newline (cut off by a kill); ignored")
                break
            try:
                record = json.loads(line)
            except json.JSONDecodeError as error:
                problems.append(f"line {number}: not JSON: {error}")
                continue
            if validator is not None:
                for error in validator.iter_errors(record):
                    problems.append(f"line {number}: {error.message}")
            record["_line"] = number
            records.append(record)
    if not records:
        return records, ["empty trace"]

    if records[0].get("type") != "header":
        problems.append("line 1 is not the header")
    roster = {a["agentId"] for a in records[0].get("agents", [])} if records[0].get("type") == "header" else set()
    last_tick: dict[str, int] = {}
    intents: set[str] = set()
    entered: dict[str, str] = {}  # agent -> scene of its latest scene_entities record
    awaiting_entities: dict[str, str] = {}  # agent -> scene a transition entered, not yet listed
    for record in records[1:]:
        kind = record.get("type")
        where = f"line {record['_line']}"
        if kind == "header":
            problems.append(f"{where}: a second header")
        if kind == "truncated" and record is not records[-1]:
            problems.append(f"{where}: records follow the truncated record")
        agent = record.get("agentId")
        if agent is not None and agent not in roster:
            problems.append(f"{where}: agent '{agent}' is not on the header roster")
        if kind == "tick":
            previous = last_tick.get(agent, -1)
            if record["tick"] <= previous:
                problems.append(f"{where}: tick {record['tick']} does not advance past {previous} for {agent}")
            last_tick[agent] = record["tick"]
        if kind == "scene_entities":
            entered[agent] = record["sceneId"]
            awaiting_entities.pop(agent, None)
        if kind == "scene_transition":
            awaiting_entities[agent] = record["to"]
        if kind == "tick" and agent not in entered:
            problems.append(f"{where}: tick record before any scene_entities for {agent}")
        if kind == "intent":
            intents.add(record["messageId"])
            if "ticksBehind" in record and record["ticksBehind"] != record["atTick"] - record["observedTick"]:
                problems.append(f"{where}: ticksBehind is not atTick - observedTick")
        if kind == "result" and record["intentMessageId"] not in intents and record.get("stage") != "protocol":
            problems.append(f"{where}: result for '{record['intentMessageId']}' has no intent before it")
    truncated = records[-1].get("type") == "truncated"
    for agent, scene in awaiting_entities.items():
        if not truncated:
            problems.append(f"{agent} entered {scene} but no scene_entities record followed")
    return records, problems


def check_truth(records: list[dict[str, Any]], truth_path: Path) -> tuple[int, list[str]]:
    """Compare tick records with the scene-tree sampler; returns (ticks compared, mismatches)."""
    header = records[0]
    engine_for = {a["agentId"]: a["engineId"] for a in header.get("agents", [])}
    truth: dict[tuple[int, str], dict[str, Any]] = {}
    with truth_path.open(encoding="utf-8") as handle:
        for line in handle:
            if line.strip():
                sample = json.loads(line)
                truth[(sample["tick"], sample["engineId"])] = sample
    mismatches: list[str] = []
    compared = 0
    for record in records:
        if record.get("type") != "tick":
            continue
        key = (record["tick"], engine_for.get(record["agentId"], record["agentId"]))
        sample = truth.get(key)
        where = f"tick {record['tick']} {record['agentId']}"
        if sample is None:
            mismatches.append(f"{where}: no scene-tree sample at this tick")
            continue
        compared += 1
        for field in ("position", "velocity"):
            traced = [f32(record[field][axis]) for axis in ("x", "y", "z")]
            engine = [f32(v) for v in sample[field]]
            if traced != engine:
                mismatches.append(f"{where}: {field} trace {traced} != scene tree {engine}")
        if record["scene"]["id"] != sample["sceneId"]:
            mismatches.append(f"{where}: scene trace {record['scene']['id']} != engine {sample['sceneId']}")
    return compared, mismatches


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("trace", type=Path)
    parser.add_argument("--truth", type=Path, help="scene-tree samples from --trace-truth")
    parser.add_argument("--expect", default="", help="comma-separated record types that must be present")
    parser.add_argument("--json", type=Path, help="write the summary here as JSON")
    args = parser.parse_args()

    records, problems = check_trace(args.trace)
    counts = Counter(r.get("type") for r in records)
    size = args.trace.stat().st_size
    print(f"trace: {args.trace} ({size} bytes, {len(records)} records)")
    for kind, count in sorted(counts.items()):
        print(f"  {kind:17} {count}")
    for kind in filter(None, args.expect.split(",")):
        if counts.get(kind, 0) == 0:
            problems.append(f"expected at least one '{kind}' record")

    summary: dict[str, Any] = {"bytes": size, "records": len(records), "byType": dict(counts)}
    if args.truth and records and records[0].get("type") == "header":
        compared, mismatches = check_truth(records, args.truth)
        print(f"truth: {compared} tick record(s) compared with the scene tree, {len(mismatches)} mismatch(es)")
        summary.update({"truthCompared": compared, "truthMismatches": mismatches})
        problems.extend(mismatches)

    for problem in problems:
        print(f"PROBLEM {problem}")
    summary["problems"] = problems
    if args.json:
        args.json.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print("OK" if not problems else f"{len(problems)} PROBLEM(S)")
    return 0 if not problems else 1


if __name__ == "__main__":
    sys.exit(main())
