// A started engine run, read while it happens: a FeedSource that polls /api/run/trace for the
// new lines of the run's nlt.observer-trace.v1 file and adds them to the same frame builder a
// recorded file uses.
//
// This is near-live, a few seconds behind, not a stream. The run writes its trace inside a
// sandbox that exposes no port; /api/run/trace is the only way out and it only reads. Like any
// trace it carries positions and decisions only: no needs, states or readiness (those are
// Fusion's). Nothing is inferred.
//
// Kept to erasable TypeScript (no parameter properties or enums) so Node can run it in the tests.
import { parseChunk, parseHeaderLine } from '../trace/chunk';
import type { TraceHeader } from '../trace/types';
import type { FeedSource, SourceInfo } from './source';
import { TraceFrames } from './traceFrames';
import type { StateFeedDoc } from './types';

export interface LiveRunOptions {
  fetch?: typeof fetch;
  /** Milliseconds between polls while the run is quiet. */
  pollMs?: number;
  /** Waits; replaced in tests so they need no real time. */
  wait?: (ms: number) => Promise<void>;
  /** How long open() waits for the engine's first tick before giving up. */
  firstDataTimeoutMs?: number;
  /** Called when frames were added or the run ended, so the player can update. */
  onChange?: () => void;
}

interface TraceReply {
  state?: string;
  text?: string;
  next?: number;
  more?: boolean;
  error?: string;
}

const MISSED_POLLS_BEFORE_GIVING_UP = 5;

export class LiveRunSource implements FeedSource {
  info: SourceInfo = {
    kind: 'live',
    content: 'physical-trace',
    id: 'live-run',
    title: 'Live run',
    status: 'idle',
    provenance: 'Live engine run, a few seconds behind',
  };

  private fetchImpl: typeof fetch;
  private pollMs: number;
  private wait: (ms: number) => Promise<void>;
  private firstDataTimeoutMs: number;
  private onChange: () => void;

  private built: TraceFrames | null = null;
  private header: TraceHeader | null = null;
  private headerLine = '';
  private offset = 0;
  private lines = 0;
  private diag: string[] = [];
  private growing = true;
  private closed = false;
  private missed = 0;

  constructor(options: LiveRunOptions = {}) {
    this.fetchImpl = options.fetch ?? fetch;
    this.pollMs = options.pollMs ?? 2000;
    this.wait = options.wait ?? ((ms) => new Promise((r) => setTimeout(r, ms)));
    this.firstDataTimeoutMs = options.firstDataTimeoutMs ?? 30_000;
    this.onChange = options.onChange ?? (() => {});
  }

  /** Resolves once the engine has written its first tick, then keeps polling in the background. */
  async open(): Promise<void> {
    this.info.status = 'loading';
    const started = Date.now();
    try {
      while (this.frameCount() === 0) {
        if (this.closed) throw new Error('Closed before the run produced anything.');
        const state = await this.pollOnce();
        if (this.frameCount() > 0) break;
        if (state === 'idle') throw new Error('No engine run is active.');
        if (Date.now() - started >= this.firstDataTimeoutMs) {
          throw new Error('The engine has not written any ticks yet. Try again in a moment.');
        }
        await this.wait(this.pollMs);
      }
    } catch (e) {
      this.info.status = 'error';
      this.info.detail = e instanceof Error ? e.message : String(e);
      this.growing = false;
      throw e;
    }
    this.info.status = 'ready';
    this.following = this.follow();
  }

  private following: Promise<void> = Promise.resolve();

  /** Resolves when the background polling has stopped (the run ended, was closed, or contact was lost). */
  untilEnded(): Promise<void> {
    return this.following;
  }

  private inflight: Promise<string> | null = null;

  /** One request. Returns the run's state as the server reported it. Calls never overlap: a second
   *  caller waits for the request already under way, so the same bytes are never read twice. */
  pollOnce(): Promise<string> {
    if (!this.inflight) {
      this.inflight = this.poll().finally(() => {
        this.inflight = null;
      });
    }
    return this.inflight;
  }

