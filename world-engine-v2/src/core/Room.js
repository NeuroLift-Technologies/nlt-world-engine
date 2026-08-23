import { SimObject } from './Object.js';
import { OBJECT_FX } from '../data/objects.js';

export class Room {
  constructor(name, wh=[10,10]){
    this.name = name;
    this.dimensions = [...wh]; // [w,h]
    this.objects = []; // SimObject[]
    this.sims = [];
    this.house = null;
  }
  getName(){ return this.name; }
  getObjects(){ return [...this.objects]; }
  getDimensions(){ return [...this.dimensions]; }
  getHouse(){ return this.house; }
  getSims(){ return [...this.sims]; }

  changeHouse(newHouse){
    this.house = newHouse;
    for(const s of this.sims) newHouse.placeSim(s);
  }
  placeSim(sim){
    if (this.sims.includes(sim)) return;
    sim.current_house(this.house);
    sim.current_room(this);
    this.sims.push(sim);
  }
  removeSim(sim){
    const i = this.sims.indexOf(sim);
    if (i>=0) this.sims.splice(i,1);
  }
  objectInside(obj){
    return this.objects.includes(obj);
  }
  check_position([x,y]){
    const [w,h] = this.dimensions;
    if (x<0 || x>=w || y<0 || y>=h) return false;
    for(const o of this.objects){
      const [ox,oy]=o.getCoordinates();
      if (ox===x && oy===y) return false;
    }
    return true;
  }
  add_object(object){
    if (this.objectInside(object)) return false;
    let [x,y]=object.getCoordinates();
    const [w,h]=this.dimensions;
    if (x>=w || x<0){
      x = x<0 ? 0 : w-1;
      object.changeCoordinates([x, y]);
    }
    if (y>=h || y<0){
      y = y<0 ? 0 : h-1;
      object.changeCoordinates([x,y]);
    }
    this.objects.push(object);
    object.setRoom(this);
    object.setHouse(this.getHouse());
    return true;
  }
  place_object(objName, coordinates){
    if (this.check_position(coordinates)){
      const fx = OBJECT_FX[objName];
      if (!fx) return false;
      const no = new SimObject(objName, fx, coordinates);
      this.add_object(no);
      return true;
    } else {
      const offs=[[0,1],[1,0],[0,-1],[-1,0]];
      for(const [dx,dy] of offs){
        const p=[coordinates[0]+dx, coordinates[1]+dy];
        if (this.check_position(p)){
          const fx = OBJECT_FX[objName];
          if (!fx) return false;
          const no = new SimObject(objName, fx, p);
          this.add_object(no);
          return true;
        }
      }
    }
    return false;
  }
  move_object(object, coordinates){
    if (this.check_position(coordinates)){
      object.changeCoordinates(coordinates);
      return true;
    } else {
      const offs=[[0,1],[1,0],[0,-1],[-1,0]];
      for(const [dx,dy] of offs){
        const p=[coordinates[0]+dx, coordinates[1]+dy];
        if (this.check_position(p)){
          object.changeCoordinates(p);
          return true;
        }
      }
    }
    return false;
  }
  delete_object(pos){
    const obj = this.objects[pos];
    this.objects.splice(pos,1);
    return obj;
  }
  mutate_objects(){
    const _mut_add_prob = 30;
    const _mut_delete_prob = 10;
    const _mut_move_prob = 40;
    // iterate copy index-wise but splice aware
    for(let i=0;i<this.objects.length;i++){
      const r = Math.floor(Math.random()*101);
      if (r <= _mut_delete_prob){
        this.delete_object(i);
        i--; // adjust
      } else if (r <= _mut_delete_prob + _mut_move_prob){
        const newPos = [Math.floor(Math.random()*this.dimensions[0]), Math.floor(Math.random()*this.dimensions[1])];
        this.move_object(this.objects[i], newPos);
      }
    }
    if (Math.floor(Math.random()*101) <= _mut_add_prob){
      const keys=Object.keys(OBJECT_FX);
      const name = keys[Math.floor(Math.random()*keys.length)];
      const newPos = [Math.floor(Math.random()*this.dimensions[0]), Math.floor(Math.random()*this.dimensions[1])];
      this.place_object(name, newPos);
    }
  }

  closestToSim(coordinates, sim){
    let best=null; let bestD=Infinity;
    const [sx,sy]=coordinates;
    for(const o of this.objects){
      const [ox,oy]=o.getCoordinates();
      const d = Math.hypot(sx-ox, sy-oy);
      if (d < bestD){ bestD=d; best=o; }
    }
    return best;
  }
  interactwithObjects(sim){
    for(const o of this.objects) sim.interactWith(o);
  }
  toJSON(){
    return {
      name: this.name,
      dimensions: { x:this.dimensions[0], y:this.dimensions[1]},
      objects: this.objects.map(o=>o.toJSON())
    };
  }
}
