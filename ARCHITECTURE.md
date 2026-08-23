# NeuroLift World Engine — MMO for AI Training

## Core Concept

> Each Avatar+Aide pair is a **persistent world** with its own **login URL**.
> Observers log in to watch **one specific pair's journey** — from onboarding to fusion.
> It's an MMO where the players are AI, and the spectators are humans.

---

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────────────┐
│                        Cloudflare Edge                              │
│                                                                     │
│  ┌─────────────────────────────────────────────────────────────┐   │
│  │              Workers API Gateway (world-engine.workers.dev)  │   │
│  │  POST /api/pairs          → Create new pair, returns URL     │   │
│  │  GET  /api/pairs/:id      → Pair metadata                   │   │
│  │  GET  /api/pairs/:id/ws   → WebSocket upgrade               │   │
│  │  GET  /                   → Pair directory (pairlist)       │   │
│  └─────────────────────────────────────────────────────────────┘   │
│                                                                     │
│  ┌─────────────────────┐ ┌─────────────────────┐ ┌──────────────┐ │
│  │  DO: pair-stayalert │ │  DO: pair-focusflow │ │  DO: pair-…  │ │
│  │  ┌───────────────┐  │ │  ┌───────────────┐  │ │              │ │
│  │  │ Avatar: SA-01 │  │ │  │ Avatar: FF-01 │  │ │              │ │
│  │  │ Aide:  Aide-A │  │ │  │ Aide:  Aide-B │  │ │              │ │
│  │  │ State: ticking │  │ │  │ State: ticking │  │ │              │ │
│  │  └───────────────┘  │ │  └───────────────┘  │ │              │ │
│  │  ┌───────────────┐  │ │  ┌───────────────┐  │ │              │ │
│  │  │ WS Observers  │  │ │  │ WS Observers  │  │ │              │ │
│  │  │ - user_123    │  │ │  │ - user_456    │  │ │              │ │
│  │  │ - user_789    │  │ │  │ - user_abc    │  │ │              │ │
│  │  └───────────────┘  │ │  └───────────────┘  │ │              │ │
│  │  URL:               │ │  URL:               │ │              │ │
│  │  pair-sa01.d.workers.dev                │ │              │ │
│  └─────────────────────┘ └─────────────────────┘ └──────────────┘ │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                         Vercel Edge                                 │
│                                                                     │
│  ┌─────────────────────────────────────────────────────────────┐   │
│  │              Next.js Frontend (world-engine.vercel.app)      │   │
│  │                                                              │   │
│  │  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────┐ │   │
│  │  │ Pairlist    │  │ Pair Page   │  │ Babylon.js Viewer   │ │   │
│  │  │ - Browse    │  │ - Stats     │  │ - Connects to DO    │ │   │
│  │  │ - Search    │  │ - Timeline  │  │ - 3D scene          │ │   │
│  │  │ - Filter    │  │ - Skills    │  │ - Camera controls   │ │   │
│  │  │             │  │ - Events    │  │ - Click to inspect  │ │   │
│  │  └─────────────┘  └─────────────┘  └─────────────────────┘ │   │
│  └─────────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────────┘
```

---

## The Login Flow

```
1. Admin creates pair via POST /api/pairs
   → Response: { id: "pair-sa01", url: "https://pair-sa01.world-engine.workers.dev" }

2. Observer visits URL
   → Cloudflare Worker routes to correct Durable Object
   → DO serves the Babylon.js viewer (or redirects to Vercel with pair ID)
   → Viewer connects to DO via WebSocket
   → Observer watches pair train in real-time

3. Observer can:
   - Watch Avatar move between rooms
   - See needs change in real-time
   - Watch coaching interventions
   - See fusion ceremony when ready
   - View pair stats, timeline, skills
