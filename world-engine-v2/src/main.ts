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

const camera = new ArcRotateCamera('camera', Math.PI / 3, Math.PI / 3, 25, Vector3.Zero(), scene);
camera.attachControl(canvas, true);
camera.lowerRadiusLimit = 5;
camera.upperRadiusLimit = 50;
camera.wheelPrecision = 20;

// Lighting
const hemiLight = new HemisphericLight('hemi', new Vector3(0, 1, 0), scene);
hemiLight.intensity = 0.5;
hemiLight.diffuse = new Color3(0.8, 0.8, 1.0);
hemiLight.groundColor = new Color3(0.2, 0.2, 0.3);

const sunLight = new DirectionalLight('sun', new Vector3(-1, -2, -1), scene);
sunLight.intensity = 1.2;
sunLight.position = new Vector3(20, 30, 20);
sunLight.diffuse = new Color3(1.0, 0.95, 0.8);

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
ground.receiveShadows = true;

// State
let worldState: PairState | null = null;
const simMeshes = new Map<string, TransformNode>();
let ws: WebSocket | null = null;

function buildScene(state: PairState) {
  for (const [, mesh] of simMeshes) mesh.dispose();
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
    const doorMat = new StandardMaterial(`doorMat_${room.id}`, scene);
    doorMat.diffuseColor = new Color3(0.3, 0.2, 0.1);
    door.material = doorMat;

    const labelTex = makeLabelTexture(room.name);
    const labelPlane = MeshBuilder.CreatePlane(`label_${room.id}`, { width: 3, height: 0.75 }, scene);
    labelPlane.position.set(room.x + room.w / 2, 4.5, room.y + room.h / 2);
    const labelMat = new StandardMaterial(`labelMat_${room.id}`, scene);
    labelMat.diffuseTexture = labelTex;
    labelMat.emissiveColor = new Color3(1, 1, 1);
    labelMat.backFaceCulling = false;
    labelPlane.material = labelMat;
  }

  for (const av of state.avatars) {
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

    const labelTex = makeLabelTexture(av.name);
    const labelPlane = MeshBuilder.CreatePlane(`plabel_${av.id}`, { width: 1, height: 0.25 }, scene);
    labelPlane.position.y = 1.45;
    const labelMat = new StandardMaterial(`plabelMat_${av.id}`, scene);
    labelMat.diffuseTexture = labelTex;
    labelMat.emissiveColor = new Color3(1, 1, 1);
    labelMat.backFaceCulling = false;
    labelPlane.material = labelMat;
    labelPlane.parent = group;

    simMeshes.set(av.id, group);
  }
}

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

// Backend connection
const BACKEND_URL = 'cloudflare-pairs.joshdorsey.workers.dev';

function connectWebSocket() {
  const protocol = location.protocol === 'https:' ? 'wss:' : 'ws:';
  ws = new WebSocket(`${protocol}//${BACKEND_URL}`);

  ws.onopen = () => console.log('WS connected to backend');

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
    console.log('WS disconnected, retrying...');
    setTimeout(connectWebSocket, 3000);
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
  const tickEl = document.getElementById('tick-count');
  const timeEl = document.getElementById('time-display');
  const focusEl = document.getElementById('focus-bar');
  const stressEl = document.getElementById('stress-bar');
  const energyEl = document.getElementById('energy-bar');

  if (tickEl) tickEl.textContent = String(worldState.tickCount);
  if (timeEl) timeEl.textContent = formatTime(worldState.timeOfDay);

  const av = worldState.avatars[0];
  if (av) {
    if (focusEl) focusEl.style.width = `${Math.round(av.focus * 100)}%`;
    if (stressEl) stressEl.style.width = `${Math.round(av.stress * 100)}%`;
    if (energyEl) energyEl.style.width = `${Math.round(av.energy * 100)}%`;
  }
}

function formatTime(mins: number): string {
  const h = Math.floor(mins / 60) % 24;
  const m = Math.floor(mins % 60);
  const period = h < 12 ? 'AM' : 'PM';
  const h12 = h % 12 === 0 ? 12 : h % 12;
  return `${h12}:${String(m).padStart(2, '0')} ${period}`;
}

// Show demo scene immediately so user sees something before WS connects
function showDemoScene() {
  worldState = {
    id: 'demo',
    tickCount: 0,
    timeOfDay: 600,
    avatars: [
      { id: 'sim-demo', name: 'StayAlert', hue: 200, x: 4, y: 4, focus: 0.7, stress: 0.3, energy: 0.8, state: 'idle' },
    ],
    rooms: [
      { id: 'office', name: 'Office', x: 0, y: 0, w: 8, h: 8, props: ['desk', 'monitor', 'chair'] },
      { id: 'meeting', name: 'Meeting Room', x: 10, y: 0, w: 8, h: 8, props: ['longtable', 'chair', 'screen'] },
      { id: 'home', name: 'Home', x: 0, y: 10, w: 8, h: 8, props: ['bed', 'night stand', 'dresser'] },
      { id: 'phone', name: 'Phone Booth', x: 10, y: 10, w: 4, h: 4, props: ['phone'] },
      { id: 'lounge', name: 'Lounge', x: 16, y: 0, w: 8, h: 8, props: ['sofa', 'coffee table', 'music stereo'] },
    ],
    recentEvents: [],
  };
  buildScene(worldState);
}

showDemoScene();
connectWebSocket();

export { scene, engine, camera, buildScene, worldState };
