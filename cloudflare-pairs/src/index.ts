export class PairRoom implements DurableObject {
  private state: PairState;
  private observers: Set<WebSocket> = new Set();
  private tickAlarm: number | null = null;

  constructor(private stateObj: DurableObjectState, private env: Env) {
    this.state = this.createInitialState();
  }

  private createInitialState(): PairState {
    return {
      id: crypto.randomUUID(),
      tickCount: 0,
      timeOfDay: 600,
      avatars: [
        { id: 'sim-001', name: 'StayAlert', hue: 200, x: 4, y: 4, focus: 0.7, stress: 0.3, energy: 0.8, hunger: 0.5, social: 0.6, fun: 0.5, state: 'idle', interventions: 0 },
      ],
      aides: [
        { id: 'aide-001', name: 'Aide-A', hue: 260, x: 5, y: 5, focus: 0.9, stress: 0.1, energy: 0.9, hunger: 0.3, social: 0.8, fun: 0.7, state: 'idle', interventions: 0 },
      ],
      npcs: [
        { id: 'npc-001', name: 'Marcus', hue: 30, x: 12, y: 4 },
        { id: 'npc-002', name: 'Priya', hue: 330, x: 14, y: 12 },
      ],
      rooms: [
        { id: 'office', name: 'Office', x: 0, y: 0, w: 8, h: 8, props: ['desk', 'monitor', 'chair'] },
        { id: 'meeting', name: 'Meeting Room', x: 10, y: 0, w: 8, h: 8, props: ['longtable', 'chair', 'screen'] },
        { id: 'home', name: 'Home', x: 0, y: 10, w: 8, h: 8, props: ['bed', 'night stand', 'dresser'] },
        { id: 'phone', name: 'Phone Booth', x: 10, y: 10, w: 4, h: 4, props: ['phone'] },
        { id: 'lounge', name: 'Lounge', x: 16, y: 0, w: 8, h: 8, props: ['sofa', 'coffee table', 'music stereo'] },
      ],
      recentEvents: [],
      createdAt: Date.now(),
    };
  }

  async startTicking() {
    if (this.tickAlarm !== null) return;
    this.tickAlarm = Date.now() + 1000;
    await this.stateObj.storage.setAlarm(this.tickAlarm);
  }

  async alarm() {
    this.tick();
    this.tickAlarm = Date.now() + 1000;
    await this.stateObj.storage.setAlarm(this.tickAlarm);
  }

  private tick() {
    this.state.tickCount++;
    this.state.timeOfDay += 2;
    if (this.state.timeOfDay > 1440) this.state.timeOfDay = 0;

    for (const av of this.state.avatars) {
      av.focus = Math.max(0, Math.min(1, av.focus - 0.005 + (Math.random() - 0.5) * 0.01));
      av.stress = Math.max(0, Math.min(1, av.stress + 0.003 + (Math.random() - 0.5) * 0.01));
      av.energy = Math.max(0, Math.min(1, av.energy - 0.002 + (Math.random() - 0.5) * 0.01));
      av.hunger = Math.min(1, av.hunger + 0.003);
      av.fun = Math.max(0, av.fun - 0.002);
      av.social = Math.max(0, av.fun - 0.001);

      if (Math.random() < 0.02) {
        av.state = ['idle', 'walking', 'working', 'struggling', 'hyperfocus', 'coached'][Math.floor(Math.random() * 6)];
      }

      if (Math.random() < 0.005) {
        av.x = Math.max(0, Math.min(24, av.x + (Math.random() - 0.5) * 2));
        av.y = Math.max(0, Math.min(18, av.y + (Math.random() - 0.5) * 2));
      }
    }

    for (const aide of this.state.aides) {
      if (Math.random() < 0.01) {
        aide.state = ['idle', 'coaching'][Math.floor(Math.random() * 2)];
      }
    }

    if (Math.random() < 0.03) {
      const av = this.state.avatars[0];
      const events = ['started a new task', 'is focusing', 'is struggling with attention', 'is taking a break', 'is drifting off'];
      this.state.recentEvents.push({
        tick: this.state.tickCount,
        type: 'action',
        message: `${av.name} ${events[Math.floor(Math.random() * events.length)]}`,
      });
      if (this.state.recentEvents.length > 20) this.state.recentEvents.shift();
    }

    const msg = JSON.stringify({
      type: 'tick',
      tick: this.state.tickCount,
      timeOfDay: this.state.timeOfDay,
      avatars: this.state.avatars,
      recentEvents: this.state.recentEvents.slice(-5),
    });

    for (const ws of this.observers) {
      try { ws.send(msg); } catch { this.observers.delete(ws); }
    }

    this.stateObj.storage.put('pairState', this.state);
  }

  async fetch(request: Request): Promise<Response> {
    const url = new URL(request.url);

    if (request.headers.get('Upgrade') === 'websocket') {
      const pair = new WebSocketPair();
      const client = pair[1];
      this.observers.add(client);

      client.addEventListener('close', () => this.observers.delete(client));

      client.send(JSON.stringify({ type: 'init', state: this.state }));

      this.startTicking();

      return new Response(null, { status: 101, webSocket: pair[0] });
    }

    if (url.pathname === '/api/state') {
      return new Response(JSON.stringify(this.state), {
        headers: { 'Content-Type': 'application/json' },
      });
    }

    return new Response(JSON.stringify({ message: 'NeuroLift World Engine', pairs: [] }), {
      headers: { 'Content-Type': 'application/json' },
    });
  }
}

export default {
  async fetch(request: Request, env: Env): Promise<Response> {
    const url = new URL(request.url);
    const pairId = url.hostname.split('.')[0];

    // If accessed directly (no pair subdomain), use a default pair
    if (!pairId || pairId === 'www' || pairId === 'api' || pairId === 'world-engine' || pairId === 'cloudflare-pairs') {
      const id = env.PAIR_ROOMS.idFromName('default');
      const room = env.PAIR_ROOMS.get(id);
      return room.fetch(request);
    }

    // Route to correct DO based on subdomain
    const id = env.PAIR_ROOMS.idFromName(pairId);
    const room = env.PAIR_ROOMS.get(id);
    return room.fetch(request);
  },
};
