import * as THREE from 'three';

export class SimAvatar {
  constructor(scene){
    this.scene=scene;
    this.group=new THREE.Group();
    scene.add(this.group);

    // capsule-ish sim: cylinder + sphere top
    const bodyMat=new THREE.MeshStandardMaterial({ color:0xffffff, roughness:0.5, metalness:0.05 });
    this.body=new THREE.Mesh(new THREE.CapsuleGeometry(0.28, 0.5, 4, 12), bodyMat);
    this.body.position.y=0.55;
    this.body.castShadow=true;
    this.group.add(this.body);

    // head
    const headMat=new THREE.MeshStandardMaterial({ color:0xffe8cc });
    this.head=new THREE.Mesh(new THREE.SphereGeometry(0.22, 12, 10), headMat);
    this.head.position.y=1.05;
    this.group.add(this.head);

    // burnout ring
    const ringGeo=new THREE.RingGeometry(0.35,0.42, 32);
    // make double sided
    const ringMat=new THREE.MeshBasicMaterial({ color:0xff8a3d, transparent:true, opacity:0, side:THREE.DoubleSide });
    this.ring=new THREE.Mesh(ringGeo, ringMat);
    this.ring.rotation.x=-Math.PI/2;
    this.ring.position.y=0.08;
    this.ring.visible=false;
    this.group.add(this.ring);

    // shadow blob
    const blob=new THREE.Mesh(
      new THREE.CircleGeometry(0.32, 12),
      new THREE.MeshBasicMaterial({ color:0x000000, transparent:true, opacity:0.28 })
    );
    blob.rotation.x=-Math.PI/2;
    blob.position.y=0.015;
    this.blob=blob;
    this.group.add(blob);

    this.targetPos=new THREE.Vector3(0.5,0,0.5);
    this.lerpPos=new THREE.Vector3(0.5,0,0.5);
  }

  setCell([x,y], immediate=false){
    this.targetPos.set(x+0.5, 0, y+0.5);
    if(immediate){
      this.lerpPos.copy(this.targetPos);
      this.group.position.copy(this.targetPos);
    }
  }
  setBurnout(isBurnt, progress=0){
    if(isBurnt){
      this.body.material.color.setHex(0x8a7a6a);
      this.body.scale.set(1,0.55,1);
      this.body.position.y=0.32;
      this.head.position.y=0.62;
      this.ring.visible=true;
      const pct = Math.max(0, Math.min(1, progress));
      this.ring.material.opacity=0.85;
      // animate ring arc via scale? keep full ring, pulse opacity
      this.ring.scale.set(0.6 + pct*0.5, 0.6 + pct*0.5, 1);
    } else {
      this.body.material.color.setHex(0xffffff);
      this.body.scale.set(1,1,1);
      this.body.position.y=0.55;
      this.head.position.y=1.05;
      this.ring.visible=false;
      this.ring.material.opacity=0;
    }
  }
  update(dt){
    // smooth lerp 12x sec
    const k = 1 - Math.pow(0.001, dt);
    this.lerpPos.lerp(this.targetPos, k);
    this.group.position.x=this.lerpPos.x;
    this.group.position.z=this.lerpPos.z;
    // bob when walking
    const moving = this.lerpPos.distanceTo(this.targetPos) > 0.01;
    if(moving && !this.ring.visible){
      const t=performance.now()*0.008;
      this.group.position.y = Math.abs(Math.sin(t))*0.06;
      this.body.rotation.z = Math.sin(t*0.7)*0.08;
    } else {
      this.group.position.y = 0;
      this.body.rotation.z = 0;
    }
  }
  flashInteract(){
    this.body.material.emissive = new THREE.Color(0x7aa2ff);
    this.body.material.emissiveIntensity=0.6;
    setTimeout(()=> { this.body.material.emissiveIntensity=0; }, 220);
  }
}
