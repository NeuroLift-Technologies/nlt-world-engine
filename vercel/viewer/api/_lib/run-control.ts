// Request handling for the observer's "run" control (start / stop / status).
//
// This file knows nothing about Vercel or the Sandbox SDK: it takes a `RunPort` and returns
// plain results, so the rules below (single run, idempotent stop, same-origin guard) are
// testable without a network. The viewer only *requests* a start or stop. The Godot engine
// stays the authority over what runs inside the sandbox.

export type RunState = 'idle' | 'starting' | 'running' | 'stopping';

export interface RunInfo {
  id: string;
  state: Exclude<RunState, 'idle'>;
  createdAt: number;
  expiresAt?: number;
}

export interface RunPort {
  /** Runs that are starting, running or stopping, in any order. */
  listActive(): Promise<RunInfo[]>;
  start(): Promise<RunInfo>;
  stop(id: string): Promise<void>;
}

export interface ControlRequest {
  method: string;
  header(name: string): string | null;
}

export interface ControlResult {
  status: number;
  body: Record<string, unknown>;
  headers?: Record<string, string>;
}

/** Operator opt-in. Without it the control is off, so a fresh deploy can never start a run. */
export function controlEnabled(env: Record<string, string | undefined>): boolean {
  return env.NLT_RUN_CONTROL === 'enabled';
}

function newest(runs: RunInfo[]): RunInfo | undefined {
  return [...runs].sort((a, b) => b.createdAt - a.createdAt || (a.id < b.id ? 1 : -1))[0];
}

function oldest(runs: RunInfo[]): RunInfo | undefined {
  return [...runs].sort((a, b) => a.createdAt - b.createdAt || (a.id < b.id ? -1 : 1))[0];
}

/**
 * State-changing requests must come from our own page: a custom header (which forces a CORS
 * preflight for cross-site callers) and, when the browser sends one, a matching Origin.
 * This is not user authentication. Who may press the button is decided by the deployment's
 * protection (see README); the endpoint stays off until the operator enables it.
 */
function sameOriginIntent(req: ControlRequest): boolean {
  if (req.header('x-nlt-run') !== '1') return false;
  const origin = req.header('origin');
  if (origin === null) return true;
  const host = req.header('x-forwarded-host') ?? req.header('host');
  if (host === null) return false;
  try {
    return new URL(origin).host === host;
  } catch {
    return false;
  }
}

export async function handleRunRequest(
  req: ControlRequest,
  enabled: boolean,
  port: RunPort,
): Promise<ControlResult> {
  if (!enabled) {
    return { status: 503, body: { error: 'run_control_disabled' } };
  }

  const method = req.method.toUpperCase();

  if (method === 'GET') {
    const run = newest(await port.listActive());
    return { status: 200, body: { state: run ? run.state : 'idle', run: run ?? null } };
  }

  if (method !== 'POST' && method !== 'DELETE') {
    return { status: 405, body: { error: 'method_not_allowed' }, headers: { allow: 'GET, POST, DELETE' } };
  }

  if (!sameOriginIntent(req)) {
    return { status: 403, body: { error: 'forbidden' } };
  }

  if (method === 'POST') {
    const active = await port.listActive();
    if (active.length > 0) {
      const run = newest(active)!;
      return { status: 409, body: { error: 'run_in_progress', state: run.state, run } };
    }

    const started = await port.start();

    // Two requests can pass the check above together. The older run wins; the newer one stops
    // itself, so a double press never leaves two simulations running.
    const after = await port.listActive();
    const winner = oldest(after);
    if (winner && winner.id !== started.id) {
      await port.stop(started.id);
      return { status: 409, body: { error: 'run_in_progress', state: winner.state, run: winner } };
    }
    return { status: 202, body: { state: started.state, run: started } };
  }

  // DELETE: stop is idempotent. Nothing running is a success, not an error.
  const active = await port.listActive();
  if (active.length === 0) {
    return { status: 200, body: { state: 'idle', run: null } };
  }
  const toStop = active.filter((r) => r.state !== 'stopping');
  for (const run of toStop) await port.stop(run.id);
  return { status: 202, body: { state: 'stopping', run: newest(active) ?? null } };
}
