// World Engine simulation core — tick loop, avatar state, event emission.
//
// Ported from world-engine/sim.jsx to TypeScript.
// Pure logic, no rendering. Runs at a configurable tick rate.

import { AVATARS, AIDES, SCENARIOS, ROOMS, NPCS, STRATEGIES } from './data';

// ─── helpers ──────────────────────────────────────────────────────
const clamp = (v: number, lo = 0, hi = 1) => Math.max(lo, Math.min(hi, v));

// Deterministic-ish PRNG (mulberry32)
const rng = (() => {
  let s = 1337;
  return () => {
    s = (s * 1664525 + 1013904223) >>> 0;
    return (s & 0xfffffff) / 0xfffffff;
  };
})();

const pick = <T,>(arr: T[]): T => arr[Math.floor(rng() * arr.length)];

// ─── Flavor bias ──────────────────────────────────────────────────
export interface FlavorBias {
  drift: number;
  hyperfocus: number;
  stress: number;
  resist?: number;
  blurt?: number;
}

const FLAVOR_BIAS: Record<string, FlavorBias> = {
  attention:   { drift: 0.35, hyperfocus: 0.15, stress: 0.20 },
  initiation:  { drift: 0.10, hyperfocus: 0.05, stress: 0.25, resist: 0.55 },
  impulse:     { drift: 0.40, hyperfocus: 0.05, stress: 0.20, blurt: 0.35 },
  memory:      { drift: 0.30, hyperfocus: 0.05, stress: 0.30 },
  time:        { drift: 0.25, hyperfocus: 0.20, stress: 0.20 },
  emotion:     { drift: 0.20, hyperfocus: 0.05, stress: 0.50 },
  focus:       { drift: 0.05, hyperfocus: 0.55, stress: 0.30 },
  frustration: { drift: 0.15, hyperfocus: 0.10, stress: 0.45 },
  planning:    { drift: 0.30, hyperfocus: 0.05, stress: 0.25 },
  transition:  { drift: 0.20, hyperfocus: 0.10, stress: 0.30 },
  monitor:     { drift: 0.25, hyperfocus: 0.10, stress: 0.20 },
  fatigue:     { drift: 0.35, hyperfocus: 0.10, stress: 0.40 },
  effort:      { drift: 0.20, hyperfocus: 0.05, stress: 0.25 },
  stress:      { drift: 0.20, hyperfocus: 0.05, stress: 0.55 },
  sensory:     { drift: 0.30, hyperfocus: 0.20, stress: 0.40 },
  social:      { drift: 0.25, hyperfocus: 0.10, stress: 0.35 },
  identity:    { drift: 0.15, hyperfocus: 0.10, stress: 0.40 },
};

// ─── Types ────────────────────────────────────────────────────────
export interface AvatarState {
  id: string;
  name: string;
  trait: string;
  tag: string;
  hue: number;
  flavor: string;
  blurb: string;
  state: string;
  emotional: string;
  focus: number;
  cogLoad: number;
  stress: number;
  burnout: number;
  independence: number;
  fusionReady: number;
  successRate: number;
  scenarioId: string | null;
  elapsed: number;
  expected: number;
  minutesFocused: number;
  falseStarts: number;
  interventions: number;
  successes: number;
  failures: number;
  room: string;
  px: number;
  py: number;
  tx: number;
  ty: number;
  moveT: number;
  facing: string;
  lastEventTick: number;
}

export interface SimEvent {
  id: string;
  t: number;
  kind: string;
  text: string;
  who: string | null;
  scenarioId: string | null;
  avatarId: string;
  avatarName: string;
  avatarHue: number;
  strategy?: string;
  effectiveness?: number;
}

export interface WorldState {
  avatars: AvatarState[];
  events: SimEvent[];
  interventions: SimEvent[];
  tickCount: number;
  simTime: number;
}

// ─── Spawn ────────────────────────────────────────────────────────
function spawnAvatar(def: typeof AVATARS[number], room: typeof ROOMS[number]): AvatarState {
  return {
    ...def,
    state: 'idle',
    emotional: 'neutral',
    focus: 0.65 + rng() * 0.15,
    cogLoad: 0.20 + rng() * 0.10,
    stress: 0.15 + rng() * 0.10,
    burnout: 0.05,
    independence: 0.20 + rng() * 0.30,
    fusionReady: 0.0,
    successRate: 0.50,
    scenarioId: null,
    elapsed: 0,
    expected: 0,
    minutesFocused: 0,
    falseStarts: 0,
    interventions: 0,
    successes: 0,
    failures: 0,
    room: room.id,
    px: room.x + Math.floor(room.w / 2),
    py: room.y + Math.floor(room.h / 2),
    tx: room.x + Math.floor(room.w / 2),
    ty: room.y + Math.floor(room.h / 2),
    moveT: 0,
    facing: 'south',
    lastEventTick: 0,
  };
}

