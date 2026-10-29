// A recorded Godot engine run (nlt.observer-trace.v1, docs/contracts/observer-trace-v1.md) as a
// FeedSource, so the 3D view can replay a headless run on the real island.
//
// A trace is physical only: positions, velocities, scenes and the agent loop's decisions. It has no
// needs, levels, named state or Fusion gate — those are Fusion's and are not in the file — so the
// agents here carry none, and the UI says so rather than drawing bars. Nothing is inferred.
import { parseTrace } from '../trace/parser';
import type { ParsedRecord, ResultRecord, TraceHeader } from '../trace/types';
import type { FeedSource, SourceInfo } from './source';
import type { Agent, FeedEvent, StateFeedDoc } from './types';

/** The real headless run bundled with the viewer (fixtures/observer-trace/README.md). */
export const TRACE_SAMPLE = { id: 'sample', url: 'godot/fixtures/observer-trace-sample.jsonl', label: 'Headless engine run — sample' };

/** How many recent decisions each frame lists, newest first: the events panel's window. */
const EVENTS_SHOWN = 8;

const STAGE_WORDS: Record<string, string> = {
  accepted: 'accepted',
  protocol: 'refused by protocol',
  governance: 'refused by governance',
  physical: 'refused by the world',
};

type Load = { kind: 'url'; url: string } | { kind: 'text'; text: string; name: string };

export class TraceSource implements FeedSource {
  info: SourceInfo;
  private frames: StateFeedDoc[] = [];
  private diag: string[] = [];
  private cadenceHz = 10;

  constructor(private load: Load, label: string) {
    this.info = { kind: 'replay', content: 'physical-trace', id: 'trace', title: label, status: 'idle', provenance: 'Recorded engine run' };
  }

  async open(): Promise<void> {
    this.info.status = 'loading';
    try {
      let text: string;
      if (this.load.kind === 'url') {
        const res = await fetch(this.load.url);
        if (!res.ok) throw new Error(`HTTP ${res.status} loading ${this.load.url}`);
        text = await res.text();
      } else text = this.load.text;
      const parsed = parseTrace(text);
      // The parser reports a wrong schemaVersion or an unreadable header as an error; either means
      // this is not a trace this viewer can read, so refuse it rather than draw a guess.
      const fatal = parsed.errors.filter((e) => e.includes('schemaVersion') || e.includes('header'));
      if (fatal.length) throw new Error(fatal.join(' '));
      this.diag.push(...parsed.errors);
      for (const r of parsed.records) if (r.kind === 'unknown') this.diag.push(`line ${r.line}: ${r.reason}`);
      this.build(parsed.header, parsed.records);
      if (!this.frames.length) throw new Error('the recording has no tick records, so there is nothing to place');
      this.describe(parsed.header);
      this.info.status = 'ready';
    } catch (e) {
      this.info.status = 'error';
      this.info.detail = e instanceof Error ? e.message : String(e);
      throw e;
    }
  }

  private describe(h: TraceHeader) {
    this.cadenceHz = h.cadenceHz > 0 ? h.cadenceHz : 10;
    this.info.provenance = `Recorded engine run (Godot ${h.godotVersion || '?'}, engine ${h.engineCommit || '?'}) — positions and decisions only`;
    this.info.detail = `Run ${h.runId || '?'}, started ${h.startTime || '?'}. nlt.observer-trace.v1 recorded by the Godot World Engine; Fusion's needs, states and readiness are not in this file.`;
  }

  private build(header: TraceHeader, records: ParsedRecord[]) {
    const roster = new Set(header.agentRoster);
    // Agents at each sampled tick. The engine samples every avatar at the same tick (cadenceHz).
    const byTick = new Map<number, Agent[]>();
    for (const r of records) {
      if (r.kind !== 'tick') continue;
      const list = byTick.get(r.tick) ?? [];
      list.push({
        id: r.agentId,
        name: r.agentId,
        role: roster.has(r.agentId) ? 'avatar' : 'resident',
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
      byTick.set(r.tick, list);
    }
    const ticks = [...byTick.keys()].sort((a, b) => a - b);

    // Decisions as the engine recorded them: an intent with its result, a failed request, a scene
    // change. Text only restates the record; nothing is scored or interpreted.
    const results = new Map<string, ResultRecord>();
    for (const r of records) if (r.kind === 'result') results.set(r.intentMessageId, r);
    const events: FeedEvent[] = [];
    for (const r of records) {
      if (r.kind === 'intent') {
        const res = results.get(r.messageId);
        const target = r.targetId ? ` → ${r.targetId}` : '';
        const outcome = res
          ? `${STAGE_WORDS[res.stage] ?? res.stage}${res.governanceCode ? ` (${res.governanceCode})` : ''}`
          : 'no result recorded';
        events.push({ tick: r.observedTick, agentId: r.agentId, kind: 'decision', text: `${r.verb}${target} · ${outcome}`, severity: res && res.status !== 'accepted' ? 'warn' : undefined });
      } else if (r.kind === 'decision_failed') {
        const why = [r.httpStatus ? `HTTP ${r.httpStatus}` : '', r.error ?? ''].filter(Boolean).join(' ');
        events.push({ tick: r.tick, agentId: r.agentId, kind: 'decision_failed', text: `no decision${why ? ` · ${why}` : ''}`, severity: 'warn' });
      } else if (r.kind === 'scene_transition') {
        events.push({ tick: r.tick, agentId: r.agentId, kind: 'scene_enter', text: `${r.from} → ${r.to}` });
      }
    }
    events.sort((a, b) => a.tick - b.tick);

    let next = 0;
    const recent: FeedEvent[] = [];
    for (const tick of ticks) {
      while (next < events.length && events[next].tick <= tick) recent.push(events[next++]);
      const agents = byTick.get(tick)!;
      const first = records.find((r) => r.kind === 'tick' && r.tick === tick);
      this.frames.push({
        schemaVersion: 'nlt.observer-trace.v1',
        tick,
        simTimeIso: '',
        scene: { id: agents[0].scene, kind: first && first.kind === 'tick' && first.scene.kind === 'interior' ? 'interior' : 'open_world' },
        agents,
        pairs: [],
        burnoutEpisodes: [],
        selfRecognitions: [],
        events: recent.slice(-EVENTS_SHOWN),
      });
    }
  }

  close(): void {}
  frameCount(): number { return this.frames.length; }
  frame(i: number): StateFeedDoc { return this.frames[Math.max(0, Math.min(this.frames.length - 1, i))]; }
  diagnostics(): string[] { return this.diag; }
  /** Frames are sampled at the header's cadenceHz, so 1× plays them at that rate. */
  framesPerSecond(): number { return this.cadenceHz; }
}
