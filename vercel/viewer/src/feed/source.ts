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
}
