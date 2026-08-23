import { Engine } from '@babylonjs/core/Engines/engine';
import { Scene } from '@babylonjs/core/scene';
import { ArcRotateCamera } from '@babylonjs/core/Cameras/arcRotateCamera';
import { HemisphericLight } from '@babylonjs/core/Lights/hemisphericLight';
import { DirectionalLight } from '@babylonjs/core/Lights/directionalLight';
import { Vector3 } from '@babylonjs/core/Maths/math.vector';
import { Color3, Color4 } from '@babylonjs/core/Maths/math.color';
import { MeshBuilder } from '@babylonjs/core/Meshes/meshBuilder';
import { StandardMaterial } from '@babylonjs/core/Materials/standardMaterial';
import { TransformNode } from '@babylonjs/core/Meshes/transformNode';
import { DynamicTexture } from '@babylonjs/core/Materials/Textures/dynamicTexture';

// Types
export interface SimState {
  id: string; name: string; hue: number; x: number; y: number;
  focus: number; stress: number; energy: number; state: string;
}
export interface RoomState {
  id: string; name: string; x: number; y: number; w: number; h: number; props: string[];
}
export interface PairState {
  id: string; tickCount: number; timeOfDay: number;
  avatars: SimState[]; rooms: RoomState[];
  recentEvents: { tick: number; type: string; message: string }[];
}

function hsl(h: number, s: number, l: number): Color3 {
  const c = (1 - Math.abs(2 * l - 1)) * s;
  const x = c * (1 - Math.abs((h / 60) % 2 - 1));
  const m = l - c / 2;
  let r = 0, g = 0, b = 0;
  if (h < 60) { r = c; g = x; } else if (h < 120) { r = x; g = c; }
  else if (h < 180) { g = c; b = x; } else if (h < 240) { g = x; b = c; }
  else if (h < 300) { r = x; b = c; } else { r = c; b = x; }
  return new Color3(r + m, g + m, b + m);
}

function makeLabelTexture(text: string): DynamicTexture {
  const w = 256, h = 64;
  const tex = new DynamicTexture(`tex_${text}`, { width: w, height: h }, scene, false);
  const ctx = tex.getContext() as unknown as CanvasRenderingContext2D;
  ctx.fillStyle = 'rgba(0,0,0,0.75)';
  ctx.beginPath(); ctx.roundRect(0, 0, w, h, 8); ctx.fill();
  ctx.fillStyle = '#fff'; ctx.font = 'bold 24px system-ui'; ctx.textAlign = 'center';
  ctx.fillText(text, w / 2, 40);
  tex.update();
  return tex;
}

// Renderer
const canvas = document.getElementById('renderCanvas') as HTMLCanvasElement;
const engine = new Engine(canvas, true);
engine.setHardwareScalingLevel(1 / Math.min(window.devicePixelRatio, 2));

const scene = new Scene(engine);
scene.clearColor = new Color4(0.04, 0.04, 0.1, 1);

const camera = new ArcRotateCamera('cam', Math.PI / 3, Math.PI / 3, 25, Vector3.Zero(), scene);
camera.attachControl(canvas, true);
camera.lowerRadiusLimit = 5;
camera.upperRadiusLimit = 50;

const hemi = new HemisphericLight('hemi', new Vector3(0, 1, 0), scene);
hemi.intensity = 0.6;

const sun = new DirectionalLight('sun', new Vector3(-1, -2, -1), scene);
sun.intensity = 1.2;
sun.position = new Vector3(20, 30, 20);

// Materials
const groundMat = new StandardMaterial('groundMat', scene);
groundMat.diffuseColor = new Color3(0.1, 0.12, 0.18);

const floorMat = new StandardMaterial('floorMat', scene);
floorMat.diffuseColor = new Color3(0.15, 0.15, 0.25);

const wallMat = new StandardMaterial('wallMat', scene);
wallMat.diffuseColor = new Color3(0.3, 0.25, 0.5);
wallMat.alpha = 0.3;

// Ground
const ground = MeshBuilder.CreateGround('ground', { width: 60, height: 60 }, scene);
ground.material = groundMat;

// State
let worldState: PairState | null = null;
const simMeshes = new Map<string, TransformNode>();
let ws: WebSocket | null = null;

