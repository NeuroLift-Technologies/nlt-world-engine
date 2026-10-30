import { Sandbox } from '@vercel/sandbox';
import { maxRunMs, sandboxVcpus, TRACE_CHUNK_BYTES, TRACE_PATH } from './run-config.js';
import type { RunInfo, RunPort } from './run-control.js';

// A run is one Vercel Sandbox started from the engine image, with headless Godot as its process.
// Sandboxes are found by tag, not by instance, so start, stop and status always see the same run.

const TAG = { app: 'nlt-world-engine-run' } as const;
// Mirrors the image's own runtime settings; Sandbox does not run the image's ENTRYPOINT or CMD.
const GODOT_ARGS = ['--headless', '--path', '/app/world-engine-godot', '--audio-driver', 'Dummy'];
const GODOT_ENV = {
  GODOT_SILENCE_ROOT_WARNING: '1',
  DOTNET_EnableDiagnostics: '0',
  NLT_AGENT_LOOP_ENABLED: '0',
  NLT_OBSERVER_TRACE: TRACE_PATH, // the engine flushes one line at a time
};

type SandboxStatus = 'pending' | 'running' | 'stopping' | 'stopped' | 'failed' | 'aborted' | 'snapshotting';

function toState(status: SandboxStatus): RunInfo['state'] | null {
  switch (status) {
    case 'pending':
      return 'starting';
    case 'running':
      return 'running';
    case 'stopping':
    case 'snapshotting':
      return 'stopping';
    default:
      return null; // stopped, failed, aborted: nothing is running
  }
}

export function sandboxPort(env: Record<string, string | undefined>): RunPort {
  return {
    async listActive() {
      const runs: RunInfo[] = [];
      const page = await Sandbox.list({ tags: TAG });
      for await (const s of page) {
        const state = toState(s.status);
        if (state) runs.push({ id: s.name, state, createdAt: s.createdAt });
      }
      return runs;
    },

    async start() {
      const image = env.NLT_SANDBOX_IMAGE;
      if (!image) throw new Error('NLT_SANDBOX_IMAGE is not set');

      // No ports are exposed: the sandbox has no public URL. A live feed needs its own
      // authenticated, read-only relay (vercel/transport/README.md).
      const sandbox = await Sandbox.create({
        name: `nlt-run-${Date.now()}`,
        image,
        timeout: maxRunMs(env),
        resources: { vcpus: sandboxVcpus(env) },
        tags: { ...TAG },
      });

      try {
        await sandbox.runCommand({ cmd: 'godot', args: GODOT_ARGS, env: GODOT_ENV, detached: true });
      } catch (err) {
        await sandbox.stop().catch(() => undefined);
        throw err;
      }

      return {
        id: sandbox.name,
        state: 'running',
        createdAt: Date.now(),
        expiresAt: sandbox.expiresAt?.getTime(),
      };
    },

    async stop(id: string) {
      const sandbox = await Sandbox.get({ name: id });
      await sandbox.stop();
    },

    async readTrace(id: string, from: number) {
      const sandbox = await Sandbox.get({ name: id });
      // Offsets are validated integers and the path is a constant; both go in as arguments, never into the script.
      const result = await sandbox.runCommand({
        cmd: 'sh',
        args: ['-c', 'tail -c +"$1" "$2" 2>/dev/null | head -c "$3"', 'sh', String(from + 1), TRACE_PATH, String(TRACE_CHUNK_BYTES)],
      });
      const raw = await result.stdout();
      // Hand back whole lines only. Anything after the last newline is a half-written line or a cut
      // multi-byte character; it is read again next time because `next` stops at the newline.
      const end = raw.lastIndexOf('\n');
      const text = end === -1 ? '' : raw.slice(0, end + 1);
      return { text, next: from + Buffer.byteLength(text, 'utf8'), more: Buffer.byteLength(raw, 'utf8') >= TRACE_CHUNK_BYTES };
    },
  };
}
