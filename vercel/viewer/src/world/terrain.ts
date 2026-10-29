// Port of world-engine-godot/TerrainBuilder.cs (mesh + vertex palette) and
// WaterBuilder.cs (the unshaded wave shader). Static scene data, not state.
import * as THREE from 'three';
import { SEED, WATER, WORLD, TERRAIN_SEGMENTS, fbm, heightAt, slopeAt, smoothstep, lerp } from './geometry';

type RGB = [number, number, number];
const hex = (h: number): RGB => [((h >> 16) & 255) / 255, ((h >> 8) & 255) / 255, (h & 255) / 255];
const mix = (a: RGB, b: RGB, t: number): RGB => [lerp(a[0], b[0], t), lerp(a[1], b[1], t), lerp(a[2], b[2], t)];
const scale = (a: RGB, s: number): RGB => [a[0] * s, a[1] * s, a[2] * s];

// TerrainBuilder.ColorAt palette, authored as sRGB.
const SAND = hex(0xc9b48c), GRASS = hex(0x5c7444), GRASS2 = hex(0x48603a), ROCK = hex(0x7b7468), DARK = hex(0x4c4740);

function colorAt(x: number, z: number, h: number): RGB {
  const slope = slopeAt(x, z);
  const grain = fbm(x * 0.06, z * 0.06, 3, SEED + 991);
  let c: RGB;
  if (h < WATER - 2.6) c = DARK;
  else if (h < WATER + 1.5) c = SAND;
  else {
    c = mix(GRASS, GRASS2, grain);
    c = mix(c, ROCK, smoothstep(0.28, 0.72, slope));
    c = mix(c, SAND, smoothstep(2.4, 0.9, h) * 0.25);
    c = scale(c, 0.86 + grain * 0.3);
  }
  const shade = 0.94 + fbm(x * 0.012, z * 0.012, 2, SEED + 77) * 0.14;
  return scale(c, shade);
}

/** Heights on the terrain grid, shared by the mesh, the minimap and anything else that needs them. */
export function sampleGrid(seg = TERRAIN_SEGMENTS): Float32Array {
  const n = seg + 1;
  const out = new Float32Array(n * n);
  const step = WORLD / seg;
  for (let j = 0; j < n; j++)
    for (let i = 0; i < n; i++) out[j * n + i] = heightAt(-WORLD / 2 + i * step, -WORLD / 2 + j * step);
  return out;
}

export function buildTerrain(grid: Float32Array, seg = TERRAIN_SEGMENTS): THREE.Mesh {
  const n = seg + 1;
  const step = WORLD / seg;
  const pos = new Float32Array(n * n * 3);
  const col = new Float32Array(n * n * 3);
  const c = new THREE.Color();
  for (let j = 0; j < n; j++)
    for (let i = 0; i < n; i++) {
      const k = j * n + i;
      const x = -WORLD / 2 + i * step, z = -WORLD / 2 + j * step, y = grid[k];
      pos.set([x, y, z], k * 3);
      const rgb = colorAt(x, z, y);
      // Godot reads these as sRGB (VertexColorIsSrgb); three wants linear vertex colours.
      c.setRGB(rgb[0], rgb[1], rgb[2], THREE.SRGBColorSpace);
      col.set([c.r, c.g, c.b], k * 3);
    }
  // Same diagonal split as Godot: triangles (a, b, c) and (a, c, d), wound for three's CCW front face.
  const idx = new Uint32Array(seg * seg * 6);
  let p = 0;
  for (let j = 0; j < seg; j++)
    for (let i = 0; i < seg; i++) {
      const a = j * n + i, b = j * n + i + 1, cc = (j + 1) * n + i + 1, d = (j + 1) * n + i;
      idx.set([a, cc, b, a, d, cc], p);
      p += 6;
    }
  const g = new THREE.BufferGeometry();
  g.setAttribute('position', new THREE.BufferAttribute(pos, 3));
  g.setAttribute('color', new THREE.BufferAttribute(col, 3));
  g.setIndex(new THREE.BufferAttribute(idx, 1));
  g.computeVertexNormals();
  const mesh = new THREE.Mesh(g, new THREE.MeshStandardMaterial({ vertexColors: true, roughness: 0.97, metalness: 0 }));
  mesh.receiveShadow = true;
  mesh.name = 'Terrain';
  return mesh;
}

