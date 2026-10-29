// Port of world-engine-godot/SettlementBuilder.cs, BuildingArchetypes.cs and
// PortalMarker (Portal.cs). Same plan sampler, same kind pattern, same silhouettes.
import * as THREE from 'three';
import {
  PI_F, SETTLE_R, SETTLE_X, SETTLE_Z, SimulationRng, heightAt, surfaceHeightAt, walkable,
} from './geometry';

const f = Math.fround;
const TAU = Math.PI * 2;

export type BuildingKind = 'Apartment' | 'Office' | 'Shop' | 'School';
export interface Plan { x: number; z: number; rad: number; r: number; rot: number; kind: number }

const KIND_PATTERN: BuildingKind[] = [
  'Apartment', 'Office', 'Shop', 'School', 'Apartment', 'Apartment', 'Office', 'Shop', 'Apartment',
  'School', 'Apartment', 'Office', 'Apartment', 'Shop', 'Apartment', 'Office', 'Apartment', 'School', 'Apartment',
];
export const kindAt = (i: number) => KIND_PATTERN[i % KIND_PATTERN.length];
export const kindLabel = (k: BuildingKind) => ({ Apartment: 'Home', Office: 'Office', Shop: 'Shop', School: 'School' })[k];
/** Okabe–Ito hue per kind; the word carries the meaning, colour reinforces it. */
export const kindColour = (k: BuildingKind) => ({ Apartment: 0x56b4e9, Office: 0x009e73, Shop: 0xe69f00, School: 0xcc79a7 })[k];
export const sceneIdFor = (k: BuildingKind, i: number) =>
  `${({ Apartment: 'personal', Office: 'workplace', Shop: 'social', School: 'academic' })[k]}_${i + 1}`;

export const PLAZA_RADIUS = 13;
const MAX_HALF_EXTENT = 9.6;
const ROAD_COUNT = 5, ROAD_ANGLE_OFFSET = f(0.4), ROAD_WIDTH = 2.5;
const ROAD_LENGTH = f(SETTLE_R * f(0.9));
const ROAD_LIFT = 0.03, PLAZA_LIFT = 0.04;
const ROAD_PAVING_START = PLAZA_RADIUS - 0.5;

function clearOfRoads(x: number, z: number, half: number): boolean {
  const dx = x - SETTLE_X, dz = z - SETTLE_Z;
  const reach = ROAD_WIDTH * 0.5 + half;
  for (let i = 0; i < ROAD_COUNT; i++) {
    const a = f(f(f(i / ROAD_COUNT) * PI_F) * 2) + ROAD_ANGLE_OFFSET;
    const ax = f(Math.sin(a)), az = f(Math.cos(a));
    const along = dx * ax + dz * az;
    if (along < 0 || along > ROAD_LENGTH) continue;
    if (Math.abs(dx * az - dz * ax) < reach) return false;
  }
  return true;
}

/** SettlementBuilder.BuildPlans — consumes the world RNG in the same order. */
export function buildPlans(rng: SimulationRng): Plan[] {
  const placed: Plan[] = [];
  let guard = 0;
  const minR = PLAZA_RADIUS + MAX_HALF_EXTENT, maxR = SETTLE_R - 6;
  while (placed.length < 19 && guard++ < 40000) {
    const a = f(f(rng.next() * PI_F) * 2);
    const rad = rng.range(f(4.2), f(6.4));
    const half = f(rad * 1.5);
    const r = f(minR + f(f(Math.sqrt(rng.next())) * (maxR - minR)));
    const x = f(SETTLE_X + f(f(Math.cos(a)) * r));
    const z = f(SETTLE_Z + f(f(Math.sin(a)) * r));
    const ds = Math.sqrt((x - SETTLE_X) ** 2 + (z - SETTLE_Z) ** 2);
    if (ds > maxR) continue;
    if (ds - half < PLAZA_RADIUS) continue;
    if (!walkable(x, z)) continue;
    if (!clearOfRoads(x, z, half)) continue;
    if (placed.some((p) => Math.sqrt((p.x - x) ** 2 + (p.z - z) ** 2) < p.rad + rad + 3.4)) continue;
    placed.push({ x, z, rad, r: rng.next(), rot: f(rng.next() * PI_F), kind: rng.next() });
  }
  return placed;
}

