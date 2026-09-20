# Realistic Viewer Architecture — NLT World Engine

## Goal

Replace the procedural-capsule viewer with a **realistic spectator viewer** that
renders AI residents as animated GLB humans in a physically-based environment.
Think: observing a living world, not a game.

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────────┐
│                    Realistic Viewer (Three.js)                   │
│                                                                  │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────────────┐  │
│  │  GLB Loader   │  │  PBR Meshes  │  │  Post-Processing     │  │
│  │  + Animations │  │  + Materials │  │  (SSAO, Bloom, TAA)  │  │
│  └──────────────┘  └──────────────┘  └──────────────────────┘  │
│                                                                  │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────────────┐  │
│  │  Camera Rig   │  │  Lighting    │  │  Spectator HUD       │  │
│  │  (orbit/fly)  │  │  (soft/IBL)  │  │  (needs/events/info) │  │
│  └──────────────┘  └──────────────┘  └──────────────────────┘  │
│                                                                  │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │              Live Client (WebSocket Bridge)                │   │
│  │   Maps contract-v1 snapshots → viewer scene state         │   │
│  └──────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
                              │
                              │ WebSocket + REST
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│              Existing Python Server (server.py)                  │
│              Existing ECS Kernel (world_engine.py)               │
└─────────────────────────────────────────────────────────────────┘
```

## File Structure

```
world-engine-3d/
├── index.html              # Entry point (loads realistic viewer)
├── src/
│   ├── main.js             # Scene setup, render loop, camera
│   ├── renderer.js         # WebGL renderer + post-processing
│   ├── lighting.js         # Ambient, directional, IBL
│   ├── camera-rig.js       # Orbit, fly, follow modes
│   ├── world-builder.js    # Builds rooms/meshes from data.js
│   ├── GLTFModel.js        # GLB loader + animation mixer
│   ├── character.js        # Resident character (model + state)
│   ├── furniture.js        # PBR furniture mesh factory
│   ├── materials.js        # Shared PBR materials
│   ├── spectator-hud.js    # Needs bars, event feed, info panel
│   ├── live-client.js      # WS bridge (contract-v1 → scene)
│   └── offline-sim.js      # Fallback: sim-core.js compatible
├── assets/
│   ├── characters/         # GLB models (Mixamo, CC0)
│   │   / (empty — populated by user or build script)
│   └── textures/           # PBR texture maps
├── assets.js               # Character/object manifest
├── data.js                 # World definition (rooms, props, NPCs)
└── package.json            # Three.js + dependencies
```

## Rendering Pipeline

### 1. Physically-Based Materials

```js
// materials.js — shared PBR materials
const wood = new THREE.MeshStandardMaterial({
  color: 0x8B6B4A,
  roughness: 0.7,
  metalness: 0.0,
  map: loadTexture('wood_albedo.jpg'),
  normalMap: loadTexture('wood_normal.jpg'),
  roughnessMap: loadTexture('wood_rough.jpg'),
});

const fabric = new THREE.MeshStandardMaterial({
  color: 0x4a6b8a,
  roughness: 0.9,
  metalness: 0.0,
  sheen: 1.0,
  sheenRoughness: 0.5,
});

const metal = new THREE.MeshStandardMaterial({
  color: 0xaaaaaa,
  roughness: 0.3,
  metalness: 0.9,
});
```

### 2. Soft Lighting

```js
// lighting.js — physically-based lighting
const ambient = new THREE.AmbientLight(0xffffff, 0.3);
const hemi = new THREE.HemisphereLight(0x87CEEB, 0x2d5a3d, 0.4);

const sun = new THREE.DirectionalLight(0xffeedd, 1.2);
sun.castShadow = true;
sun.shadow.mapSize.set(2048, 2048);
sun.shadow.bias = -0.0001;
sun.shadow.normalBias = 0.05;

// Image-based lighting for reflections
const pmrem = new THREE.PMREMGenerator(renderer);
scene.environment = pmrem.fromEquirectangular(hdrTexture).texture;
```

### 3. Post-Processing

```js
// renderer.js — effect chain
import { EffectComposer } from 'three/addons/postprocessing/EffectComposer.js';
import { RenderPass } from 'three/addons/postprocessing/RenderPass.js';
import { SSAOPass } from 'three/addons/postprocessing/SSAOPass.js';
import { UnrealBloomPass } from 'three/addons/postprocessing/UnrealBloomPass.js';
import { OutputPass } from 'three/addons/postprocessing/OutputPass.js';

