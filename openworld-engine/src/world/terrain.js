// Terrain: heightfield mesh with procedural PBR textures (color, normal,
// roughness baked from the height field at load time — no vertex colors).
import * as THREE from 'three';
import { makeNoise2D, makeFbm, mulberry32 } from './noise.js';
import { createTerrainDetail } from '../materials/pbr.js';

// --- small hash-based value noise for texture generation ---
function noiseHash(x, y, seed) {
  let h = (seed + x * 374761393 + y * 668265263) | 0;
  h = (h ^ (h >>> 13)) * 1274126177;
  return ((h ^ (h >>> 16)) >>> 0) / 4294967295;
}
function noise2D(x, y, seed) {
  const xi = Math.floor(x), yi = Math.floor(y);
  const xf = x - xi, yf = y - yi;
  const u = xf * xf * (3 - 2 * xf);
  const v = yf * yf * (3 - 2 * yf);
  const a = noiseHash(xi, yi, seed), b = noiseHash(xi + 1, yi, seed);
  const c = noiseHash(xi, yi + 1, seed), d = noiseHash(xi + 1, yi + 1, seed);
  return a + (b - a) * u + (c - a) * v + (a - b - c + d) * u * v;
}
function fbm2D(x, y, seed, octaves) {
  let sum = 0, amp = 1, f = 1, total = 0;
  for (let i = 0; i < octaves; i++) {
    sum += amp * noise2D(x * f, y * f, seed + i * 137);
    total += amp; amp *= 0.5; f *= 2;
  }
  return sum / total;
}
function lerpHex(a, b, t) {
  const ar = (a >> 16) & 0xff, ag = (a >> 8) & 0xff, ab = a & 0xff;
  const br = (b >> 16) & 0xff, bg = (b >> 8) & 0xff, bb = b & 0xff;
  return (Math.round(ar + (br - ar) * t) << 16) | (Math.round(ag + (bg - ag) * t) << 8) | Math.round(ab + (bb - ab) * t);
}
function makeTexture(canvas, colorSpace) {
  const t = new THREE.CanvasTexture(canvas);
  t.wrapS = THREE.RepeatWrapping; t.wrapT = THREE.RepeatWrapping;
  t.colorSpace = colorSpace;
  return t;
}

export function createHeightField(config) {
  const noise = makeNoise2D(config.seed);
  const fbm = makeFbm(noise, 5);
  const macro = makeFbm(makeNoise2D(config.seed + 99), 3);
  const size = config.size;

  // Island falloff: continent in the middle, ocean at the edges.
  function baseHeight(nx, ny) {
    const dx = nx - 0.5, dy = ny - 0.5;
    const dist = Math.sqrt(dx * dx + dy * dy) * 2; // 0 center -> ~1 edge
    const continent = 1 - Math.pow(Math.min(1, Math.max(0, dist)), 2.2);
    const hills = fbm(nx * 6, ny * 6) * 0.5 + 0.5;
    const mountains = Math.pow(Math.max(0, macro(nx * 3 + 7, ny * 3 - 3) * 0.5 + 0.5), 2);
    let h = continent * (0.25 + hills * 0.55 + mountains * 0.9) - 0.18;
    return h * config.heightScale;
  }

  function sample(x, z) {
    const nx = x / size + 0.5, ny = z / size + 0.5;
    return baseHeight(nx, ny);
  }

  return { sample, size };
}

const BIOME = {
  sand: new THREE.Color(0xc2b280),
  grass: new THREE.Color(0x4d7c3a),
  grassDry: new THREE.Color(0x7d9b4a),
  rock: new THREE.Color(0x6b6f75),
  snow: new THREE.Color(0xe8edf2),
};

export function buildTerrain(scene, heightField, config, pbr) {
  const { size, segments, seaLevel } = config;
  const geo = new THREE.PlaneGeometry(size, size, segments, segments);
  geo.rotateX(-Math.PI / 2);
  const pos = geo.attributes.position;
  const colors = new Float32Array(pos.count * 3);
  const rand = mulberry32(config.seed + 7);

  const cSand = BIOME.sand, cGrass = BIOME.grass, cDry = BIOME.grassDry;
  const cRock = BIOME.rock, cSnow = BIOME.snow;
  const tmp = new THREE.Color();

  // Second sampler for slope variation so biomes aren't perfectly banded.
  const detail = makeFbm(makeNoise2D(config.seed + 5), 3);

  for (let i = 0; i < pos.count; i++) {
    const x = pos.getX(i), z = pos.getZ(i);
    const h = heightField.sample(x, z);
    pos.setY(i, h);

    const n = detail(x * 0.02, z * 0.02) * 0.5 + 0.5;
    if (h < seaLevel + 0.6) tmp.copy(cSand);
    else if (h < seaLevel + 7) tmp.copy(cGrass).lerp(cDry, n * 0.7);
    else if (h < seaLevel + 15) tmp.copy(cRock).lerp(cGrass, (1 - n) * 0.25);
    else tmp.copy(cRock).lerp(cSnow, Math.min(1, (h - seaLevel - 15) / 8));

    const jitter = 0.94 + rand() * 0.12;
    colors[i * 3] = tmp.r * jitter;
    colors[i * 3 + 1] = tmp.g * jitter;
    colors[i * 3 + 2] = tmp.b * jitter;
  }
  geo.setAttribute('color', new THREE.BufferAttribute(colors, 3));
  geo.computeVertexNormals();

  const detailMaps = createTerrainDetail({
    ...config, ...pbr, tileSize: pbr?.terrainTileSize,
  }, heightField);
  const mat = new THREE.MeshStandardMaterial({
    vertexColors: true,
    roughness: 1.0,
    metalness: 0.0,
    map: detailMaps.color,
    roughnessMap: detailMaps.roughness,
    normalMap: detailMaps.normal,
    normalScale: new THREE.Vector2(pbr?.terrainNormalScale ?? 1.6, pbr?.terrainNormalScale ?? 1.6),
  });
  const mesh = new THREE.Mesh(geo, mat);
  mesh.receiveShadow = true;
  mesh.name = 'terrain';
  scene.add(mesh);
  return mesh;
}
