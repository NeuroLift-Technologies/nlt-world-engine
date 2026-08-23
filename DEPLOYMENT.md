# Vercel vs Cloudflare for NeuroLift World Engine

## TL;DR: Use Both

| Layer | Platform | Why |
|-------|----------|-----|
| **Frontend** (Babylon.js viewer, dashboard) | **Vercel** | Best DX, preview deploys, instant rollbacks, Vercel AI SDK |
| **Simulation backend** (tick loop, state, WebSocket) | **Cloudflare Workers + Durable Objects** | Stateful compute, continuous tick loop, zero egress, global edge |
| **Storage** (assets, snapshots, training data) | **Cloudflare R2** | Zero egress, cheap, same account as Workers |
| **Relational data** (accounts, configs, history) | **Cloudflare D1** | SQLite at edge, same account |

---

## Why Not Just One?

### Vercel Alone ❌
- **Fluid Compute is serverless** — can't run a continuous tick loop
- **No stateful primitives** — Rivet Actors is a workaround, not native
- **$0.15/GB egress** — expensive for WebSocket streaming
- Good for frontend, wrong for simulation backend

### Cloudflare Alone ❌
- **Workers DX is weaker** — harder to build complex React dashboards
- **No Next.js equivalent** — would need separate frontend tooling
- Good for backend, suboptimal for frontend

### Both ✅ (Recommended)
- **Vercel** hosts the static frontend (Babylon.js bundle, React dashboard)
- **Cloudflare** runs the real-time simulation (Durable Objects with WebSocket fan-out)
- **Frontend ↔ Backend** via REST + WebSocket
- Best of both worlds

---

## Architecture

```
                    ┌─────────────────────────────────┐
                    │         Cloudflare Edge          │
                    │  ┌───────────────────────────┐  │
                    │  │   Durable Object (World)  │  │
                    │  │   - Tick loop (1Hz)       │  │
                    │  │   - ECS state             │  │
                    │  │   - WebSocket aggregation │  │
                    │  └─────────────┬─────────────┘  │
                    │                │                 │
                    │  ┌─────────────▼─────────────┐  │
                    │  │   Workers (API Gateway)   │  │
                    │  │   - REST endpoints        │  │
                    │  │   - Auth                  │  │
                    │  │   - DO routing            │  │
                    │  └───────────────────────────┘  │
                    └─────────────────────────────────┘
                                   ▲
                                   │ WebSocket + REST
                                   │
                    ┌──────────────┴──────────────────┐
                    │         Vercel Edge              │
                    │  ┌───────────────────────────┐  │
                    │  │   Babylon.js Viewer       │  │
                    │  │   - 3D scene              │  │
                    │  │   - Camera controls       │  │
                    │  │   - Click-to-inspect      │  │
                    │  └───────────────────────────┘  │
                    │  ┌───────────────────────────┐  │
                    │  │   React Dashboard         │  │
                    │  │   - Pair management       │  │
                    │  │   - Training config       │  │
                    │  │   - Analytics             │  │
                    │  └───────────────────────────┘  │
                    └─────────────────────────────────┘
```

---

## Cost Estimate (19 pairs, 1000 observers)

### Cloudflare (Simulation Backend)
| Resource | Usage | Cost |
|----------|-------|------|
| Workers requests | 10M/month | $0.30 |
| Durable Objects | 19 instances × 24/7 | ~$18 |
| WebSocket messages | 100M/month | ~$3 |
| R2 storage | 10GB | $0.15 |
| D1 rows | 1M reads | $0.50 |
| **Total** | | **~$22/month** |

### Vercel (Frontend)
| Resource | Usage | Cost |
|----------|-------|------|
| Hobby plan | 1 user | $0 (or $20 for Pro) |
| Bandwidth | 100GB | $0 (included) |
| **Total** | | **$0-20/month** |

### Combined: **$22-42/month**

Compare to Vercel-only with a VPS for the backend: **$100+/month**

---

## Why Durable Objects Are Perfect for This

Each **World Instance** = 1 Durable Object:

```typescript
// Each room/world is a Durable Object
export class WorldRoom {
  // Persistent state (survives restarts)
  state: {
    tickCount: number;
    sims: Map<string, SimState>;
    furniture: Map<string, FurnitureState>;
    timeOfDay: number;
  };

  // WebSocket connections from observers
  websockets: Set<WebSocket>;

  // Runs every 1 second (scheduled via alarm)
  async tick() {
    this.state = simulateTick(this.state);
    this.broadcastToObservers(this.state);
    storage.setAlarm(Date.now() + 1000);
  }

  // Observer connects via WebSocket
  async fetch(request: Request) {
    if (request.headers.get("Upgrade") === "websocket") {
      const pair = new WebSocketPair();
      const ws = pair[1];
      this.websockets.add(ws);
      ws.addEventListener("close", () => this.websockets.delete(ws));
      return new Response(null, { status: 101, webSocket: pair[0] });
    }
    return new Response(JSON.stringify(this.state));
  }
}
```

**Benefits:**
- **Single-threaded** — no race conditions on shared state
- **Global** — DO exists in one region, but observers connect to nearest edge
- **Persistent** — state survives restarts, crashes
- **WebSocket aggregation** — one DO fans out to thousands of observers
- **Cheap** — $1.30/month per million requests

---

## Recommendation

1. **Phase 1**: Cloudflare Workers + Durable Objects for the simulation backend
2. **Phase 2**: Vercel for the Babylon.js frontend + React dashboard
3. **Phase 3**: R2 for assets, D1 for relational data
4. **Phase 4**: Workers AI for edge inference (future)

This gives us:
- **Stateful simulation** (Durable Objects)
- **Real-time updates** (WebSocket fan-out)
- **Global low latency** (300+ edge locations)
- **Cheap at scale** (no egress fees, $0.30/M requests)
- **Best frontend DX** (Vercel + Next.js)
- **Portability** (business logic in Workers is portable if we ever need to migrate)
