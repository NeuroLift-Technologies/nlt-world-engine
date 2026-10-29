// The browser projection of the Godot world. It draws static scene geometry
// (ported builders, project-owned interiors) and places agents where the feed
// says they are. It owns no simulation state: nothing here moves an agent,
// decides anything, or advances time on its own.
import * as THREE from 'three';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js';
import * as SkeletonUtils from 'three/examples/jsm/utils/SkeletonUtils.js';
import { SEED, SETTLE_X, SETTLE_Y, SETTLE_Z, SimulationRng, clamp } from '../world/geometry';
import { buildTerrain, buildWater, sampleGrid } from '../world/terrain';
import { buildPlans, buildSettlement, type Building } from '../world/settlement';
import { buildVegetation, windUniforms } from '../world/vegetation';
import type { Agent } from '../feed/types';
import { applyInteriorStyle, frameBounds } from './interiorStyle';

export type SceneKey = 'open_world' | 'personal' | 'workplace' | 'social' | 'academic';
export const INTERIORS: Record<Exclude<SceneKey, 'open_world'>, string> = {
  personal: 'godot/levels/Personal_Level.fbx',
  workplace: 'godot/levels/Workplace_Level.fbx',
  social: 'godot/levels/Social_Level.fbx',
  academic: 'godot/levels/Academic_Level.fbx',
};
export const sceneKeyFor = (sceneId: string): SceneKey =>
  sceneId === 'open_world' ? 'open_world' : ((sceneId.split('_')[0] as SceneKey) in INTERIORS ? (sceneId.split('_')[0] as SceneKey) : 'open_world');

// WorldView.cs camera constants.
const OPEN_WORLD_DIST = 78, OPEN_WORLD_PITCH = 0.42, INTERIOR_PITCH = 0.95, PAN_SPEED = 24, MAX_DIST = 340;
const FOG = new THREE.Color().setHex(0x9fb6c4, THREE.SRGBColorSpace);

export interface Resident {
  id: string;
  root: THREE.Group;
  mixer?: THREE.AnimationMixer;
  walk?: THREE.AnimationAction;
  ring: THREE.Mesh;
}

export class WorldView {
  readonly renderer: THREE.WebGLRenderer;
  readonly scene = new THREE.Scene();
  readonly camera = new THREE.PerspectiveCamera(52, 1, 0.5, 2400);
  readonly grid: Float32Array;
  buildings: Building[] = [];

  private openWorld = new THREE.Group();
  private interiorRoot = new THREE.Group();
  private interiorCache = new Map<string, THREE.Object3D>();
  private residentsRoot = new THREE.Group();
  private sun: THREE.DirectionalLight;
  private hemi: THREE.HemisphereLight;
  private indoor: THREE.Group;
  private waterUniforms: Record<string, THREE.IUniform>;
  private sky: THREE.Mesh;
  private residentTemplate?: { scene: THREE.Object3D; clip?: THREE.AnimationClip };
  private residents = new Map<string, Resident>();
  private clock = new THREE.Clock();
  private t = 0;

  current: SceneKey = 'open_world';
  target = new THREE.Vector3(SETTLE_X, SETTLE_Y + 2, SETTLE_Z);
  yaw = 0.6;
  pitch = OPEN_WORLD_PITCH;
  dist = OPEN_WORLD_DIST;
  minDist = 8;
  reducedMotion = false;
  followId: string | null = null;
  private keys = new Set<string>();
  onFrame?: () => void;