// ---------------------------------------------------------------- materials
const mats = new Map<string, THREE.MeshStandardMaterial>();
function mat(albedo: number, rough = 0.85, glow?: number, glowEnergy = 0.85): THREE.MeshStandardMaterial {
  const key = `${albedo}|${rough}|${glow}|${glowEnergy}`;
  let m = mats.get(key);
  if (!m) {
    m = new THREE.MeshStandardMaterial({ color: albedo, roughness: rough, metalness: 0 });
    if (glow !== undefined) {
      m.emissive = new THREE.Color(glow);
      m.emissiveIntensity = glowEnergy;
    }
    mats.set(key, m);
  }
  return m;
}

const HOME_WALLS = [0xd9cdb8, 0xc9bfa9, 0xe0d4c0, 0xbfae96, 0xcfc4ae, 0xc4b49c];
const HOME_ROOFS = [0x7a4a3c, 0x6b5340, 0x8a5a44, 0x5f4a3e, 0x74503f];
const SHOP_WALLS = [0xe8d6b0, 0xd98f6a, 0xf0e4cf, 0xc9a27e];
const STONE = 0x7d776d, WARM_GLASS = 0xffe0b0, WARM_GLOW = 0xffc478, TRIM = 0xe8e2d4;

function add(parent: THREE.Object3D, geo: THREE.BufferGeometry, m: THREE.Material, x: number, y: number, z: number, rotX = 0, rotY = 0) {
  const mesh = new THREE.Mesh(geo, m);
  mesh.position.set(x, y, z);
  mesh.rotation.set(rotX, rotY, 0, 'YXZ');
  mesh.castShadow = true;
  mesh.receiveShadow = true;
  parent.add(mesh);
  return mesh;
}
const box = (p: THREE.Object3D, sx: number, sy: number, sz: number, x: number, y: number, z: number, m: THREE.Material, rotX = 0) =>
  add(p, new THREE.BoxGeometry(sx, sy, sz), m, x, y, z, rotX);
const cyl = (p: THREE.Object3D, top: number, bottom: number, h: number, x: number, y: number, z: number, m: THREE.Material, seg = 12) =>
  add(p, new THREE.CylinderGeometry(top, bottom, h, seg), m, x, y, z);

/** Godot PrismMesh: triangle in XY (apex centred on top), extruded along Z. */
function prism(sx: number, sy: number, sz: number): THREE.BufferGeometry {
  const x = sx / 2, y = sy / 2, z = sz / 2;
  const L = [-x, -y], R = [x, -y], A = [0, y];
  const v = (p: number[], zz: number) => [p[0], p[1], zz];
  const tris = [
    [v(L, z), v(R, z), v(A, z)], [v(R, -z), v(L, -z), v(A, -z)],
    [v(L, -z), v(L, z), v(A, z)], [v(L, -z), v(A, z), v(A, -z)],
    [v(R, z), v(R, -z), v(A, -z)], [v(R, z), v(A, -z), v(A, z)],
    [v(L, -z), v(R, -z), v(R, z)], [v(L, -z), v(R, z), v(L, z)],
  ];
  const g = new THREE.BufferGeometry();
  g.setAttribute('position', new THREE.Float32BufferAttribute(tris.flat(2), 3));
  g.computeVertexNormals();
  return g;
}

const plinth = (g: THREE.Object3D, w: number, d: number) => box(g, w + 0.25, 1.4, d + 0.25, 0, -0.55, 0, mat(STONE, 0.95));

