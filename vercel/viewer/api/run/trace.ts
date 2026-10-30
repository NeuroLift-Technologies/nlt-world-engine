import { controlEnabled, handleTraceRequest } from '../_lib/run-control.js';
import { sandboxPort } from '../_lib/sandbox-port.js';

// GET /api/run/trace?from=<byte offset> -> { state, runId, text, next, more }
// New whole lines of the running engine's nlt.observer-trace.v1 file. Read-only; off unless
// NLT_RUN_CONTROL=enabled, and meant to sit behind the same Vercel Auth as /api/run.

export async function GET(request: Request): Promise<Response> {
  const headers = { 'cache-control': 'no-store', 'content-type': 'application/json' };
  try {
    const from = new URL(request.url).searchParams.get('from');
    const result = await handleTraceRequest(
      { method: request.method, header: (name) => request.headers.get(name) },
      controlEnabled(process.env),
      sandboxPort(process.env),
      from,
    );
    return new Response(JSON.stringify(result.body), { status: result.status, headers: { ...headers, ...result.headers } });
  } catch (err) {
    console.error('trace read failed', err);
    return new Response(JSON.stringify({ error: 'trace_read_failed' }), { status: 502, headers });
  }
}
