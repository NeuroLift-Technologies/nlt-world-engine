import type { FeedSource, SourceInfo } from './source';
import { REPLAY_V1, STATE_FEED_V1, validateDoc, type ReplayBundle, type StateFeedDoc } from './types';

export interface ReplayEntry { id: string; url: string; label: string }

/** The Godot project's own replay fixtures (world-engine-godot/fixtures/replay/). */
export const REPLAYS: ReplayEntry[] = [
  { id: 'open-world-day', url: 'godot/fixtures/open-world-day.json', label: 'Open world — a walk out of the settlement' },
  { id: 'stayalert-day', url: 'godot/fixtures/stayalert-day.json', label: 'StayAlert — one working morning' },
  { id: 'rescue-only', url: 'godot/fixtures/rescue-only.json', label: 'Needed rescue — one episode' },
  { id: 'collapse-only', url: 'godot/fixtures/collapse-only.json', label: 'Repeated collapse — three episodes' },
];

/** Mirrors Feed/FixtureFeedSource.cs: a single document or a replay bundle of complete documents. */
export class ReplaySource implements FeedSource {
  info: SourceInfo;
  private frames: StateFeedDoc[] = [];
  private diag: string[] = [];

  constructor(private entry: ReplayEntry) {
    this.info = { kind: 'replay', id: entry.id, title: entry.label, status: 'idle', provenance: 'Authored fixture' };
  }

  async open(): Promise<void> {
    this.info.status = 'loading';
    try {
      const res = await fetch(this.entry.url);
      if (!res.ok) throw new Error(`HTTP ${res.status} loading ${this.entry.url}`);
      const raw = (await res.json()) as ReplayBundle | StateFeedDoc;
      const docs = raw.schemaVersion === REPLAY_V1 ? (raw as ReplayBundle).frames : [raw as StateFeedDoc];
      if (raw.schemaVersion !== REPLAY_V1 && raw.schemaVersion !== STATE_FEED_V1)
        throw new Error(`unknown schemaVersion ${raw.schemaVersion}`);
      if (raw.schemaVersion === REPLAY_V1) {
        const b = raw as ReplayBundle;
        this.info.title = b.title || this.info.title;
        this.info.detail = b.provenance?.note;
        this.info.provenance = b.provenance?.authored === false ? 'Recorded replay' : 'Authored fixture — no policy produced these frames';
      }
      docs.forEach((d, i) => {
        const v = validateDoc(d);
        if (!v.ok) this.diag.push(`frame ${i}: rejected — ${v.error}`);
        else {
          v.warnings.forEach((w) => this.diag.push(`frame ${i}: ${w}`));
          this.frames.push(d);
        }
      });
      if (!this.frames.length) throw new Error('no valid frames');
      this.info.status = 'ready';
    } catch (e) {
      this.info.status = 'error';
      this.info.detail = e instanceof Error ? e.message : String(e);
      throw e;
    }
  }
  close(): void {}
  frameCount(): number { return this.frames.length; }
  frame(i: number): StateFeedDoc { return this.frames[Math.max(0, Math.min(this.frames.length - 1, i))]; }
  diagnostics(): string[] { return this.diag; }
}
