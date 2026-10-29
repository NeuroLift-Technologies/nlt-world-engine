import type { FeedSource, SourceInfo } from './source';
import type { StateFeedDoc } from './types';

/**
 * Placeholder for the authorised observer relay (vercel/transport/README.md).
 *
 * Deliberately not implemented. The Godot app has no server of its own; the planned
 * Python sidecar owns HTTP 8765 / WS 8766 on loopback (DEPLOYMENT.md), and the
 * agent-loop endpoint is loopback-only by design. A browser on Vercel cannot and
 * must not reach either. Until a signed, read-only relay exists, this source reports
 * itself unavailable rather than pretending to connect.
 */
export class LiveRelaySource implements FeedSource {
  info: SourceInfo = {
    kind: 'live',
    id: 'live',
    title: 'Live simulation',
    status: 'unavailable',
    provenance: 'Godot World Engine via an authorised observer relay',
    detail:
      'No observer relay is deployed. Live viewing needs a read-only, authenticated relay that ' +
      'carries nlt.state-feed.v1 documents from the Godot/Fusion runtime to browsers. The ' +
      'loopback agent-loop endpoint must never be exposed for this.',
  };
  async open(): Promise<void> {
    throw new Error(this.info.detail);
  }
  close(): void {}
  frameCount(): number { return 0; }
  frame(): StateFeedDoc { throw new Error('live source unavailable'); }
  diagnostics(): string[] { return []; }
}
