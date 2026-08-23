import * as THREE from 'three';

const PALETTE = {
  "fridge": 0x7aa2ff,
  "stove": 0xff8a3d,
  "bed": 0x7a5cff,
  "toilet": 0x2ec4b6,
  "sink": 0x2ec4b6,
  "bathtub": 0x2ec4b6,
  "shower": 0x2ec4b6,
  "couch": 0x5cc8ff,
  "tv": 0xff3b30,
  "video game console": 0xff3b30,
  "laptop": 0xb47aff,
  "default": 0x9aa6c2
};

function colorFor(name){
  if (PALETTE[name] !== undefined) return PALETTE[name];
  // hash to hue for variety
  let h=0; for(let i=0;i<name.length;i++) h=(h*31 + name.charCodeAt(i))%360;
  const c=new THREE.Color().setHSL(h/360, 0.62, 0.6);
  return c.getHex();
}

function makeLabel(text){
  const c=document.createElement('canvas');
  c.width=256; c.height=64;
  const g=c.getContext('2d');
  g.fillStyle='#0f1422f0';
  g.fillRect(0,0,256,64);
  g.strokeStyle='#26304a'; g.strokeRect(0.5,0.5,255,63);
  g.fillStyle='#e6e8ee'; g.font='700 13px system-ui, sans-serif';
  g.textAlign='center'; g.textBaseline='middle';
  g.fillText(text.slice(0,26),128,32);
  const tex=new THREE.CanvasTexture(c);
  tex.colorSpace = THREE.SRGBColorSpace;
  const mat=new THREE.SpriteMaterial({ map:tex, transparent:true });
  const spr=new THREE.Sprite(mat);
  spr.scale.set(1.2,0.3,1);
  return spr;
}

export class HouseMesh {
  constructor(scene){
    this.scene=scene;
    this.group=new THREE.Group();
    scene.add(this.group);
    this.floor=null;
    this.walls=[];
    this.objectMeshes=new Map(); // SimObject -> Mesh
    this.labelSprites=[];
  }
  clear(){
    for(const m of this.objectMeshes.values()){
      this.group.remove(m.mesh);
      if(m.label) this.group.remove(m.label);
    }
    this.objectMeshes.clear();
    this.labelSprites.forEach(s=> this.group.remove(s));
    this.labelSprites=[];
    if(this.floor){ this.group.remove(this.floor); this.floor=null; }
    this.walls.forEach(w=> this.group.remove(w));
    this.walls=[];
  }
  buildFromRoom(room){
    this.clear();
    const [w,h]=room.getDimensions();
    // floor
    const floorGeo=new THREE.PlaneGeometry(w, h);
    const floorMat=new THREE.MeshStandardMaterial({ color:0x151a28, roughness:0.9, metalness:0.02 });
    const floor=new THREE.Mesh(floorGeo,floorMat);
    floor.rotation.x=-Math.PI/2;
    floor.position.set(w/2, 0, h/2);
    floor.receiveShadow=true;
    this.group.add(floor); this.floor=floor;
    // cell lines
    const grid=new THREE.GridHelper(Math.max(w,h), Math.max(w,h), 0x2b3655, 0x1a2238);
    // fake with lines? keep helper scaled
    grid.position.set(w/2, 0.02, h/2);
    // scale grid to room size
    // helper is square; just add a custom
    this.group.add(grid);
    this.walls.push(grid);
    // perimeter walls
    const wallMat=new THREE.MeshStandardMaterial({ color:0x1e263a });
    const th=0.15, hh=1.0;
    const mkWall=(x,y, sx, sz)=>{
      const m=new THREE.Mesh(new THREE.BoxGeometry(sx, hh, sz), wallMat);
      m.position.set(x, hh/2, y);
      m.castShadow=true; m.receiveShadow=true;
      this.group.add(m); this.walls.push(m);
    };
    mkWall(w/2, 0, w+th, th);
    mkWall(w/2, h, w+th, th);
    mkWall(0, h/2, th, h);
    mkWall(w, h/2, th, h);

    for(const obj of room.getObjects()){
      this.addObject(obj);
    }
  }
  addObject(obj){
    const [x,y]=obj.getCoordinates();
    const name=obj.getName();
    const col=colorFor(name);
    // pick shape family
    let geo;
    const foodish = ["fridge","stove","microwave","grill","buffet table","vending machine"].includes(name);
    const sitish = ["bed","couch","chair","toilet","bathtub","hot tub"].includes(name);
    if (foodish) geo=new THREE.BoxGeometry(0.85,0.7,0.85);
    else if (sitish) geo=new THREE.BoxGeometry(0.9,0.45,0.9);
    else if (name.includes("table")) geo=new THREE.CylinderGeometry(0.42,0.42,0.55, 8);
    else geo=new THREE.BoxGeometry(0.62,0.62,0.62);

    const mat=new THREE.MeshStandardMaterial({ color:col, roughness:0.7, emissive: col, emissiveIntensity:0.08 });
    const mesh=new THREE.Mesh(geo, mat);
    mesh.position.set(x+0.5, geo.parameters.height ? geo.parameters.height/2 : 0.31, y+0.5);
    mesh.castShadow=true; mesh.receiveShadow=true;
    mesh.userData.name=name;
    this.group.add(mesh);
    const label=makeLabel(name);
    label.position.set(x+0.5, 1.35, y+0.5);
    this.group.add(label);
    this.objectMeshes.set(obj, { mesh, label, baseY: mesh.position.y });
  }
  updateObjectPositions(){
    for(const [obj, {mesh,label}] of this.objectMeshes){
      const [x,y]=obj.getCoordinates();
      mesh.position.x=x+0.5; mesh.position.z=y+0.5;
      label.position.x=x+0.5; label.position.z=y+0.5;
    }
  }
  pulseObject(obj){
    const e=this.objectMeshes.get(obj);
    if(!e) return;
    const m=e.mesh;
    m.scale.set(1.15,1.15,1.15);
    setTimeout(()=> m.scale.set(1,1,1), 220);
  }
  highlightTarget(obj){
    for(const {mesh} of this.objectMeshes.values()){
      mesh.material.emissiveIntensity=0.08;
    }
    if(obj){
      const e=this.objectMeshes.get(obj);
      if(e) e.mesh.material.emissiveIntensity=0.45;
    }
  }
}
