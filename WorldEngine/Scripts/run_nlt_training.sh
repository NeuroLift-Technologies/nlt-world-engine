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

# 1) Clean up stale shared memory from crashed/killed previous runs.
#    These look like /dev/shm/{GUID} and are left behind when the UE process
#    dies before LearningAgents can deallocate them. They cause the Python
#    trainer subprocess to map stale control blocks and fail the handshake.
echo "Cleaning up stale shared memory..."
rm -f /dev/shm/\{*\} 2>/dev/null || true

# 2) Clean up stale LearningCore intermediate config files from previous runs.
#    Old config files reference GUIDs that no longer exist in /dev/shm/,
#    causing FileNotFoundError in the Python trainer subprocess.
echo "Cleaning up stale LearningCore intermediate files..."
rm -rf "$PROJECT_ROOT/WorldEngine/Intermediate/LearningCore"/NLTTraining* 2>/dev/null || true

# 3) Kill any orphaned Python trainer processes from prior runs.
#    Use exact pattern to avoid killing this bash script itself.
echo "Killing orphaned trainer processes..."
pkill -9 -f "train[.]ppo" 2>/dev/null || true
pkill -9 -f "train[.]py" 2>/dev/null || true
pkill -9 -f "UnrealEditor-Cmd" 2>/dev/null || true

# 4) Give the OS a moment to release handles
sleep 1

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
