#!/usr/bin/env bash
# Launch the WorldEngine editor with NLTTrainingGameMode for visual training observation
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_FILE="$SCRIPT_DIR/../WorldEngine.uproject"
ENGINE_DIR="/home/joshd/Documents/NLT/Engine"

cd "$SCRIPT_DIR/.."

# Launch the editor directly (no render-off commands, no automation driver)
"$ENGINE_DIR/Binaries/Linux/UnrealEditor" "$PROJECT_FILE" "$@" &
