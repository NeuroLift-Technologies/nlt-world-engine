#!/usr/bin/env bash
# Headless agent-loop run: a local Fusion endpoint plus Godot with no GPU, for a fixed time, then a
# short summary of what the loop did. Linux (or WSL). See docs/headless-loop.md.
#
# Usage: tools/headless-loop.sh [--seconds N] [--iterations N] [--agent-id ID] [--frames]
#                               [--skip-build] [--out DIR]
#
#   --seconds N     stop Godot after N seconds (default 120); with --iterations, the upper bound
#   --iterations N  let Godot quit by itself after N main-loop iterations (--quit-after): the only
#                   clean engine exit, since Godot ignores SIGINT and SIGTERM
#
# Environment:
#   GODOT              Godot 4.7.2 .NET (mono) editor binary                       (required)
#   FUSION_REPO        nlt-ai-fusion checkout                                       (required)
#   FUSION_PYTHON      Python with Fusion's requirements            (default: python3)
#   FUSION_PYTHONPATH  extra PYTHONPATH for Fusion, e.g. a llama-cpp-python venv's site-packages
#   FUSION_GGUF_MODEL  GGUF model path: model decisions; unset: the rule-based fallback
#   FUSION_AGENT_LOOP_PORT  endpoint port                           (default: 8001)
#
# Processes are tracked by PID files in the output folder, never by name patterns. Each runs in its
# own process group, so stopping it also stops its children (xvfb-run, uvicorn).

set -euo pipefail

SECONDS_TO_RUN=120
ITERATIONS=""
AGENT_ID="stay_alert_001"
FRAMES=0
SKIP_BUILD=0
OUT=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    --seconds) SECONDS_TO_RUN="$2"; shift 2 ;;
    --iterations) ITERATIONS="$2"; shift 2 ;;
    --agent-id) AGENT_ID="$2"; shift 2 ;;
    --frames) FRAMES=1; shift ;;
    --skip-build) SKIP_BUILD=1; shift ;;
    --out) OUT="$2"; shift 2 ;;
    -h|--help) sed -n '2,24p' "$0"; exit 0 ;;
    *) echo "unknown option: $1" >&2; exit 2 ;;
  esac
done

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROJECT="$REPO_ROOT/world-engine-godot"
PORT="${FUSION_AGENT_LOOP_PORT:-8001}"
OUT="${OUT:-${TMPDIR:-/tmp}/nlt-headless-loop/$(date -u +%Y%m%dT%H%M%SZ)}"
GRACE_SECONDS=5

fail() { echo "headless-loop: $*" >&2; exit 1; }

[[ -n "${GODOT:-}" && -x "$GODOT" ]] || fail "set GODOT to the Godot 4.7.2 .NET binary"
[[ -n "${FUSION_REPO:-}" && -f "$FUSION_REPO/src/fusion/agent_loop_http.py" ]] \
  || fail "set FUSION_REPO to an nlt-ai-fusion checkout"
[[ -f "$REPO_ROOT/../asfdk-csharp/src/Asfdk/Asfdk.csproj" ]] \
  || fail "world-engine-godot.csproj needs asfdk-csharp beside this repo: $REPO_ROOT/../asfdk-csharp"
if (( FRAMES )); then command -v xvfb-run >/dev/null || fail "--frames needs xvfb-run (and Mesa)"; fi

mkdir -p "$OUT"
echo "headless-loop: output in $OUT"

# Whether any process is left in the group led by the PID in a PID file. The leader alone is not
# enough: xvfb-run can exit while Godot, its child, is still running.
group_alive() {
  [[ -f "$1" ]] && kill -0 -- "-$(cat "$1")" 2>/dev/null
}

# Stop a process group recorded in a PID file with the given signal, then KILL after the grace
# period. Godot 4.7.2 ignores SIGINT, SIGTERM and SIGQUIT (with or without the agent loop; the
# loop driver is not the cause) and leaves SIGHUP at its default, so it is stopped with HUP:
# immediate, but not a clean shutdown (use --iterations for that). uvicorn stops cleanly on INT.
stop_group() {
  local pidfile="$1" sig="$2" pid
  [[ -f "$pidfile" ]] || return 0
  pid="$(cat "$pidfile")"
  if group_alive "$pidfile"; then
    kill -"$sig" -- "-$pid" 2>/dev/null || true
    for _ in $(seq "$GRACE_SECONDS"); do
      group_alive "$pidfile" || break
      sleep 1
    done
    if group_alive "$pidfile"; then
      echo "headless-loop: $(basename "$pidfile" .pid) did not exit after $sig; killing" >&2
      kill -KILL -- "-$pid" 2>/dev/null || true
    fi
  fi
  rm -f "$pidfile"
}
cleanup() {
  stop_group "$OUT/godot.pid" HUP
  stop_group "$OUT/fusion.pid" INT
}
trap cleanup EXIT