  constructor(private canvas: HTMLCanvasElement) {
    this.renderer = new THREE.WebGLRenderer({ canvas, antialias: true, powerPreference: 'high-performance' });
    this.renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
    this.renderer.outputColorSpace = THREE.SRGBColorSpace;
    this.renderer.toneMapping = THREE.ACESFilmicToneMapping;
    this.renderer.toneMappingExposure = 1.05;
    this.renderer.shadowMap.enabled = true;
    this.renderer.shadowMap.type = THREE.PCFSoftShadowMap;

    // --- open world: the ported Godot builders, same seed and order as WorldView._Ready
    this.grid = sampleGrid();
    this.openWorld.add(buildTerrain(this.grid));
    const water = buildWater();
    this.waterUniforms = water.uniforms;
    this.openWorld.add(water.mesh);
    const plans = buildPlans(new SimulationRng(SEED));
    const settlement = buildSettlement(plans);
    this.buildings = settlement.buildings;
    this.openWorld.add(settlement.root);
    this.openWorld.add(buildVegetation(plans));
    this.sky = this.buildSky();
    this.openWorld.add(this.sky);
    this.scene.add(this.openWorld, this.interiorRoot, this.residentsRoot);

    // Noon light. Sky3D owns the sun in Godot; this is a fixed stand-in, not its model.
    this.sun = new THREE.DirectionalLight(0xfff0d8, 2.2);
    this.sun.position.set(SETTLE_X + 60, SETTLE_Y + 110, SETTLE_Z + 45);
    this.sun.target.position.set(SETTLE_X, SETTLE_Y, SETTLE_Z);
    this.sun.castShadow = true;
    this.sun.shadow.mapSize.set(2048, 2048);
    const sc = this.sun.shadow.camera;
    sc.left = -70; sc.right = 70; sc.top = 70; sc.bottom = -70; sc.near = 10; sc.far = 300;
    this.sun.shadow.bias = -0.0005;
    this.sun.shadow.normalBias = 0.04;
    this.hemi = new THREE.HemisphereLight(0xd6e2ea, 0x8a8670, 1.55);
    this.openWorld.add(this.sun, this.sun.target, this.hemi);

    // WorldView.GetOrCreateIndoorEnvironment: warm ambient fill, dark background.
    this.indoor = new THREE.Group();
    this.indoor.add(new THREE.AmbientLight(new THREE.Color(0.85, 0.8, 0.7), 1.2));
    this.interiorRoot.add(this.indoor);
    this.interiorRoot.visible = false;

    this.applyEnvironment();
    this.updateCamera();
    this.bindInput();
    this.resize();
    window.addEventListener('resize', () => this.resize());
    this.renderer.setAnimationLoop(() => this.frame());
  }

  // ----------------------------------------------------------- environment
  private buildSky(): THREE.Mesh {
    const mat = new THREE.ShaderMaterial({
      side: THREE.BackSide,
      depthWrite: false,
      fog: false,
      uniforms: {
        top: { value: new THREE.Color().setHex(0x6f8aa3, THREE.SRGBColorSpace) },
        horizon: { value: new THREE.Color().setHex(0xc3d4dd, THREE.SRGBColorSpace) },
        ground: { value: FOG.clone() },
      },
      vertexShader: 'varying vec3 vDir; void main(){ vDir = normalize(position); gl_Position = projectionMatrix * modelViewMatrix * vec4(position,1.0); }',
      fragmentShader: `uniform vec3 top, horizon, ground; varying vec3 vDir;
        void main(){ float h = vDir.y; vec3 c = h > 0.0 ? mix(horizon, top, pow(clamp(h,0.0,1.0), 0.55)) : ground;
        gl_FragColor = vec4(c, 1.0);
        #include <tonemapping_fragment>
        #include <colorspace_fragment>
        }`,
    });
    const m = new THREE.Mesh(new THREE.SphereGeometry(1800, 32, 16), mat);
    m.name = 'Sky';
    m.renderOrder = -1;
    m.onBeforeRender = (_r, _s, cam) => m.position.copy(cam.position);
    return m;
  }

  private applyEnvironment() {
    if (this.current === 'open_world') {
      this.scene.background = FOG;
      this.scene.fog = new THREE.FogExp2(FOG, 0.0032);
    } else {
      this.scene.background = new THREE.Color(0.05, 0.05, 0.07);
      this.scene.fog = null;
    }
  }

  // ----------------------------------------------------------- scenes
  /** Scene id currently shown: 'open_world' or an interior id such as 'workplace_7'. */
  currentId = 'open_world';

  /** WorldView.ShowScene: the open world, or an interior level dressed in that building's scheme. */
  async showScene(sceneId: string): Promise<void> {
    const key = sceneKeyFor(sceneId);
    if (key === 'open_world') {
      this.current = key;
      this.currentId = 'open_world';
      this.openWorld.visible = true;
      this.interiorRoot.visible = false;
      this.minDist = 8;
      this.dist = OPEN_WORLD_DIST;
      this.pitch = OPEN_WORLD_PITCH;
      this.target.set(SETTLE_X, SETTLE_Y + 2, SETTLE_Z);
      this.camera.far = 2400;
      this.camera.updateProjectionMatrix();
      this.applyEnvironment();
      this.updateCamera();
      return;
    }
    const room = await this.interiorFor(key, sceneId);
    this.current = key;
    this.currentId = sceneId;
    for (const c of [...this.interiorRoot.children]) if (c !== this.indoor) this.interiorRoot.remove(c);
    this.interiorRoot.add(room);
    this.openWorld.visible = false;
    this.interiorRoot.visible = true;
    this.applyEnvironment();
    this.frameInterior(room);
  }

