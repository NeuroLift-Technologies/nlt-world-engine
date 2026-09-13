#!/usr/bin/env bash
# Launch the WorldEngine editor with NLTTrainingGameMode for visual debugging
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_FILE="$SCRIPT_DIR/../WorldEngine.uproject"
ENGINE_DIR="$HOME/Documents/NLT/Engine"

cd "$SCRIPT_DIR/.."

"$ENGINE_DIR/Binaries/Linux/UnrealEditor" "$PROJECT_FILE" \
    -game \
    -AllowProcessAsync=0 \
    -NoAutoCompile \
    -RenderOffScreen \
    -nopause \
    -run=AutomationDriver \
    -debugcpu \
    2>&1
