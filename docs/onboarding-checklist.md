# Developer Onboarding Checklist

> Follow this in order. Each step takes 2–10 minutes. Check it off as you go.

## Prerequisites

- [ ] **UE5.8.2** installed at `~/Documents/NLT/Engine/` (Linux)
- [ ] **Python 3.11+** available (`python3 --version`)
- [ ] **PyTorch** installed (`python3 -c "import torch; print(torch.__version__)"`)
- [ ] **TensorBoard** available (`python3 -m tensorboard --version`)
- [ ] **Learning Agents plugin** enabled in `WorldEngine/WorldEngine.uproject`
- [ ] **Governance read** — `NLT-DEV-OTOI.md` + `AGENTS.md` + this checklist

---

## Step 1: Governance & Environment

```bash
# 1. Clone the repo
git clone https://github.com/NeuroLift-Technologies/nlt-world-engine.git
cd nlt-world-engine

# 2. Run governance validation
bash .nltotoi/scripts/validate-governance.sh
# Expected: 29 passed, 0 failed, 0 warned
```

- [ ] Governance validation passes

---

## Step 2: UE5 Build

```bash
# 3. Build the UE5 project
cd WorldEngine
make WorldEngineEditor
# Expected: "Succeeded" (85s on warm cache, ~3min cold)
make WorldEngine
# Expected: "Succeeded" (22s on warm cache)
```

- [ ] `make WorldEngineEditor` succeeds
- [ ] `make WorldEngine` succeeds

---

## Step 3: Python Engine (read-only demo)

```bash
# 4. Run the Python demo (no UE needed)
cd world-engine
python3 demo.py
# Expected: Prints "Day complete" + avatar stats
```

- [ ] `python3 demo.py` runs successfully

---

## Step 4: SSE Service (Studio viewer)

```bash
# 5. Start the SSE/REST service
python3 world-engine/service/server.py &
# Expected: "SSE server started on :8765"

# 6. In another terminal, test the endpoint
curl http://localhost:8765/api/status
# Expected: JSON with {"status": "ok", "sim_state": {...}}
curl http://localhost:8765/api/scene
# Expected: JSON with scene graph
# Kill the server:
kill %1
```

- [ ] Server starts on port 8765
- [ ] `/api/status` returns JSON
- [ ] `/api/scene` returns JSON

---

## Step 5: Studio Viewer (browser)

```bash
# 7. Start static file server
cd world-engine
python3 -m http.server 8765 &

# 8. Start SSE service in another terminal
python3 service/server.py &

# 9. Open in browser:
#    http://127.0.0.1:8765/index.html?live=1
```

- [ ] Live viewer shows avatar moving through a day
- [ ] HUD panels show cognitive state, event stream, aide log

---

## Step 6: Training (the ML part)

```bash
# 10. Build the training binaries (already done in Step 2)

# 11. Launch UE5 in headless training mode
cd WorldEngine
~/Documents/NLT/Engine/Binaries/Linux/UnrealEditor \
  WorldEngine.uproject \
  -nullrhi -game -server -log \
  -MAP=/Game/Scenarios/Levels/Workplace_Level.Workplace_Level

# 12. Check the log for:
grep "NLTTrainingManager" Saved/Logs/WorldEngine.log
# Expected: "NLTTrainingManager: LA components initialized"
```

- [ ] UE5 headless training mode launches cleanly
- [ ] `NLTTrainingManager` initializes without errors

```bash
# 13. Run Python PPO training
cd ../../neurolift-ai-fusion/src/simulation/training
python3 train_nlt.py --standalone --agents 1 --iterations 50
# (Standalone mode runs without UE5; use --port 5555 for UE5 connection)

# 14. Monitor TensorBoard
python3 -m tensorboard --logdir=../../../WorldEngine/Saved/LearningAgents/TensorBoard/ --port 6006 &
# Open http://localhost:6006 → look for "Loss/AvatarPolicy", "Reward/AvatarMean", "Independence/AvatarMean"

---

## Step 7: Writing Code

Before you commit anything:

```bash
# 15. Run flake8 (Python critical errors)
flake8 world-engine/src/ --count --select=E9,F63,F7,F82 --show-source --statistics

# 16. Validate governance
bash .nltotoi/scripts/validate-governance.sh

# 17. Run Python tests
cd world-engine && python3 -m pytest tests/ -v
```

- [ ] flake8: 0 errors
- [ ] Governance validation: passes
- [ ] Tests: all pass

---

## Troubleshooting Quick Reference

| Problem | Fix |
|---------|-----|
| `make: command not found` | Install `make` via package manager |
| `UnrealEditor not found` | Check `~/Documents/NLT/Engine/Binaries/Linux/` |
| `Module LearningAgents not found` | Enable plugin in `WorldEngine.uproject` |
| `python3: command not found` | Install Python 3.11+ |
| Port 8765 already in use | `kill $(lsof -t -i:8765)` |
| UE build fails on Niagara | Ensure `Niagara` plugin is enabled in `.uproject` |
| Python imports fail | `pip install -r world-engine/requirements.txt` |

---

## Questions?

- **Scope questions** → escalate to Joshua (see `templates/escalation.md`)
- **Code questions** → read `docs/neurodivergent-guide.md`
- **Training issues** → read `docs/training/README.md`
- **Emergency** → file an issue with `ISSUE_TEMPLATE/agent-escalation.md`
