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
# Match only NLT-related shared-memory files (LearningAgents uses task-name
# based names) to avoid clobbering unrelated processes' IPC.
echo "Cleaning up stale shared memory..."
rm -f /dev/shm/*NLT* 2>/dev/null || true
rm -f /dev/shm/ue4.NLT* 2>/dev/null || true
rm -f /dev/shm/ue.NLT* 2>/dev/null || true

# 2) Clean up stale LearningCore intermediate config files from previous runs.
echo "Cleaning up stale LearningCore intermediate files..."
rm -rf "$PROJECT_ROOT/WorldEngine/Intermediate/LearningCore"/NLTTraining* 2>/dev/null || true

# 3) Kill only orphaned trainer/editor processes tied to THIS project.
# Match on the project file path to avoid terminating unrelated Unreal
# projects or trainers running on the same machine.
echo "Killing orphaned trainer processes for this project..."
pkill -9 -f "train_nlt_ppo.*$PROJECT_FILE" 2>/dev/null || true
pkill -9 -f "UnrealEditor-Cmd.*$PROJECT_FILE" 2>/dev/null || true

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
        "/Game/Scenarios/Levels/Workplace_Level.Workplace_Level?game=/Script/WorldEngine.NLTTrainingGameMode" \
        -game \
        -nullrhi \
        -unattended \
        -stdout \
        -FullStdOutLogOutput \
        -llm
else
    echo "Launching headless sim with PPO training..."
    echo "  Map:      /Game/Scenarios/Levels/Workplace_Level.Workplace_Level"
    echo "  GameMode: /Script/WorldEngine.NLTTrainingGameMode"
    echo ""
    exec "$UE_EDITOR" \
        "$PROJECT_FILE" \
        "/Game/Scenarios/Levels/Workplace_Level.Workplace_Level?game=/Script/WorldEngine.NLTTrainingGameMode" \
        -game \
        -nullrhi \
        -unattended \
        -stdout \
        -FullStdOutLogOutput \
        -ppo
fi