function home(g: THREE.Object3D, w: number, d: number, r: number, i: number): number {
  const wallH = 3.2 + r * 2.6, roofH = 2.0 + r * 1.2;
  plinth(g, w, d);
  box(g, w, wallH, d, 0, wallH / 2, 0, mat(HOME_WALLS[i % HOME_WALLS.length]));
  const roofMat = mat(HOME_ROOFS[i % HOME_ROOFS.length], 0.78);
  add(g, prism(d + 0.7, roofH, w + 0.5), roofMat, 0, wallH + roofH / 2, 0, 0, Math.PI / 2);
  box(g, 0.7, roofH + 0.4, 0.7, w * 0.28, wallH + roofH * 0.5, -d * 0.18, roofMat);
  const glass = mat(WARM_GLASS, 0.3, WARM_GLOW);
  const floors = wallH > 4.6 ? 2 : 1;
  for (let fl = 0; fl < floors; fl++) for (const s of [-1, 1]) box(g, 1.0, 0.9, 0.1, s * w * 0.3, 1.7 + fl * 2.6, d / 2 + 0.02, glass);
  box(g, 1.8, 0.2, 0.9, 0, 0.1, d / 2 + 0.45, mat(STONE, 0.95));
  return d / 2;
}

function office(g: THREE.Object3D, w: number, d: number, r: number, accent: number): number {
  const tw = w * 0.8, td = d * 0.85;
  const floors = 4 + Math.trunc(r * 4);
  const floorH = 3.2, h = floors * floorH;
  const concrete = mat(0xb8bcc2, 0.8), dark = mat(0x4a4f57, 0.6), glass = mat(0x6f9fc4, 0.15, 0x9fc9ec, 0.55);
  plinth(g, tw, td);
  box(g, tw, h, td, 0, h / 2, 0, concrete);
  for (let fl = 1; fl < floors; fl++) box(g, tw + 0.06, 1.7, td + 0.06, 0, fl * floorH + 1.6, 0, glass);
  box(g, tw * 0.75, 2.4, 0.1, 0, 1.3, td / 2 + 0.03, glass);
  box(g, 3.2, 0.18, 1.8, 0, 2.75, td / 2 + 0.9, dark);
  box(g, 3.2, 0.25, 0.12, 0, 2.98, td / 2 + 1.78, mat(accent, 0.5, accent, 0.6));
  box(g, tw + 0.3, 0.5, td + 0.3, 0, h + 0.25, 0, dark);
  box(g, tw * 0.35, 1.2, td * 0.3, -tw * 0.15, h + 1.1, -td * 0.1, concrete);
  cyl(g, 0.05, 0.08, 3.5, tw * 0.3, h + 2.2, -td * 0.25, dark, 6);
  return td / 2;
}

function shop(g: THREE.Object3D, w: number, d: number, i: number, accent: number): number {
  const sw = w, sd = d * 0.8, h = 4.2;
  const trim = mat(0x5a4636, 0.7), white = mat(TRIM, 0.8), accentMat = mat(accent, 0.7);
  plinth(g, sw, sd);
  box(g, sw, h, sd, 0, h / 2, 0, mat(SHOP_WALLS[i % SHOP_WALLS.length]));
  box(g, sw + 0.3, 0.45, sd + 0.3, 0, h + 0.2, 0, trim);
  const paneW = sw / 2 - 1.2;
  const glass = mat(WARM_GLASS, 0.25, WARM_GLOW, 1.0);
  for (const s of [-1, 1]) box(g, paneW, 2.2, 0.1, s * (0.75 + paneW / 2), 1.6, sd / 2 + 0.03, glass);
  box(g, sw * 0.6, 0.8, 0.12, 0, h - 0.55, sd / 2 + 0.08, mat(accent, 0.5, accent, 0.4));
  const stripes = 8, span = sw * 0.9, stripeW = span / stripes;
  for (let k = 0; k < stripes; k++)
    box(g, stripeW, 0.06, 1.7, -span / 2 + (k + 0.5) * stripeW, 3.0, sd / 2 + 0.75, k % 2 === 0 ? accentMat : white, 0.35);
  for (const s of [-1, 1]) {
    const ax = s * sw * 0.32, az = sd / 2 + 2.3;
    cyl(g, 0.45, 0.45, 0.06, ax, 0.75, az, white);
    cyl(g, 0.05, 0.05, 2.3, ax, 1.15, az, trim, 6);
    cyl(g, 0, 1.1, 0.5, ax, 2.3, az, accentMat, 8);
  }
  return sd / 2;
}