if (( ! SKIP_BUILD )); then
  echo "headless-loop: building C# and importing assets"
  dotnet build "$PROJECT/world-engine-godot.csproj" -v q > "$OUT/build.log" 2>&1 \
    || fail "dotnet build failed; see $OUT/build.log"
  "$GODOT" --headless --import --path "$PROJECT" > "$OUT/import.log" 2>&1 \
    || fail "asset import failed; see $OUT/import.log"
fi

probe_port() {
  curl -s -o /dev/null -w '%{http_code}' -X POST -H 'content-type: application/json' \
    -d '{}' "http://127.0.0.1:$PORT/agent-loop/perception" || true
}

# Something already answering on the port would take this run's perceptions (and this run's Fusion
# would fail to bind), so refuse to start rather than measure the wrong endpoint.
[[ "$(probe_port)" == "000" ]] \
  || fail "port $PORT is already in use; stop that server or set FUSION_AGENT_LOOP_PORT"

echo "headless-loop: starting Fusion on port $PORT ($([[ -n "${FUSION_GGUF_MODEL:-}" ]] && echo "model: $FUSION_GGUF_MODEL" || echo "rule-based fallback"))"
(
  cd "$FUSION_REPO"
  export FUSION_AGENT_LOOP_PORT="$PORT"
  [[ -n "${FUSION_PYTHONPATH:-}" ]] && export PYTHONPATH="${FUSION_PYTHONPATH}${PYTHONPATH:+:$PYTHONPATH}"
  exec setsid "${FUSION_PYTHON:-python3}" -m src.fusion.agent_loop_http
) > "$OUT/fusion.log" 2>&1 &
echo $! > "$OUT/fusion.pid"
disown  # stopped through its PID file; keeps the shell from reporting the kill

# Fusion is up once it answers an empty body with its fail-closed 422.
for _ in $(seq 60); do
  code="$(probe_port)"
  [[ "$code" == "422" ]] && break
  group_alive "$OUT/fusion.pid" || fail "Fusion exited; see $OUT/fusion.log"
  sleep 1
done
[[ "${code:-}" == "422" ]] || fail "Fusion did not come up on port $PORT; see $OUT/fusion.log"

GODOT_ARGS=(--path "$PROJECT")
[[ -n "$ITERATIONS" ]] && GODOT_ARGS+=(--quit-after "$ITERATIONS")
LAUNCH=(setsid)
if (( FRAMES )); then
  # Software-rendered (Mesa llvmpipe, Compatibility renderer): not representative of GPU output.
  mkdir -p "$OUT/frames-software-rendered"
  LAUNCH+=(xvfb-run -a -s "-screen 0 1280x720x24")
  GODOT_ARGS+=(--rendering-method gl_compatibility --rendering-driver opengl3
    --write-movie "$OUT/frames-software-rendered/frame.png" --fixed-fps 2)
else
  GODOT_ARGS=(--headless "${GODOT_ARGS[@]}")
fi

echo "headless-loop: running Godot as agent '$AGENT_ID' for ${ITERATIONS:+$ITERATIONS iterations, at most }${SECONDS_TO_RUN}s"
NLT_AGENT_LOOP_ENABLED=1 \
NLT_AGENT_LOOP_AGENT_ID="$AGENT_ID" \
NLT_AGENT_LOOP_ENDPOINT="http://127.0.0.1:$PORT/agent-loop/perception" \
  "${LAUNCH[@]}" "$GODOT" "${GODOT_ARGS[@]}" > "$OUT/godot.raw.log" 2>&1 &
echo $! > "$OUT/godot.pid"
disown

GODOT_EXIT="stopped after ${SECONDS_TO_RUN}s"
for _ in $(seq "$SECONDS_TO_RUN"); do
  group_alive "$OUT/godot.pid" || { GODOT_EXIT="exited by itself"; break; }
  sleep 1
done
cleanup
trap - EXIT

sed 's/\x1b\[[0-9;]*m//g' "$OUT/godot.raw.log" > "$OUT/godot.log"
LOG="$OUT/godot.log"
echo
echo "== summary =="
echo "godot: $GODOT_EXIT"
grep -m1 "Fusion agent loop enabled" "$LOG" || echo "agent loop did not start (see $LOG)"
echo "perceptions posted: $(grep -c '\[AgentLoopDriver\] perception' "$LOG" || true)"
echo "intents:"
grep -oE 'Intent [a-z_]+ for [^ ]+ (accepted|rejected)' "$LOG" | awk '{print "  " $2, $5}' | sort | uniq -c || true
echo "refusals and transport warnings: $(grep -cE 'does not serve agent|HTTP [0-9]{3}|transport failed' "$LOG" || true)"
if (( FRAMES )); then
  echo "frames (software-rendered): $(find "$OUT/frames-software-rendered" -name '*.png' | wc -l) in $OUT/frames-software-rendered"
fi
echo "logs: $LOG, $OUT/fusion.log"
