import type { AgentState, SceneEntity } from './trace/types.js';

// ---------------------------------------------------------------------------
// Godot-style 3D world view for the observer. A canvas port of the native
// app's open-world frame (world-engine-godot): same orbit camera defaults
// (FOV 52, yaw 0.6, pitch 0.42, distance 78 m on the settlement), same island
// constants (460 m world, lake at 82/-58 r34, settlement at -66/46), and the
// TerrainBuilder colour palette. Observer visualization only — it never
// becomes simulation authority and does not read authoritative geometry.
// ---------------------------------------------------------------------------

type Vec3 = { x: number; y: number; z: number };

// WorldConstants.cs
const SEED = 20260401;
const WORLD = 460;
const WATER = 0;
const LAKE = { x: 82, z: -58, r: 34 };
const SETTLE = { x: -66, z: 46, r: 38, y: 7.2 };

// WorldView.cs camera defaults
const FOV = 52;
const TARGET: Vec3 = { x: SETTLE.x, y: SETTLE.y + 2, z: SETTLE.z };
const MIN_DIST = 8;
const MAX_DIST = 340;

// TerrainBuilder.cs palette (authored as sRGB hex)
const C_SAND = [201, 180, 140];
const C_GRASS = [92, 116, 68];
const C_GRASS2 = [72, 96, 58];
const C_ROCK = [123, 116, 104];
const C_DARK = [76, 71, 64];

const clamp = (v: number, a: number, b: number) => (v < a ? a : v > b ? b : v);
const clamp01 = (v: number) => clamp(v, 0, 1);
const lerp = (a: number, b: number, t: number) => a + (b - a) * t;
const smooth = (t: number) => t * t * (3 - 2 * t);
const smoothstep = (e0: number, e1: number, x: number) => smooth(clamp01((x - e0) / (e1 - e0)));
const mixC = (a: number[], b: number[], t: number) => [lerp(a[0], b[0], t), lerp(a[1], b[1], t), lerp(a[2], b[2], t)];
const css = (c: number[], m = 1) => 'rgb(' + Math.round(clamp(c[0] * m, 0, 255)) + ',' + Math.round(clamp(c[1] * m, 0, 255)) + ',' + Math.round(clamp(c[2] * m, 0, 255)) + ')';

// SimulationRng.cs noise ports (mulberry32 + hash2/valueNoise/fbm)
function hash2(x: number, y: number, seed: number): number {
  let h = seed >>> 0;
  h = Math.imul(h ^ (Math.imul(x, 374761393) >>> 0), 668265263) >>> 0;
  h = Math.imul(h ^ (Math.imul(y, 2246822519) >>> 0), 3266489917) >>> 0;
  h = (h ^ (h >>> 13)) >>> 0;
  h = Math.imul(h, 1274126177) >>> 0;
  return ((h ^ (h >>> 16)) >>> 0) / 4294967296;
}
function valueNoise(x: number, y: number, seed: number): number {
  const xi = Math.floor(x), yi = Math.floor(y);
  const u = smooth(x - xi), v = smooth(y - yi);
  const a = hash2(xi, yi, seed), b = hash2(xi + 1, yi, seed);
  const c = hash2(xi, yi + 1, seed), d = hash2(xi + 1, yi + 1, seed);
  return lerp(lerp(a, b, u), lerp(c, d, u), v);
}
function fbm(x: number, y: number, octaves: number, seed: number): number {
  let sum = 0, amp = 0.5, freq = 1, norm = 0;
  for (let i = 0; i < octaves; i++) {
    sum += valueNoise(x * freq, y * freq, seed + i * 7919) * amp;
    norm += amp;
    amp *= 0.5;
    freq *= 2.03;
  }
  return sum / norm;
}

