import * as THREE from 'three';

export function createScene(canvas){
  const renderer = new THREE.WebGLRenderer({ canvas, antialias:true, alpha:false });
  renderer.setPixelRatio(Math.min(devicePixelRatio, 2));
  renderer.shadowMap.enabled = true;

  const scene = new THREE.Scene();
  scene.background = new THREE.Color(0x0b0e14);
  scene.fog = new THREE.Fog(0x0b0e14, 18, 40);

  const camera = new THREE.PerspectiveCamera(45, 1, 0.1, 100);
  camera.position.set(12, 12, 12);

  // lights
  const amb = new THREE.AmbientLight(0x8ea0c6, 0.7);
  scene.add(amb);
  const dir = new THREE.DirectionalLight(0xffffff, 1.1);
  dir.position.set(8, 14, 6);
  dir.castShadow = true;
  dir.shadow.mapSize.set(2048,2048);
  scene.add(dir);
  const hemi = new THREE.HemisphereLight(0x7aa2ff, 0x0b0e14, 0.35);
  scene.add(hemi);

  // ground
  const ground = new THREE.Mesh(
    new THREE.PlaneGeometry(80,80),
    new THREE.MeshStandardMaterial({ color:0x0e1320, roughness:0.92 })
  );
  ground.rotation.x = -Math.PI/2;
  ground.position.y = -0.02;
  ground.receiveShadow = true;
  scene.add(ground);

  // grid helper
  const grid = new THREE.GridHelper(24, 24, 0x26304a, 0x1a2238);
  grid.position.y = 0.01;
  scene.add(grid);

  // simple orbit (no extra addon) — drag to orbit, wheel to zoom
  let isDragging=false, lastX=0, lastY=0;
  let yaw = 0.8, pitch = 0.9, dist = 16;
  const target = new THREE.Vector3(5,0,5);
  function updateCam(){
    const x = target.x + dist * Math.sin(yaw) * Math.cos(pitch);
    const y = target.y + dist * Math.sin(pitch);
    const z = target.z + dist * Math.cos(yaw) * Math.cos(pitch);
    camera.position.set(x,y,z);
    camera.lookAt(target);
  }
  updateCam();
  canvas.addEventListener('pointerdown', e=>{
    isDragging=true; lastX=e.clientX; lastY=e.clientY; canvas.setPointerCapture(e.pointerId);
  });
  canvas.addEventListener('pointerup', ()=> isDragging=false);
  canvas.addEventListener('pointermove', e=>{
    if(!isDragging) return;
    const dx=e.clientX-lastX, dy=e.clientY-lastY;
    lastX=e.clientX; lastY=e.clientY;
    yaw -= dx*0.005;
    pitch = Math.max(0.15, Math.min(1.45, pitch - dy*0.005));
    updateCam();
  });
  canvas.addEventListener('wheel', e=>{
    dist = Math.max(6, Math.min(32, dist + e.deltaY*0.015));
    updateCam();
  }, { passive:true });

  function resize(){
    const w = canvas.clientWidth, h = canvas.clientHeight;
    const dpr = Math.min(devicePixelRatio, 2);
    const needW = Math.floor(w*dpr), needH = Math.floor(h*dpr);
    if (canvas.width !== needW || canvas.height !== needH){
      renderer.setSize(w, h, false);
    }
    camera.aspect = w/h;
    camera.updateProjectionMatrix();
  }

  return { renderer, scene, camera, target, updateCam, resize, setTarget(v){ target.copy(v); updateCam(); } };
}
