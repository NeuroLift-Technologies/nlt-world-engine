import { controlEnabled, handleRunRequest } from './_lib/run-control.js';
import { sandboxPort } from './_lib/sandbox-port.js';

// GET    /api/run  -> { state, run }          current run, or idle
// POST   /api/run  -> start a run (409 if one is already active)
// DELETE /api/run  -> stop the run (idempotent)
//
// Off unless NLT_RUN_CONTROL=enabled. Deploy it only behind Vercel Deployment Protection (or
// another gate that decides who is an authorised observer): the checks here stop cross-site
// requests, they do not identify a person.

async function respond(request: Request): Promise<Response> {
  const noStore = { 'cache-control': 'no-store', 'content-type': 'application/json' };
  try {
    const result = await handleRunRequest(
      { method: request.method, header: (name) => request.headers.get(name) },
      controlEnabled(process.env),
      sandboxPort(process.env),
    );
    return new Response(JSON.stringify(result.body), {
      status: result.status,
      headers: { ...noStore, ...result.headers },
    });
  } catch (err) {
    // Details stay in the function logs; the page only learns that the engine could not be reached.
    console.error('run control failed', err);
    return new Response(JSON.stringify({ error: 'run_control_failed' }), { status: 502, headers: noStore });
  }
}

export const GET = respond;
export const POST = respond;
export const DELETE = respond;
