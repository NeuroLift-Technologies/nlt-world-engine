import { Engine } from '@babylonjs/core/Engines/engine';
import { Scene } from '@babylonjs/core/scene';
import { ArcRotateCamera } from '@babylonjs/core/Cameras/arcRotateCamera';
import { HemisphericLight } from '@babylonjs/core/Lights/hemisphericLight';
import { DirectionalLight } from '@babylonjs/core/Lights/directionalLight';
import { Vector3 } from '@babylonjs/core/Maths/math.vector';
import { Color3 } from '@babylonjs/core/Maths/math.color';
import { MeshBuilder } from '@babylonjs/core/Meshes/meshBuilder';
import { StandardMaterial } from '@babylonjs/core/Materials/standardMaterial';
import { TransformNode } from '@babylonjs/core/Meshes/transformNode';
import { DynamicTexture } from '@babylonjs/core/Materials/Textures/dynamicTexture';
import { Sprite } from '@babylonjs/core/Sprites/sprite';
import { SpriteManager } from '@babylonjs/core/Sprites/spriteManager';

// ─── Types ────────────────────────────────────────────────────────
export interface SimState {
  id: string;
  name: string;
  hue: number;
  x: number;
  y: number;
  focus: number;
  stress: number;
  energy: number;
  state: string;
}

export interface PairState {
  id: string;
  tickCount: number;
  timeOfDay: number;
  avatars: SimState[];
  rooms: RoomState[];
  recentEvents: { tick: number; type: string; message: string }[];
}

export interface RoomState {
  id: string;
  name: string;
  x: number;
  y: number;
  w: number;
  h: number;
  props: string[];
}

// ─── Helpers ──────────────────────────────────────────────────────
function hslToColor3(h: number, s: number, l: number): Color3 {
  const c = (1 - Math.abs(2 * l - 1)) * s;
  const x = c * (1 - Math.abs((h / 60) % 2 - 1));
  const m = l - c / 2;
  let r = 0, g = 0, b = 0;
  if (h < 60) { r = c; g = x; }
  else if (h < 120) { r = x; g = c; }
  else if (h < 180) { g = c; b = x; }
  else if (h < 240) { g = x; b = c; }
  else if (h < 300) { r = x; b = c; }
  else { r = c; b = x; }
  return new Color3(r + m, g + m, b + m);
}

// ─── Renderer ─────────────────────────────────────────────────────
const canvas = document.getElementById('renderCanvas') as HTMLCanvasElement;
const engine = new Engine(canvas, true);
engine.setHardwareScalingLevel(1 / Math.min(window.devicePixelRatio, 2));

const scene = new Scene(engine);
scene.clearColor = new Color3(0.04, 0.04, 0.1).toColor4(1);

const camera = new ArcRotateCamera('camera', Math.PI / 3, Math.PI / 3, 25, Vector3.Zero(), scene);
camera.attachControl(canvas, true);
camera.lowerRadiusLimit = 5;
camera.upperRadiusLimit = 50;
camera.wheelPrecision = 20;

// ─── Lighting ─────────────────────────────────────────────────────
const hemiLight = new HemisphericLight('hemi', new Vector3(0, 1, 0), scene);
hemiLight.intensity = 0.5;
hemiLight.diffuse = new Color3(0.8, 0.8, 1.0);
hemiLight.groundColor = new Color3(0.2, 0.2, 0.3);

const sunLight = new DirectionalLight('sun', new Vector3(-1, -2, -1), scene);
sunLight.intensity = 1.2;
sunLight.position = new Vector3(20, 30, 20);
sunLight.diffuse = new Color3(1.0, 0.95, 0.8);

// ─── Materials ────────────────────────────────────────────────────
const groundMat = new StandardMaterial('groundMat', scene);
groundMat.diffuseColor = new Color3(0.1, 0.12, 0.18);

const floorMat = new StandardMaterial('floorMat', scene);
floorMat.diffuseColor = new Color3(0.15, 0.15, 0.25);

const wallMat = new StandardMaterial('wallMat', scene);
wallMat.diffuseColor = new Color3(0.3, 0.25, 0.5);
wallMat.alpha = 0.3;

// ─── Ground ───────────────────────────────────────────────────────
const ground = MeshBuilder.CreateGround('ground', { width: 60, height: 60 }, scene);
ground.material = groundMat;
ground.receiveShadows = true;

// ─── Scene State ──────────────────────────────────────────────────
let worldState: PairState | null = null;
let simMeshes = new Map<string, TransformNode>();
let labelSprites = new Map<string, Sprite>();
let labelManagers = new Map<string, SpriteManager>();
let ws: WebSocket | null = null;

// ─── Build Scene ──────────────────────────────────────────────────
function buildScene(state: PairState) {
  for (const [, mesh] of simMeshes) mesh.dispose();
  for (const [, sprite] of labelSprites) sprite.dispose();
  for (const [, mgr] of labelManagers) mgr.dispose();
  simMeshes.clear();
  labelSprites.clear();
  labelManagers.clear();

  for (const room of state.rooms) buildRoom(room);
  for (const av of state.avatars) buildSim(av);
}