  private rawLevels = new Map<string, Promise<THREE.Group>>();
  private rawLevel(key: Exclude<SceneKey, 'open_world'>): Promise<THREE.Group> {
    let p = this.rawLevels.get(key);
    if (!p) {
      // FBXLoader is fetched only when an interior is first opened.
      p = import('three/examples/jsm/loaders/FBXLoader.js').then(({ FBXLoader }) => new FBXLoader().loadAsync(INTERIORS[key]));
      this.rawLevels.set(key, p);
      p.catch(() => this.rawLevels.delete(key));
    }
    return p;
  }

  private async interiorFor(key: Exclude<SceneKey, 'open_world'>, sceneId: string): Promise<THREE.Object3D> {
    const cached = this.interiorCache.get(sceneId);
    if (cached) return cached;
    const level = (await this.rawLevel(key)).clone(true);
    // StripInteriorClutter: sky sphere, UCX_ collision hulls and outdoor lights don't belong indoors.
    const drop: THREE.Object3D[] = [];
    level.traverse((o) => {
      if (o.name.includes('Sky') || (o as THREE.Light).isLight) drop.push(o);
      else if (o.name.startsWith('UCX_')) o.visible = false;
      const mesh = o as THREE.Mesh;
      if (mesh.isMesh) { mesh.castShadow = true; mesh.receiveShadow = true; }
    });
    drop.forEach((o) => o.parent?.remove(o));
    // Axis + unit conversion. The four levels declare UpAxis +Z, FrontAxis -Y, CoordAxis +X and
    // UnitScaleFactor 1 (centimetres) — Unreal's convention. Godot's ufbx importer converts that to
    // Y-up metres; three's FBXLoader leaves it as authored. (x, y, z)cm -> (x, z, -y)m is the same
    // conversion: a -90° turn about X and a 1/100 scale.
    level.rotation.set(-Math.PI / 2, 0, 0);
    level.scale.setScalar(0.01);
    level.updateMatrixWorld(true);
    const room = new THREE.Group();
    room.name = `Interior:${sceneId}`;
    room.add(level);
    applyInteriorStyle(level, room, sceneId);
    this.addIndoorLights(room);
    this.interiorCache.set(sceneId, room);
    return room;
  }

  /** WorldView.SetupInteriorLighting: a ceiling grid of warm lights sized to the room. */
  private addIndoorLights(room: THREE.Object3D) {
    const box = frameBounds(room);
    if (box.isEmpty()) return;
    const size = box.getSize(new THREE.Vector3());
    const span = Math.max(size.x, size.z);
    const n = clamp(Math.trunc(span / 10), 1, 3);
    const range = clamp(span * 0.55, 8, 28);
    for (let ix = 0; ix < n; ix++)
      for (let iz = 0; iz < n; iz++) {
        const l = new THREE.PointLight(new THREE.Color(1, 0.92, 0.78), 45, range * 1.6, 1.4);
        l.position.set(
          box.min.x + size.x * (n === 1 ? 0.5 : ix / (n - 1)),
          box.max.y - 0.3,
          box.min.z + size.z * (n === 1 ? 0.5 : iz / (n - 1)),
        );
        room.add(l);
      }
  }

  private frameInterior(root: THREE.Object3D) {
    const box = frameBounds(root);
    if (box.isEmpty()) {
      this.target.set(0, 1.1, 0);
      this.dist = 8;
      this.pitch = 0.5;
    } else {
      box.getCenter(this.target);
      const s = box.getSize(new THREE.Vector3());
      this.dist = clamp(Math.max(s.x, s.z) * 1.05, 10, 70);
      this.pitch = INTERIOR_PITCH;
    }
    this.minDist = 3;
    this.camera.far = 600;
    this.camera.updateProjectionMatrix();
    this.updateCamera();
  }

  // ----------------------------------------------------------- residents
  async loadResidentModel(url: string): Promise<void> {
    const gltf = await new GLTFLoader().loadAsync(url);
    gltf.scene.traverse((o) => {
      const m = o as THREE.Mesh;
      if (m.isMesh) { m.castShadow = true; m.frustumCulled = false; }
    });
    this.residentTemplate = { scene: gltf.scene, clip: gltf.animations.find((a) => a.name === 'ResidentRig') ?? gltf.animations[0] };
  }

