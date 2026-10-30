// Reads a trace that arrives in pieces (a run in progress) with the same parser as a whole file.
//
// The parser expects a header on the first line, so each piece is parsed behind the header line
// already seen, and line numbers are moved back to where the piece sits in the whole file.
import { parseTrace } from './parser';
import type { ParsedRecord, TraceHeader } from './types';

export interface ParsedChunk {
  records: ParsedRecord[];
  /** Lines the parser could not use, with their position in the whole trace. */
  diagnostics: string[];
  /** Lines in the piece, so the next piece can be numbered. */
  lines: number;
}

export function parseHeaderLine(line: string): { header: TraceHeader; errors: string[] } {
  const parsed = parseTrace(line);
  return { header: parsed.header, errors: parsed.errors };
}

/** `linesBefore` counts every line already read, header included. */
export function parseChunk(headerLine: string, chunk: string, linesBefore: number): ParsedChunk {
  const text = chunk.replace(/\n$/, '');
  if (text === '') return { records: [], diagnostics: [], lines: 0 };
  const parsed = parseTrace(headerLine + '\n' + text);
  const records = parsed.records.map((r) => (r.kind === 'unknown' ? { ...r, line: linesBefore + r.line - 1 } : r));
  const diagnostics = records.filter((r) => r.kind === 'unknown').map((r) => `line ${r.line}: ${(r as { reason: string }).reason}`);
  return { records, diagnostics, lines: text.split('\n').length };
}
