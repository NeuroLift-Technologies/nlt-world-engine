import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { describe, it } from 'node:test';
import { handleTraceRequest } from '../api/_lib/run-control.ts';
import type { RunInfo, RunPort } from '../api/_lib/run-control.ts';
import { readWholeLines } from '../api/_lib/trace-read.ts';
import { LiveRunSource } from '../src/feed/liveRun.ts';
import { TraceFrames } from '../src/feed/traceFrames.ts';
import { parseTrace } from '../src/trace/parser.ts';

const SAMPLE = Buffer.from(readFileSync(new URL('../../../fixtures/observer-trace/sample.jsonl', import.meta.url), 'utf8'), 'utf8');

type ServerState = 'starting' | 'running' | 'stopping' | 'idle';

/** The run ends only once the viewer has read everything the engine wrote (a real stop would lose the rest). */
const endWhenRead = (run: { released: number; consumed: number; state: ServerState }) => {
  if (run.released >= SAMPLE.length && run.consumed >= SAMPLE.length) run.state = 'idle';
};

/** The real /api/run/trace handler on top of an in-memory "sandbox" whose trace file grows. */
function fakeRun(limitBytes = 4000) {
  const run = { released: 0, consumed: 0, state: 'running' as ServerState, requests: [] as number[] };
  const port: RunPort = {
    async listActive() {
      return run.state === 'idle' ? [] : [{ id: 'run-1', state: run.state, createdAt: 1 } as RunInfo];
    },
    async start() { throw new Error('not used'); },
    async stop() { throw new Error('not used'); },
    async readTrace(_id, from) {
      run.requests.push(from);
      const chunk = await readWholeLines(
        async (limit) => SAMPLE.subarray(from, Math.min(run.released, from + limit)).toString('utf8'),
        from,
        limitBytes,
      );
      run.consumed = Math.max(run.consumed, chunk.next);
      return chunk;
    },
  };
  const fetchImpl = (async (url: string) => {
    const from = new URL(url, 'https://viewer.example').searchParams.get('from');
    const res = await handleTraceRequest({ method: 'GET', header: () => null }, true, port, from);
    return { ok: res.status >= 200 && res.status < 300, status: res.status, json: async () => res.body };
  }) as unknown as typeof fetch;
  return { run, fetchImpl };
}