function buildRoom(room: RoomState) {
  const floor = MeshBuilder.CreateBox(`floor_${room.id}`, { width: room.w, height: 0.1, depth: room.h }, scene);
  floor.position.set(room.x + room.w / 2, 0.05, room.y + room.h / 2);
  floor.material = floorMat;

  const wallH = 3.2, wallT = 0.2;
  const walls = [
    { w: room.w + wallT, d: wallT, x: room.x + room.w / 2, z: room.y - wallT / 2 },
    { w: room.w + wallT, d: wallT, x: room.x + room.w / 2, z: room.y + room.h + wallT / 2 },
    { w: wallT, d: room.h + wallT, x: room.x - wallT / 2, z: room.y + room.h / 2 },
    { w: wallT, d: room.h + wallT, x: room.x + room.w + wallT / 2, z: room.y + room.h / 2 },
  ];
  for (const w of walls) {
    const wall = MeshBuilder.CreateBox(`wall_${room.id}_${w.x}_${w.z}`, { width: w.w, height: wallH, depth: w.d }, scene);
    wall.position.set(w.x, wallH / 2, w.z);
    wall.material = wallMat;
  }

  const door = MeshBuilder.CreateBox(`door_${room.id}`, { width: 0.8, height: 2.2, depth: 0.25 }, scene);
  door.position.set(room.x + room.w / 2, 1.1, room.y - wallT / 2);
  const doorMat = new StandardMaterial(`doorMat_${room.id}`, scene);
  doorMat.diffuseColor = new Color3(0.3, 0.2, 0.1);
  door.material = doorMat;

  // Per-room label. A Sprite cannot hold its own texture (a SpriteManager
  // shares one spritesheet across all of its Sprites), so give this room its
  // own manager + DynamicTexture. cellSize matches the 256x64 texture so a
  // single cell covers the whole label; Sprite.size is a scalar (width), and
  // the 4:1 texture aspect auto-scales the height to 0.75 — matching the old
  // Vector3(3, 0.75, 1) intent.
  const tex = new DynamicTexture(`tex_${room.id}`, { width: 256, height: 64 }, scene, false);
  const ctx = tex.getContext() as unknown as CanvasRenderingContext2D;
  ctx.fillStyle = 'rgba(0,0,0,0.7)';
  ctx.beginPath(); ctx.roundRect(0, 0, 256, 64, 8); ctx.fill();
  ctx.fillStyle = '#fff'; ctx.font = 'bold 24px system-ui'; ctx.textAlign = 'center';
  ctx.fillText(room.name, 128, 40);
  tex.update();

  const roomLabelManager = new SpriteManager(`labelMgr_${room.id}`, '', 1, { width: 256, height: 64 }, scene);
  roomLabelManager.texture = tex;
  const label = new Sprite(`label_${room.id}`, roomLabelManager);
  label.size = 3;
  label.position = new Vector3(room.x + room.w / 2, 4.5, room.y + room.h / 2);
  labelSprites.set(room.id, label);
  labelManagers.set(room.id, roomLabelManager);
}

function buildSim(av: SimState) {
  const group = new TransformNode(`sim_${av.id}`, scene);
  group.position.set(av.x, 0, av.y);

  const body = MeshBuilder.CreateCapsule(`body_${av.id}`, { radius: 0.15, height: 0.6 }, scene);
  body.position.y = 0.55;
  const bodyMat = new StandardMaterial(`bodyMat_${av.id}`, scene);
  bodyMat.diffuseColor = hslToColor3(av.hue, 0.6, 0.5);
  body.material = bodyMat;
  body.parent = group;

  const head = MeshBuilder.CreateSphere(`head_${av.id}`, { diameter: 0.25 }, scene);
  head.position.y = 0.95;
  const headMat = new StandardMaterial(`headMat_${av.id}`, scene);
  headMat.diffuseColor = new Color3(1.0, 0.85, 0.7);
  head.material = headMat;
  head.parent = group;

  simMeshes.set(av.id, group);
}

// ─── Animation Loop ───────────────────────────────────────────────
function animate() {
  const now = Date.now();
  if (worldState) {
    for (const av of worldState.avatars) {
      const mesh = simMeshes.get(av.id);
      if (mesh) mesh.position.y = Math.sin(now * 0.003 + av.hue) * 0.02;
    }
  }
  scene.render();
}

engine.runRenderLoop(animate);
window.addEventListener('resize', () => engine.resize());

// ─── WebSocket ────────────────────────────────────────────────────
function connectWebSocket(pairId: string) {
  const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
  ws = new WebSocket(`${protocol}//${window.location.host}/ws`);

  ws.onopen = () => console.log('WebSocket connected');

  ws.onmessage = (event: MessageEvent) => {
    const data = JSON.parse(event.data);
    if (data.type === 'init') {
      worldState = data.state;
      buildScene(worldState!);
      updateHUD();
    } else if (data.type === 'tick') {
      worldState = { ...worldState!, ...data };
      updateSimPositions();
      updateHUD();
    }
  };

  ws.onclose = () => {
    console.log('WebSocket disconnected, retrying...');
    setTimeout(() => connectWebSocket(pairId), 3000);
  };
}

function updateSimPositions() {
  if (!worldState) return;
  for (const av of worldState.avatars) {
    const mesh = simMeshes.get(av.id);
    if (mesh) {
      mesh.position.x += (av.x - mesh.position.x) * 0.05;
      mesh.position.z += (av.y - mesh.position.z) * 0.05;
    }
  }
}

function updateHUD() {
  if (!worldState) return;
  const hud = document.getElementById('pair-info');
  if (hud) {
    // Build via textContent/DOM (not innerHTML) to avoid a CodeQL-flagged
    // XSS sink: worldState arrives over WebSocket as JSON.parse(event.data),
    // i.e. untrusted input.
    hud.textContent = '';
    for (const [label, value] of [
      ['Tick', String(worldState.tickCount)],
      ['Sims', String(worldState.avatars.length)],
      ['Rooms', String(worldState.rooms.length)],
    ]) {
      const row = document.createElement('div');
      row.textContent = `${label}: ${value}`;
      hud.appendChild(row);
    }
  }
}

const pairId = window.location.hostname.split('.')[0];
connectWebSocket(pairId);

export { scene, engine, camera, buildScene, worldState };
