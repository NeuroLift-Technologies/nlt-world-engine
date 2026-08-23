// Babylon.js scene builder — rooms, props, characters.
//
// Ported from world-engine/world-view.jsx (CSS/SVG iso renderer).
// Now uses Babylon.js meshes with StandardMaterial for guaranteed visibility.

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
import { Mesh } from '@babylonjs/core/Meshes/mesh';

import { ROOMS, NPCS, PROP_COLORS, PROP_HEIGHTS } from './data';
import type { AvatarState } from './simulation';

// ─── Color helpers ────────────────────────────────────────────────
function hexToColor3(hex: string): Color3 {
  const n = parseInt(hex.replace('#', ''), 16);
  const r = ((n >> 16) & 0xff) / 255;
  const g = ((n >> 8) & 0xff) / 255;
  const b = (n & 0xff) / 255;
  return new Color3(r, g, b);
}

function shadeHex(hex: string, pct: number): string {
  const n = parseInt(hex.replace('#', ''), 16);
  let r = (n >> 16) + pct;
  let g = ((n >> 8) & 0xff) + pct;
  let b = (n & 0xff) + pct;
  r = Math.max(0, Math.min(255, r));
  g = Math.max(0, Math.min(255, g));
  b = Math.max(0, Math.min(255, b));
  return '#' + ((r << 16) | (g << 8) | b).toString(16).padStart(6, '0');
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

// ─── Camera setup ─────────────────────────────────────────────────
export function createCamera(scene: Scene): ArcRotateCamera {
  const camera = new ArcRotateCamera(
    'camera',
    -Math.PI / 4,
    Math.PI / 4,
    80,
    Vector3.Zero(),
    scene,
  );
  camera.attachControl(scene.getEngine().getRenderingCanvas(), true);
  camera.lowerRadiusLimit = 20;
  camera.upperRadiusLimit = 200;
  camera.wheelPrecision = 10;
  camera.panningSensibility = 50;
  return camera;
}

// ─── Lighting ─────────────────────────────────────────────────────
export function setupLighting(scene: Scene): void {
  const hemiLight = new HemisphericLight('hemi', new Vector3(0, 1, 0), scene);
  hemiLight.intensity = 0.6;
  hemiLight.diffuse = new Color3(0.9, 0.9, 1.0);
  hemiLight.groundColor = new Color3(0.3, 0.3, 0.4);

  const sunLight = new DirectionalLight('sun', new Vector3(-1, -2, -1), scene);
  sunLight.intensity = 1.5;
  sunLight.position = new Vector3(40, 60, 40);
  sunLight.diffuse = new Color3(1.0, 0.95, 0.8);
}

// ─── Scene builder ────────────────────────────────────────────────
export class WorldScene {
  private scene: Scene;
  private camera: ArcRotateCamera;
  private roomMeshes: Map<string, Mesh[]> = new Map();
  private propMeshes: Map<string, Mesh[]> = new Map();
  private characterNodes: Map<string, TransformNode> = new Map();
  private characterLabels: Map<string, Mesh> = new Map();
  private roomLabels: Map<string, Mesh> = new Map();

  constructor(scene: Scene, camera: ArcRotateCamera) {
    this.scene = scene;
    this.camera = camera;
  }

  // Build the entire static world
  buildWorld(): void {
    this.buildRooms();
    this.buildProps();
    this.buildNpcs();
    this.frameCamera();
  }

  // ─── Rooms ────────────────────────────────────────────────────
  private buildRooms(): void {
    for (const room of ROOMS) {
      const meshes: Mesh[] = [];
      const roomMeshes = this.buildRoomFloor(room);
      meshes.push(...roomMeshes);
      this.roomMeshes.set(room.id, meshes);
    }
  }

  private buildRoomFloor(room: typeof ROOMS[number]): Mesh[] {
    const meshes: Mesh[] = [];
    const baseColor = hexToColor3(room.floor);

    // Create individual tiles with checkerboard pattern
    for (let y = 0; y < room.h; y++) {
      for (let x = 0; x < room.w; x++) {
        const dark = (x + y) % 2 === 0;
        const tileColor = dark ? baseColor : hexToColor3(shadeHex(room.floor, 12));

        const tile = MeshBuilder.CreateBox(
          `tile_${room.id}_${x}_${y}`,
          { width: 1.8, height: 0.2, depth: 1.8 },
          this.scene,
        );
        // Position in iso space: convert tile coords to world position
        const worldX = (room.x + x) * 2 - 10;
        const worldZ = (room.y + y) * 2 - 10;
        tile.position.set(worldX, -0.1, worldZ);

        const mat = new StandardMaterial(`tileMat_${room.id}_${x}_${y}`, this.scene);
        mat.emissiveColor = tileColor;
        mat.diffuseColor = tileColor;
        tile.material = mat;
        meshes.push(tile);
      }
    }

    // Room label
    this.createRoomLabel(room);

    return meshes;
  }

  private createRoomLabel(room: typeof ROOMS[number]): void {
    const labelMesh = MeshBuilder.CreatePlane(
      `roomLabel_${room.id}`,
      { width: 6, height: 1.5 },
      this.scene,
    );

    const worldCX = (room.x + room.w / 2) * 2 - 10;
    const worldCZ = (room.y + room.h / 2) * 2 - 10;
    labelMesh.position.set(worldCX, 8, worldCZ);
    labelMesh.billboardMode = Mesh.BILLBOARDMODE_ALL;

    const tex = new DynamicTexture(
      `roomLabelTex_${room.id}`,
      { width: 512, height: 128 },
      this.scene,
      false,
    );
    const ctx = tex.getContext() as unknown as CanvasRenderingContext2D;
    ctx.fillStyle = 'rgba(0,0,0,0.75)';
    ctx.beginPath();
    ctx.roundRect(0, 0, 512, 128, 16);
    ctx.fill();
    ctx.fillStyle = room.color;
    ctx.font = 'bold 48px system-ui, sans-serif';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.fillText(room.name, 256, 64);
    tex.update();

    const mat = new StandardMaterial(`roomLabelMat_${room.id}`, this.scene);
    mat.emissiveColor = new Color3(1, 1, 1);
    mat.diffuseColor = new Color3(0, 0, 0);
    mat.diffuseTexture = tex;
    mat.opacityTexture = tex;
    mat.emissiveTexture = tex;
    mat.disableLighting = true;
    labelMesh.material = mat;

    this.roomLabels.set(room.id, labelMesh);
  }

  // ─── Props ────────────────────────────────────────────────────
  private buildProps(): void {
    for (const room of ROOMS) {
      const meshes: Mesh[] = [];
      for (const prop of room.props) {
        const propMeshes = this.buildProp(prop, room);
        meshes.push(...propMeshes);
      }
      this.propMeshes.set(room.id, meshes);
    }
  }

  private buildProp(prop: typeof ROOMS[number]['props'][number], room: typeof ROOMS[number]): Mesh[] {
    const meshes: Mesh[] = [];
    const color = PROP_COLORS[prop.kind] || '#6b7280';
    const height = PROP_HEIGHTS[prop.kind] ?? 1.0;
    const w = prop.w ?? 1;
    const h = prop.h ?? 1;

    const worldX = (room.x + prop.x) * 2 - 10;
    const worldZ = (room.y + prop.y) * 2 - 10;

    const box = MeshBuilder.CreateBox(
      `prop_${room.id}_${prop.kind}_${prop.x}_${prop.y}`,
      { width: w * 1.6, height: height, depth: h * 1.6 },
      this.scene,
    );
    box.position.set(worldX, height / 2, worldZ);

    const mat = new StandardMaterial(`propMat_${prop.kind}`, this.scene);
    mat.emissiveColor = hexToColor3(color);
    mat.diffuseColor = hexToColor3(color);
    box.material = mat;
    meshes.push(box);

    // Add extra detail for specific prop types
    if (prop.kind === 'monitor') {
      const screen = MeshBuilder.CreateBox(
        `screen_${room.id}_${prop.x}_${prop.y}`,
        { width: 1.2, height: 0.8, depth: 0.05 },
        this.scene,
      );
      screen.position.set(worldX, height + 0.4, worldZ);
      const screenMat = new StandardMaterial(`screenMat_${prop.kind}`, this.scene);
      screenMat.emissiveColor = new Color3(0.2, 0.6, 1.0);
      screenMat.diffuseColor = new Color3(0.1, 0.3, 0.5);
      screen.material = screenMat;
      screen.parent = box;
      meshes.push(screen);
    }

    if (prop.kind === 'plant') {
      const leaves = MeshBuilder.CreateSphere(
        `leaves_${room.id}_${prop.x}_${prop.y}`,
        { diameter: 1.2 },
        this.scene,
      );
      leaves.position.set(worldX, height + 0.5, worldZ);
      const leavesMat = new StandardMaterial(`leavesMat_${prop.kind}`, this.scene);
      leavesMat.emissiveColor = hexToColor3(shadeHex(color, 40));
      leavesMat.diffuseColor = hexToColor3(shadeHex(color, 20));
      leaves.material = leavesMat;
      leaves.parent = box;
      meshes.push(leaves);
    }

    return meshes;
  }

  // ─── NPCs ─────────────────────────────────────────────────────
  private buildNpcs(): void {
    for (const npc of NPCS) {
      if (npc.invisible) continue;
      const room = ROOMS.find((r) => r.id === npc.room);
      if (!room) continue;
      this.createCharacter(`npc-${npc.id}`, npc.name, npc.hue, room.x + npc.x, room.y + npc.y);
    }
  }

  // ─── Character creation ─────────────────────────────────────────
  private createCharacter(
    id: string,
    name: string,
    hue: number,
    tileX: number,
    tileY: number,
  ): TransformNode {
    const worldX = tileX * 2 - 10;
    const worldZ = tileY * 2 - 10;

    const node = new TransformNode(`char_${id}`, this.scene);
    node.position.set(worldX, 0, worldZ);

    // Body (capsule)
    const body = MeshBuilder.CreateCapsule(
      `body_${id}`,
      { radius: 0.25, height: 1.0 },
      this.scene,
    );
    body.position.y = 0.75;
    const bodyMat = new StandardMaterial(`bodyMat_${id}`, this.scene);
    bodyMat.emissiveColor = hslToColor3(hue, 0.7, 0.5);
    bodyMat.diffuseColor = hslToColor3(hue, 0.7, 0.5);
    body.material = bodyMat;
    body.parent = node;

    // Head (sphere)
    const head = MeshBuilder.CreateSphere(
      `head_${id}`,
      { diameter: 0.4 },
      this.scene,
    );
    head.position.y = 1.4;
    const headMat = new StandardMaterial(`headMat_${id}`, this.scene);
    headMat.emissiveColor = hslToColor3(hue, 0.3, 0.78);
    headMat.diffuseColor = hslToColor3(hue, 0.3, 0.78);
    head.material = headMat;
    head.parent = node;

    // Eyes
    const eyeMat = new StandardMaterial(`eyeMat_${id}`, this.scene);
    eyeMat.emissiveColor = new Color3(1, 1, 1);
    eyeMat.diffuseColor = new Color3(1, 1, 1);

    const leftEye = MeshBuilder.CreateSphere(`leftEye_${id}`, { diameter: 0.08 }, this.scene);
    leftEye.position.set(-0.1, 1.45, 0.18);
    leftEye.material = eyeMat;
    leftEye.parent = node;

    const rightEye = MeshBuilder.CreateSphere(`rightEye_${id}`, { diameter: 0.08 }, this.scene);
    rightEye.position.set(0.1, 1.45, 0.18);
    rightEye.material = eyeMat;
    rightEye.parent = node;

    // Label (floating text)
    this.createCharacterLabel(id, name, hue, node);

    this.characterNodes.set(id, node);
    return node;
  }

  private createCharacterLabel(id: string, name: string, hue: number, parent: TransformNode): void {
    const labelMesh = MeshBuilder.CreatePlane(
      `label_${id}`,
      { width: 3, height: 0.8 },
      this.scene,
    );
    labelMesh.position.set(0, 2.2, 0);
    labelMesh.billboardMode = Mesh.BILLBOARDMODE_ALL;
    labelMesh.parent = parent;

    const tex = new DynamicTexture(
      `labelTex_${id}`,
      { width: 256, height: 64 },
      this.scene,
      false,
    );
    const ctx = tex.getContext() as unknown as CanvasRenderingContext2D;
    ctx.fillStyle = 'rgba(0,0,0,0.8)';
    ctx.beginPath();
    ctx.roundRect(0, 0, 256, 64, 8);
    ctx.fill();
    ctx.fillStyle = `hsl(${hue}, 70%, 70%)`;
    ctx.font = 'bold 28px system-ui, sans-serif';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.fillText(name, 128, 34);
    tex.update();

    const mat = new StandardMaterial(`labelMat_${id}`, this.scene);
    mat.emissiveColor = new Color3(1, 1, 1);
    mat.diffuseColor = new Color3(0, 0, 0);
    mat.diffuseTexture = tex;
    mat.opacityTexture = tex;
    mat.emissiveTexture = tex;
    mat.disableLighting = true;
    labelMesh.material = mat;

    this.characterLabels.set(id, labelMesh);
  }

  // ─── Avatar characters ─────────────────────────────────────────
  buildAvatars(avatars: AvatarState[]): void {
    // Remove existing avatar characters
    for (const [id, node] of this.characterNodes) {
      if (!id.startsWith('npc-')) {
        node.dispose();
        this.characterNodes.delete(id);
        const label = this.characterLabels.get(id);
        if (label) {
          label.dispose();
          this.characterLabels.delete(id);
        }
      }
    }

    // Create new avatar characters
    for (const av of avatars) {
      const room = ROOMS.find((r) => r.id === av.room);
      if (!room) continue;
      const worldX = room.x + av.px;
      const worldZ = room.y + av.py;
      this.createCharacter(av.id, av.name, av.hue, worldX, worldZ);
    }
  }

  // ─── Update avatar positions ───────────────────────────────────
  updateAvatarPositions(avatars: AvatarState[]): void {
    for (const av of avatars) {
      const node = this.characterNodes.get(av.id);
      if (!node) continue;

      const room = ROOMS.find((r) => r.id === av.room);
      if (!room) continue;

      const targetX = (room.x + av.px) * 2 - 10;
      const targetZ = (room.y + av.py) * 2 - 10;

      // Smooth interpolation
      node.position.x += (targetX - node.position.x) * 0.1;
      node.position.z += (targetZ - node.position.z) * 0.1;

      // Bobbing animation
      node.position.y = Math.sin(Date.now() * 0.003 + av.hue) * 0.05;
    }
  }

  // ─── Camera framing ────────────────────────────────────────────
  private frameCamera(): void {
    // Calculate world center based on all rooms
    let minX = Infinity, maxX = -Infinity, minZ = Infinity, maxZ = -Infinity;
    for (const room of ROOMS) {
      const wx = room.x * 2 - 10;
      const wz = room.y * 2 - 10;
      const wx2 = (room.x + room.w) * 2 - 10;
      const wz2 = (room.y + room.h) * 2 - 10;
      minX = Math.min(minX, wx, wx2);
      maxX = Math.max(maxX, wx, wx2);
      minZ = Math.min(minZ, wz, wz2);
      maxZ = Math.max(maxZ, wz, wz2);
    }

    const centerX = (minX + maxX) / 2;
    const centerZ = (minZ + maxZ) / 2;

    this.camera.target.set(centerX, 0, centerZ);
    this.camera.radius = Math.max(maxX - minX, maxZ - minZ) * 1.2;
  }

  // ─── Dispose ───────────────────────────────────────────────────
  dispose(): void {
    for (const [, meshes] of this.roomMeshes) {
      for (const m of meshes) m.dispose();
    }
    for (const [, meshes] of this.propMeshes) {
      for (const m of meshes) m.dispose();
    }
    for (const [, node] of this.characterNodes) {
      node.dispose();
    }
    for (const [, label] of this.characterLabels) {
      label.dispose();
    }
    for (const [, label] of this.roomLabels) {
      label.dispose();
    }
    this.roomMeshes.clear();
    this.propMeshes.clear();
    this.characterNodes.clear();
    this.characterLabels.clear();
    this.roomLabels.clear();
  }
}