// ─── Event factory ────────────────────────────────────────────────
function mkEvent(
  kind: string,
  avatar: AvatarState,
  text: string,
  scenarioId: string | null = null,
  who: string | null = null,
  meta: Record<string, unknown> = {},
): SimEvent {
  return {
    id: `${Date.now().toString(36)}-${Math.floor(Math.random() * 1e6).toString(36)}`,
    t: Date.now(),
    kind,
    text,
    who,
    scenarioId,
    avatarId: avatar.id,
    avatarName: avatar.name,
    avatarHue: avatar.hue,
    ...meta,
  };
}

// ─── Simulation class ─────────────────────────────────────────────
export interface SimOptions {
  tickHz?: number;
  timeScale?: number;
  dysfunctionOn?: boolean;
  urgencyThreshold?: number;
}

export class Simulation {
  tickCount = 0;
  simTime = 0;
  running = true;
  private timer: ReturnType<typeof setInterval> | null = null;
  private opts: SimOptions;

  state: WorldState;

  constructor(opts: SimOptions = {}) {
    this.opts = {
      tickHz: 4,
      timeScale: 1.0,
      dysfunctionOn: true,
      urgencyThreshold: 0.6,
      ...opts,
    };
    this.state = this.makeInitialState();
  }

  private makeInitialState(): WorldState {
    return {
      avatars: AVATARS.map((def, i) => spawnAvatar(def, ROOMS[i % ROOMS.length])),
      events: [],
      interventions: [],
      tickCount: 0,
      simTime: 0,
    };
  }

  start(): void {
    if (this.timer) return;
    this.running = true;
    const ms = 1000 / (this.opts.tickHz ?? 4);
    this.timer = setInterval(() => this.step(), ms);
  }

  stop(): void {
    this.running = false;
    if (this.timer) {
      clearInterval(this.timer);
      this.timer = null;
    }
  }

  toggle(): void {
    if (this.running) this.stop();
    else this.start();
  }

  reset(): void {
    this.state = this.makeInitialState();
    this.tickCount = 0;
    this.simTime = 0;
  }