// Island heightfield in the spirit of WorldGeometry.HeightAt: radial falloff
// to the sea, an fbm ridge field, a flattened settlement plateau, and the
// lake basin carved below sea level.
function heightAt(x: number, z: number): number {
  const r = Math.hypot(x, z);
  const edge = WORLD / 2;
  const fall = Math.pow(clamp01(1 - r / edge), 1.35);
  let h = fall * (5 + fbm(x * 0.009, z * 0.009, 4, SEED) * 16) - 4.2 * (1 - fall);
  // Settlement plateau
  const ds = Math.hypot(x - SETTLE.x, z - SETTLE.z);
  if (ds < SETTLE.r + 14) {
    const t = smoothstep(SETTLE.r + 14, SETTLE.r - 6, ds);
    h = lerp(h, SETTLE.y, t);
  }
  // Lake basin
  const dl = Math.hypot(x - LAKE.x, z - LAKE.z);
  if (dl < LAKE.r + 8) {
    const t = smoothstep(LAKE.r + 8, LAKE.r * 0.55, dl);
    h = lerp(h, -3.4, t);
  }
  return h;
}

function terrainColor(x: number, z: number, h: number): string {
  const grain = fbm(x * 0.06, z * 0.06, 3, SEED + 991);
  let c: number[];
  if (h < WATER - 2.6) c = C_DARK;
  else if (h < WATER + 1.5) c = C_SAND;
  else {
    c = mixC(C_GRASS, C_GRASS2, grain);
    c = mixC(c, C_ROCK, smoothstep(0.28, 0.72, grain * 0.5));
    c = mixC(c, C_SAND, smoothstep(2.4, 0.9, h) * 0.25);
    c = c.map(v => v * (0.86 + grain * 0.3));
  }
  const shade = 0.94 + fbm(x * 0.012, z * 0.012, 2, SEED + 77) * 0.14;
  return css(c, shade);
}

function waterColor(x: number, z: number): string {
  const ripple = fbm(x * 0.05, z * 0.05, 2, SEED + 555);
  const deep = [44, 93, 117], shallow = [95, 159, 178];
  return css(mixC(deep, shallow, ripple * 0.8));
}

type Building = { x: number; z: number; w: number; d: number; h: number; label: string; wall: string };
const BUILDINGS: Building[] = [
  { x: SETTLE.x - 16, z: SETTLE.z - 13, w: 11, d: 9, h: 7.5, label: 'HOME', wall: '#d9c7a0' },
  { x: SETTLE.x + 15, z: SETTLE.z - 15, w: 13, d: 10, h: 10, label: 'WORK', wall: '#b7c8d8' },
  { x: SETTLE.x + 17, z: SETTLE.z + 12, w: 11, d: 10, h: 8.5, label: 'SCHOOL', wall: '#d8b6a8' },
  { x: SETTLE.x - 17, z: SETTLE.z + 14, w: 12, d: 10, h: 9, label: 'COMMUNITY', wall: '#c4d2ae' },
  { x: SETTLE.x, z: SETTLE.z + 19, w: 14, d: 10, h: 6.5, label: 'SHOP', wall: '#d8c0d8' },
];