  private async poll(): Promise<string> {
    let reply: TraceReply;
    try {
      const res = await this.fetchImpl(`/api/run/trace?from=${this.offset}`, { cache: 'no-store' });
      reply = (await res.json()) as TraceReply;
      if (res.status === 503 && reply.error === 'run_control_disabled') throw new Error('Run control is off on this deployment.');
      if (!res.ok) throw new Error(reply.error ? `The run could not be read (${reply.error}).` : `The run could not be read (HTTP ${res.status}).`);
    } catch (e) {
      this.missed++;
      if (this.frameCount() === 0 || this.missed >= MISSED_POLLS_BEFORE_GIVING_UP) {
        if (this.frameCount() > 0) this.end('Lost contact with the run.');
        throw e;
      }
      return 'unreachable';
    }
    this.missed = 0;

    if (typeof reply.text === 'string' && reply.text !== '') this.ingest(reply.text);
    if (typeof reply.next === 'number') this.offset = reply.next;

    const state = reply.state ?? 'idle';
    if (state === 'idle' && this.frameCount() > 0) this.end();
    this.pendingMore = reply.more === true;
    return state;
  }

  private pendingMore = false;

  private ingest(text: string): void {
    let body = text;
    if (this.header === null) {
      const cut = text.indexOf('\n');
      if (cut === -1) return; // the server only sends whole lines; wait for the rest
      this.headerLine = text.slice(0, cut);
      const parsed = parseHeaderLine(this.headerLine);
      if (parsed.errors.length > 0) throw new Error(parsed.errors.join(' '));
      this.header = parsed.header;
      this.built = new TraceFrames(parsed.header);
      this.lines = 1;
      this.info.provenance = `Live engine run, a few seconds behind (Godot ${parsed.header.godotVersion || '?'}, engine ${parsed.header.engineCommit || '?'}) — positions and decisions only`;
      this.info.detail = `Run ${parsed.header.runId || '?'}, started ${parsed.header.startTime || '?'}. Read from the running engine's nlt.observer-trace.v1 file; Fusion's needs, states and readiness are not in it.`;
      body = text.slice(cut + 1);
    }
    const chunk = parseChunk(this.headerLine, body, this.lines);
    this.lines += chunk.lines;
    this.diag.push(...chunk.diagnostics);
    this.built!.add(chunk.records);
    this.onChange();
  }

  /** The background loop: poll until the run ends, the source is closed, or contact is lost. */
  private async follow(): Promise<void> {
    while (this.growing && !this.closed) {
      await this.wait(this.pendingMore ? 0 : this.pollMs);
      if (this.closed || !this.growing) return;
      try {
        await this.pollOnce();
      } catch {
        return; // pollOnce has already ended the source with the reason
      }
    }
  }

  private end(reason?: string): void {
    if (!this.growing) return;
    this.growing = false;
    this.built?.finish(); // the newest tick can no longer get more agents
    this.info.provenance = 'Engine run that has ended — positions and decisions only; not live';
    if (reason) this.info.detail = reason;
    this.onChange();
  }

  /**
   * Reads whatever the engine has written that has not been read yet. The page calls this just
   * before it asks for the run to stop, since a stopped run cannot be read again.
   */
  async drain(): Promise<void> {
    if (!this.growing) return;
    for (let i = 0; i < 20; i++) {
      try {
        await this.pollOnce();
      } catch {
        return;
      }
      if (!this.pendingMore) {
        // One more, in case lines landed while the last request was in flight.
        try { await this.pollOnce(); } catch { /* the stop goes ahead regardless */ }
        return;
      }
    }
  }

  /** True while the run may still add frames, so the player waits at the end instead of stopping. */
  isGrowing(): boolean {
    return this.growing;
  }

  close(): void {
    this.closed = true;
    this.growing = false;
  }

  frameCount(): number {
    return this.built?.count() ?? 0;
  }

  frame(i: number): StateFeedDoc {
    const n = this.frameCount();
    return this.built!.frame(Math.max(0, Math.min(n - 1, i)));
  }

  diagnostics(): string[] {
    return [...this.diag, ...(this.built?.problems ?? [])];
  }

  framesPerSecond(): number {
    return this.header && this.header.cadenceHz > 0 ? this.header.cadenceHz : 10;
  }
}