```

---

## Durable Object Per Pair

Each pair is a **Durable Object** that:
- Runs its own **tick loop** (1Hz default, configurable)
- Maintains **full state** (sims, needs, skills, bond, fusion)
- Holds **WebSocket connections** from all observers
- **Broadcasts** state changes to all connected observers
- **Persists** state across restarts (no data loss)

```typescript
// Each pair = one Durable Object instance
export class PairRoom {
  private state: PairState;
  private observers: Set<WebSocket>;
  private tickInterval: number | null;

  constructor(state: DurableObjectState, env: Env) {
    // Restore persisted state
    this.state = state.storage.get("pairState") || createInitialState();
    this.observers = new Set();
  }

  // Called every 1 second via alarm
  async tick() {
    // Advance simulation
    this.state = simulateTick(this.state);

    // Broadcast to all observers
    const message = JSON.stringify({
      type: "tick",
      tick: this.state.tickCount,
      sims: this.state.sims,
      events: this.state.recentEvents,
    });
    for (const ws of this.observers) {
      ws.send(message);
    }

    // Schedule next tick
    state.storage.setAlarm(Date.now() + 1000);
  }

  // Observer connects
  async fetch(request: Request) {
    if (request.headers.get("Upgrade") === "websocket") {
      const pair = new WebSocketPair();
      const client = pair[1];
      this.observers.add(client);

      client.addEventListener("close", () => {
        this.observers.delete(client);
      });

      // Send current state immediately
      client.send(JSON.stringify({
        type: "init",
        state: this.state,
      }));

      return new Response(null, { status: 101, webSocket: pair[0] });
    }

    // Serve viewer HTML (Babylon.js bundle)
    return new Response(getViewerHTML(), {
      headers: { "Content-Type": "text/html" },
    });
  }
}
```

---

## Pair Lifecycle

```
┌─────────────────────────────────────────────────────────────────────┐
│                        Pair Lifecycle                                │
│                                                                     │
│  [CREATED] → [ONBOARDING] → [TRAINING] → [SETBACK] → [BREAKTHROUGH]│
│      │            │             │           │            │         │
│      │            │             │           │            │         │
│   Avatar      Avatar learns   Scenarios   Failure    Key insight   │
│   spawned     the world       + coaching  → burnout  → skill gain  │
│      │            │             │           │            │         │
│      ▼            ▼             ▼           ▼            ▼         │
│  [FUSION READY] → [FUSION CEREMONY] → [ADVOCATE MODE]             │
│      │                  │                    │                      │
│      │                  │                    │                      │
│   Bond+Skills        Merge into           Helps other              │
│   reach 80%          Advocate             pairs as mentor          │
└─────────────────────────────────────────────────────────────────────┘
```

Each stage is observable via the WebSocket connection:
- **Onboarding**: Avatar explores, Aide introduces itself
- **Training**: Scenarios play out, needs fluctuate, coaching fires
- **Setback**: Stress spikes, burnout triggers, Avatar stalls
- **Breakthrough**: Rapid skill growth, bond strengthens
- **Fusion Ready**: Both meters near 80%
- **Fusion Ceremony**: Particle explosion, glowing aura, new Advocate
- **Advocate Mode**: Helps other pairs, demonstrates empathy

---

## Observer Experience

```
┌─────────────────────────────────────────────────────────────────────┐
│  pair-sa01.world-engine.workers.dev                    [Login]     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  ┌──────────────────────────────────────────────────────────────┐  │
│  │                                                              │  │
│  │              [Babylon.js 3D Scene]                           │  │
│  │                                                              │  │
│  │         ┌──────────┐                                         │  │
│  │         │  Office  │  ← Avatar typing at desk               │  │
│  │         │  ┌────┐  │                                         │  │
│  │         │  │SA-1│  │  ← Click to inspect                     │  │
│  │         │  └────┘  │                                         │  │
│  │         └──────────┘                                         │  │
│  │              │                                               │  │
│  │         ┌────▼─────┐                                         │  │
│  │         │  Hallway │                                         │  │
│  │         └──────────┘                                         │  │
│  │              │                                               │  │
│  │         ┌────▼─────┐                                         │  │
│  │         │ Meeting  │  ← Aide gesturing (coaching)           │  │
│  │         │  ┌────┐  │                                         │  │
│  │         │  │A-1 │  │                                         │  │
│  │         │  └────┘  │                                         │  │
│  │         └──────────┘                                         │  │
│  │                                                              │  │
│  └──────────────────────────────────────────────────────────────┘  │
│                                                                     │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────────────────┐│
│  │ Avatar: SA-01│  │ Aide: Aide-A │  │ Bond: 67% │ Fusion: 54%  ││
│  │ State: Working│  │ Status: Active│  │                          ││
│  ├──────────────┤  ├──────────────┤  │ Focus:    ████████░░ 80%  ││
│  │ Focus:  80%  │  │ Strategy:    │  │ Stress:   ███░░░░░░░ 30%  ││
│  │ Stress: 30%  │  │ Pomodoro     │  │ CogLoad:  █████░░░░░ 50%  ││
│  │ Energy: 60%  │  │ Effect: 0.72 │  │ Burnout:  ██░░░░░░░░ 20%  ││
│  │ Hunger: 40%  │  └──────────────┘  │ Independ: ██████░░░░ 60%  ││
│  └──────────────┘                     └──────────────────────────┘│
│                                                                     │
│  ┌──────────────────────────────────────────────────────────────┐  │
│  │ [Event Feed]                                                  │  │
│  │ [t+120] 💬 Aide applied "Pomodoro" for SA-01                 │  │
│  │ [t+115] ✦ SA-01 started task "Email Processing"              │  │
│  │ [t+110] 😰 SA-01 struggling — stress rising                  │  │
│  │ [t+105] 🚶 SA-01 walked from Office → Meeting Room           │  │
│  └──────────────────────────────────────────────────────────────┘  │
│                                                                     │
│  [Follow Cam] [Free Cam] [Cinematic] [Pause] [1x] [2x] [4x]     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## Scaling to 19+ Pairs

