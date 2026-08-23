# NeuroLift World Engine v2

> A real-time 3D simulation where pairs of ML Models (Avatar + Aide) train through authentic ADHD experiences in a Sims-like world, fusing into empathetic Advocates.

## Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    Browser (Babylon.js)                  │
│  ┌─────────┐ ┌─────────┐ ┌──────────┐ ┌─────────────┐ │
│  │  Scene  │ │  Sims   │ │   HUD    │ │   Camera    │ │
│  │ Rooms   │ │  Avatar │ │  Needs   │ │   System    │ │
│  │ Lighting│ │  Aide   │ │  Events  │ │   Follow    │ │
│  │Particles│ │Animation│ │  Skills  │ │   Cinematic │ │
│  └─────────┘ └─────────┘ └──────────┘ └─────────────┘ │
└──────────────────────────┬──────────────────────────────┘
                           │ REST + WebSocket
┌──────────────────────────▼──────────────────────────────┐
│                 Python FastAPI Backend                   │
│  ┌─────────────┐ ┌─────────────┐ ┌──────────────────┐ │
│  │  World Engine│ │  Avatars    │ │  Scenarios       │ │
│  │  ECS        │ │  Aides      │ │  Fusion          │ │
│  │  Tick Loop  │ │  Strategies │ │  Sessions        │ │
│  └─────────────┘ └─────────────┘ └──────────────────┘ │
└─────────────────────────────────────────────────────────┘
```

## Phases

1. **Phase 1** — Backend: Python FastAPI + ECS + World Engine (ported from neurolift-ai-fusion)
2. **Phase 2** — Frontend: Babylon.js scene, rooms, lighting, camera
3. **Phase 3** — Characters: Sim models, animation states, needs display
4. **Phase 4** — Connection: REST API + WebSocket for real-time updates
5. **Phase 5** — Polish: Particles, post-processing, HUD, controls
6. **Phase 6** — Deploy: Vercel frontend + backend hosting

## Quick Start

```bash
# Frontend (Babylon.js v2 scene)
cd world-engine-v2
npm install
npm run dev        # -> http://localhost:5173
npm run build      # production build (runs tsc && vite build)
npm run preview    # preview the production build locally
```

```bash
# Backend (Python FastAPI + ECS)
# The backend lives in a separate repository (Phase 1: World Engine core loop).
# See ARCHITECTURE.md for the component layout and the WebSocket contract
# (the frontend connects to /ws on the same host).
```
