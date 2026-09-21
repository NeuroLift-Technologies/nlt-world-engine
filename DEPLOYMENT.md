# UE 5.8 Deployment — NeuroLift World Engine

## The Vision

**NLT World Engine is an embodied multi-agent simulation where machine learning models inhabit a persistent world, control their characters, interact with environments and other agents, and transition between meaningful life scenarios.**

**An AI habitat — a virtual world where AI agents live, perceive, act, and learn.** The world is rendered with realistic graphics: procedural terrain, water, sky, vegetation, and settlement. AI residents walk through this world with articulated bodies, animated walk cycles, and name labels. Humans watch through a spectator viewer.

---

## TL;DR

UE 5.8 dedicated servers run the authoritative simulation — the embodied multi-agent world itself. The Babylon.js web viewer (spectator viewer) is deployed as a static site and connects to the UE servers via WebSocket.

---

## Deployment Architecture

```
                    ┌─────────────────────────────────┐
                    │         UE 5.8 Build            │
                    │  WorldEngineEditor (Windows)    │
                    │  WorldEngine (Linux)            │
                    │  WorldEngineServer (Linux)      │
                    └───────────────┬─────────────────┘
                                    │
                    ┌───────────────▼─────────────────┐
                    │      Container / VM / K8s       │
                    │    UE Dedicated Server (headless)│
                    │    -nullrhi -game -unattended   │
                    │    WebSocket on port 7777       │
                    └───────────────┬─────────────────┘
                                    │ WebSocket + HTTP
                    ┌───────────────▼─────────────────┐
                    │     Static Web Viewer (CDN)     │
                    │  world-engine-v2 (Babylon.js)    │
                    │  Vercel / Cloudflare Pages / S3 │
                    └─────────────────────────────────┘
```

---

## UE 5.8 Build Targets

| Target | Platform | Purpose |
|--------|----------|---------|
| `WorldEngineEditor` | Windows | Development editor |
| `WorldEngine` | Windows | Client build |
| `WorldEngineServer` | Linux | Headless dedicated server (production) |
| `WorldEngine` | Linux | Linux client (optional) |

---

## Build Commands

```bash
# Windows editor (development)
make WorldEngineEditor

# Linux dedicated server (production)
make WorldEngineServer

# Headless run
~/Documents/NLT/Engine/Binaries/Linux/UnrealEditor-Cmd \
  -project=WorldEngine.uproject \
  -nullrhi -game -unattended -log \
  -MAP=/Game/Scenarios/Levels/Workplace_Level.Workplace_Level
```

---

## Windows Build Environment (developer machine)

The Makefile above targets the Linux layout (`~/Documents/NLT/Engine`). The Windows
developer environment differs and is documented here (added 2026-09-21 after the
Win64 build-repair session — see `WorldEngine/docs/building/LNK1104-rsp-diagnosis.md`):

| Piece | Windows value |
|---|---|
| Engine | Epic launcher install, e.g. `C:\Program Files\Epic Games\UE_5.8` (5.8.2) |
| Toolchain | Visual Studio (MSVC 14.50.x), C++20 |
| Build tree | The UE projects folder, e.g. `C:\Users\<you>\Documents\Unreal Projects\WorldEngine` |
| Build command | `"<UE>\Engine\Build\BatchFiles\Build.bat" WorldEngineEditor Win64 Development -Project="<build tree>\WorldEngine.uproject" -WaitMutex -architecture=x64` (this is exactly what Visual Studio runs) |

### ASFDK-C++ headers (NLTGovernanceSubsystem)

The plugin needs the `asfdk-cplus` headers at
`WorldEngine/Plugins/NLTGovernanceSubsystem/ThirdParty/ASFDK`. Resolution order:

1. **`ASFDK_ROOT` environment variable** pointing at an asfdk-cplus checkout
   (the directory containing `packages/`). Use this on build agents or relocated checkouts:
   `setx ASFDK_ROOT D:\nlt-repos\asfdk-cplus`
2. **`ThirdParty/ASFDK`** — the git submodule (restore with
   `git submodule update --init WorldEngine/Plugins/NLTGovernanceSubsystem/ThirdParty/ASFDK`).
   In the C: build tree this path is a Windows junction into the asfdk-cplus checkout
   (create/repair with `cmd /c mklink /J <path> D:\nlt-repos\asfdk-cplus`).

If neither resolves, `NLTGovernanceSubsystem.Build.cs` fails the build immediately with the
exact fix commands — a silent dead include path was the root cause of the 2026-09-21 C1083.

### Hot-reload note (Win64 editor builds)

