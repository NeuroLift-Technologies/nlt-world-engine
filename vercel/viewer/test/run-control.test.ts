import assert from 'node:assert/strict';
import { describe, it } from 'node:test';
import { controlEnabled, handleRunRequest } from '../api/_lib/run-control.ts';
import type { ControlRequest, RunInfo, RunPort } from '../api/_lib/run-control.ts';

const HOST = 'viewer.example.com';

function req(method: string, headers: Record<string, string> = {}): ControlRequest {
  const lower = Object.fromEntries(Object.entries(headers).map(([k, v]) => [k.toLowerCase(), v]));
  return { method, header: (name) => lower[name.toLowerCase()] ?? null };
}

const sameOrigin = { host: HOST, origin: `https://${HOST}`, 'x-nlt-run': '1' };

/** In-memory stand-in for the Sandbox adapter. `hideFirst` makes the first N listings look empty. */
function fakePort(initial: RunInfo[] = [], hideFirst = 0) {
  const runs = [...initial];
  let clock = 100;
  let listCalls = 0;
  const stopped: string[] = [];
  const port: RunPort = {
    async listActive() {
      listCalls += 1;
      return listCalls <= hideFirst ? [] : runs.filter((r) => !stopped.includes(r.id));
    },
    async start() {
      clock += 1;
      const run: RunInfo = { id: `run-${clock}`, state: 'running', createdAt: clock };
      runs.push(run);
      return run;
    },
    async stop(id) {
      stopped.push(id);
    },
  };
  return { port, stopped, runs };
}

const running = (id: string, createdAt: number): RunInfo => ({ id, state: 'running', createdAt });

describe('controlEnabled', () => {
  it('is off unless explicitly enabled', () => {
    assert.equal(controlEnabled({}), false);
    assert.equal(controlEnabled({ NLT_RUN_CONTROL: 'true' }), false);
    assert.equal(controlEnabled({ NLT_RUN_CONTROL: 'enabled' }), true);
  });
});

describe('handleRunRequest', () => {
  it('returns 503 for every method when disabled', async () => {
    const { port } = fakePort();
    for (const method of ['GET', 'POST', 'DELETE']) {
      const res = await handleRunRequest(req(method, sameOrigin), false, port);
      assert.equal(res.status, 503);
    }
  });

  it('GET reports idle, then the active run', async () => {
    const idle = await handleRunRequest(req('GET'), true, fakePort().port);
    assert.deepEqual(idle.body, { state: 'idle', run: null });

    const run = running('run-1', 1);
    const busy = await handleRunRequest(req('GET'), true, fakePort([run]).port);
    assert.equal(busy.body.state, 'running');
    assert.deepEqual(busy.body.run, run);
  });

  it('rejects other methods with 405', async () => {
    const res = await handleRunRequest(req('PUT', sameOrigin), true, fakePort().port);
    assert.equal(res.status, 405);
    assert.equal(res.headers?.allow, 'GET, POST, DELETE');
  });

  describe('same-origin guard', () => {
    it('refuses POST and DELETE without the intent header', async () => {
      for (const method of ['POST', 'DELETE']) {
        const { port, runs } = fakePort();
        const res = await handleRunRequest(req(method, { host: HOST, origin: `https://${HOST}` }), true, port);
        assert.equal(res.status, 403);
        assert.equal(runs.length, 0);
      }
    });

    it('refuses a cross-site Origin', async () => {
      const { port, runs } = fakePort();
      const res = await handleRunRequest(
        req('POST', { host: HOST, origin: 'https://evil.example', 'x-nlt-run': '1' }),
        true,
        port,
      );
      assert.equal(res.status, 403);
      assert.equal(runs.length, 0);
    });

    it('refuses an unparseable Origin', async () => {
      const res = await handleRunRequest(
        req('POST', { host: HOST, origin: 'not a url', 'x-nlt-run': '1' }),
        true,
        fakePort().port,
      );
      assert.equal(res.status, 403);
    });

    it('prefers x-forwarded-host when present', async () => {
      const res = await handleRunRequest(
        req('POST', { host: 'internal.local', 'x-forwarded-host': HOST, origin: `https://${HOST}`, 'x-nlt-run': '1' }),
        true,
        fakePort().port,
      );
      assert.equal(res.status, 202);
    });

    it('allows a request with no Origin header when the intent header is set', async () => {
      const res = await handleRunRequest(req('POST', { 'x-nlt-run': '1' }), true, fakePort().port);
      assert.equal(res.status, 202);
    });
  });

  describe('start', () => {
    it('starts one run and answers 202', async () => {
      const { port, runs } = fakePort();
      const res = await handleRunRequest(req('POST', sameOrigin), true, port);
      assert.equal(res.status, 202);
      assert.equal(res.body.state, 'running');
      assert.equal(runs.length, 1);
    });

    it('answers 409 and starts nothing when a run is already active', async () => {
      const { port, runs } = fakePort([running('run-1', 1)]);
      const res = await handleRunRequest(req('POST', sameOrigin), true, port);
      assert.equal(res.status, 409);
      assert.equal(res.body.error, 'run_in_progress');
      assert.equal(runs.length, 1);
    });

    it('also treats a run that is stopping as in progress', async () => {
      const { port } = fakePort([{ id: 'run-1', state: 'stopping', createdAt: 1 }]);
      const res = await handleRunRequest(req('POST', sameOrigin), true, port);
      assert.equal(res.status, 409);
    });

    it('stops the newer run when two starts race, so only one simulation survives', async () => {
      // Both requests see "nothing running" on their first check.
      const { port, stopped, runs } = fakePort([], 2);
      const [a, b] = await Promise.all([
        handleRunRequest(req('POST', sameOrigin), true, port),
        handleRunRequest(req('POST', sameOrigin), true, port),
      ]);
      assert.deepEqual([a.status, b.status].sort(), [202, 409]);
      assert.equal(runs.length, 2);
      assert.equal(stopped.length, 1);
      assert.equal(stopped[0], 'run-102', 'the newer run is the one stopped');
    });
  });

  describe('stop', () => {
    it('is a success when nothing is running', async () => {
      const { port, stopped } = fakePort();
      const res = await handleRunRequest(req('DELETE', sameOrigin), true, port);
      assert.equal(res.status, 200);
      assert.equal(res.body.state, 'idle');
      assert.equal(stopped.length, 0);
    });

    it('stops the active run and answers 202', async () => {
      const { port, stopped } = fakePort([running('run-1', 1)]);
      const res = await handleRunRequest(req('DELETE', sameOrigin), true, port);
      assert.equal(res.status, 202);
      assert.equal(res.body.state, 'stopping');
      assert.deepEqual(stopped, ['run-1']);
    });

    it('does not stop a run that is already stopping', async () => {
      const { port, stopped } = fakePort([{ id: 'run-1', state: 'stopping', createdAt: 1 }]);
      const res = await handleRunRequest(req('DELETE', sameOrigin), true, port);
      assert.equal(res.status, 202);
      assert.equal(stopped.length, 0);
    });

    it('stops every active run if a race ever left more than one', async () => {
      const { port, stopped } = fakePort([running('run-1', 1), running('run-2', 2)]);
      await handleRunRequest(req('DELETE', sameOrigin), true, port);
      assert.deepEqual(stopped.sort(), ['run-1', 'run-2']);
    });
  });
});
