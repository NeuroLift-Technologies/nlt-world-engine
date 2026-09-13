#!/usr/bin/env bash
# run_nlt_training.sh — Launch headless UE sim + PPO training for NLT WorldEngine
#
# Usage:
#   Terminal 1: ./WorldEngine/Scripts/run_nlt_training.sh
#   Terminal 2: python3 WorldEngine/Scripts/train_nlt_ppo.py
#
# Or run both in one shot:
#   ./WorldEngine/Scripts/run_nlt_training.sh --with-training

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
PROJECT_FILE="$PROJECT_ROOT/WorldEngine.uproject"

# Find UE editor
UE_EDITOR="$HOME/Documents/NLT/Engine/Binaries/Linux/UnrealEditor-Cmd"
if [[ ! -x "$UE_EDITOR" ]]; then
    echo "ERROR: UnrealEditor-Cmd not found at $UE_EDITOR"
    echo "Install UE 5.8 or set UE_EDITOR env var"
    exit 1
fi

echo "=== NLT WorldEngine Training Launcher ==="
echo "Project: $PROJECT_FILE"
echo "Editor:  $UE_EDITOR"

# Saved dir for training outputs
TASK_DIR="$PROJECT_ROOT/WorldEngine/Saved/LearningAgents/NLT"
mkdir -p "$TASK_DIR/Snapshots" "$TASK_DIR/TensorBoard"

echo ""
echo "Launching headless sim with NLTTrainingManager..."
echo "  Map:      /Game/Scenarios/Levels/Workplace_Level.Workplace_Level"
echo "  GameMode: /Script/WorldEngine.NLTDemoGameMode"
echo "  TaskDir:  $TASK_DIR"
echo ""

# Launch headless with training manager
# -nullrhi: no GPU (headless on Linux server)
# -game: game mode (not editor)
# -unattended: no UI prompts
# -stdout: log to stdout
# -FullStdOutLogOutput: verbose
exec "$UE_EDITOR" \
    "$PROJECT_FILE" \
    /Game/Scenarios/Levels/Workplace_Level.Workplace_Level \
    -game \
    -nullrhi \
    -unattended \
    -stdout \
    -FullStdOutLogOutput \
    -NLTDualModelTraining \
    -NLTTaskDir="$TASK_DIR"