describe('LiveRunSource against the real trace route', () => {
  it('shows the same frames as the recorded file once the run has been read to the end', async () => {
    const { run, fetchImpl } = fakeRun();
    const waits: number[] = [];
    // Each wait is time passing: the engine writes another slice of its trace.
    const wait = async (ms: number) => {
      waits.push(ms);
      run.released = Math.min(SAMPLE.length, run.released + 9000);
      endWhenRead(run);
    };
    run.released = 3000; // enough for the header and some ticks
    const live = new LiveRunSource({ fetch: fetchImpl, wait });
    await live.open();
    assert.equal(live.info.status, 'ready');
    assert.ok(live.frameCount() > 0 && live.isGrowing());
    const early = live.frameCount();

    await live.untilEnded();
    assert.equal(live.isGrowing(), false, 'the run ended');
    assert.ok(live.frameCount() > early, 'frames kept arriving');

    const parsed = parseTrace(SAMPLE.toString('utf8'));
    const whole = new TraceFrames(parsed.header);
    whole.add(parsed.records);
    whole.finish();
    assert.equal(live.frameCount(), whole.count());
    assert.deepEqual(JSON.parse(JSON.stringify(live.frame(0))), JSON.parse(JSON.stringify(whole.frame(0))));
    assert.deepEqual(
      JSON.parse(JSON.stringify(Array.from({ length: live.frameCount() }, (_, i) => live.frame(i)))),
      JSON.parse(JSON.stringify(whole.all())),
    );
    assert.deepEqual(live.diagnostics(), []);
  });

  it('asks for exactly the bytes it has not seen', async () => {
    const { run, fetchImpl } = fakeRun(2500);
    run.released = SAMPLE.length;
    const wait = async () => { endWhenRead(run); };
    const live = new LiveRunSource({ fetch: fetchImpl, wait });
    await live.open();
    await live.untilEnded();
    assert.equal(run.requests[0], 0);
    for (let i = 1; i < run.requests.length; i++) assert.ok(run.requests[i] >= run.requests[i - 1], 'offsets never go back');
    assert.ok(run.requests.length > 3, 'a small limit means several requests');
  });

  it('does not wait between requests while the server says more is ready', async () => {
    const { run, fetchImpl } = fakeRun(2500);
    run.released = SAMPLE.length;
    const waits: number[] = [];
    const wait = async (ms: number) => { waits.push(ms); endWhenRead(run); };
    const live = new LiveRunSource({ fetch: fetchImpl, wait, pollMs: 2000 });
    await live.open();
    await live.untilEnded();
    assert.ok(waits.includes(0), 'catching up polls straight away');
    assert.ok(waits.includes(2000), 'and waits the usual time once caught up');
  });

  it('waits for the first tick, then opens', async () => {
    const { run, fetchImpl } = fakeRun();
    run.state = 'starting';
    let calls = 0;
    const wait = async () => { calls++; if (calls === 2) { run.state = 'running'; run.released = 6000; } };
    const live = new LiveRunSource({ fetch: fetchImpl, wait });
    await live.open();
    assert.ok(calls >= 2);
    assert.ok(live.frameCount() > 0);
    live.close();
  });

  it('refuses to open when no run is active', async () => {
    const { run, fetchImpl } = fakeRun();
    run.state = 'idle';
    const live = new LiveRunSource({ fetch: fetchImpl, wait: async () => {} });
    await assert.rejects(live.open(), /No engine run is active/);
    assert.equal(live.info.status, 'error');
  });

  it('gives up with a clear message if the engine never writes a tick', async () => {
    const { run, fetchImpl } = fakeRun();
    run.released = 0;
    const live = new LiveRunSource({ fetch: fetchImpl, wait: async () => {}, firstDataTimeoutMs: 0 });
    await assert.rejects(live.open(), /has not written any ticks yet/);
  });

  it('reports run control being off instead of waiting', async () => {
    const fetchImpl = (async () => ({ ok: false, status: 503, json: async () => ({ error: 'run_control_disabled' }) })) as unknown as typeof fetch;
    const live = new LiveRunSource({ fetch: fetchImpl, wait: async () => {} });
    await assert.rejects(live.open(), /Run control is off/);
  });

  it('rides out a few failed polls and carries on', async () => {
    const { run, fetchImpl } = fakeRun();
    run.released = SAMPLE.length;
    let failures = 0;
    const flaky = (async (url: string) => {
      if (live.frameCount() > 0 && failures < 3) { failures++; throw new Error('offline'); }
      return fetchImpl(url);
    }) as unknown as typeof fetch;
    const wait = async () => { if (failures >= 3) endWhenRead(run); };
    const live: LiveRunSource = new LiveRunSource({ fetch: flaky, wait });
    await live.open();
    await live.untilEnded();
    assert.equal(failures, 3);
    assert.equal(live.info.detail?.includes('Lost contact'), false);
    assert.ok(live.frameCount() > 500, 'it still read the whole run');
  });

  it('ends with a reason after too many failed polls in a row', async () => {
    const { run, fetchImpl } = fakeRun();
    run.released = 6000;
    const dead = (async (url: string) => {
      if (live.frameCount() > 0) throw new Error('offline');
      return fetchImpl(url);
    }) as unknown as typeof fetch;
    const live: LiveRunSource = new LiveRunSource({ fetch: dead, wait: async () => {} });
    await live.open();
    await live.untilEnded();
    assert.equal(live.isGrowing(), false);
    assert.match(live.info.detail ?? '', /Lost contact/);
    assert.ok(live.frameCount() > 0, 'what was read stays viewable');
  });

  it('stops polling when closed', async () => {
    const { run, fetchImpl } = fakeRun();
    run.released = 6000;
    const waits: number[] = [];
    const live: LiveRunSource = new LiveRunSource({ fetch: fetchImpl, wait: async (ms) => { waits.push(ms); live.close(); } });
    await live.open();
    await live.untilEnded();
    assert.equal(live.isGrowing(), false);
    assert.ok(waits.length <= 2);
  });

  it('rejects a trace with the wrong schema version', async () => {
    const bad = '{"schemaVersion":"something.else","agentRoster":[],"cadenceHz":10}\n{"type":"tick","tick":1,"agentId":"a","scene":{"id":"x","kind":"open_world"},"position":{"x":0,"y":0,"z":0},"velocity":{"x":0,"y":0,"z":0}}\n';
    const fetchImpl = (async () => ({ ok: true, status: 200, json: async () => ({ state: 'running', text: bad, next: bad.length, more: false }) })) as unknown as typeof fetch;
    const live = new LiveRunSource({ fetch: fetchImpl, wait: async () => {} });
    await assert.rejects(live.open(), /schemaVersion/);
  });

  it('never reads the same bytes twice when polls overlap', async () => {
    const { run, fetchImpl } = fakeRun();
    run.released = SAMPLE.length;
    const slow = (async (url: string) => {
      await new Promise((r) => setTimeout(r, 5));
      return fetchImpl(url);
    }) as unknown as typeof fetch;
    const live: LiveRunSource = new LiveRunSource({ fetch: slow, wait: async () => { endWhenRead(run); } });
    await live.open();
    await Promise.all([live.pollOnce(), live.pollOnce(), live.drain()]);
    await live.untilEnded();
    const parsed = parseTrace(SAMPLE.toString('utf8'));
    const whole = new TraceFrames(parsed.header);
    whole.add(parsed.records);
    whole.finish();
    assert.equal(live.frameCount(), whole.count(), 'no duplicated ticks');
    assert.deepEqual(live.diagnostics(), []);
  });

  it('drain reads what the engine wrote since the last poll, before a stop', async () => {
    const { run, fetchImpl } = fakeRun(8000);
    run.released = 20000;
    const live: LiveRunSource = new LiveRunSource({ fetch: fetchImpl, wait: () => new Promise(() => {}) }); // background loop never runs again
    await live.open();
    const before = live.frameCount();
    run.released = SAMPLE.length; // the engine kept writing
    await live.drain();
    assert.ok(live.frameCount() > before, 'the later lines were read');
    assert.equal(run.consumed, SAMPLE.length, 'all of it');
    live.close();
  });

  it('drain does nothing once the run has ended', async () => {
    const { run, fetchImpl } = fakeRun();
    run.released = SAMPLE.length;
    const live: LiveRunSource = new LiveRunSource({ fetch: fetchImpl, wait: async () => { endWhenRead(run); } });
    await live.open();
    await live.untilEnded();
    const requests = run.requests.length;
    await live.drain();
    assert.equal(run.requests.length, requests);
  });
});