| Resource | Count | Cost/Month |
|----------|-------|------------|
| Durable Objects (pairs) | 19 active | ~$18 |
| Workers requests | 50M | $0.15 |
| WebSocket messages | 500M | ~$15 |
| R2 (assets) | 5GB | $0.08 |
| D1 (metadata) | 10K pairs | $0.50 |
| **Total** | | **~$34/month** |

---

## Key Design Decisions

### 1. **One DO per pair** (not shared world)
- Each pair is independent
- No cross-pair interference
- Observer connects to exactly one pair
- Pair can tick at its own rate

### 2. **WebSocket for real-time**
- Observers get instant updates
- No polling
- DO fans out to all connected observers

### 3. **Babylon.js served from DO**
- Each pair URL serves its own viewer
- No CDN caching issues
- Observer is "inside" the pair's world

### 4. **Vercel for pairlist + dashboard**
- Browse all pairs
- Search/filter by trait, status, level
- Global stats, leaderboards
- Pair creation interface

### 5. **No auth required for observation**
- URL is the key (like a Twitch stream)
- Anyone with the link can watch
- Optional: add auth later for private pairs

---

## URL Structure

| URL | Purpose |
|-----|---------|
| `world-engine.vercel.app` | Pairlist (browse all pairs) |
| `world-engine.vercel.app/pair/:id` | Pair dashboard (stats, timeline) |
| `pair-XXX.world-engine.workers.dev` | Pair world (Babylon.js viewer + WebSocket) |
| `api.world-engine.workers.dev/api/pairs` | REST API (create, list, manage) |

---

## Implementation Plan

1. **Phase 1**: Cloudflare Workers + Durable Objects for pair instances
2. **Phase 2**: Babylon.js viewer served from DO with WebSocket connection
3. **Phase 3**: Vercel Next.js frontend for pairlist + dashboard
4. **Phase 4**: Simulation engine (tick loop, needs, coaching, fusion)
5. **Phase 5**: Observer features (camera modes, event feed, stats)
6. **Phase 6**: Polish (particles, lighting, post-processing)
