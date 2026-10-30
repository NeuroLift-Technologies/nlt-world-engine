// Turns nlt.observer-trace.v1 records into state-feed frames, a piece at a time.
//
// A recorded file is added in one go (feed/trace.ts). A run in progress is added as its lines
// arrive (feed/liveRun.ts). The two give the same frames for the same records.
//
// A trace is physical only: positions, velocities, scenes and the agent loop's decisions. It has no
// needs, levels, named state or Fusion gate, so the agents carry none. Nothing is inferred.
//
// Kept to erasable TypeScript (no parameter properties or enums) so Node can run it in the tests.
import type { IntentRecord, ParsedRecord, ResultRecord, TickRecord, TraceHeader } from '../trace/types';
import type { Agent, FeedEvent, StateFeedDoc } from './types';

/** How many recent decisions each frame lists, newest first: the events panel's window. */
export const EVENTS_SHOWN = 8;

const STAGE_WORDS: Record<string, string> = {
  accepted: 'accepted',
  protocol: 'refused by protocol',
  governance: 'refused by governance',
  physical: 'refused by the world',
};

function intentEvent(r: IntentRecord, res: ResultRecord | undefined): FeedEvent {
  const target = r.targetId ? ` → ${r.targetId}` : '';
  const outcome = res
    ? `${STAGE_WORDS[res.stage] ?? res.stage}${res.governanceCode ? ` (${res.governanceCode})` : ''}`
    : 'no result recorded';
  return {
    tick: r.observedTick,
    agentId: r.agentId,
    kind: 'decision',
    text: `${r.verb}${target} · ${outcome}`,
    severity: res && res.status !== 'accepted' ? 'warn' : undefined,
  };
}

interface TickGroup {
  tick: number;
  agents: Agent[];
  sceneKind: 'interior' | 'open_world';
  doc?: StateFeedDoc;
  docVersion?: number;
}

export class TraceFrames {
  /** Things worth telling the observer, such as a tick that arrived after its frame was built. */
  readonly problems: string[] = [];

  // Finished tick groups. A frame's decision list is worked out when the frame is read, not when
  // the group closes, because the engine writes a decision after the ticks that follow it. Reading
  // late means a decision shows up in every frame it belongs to, the same as a whole-file load.
  private groups: TickGroup[] = [];
  private version = 0; // bumped whenever the decision list changes, to drop cached frames

  private roster: Set<string>;
  // The tick group being collected. A group is complete when a later tick appears (or finish()).
  private pendingTick: number | null = null;
  private pendingAgents: Agent[] = [];
  private pendingSceneKind: 'interior' | 'open_world' = 'open_world';
  private lastEmittedTick = -Infinity;

  // Decisions, kept sorted by tick (ties in arrival order).
  private events: FeedEvent[] = [];
  private results = new Map<string, ResultRecord>();
  private intents = new Map<string, { record: IntentRecord; event: FeedEvent }>();

  constructor(header: TraceHeader) {
    this.roster = new Set(header.agentRoster);
  }

  add(records: ParsedRecord[]): void {
    for (const r of records) {
      if (r.kind === 'tick') this.addTick(r);
      else if (r.kind === 'intent') this.addIntent(r);
      else if (r.kind === 'result') this.addResult(r);
      else if (r.kind === 'decision_failed') {
        const why = [r.httpStatus ? `HTTP ${r.httpStatus}` : '', r.error ?? ''].filter(Boolean).join(' ');
        this.insertEvent({ tick: r.tick, agentId: r.agentId, kind: 'decision_failed', text: `no decision${why ? ` · ${why}` : ''}`, severity: 'warn' });
      } else if (r.kind === 'scene_transition') {
        this.insertEvent({ tick: r.tick, agentId: r.agentId, kind: 'scene_enter', text: `${r.from} → ${r.to}` });
      }
    }
  }

  /** The last tick group is only known to be complete once no more records are coming. */
  finish(): void {
    this.flush();
  }

  private addTick(r: TickRecord): void {
    if (this.pendingTick !== null && r.tick < this.pendingTick) {
      if (r.tick <= this.lastEmittedTick) this.problems.push(`tick ${r.tick} arrived after its frame was built; skipped`);
      else this.problems.push(`tick ${r.tick} arrived out of order; skipped`);
      return;
    }
    if (this.pendingTick === null && r.tick <= this.lastEmittedTick) {
      this.problems.push(`tick ${r.tick} arrived after its frame was built; skipped`);
      return;
    }
    if (this.pendingTick !== null && r.tick > this.pendingTick) this.flush();
    if (this.pendingTick === null) {
      this.pendingTick = r.tick;
      this.pendingSceneKind = r.scene.kind === 'interior' ? 'interior' : 'open_world';
    }
    this.pendingAgents.push({
      id: r.agentId,
      name: r.agentId,
      role: this.roster.has(r.agentId) ? 'avatar' : 'resident',
      scene: r.scene.id,
      position: r.position,
      velocity: r.velocity,
      levels: {},
      needs: {},
      state: '',
      stateSince: r.tick,
      struggleSignals: [],
      learnedStrategies: [],
      burnout: false,
      supportIndex: null,
    });
  }

  private addIntent(r: IntentRecord): void {
    const event = intentEvent(r, this.results.get(r.messageId));
    this.intents.set(r.messageId, { record: r, event });
    this.insertEvent(event);
  }

  /** A result can arrive after its intent. The decision's event is rewritten in place, so frames
   *  already built that list it show the outcome too. */
  private addResult(r: ResultRecord): void {
    this.results.set(r.intentMessageId, r);
    const known = this.intents.get(r.intentMessageId);
    if (known) {
      Object.assign(known.event, intentEvent(known.record, r));
      this.version++;
    }
  }

  private insertEvent(e: FeedEvent): void {
    this.version++;
    // After the last event with a tick <= e.tick, so equal ticks keep arrival order.
    let lo = 0;
    let hi = this.events.length;
    while (lo < hi) {
      const mid = (lo + hi) >> 1;
      if (this.events[mid].tick <= e.tick) lo = mid + 1;
      else hi = mid;
    }
    this.events.splice(lo, 0, e);
  }

  private flush(): void {
    if (this.pendingTick === null) return;
    this.groups.push({ tick: this.pendingTick, agents: this.pendingAgents, sceneKind: this.pendingSceneKind });
    this.lastEmittedTick = this.pendingTick;
    this.pendingTick = null;
    this.pendingAgents = [];
  }

  /** Frames that are complete so far. */
  count(): number {
    return this.groups.length;
  }

  frame(i: number): StateFeedDoc {
    const g = this.groups[i];
    if (g.doc && g.docVersion === this.version) return g.doc;

    let lo = 0;
    let hi = this.events.length;
    while (lo < hi) {
      const mid = (lo + hi) >> 1;
      if (this.events[mid].tick <= g.tick) lo = mid + 1;
      else hi = mid;
    }
    g.doc = {
      schemaVersion: 'nlt.observer-trace.v1',
      tick: g.tick,
      simTimeIso: '',
      scene: { id: g.agents[0].scene, kind: g.sceneKind },
      agents: g.agents,
      pairs: [],
      burnoutEpisodes: [],
      selfRecognitions: [],
      events: this.events.slice(Math.max(0, lo - EVENTS_SHOWN), lo),
    };
    g.docVersion = this.version;
    return g.doc;
  }

  all(): StateFeedDoc[] {
    return this.groups.map((_, i) => this.frame(i));
  }
}