/** WaterBuilder.FogDensity */
export const WATER_FOG_DENSITY = 0.0011;

export function buildWater(): { mesh: THREE.Mesh; uniforms: Record<string, THREE.IUniform> } {
  const srgb = (h: number) => new THREE.Color().setHex(h, THREE.SRGBColorSpace);
  const uniforms: Record<string, THREE.IUniform> = {
    u_time: { value: 0 },
    u_deep: { value: srgb(0x16323d) },
    u_shallow: { value: srgb(0x2f6f74) },
    u_sky: { value: srgb(0xc3d4dd) },
    u_sun_color: { value: srgb(0xfff2d6) },
    u_sun_dir: { value: new THREE.Vector3(0.5, 0.7, 0.4).normalize() },
    u_fog_color: { value: srgb(0x9fb6c4) },
    u_fog_density: { value: WATER_FOG_DENSITY },
    u_light: { value: 1 },
    u_waves: { value: 1 },
  };
  const waves = /* glsl */ `
    uniform float u_time; uniform float u_waves;
    float wave(vec2 p, vec2 dir, float freq, float speed) { return sin(dot(p, dir) * freq + u_time * speed); }
    float waves(vec2 p) {
      float s = 0.0;
      s += wave(p, normalize(vec2( 1.00, 0.32)), 0.052, 1.15) * 0.30;
      s += wave(p, normalize(vec2(-0.42, 1.00)), 0.081, 0.95) * 0.17;
      s += wave(p, normalize(vec2( 0.72,-0.68)), 0.173, 1.70) * 0.08;
      s += wave(p, normalize(vec2(-0.86,-0.51)), 0.290, 2.35) * 0.04;
      return s * u_waves;
    }`;
  const mat = new THREE.ShaderMaterial({
    uniforms,
    transparent: true,
    vertexShader: /* glsl */ `
      ${waves}
      varying vec3 v_world;
      void main() {
        vec4 w = modelMatrix * vec4(position, 1.0);
        w.y += waves(w.xz) * 0.5;
        v_world = w.xyz;
        gl_Position = projectionMatrix * viewMatrix * w;
      }`,
    fragmentShader: /* glsl */ `
      ${waves}
      uniform vec3 u_deep, u_shallow, u_sky, u_sun_color, u_sun_dir, u_fog_color;
      uniform float u_fog_density, u_light;
      varying vec3 v_world;
      void main() {
        vec2 p = v_world.xz;
        float h = waves(p);
        float e = 1.6;
        float hx = waves(p + vec2(e, 0.0)) - waves(p - vec2(e, 0.0));
        float hz = waves(p + vec2(0.0, e)) - waves(p - vec2(0.0, e));
        vec3 N = normalize(vec3(-hx * 0.85, 1.0, -hz * 0.85));
        vec3 V = normalize(cameraPosition - v_world);
        vec3 L = normalize(u_sun_dir);
        float fres = pow(1.0 - clamp(dot(N, V), 0.0, 1.0), 4.2);
        float spec = pow(max(dot(reflect(-L, N), V), 0.0), 180.0);
        float glitter = pow(max(dot(reflect(-L, N), V), 0.0), 28.0) * 0.14;
        vec3 col = mix(u_deep, u_shallow, clamp(h * 0.35 + 0.5, 0.0, 1.0)) * u_light;
        col = mix(col, u_sky, clamp(fres * 0.85, 0.0, 1.0));
        col += u_sun_color * (spec * 1.3 + glitter);
        float dist = length(cameraPosition - v_world);
        float f = 1.0 - exp(-dist * dist * u_fog_density * u_fog_density * 12.0);
        col = mix(col, u_fog_color, clamp(f, 0.0, 1.0));
        gl_FragColor = vec4(col, mix(0.86, 0.97, fres));
        #include <colorspace_fragment>
      }`,
  });
  const geo = new THREE.PlaneGeometry(2600, 2600, 96, 96);
  geo.rotateX(-Math.PI / 2);
  const mesh = new THREE.Mesh(geo, mat);
  mesh.position.y = WATER;
  mesh.name = 'Water';
  mesh.renderOrder = 1;
  return { mesh, uniforms };
}
