// nlt.state-feed.v1 — docs/contracts/state-feed-v1.md. The viewer reads these
// documents; it never computes any of their fields (contract §2).

export const STATE_FEED_V1 = 'nlt.state-feed.v1';
export const REPLAY_V1 = 'nlt.state-feed.replay.v1';

export interface Vec3 { x: number; y: number; z: number }
export type Role = 'avatar' | 'aide' | 'advocate' | string;
export type NamedState = 'settled' | 'drifting' | 'resisting' | 'hyperfocus' | 'overwhelmed' | 'recovering' | 'coached' | string;

export interface Agent {
  id: string;
  name: string;
  role: Role;
  scene: string;
  position: Vec3;
  velocity: Vec3;
  appearance?: { body?: string; walkPhase?: number };
  levels: Record<string, number>;
  needs: Record<string, number>;
  state: NamedState;
  stateSince: number;
  currentGoal?: string;
  currentTask?: string;
  struggleSignals: string[];
  learnedStrategies: string[];
  burnout: boolean;
  supportIndex: number | null;
}

export interface Pair {
  avatarId: string;
  aideId: string;
  ready: boolean;
  overallScore: number;
  blockingDimensions: string[];
  dimensions: Record<string, { score: number; passes: boolean }>;
  recommendations?: string[];
}

export interface BurnoutEpisode { startTick: number; severity: number; peakBelow: number; recoveredTick?: number; recoveryMode?: 'solo' | 'rrt' }
export interface SelfRecognition { tick: number; riskAtRecognition: number; actedOn: boolean; ledTo: 'prevented' | 'delayed' | 'ignored' }
export interface FeedEvent { tick: number; agentId: string; kind: string; text: string; severity?: string; strategy?: string; helped?: boolean }

export interface StateFeedDoc {
  schemaVersion: string;
  tick: number;
  simTimeIso: string;
  scene: { id: string; kind: 'open_world' | 'interior' };
  agents: Agent[];
  pairs: Pair[];
  burnoutEpisodes: BurnoutEpisode[];
  selfRecognitions: SelfRecognition[];
  events: FeedEvent[];
}

export interface ReplayBundle {
  schemaVersion: string;
  name: string;
  title: string;
  provenance: { authored?: boolean; authoringTool?: string; generatedUtc?: string; note?: string };
  frameCount: number;
  frames: StateFeedDoc[];
}

const NEED_KEYS = ['quiet', 'rest', 'social', 'stimulation'];

/** Contract §9: missing required keys fail loudly, unknown keys are ignored, odd needs warn. */
export function validateDoc(d: unknown): { ok: true; warnings: string[] } | { ok: false; error: string } {
  const doc = d as Partial<StateFeedDoc>;
  if (!doc || typeof doc !== 'object') return { ok: false, error: 'document is not an object' };
  if (doc.schemaVersion !== STATE_FEED_V1) return { ok: false, error: `schemaVersion is ${String(doc.schemaVersion)}, expected ${STATE_FEED_V1}` };
  for (const k of ['tick', 'scene', 'agents'] as const) if (doc[k] === undefined) return { ok: false, error: `missing ${k}` };
  const warnings: string[] = [];
  for (const a of doc.agents ?? []) {
    for (const k of ['id', 'name', 'role', 'position', 'velocity', 'needs', 'state'] as const)
      if ((a as unknown as Record<string, unknown>)[k] === undefined) return { ok: false, error: `agent ${a.id ?? '?'} missing ${k}` };
    for (const n of NEED_KEYS) if (typeof a.needs[n] !== 'number') return { ok: false, error: `agent ${a.id} missing need ${n}` };
    for (const n of Object.keys(a.needs)) if (!NEED_KEYS.includes(n)) warnings.push(`agent ${a.id}: '${n}' is not an agent need (contract §4.3)`);
  }
  return { ok: true, warnings };
}
