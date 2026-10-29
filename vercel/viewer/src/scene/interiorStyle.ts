// Port of world-engine-godot/InteriorStyle.cs: Godot restyles each imported level by mesh-name
// prefix, so building N's interior wears scheme N. Same rules, same palette, same pick order.
import * as THREE from 'three';

export const FRAME_SKIP = 'interior_frame_skip';

const cache = new Map<string, THREE.MeshStandardMaterial>();
function M(albedo: number, rough = 0.8, metal = 0, glow?: number, glowEnergy = 1): THREE.MeshStandardMaterial {
  const key = `${albedo}|${rough}|${metal}|${glow}|${glowEnergy}`;
  let m = cache.get(key);
  if (!m) {
    m = new THREE.MeshStandardMaterial({ color: new THREE.Color().setHex(albedo, THREE.SRGBColorSpace), roughness: rough, metalness: metal });
    if (glow !== undefined) { m.emissive = new THREE.Color().setHex(glow, THREE.SRGBColorSpace); m.emissiveIntensity = glowEnergy; }
    cache.set(key, m);
  }
  return m;
}
const pick = <T,>(o: T[], n: number) => o[(n - 1) % o.length];

const Walnut = () => M(0x6b4a32, 0.6), Oak = () => M(0xb08a5a, 0.65), Laminate = () => M(0xe8e6e1, 0.5);
const Stone = () => M(0x3d3d40, 0.35), Steel = () => M(0xc9ccd1, 0.35, 0.6), Black = () => M(0x1d1f22, 0.4);
const Charcoal = () => M(0x2b2d31, 0.6), Porcelain = () => M(0xf4f4f2, 0.15), Brass = () => M(0xb08d57, 0.35, 0.8);
const WarmGlow = () => M(0xf3e6c8, 0.6, 0, 0xffd9a0, 1.2), Screen = () => M(0x15171a, 0.15, 0, 0x2a4a75, 0.9);
const Whiteboard = () => M(0xf8f8f6, 0.1), Glass = () => M(0x9fc4d8, 0.05, 0.2), Terracotta = () => M(0xb8643f, 0.85);
const Foliage = () => M(0x4f7a3a, 0.9), Lawn = () => M(0x6d8a4a, 0.95), Paving = () => M(0xa8a39a, 0.95);

type Rules = [string, THREE.Material][];

