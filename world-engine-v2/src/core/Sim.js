export class Sim {
  constructor(name){
    this.name = name;
    this.needs = [5,5,5,5,5,5]; // hunger, hygiene, bladder, energy, social, fun
    this.house = null;
    this.room = null;
    this.target = null; // SimObject
    this.coordinates = [0,0];
    this.navPath = []; // array of [x,y]
    // recoverable burnout state (replaces death)
    this.isBurntOut = false;
    this.burnoutTicks = 0;
    this.burnoutCount = 0;
    this.burnoutReason = null; // 'hunger' | 'energy' | null
  }

  getName(){ return this.name; }
  getNeeds(){ return [...this.needs]; }
  getHouse(){ return this.house; }
  getRoom(){ return this.room; }
  getCoordinates(){ return [...this.coordinates]; }
  getTarget(){ return this.target; }
  hasTarget(){ return this.target !== null; }
  setTarget(o){ this.target = o; }
  hasNavPath(){ return this.navPath.length > 0; }
  setNavPath(path){ this.navPath = path.map(p=>[...p]); }
  changeCoordinates(xy){ this.coordinates = [...xy]; }

  // was isDead() — now recoverable burnout
  checkBurnoutTrigger(){
    if (this.needs[0] === 0) return 'hunger';
    if (this.needs[3] === 0) return 'energy';
    return null;
  }
  isDead(){ // keep alias for compat, delegates to burnout
    return this.isBurntOut;
  }
  enterBurnout(reason){
    if (this.isBurntOut) return;
    this.isBurntOut = true;
    this.burnoutTicks = 0;
    this.burnoutCount++;
    this.burnoutReason = reason;
    this.target = null;
    this.navPath = [];
  }
  tickBurnoutRecovery({ recoveryTicks = 8, minEnergy = 3, minHunger = 2 } = {}){
    if (!this.isBurntOut) return false;
    this.burnoutTicks++;
    // recover while stalled — mirrors spec: energy +1, hunger +0.5 per tick
    this.needs[3] = Math.min(10, this.needs[3] + 1);
    this.needs[0] = Math.min(10, this.needs[0] + 0.5);
    // keep other needs from going negative too fast — light slip
    // (hide in recovery so HUD doesn't flicker wildly)
    if (this.burnoutTicks >= recoveryTicks && this.needs[3] >= minEnergy && this.needs[0] >= minHunger){
      this.isBurntOut = false;
      this.burnoutTicks = 0;
      this.burnoutReason = null;
      return true; // recovered this tick
    }
    return false;
  }

  alterNeed(idx, amt){
    this.needs[idx] += amt;
    if (this.needs[idx] < 0) this.needs[idx] = 0;
    if (this.needs[idx] > 10) this.needs[idx] = 10;
  }
  printNeeds(){ return this.needs.join(' '); }

  current_room(newRoom){
    if (this.house === null){
      if (this.room) this.room.removeSim(this);
      this.room = newRoom;
    } else {
      if (this.house.roomInside(newRoom)){
        if (this.room) this.room.removeSim(this);
        this.room = newRoom;
      } else {
        // not in same house — fail silently (keep old room)
      }
    }
  }
  current_house(newHouse){
    if (this.house !== newHouse && this.house !== null){
      this.house.removeSim(this);
      if (this.room) this.room.removeSim(this);
      this.house = newHouse;
    } else if (this.house !== newHouse && this.house === null){
      this.house = newHouse;
    } else {
      this.house = newHouse;
    }
  }

  interactWith(object){
    if (this.room === null){
      if (!object.inRoom()){
        for(let i=0;i<this.needs.length;i++){
          let v = this.needs[i] + object.getNeedValue(i);
          this.needs[i] = v > 10 ? 10 : v;
          if (this.needs[i] < 0) this.needs[i] = 0;
        }
      }
    } else {
      if (this.room.objectInside(object)){
        for(let i=0;i<this.needs.length;i++){
          let v = this.needs[i] + object.getNeedValue(i);
          this.needs[i] = v > 10 ? 10 : v;
          if (this.needs[i] < 0) this.needs[i] = 0;
        }
      }
    }
  }

  atTarget(debug=false){
    if (!this.hasTarget()) return;
    const [sx,sy] = this.coordinates;
    const [tx,ty] = this.target.getCoordinates();
    if (sx !== tx || sy !== ty) return;
    this.interactWith(this.target);
    this.target = null;
    this.navPath = [];
  }

  goToNext(){
    if (!this.hasTarget()) return;
    if (!this.hasNavPath()) return;
    const next = this.navPath.shift();
    this.changeCoordinates(next);
  }

  closestObject(){
    if (!this.room) return null;
    return this.room.closestToSim(this.coordinates, this);
  }
}
