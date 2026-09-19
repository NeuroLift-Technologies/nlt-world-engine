// CharacterManager.js — spawn, update, and manage all AI residents
import * as THREE from 'three';
import { Character } from './Character.js';
import { GLTFModel } from './GLTFModel.js';

export class CharacterManager {
  constructor(scene, heightField, characterCfg = {}) {
    this.scene = scene;
    this.heightField = heightField;
    this.characters = new Map(); // id -> Character
    this.sharedModel = null; // shared GLB template (loaded once, cloned per resident)
    this.characterCfg = characterCfg; // { model, height } from CONFIG.characters
    this.socialProximityRadius = 3.0; // meters - when characters are this close, they socialize
  }

  async loadSharedModel(url) {
    if (!url) return;
    const model = new GLTFModel(url);
    await model.load();
    if (model.loaded) {
      this.sharedModel = model;
    }
  }

  addCharacter(id, name, position) {
    const character = new Character(id, name, position, this.heightField, this.sharedModel, this.characterCfg);
    this.scene.add(character.group);
    this.characters.set(id, character);
    return character;
  }

  removeCharacter(id) {
    const character = this.characters.get(id);
    if (character) {
      this.scene.remove(character.group);
      character.dispose();
      this.characters.delete(id);
    }
  }

  setCharacterTarget(id, x, z) {
    const character = this.characters.get(id);
    if (character) {
      character.setTarget(x, z);
    }
  }

  // Set a social target for a character (another character to interact with)
  setSocialTarget(id, targetId) {
    const character = this.characters.get(id);
    const target = this.characters.get(targetId);
    if (character && target && targetId !== id) {
      character.socialState = 'chat';
      character.socialTarget = target.position.clone();
      target.socialState = 'chat';
      target.socialTarget = character.position.clone();
    }
  }

  clearSocialTargets() {
    for (const character of this.characters.values()) {
      character.socialState = 'idle';
      character.socialTarget = null;
    }
  }

  update(delta) {
    // Social interaction: detect proximity and trigger behaviors
    const characterIds = Array.from(this.characters.keys());
    for (let i = 0; i < characterIds.length; i++) {
      const id1 = characterIds[i];
      const char1 = this.characters.get(id1);
      if (!char1 || char1.socialState !== 'idle') continue;

      for (let j = i + 1; j < characterIds.length; j++) {
        const id2 = characterIds[j];
        const char2 = this.characters.get(id2);
        if (!char2 || char2.socialState !== 'idle') continue;

        const dist = char1.position.distanceTo(char2.position);
        if (dist < this.socialProximityRadius) {
          // Characters are close enough to socialize
          this.setSocialTarget(id1, id2);
          this.setSocialTarget(id2, id1);
        }
      }
    }

    for (const character of this.characters.values()) {
      character.update(delta);
    }
  }

  getCharacter(id) {
    return this.characters.get(id);
  }

  getCharacterCount() {
    return this.characters.size;
  }

  dispose() {
    for (const [id, character] of this.characters) {
      this.scene.remove(character.group);
      character.dispose();
    }
    this.characters.clear();
  }
}