function school(g: THREE.Object3D, w: number, d: number, accent: number): number {
  const bw = w, bd = d * 0.75, h = 7.0;
  const brick = mat(0x9c4a3a, 0.9), trim = mat(TRIM, 0.75), slate = mat(0x3f4650, 0.7), glass = mat(WARM_GLASS, 0.3, WARM_GLOW);
  plinth(g, bw, bd);
  box(g, bw, h, bd, 0, h / 2, 0, brick);
  box(g, bw + 0.3, 0.4, bd + 0.3, 0, h + 0.2, 0, trim);
  const cols = Math.max(2, Math.trunc(bw / 2.2));
  for (let row = 0; row < 2; row++)
    for (let c = 0; c < cols; c++) {
      const x = -bw / 2 + ((c + 0.5) * bw) / cols;
      if (Math.abs(x) < 2.6) continue;
      box(g, 1.0, 1.4, 0.1, x, 1.9 + row * 3.0, bd / 2 + 0.02, glass);
    }
  const pz = bd / 2 + 1.0;
  for (const x of [-2.1, -1.3, 1.3, 2.1]) cyl(g, 0.2, 0.24, 5.0, x, 2.5, pz, trim);
  box(g, 4.9, 0.45, 1.5, 0, 5.2, bd / 2 + 0.75, trim);
  add(g, prism(4.9, 1.3, 1.5), trim, 0, 6.08, bd / 2 + 0.75);
  box(g, 5.2, 0.3, 1.8, 0, 0.15, bd / 2 + 0.9, mat(STONE, 0.95));
  box(g, 1.8, 1.6, 1.8, 0, h + 1.2, 0, trim);
  add(g, new THREE.CylinderGeometry(0, 1.45, 1.4, 4), slate, 0, h + 2.7, 0, 0, Math.PI / 4);
  add(g, new THREE.CylinderGeometry(0.55, 0.55, 0.08, 16), mat(0xf5f1e6, 0.5, 0xf5f1e6, 0.3), 0, h + 1.25, 0.92, Math.PI / 2);
  const px = bw * 0.42, pzz = bd / 2 + 1.6;
  cyl(g, 0.05, 0.07, 8.0, px, 4.0, pzz, slate, 6);
  box(g, 1.4, 0.9, 0.04, px + 0.72, 7.4, pzz, mat(accent, 0.7));
  return bd / 2;
}

// ---------------------------------------------------------------- labels
export function textSprite(text: string, colour: string, worldHeight: number): THREE.Sprite {
  const pad = 12, px = 64;
  const c = document.createElement('canvas');
  const ctx = c.getContext('2d')!;
  ctx.font = `600 ${px}px "IBM Plex Sans", system-ui, sans-serif`;
  c.width = Math.ceil(ctx.measureText(text).width) + pad * 2;
  c.height = px + pad * 2;
  ctx.font = `600 ${px}px "IBM Plex Sans", system-ui, sans-serif`;
  ctx.textAlign = 'center';
  ctx.textBaseline = 'middle';
  ctx.lineWidth = 14;
  ctx.strokeStyle = 'rgba(0,0,0,0.85)';
  ctx.strokeText(text, c.width / 2, c.height / 2);
  ctx.fillStyle = colour;
  ctx.fillText(text, c.width / 2, c.height / 2);
  const tex = new THREE.CanvasTexture(c);
  tex.colorSpace = THREE.SRGBColorSpace;
  const s = new THREE.Sprite(new THREE.SpriteMaterial({ map: tex, depthWrite: false }));
  s.scale.set((worldHeight * c.width) / c.height, worldHeight, 1);
  return s;
}

