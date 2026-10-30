// Limits for a run, read from the environment. Kept free of the Sandbox SDK so they can be tested.

export const DEFAULT_MAX_MINUTES = 15;
export const MAX_MINUTES_CEILING = 60;
export const DEFAULT_VCPUS = 2; // 2 GB of memory per vCPU, so 4 GB
export const MAX_VCPUS = 4;

type Env = Record<string, string | undefined>;

function positiveInt(value: string | undefined): number | null {
  const parsed = Number.parseInt(value ?? '', 10);
  return Number.isFinite(parsed) && parsed > 0 ? parsed : null;
}

/** How long a run may last before the sandbox stops itself, in milliseconds. */
export function maxRunMs(env: Env): number {
  const minutes = Math.min(positiveInt(env.NLT_RUN_MAX_MINUTES) ?? DEFAULT_MAX_MINUTES, MAX_MINUTES_CEILING);
  return minutes * 60_000;
}

/** Sandbox size. Memory follows the vCPU count at 2048 MB each. */
export function sandboxVcpus(env: Env): number {
  return Math.min(positiveInt(env.NLT_SANDBOX_VCPUS) ?? DEFAULT_VCPUS, MAX_VCPUS);
}

/** Where the engine writes the observer trace inside the sandbox. Fixed: callers never choose a path. */
export const TRACE_PATH = '/tmp/nlt-observer-trace.jsonl';

/** Most bytes one poll returns. The client asks again while `more` is true. */
export const TRACE_CHUNK_BYTES = 256 * 1024;
