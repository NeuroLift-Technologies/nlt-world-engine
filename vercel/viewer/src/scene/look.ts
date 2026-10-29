// Presentation-only lighting and post-processing. Nothing here changes geometry, positions or
// state: it changes how the same Godot-derived world is lit and finished on screen.
import * as THREE from 'three';
import { EffectComposer } from 'three/examples/jsm/postprocessing/EffectComposer.js';
import { RenderPass } from 'three/examples/jsm/postprocessing/RenderPass.js';
import { GTAOPass } from 'three/examples/jsm/postprocessing/GTAOPass.js';
import { UnrealBloomPass } from 'three/examples/jsm/postprocessing/UnrealBloomPass.js';
import { OutputPass } from 'three/examples/jsm/postprocessing/OutputPass.js';
import { SMAAPass } from 'three/examples/jsm/postprocessing/SMAAPass.js';

export type LookId = 'golden' | 'midday';
export type Quality = 'high' | 'fast';

export interface Look {
  /** Direction toward the sun (normalised in use). */
  sunDir: THREE.Vector3;
  sunColor: number;
  sunIntensity: number;
  hemiSky: number;
  hemiGround: number;
  hemiIntensity: number;
  envIntensity: number;
  skyTop: number;
  skyHorizon: number;
  /** Warm glow around the sun on the sky dome and in the haze. */
  sunGlow: number;
  fog: number;
  fogDensity: number;
  exposure: number;
  waterSun: number;
}

export const LOOKS: Record<LookId, Look> = {
  // Low sun from the left of the default camera (WorldView yaw 0.6): long shadows across the
  // plaza, warm light on the west faces, cool fill from the sky, the sea staying blue.
  golden: {
    sunDir: new THREE.Vector3(-0.86, 0.34, 0.12),
    sunColor: 0xffc58a,
    sunIntensity: 3.4,
    hemiSky: 0xb9cde0,
    hemiGround: 0x6b5a44,
    hemiIntensity: 1.2,
    envIntensity: 0.55,
    skyTop: 0x4a6f9a,
    skyHorizon: 0xe6d3bb,
    sunGlow: 0xffb36b,
    fog: 0xaebdc6,
    fogDensity: 0.0017,
    exposure: 1.08,
    waterSun: 0xffc48a,
  },
  // Close to the earlier noon stand-in, with the same finishing passes.
  midday: {
    sunDir: new THREE.Vector3(0.5, 0.8, 0.38),
    sunColor: 0xfff0d8,
    sunIntensity: 2.4,
    hemiSky: 0xd6e2ea,
    hemiGround: 0x8a8670,
    hemiIntensity: 1.35,
    envIntensity: 0.45,
    skyTop: 0x5b86b3,
    skyHorizon: 0xc9d8e2,
    sunGlow: 0xfff2d6,
    fog: 0xa9bccb,
    fogDensity: 0.0028,
    exposure: 1.0,
    waterSun: 0xfff2d6,
  },
};

export const srgb = (h: number) => new THREE.Color().setHex(h, THREE.SRGBColorSpace);

/** Sky dome: zenith → horizon gradient, a soft sun disc and a wide warm glow around it. */
export function buildSkyDome(): { mesh: THREE.Mesh; uniforms: Record<string, THREE.IUniform> } {
  const uniforms: Record<string, THREE.IUniform> = {
    top: { value: new THREE.Color() },
    horizon: { value: new THREE.Color() },
    ground: { value: new THREE.Color() },
    glow: { value: new THREE.Color() },
    sunDir: { value: new THREE.Vector3(0, 1, 0) },
  };
  const mat = new THREE.ShaderMaterial({
    side: THREE.BackSide,
    depthWrite: false,
    fog: false,
    uniforms,
    vertexShader: 'varying vec3 vDir; void main(){ vDir = normalize(position); gl_Position = projectionMatrix * modelViewMatrix * vec4(position,1.0); }',
    fragmentShader: /* glsl */ `
      uniform vec3 top, horizon, ground, glow, sunDir; varying vec3 vDir;
      void main(){
        vec3 d = normalize(vDir);
        float h = d.y;
        vec3 c = mix(horizon, top, pow(clamp(h, 0.0, 1.0), 0.48));
        float mu = max(dot(d, normalize(sunDir)), 0.0);
        // Wide forward-scatter glow, strongest near the horizon, plus a small bright disc.
        float haze = pow(mu, 6.0) * (0.55 + 0.45 * (1.0 - clamp(h * 2.0, 0.0, 1.0)));
        c = mix(c, glow, clamp(haze, 0.0, 1.0) * 0.75);
        c += glow * pow(mu, 900.0) * 6.0 + glow * pow(mu, 64.0) * 0.35;
        c = h < 0.0 ? mix(horizon, ground, clamp(-h * 6.0, 0.0, 1.0)) : c;
        gl_FragColor = vec4(c, 1.0);
        #include <tonemapping_fragment>
        #include <colorspace_fragment>
      }`,
  });
  const mesh = new THREE.Mesh(new THREE.SphereGeometry(1800, 48, 24), mat);
  mesh.name = 'Sky';
  mesh.renderOrder = -1;
  mesh.frustumCulled = false;
  mesh.onBeforeRender = (_r, _s, cam) => mesh.position.copy(cam.position);
  return { mesh, uniforms };
}

