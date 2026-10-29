// Port of world-engine-godot/WorldConstants.cs, WorldGeometry.cs and
// TerrainBuilder.SurfaceHeightAt. Presentation only: the viewer rebuilds the
// same static landform the Godot app draws, from the same seed and constants,
// so agent positions in the state feed land on the same ground. Godot remains
// the authority — if this file and the C# disagree, the C# is right.
//
// C# does this arithmetic in 32-bit float. Math.fround is applied where the
// result feeds a discrete decision (RNG draws, hashes) so placement sampling
// takes the same branches as the engine.

const f = Math.fround;

export const SEED = 20260401;
export const WORLD = 460;
export const WATER = 0;
export const LAKE_X = 82, LAKE_Z = -58, LAKE_R = 34;
export const SETTLE_X = -66, SETTLE_Z = 46, SETTLE_R = 38, SETTLE_Y = 7.2;
export const TERRAIN_SEGMENTS = 208;
export const PI_F = f(Math.PI);

export const clamp = (v: number, a: number, b: number) => (v < a ? a : v > b ? b : v);
export const clamp01 = (v: number) => clamp(v, 0, 1);
export const lerp = (a: number, b: number, t: number) => a + (b - a) * t;
export const smooth = (t: number) => t * t * (3 - 2 * t);
export function smoothstep(e0: number, e1: number, x: number): number {
  const t = clamp01((x - e0) / (e1 - e0));
  return t * t * (3 - 2 * t);
}

/** mulberry32, exactly as SimulationRng.Next. */
export class SimulationRng {
  private a: number;
  constructor(seed: number) {
    this.a = seed >>> 0;
  }
  next(): number {
    this.a = (this.a + 0x6d2b79f5) >>> 0;
    let t = this.a;
    t = Math.imul(t ^ (t >>> 15), 1 | this.a) >>> 0;
    t = ((t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t) >>> 0;
    // (uint)/4294967296f: the uint is converted to float32 first.
    return f(f((t ^ (t >>> 14)) >>> 0) / 4294967296);
  }
  range(a: number, b: number): number {
    return f(a + f(f(b - a) * this.next()));
  }
}

export function hash2(x: number, y: number, seed: number): number {
  let h = seed >>> 0;
  h = Math.imul((h ^ Math.imul(x, 374761393)) >>> 0, 668265263) >>> 0;
  h = Math.imul((h ^ Math.imul(y, 2246822519 | 0)) >>> 0, 3266489917 | 0) >>> 0;
  h = (h ^ (h >>> 13)) >>> 0;
  h = Math.imul(h, 1274126177) >>> 0;
  return f(f((h ^ (h >>> 16)) >>> 0) / 4294967296);
}

export function valueNoise(x: number, y: number, seed: number): number {
  const xi = Math.floor(x), yi = Math.floor(y);
  const u = smooth(x - xi), v = smooth(y - yi);
  const a = hash2(xi, yi, seed), b = hash2(xi + 1, yi, seed);
  const c = hash2(xi, yi + 1, seed), d = hash2(xi + 1, yi + 1, seed);
  return lerp(lerp(a, b, u), lerp(c, d, u), v);
}

export function fbm(x: number, y: number, octaves: number, seed: number): number {
  let sum = 0, amp = 0.5, freq = 1, norm = 0;
  for (let i = 0; i < octaves; i++) {
    sum += valueNoise(x * freq, y * freq, seed + i * 7919) * amp;
    norm += amp;
    amp *= 0.5;
    freq = f(freq * f(2.03));
  }
  return sum / norm;
}

/** WorldGeometry.RawHeight / HeightAt. */
export function heightAt(x: number, z: number): number {
  let h = fbm(x * f(0.0072), z * f(0.0072), 5, SEED) * 24 - 6;

  const ridge = 1 - Math.abs(fbm(x * f(0.0155) + f(31.7), z * f(0.0155) - f(12.3), 4, SEED + 13) * 2 - 1);
  h += ridge * ridge * 11 * smoothstep(-2, 9, h);

  const r = Math.sqrt(x * x + z * z) / (WORLD * f(0.43));
  const island = 1 - smoothstep(f(0.6), f(1.06), r);
  h = h * island - 9 * (1 - island);

  const lakeD = Math.hypot(x - LAKE_X, z - LAKE_Z);
  const region = 1 - smoothstep(0, LAKE_R * f(3.2), lakeD);
  h -= region * 10;
  const lake = 1 - smoothstep(0, LAKE_R, lakeD);
  h = lerp(h, -5, Math.pow(lake, f(1.2)));

  const sd = Math.hypot(x - SETTLE_X, z - SETTLE_Z);
  const flat = 1 - smoothstep(SETTLE_R * f(0.55), SETTLE_R, sd);
  h = lerp(h, f(SETTLE_Y), flat * f(0.94));
  return f(h);
}

export function slopeAt(x: number, z: number): number {
  const e = f(2.2);
  const hx = heightAt(x + e, z) - heightAt(x - e, z);
  const hz = heightAt(x, z + e) - heightAt(x, z - e);
  return f(Math.sqrt(hx * hx + hz * hz) / (2 * e));
}

export const walkable = (x: number, z: number) => heightAt(x, z) > WATER + f(0.55) && slopeAt(x, z) < f(0.62);

/** TerrainBuilder.SurfaceHeightAt — the flat-triangle surface the mesh actually draws. */
export function surfaceHeightAt(x: number, z: number): number {
  const size = WORLD;
  const step = size / TERRAIN_SEGMENTS;
  const gx = (x + size / 2) / step, gz = (z + size / 2) / step;
  if (gx < 0 || gz < 0 || gx >= TERRAIN_SEGMENTS || gz >= TERRAIN_SEGMENTS) return heightAt(x, z);
  const i = Math.floor(gx), j = Math.floor(gz);
  const fx = gx - i, fz = gz - j;
  const H = (ci: number, cj: number) => heightAt(-size / 2 + ci * step, -size / 2 + cj * step);
  const a = H(i, j), b = H(i + 1, j), c = H(i + 1, j + 1), d = H(i, j + 1);
  return fx >= fz ? a + (b - a) * fx + (c - b) * fz : a + (d - a) * fz + (c - d) * fx;
}