Building `WorldEngineEditor` from Visual Studio **while the Unreal Editor is running** uses
UBT's legacy hot-reload-from-IDE path. If a build fails with
`LNK1104: cannot open file '...-NNNN.lib.rsp'` or
`Unexpected conflict in renaming files`, the persisted hot-reload state is stale: close the
editor (UBT self-cleans on the next build) or delete
`Intermediate\Build\Win64\x64\WorldEngineEditor\Development\HotReloadState.json` and
`Metadata-HotReload.json`, then rebuild. Full diagnosis:
`WorldEngine/docs/building/LNK1104-rsp-diagnosis.md`.

---

## Dedicated Server Deployment

### Container (Docker)

```dockerfile
FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    libicu70 libssl1.1 libcurl4 libx11-6 \
    && rm -rf /var/lib/apt/lists/*

# Copy UE server binaries
COPY Binaries/Linux/ /opt/worldengine/

EXPOSE 7777/udp 7777/tcp

CMD ["/opt/worldengine/WorldEngineServer", \
     "-nullrhi", "-game", "-unattended", "-log", \
     "-MAP=/Game/Scenarios/Levels/Workplace_Level"]
```

### Kubernetes

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: worldengine-pair-sa01
spec:
  replicas: 1
  selector:
    matchLabels:
      app: worldengine
      pair: sa01
  template:
    metadata:
      labels:
        app: worldengine
        pair: sa01
    spec:
      containers:
      - name: worldengine
        image: neurolift/worldengine:latest
        ports:
        - containerPort: 7777
          protocol: UDP
        - containerPort: 7777
          protocol: TCP
        resources:
          requests:
            memory: "4Gi"
            cpu: "2"
          limits:
            memory: "8Gi"
            cpu: "4"
```

---

## Web Viewer Deployment

The Babylon.js viewer (`world-engine-v2/`) is a static site:

```bash
cd world-engine-v2
npm install
npm run build    # Outputs to dist/
```

Deploy `dist/` to:
- **Vercel**: `vercel deploy --prod`
- **Cloudflare Pages**: `npx wrangler pages deploy dist/`
- **S3 + CloudFront**: `aws s3 sync dist/ s3://worldengine-viewer/`

The viewer connects to the UE server via WebSocket:

```javascript
const ws = new WebSocket('ws://pair-sa01.worldengine.internal:7777');
```

---

## Scaling to 19+ Pairs

| Resource | Count | Notes |
|----------|-------|-------|
| UE Server containers | 19 | One per pair, isolated |
| CPU per server | 2-4 cores | Mass Entity simulation |
| Memory per server | 4-8 GB | Assets + state |
| WebSocket connections | 100-1000/pair | Observers |

### Orchestration Options

| Platform | Approach |
|----------|----------|
| Kubernetes | One Deployment per pair, StatefulSet for persistence |
| Docker Compose | Development: `docker compose up` with 19 services |
| VM-based | One VM per pair, systemd service for UE server |

---

## Environment Configuration

Each pair instance needs:

```bash
# Server
UE_SIM_TICK_RATE=1
UE_SIM_MODE=headless
UE_WS_PORT=7777
UE_HTTP_PORT=8080

# Observer Gateway
WEBSOCKET_URL=ws://pair-XXX.worldengine.internal:7777
PAIR_ID=pair-sa01
```

---

## CI/CD

```yaml
# .github/workflows/deploy.yml
name: Deploy WorldEngine
on:
  push:
    branches: [main]

jobs:
  build:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v4
      - name: Build UE Server
        run: make WorldEngineServer
      - name: Build Web Viewer
        run: |
          cd world-engine-v2
          npm install
          npm run build
      - name: Deploy Viewer
        run: npx vercel deploy world-engine-v2/dist --prod
      - name: Deploy Servers
        run: |
          # Push container image, rollout to K8s
          docker build -t neurolift/worldengine:${{ github.sha }} .
          docker push neurolift/worldengine:${{ github.sha }}
          kubectl set image deployment/worldengine-* worldengine=neurolift/worldengine:${{ github.sha }}
```

---

## Monitoring

| Metric | Source |
|--------|--------|
| Tick rate (Hz) | UE log + WebSocket heartbeat |
| Memory usage | Container metrics |
| WebSocket connections | UNLTWebServerSubsystem stats |
| Pair state | UE HTTP control API (`/api/state`) |

---

## Rollback

1. **Web viewer**: Revert static deployment (instant)
2. **UE server**: Roll back container image tag
3. **UE project**: `git revert` + rebuild

---

*Supersedes: Cloudflare Workers + Vercel + R2 + D1 deployment (2026-03)*
