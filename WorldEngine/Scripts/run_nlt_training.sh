#!/usr/bin/env bash
# run_nlt_training.sh — Launch headless UE sim with NLTTrainingGameMode
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
PROJECT_FILE="$PROJECT_ROOT/WorldEngine.uproject"

UE_EDITOR="$HOME/Documents/NLT/Engine/Binaries/Linux/UnrealEditor-Cmd"
if [[ ! -x "$UE_EDITOR" ]]; then
    echo "ERROR: UnrealEditor-Cmd not found at $UE_EDITOR"
    exit 1
fi

echo "=== NLT WorldEngine Training Launcher ==="
echo "Project: $PROJECT_FILE"
echo "Editor:  $UE_EDITOR"
echo ""

TASK_DIR="$PROJECT_ROOT/WorldEngine/Saved/LearningAgents/NLT"
mkdir -p "$TASK_DIR/Snapshots" "$TASK_DIR/TensorBoard"

echo "Launching headless sim with NLTTrainingGameMode..."
echo "  Map:      /Game/Scenarios/Levels/Workplace_Level.Workplace_Level"
echo "  GameMode: /Script/WorldEngine.NLTTrainingGameMode"
echo ""

exec "$UE_EDITOR" \
    "$PROJECT_FILE" \
    /Game/Scenarios/Levels/Workplace_Level.Workplace_Level \
    -game \
    -nullrhi \
    -unattended \
    -stdout \
    -FullStdOutLogOutput