type Tree = { x: number; z: number; h: number; r: number };
const TREES: Tree[] = (() => {
  let a = SEED >>> 0;
  const next = () => {
    a = (a + 0x6d2b79f5) >>> 0;
    let t = a >>> 0;
    t = Math.imul(t ^ (t >>> 15), (1 | a)) >>> 0;
    t = (t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t;
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
  const trees: Tree[] = [];
  for (let i = 0; i < 900 && trees.length < 130; i++) {
    const x = (next() - 0.5) * WORLD * 0.92;
    const z = (next() - 0.5) * WORLD * 0.92;
    const h = heightAt(x, z);
    if (h < WATER + 1.8) continue;
    if (Math.hypot(x - SETTLE.x, z - SETTLE.z) < SETTLE.r + 8) continue;
    if (Math.hypot(x - LAKE.x, z - LAKE.z) < LAKE.r + 10) continue;
    trees.push({ x, z, h, r: 1.4 + next() * 1.3 });
  }
  return trees;
})();

const AGENT_COLORS = ['#56b4e9', '#e69f00', '#009e73', '#cc79a7'];

export class World3DView {
  private canvas: HTMLCanvasElement;
  private ctx: CanvasRenderingContext2D;
  private agents = new Map<string, AgentState>();
  private entities = new Map<string, SceneEntity[]>();
  private dpr = 1;

  // WorldView.cs orbit state
  private yaw = 0.6;
  private pitch = 0.42;
  private dist = 78;
  private dragging = false;
  private lastX = 0;
  private lastY = 0;

  // Cached projection basis, rebuilt per render
  private cam: Vec3 = { x: 0, y: 0, z: 0 };
  private fwd: Vec3 = { x: 0, y: 0, z: 0 };
  private right: Vec3 = { x: 0, y: 0, z: 0 };
  private up: Vec3 = { x: 0, y: 0, z: 0 };
  private focal = 1;
  private vw = 800;
  private vh = 480;

  constructor(canvas: HTMLCanvasElement) {
    this.canvas = canvas;
    const ctx = canvas.getContext('2d');
    if (!ctx) throw new Error('2D canvas context unavailable for world scene');
    this.ctx = ctx;
    canvas.addEventListener('wheel', (event) => {
      event.preventDefault();
      this.dist = clamp(this.dist + (event.deltaY > 0 ? 6 : -6), MIN_DIST, MAX_DIST);
      this.render();
    }, { passive: false });
    canvas.addEventListener('pointerdown', (event) => {
      this.dragging = true; this.lastX = event.clientX; this.lastY = event.clientY;
      canvas.setPointerCapture(event.pointerId);
    });
    canvas.addEventListener('pointermove', (event) => {
      if (!this.dragging) return;
      this.yaw -= (event.clientX - this.lastX) * 0.005;
      this.pitch = clamp(this.pitch + (event.clientY - this.lastY) * 0.004, 0.05, Math.PI * 0.487);
      this.lastX = event.clientX; this.lastY = event.clientY;
      this.render();
    });
    canvas.addEventListener('pointerup', () => { this.dragging = false; });
    canvas.addEventListener('pointercancel', () => { this.dragging = false; });
    window.addEventListener('resize', () => this.render());
    this.render();
  }

  update(agents: Map<string, AgentState>, entities: Map<string, SceneEntity[]>) {
    this.agents = new Map(agents);
    this.entities = new Map(entities);
    this.render();
  }

  // Godot Camera3D-style perspective projection; null when behind the near plane.
  private project(p: Vec3): { x: number; y: number; z: number } | null {
    const dx = p.x - this.cam.x, dy = p.y - this.cam.y, dz = p.z - this.cam.z;
    const zc = dx * this.fwd.x + dy * this.fwd.y + dz * this.fwd.z;
    if (zc < 0.5) return null;
    const xc = dx * this.right.x + dy * this.right.y + dz * this.right.z;
    const yc = dx * this.up.x + dy * this.up.y + dz * this.up.z;
    return { x: this.vw / 2 + (xc / zc) * this.focal, y: this.vh / 2 - (yc / zc) * this.focal, z: zc };
  }

  private updateCamera() {
    // WorldView.UpdateCamera: position on the orbit, look at target, up = +Y.
    const cp = Math.cos(this.pitch), sp = Math.sin(this.pitch);
    this.cam = {
      x: TARGET.x + cp * Math.sin(this.yaw) * this.dist,
      y: TARGET.y + sp * this.dist,
      z: TARGET.z + cp * Math.cos(this.yaw) * this.dist,
    };
    const fx = TARGET.x - this.cam.x, fy = TARGET.y - this.cam.y, fz = TARGET.z - this.cam.z;
    const fl = Math.hypot(fx, fy, fz);
    this.fwd = { x: fx / fl, y: fy / fl, z: fz / fl };
    const rx = this.fwd.z, rz = -this.fwd.x;
    const rl = Math.hypot(rx, rz);
    this.right = { x: rx / rl, y: 0, z: rz / rl };
    this.up = {
      x: this.right.y * this.fwd.z - this.right.z * this.fwd.y,
      y: this.right.z * this.fwd.x - this.right.x * this.fwd.z,
      z: this.right.x * this.fwd.y - this.right.y * this.fwd.x,
    };
    this.focal = (this.vh / 2) / Math.tan((FOV * Math.PI / 180) / 2);
  }

  private quad(a: Vec3, b: Vec3, c: Vec3, d: Vec3, fill: string) {
    const ctx = this.ctx;
    const pa = this.project(a), pb = this.project(b), pc = this.project(c), pd = this.project(d);
    if (!pa || !pb || !pc || !pd) return;
    if (Math.max(pa.x, pb.x, pc.x, pd.x) < 0 || Math.min(pa.x, pb.x, pc.x, pd.x) > this.vw) return;
    if (Math.max(pa.y, pb.y, pc.y, pd.y) < 0 || Math.min(pa.y, pb.y, pc.y, pd.y) > this.vh) return;
    ctx.beginPath();
    ctx.moveTo(pa.x, pa.y); ctx.lineTo(pb.x, pb.y); ctx.lineTo(pc.x, pc.y); ctx.lineTo(pd.x, pd.y);
    ctx.closePath();
    ctx.fillStyle = fill;
    ctx.fill();
  }

  private drawBuilding(b: Building, groundY: number) {
    const x0 = b.x - b.w / 2, x1 = b.x + b.w / 2;
    const z0 = b.z - b.d / 2, z1 = b.z + b.d / 2;
    const top = groundY + b.h;
    const camSideX = this.cam.x > b.x, camSideZ = this.cam.z > b.z;
    // Two visible walls (the ones facing the camera), then the roof.
    const wallX = camSideX ? x1 : x0, wallXFar = camSideX ? x0 : x1;
    const wallZ = camSideZ ? z1 : z0, wallZFar = camSideZ ? z0 : z1;
    this.quad(
      { x: wallX, y: groundY, z: wallZFar }, { x: wallX, y: groundY, z: wallZ },
      { x: wallX, y: top, z: wallZ }, { x: wallX, y: top, z: wallZFar },
      '#a8a49a');
    this.quad(
      { x: wallXFar, y: groundY, z: wallZ }, { x: wallX, y: groundY, z: wallZ },
      { x: wallX, y: top, z: wallZ }, { x: wallXFar, y: top, z: wallZ },
      '#b4b1a6');
    this.quad(
      { x: x0, y: top, z: z0 }, { x: x1, y: top, z: z0 },
      { x: x1, y: top, z: z1 }, { x: x0, y: top, z: z1 },
      '#e5e2d7');
    // Sun-side wall tint so orientation reads like the Godot frame.
    this.quad(
      { x: wallXFar, y: groundY, z: wallZFar }, { x: wallX, y: groundY, z: wallZFar },
      { x: wallX, y: top, z: wallZFar }, { x: wallXFar, y: top, z: wallZFar },
      b.wall);
    const c = this.project({ x: b.x, y: top + 1.5, z: b.z });
    if (c) {
      const ctx = this.ctx;
      ctx.font = '700 10px system-ui';
      ctx.textAlign = 'center';
      const wch = ctx.measureText(b.label).width + 10;
      ctx.fillStyle = 'rgba(13,20,26,0.78)';
      ctx.fillRect(c.x - wch / 2, c.y - 12, wch, 14);
      ctx.fillStyle = '#e6edf3';
      ctx.fillText(b.label, c.x, c.y - 2);
    }
  }

  private drawTree(t: Tree) {
    const ctx = this.ctx;
    const base = this.project({ x: t.x, y: t.h, z: t.z });
    if (!base) return;
    const s = this.focal / base.z;
    const trunk = { x: base.x, y: base.y - t.r * s * 0.9 };
    ctx.strokeStyle = '#5d4a35';
    ctx.lineWidth = Math.max(1, t.r * s * 0.22);
    ctx.beginPath(); ctx.moveTo(base.x, base.y); ctx.lineTo(trunk.x, trunk.y); ctx.stroke();
    ctx.beginPath(); ctx.arc(trunk.x, trunk.y - t.r * s * 0.4, t.r * s, 0, Math.PI * 2);
    ctx.fillStyle = t.r > 2 ? '#3f6a48' : '#4f7d50';
    ctx.fill();
  }

  // Observer World View HUD pins: screen-space glowing markers over the
  // camera-projected feed position (RENDERER-PLAN 6.1).
  private drawAgent(agent: AgentState, index: number) {
    const ctx = this.ctx;
    const ground = { x: agent.position.x, y: Math.max(heightAt(agent.position.x, agent.position.z), WATER), z: agent.position.z };
    const g = this.project(ground);
    if (!g) return;
    const color = AGENT_COLORS[index % AGENT_COLORS.length];
    const lift = 3.2 * (this.focal / g.z);
    ctx.strokeStyle = 'rgba(230,237,243,0.75)';
    ctx.lineWidth = 1.5;
    ctx.beginPath(); ctx.moveTo(g.x, g.y); ctx.lineTo(g.x, g.y - lift); ctx.stroke();
    ctx.save();
    ctx.shadowColor = color;
    ctx.shadowBlur = 12;
    ctx.fillStyle = color;
    ctx.beginPath(); ctx.arc(g.x, g.y - lift, 5.5, 0, Math.PI * 2); ctx.fill();
    ctx.restore();
    ctx.strokeStyle = 'rgba(13,20,26,0.85)';
    ctx.lineWidth = 1.5;
    ctx.beginPath(); ctx.arc(g.x, g.y - lift, 5.5, 0, Math.PI * 2); ctx.stroke();
    ctx.font = '700 10px system-ui';
    ctx.textAlign = 'center';
    const wch = ctx.measureText(agent.agentId).width + 10;
    ctx.fillStyle = 'rgba(13,20,26,0.78)';
    ctx.fillRect(g.x - wch / 2, g.y - lift - 24, wch, 14);
    ctx.fillStyle = '#e6edf3';
    ctx.fillText(agent.agentId, g.x, g.y - lift - 14);
  }

  private drawSky() {
    const ctx = this.ctx;
    // Sky3D-style atmospheric gradient with a soft sun glow and horizon fog.
    const horizon = this.project({ x: this.cam.x + this.fwd.x * 2000, y: this.cam.y, z: this.cam.z + this.fwd.z * 2000 });
    const hy = horizon ? horizon.y : this.vh * 0.35;
    const sky = ctx.createLinearGradient(0, 0, 0, Math.max(hy, 1));
    sky.addColorStop(0, '#3d6fa5');
    sky.addColorStop(0.62, '#7ba7cc');
    sky.addColorStop(1, '#cfe0ea');
    ctx.fillStyle = sky;
    ctx.fillRect(0, 0, this.vw, Math.max(hy, 0));
    // Sun glow, high sun as at the sim-clock noon the world opens on.
    const sun = this.project({ x: this.cam.x + this.fwd.x * 1800 + this.right.x * 400, y: this.cam.y + this.fwd.y * 1800 + 900, z: this.cam.z + this.fwd.z * 1800 + this.right.z * 400 });
    if (sun) {
      const glow = ctx.createRadialGradient(sun.x, sun.y, 0, sun.x, sun.y, 130);
      glow.addColorStop(0, 'rgba(255,244,214,0.9)');
      glow.addColorStop(0.35, 'rgba(255,236,190,0.35)');
      glow.addColorStop(1, 'rgba(255,236,190,0)');
      ctx.fillStyle = glow;
      ctx.fillRect(sun.x - 130, sun.y - 130, 260, 260);
    }
    // Sea to the bottom edge, fading toward the horizon fog colour.
    const sea = ctx.createLinearGradient(0, Math.max(hy, 0), 0, this.vh);
    sea.addColorStop(0, '#9fb6c4');
    sea.addColorStop(0.18, '#5d7f96');
    sea.addColorStop(1, '#33566d');
    ctx.fillStyle = sea;
    ctx.fillRect(0, Math.max(hy, 0), this.vw, this.vh - Math.max(hy, 0));
  }

  private drawHud() {
    const ctx = this.ctx;
    const chip = (x: number, y: number, w: number, h: number) => {
      ctx.fillStyle = 'rgba(13,20,26,0.78)';
      ctx.fillRect(x, y, w, h);
    };
    ctx.textAlign = 'left';
    chip(12, 12, 268, 46);
    ctx.fillStyle = '#e6edf3'; ctx.font = '700 12px system-ui';
    ctx.fillText('NLT WORLD ENGINE · WORLD VIEW', 22, 30);
    ctx.font = '11px system-ui'; ctx.fillStyle = '#a3b1c0';
    ctx.fillText(BUILDINGS.length + ' structures · ' + TREES.length + ' trees · ' + this.agents.size + ' trace agents', 22, 47);
    ctx.textAlign = 'center';
    chip(this.vw - 192, 12, 180, 28);
    ctx.fillStyle = '#a3b1c0'; ctx.font = '10px system-ui';
    ctx.fillText('Drag to orbit · Scroll to zoom', this.vw - 102, 30);
  }

  render() {
    const ctx = this.ctx;
    const w = this.canvas.clientWidth || 800, h = this.canvas.clientHeight || 480;
    this.vw = w; this.vh = h;
    this.dpr = window.devicePixelRatio || 1;
    this.canvas.width = Math.round(w * this.dpr);
    this.canvas.height = Math.round(h * this.dpr);
    ctx.setTransform(this.dpr, 0, 0, this.dpr, 0, 0);
    this.updateCamera();

    this.drawSky();

    // Terrain: a coarse port of TerrainBuilder.Build — one quad per grid cell,
    // painted far-to-near so the near shore overlaps the far water correctly.
    const SEG = 64;
    const step = WORLD / SEG;
    type Item = { depth: number; draw: () => void };
    const items: Item[] = [];
    const half = WORLD / 2;
    const inView = (x: number, z: number) => Math.hypot(x - this.cam.x, z - this.cam.z) < this.dist * 4 + 260;
    for (let j = 0; j < SEG; j++) {
      for (let i = 0; i < SEG; i++) {
        const x0 = -half + i * step, z0 = -half + j * step;
        if (!inView(x0 + step / 2, z0 + step / 2)) continue;
        const x1 = x0 + step, z1 = z0 + step;
        const hA = heightAt(x0, z0), hB = heightAt(x1, z0), hC = heightAt(x1, z1), hD = heightAt(x0, z1);
        const isWater = Math.min(hA, hB, hC, hD) < WATER;
        const fill = isWater ? waterColor(x0, z0) : terrainColor(x0 + step / 2, z0 + step / 2, (hA + hB + hC + hD) / 4);
        const cx = x0 + step / 2, cz = z0 + step / 2;
        const c = this.project({ x: cx, y: Math.max((hA + hB + hC + hD) / 4, WATER), z: cz });
        if (!c) continue;
        items.push({
          depth: c.z,
          draw: () => this.quad(
            { x: x0, y: isWater ? WATER : hA, z: z0 },
            { x: x1, y: isWater ? WATER : hB, z: z0 },
            { x: x1, y: isWater ? WATER : hC, z: z1 },
            { x: x0, y: isWater ? WATER : hD, z: z1 },
            fill),
        });
      }
    }

    for (const b of BUILDINGS) {
      const c = this.project({ x: b.x, y: SETTLE.y + b.h / 2, z: b.z });
      if (c) items.push({ depth: c.z - 1, draw: () => this.drawBuilding(b, SETTLE.y) });
    }
    for (const t of TREES) {
      const c = this.project({ x: t.x, y: t.h + 2, z: t.z });
      if (c) items.push({ depth: c.z, draw: () => this.drawTree(t) });
    }

    items.sort((a, b) => b.depth - a.depth);
    for (const item of items) item.draw();

    // Scene entity markers, then glowing agent pins on top.
    for (const [, list] of this.entities) {
      for (const ent of list) {
        const g = this.project({ x: ent.position.x, y: Math.max(ent.position.y, WATER + 0.5), z: ent.position.z });
        if (!g) continue;
        const ctx2 = this.ctx;
        ctx2.save();
        ctx2.strokeStyle = '#e6edf3';
        ctx2.lineWidth = 1;
        ctx2.setLineDash([4, 3]);
        ctx2.strokeRect(g.x - 5, g.y - 9, 10, 10);
        ctx2.restore();
        ctx2.font = '9px system-ui';
        ctx2.textAlign = 'center';
        ctx2.fillStyle = '#e6edf3';
        ctx2.fillText(ent.id, g.x, g.y - 13);
      }
    }
    [...this.agents.values()]
      .sort((a, b) => b.position.z - a.position.z)
      .forEach((agent, index) => this.drawAgent(agent, index));

    this.drawHud();
  }
}