function portalMarker(label: string, colour: number): THREE.Group {
  const root = new THREE.Group();
  const m = new THREE.MeshStandardMaterial({ color: colour, emissive: colour, emissiveIntensity: 1.4, roughness: 0.4 });
  for (const x of [-0.78, 0.78]) add(root, new THREE.BoxGeometry(0.16, 2.3, 0.16), m, x, 1.15, 0);
  add(root, new THREE.BoxGeometry(1.72, 0.16, 0.16), m, 0, 2.32, 0);
  // Godot's Label3D is 48 px at 0.006 m/px (~0.3 m); doubled so the word survives the browser's
  // lower default resolution. Noted as a deliberate presentation difference in the README.
  const s = textSprite(label, '#' + colour.toString(16).padStart(6, '0'), 0.62);
  s.position.set(0, 2.85, 0);
  root.add(s);
  return root;
}

export interface Building {
  index: number;
  kind: BuildingKind;
  label: string;
  sceneId: string;
  group: THREE.Group;
  door: THREE.Vector3;
}

export function buildSettlement(plans: Plan[]): { root: THREE.Group; buildings: Building[] } {
  const root = new THREE.Group();
  root.name = 'Settlement';
  const buildings: Building[] = [];
  const roofMat = mat(0x6b5340, 0.78), glassMat = mat(0xffe0b0, 0.3, 0xffc478, 0.85);
  const pathMat = mat(0x8a8377, 0.98), doorMat = mat(0x54402f, 0.8);

  plans.forEach((plan, i) => {
    const kind = kindAt(i);
    const g = new THREE.Group();
    const w = plan.rad * 1.5, d = plan.rad * 1.25;
    const accent = kindColour(kind);
    const front =
      kind === 'Office' ? office(g, w, d, plan.r, accent)
      : kind === 'Shop' ? shop(g, w, d, i, accent)
      : kind === 'School' ? school(g, w, d, accent)
      : home(g, w, d, plan.r, i);
    box(g, 1.15, 2.1, 0.14, 0, 1.05, front + 0.02, doorMat);
    const marker = portalMarker(kindLabel(kind), accent);
    marker.position.set(0, 0, front + 0.09);
    g.add(marker);
    g.position.set(plan.x, heightAt(plan.x, plan.z), plan.z);
    g.rotation.y = plan.rot;
    g.userData = { buildingIndex: i };
    root.add(g);
    g.updateMatrixWorld(true);
    buildings.push({
      index: i, kind, label: kindLabel(kind), sceneId: sceneIdFor(kind, i), group: g,
      door: new THREE.Vector3(0, 1.05, front + 0.02).applyMatrix4(g.matrixWorld),
    });
  });

  root.add(paving(plazaPaving(), pathMat));
  for (let r = 0; r < ROAD_COUNT; r++) root.add(paving(roadPaving(r), pathMat));

  // Well at the plaza edge.
  const wx = SETTLE_X + 8, wz = SETTLE_Z + 3, wy = surfaceHeightAt(wx, wz);
  cyl(root, 1.3, 1.45, 1.1, wx, wy + 0.55, wz, mat(0x8a8078, 0.95));
  cyl(root, 1.05, 1.05, 0.1, wx, wy + 1.05, wz, mat(0x2f6f74, 0.3));
  add(root, new THREE.CylinderGeometry(0, 1.7, 2.0, 4), roofMat, wx, wy + 2.4, wz, 0, Math.PI / 4);

  // Benches around the plaza.
  for (let b = 0; b < 6; b++) {
    const a = (b / 6) * TAU + 0.2, rr = 10.5;
    const bx = SETTLE_X + Math.cos(a) * rr, bz = SETTLE_Z + Math.sin(a) * rr;
    const bench = new THREE.Group();
    bench.position.set(bx, surfaceHeightAt(bx, bz) + PLAZA_LIFT, bz);
    bench.rotation.y = a + Math.PI / 2;
    box(bench, 2.2, 0.1, 0.55, 0, 0.45, 0, doorMat);
    for (const lx of [-0.85, 0.85]) box(bench, 0.12, 0.4, 0.45, lx, 0.2, 0, doorMat);
    root.add(bench);
  }
  // Desks with emissive monitors.
  for (let k = 0; k < 4; k++) {
    const a = (k / 4) * TAU + 0.9, rr = 15;
    const dx = SETTLE_X + Math.cos(a) * rr, dz = SETTLE_Z + Math.sin(a) * rr;
    const desk = new THREE.Group();
    desk.position.set(dx, heightAt(dx, dz), dz);
    desk.rotation.y = a;
    box(desk, 2.0, 0.12, 0.9, 0, 0.95, 0, doorMat);
    box(desk, 0.8, 0.5, 0.08, 0, 1.35, -0.25, glassMat);
    root.add(desk);
  }
  return { root, buildings };
}

