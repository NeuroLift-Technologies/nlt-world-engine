export class PairRoom implements DurableObject {
  private state: PairState;
  private observers: Set<WebSocket>;
  private tickInterval: number | null;
  private sql: SqlStorage;

  constructor(private state: DurableObjectState, private env: Env) {
    this.sql = state.storage.sql;
    this.observers = new new Set();
    this.tickInterval = null;

    // Initialize or restore state
    this.state = this.loadState() || this.createInitialState();
    this.initDatabase();
  }

  private initDatabase() {
    this.sql.exec(`
      CREATE TABLE IF NOT EXISTS events (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        tick INTEGER NOT NULL,
        type TEXT NOT NULL,
        message TEXT NOT NULL,
        timestamp INTEGER NOT NULL
      );
      CREATE INDEX IF NOT EXISTS idx_events_tick ON events(tick);
    `);
  }

  private createInitialState(): PairState {
    return {
      id: crypto.randomUUID(),
      tickCount: 0,
      timeOfDay: 600, // 10:00 AM
      avatars: [],
      aides: [],
      npcs: [],
      rooms: [
        { id: 'office', name: 'Office', x: 0, y: 0, w: 8, h: 8, props: ['desk', 'monitor', 'chair'] },
        { id: 'meeting', name: 'Meeting Room', x: 10, y: 0, w: 8, h: 8, props: ['longtable', 'chair', 'chair', 'screen'] },
        { id: 'home', name: 'Home', x: 0, y: 10, w: 8, h: 8, props: ['bed', 'night stand', 'dresser'] },
        { id: 'phone', name: 'Phone Booth', x: 10, y: 10, w: 4, h: 4, props: ['phone'] },
        { id: 'lounge', name: 'Lounge', x: 16, y: 0, w: 8, h: 8, props: ['sofa', 'coffee table', 'music stereo'] },
      ],
      recentEvents: [],
      createdAt: Date.now(),
    };
  }

  private loadState(): PairState | null {
    const stored = this.state.storage.get('pairState');
    return stored || null;
  }

  private saveState() {
    this.state.storage.put('pairState', this.state);
  }

  async tick() {
    if (this.tickInterval === null) return;

    this.state.tickCount++;
    this.state.timeOfDay += 2;
    if (this.state.timeOfDay > 1440) this.state.timeOfDay = 0;

    // Update avatars (simulate)
    for (const av of this.state.avatars) {
      this.simulateAvatar(av);
    }

    // Broadcast to observers
    const message = JSON.stringify({
      type: 'tick',
      tick: this.state.tickCount,
      timeOfDay: this.state.timeOfDay,
      avatars: this.state.avatars,
      recentEvents: this.state.recentEvents.slice(-5),
    });

    for (const ws of this.observers) {
      try {
        ws.send(message);
      } catch {
        this.observers.delete(ws);
      }
    }

    this.saveState();
  }

  private simulateAvatar(av: any) {
    // Simple need decay
    av.focus = Math.max(0, av.focus - 0.005);
    av.stress = Math.min(1, av.stress + 0.003);
    av.energy = Math.max(0, av.energy - 0.002);

    // Random events
    if (Math.random() < 0.02) {
      av.state = 'working';
      this.state.recentEvents.push({
        tick: this.state.tickCount,
        type: 'action',
        message: `${av.name} started working on a task`,
      });
    }
  }

  async fetch(request: Request): Promise<Response> {
    const url = new URL(request.url);

    // WebSocket upgrade
    if (request.headers.get('Upgrade') === 'websocket') {
      const pair = new WebSocketPair();
      const client = pair[1];
      this.observers.add(client);

      client.addEventListener('close', () => {
        this.observers.delete(client);
      });

      // Send current state immediately
      client.send(JSON.stringify({
        type: 'init',
        state: this.state,
      }));

      return new Response(null, { status: 101, webSocket: pair[0] });
    }

    // REST API
    if (url.pathname === '/api/state') {
      return new Response(JSON.stringify(this.state), {
        headers: { 'Content-Type': 'application/json' },
      });
    }

    if (url.pathname === '/api/events') {
      const events = this.sql.exec('SELECT * FROM events ORDER BY tick DESC LIMIT 50').toArray();
      return new Response(JSON.stringify(events), {
        headers: { 'Content-Type': 'application/json' },
      });
    }

    // Serve viewer HTML
    return new Response(getViewerHTML(), {
      headers: { 'Content-Type': 'text/html' },
    });
  }
}

function getViewerHTML(): string {
  return `<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>NeuroLift · Pair Viewer</title>
  <style>
    html, body { margin: 0; padding: 0; width: 100%; height: 100%; overflow: hidden; background: #0a0a1a; font-family: system-ui; color: #fff; }
    #renderCanvas { width: 100%; height: 100%; display: block; touch-action: none; }
    #hud { position: fixed; top: 16px; left: 16px; background: rgba(10,10,30,0.9); padding: 16px; border-radius: 12px; min-width: 220px; }
    #events { position: fixed; bottom: 16px; left: 16px; background: rgba(10,10,30,0.9); padding: 16px; border-radius: 12px; max-width: 400px; max-height: 200px; overflow-y: auto; }
  </style>
</head>
<body>
  <canvas id="renderCanvas"></canvas>
  <div id="hud">
    <h2>Pair Viewer</h2>
    <div id="pair-info">Connecting...</div>
  </div>
  <div id="events"></div>
  <script type="module" src="/viewer.js"></script>
</body>
</html>`;
}

export default {
  async fetch(request: Request, env: Env): Promise<Response> {
    const url = new URL(request.url);

    // Route to correct Durable Object based on subdomain
    const pairId = url.hostname.split('.')[0];
    if (pairId && pairId !== 'www' && pairId !== 'api') {
      const id = env.PAIR_ROOMS.idFromName(pairId);
      const room = env.PAIR_ROOMS.get(id);
      return room.fetch(request);
    }

    // Default: serve pairlist
    return new Response('NeuroLift World Engine', {
      headers: { 'Content-Type': 'text/plain' },
    });
  },
};