function homeRules(n: number): Rules {
  const walls = M(pick([0xefe6d6, 0xe4ece6, 0xf1e3dc, 0xe6e9f0], n), 0.9);
  const sofa = M(pick([0x3f7f8c, 0x8c5a3c, 0x5b6b8c, 0x7a8c5b], n), 0.9);
  const blanket = M(pick([0x5b7fa6, 0xc98b6b, 0x8a6aa6, 0x6aa68a], n), 0.95);
  const livingRug = M(pick([0xb5523b, 0x4f6d7a, 0xc9a24f, 0x8c4f6d], n), 0.95);
  const bedroomRug = M(pick([0x6a5a9c, 0x7a8c5b, 0x4f7a8c, 0xb5733b], n), 0.95);
  return [
    ['Wall_', walls], ['Corridor_Wall', walls], ['MidWall', walls], ['BathBathDiv', walls], ['Front_Door', Walnut()],
    ['Hall_Rug', M(0x8a6d4f, 0.95)], ['Living_Rug', livingRug], ['Bedroom_Rug', bedroomRug], ['Coatrack', Brass()],
    ['Sofa_', sofa], ['Coffee_', Walnut()], ['TV_Stand', Walnut()], ['TV', M(0x15171a, 0.15, 0, 0x1e2a3c, 0.6)],
    ['Lamp_Pole', Brass()], ['Lamp_Shade', WarmGlow()], ['Kit_Counter_Top', Stone()], ['Kit_Stove_Top', Black()],
    ['Kit_Counter', Laminate()], ['Kit_Cabinet', Laminate()], ['Kit_Fridge', Steel()], ['Kit_Stove', Steel()],
    ['Kit_Island', Oak()], ['Island_Leg', Black()], ['Stool_Seat', Oak()], ['Stool_Pole', Black()],
    ['Dining_Chair', Walnut()], ['Dining_', Oak()], ['Bed_Headboard', M(0x7a6a5a, 0.9)], ['Bed_Mattress', M(0xf2efe8, 0.9)],
    ['Bed_Blanket', blanket], ['Bed_Frame', Walnut()], ['Pillow', M(0xfafafa, 0.95)], ['Nightstand', Walnut()],
    ['Night_Lamp', WarmGlow()], ['Wardrobe', Oak()], ['Dresser', Oak()], ['Toilet', Porcelain()], ['Bath_Sink', Porcelain()],
    ['Bath_Tub', Porcelain()], ['Bath_Mirror', M(0xd8e2e8, 0.05, 1)], ['Office_Monitor', Screen()], ['Office_Chair', Black()],
    ['Office_Leg', Black()], ['Office_Desk', Oak()], ['Washer_Door', Glass()], ['Washing_Machine', Laminate()],
  ];
}
function officeRules(n: number): Rules {
  const walls = M(pick([0xe9edf0, 0xeef0ea, 0xf0ece6], n), 0.9);
  const carpet = M(pick([0x5d6670, 0x4f5f6b, 0x6b6257], n), 0.95);
  const accent = M(pick([0x2f6f9f, 0x3f8f6f, 0xc0603a], n), 0.8);
  return [
    ['WF_Floor', carpet], ['WF_Wall_', walls], ['WF_DeskTop', Laminate()], ['WF_DeskLeg', Black()], ['WF_Monitor', Screen()],
    ['WF_Keyboard', Charcoal()], ['WF_CPU', Charcoal()], ['WF_Docs', M(0xf5f5f0, 0.9)], ['WF_ChairSeat', accent], ['WF_ChairBack', accent],
    ['WF_ConfTable', Walnut()], ['WF_ConfLeg', Black()], ['WF_ConfChairSeat', Charcoal()], ['WF_ConfChairBack', Charcoal()],
    ['WF_Partition', M(0x7a8a96, 0.95)], ['WF_Whiteboard', Whiteboard()], ['WF_Door', M(0x3a3f45, 0.5)], ['WF_GlassW', Glass()],
    ['WF_EntryMat', Charcoal()], ['WF_Sofa', accent],
  ];
}
function cafeRules(n: number): Rules {
  const walls = M(pick([0xf3e2c7, 0xe9d5c0, 0xdfe8e1], n), 0.9);
  const floor = M(pick([0xc08a55, 0x9c6b43, 0xb5734a], n), 0.6);
  const chairs = M(pick([0xc0392b, 0x2f6f6f, 0xd68a1f], n), 0.7);
  const sofa = M(pick([0x7a3b3b, 0x3b4f7a, 0x5b6b3b], n), 0.9);
  return [
    ['Social_Floor', floor], ['Social_Wall_', walls], ['Cafe_Table', M(0xf0ede8, 0.2)], ['Cafe_Chair', chairs],
    ['Cafe_Counter_Top', Stone()], ['Cafe_Counter', Walnut()], ['Cafe_ServiceKiosk', Steel()], ['Cafe_SofaBack', sofa],
    ['Cafe_Sofa', sofa], ['Cafe_CoffeeTable', Walnut()],
  ];
}
function schoolRules(n: number): Rules {
  const walls = M(pick([0xf4efe3, 0xe7efe9, 0xefe8f2], n), 0.9);
  const floor = M(pick([0xc9a46c, 0x9fb0b8, 0xa7b89a], n), 0.6);
  const chairs = M(pick([0x2f6f9f, 0xc0603a, 0x3f8f6f], n), 0.7);
  return [
    ['Academic_Floor', floor], ['Academic_Wall_', walls], ['Whiteboard', Whiteboard()], ['BulletinBoard', M(0xb98f5e, 0.95)],
    ['Teacher_Desk', Walnut()], ['Teacher_Chair', Black()], ['DeskChair_', chairs], ['Desk_', Oak()],
    ['BookshelfShelf_', M(0xa0463c, 0.85)], ['Bookshelf_', Walnut()], ['StudyTable_', Oak()], ['StudyChair_', chairs],
    ['Academic_FrontDoor', Walnut()], ['Academic_EntryMat', Charcoal()], ['Academic_Clock', M(0xf5f1e6, 0.5)],
  ];
}

export const schemeNumber = (sceneId: string) => {
  const n = parseInt(sceneId.slice(sceneId.lastIndexOf('_') + 1), 10);
  return Number.isFinite(n) ? Math.max(n, 1) : 1;
};

/** The level's mesh children, as Godot sees them (direct children of the imported root). */
function meshChildren(root: THREE.Object3D): THREE.Mesh[] {
  return root.children.filter((c) => (c as THREE.Mesh).isMesh) as THREE.Mesh[];
}