// ---------------------------------------------------------------- paving
const onGround = (x: number, z: number, lift: number) => new THREE.Vector3(x, surfaceHeightAt(x, z) + lift, z);

function quad(out: number[], a: THREE.Vector3, b: THREE.Vector3, c: THREE.Vector3, d: THREE.Vector3) {
  up(out, a, b, c);
  up(out, a, c, d);
}
function up(out: number[], a: THREE.Vector3, b: THREE.Vector3, c: THREE.Vector3) {
  const y = (b.z - a.z) * (c.x - a.x) - (b.x - a.x) * (c.z - a.z); // (b-a)×(c-a).y
  if (Math.abs(y) < 1e-6) return;
  if (y < 0) [b, c] = [c, b]; // three: counter-clockwise from above faces up
  out.push(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
}

function plazaPaving(): number[] {
  const rings = 13, sectors = 48, out: number[] = [];
  const at = (k: number, s: number) => {
    const r = (PLAZA_RADIUS * k) / rings, a = (s / sectors) * TAU;
    return onGround(SETTLE_X + Math.cos(a) * r, SETTLE_Z + Math.sin(a) * r, PLAZA_LIFT);
  };
  for (let k = 0; k < rings; k++) for (let s = 0; s < sectors; s++) quad(out, at(k, s), at(k, s + 1), at(k + 1, s + 1), at(k + 1, s));
  return out;
}

function roadPaving(index: number): number[] {
  const a = (index / ROAD_COUNT) * Math.PI * 2 + ROAD_ANGLE_OFFSET;
  const ax = Math.sin(a), az = Math.cos(a);
  const columns = 8, steps = Math.ceil((ROAD_LENGTH - ROAD_PAVING_START) / 0.25);
  const at = (k: number, c: number) => {
    const dd = ROAD_PAVING_START + ((ROAD_LENGTH - ROAD_PAVING_START) * k) / steps;
    const lat = ROAD_WIDTH * (c / columns - 0.5);
    return onGround(SETTLE_X + ax * dd + az * lat, SETTLE_Z + az * dd - ax * lat, ROAD_LIFT);
  };
  const out: number[] = [];
  for (let k = 0; k < steps; k++) for (let c = 0; c < columns; c++) quad(out, at(k, c), at(k, c + 1), at(k + 1, c + 1), at(k + 1, c));
  return out;
}

function paving(tris: number[], m: THREE.Material): THREE.Mesh {
  const g = new THREE.BufferGeometry();
  g.setAttribute('position', new THREE.Float32BufferAttribute(tris, 3));
  g.computeVertexNormals();
  const mesh = new THREE.Mesh(g, m);
  mesh.receiveShadow = true;
  return mesh;
}
