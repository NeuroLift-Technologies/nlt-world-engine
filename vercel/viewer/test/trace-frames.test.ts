import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { describe, it } from 'node:test';
import { TraceFrames } from '../src/feed/traceFrames.ts';
import { parseChunk, parseHeaderLine } from '../src/trace/chunk.ts';

const SAMPLE = readFileSync(new URL('../../../fixtures/observer-trace/sample.jsonl', import.meta.url), 'utf8');

const HEADER = '{"schemaVersion":"nlt.observer-trace.v1","runId":"r1","engineCommit":"x","godotVersion":"4","startTime":"t","agentRoster":["a"],"cadenceHz":10}';
const tick = (n: number, agent = 'a') =>
  `{"type":"tick","tick":${n},"agentId":"${agent}","scene":{"id":"open_world","kind":"open_world"},"position":{"x":${n},"y":0,"z":0},"velocity":{"x":0,"y":0,"z":0}}`;
const intent = (id: string, observedTick: number) =>
  `{"type":"intent","messageId":"${id}","agentId":"a","observedTick":${observedTick},"verb":"approach","targetId":"well"}`;
const result = (id: string, status = 'accepted', stage = 'accepted') =>
  `{"type":"result","intentMessageId":"${id}","agentId":"a","status":"${status}","stage":"${stage}"}`;

/** Feed `lines` (header first) the way a run in progress arrives: `perChunk` lines at a time. */
function ingest(lines: string[], perChunk: number): TraceFrames {
  const headerLine = lines[0];
  const { header } = parseHeaderLine(headerLine);
  const frames = new TraceFrames(header);
  let consumed = 1;
  for (let i = 1; i < lines.length; i += perChunk) {
    const chunk = lines.slice(i, i + perChunk).join('\n') + '\n';
    const parsed = parseChunk(headerLine, chunk, consumed);
    frames.add(parsed.records);
    consumed += parsed.lines;
  }
  return frames;
}

const plain = (v: unknown) => JSON.parse(JSON.stringify(v));

describe('TraceFrames on the real engine sample', () => {
  const lines = SAMPLE.split('\n').filter((l) => l.trim() !== '');

  it('gives the same frames however the lines arrive', () => {
    const whole = ingest(lines, lines.length);
    whole.finish();
    const expected = plain(whole.all());
    assert.ok(expected.length > 500, 'the sample has hundreds of frames');

    for (const perChunk of [1, 2, 3, 7, 50, 200]) {
      const piecewise = ingest(lines, perChunk);
      piecewise.finish();
      assert.deepEqual(plain(piecewise.all()), expected, `${perChunk} lines at a time`);
    }
  });

  it('lists a decision in the frames it belongs to even though the engine wrote it later', () => {
    // In the sample the first decision is observed at tick 1 but written after tick 2's samples.
    const frames = ingest(lines, 1);
    frames.finish();
    assert.equal(frames.frame(0).tick, 1);
    assert.ok(frames.frame(0).events.some((e) => e.text.startsWith('approach')), 'frame 0 lists it');
  });

  it('holds the newest tick back until a later tick shows it is complete', () => {
    const frames = ingest(lines, 1);
    const before = frames.count();
    frames.finish();
    assert.equal(frames.count(), before + 1);
  });
});

describe('TraceFrames behaviour', () => {
  it('grows as ticks complete', () => {
    const f = ingest([HEADER, tick(1), tick(2), tick(3)], 1);
    assert.equal(f.count(), 2); // ticks 1 and 2 are complete; 3 may still get more agents
    f.finish();
    assert.equal(f.count(), 3);
  });

  it('keeps several agents of one tick in one frame', () => {
    const f = ingest([HEADER, tick(1, 'a'), tick(1, 'b'), tick(2, 'a')], 1);
    f.finish();
    assert.deepEqual(f.frame(0).agents.map((a) => [a.id, a.role]), [['a', 'avatar'], ['b', 'resident']]);
  });

  it('rewrites a decision when its result arrives after it', () => {
    const f = ingest([HEADER, tick(1), tick(2), intent('i1', 1), tick(3)], 1);
    assert.match(f.frame(0).events[0].text, /no result recorded/);
    f.add(parseChunk(HEADER, result('i1', 'rejected', 'governance') + '\n', 5).records);
    f.finish();
    assert.match(f.frame(0).events[0].text, /refused by governance/);
    assert.equal(f.frame(0).events[0].severity, 'warn');
  });

  it('reads a result that arrives before its intent', () => {
    const f = ingest([HEADER, tick(1), result('i1'), intent('i1', 1), tick(2)], 1);
    f.finish();
    assert.match(f.frame(0).events[0].text, /accepted/);
  });

  it('refuses a tick that arrives after its frame was built, and says so', () => {
    const f = ingest([HEADER, tick(1), tick(2), tick(3), tick(1)], 1);
    f.finish();
    assert.equal(f.count(), 3);
    assert.equal(f.problems.length, 1);
    assert.match(f.problems[0], /tick 1 arrived after its frame/);
  });

  it('shows only the latest eight decisions in a frame', () => {
    const lines = [HEADER, tick(1)];
    for (let i = 0; i < 12; i++) lines.push(intent(`i${i}`, 1), result(`i${i}`));
    lines.push(tick(2));
    const f = ingest(lines, 1);
    f.finish();
    assert.equal(f.frame(1).events.length, 8);
  });

  it('returns the same frame object until the decisions change', () => {
    const f = ingest([HEADER, tick(1), tick(2)], 1);
    f.finish();
    assert.equal(f.frame(0), f.frame(0));
    const first = f.frame(0);
    f.add(parseChunk(HEADER, intent('i1', 1) + '\n', 3).records);
    assert.notEqual(f.frame(0), first);
    assert.equal(f.frame(0).events.length, 1);
  });
});

describe('parseChunk', () => {
  it('numbers unreadable lines by their place in the whole trace', () => {
    const headerLine = HEADER;
    const first = parseChunk(headerLine, [tick(1), tick(2)].join('\n') + '\n', 1); // lines 2 and 3
    assert.equal(first.lines, 2);
    const second = parseChunk(headerLine, ['not json at all', tick(3)].join('\n') + '\n', 1 + first.lines); // lines 4 and 5
    assert.equal(second.diagnostics.length, 1);
    assert.match(second.diagnostics[0], /^line 4:/);
  });

  it('treats an empty piece as nothing', () => {
    assert.deepEqual(parseChunk(HEADER, '', 1), { records: [], diagnostics: [], lines: 0 });
    assert.deepEqual(parseChunk(HEADER, '\n', 1), { records: [], diagnostics: [], lines: 0 });
  });
});
