// Port of world-engine-godot/VegetationBuilder.cs: seeded tree, rock and grass
// placement with the same RNG stream, drawn as instanced meshes with the same
// per-instance tint and the same wind sway (which reduced motion turns off).
import * as THREE from 'three';
import { SEED, SETTLE_X, SETTLE_Z, WATER, WORLD, SimulationRng, heightAt, slopeAt, PI_F } from './geometry';
import type { Plan } from './settlement';

const f = Math.fround;
interface Spot { x: number; z: number; y: number; scale: number; rot: number; tint: number }

function seededPlacement(count: number, test: (x: number, z: number, r: SimulationRng) => boolean): Spot[] {
  const out: Spot[] = [];
  const r = new SimulationRng(SEED + 4242);
  let guard = 0;
  while (out.length < count && guard++ < count * 60) {
    const a = f(f(r.next() * PI_F) * 2);
    const rad = f(f(Math.sqrt(r.next())) * f(WORLD * f(0.42)));
    const x = f(f(Math.cos(a)) * rad), z = f(f(Math.sin(a)) * rad);
    if (!test(x, z, r)) continue;
    if (out.some((o) => (o.x - x) ** 2 + (o.z - z) ** 2 < 16)) continue;
    out.push({ x, z, y: heightAt(x, z), scale: r.next(), rot: r.next(), tint: r.next() });
  }
  return out;
}

function clearOfSettlement(x: number, z: number, plans: Plan[], pad = 0): boolean {
  if (Math.hypot(x - SETTLE_X, z - SETTLE_Z) < 15 + pad) return false;
  return !plans.some((b) => Math.hypot(x - b.x, z - b.z) < b.rad + 3.5 + pad);
}

/** Uniforms shared by every wind material, so one write per frame drives them all. */
export const windUniforms = { u_time: { value: 0 }, u_wind: { value: 1 } };

function windMat(albedo: number, sway: number, halfH = 1.4): THREE.MeshStandardMaterial {
  const m = new THREE.MeshStandardMaterial({ color: new THREE.Color().setHex(albedo, THREE.SRGBColorSpace), roughness: 1, metalness: 0 });
  m.onBeforeCompile = (shader) => {
    shader.uniforms.u_time = windUniforms.u_time;
    shader.uniforms.u_wind = windUniforms.u_wind;
    shader.uniforms.u_sway = { value: sway };
    shader.vertexShader = 'uniform float u_time; uniform float u_wind; uniform float u_sway;\n' +
      shader.vertexShader.replace('#include <begin_vertex>', `#include <begin_vertex>
        #ifdef USE_INSTANCING
          vec3 ip = (modelMatrix * instanceMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
        #else
          vec3 ip = (modelMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
        #endif
        float ph = ip.x * 0.35 + ip.z * 0.41;
        float wv = sin(u_time * 1.6 + ph) + 0.6 * sin(u_time * 2.7 + ph * 1.7);
        float hh = clamp(position.y, 0.0, 4.0) / 4.0;
        transformed += vec3(wv, 0.0, wv * 0.6) * u_sway * hh * u_wind;
        vShade = clamp(position.y / max(u_halfH, 0.001) * 0.5 + 0.5, 0.0, 1.0);`)
      .replace('#include <common>', '#include <common>\nvarying float vShade;\nuniform float u_halfH;');
    // Self-shadowing stand-in: darker at the base of each canopy layer and trunk, brighter at tips.
    shader.uniforms.u_halfH = { value: halfH };
    shader.fragmentShader = shader.fragmentShader
      .replace('#include <common>', '#include <common>\nvarying float vShade;')
      .replace('#include <color_fragment>', '#include <color_fragment>\ndiffuseColor.rgb *= mix(0.62, 1.12, vShade);');
  };
  return m;
}

const _q = new THREE.Quaternion(), _e = new THREE.Euler(), _m = new THREE.Matrix4(), _s = new THREE.Matrix4();
/** Godot: Transform3D(Basis(Quaternion.FromEuler(e)).Scaled(s), origin) — scale applied in parent space. */
function godotXf(ex: number, ey: number, ez: number, sx: number, sy: number, sz: number, ox: number, oy: number, oz: number) {
  _q.setFromEuler(_e.set(ex, ey, ez, 'YXZ'));
  _m.makeRotationFromQuaternion(_q);
  _s.makeScale(sx, sy, sz);
  _m.premultiply(_s);
  _m.setPosition(ox, oy, oz);
  return _m;
}

