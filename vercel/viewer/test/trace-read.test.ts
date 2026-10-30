import assert from 'node:assert/strict';
import { describe, it } from 'node:test';
import { MAX_TRACE_LINE_BYTES, readWholeLines } from '../api/_lib/trace-read.ts';

/** A file read the way `tail -c +N | head -c LIMIT` does, as text. */
const file = (content: string) => (from: number) => async (limit: number) =>
  Buffer.from(content, 'utf8').subarray(from, from + limit).toString('utf8');

describe('readWholeLines', () => {
  it('returns whole lines and the offset after the last newline', async () => {
    const r = await readWholeLines(file('{"a":1}\n{"b":2}\n')(0), 0, 1000);
    assert.deepEqual(r, { text: '{"a":1}\n{"b":2}\n', next: 16, more: false });
  });

  it('leaves a half-written last line for next time', async () => {
    const r = await readWholeLines(file('{"a":1}\n{"b":')(0), 0, 1000);
    assert.equal(r.text, '{"a":1}\n');
    assert.equal(r.next, 8);
  });

  it('returns nothing, and does not move, when no line is complete yet', async () => {
    const r = await readWholeLines(file('{"a":')(0), 0, 1000);
    assert.deepEqual(r, { text: '', next: 0, more: false });
  });

  it('says more is waiting when the read hit its limit', async () => {
    const content = '{"a":1}\n{"b":2}\n{"c":3}\n';
    const r = await readWholeLines(file(content)(0), 0, 10);
    assert.equal(r.text, '{"a":1}\n');
    assert.equal(r.more, true);
  });

  it('doubles the limit until one long line fits', async () => {
    const long = '{"x":"' + 'y'.repeat(5000) + '"}\n';
    const limits: number[] = [];
    const read = file(long + '{"n":2}\n')(0);
    const r = await readWholeLines(async (limit) => { limits.push(limit); return read(limit); }, 0, 1000);
    assert.equal(r.text.startsWith('{"x":"y'), true);
    assert.ok(r.text.endsWith('\n'));
    assert.deepEqual(limits, [1000, 2000, 4000, 8000]);
  });

  it('counts bytes, not characters, for the next offset', async () => {
    const line = '{"n":"Zoë 日本"}\n';
    const r = await readWholeLines(file(line + line)(0), 0, 1000);
    assert.equal(r.next, Buffer.byteLength(line + line));
    const second = await readWholeLines(file(line + line)(Buffer.byteLength(line)), Buffer.byteLength(line), 1000);
    assert.equal(second.text, line);
  });

  it('ignores a multi-byte character cut by the limit', async () => {
    const content = '{"n":1}\n' + '日本\n';
    const cutInsideCharacter = 8 + 1; // one byte into the first character of the second line
    const r = await readWholeLines(file(content)(0), 0, cutInsideCharacter);
    assert.equal(r.text, '{"n":1}\n');
    assert.equal(r.next, 8);
  });

  it('gives up on a line longer than the ceiling instead of reading forever', async () => {
    let calls = 0;
    const endless = async (limit: number) => { calls++; return 'x'.repeat(limit); };
    const r = await readWholeLines(endless, 0, MAX_TRACE_LINE_BYTES / 4);
    assert.equal(r.text, '');
    assert.equal(r.more, false);
    assert.equal(calls, 3);
  });
});
