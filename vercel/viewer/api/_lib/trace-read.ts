import { TRACE_CHUNK_BYTES } from './run-config.js';

/** A line longer than this is treated as not written yet rather than read. */
export const MAX_TRACE_LINE_BYTES = 8 * 1024 * 1024;

export interface WholeLines {
  text: string;
  /** Offset to ask for next: the byte after the last newline returned. */
  next: number;
  /** True when the read was cut at its limit, so more is probably waiting. */
  more: boolean;
}

/**
 * Takes the next whole lines from a trace file. `read(limit)` returns up to `limit` bytes from the
 * offset `from`. Anything after the last newline (a line the engine is still writing, or a cut
 * multi-byte character) is left for the next read. If the first line is longer than the limit,
 * the limit is doubled until the line fits, so one long line (a scene with many entities) can
 * never stall the reader.
 */
export async function readWholeLines(
  read: (limitBytes: number) => Promise<string>,
  from: number,
  startLimit: number = TRACE_CHUNK_BYTES,
): Promise<WholeLines> {
  let limit = startLimit;
  for (;;) {
    const raw = await read(limit);
    const full = Buffer.byteLength(raw, 'utf8') >= limit;
    const end = raw.lastIndexOf('\n');
    if (end !== -1) {
      const text = raw.slice(0, end + 1);
      return { text, next: from + Buffer.byteLength(text, 'utf8'), more: full };
    }
    if (!full || limit >= MAX_TRACE_LINE_BYTES) return { text: '', next: from, more: false };
    limit *= 2;
  }
}