function buildScene(state: PairState) {
  for (const [, m] of simMeshes) m.dispose();
  simMeshes.clear();

  for (const room of state.rooms) {
    const floor = MeshBuilder.CreateBox(`floor_${room.id}`, { width: room.w, height: 0.1, depth: room.h }, scene);
    floor.position.set(room.x + room.w / 2, 0.05, room.y + room.h / 2);
    floor.material = floorMat;

    const wallH = 3.2, wallT = 0.2;
    [
      { w: room.w + wallT, d: wallT, x: room.x + room.w / 2, z: room.y - wallT / 2 },
      { w: room.w + wallT, d: wallT, x: room.x + room.w / 2, z: room.y + room.h + wallT / 2 },
      { w: wallT, d: room.h + wallT, x: room.x - wallT / 2, z: room.y + room.h / 2 },
      { w: wallT, d: room.h + wallT, x: room.x + room.w + wallT / 2, z: room.y + room.h / 2 },
    ].forEach(w => {
      const wall = MeshBuilder.CreateBox(`wall_${room.id}_${w.x}_${w.z}`, { width: w.w, height: wallH, depth: w.d }, scene);
      wall.position.set(w.x, wallH / 2, w.z);
      wall.material = wallMat;
    });

    const door = MeshBuilder.CreateBox(`door_${room.id}`, { width: 0.8, height: 2.2, depth: 0.25 }, scene);
    door.position.set(room.x + room.w / 2, 1.1, room.y - wallT / 2);
    const dm = new StandardMaterial(`dm_${room.id}`, scene);
    dm.diffuseColor = new Color3(0.3, 0.2, 0.1);
    door.material = dm;

    const labelTex = makeLabelTexture(room.name);
    const labelPlane = MeshBuilder.CreatePlane(`label_${room.id}`, { width: 3, height: 0.75 }, scene);
    labelPlane.position.set(room.x + room.w / 2, 4.5, room.y + room.h / 2);
    const lm = new StandardMaterial(`lm_${room.id}`, scene);
    lm.diffuseTexture = labelTex;
    lm.emissiveColor = new Color3(1, 1, 1);
    lm.backFaceCulling = false;
    labelPlane.material = lm;
  }

  for (const av of state.avatars) {
    const g = new TransformNode(`sim_${av.id}`, scene);
    g.position.set(av.x, 0, av.y);

    const body = MeshBuilder.CreateCapsule(`body_${av.id}`, { radius: 0.15, height: 0.6 }, scene);
    body.position.y = 0.55;
    const bm = new StandardMaterial(`bm_${av.id}`, scene);
    bm.diffuseColor = hsl(av.hue, 0.6, 0.5);
    body.material = bm;
    body.parent = g;

    const head = MeshBuilder.CreateSphere(`head_${av.id}`, { diameter: 0.25 }, scene);
    head.position.y = 0.95;
    const hm = new StandardMaterial(`hm_${av.id}`, scene);
    hm.diffuseColor = new Color3(1.0, 0.85, 0.7);
    head.material = hm;
    head.parent = g;

    const labelTex = makeLabelTexture(av.name);
    const lp = MeshBuilder.CreatePlane(`plabel_${av.id}`, { width: 1, height: 0.25 }, scene);
    lp.position.y = 1.45;
    const lm = new StandardMaterial(`lm_${av.id}`, scene);
    lm.diffuseTexture = labelTex;
    lm.emissiveColor = new Color3(1, 1, 1);
    lm.backFaceCulling = false;
    lp.material = lm;
    lp.parent = g;

    simMeshes.set(av.id, g);
  }
}

function animate() {
  const now = Date.now();
  if (worldState) {
    for (const av of worldState.avatars) {
      const m = simMeshes.get(av.id);
      if (m) m.position.y = Math.sin(now * 0.003 + av.hue) * 0.02;
    }
  }
  scene.render();
}

engine.runRenderLoop(animate);
window.addEventListener('resize', () => engine.resize());

function connect() {
  const pairId = window.location.hostname.split('.')[0];
  const proto = location.protocol === 'https:' ? 'wss:' : 'ws:';
  ws = new WebSocket(`${proto}//${location.host}`);

  ws.onopen = () => console.log('WS connected');
  ws.onmessage = e => {
    const d = JSON.parse(e.data);
    if (d.type === 'init') { worldState = d.state; buildScene(worldState!); updateHUD(); }
    else if (d.type === 'tick') { worldState = { ...worldState!, ...d }; updatePositions(); updateHUD(); }
  };
  ws.onclose = () => setTimeout(connect, 3000);
}

function updatePositions() {
  if (!worldState) return;
  for (const av of worldState.avatars) {
    const m = simMeshes.get(av.id);
    if (m) { m.position.x += (av.x - m.position.x) * 0.05; m.position.z += (av.y - m.position.z) * 0.05; }
  }
}

function updateHUD() {
  const el = document.getElementById('pair-info');
  if (el && worldState) {
    el.innerHTML = `<div>Tick: ${worldState.tickCount}</div><div>Sims: ${worldState.avatars.length}</div><div>Rooms: ${worldState.rooms.length}</div>`;
  }
}

connect();
export { scene, engine, camera, buildScene, worldState };