function wallBounds(level: THREE.Object3D): THREE.Box3 | null {
  const box = new THREE.Box3();
  let any = false;
  for (const m of meshChildren(level)) {
    const n = m.name;
    if (n.startsWith('UCX_') || !n.includes('Wall_') || n.includes('Corridor') || n.includes('MidWall')) continue;
    box.union(new THREE.Box3().setFromObject(m));
    any = true;
  }
  return any ? box : null;
}

function plane(w: number, d: number, m: THREE.Material, x: number, y: number, z: number, name: string) {
  const p = new THREE.Mesh(new THREE.PlaneGeometry(w, d).rotateX(-Math.PI / 2), m);
  p.position.set(x, y, z);
  p.name = name;
  p.receiveShadow = true;
  return p;
}

/**
 * InteriorStyle.Apply. `level` is the imported FBX root (already scaled to metres and with its
 * world matrix current); `wrapper` is the parent the room floor and grounds are added to, in metres.
 */
export function applyInteriorStyle(level: THREE.Object3D, wrapper: THREE.Object3D, sceneId: string) {
  const n = schemeNumber(sceneId);
  const kind = sceneId.split('_')[0];
  const cfg =
    kind === 'personal' ? { rules: homeRules(n), slab: Lawn(), grounds: null, roomFloor: M(0xa0703f, 0.55) }
    : kind === 'workplace' ? { rules: officeRules(n), slab: null, grounds: Paving(), roomFloor: null }
    : kind === 'social' ? { rules: cafeRules(n), slab: Paving(), grounds: null, roomFloor: null }
    : { rules: schoolRules(n), slab: null, grounds: Lawn(), roomFloor: null };

  // Viewer-only addition: `Hermes` is a UE placeholder character mesh in Personal_Level that
  // InteriorStyle.cs's rule misses, so Godot draws it as a figure that reads as an extra agent.
  // The viewer must not show a person the feed doesn't contain. Reported for the Godot side.
  for (const c of level.children) if (c.name === 'Hermes' || c.name === 'AvatarCharacter') c.visible = false;

  for (const mi of meshChildren(level)) {
    const name = mi.name;
    if (name.startsWith('UCX_')) continue;
    if (name.includes('CeilingLight') || name.startsWith('Ceiling_Light') || name.startsWith('SimBody_Character') || name === 'AvatarCharacter') {
      mi.visible = false;
      continue;
    }
    if (name === 'Floor') {
      // An 80 m slab, far larger than the room: grounds outside, kept out of camera framing.
      if (cfg.slab) mi.material = cfg.slab;
      mi.userData[FRAME_SKIP] = true;
      continue;
    }
    if (name.includes('Plant')) {
      mi.material = name.includes('Pot') ? Terracotta() : Foliage();
      continue;
    }
    const rule = cfg.rules.find(([prefix]) => name.startsWith(prefix));
    if (rule) mi.material = rule[1];
  }

  for (const old of wrapper.children.filter((c) => c.name === 'RoomFloor' || c.name === 'Grounds')) wrapper.remove(old);
  const wb = wallBounds(level);
  if (cfg.roomFloor && wb)
    wrapper.add(plane(wb.max.x - wb.min.x, wb.max.z - wb.min.z, cfg.roomFloor, (wb.min.x + wb.max.x) / 2, 0.005, (wb.min.z + wb.max.z) / 2, 'RoomFloor'));
  if (cfg.grounds) {
    const c = wb ? wb.getCenter(new THREE.Vector3()) : new THREE.Vector3();
    const g = plane(80, 80, cfg.grounds, c.x, -0.02, c.z, 'Grounds');
    g.userData[FRAME_SKIP] = true;
    wrapper.add(g);
  }
}

/** WorldView.TryBounds, skipping the frame-skip group and hidden meshes. */
export function frameBounds(root: THREE.Object3D): THREE.Box3 {
  const box = new THREE.Box3();
  root.updateMatrixWorld(true);
  const visit = (o: THREE.Object3D) => {
    if (!o.visible || o.userData[FRAME_SKIP]) return;
    const m = o as THREE.Mesh;
    if (m.isMesh && m.geometry) {
      if (!m.geometry.boundingBox) m.geometry.computeBoundingBox();
      box.union(m.geometry.boundingBox!.clone().applyMatrix4(m.matrixWorld));
    }
    o.children.forEach(visit);
  };
  visit(root);
  return box;
}