/**
 * The finishing chain: scene → ground-truth ambient occlusion → subtle bloom (lit windows,
 * the sun's glint on water) → tone mapping + sRGB → SMAA edge smoothing.
 */
export class Finisher {
  composer: EffectComposer;
  private gtao: GTAOPass;
  private bloom: UnrealBloomPass;
  private smaa: SMAAPass;

  constructor(private renderer: THREE.WebGLRenderer, scene: THREE.Scene, camera: THREE.PerspectiveCamera) {
    const size = renderer.getSize(new THREE.Vector2());
    this.composer = new EffectComposer(renderer);
    this.composer.addPass(new RenderPass(scene, camera));
    this.gtao = new GTAOPass(scene, camera, size.x, size.y);
    this.gtao.updateGtaoMaterial({ radius: 1.6, distanceExponent: 1.4, thickness: 2, scale: 1.1, samples: 12 });
    this.gtao.blendIntensity = 0.85;
    this.composer.addPass(this.gtao);
    this.bloom = new UnrealBloomPass(size, 0.32, 0.55, 0.88);
    this.composer.addPass(this.bloom);
    this.composer.addPass(new OutputPass());
    this.smaa = new SMAAPass();
    this.composer.addPass(this.smaa);
  }

  /** AO is tuned for the open world's scale; rooms get a tighter radius. */
  setInterior(interior: boolean) {
    this.gtao.updateGtaoMaterial({ radius: interior ? 0.6 : 1.6, scale: interior ? 1.0 : 1.1 });
    this.bloom.strength = interior ? 0.22 : 0.32;
  }

  setSize(w: number, h: number) {
    this.composer.setPixelRatio(this.renderer.getPixelRatio());
    this.composer.setSize(w, h);
  }

  render(dt: number) {
    this.composer.render(dt);
  }
}

/** Fine surface variation in world space, so the 2.2 m terrain grid stops reading as flat patches. */
export function addTerrainDetail(mat: THREE.MeshStandardMaterial) {
  mat.onBeforeCompile = (shader) => {
    shader.vertexShader = shader.vertexShader
      .replace('#include <common>', '#include <common>\nvarying vec3 vWorldPos;')
      .replace('#include <worldpos_vertex>', '#include <worldpos_vertex>\nvWorldPos = (modelMatrix * vec4(transformed, 1.0)).xyz;');
    shader.fragmentShader = shader.fragmentShader
      .replace('#include <common>', `#include <common>
        varying vec3 vWorldPos;
        float dHash(vec2 p){ return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453); }
        float dNoise(vec2 p){ vec2 i = floor(p), f = fract(p); f = f*f*(3.0-2.0*f);
          return mix(mix(dHash(i), dHash(i+vec2(1,0)), f.x), mix(dHash(i+vec2(0,1)), dHash(i+vec2(1,1)), f.x), f.y); }`)
      .replace('#include <color_fragment>', `#include <color_fragment>
        float dn = dNoise(vWorldPos.xz * 0.42) * 0.55 + dNoise(vWorldPos.xz * 1.7) * 0.3 + dNoise(vWorldPos.xz * 6.3) * 0.15;
        diffuseColor.rgb *= 0.86 + dn * 0.26;`);
  };
}
