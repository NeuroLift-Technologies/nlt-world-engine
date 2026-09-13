#!/usr/bin/env bash
# run_nlt_training_editor.sh — Launch UE editor with NLTTrainingGameMode for viewing
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
PROJECT_FILE="$PROJECT_ROOT/WorldEngine.uproject"

UE_EDITOR="$HOME/Documents/NLT/Engine/Binaries/Linux/UnrealEditor"
if [[ ! -x "$UE_EDITOR" ]]; then
    echo "ERROR: UnrealEditor not found at $UE_EDITOR"
    exit 1
fi

echo "=== NLT WorldEditor Training (Editor Mode) ==="
echo "Project: $PROJECT_FILE"
echo ""

# Clean up stale shared memory
rm -f /dev/shm/\{*\} 2>/dev/null || true
rm -rf "$PROJECT_ROOT/WorldEngine/Intermediate/LearningCore"/NLTTraining* 2>/dev/null || true
pkill -9 -f "train[.]ppo" 2>/dev/null || true
pkill -9 -f "UnrealEditor" 2>/dev/null || true
sleep 1

echo "Opening editor..."
echo "  Map:      /Game/Scenarios/Levels/Workplace_Level.Workplace_Level"
echo "  GameMode: /Script/WorldEngine.NLTTrainingGameMode"
echo ""

exec "$UE_EDITOR" \
    "$PROJECT_FILE" \
    /Game/Scenarios/Levels/Workplace_Level.Workplace_Level \
    -GameMode=/Script/WorldEngine.NLTTrainingGameMode