  step(): void {
    if (!this.running) return;
    const { timeScale = 1, dysfunctionOn = true, urgencyThreshold = 0.6 } = this.opts;
    const ts = timeScale;

    this.tickCount++;
    this.simTime += ts;

    const newEvents: SimEvent[] = [];
    const newInterventions: SimEvent[] = [];

    const nextAvatars = this.state.avatars.map((av) => {
      const a = { ...av };
      const bias = FLAVOR_BIAS[a.flavor] || FLAVOR_BIAS.attention;

      // ── spatial movement ──
      if (a.px !== a.tx || a.py !== a.ty) {
        const dx = Math.sign(a.tx - a.px);
        const dy = Math.sign(a.ty - a.py);
        if (Math.random() < 0.55) {
          a.px += dx;
          if (a.px === a.tx && dy) a.py += dy;
        } else if (dy) {
          a.py += dy;
        } else if (dx) {
          a.px += dx;
        }
        a.facing = dx > 0 ? 'east' : dx < 0 ? 'west' : dy > 0 ? 'south' : 'north';
      } else if (a.state === 'working' && rng() < 0.15) {
        const room = ROOMS.find((r) => r.id === a.room);
        if (room) {
          a.tx = room.x + Math.floor(rng() * room.w);
          a.ty = room.y + Math.floor(rng() * room.h);
        }
      }

      // ── assign scenario if idle ──
      if (!a.scenarioId && rng() < 0.18) {
        const sc = pick(SCENARIOS);
        a.scenarioId = sc.id;
        a.expected = sc.minutes;
        a.elapsed = 0;
        a.state = 'working';
        const room = ROOMS.find((r) => r.id === sc.room);
        if (room) {
          a.room = room.id;
          a.tx = room.x + Math.floor(rng() * room.w);
          a.ty = room.y + Math.floor(rng() * room.h);
        }
        newEvents.push(mkEvent('TASK_START', a, `started ${sc.name}`, sc.id));
      }

      // ── active scenario progress ──
      if (a.scenarioId) {
        const sc = SCENARIOS.find((s) => s.id === a.scenarioId);
        a.elapsed += ts;

        if (sc) {
          const loadGain = (sc.cog * 0.04) * ts;
          a.cogLoad = clamp(a.cogLoad + loadGain * (dysfunctionOn ? 1 : 0.4));
          if (sc.sustained && dysfunctionOn) {
            a.focus = clamp(a.focus - bias.drift * 0.02 * ts);
          }
          if (sc.aversive > 0.5 && dysfunctionOn) {
            a.stress = clamp(a.stress + bias.stress * 0.015 * ts);
          }

          // probabilistic events
          if (dysfunctionOn && rng() < bias.drift * 0.06 * ts && sc.sustained) {
            a.state = 'drifting';
            a.focus = clamp(a.focus - 0.10);
            newEvents.push(mkEvent('FOCUS_DRIFT', a, 'lost focus mid-task'));
          }
          if (dysfunctionOn && rng() < bias.hyperfocus * 0.04 * ts) {
            a.state = 'hyperfocus';
            a.cogLoad = clamp(a.cogLoad + 0.08);
            newEvents.push(mkEvent('HYPERFOCUS_ENTER', a, 'tunneled into a subtask'));
          }
          if (a.stress > 0.7 && rng() < 0.20 * ts) {
            newEvents.push(mkEvent('STRESS_SPIKE', a, `stress at ${(a.stress * 100).toFixed(0)}%`));
          }
          if (a.cogLoad > 0.85 && a.state !== 'overwhelmed') {
            a.state = 'overwhelmed';
            newEvents.push(mkEvent('COGNITIVE_LOAD_HIGH', a, 'cognitive load critical'));
          }

          // NPC interruption
          if (['office', 'meeting', 'lounge'].includes(a.room) && rng() < 0.04 * ts && dysfunctionOn) {
            const roomNpcs = NPCS.filter((n) => n.room === a.room && !n.invisible);
            if (roomNpcs.length > 0) {
              const npc = pick(roomNpcs);
              a.focus = clamp(a.focus - 0.08);
              a.cogLoad = clamp(a.cogLoad + 0.05);
              newEvents.push(mkEvent('NPC_INTERRUPT', a, `${npc.name} interrupted`, null, npc.name));
            }
          }

          // Aide coaching intervention
          const urgency = Math.max(a.stress, a.cogLoad, 1 - a.focus);
          if (urgency > urgencyThreshold && rng() < 0.35) {
            const aide = AIDES[a.id];
            const strategies = STRATEGIES[a.flavor] || STRATEGIES.attention;
            const strategy = pick(strategies);
            const effectiveness = 0.4 + rng() * 0.45;
            a.stress = clamp(a.stress - 0.25 * effectiveness);
            a.cogLoad = clamp(a.cogLoad - 0.20 * effectiveness);
            a.focus = clamp(a.focus + 0.15 * effectiveness);
            a.state = 'coached';
            a.interventions += 1;
            const evt = mkEvent('COACHING_INTERVENTION', a,
              `${aide.name} → "${strategy}"`, null, aide.name, { strategy, effectiveness });
            newEvents.push(evt);
            newInterventions.push(evt);
          }

          // Scenario complete / fail
          if (a.elapsed >= a.expected) {
            const successChance = (sc.base + (a.focus - 0.5) * 0.4 - a.stress * 0.3) * (1 + a.independence * 0.2);
            const success = rng() < clamp(successChance, 0.1, 0.95);
            if (success) {
              a.successes += 1;
              a.independence = clamp(a.independence + 0.02);
              a.fusionReady = clamp(a.fusionReady + 0.015);
              a.successRate = (a.successRate * 0.85) + 0.15;
              newEvents.push(mkEvent('TASK_COMPLETE', a, `${sc.name} ✓`));
            } else {
              a.failures += 1;
              a.stress = clamp(a.stress + 0.10);
              a.successRate = (a.successRate * 0.85);
              newEvents.push(mkEvent('TASK_FAIL', a, `${sc.name} — incomplete`));
            }
            a.scenarioId = null;
            a.state = 'idle';
            a.elapsed = 0;
            a.cogLoad = clamp(a.cogLoad - 0.20);
          }
        }
      } else {
        // idle decay
        a.cogLoad = clamp(a.cogLoad - 0.01 * ts);
        a.stress = clamp(a.stress - 0.015 * ts);
        a.focus = clamp(a.focus + 0.005 * ts, 0, 0.85);
        if (a.state !== 'idle') a.state = 'idle';
      }

      // burnout
      if (a.stress > 0.7) a.burnout = clamp(a.burnout + 0.003 * ts);
      else a.burnout = clamp(a.burnout - 0.001 * ts);

      return a;
    });

    this.state = {
      avatars: nextAvatars,
      events: newEvents.length
        ? [...newEvents.reverse(), ...this.state.events].slice(0, 80)
        : this.state.events,
      interventions: newInterventions.length
        ? [...newInterventions.reverse(), ...this.state.interventions].slice(0, 40)
        : this.state.interventions,
      tickCount: this.tickCount,
      simTime: this.simTime,
    };
  }
}