  private makeResident(a: Agent): Resident {
    const root = new THREE.Group();
    root.name = `Resident:${a.id}`;
    let mixer: THREE.AnimationMixer | undefined, walk: THREE.AnimationAction | undefined;
    if (this.residentTemplate) {
      const model = SkeletonUtils.clone(this.residentTemplate.scene);
      // One tint per role, so Avatars and Aides differ in shape-independent ways too; labels carry the meaning.
      const tint = a.role === 'aide' ? 0x9cc7e4 : a.role === 'advocate' ? 0xe8c48c : 0xe8e2d4;
      model.traverse((o) => {
        const m = o as THREE.Mesh;
        if (m.isMesh) m.material = new THREE.MeshStandardMaterial({ color: tint, roughness: 0.8 });
      });
      root.add(model);
      if (this.residentTemplate.clip) {
        mixer = new THREE.AnimationMixer(model);
        walk = mixer.clipAction(this.residentTemplate.clip);
        walk.play();
        walk.paused = true;
        walk.time = 0;
      }
    } else {
      const body = new THREE.Mesh(new THREE.CapsuleGeometry(0.28, 1.2, 4, 10), new THREE.MeshStandardMaterial({ color: 0xe8e2d4 }));
      body.position.y = 0.9;
      root.add(body);
    }
    const ring = new THREE.Mesh(
      new THREE.RingGeometry(0.55, 0.72, 40).rotateX(-Math.PI / 2),
      new THREE.MeshBasicMaterial({ color: 0xffffff, transparent: true, opacity: 0.9, depthWrite: false }),
    );
    ring.position.y = 0.06;
    ring.visible = false;
    root.add(ring);
    this.residentsRoot.add(root);
    const r: Resident = { id: a.id, root, mixer, walk, ring };
    this.residents.set(a.id, r);
    return r;
  }

  /**
   * Place agents from the feed. `pos` is already interpolated between two feed frames by the
   * caller; agents not in the shown scene are hidden, never moved.
   */
  syncAgents(agents: { agent: Agent; pos: THREE.Vector3; vel: THREE.Vector3; visible: boolean }[], selected: string | null) {
    const seen = new Set<string>();
    for (const { agent, pos, vel, visible } of agents) {
      seen.add(agent.id);
      const r = this.residents.get(agent.id) ?? this.makeResident(agent);
      r.root.visible = visible;
      r.root.position.copy(pos);
      r.ring.visible = agent.id === selected;
      const speed = Math.hypot(vel.x, vel.z);
      const walking = speed > 0.05; // Resident.IsWalking
      if (walking) r.root.rotation.y = Math.atan2(vel.x, vel.z);
      if (r.walk) {
        // Walk cycles show real state, so they play under reduced motion too (Joshua, 2026-10-28).
        r.walk.paused = !walking;
        if (walking) r.walk.timeScale = clamp(speed / 1.4, 0.5, 2);
        else r.walk.time = 0;
      }
    }
    for (const [id, r] of this.residents) if (!seen.has(id)) r.root.visible = false;
  }

  residentAnchor(id: string): THREE.Vector3 | null {
    const r = this.residents.get(id);
    return r && r.root.visible ? r.root.position.clone().add(new THREE.Vector3(0, 2.15, 0)) : null;
  }

  // ----------------------------------------------------------- camera
  updateCamera() {
    this.camera.position.set(
      this.target.x + Math.cos(this.pitch) * Math.sin(this.yaw) * this.dist,
      this.target.y + Math.sin(this.pitch) * this.dist,
      this.target.z + Math.cos(this.pitch) * Math.cos(this.yaw) * this.dist,
    );
    this.camera.lookAt(this.target);
  }

  focusOn(p: THREE.Vector3, dist?: number) {
    this.target.copy(p).add(new THREE.Vector3(0, this.current === 'open_world' ? 2 : 1.1, 0));
    if (dist) this.dist = dist;
    this.updateCamera();
  }

  resetCamera() {
    void this.showScene(this.currentId);
  }

