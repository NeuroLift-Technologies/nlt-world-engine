#!/usr/bin/env python3
"""
NLT PPO Training Launcher — connects PyTorch to the WorldEngine via Learning Agents.

Prerequisites
-------------
1. UE editor or headless sim running with NLTTrainingManager in the level
2. Learning Agents + LearningCore + PythonMLPackages plugins enabled
3. PyTorch installed in UE's PipInstall (verified: 2.5.1+cu124)

Usage
-----
  # Terminal 1: launch headless sim with training manager
  ./WorldEngine/Scripts/run_training.sh

  # Terminal 2: start PPO training
  python3 WorldEngine/Scripts/train_nlt_ppo.py --config WorldEngine/Scripts/nlt_ppo_config.json

  # Monitor
  tensorboard --logdir=WorldEngine/Saved/LearningAgents/NLT/TensorBoard
"""

from __future__ import annotations

import argparse
import json
import os
import sys
import time

# UE's bundled PyTorch
PIP_INSTALL = os.path.join(
    os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
    "Intermediate", "PipInstall", "lib", "python3.11", "site-packages"
)
if PIP_INSTALL not in sys.path:
    sys.path.insert(0, PIP_INSTALL)

# UE's LearningCore Python package
LEARNING_CORE = os.path.join(
    os.path.expanduser("~"), "Documents", "NLT", "Engine", "Plugins",
    "Experimental", "LearningCore", "Content", "Python"
)
if LEARNING_CORE not in sys.path:
    sys.path.insert(0, LEARNING_CORE)

import torch
import numpy as np

from learning_core.train_common import (
    SharedMemoryCommunicator,
    TensorBoardTracker,
    JsonLoggerTracker,
)
from learning_core.train_ppo import train


def load_config(path: str) -> dict:
    with open(path, "r") as f:
        return json.load(f)


def main():
    parser = argparse.ArgumentParser(description="NLT PPO Training")
    parser.add_argument("--config", default="WorldEngine/Scripts/nlt_ppo_config.json")
    parser.add_argument("--task-dir", default=None,
                        help="Override TaskDirectory (default: from config)")
    args = parser.parse_args()

    config = load_config(args.config)
    task_dir = args.task_dir or config["TaskDirectory"]

    # Resolve relative to project root
    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    task_dir = os.path.join(project_root, task_dir)
    task_dir = os.path.abspath(task_dir)
    config["TaskDirectory"] = task_dir

    os.makedirs(task_dir, exist_ok=True)
    snapshot_dir = os.path.join(task_dir, "Snapshots")
    os.makedirs(snapshot_dir, exist_ok=True)
    tb_dir = os.path.join(task_dir, "TensorBoard")
    os.makedirs(tb_dir, exist_ok=True)

    print(f"[NLT] Task directory: {task_dir}")
    print(f"[NLT] PyTorch {torch.__version__} | CUDA available: {torch.cuda.is_available()}")

    # Create communicator (shared memory — talks to UE's ULearningAgentsCommunicator)
    communicator = SharedMemoryCommunicator()

    # Trackers
    trackers = [
        TensorBoardTracker(tb_dir),
        JsonLoggerTracker(os.path.join(task_dir, "training_log.json")),
    ]

    print("[NLT] Connecting to UE training process...")
    print("[NLT] Waiting for NLTTrainingManager to spawn agents and begin episode...")

    try:
        train(config, communicator, trackers)
    except KeyboardInterrupt:
        print("\n[NLT] Training interrupted by user")
    except Exception as e:
        print(f"\n[NLT] Training error: {e}")
        raise
    finally:
        communicator.close()
        for t in trackers:
            t.close()

    print(f"[NLT] Training complete. Snapshots saved to: {snapshot_dir}")


if __name__ == "__main__":
    main()
