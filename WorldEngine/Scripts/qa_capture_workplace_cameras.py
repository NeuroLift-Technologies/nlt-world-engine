#!/usr/bin/env python3
"""QA CaptureViewport pipeline for Workplace_Level human-scale cameras.

Poses are authored in Saved/QA/workplace_human_cameras.json.
MCP: EditorToolset.EditorAppToolset.SetCameraTransform then CaptureViewport
with annotations disabled (gridSpacing=0, maxLabelDistance=0, maxLabels=0).
Expected PNG outputs: Saved/QA/screenshots/QA_Cam_{SW,SE,NE,NW}.png
No Avatars/NPCs.
"""
from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "Saved" / "QA" / "workplace_human_cameras.json"
SHOT_DIR = ROOT / "Saved" / "QA" / "screenshots"


def load_catalog() -> dict:
    return json.loads(CATALOG.read_text())


def capture_args(cam: dict) -> dict:
    loc = cam["location"]
    rot = cam["rotation"]
    return {
        "captureTransform": {
            "location": loc,
            "rotation": rot,
            "scale": {"x": 1, "y": 1, "z": 1},
        },
        "annotations": {
            "gridSpacing": 0,
            "gridExtent": 0,
            "gridHeight": 0,
            "maxLabelDistance": 0,
            "classFilter": {"refPath": "/Script/Engine.Actor"},
            "maxLabels": 0,
        },
        "bShowUI": False,
    }


def main() -> None:
    data = load_catalog()
    SHOT_DIR.mkdir(parents=True, exist_ok=True)
    print(f"level={data['level']} eyeHeightCm={data['eyeHeightCm']}")
    for cam in data["cameras"]:
        out = SHOT_DIR / f"{cam['id']}.png"
        print(f"{cam['id']} z={cam['location']['z']} -> {out}")
        print(json.dumps(capture_args(cam)))


if __name__ == "__main__":
    main()
