// Observer-side control for starting and stopping an engine run.
//
// The viewer only asks. /api/run decides whether a sandbox may start, and the Godot engine
// inside it stays the authority. Nothing here draws or simulates; the view is still driven by
// the replay or recording selected above, because no authenticated live relay exists yet.

export type RunState = 'idle' | 'starting' | 'running' | 'stopping' | 'unavailable';

export interface RunStatus {
  state: RunState;
  note?: string;
  /** The call failed for now (network, or the sandbox API); keep the last known state. */
  transient?: boolean;
}

const POLL_MS = 4000;

const LABEL: Record<RunState, string> = {
  idle: 'Start run',
  starting: 'Starting run…',
  running: 'Stop run',
  stopping: 'Stopping run…',
  unavailable: 'Run control: unavailable',
};

const TITLE: Record<RunState, string> = {
  idle: 'Ask the engine to start a run. The view does not show it live yet.',
  starting: 'The engine run is starting.',
  running: 'An engine run is active. Stop it.',
  stopping: 'The engine run is stopping.',
  unavailable: 'Run control is off on this deployment.',
};

// What a screen reader hears when the state changes (the button label is an action, not a status).
const ANNOUNCE: Record<RunState, string> = {
  idle: 'No engine run is active.',
  starting: 'The engine run is starting.',
  running: 'An engine run is active.',
  stopping: 'The engine run is stopping.',
  unavailable: 'Run control is unavailable.',
};

const KNOWN: ReadonlySet<string> = new Set(['idle', 'starting', 'running', 'stopping']);

async function call(method: 'GET' | 'POST' | 'DELETE', fetchImpl: typeof fetch): Promise<RunStatus> {
  let res: Response;
  try {
    res = await fetchImpl('/api/run', {
      method,
      headers: method === 'GET' ? undefined : { 'x-nlt-run': '1' },
      cache: 'no-store',
    });
  } catch {
    return { state: 'unavailable', note: 'Could not reach the run control.', transient: true };
  }

  let body: { state?: string; error?: string } = {};
  try {
    body = await res.json();
  } catch {
    // Not JSON: the dev server or a static host has no /api.
  }

  if (res.status === 503 && body.error === 'run_control_disabled') {
    return { state: 'unavailable', note: 'Run control is off on this deployment.' };
  }
  if (typeof body.state === 'string' && KNOWN.has(body.state)) {
    // 200/202 carry the new state; 409 carries the state of the run already active.
    return { state: body.state as RunState };
  }
  if (res.status === 403) return { state: 'unavailable', note: 'This page is not allowed to control runs.' };
  if (body.error === 'run_control_failed') {
    return { state: 'unavailable', note: 'The engine could not be reached. Try again.', transient: true };
  }
  // 404 and non-JSON answers: a static host or `vite dev`, where /api does not exist.
  return { state: 'unavailable', note: 'Run control needs the deployed viewer.' };
}

export interface RunControl {
  refresh(): Promise<void>;
}

export function initRunControl(
  button: HTMLButtonElement,
  announce: (message: string) => void,
  fetchImpl: typeof fetch = fetch,
): RunControl {
  let state: RunState = 'unavailable';
  let busy = false;
  let timer: number | undefined;
  let first = true; // the first answer is the page loading, not a change worth announcing

  const blocked = (): boolean => state === 'unavailable' || state === 'starting' || state === 'stopping';

  function render(result: RunStatus): void {
    // A transient failure keeps what we last knew, so one bad poll does not turn the button off.
    const next: RunStatus = result.transient ? { state, note: result.note } : result;
    const changed = next.state !== state || (result.transient === true && next.note !== undefined);
    state = next.state;
    button.dataset.state = state;
    button.textContent = '';
    const dot = document.createElement('span');
    dot.className = 'dot';
    dot.setAttribute('aria-hidden', 'true');
    button.append(dot, LABEL[state]);
    button.title = next.note ?? TITLE[state];
    button.disabled = busy || blocked();
    if (changed && !first) announce(next.note ?? ANNOUNCE[state]);
    first = false;

    window.clearTimeout(timer);
    if (state !== 'idle' && state !== 'unavailable') timer = window.setTimeout(() => void refresh(), POLL_MS);
  }

  async function refresh(): Promise<void> {
    if (document.hidden) {
      // Check again when the tab is back instead of polling in the background.
      timer = window.setTimeout(() => void refresh(), POLL_MS);
      return;
    }
    render(await call('GET', fetchImpl));
  }

  button.addEventListener('click', async () => {
    if (busy) return;
    if (state !== 'idle' && state !== 'running') return;
    busy = true;
    button.disabled = true;
    try {
      render(await call(state === 'idle' ? 'POST' : 'DELETE', fetchImpl));
    } finally {
      busy = false;
      button.disabled = blocked();
    }
  });

  void refresh();
  return { refresh };
}
