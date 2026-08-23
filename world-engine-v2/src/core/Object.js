export class SimObject {
  constructor(name, effect, xy) {
    this.name = name;
    this.effect = [...effect]; // [hunger, hygiene, bladder, energy, social, fun]
    this.coordinates = [...xy]; // [x,y]
    this.house = null;
    this.room = null;
    this.hasRoom = false;
  }
  getName(){ return this.name; }
  getCoordinates(){ return [...this.coordinates]; }
  getEffect(){ return [...this.effect]; }
  getNeedValue(i){ return this.effect[i]; }
  inRoom(){ return this.hasRoom; }
  setRoom(r){ this.room = r; }
  setHouse(h){ this.house = h; }
  changeCoordinates(xy){ this.coordinates = [...xy]; }
  changeRoom(r){ this.room = r; this.hasRoom = true; }
  toJSON(){
    return {
      name: this.name,
      position: { x: this.coordinates[0], y: this.coordinates[1] },
      needFX: {
        hunger: this.effect[0], hygiene: this.effect[1], bladder: this.effect[2],
        energy: this.effect[3], social: this.effect[4], fun: this.effect[5]
      }
    };
  }
}
