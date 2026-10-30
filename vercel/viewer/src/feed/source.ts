// The transport boundary. Every source says what it is, so the UI can never
// present authored fixtures or static scene data as live simulation output.
import type { StateFeedDoc } from './types';

/**
 * - `replay`:  an authored nlt.state-feed.replay.v1 bundle (no policy produced it)
 * - `live`:    an authorised observer relay carrying Godot/Fusion state (not yet built)
 */
export type SourceKind = 'replay' | 'live';
export type SourceStatus = 'idle' | 'loading' | 'ready' | 'unavailable' | 'error';

export interface SourceInfo {
  kind: SourceKind;
  id: string;
  title: string;
  status: SourceStatus;
  /** Plain-language provenance shown to the observer. */
  provenance: string;
  detail?: string;
  /**
   * What the frames carry. `physical-trace` (a recorded engine run, feed/trace.ts) has positions
   * and decisions but none of Fusion's semantic fields, so the UI must not show needs or state.
   * Absent means full nlt.state-feed.v1 documents.
   */
  content?: 'state-feed' | 'physical-trace';
}

export interface FeedSource {
  readonly info: SourceInfo;
  /** Resolves when frames are available, or rejects with a reason the UI shows verbatim. */
  open(): Promise<void>;
  close(): void;
  frameCount(): number;
  frame(i: number): StateFeedDoc;
  /** Per-frame contract problems; rejected frames are reported, never rendered. */
  diagnostics(): string[];
  /** Frames per second at 1× playback. Absent means 1, the replay bundles' ~1 Hz. */
  framesPerSecond?(): number;
  /** True while frames may still be added (a run in progress). The player then waits at the last
   *  frame instead of stopping, and keeps its scrubber and timeline up to date. Absent means fixed. */
  isGrowing?(): boolean;
}