  private bindInput() {
    const el = this.canvas;
    const pointers = new Map<number, { x: number; y: number }>();
    let pinch = 0;
    let downAt: { x: number; y: number } | null = null;
    el.addEventListener('pointerdown', (e) => {
      el.setPointerCapture(e.pointerId);
      pointers.set(e.pointerId, { x: e.clientX, y: e.clientY });
      downAt = { x: e.clientX, y: e.clientY };
      if (pointers.size === 2) {
        const [a, b] = [...pointers.values()];
        pinch = Math.hypot(a.x - b.x, a.y - b.y);
      }
    });
    el.addEventListener('pointermove', (e) => {
      const p = pointers.get(e.pointerId);
      if (!p) return;
      const dx = e.clientX - p.x, dy = e.clientY - p.y;
      p.x = e.clientX; p.y = e.clientY;
      if (pointers.size === 1) {
        // WorldView._Input: orbit by drag.
        this.yaw -= dx * 0.005;
        this.pitch = clamp(this.pitch + dy * 0.004, 0.05, Math.PI * 0.487);
        this.updateCamera();
      } else if (pointers.size === 2) {
        const [a, b] = [...pointers.values()];
        const d = Math.hypot(a.x - b.x, a.y - b.y);
        if (pinch > 0) this.zoom((pinch - d) * 0.15);
        pinch = d;
      }
    });
    const up = (e: PointerEvent) => {
      pointers.delete(e.pointerId);
      if (downAt && pointers.size === 0 && Math.hypot(e.clientX - downAt.x, e.clientY - downAt.y) < 6) this.onClick?.(e.clientX, e.clientY);
      if (pointers.size < 2) pinch = 0;
      downAt = null;
    };
    el.addEventListener('pointerup', up);
    el.addEventListener('pointercancel', up);
    el.addEventListener('wheel', (e) => { e.preventDefault(); this.zoom(Math.sign(e.deltaY) * 6); }, { passive: false });
    window.addEventListener('keydown', (e) => {
      if ((e.target as HTMLElement)?.closest?.('input,select,textarea,button')) return;
      const k = e.key.toLowerCase();
      if (['w', 'a', 's', 'd', 'arrowup', 'arrowdown', 'arrowleft', 'arrowright'].includes(k)) { this.keys.add(k); e.preventDefault(); }
    });
    window.addEventListener('keyup', (e) => this.keys.delete(e.key.toLowerCase()));
    window.addEventListener('blur', () => this.keys.clear());
  }

  onClick?: (x: number, y: number) => void;

  zoom(delta: number) {
    this.dist = clamp(this.dist + delta, this.minDist, MAX_DIST);
    this.updateCamera();
  }

  /** Building under a screen point, for the doorway affordance. */
  pickBuilding(x: number, y: number): Building | null {
    if (this.current !== 'open_world') return null;
    const r = this.canvas.getBoundingClientRect();
    const ray = new THREE.Raycaster();
    ray.setFromCamera(new THREE.Vector2(((x - r.left) / r.width) * 2 - 1, -((y - r.top) / r.height) * 2 + 1), this.camera);
    const hits = ray.intersectObjects(this.buildings.map((b) => b.group), true);
    for (const h of hits) {
      let o: THREE.Object3D | null = h.object;
      while (o && o.userData.buildingIndex === undefined) o = o.parent;
      if (o) return this.buildings[o.userData.buildingIndex as number];
    }
    return null;
  }

  project(p: THREE.Vector3): { x: number; y: number; visible: boolean } {
    const v = p.clone().project(this.camera);
    const r = this.canvas.getBoundingClientRect();
    const behind = v.z > 1;
    return { x: r.left + ((v.x + 1) / 2) * r.width, y: r.top + ((1 - v.y) / 2) * r.height, visible: !behind && Math.abs(v.x) < 1.1 && Math.abs(v.y) < 1.1 };
  }

  resize() {
    const w = this.canvas.clientWidth || window.innerWidth, h = this.canvas.clientHeight || window.innerHeight;
    this.renderer.setSize(w, h, false);
    this.camera.aspect = w / Math.max(1, h);
    this.camera.updateProjectionMatrix();
  }

  private frame() {
    const dt = Math.min(this.clock.getDelta(), 0.1);
    this.t += dt;
    // WASD / arrows pan, as WorldView._Process.
    let px = 0, py = 0;
    if (this.keys.has('a') || this.keys.has('arrowleft')) px -= 1;
    if (this.keys.has('d') || this.keys.has('arrowright')) px += 1;
    if (this.keys.has('w') || this.keys.has('arrowup')) py -= 1;
    if (this.keys.has('s') || this.keys.has('arrowdown')) py += 1;
    if (px || py) {
      const n = Math.hypot(px, py);
      const fx = -Math.sin(this.yaw), fz = -Math.cos(this.yaw), rx = Math.cos(this.yaw), rz = -Math.sin(this.yaw);
      this.target.x += ((rx * px) / n + (fx * -py) / n) * PAN_SPEED * dt;
      this.target.z += ((rz * px) / n + (fz * -py) / n) * PAN_SPEED * dt;
      this.followId = null;
      this.updateCamera();
    }
    // Reduced motion gates the decorative motion Joshua listed (2026-10-28): wind sway. Water keeps
    // moving, as in Godot.
    windUniforms.u_time.value = this.t;
    windUniforms.u_wind.value = this.reducedMotion ? 0 : 1;
    this.waterUniforms.u_time.value = this.t;
    for (const r of this.residents.values()) r.mixer?.update(dt);
    this.onFrame?.();
    this.renderer.render(this.scene, this.camera);
  }
}
