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
  ./WorldEngine/Scripts/run_nlt_training.sh

  # Terminal 2: start PPO training (connects to UE's shared memory)
  python3 WorldEngine/Scripts/train_nlt_ppo.py \
      --controls-guid "<GUID_from_UE_logs>" \
      --task-dir "<UE_task_dir>" \
      --config WorldEngine/Scripts/nlt_ppo_config.json

  # To let this process generate a fresh GUID (if UE wasn't started with one):
  python3 WorldEngine/Scripts/train_nlt_ppo.py --create-mem --make-task-dir \
      --task-dir "<base_dir>" --config WorldEngine/Scripts/nlt_ppo_config.json

  # Monitor
  tensorboard --logdir=WorldEngine/Saved/LearningAgents/NLT/TensorBoard
"""

from __future__ import annotations

import argparse
import json
import os
import sys
import time
import uuid

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
# Clear pycache to force reload of edited source files
pycache_path = os.path.join(LEARNING_CORE, "learning_core", "__pycache__")
if os.path.exists(pycache_path):
    import shutil
    try:
        shutil.rmtree(pycache_path)
    except Exception:
        pass

if LEARNING_CORE not in sys.path:
    sys.path.insert(0, LEARNING_CORE)
else:
    # Move to front to ensure it overrides any installed site-packages version
    sys.path.remove(LEARNING_CORE)
    sys.path.insert(0, LEARNING_CORE)

import torch
import numpy as np

from learning_core.communicators.shared_memory_communicator import SharedMemoryCommunicator
from learning_core.train_common import AbstractExperimentTracker, get_experiment_trackers
from learning_core.train_ppo import train


class JsonLoggerTracker(AbstractExperimentTracker):
    """Simple experiment tracker that logs metrics to a JSON file."""

    def __init__(self, log_path: str):
        super().__init__({})
        self.log_path = log_path
        self.entries: list[dict] = []

    def initialize_tracker(self):
        os.makedirs(os.path.dirname(self.log_path) or ".", exist_ok=True)
        # Start fresh
        self.entries = []
        with open(self.log_path, "w") as f:
            json.dump([], f)

    def track(self, data: list):
        for key, value, step in data:
            self.entries.append({"key": key, "value": float(value), "step": int(step)})
        with open(self.log_path, "w") as f:
            json.dump(self.entries, f, indent=2)

    def track_snapshots(self, data: list, dir: str):
        pass

    def track_dict(self, data: dict, name: str):
        pass

    def close(self):
        with open(self.log_path, "w") as f:
            json.dump(self.entries, f, indent=2)


def load_config(path: str) -> dict:
    with open(path, "r") as f:
        return json.load(f)


def main():
    parser = argparse.ArgumentParser(description="NLT PPO Training (manual launcher)")
    parser.add_argument("--config", default="WorldEngine/Scripts/nlt_ppo_config.json",
                        help="Path to PPO settings config JSON (overrides UE-provided PPO settings)")
    parser.add_argument("--task-dir", default=None,
                        help="Override TaskDirectory (default: from config or UE)")
    parser.add_argument("--controls-guid", default="",
                        help="Controls GUID for shared memory (leave empty to auto-generate)")
    parser.add_argument("--num-processes", type=int, default=1,
                        help="Number of game processes (default: 1)")
    parser.add_argument("--make-task-dir", action="store_true",
                        help="Create the task directory and config directory")
    parser.add_argument("--create-mem", action="store_true",
                        help="Create shared memory (use when UE is not creating it)")
    args = parser.parse_args()

    # Load optional config for PPO settings overrides
    ppo_overrides = {}
    if os.path.exists(args.config):
        ppo_overrides = load_config(args.config)
        print(f"[NLT] Loaded config overrides from: {args.config}")
    else:
        print(f"[NLT] No config found at {args.config}, using UE-provided config")

    # Resolve task_dir
    if args.task_dir:
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        task_dir = os.path.join(project_root, args.task_dir)
    elif "TaskDirectory" in ppo_overrides:
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        task_dir = os.path.join(project_root, ppo_overrides["TaskDirectory"])
    else:
        task_dir = ""

    os.makedirs(task_dir, exist_ok=True) if task_dir else None
    snapshot_dir = os.path.join(task_dir or ".", "Snapshots")
    os.makedirs(snapshot_dir, exist_ok=True) if task_dir else None

    print(f"[NLT] Task directory: {task_dir or '(from UE)'}")
    print(f"[NLT] PyTorch {torch.__version__} | CUDA available: {torch.cuda.is_available()}")

    # Create communicator (shared memory — talks to UE's ULearningAgentsCommunicator)
    task_name = ppo_overrides.get("TaskName", "NLTTraining")
    communicator = SharedMemoryCommunicator(
        controls_guid=args.controls_guid,
        process_num=args.num_processes,
        task_dir=task_dir,
        task_name=task_name,
        create_mem=args.create_mem,
        make_task_dir=args.make_task_dir,
    )

    # All setup work that can leak shared-memory resources must happen inside
    # the try/finally so communicator.close() runs on any failure.
    trackers = []

    try:
        # Get config from UE (via shared memory)
        config = communicator.shared_memory_processes[0].config
        config['TaskName'] = task_name
        config["TaskDirectory"] = communicator.task_dir
        config['CommunicationType'] = 'SharedMemory'

        # Apply PPO settings overrides from config file (if provided)
        if "PPOSettings" in ppo_overrides:
            print("[NLT] Overriding PPO settings from config file")
            config['PPOSettings'] = ppo_overrides['PPOSettings']
        if "TrainingSettings" in ppo_overrides:
            config['TrainingSettings'] = ppo_overrides['TrainingSettings']

        # Trackers
        trackers = get_experiment_trackers(config)
        trackers.append(JsonLoggerTracker(os.path.join(task_dir, "training_log.json")))

        print(f"[NLT] Trackers: {[type(t).__name__ for t in trackers]}")
        print("[NLT] Connecting to UE training process...")
        print("[NLT] Waiting for NLTTrainingManager to spawn agents and begin episode...")

        train(config, communicator, trackers)
    except KeyboardInterrupt:
        print("\n[NLT] Training interrupted by user")
    except Exception as e:
        print(f"\n[NLT] Training error: {e}")
        raise
    finally:
        communicator.close()
        for t in trackers:
            try:
                t.close()
            except Exception:
                pass

    print(f"[NLT] Training complete. Snapshots saved to: {snapshot_dir}")


if __name__ == "__main__":
    main()
