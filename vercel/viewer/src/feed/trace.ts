// A recorded Godot engine run (nlt.observer-trace.v1, docs/contracts/observer-trace-v1.md) as a
// FeedSource, so the 3D view can replay a headless run on the real island.
//
// A trace is physical only: positions, velocities, scenes and the agent loop's decisions. It has no
// needs, levels, named state or Fusion gate — those are Fusion's and are not in the file — so the
// agents here carry none, and the UI says so rather than drawing bars. Nothing is inferred.
import { parseTrace } from '../trace/parser';
import type { ParsedRecord, TraceHeader } from '../trace/types';
import type { FeedSource, SourceInfo } from './source';
import { TraceFrames } from './traceFrames';
import type { StateFeedDoc } from './types';

/** The real headless run bundled with the viewer (fixtures/observer-trace/README.md). */
export const TRACE_SAMPLE = { id: 'sample', url: 'godot/fixtures/observer-trace-sample.jsonl', label: 'Headless engine run — sample' };

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
    const built = new TraceFrames(header);
    built.add(records);
    built.finish();
    this.frames = built.all();
    this.diag.push(...built.problems);
  }

  close(): void {}
  frameCount(): number { return this.frames.length; }
  frame(i: number): StateFeedDoc { return this.frames[Math.max(0, Math.min(this.frames.length - 1, i))]; }
  diagnostics(): string[] { return this.diag; }
  /** Frames are sampled at the header's cadenceHz, so 1× plays them at that rate. */
  framesPerSecond(): number { return this.cadenceHz; }
}