function instanced(geo: THREE.BufferGeometry, m: THREE.Material, spots: Spot[], xf: (s: Spot) => THREE.Matrix4, tint: boolean) {
  const mesh = new THREE.InstancedMesh(geo, m, spots.length);
  const c = new THREE.Color();
  spots.forEach((s, i) => {
    mesh.setMatrixAt(i, xf(s));
    if (tint) {
      const v = 0.82 + s.tint * 0.36;
      mesh.setColorAt(i, c.setRGB(v * (0.94 + s.scale * 0.12), v, v * (0.94 + s.scale * 0.1)));
    }
  });
  mesh.castShadow = true;
  mesh.receiveShadow = true;
  mesh.computeBoundingSphere();
  return mesh;
}

const cone = (radius: number, height: number, sides: number) => new THREE.CylinderGeometry(0, radius, height, sides);

export function buildVegetation(plans: Plan[]): THREE.Group {
  const root = new THREE.Group();
  root.name = 'Vegetation';
  const trees = seededPlacement(620, (x, z) => heightAt(x, z) > WATER + 1.6 && slopeAt(x, z) < 0.42 && clearOfSettlement(x, z, plans, 1.5));

  root.add(instanced(new THREE.CylinderGeometry(0.16, 0.3, 2.6, 6), windMat(0x5a4534, 0.03, 1.3), trees, (t) => {
    const sc = 0.72 + t.scale * 0.85;
    return godotXf(0, t.rot * Math.PI * 2, 0, sc, sc * (0.85 + t.tint * 0.4), sc, t.x, t.y - 0.2 + 1.3 * sc, t.z);
  }, true));
  const layer = (yOff: number) => (t: Spot) => {
    const sc = 0.72 + t.scale * 0.85;
    return godotXf(0, t.rot * Math.PI * 2, 0, sc, sc * (0.85 + t.tint * 0.4), sc, t.x, t.y - 0.2 + yOff, t.z);
  };
  root.add(instanced(cone(1.35, 2.9, 8), windMat(0x3d5c36, 0.1, 1.45), trees, layer(3.2), true));
  root.add(instanced(cone(1.05, 2.4, 8), windMat(0x4a7038, 0.13, 1.2), trees, layer(4.5), true));
  root.add(instanced(cone(0.68, 1.8, 8), windMat(0x5c8440, 0.16, 0.9), trees, layer(5.7), true));

  const rocks = seededPlacement(190, (x, z) => heightAt(x, z) > WATER + 0.6 && slopeAt(x, z) > 0.16 && clearOfSettlement(x, z, plans, 0.5));
  const rockMat = new THREE.MeshLambertMaterial({ color: new THREE.Color().setHex(0x7d776c, THREE.SRGBColorSpace), flatShading: true });
  root.add(instanced(new THREE.SphereGeometry(1, 6, 3), rockMat, rocks, (t) => {
    const sc = 0.5 + t.scale * 1.5;
    return godotXf(t.tint * 3, t.rot * 6, t.tint * 2, sc, sc * (0.6 + t.rot * 0.5), sc * (0.8 + t.tint * 0.4), t.x, t.y - 0.25, t.z);
  }, false));

  const grass = seededPlacement(3400, (x, z, r) => {
    const dPlaza = Math.hypot(x - SETTLE_X, z - SETTLE_Z);
    if (dPlaza < 14 && r.next() < 0.85) return false;
    return heightAt(x, z) > WATER + 0.9 && slopeAt(x, z) < 0.45;
  });
  const g = instanced(cone(0.075, 0.62, 3), windMat(0x7d9c4e, 0.22, 0.31), grass, (t) => {
    const sc = 0.7 + t.scale * 0.9;
    return godotXf(0, t.rot * Math.PI * 2, 0, sc, sc * (0.7 + t.tint * 0.8), sc, t.x, t.y - 0.05, t.z);
  }, true);
  g.castShadow = false;
  root.add(g);
  return root;
}
