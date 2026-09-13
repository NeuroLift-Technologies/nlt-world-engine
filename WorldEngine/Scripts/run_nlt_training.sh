#!/usr/bin/env bash
# run_nlt_training.sh — Launch headless UE sim with NLTTrainingGameMode
#
# Usage:
#   ./run_nlt_training.sh           # Default: LLM-driven control via Ollama REST bridge
#   ./run_nlt_training.sh --ppo      # PPO training mode (uses LearningAgents + Python)
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
PROJECT_FILE="$PROJECT_ROOT/WorldEngine.uproject"

UE_EDITOR="$HOME/Documents/NLT/Engine/Binaries/Linux/UnrealEditor-Cmd"
if [[ ! -x "$UE_EDITOR" ]]; then
    echo "ERROR: UnrealEditor-Cmd not found at $UE_EDITOR"
    exit 1
fi

# Parse arguments
MODE="llm"
if [[ "${1:-}" == "--ppo" ]]; then
    MODE="ppo"
fi

echo "=== NLT WorldEngine Training Launcher ==="
echo "Project: $PROJECT_FILE"
echo "Editor:  $UE_EDITOR"
echo "Mode:    $MODE"
echo ""

# 1) Clean up stale shared memory from crashed/killed previous runs.
echo "Cleaning up stale shared memory..."
rm -f /dev/shm/\{\*\} 2>/dev/null || true

# 2) Clean up stale LearningCore intermediate config files from previous runs.
echo "Cleaning up stale LearningCore intermediate files..."
rm -rf "$PROJECT_ROOT/WorldEngine/Intermediate/LearningCore"/NLTTraining* 2>/dev/null || true

# 3) Kill any orphaned Python trainer processes from prior runs.
echo "Killing orphaned trainer processes..."
pkill -9 -f "train[.]ppo" 2>/dev/null || true
pkill -9 -f "train[.]py" 2>/dev/null || true
pkill -9 -f "UnrealEditor-Cmd" 2>/dev/null || true

# 4) Give the OS a moment to release handles
sleep 1

TASK_DIR="$PROJECT_ROOT/WorldEngine/Saved/LearningAgents/NLT"
mkdir -p "$TASK_DIR/Snapshots" "$TASK_DIR/TensorBoard"

if [[ "$MODE" == "llm" ]]; then
    echo "Launching headless sim with LLM-driven control (Ollama REST bridge)..."
    echo "  LLM endpoint: http://localhost:11434/api/generate"
    echo "  Model:        qwen3:0.6b"
    echo ""
    exec "$UE_EDITOR" \
        "$PROJECT_FILE" \
        /Game/Scenarios/Levels/Workplace_Level.Workplace_Level \
        -game \
        -nullrhi \
        -unattended \
        -stdout \
        -FullStdOutLogOutput
else
    echo "Launching headless sim with PPO training..."
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
fi