const composer = new EffectComposer(renderer);
composer.addPass(new RenderPass(scene, camera));
composer.addPass(ssaoPass);        // ambient occlusion
composer.addPass(bloomPass);        // subtle glow
composer.addPass(outputPass);       // tone mapping + color space
```

### 4. GLB Character Loading

```js
// GLTFModel.js — async GLB load + animation
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';

class GLTFModel {
  constructor(url) {
    this.url = url;
    this.mixer = null;
    this.animations = {};
  }

  async load() {
    const gltf = await new GLTFLoader().loadAsync(this.url);
    this.scene = gltf.scene;
    this.mixer = new THREE.AnimationMixer(this.scene);
    for (const clip of gltf.animations) {
      this.animations[clip.name] = this.mixer.clipAction(clip);
    }
    return this;
  }

  play(name, loop = true) {
    const action = this.animations[name];
    if (action) {
      action.reset();
      action.setLoop(loop ? THREE.LoopRepeat : THREE.LoopOnce);
      action.play();
    }
  }

  update(delta) {
    if (this.mixer) this.mixer.update(delta);
  }
}
```

### 5. Character State Machine

```
IDLE → WALK → ARRIVE → USE → IDLE
              ↓
         CONVERSE → IDLE
              ↓
           SIT → IDLE
```

Each character tracks:
- `position` (Vector3, smoothed toward target)
- `state` (idle/walk/use/sit/converse)
- `needBubble` (floating icon when critical need)
- `moodColor` (subtle tint based on emotional state)

### 6. Live Client (WebSocket Bridge)

```js
// live-client.js — same protocol, richer mapping
function connect({ onState, onStatus }) {
  const ws = new WebSocket(resolveWsUrl());

  ws.onmessage = (ev) => {
    const msg = JSON.parse(ev.data);
    switch (msg.type) {
      case 'snapshot':
        scene.setAvatars(mapContractAvatars(msg.avatars));
        break;
      case 'tick':
        scene.applyEvents(mapContractEvents(msg.events));
        scene.updateNeeds(msg.you);
        break;
      case 'you':
        scene.updateAvatarNeeds(msg.avatar_id, msg.you.needs);
        break;
    }
  };
}
```

### 7. Offline Fallback

When no server is running, the viewer falls back to `sim-core.js` (existing
offline simulation). The offline-sim module maps the existing sim-core world
state to the same scene structure:

```js
// offline-sim.js
function mapOfflineState(state) {
  return {
    avatars: state.avatars.map(av => ({
      id: av.id, name: av.name, trait: av.trait,
      position: { x: av.px, y: av.py },
      state: av.state,
      needs: { focus: av.focus, stress: av.stress, ... },
    })),
  };
}
```

## Spectator HUD

```
┌─────────────────────────────────────────────────────┐
│  NeuroLift World Engine          ● LIVE  tick: 42   │
│                                                     │
│  ┌───────────┐  ┌──────────────────────────────┐   │
│  │ Event Feed│  │  Clicked: StayAlert          │   │
│  │           │  │  Trait: Sustained Attention   │   │
│  │ TASK_START│  │                              │   │
│  │ FOCUS_DRIFT│ │  ████████░░ Focus     0.82  │   │
│  │ STRESS_SPIKE││  ██████░░░░ Hunger    0.55  │   │
│  │           │  │  ████░░░░░░ Energy    0.38  │   │
│  └───────────┘  │  █████████░ Social    0.91  │   │
│                 └──────────────────────────────┘   │
│  1: Free Cam  2: Orbit  3: Follow  4: Click inspect │
└─────────────────────────────────────────────────────┘
```

## Performance Targets

- **60 FPS** on mid-range GPUs (GTX 1060 / RX 580 equivalent)
- **10-20 visible characters** with full animation
- **< 16ms frame time** for rendering + animation updates
- **Instanced rendering** for repeated furniture (chairs, plants)

## Asset Pipeline

1. **Characters:** Mixamo FBX → Blender (retarget) → glTF export → .glb
2. **Textures:** CC0 textures (Poly Haven) → resize to 1K/2K → compress
3. **HDR environment:** Poly Haven HDR → PMREM for IBL

## Implementation Order

1. **Phase 1:** Scene + renderer + PBR materials + soft lighting
2. **Phase 2:** Camera rig + spectator HUD + room meshes
3. **Phase 3:** GLB character load + walk/idle animation + state machine
4. **Phase 4:** Live client (WS bridge) + contract-v1 mapping
5. **Phase 5:** Offline fallback (sim-core compatibility)
6. **Phase 6:** Post-processing (SSAO, bloom, tone mapping)
7. **Phase 7:** Polish (particles, sound, weather)
