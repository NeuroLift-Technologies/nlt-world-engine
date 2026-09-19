// GLTFModel.js — async GLB loader + per-character animation instances.
//
// A GLTFModel is a *template*: load the model once (e.g. the three.js soldier,
// a free animated human with a Mixamo rig). `instantiate()` then clones the
// scene graph (cloning each skeleton so every resident animates independently)
// and creates a fresh AnimationMixer, returning a standalone GLTFInstance.
// This keeps a single network download while giving each resident its own walk
// phase — the previous shared-scene approach only parented the model under the
// last character to attach it.
import * as THREE from 'three';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import { clone } from 'three/addons/utils/SkeletonUtils.js';

export class GLTFModel {
  constructor(url) {
    this.url = url;
    this.gltf = null;     // parsed glTF (template; never added directly to the scene)
    this.clips = [];      // shared animation clips
    this.loaded = false;
  }

  async load() {
    try {
      const gltf = await new GLTFLoader().loadAsync(this.url);
      this.gltf = gltf;
      this.clips = gltf.animations || [];
      this.loaded = true;
      console.log(`[GLTFModel] loaded ${this.url} (${this.clips.length} clips)`);
      return this;
    } catch (e) {
      console.warn(`[GLTFModel] failed to load ${this.url}`, e);
      return null;
    }
  }

  /**
   * Build an independent runtime instance: a cloned skeleton (so animation
   * state/mixers don't cross talk between residents) + its own mixer + actions.
   * Shared geometry and materials are reused to keep memory low.
   */
  instantiate() {
    if (!this.loaded || !this.gltf) return null;
    const scene = clone(this.gltf.scene);
    const mixer = new THREE.AnimationMixer(scene);
    const actions = {};
    for (const clip of this.clips) {
      actions[clip.name] = mixer.clipAction(clip);
    }
    return new GLTFInstance(scene, mixer, actions);
  }

  dispose() {
    this.gltf?.scene?.traverse((c) => {
      if (c.isMesh) { c.geometry?.dispose?.(); c.material?.dispose?.(); }
    });
    this.clips = [];
    this.loaded = false;
  }
}

export class GLTFInstance {
  constructor(scene, mixer, actions) {
    this.scene = scene;
    this.mixer = mixer;
    this.actions = actions;          // { clipName: AnimationAction }
    this.current = null;            // currently fading-in / playing action
  }

  // Resolve a logical name (e.g. 'walk'/'idle') to an action, tolerating
  // Mixamo-style prefixes like 'Character_Walk'. Falls back to substring.
  _resolve(name) {
    if (this.actions[name]) return this.actions[name];
    const lower = name.toLowerCase();
    const key = Object.keys(this.actions).find(
      (k) => k.toLowerCase() === lower || k.toLowerCase().includes(lower),
    );
    return key ? this.actions[key] : null;
  }

  play(name, fadeDuration = 0.3) {
    const next = this._resolve(name);
    if (!next || next === this.current) return;
    if (this.current) this.current.fadeOut(fadeDuration);
    if (!next.isRunning()) {
      // Random start phase so residents don't walk in lockstep.
      const dur = next.clip?.duration || 1;
      next.time = Math.random() * dur;
    }
    next.fadeIn(fadeDuration).play();
    this.current = next;
  }

  update(delta) {
    this.mixer?.update(delta);
  }

  dispose() {
    this.mixer?.stopAllAction();
    this.mixer?.uncacheRoot(this.scene);
    this.mixer = null;
  }
}

// CharacterManifest — optional per-character GLB override map.
// Empty by default: all residents share CONFIG.characters.model. To give a
// resident its own model, add: '<character-id>': '<cdn glb url>'
export const CHARACTER_MANIFEST = {
  // 'resident-1': 'https://cdn.example.com/avatar-1.glb',
};

export function getCharacterModelUrl(characterId) {
  return CHARACTER_MANIFEST[characterId] || null;
}
