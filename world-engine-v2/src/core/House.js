export class House {
  constructor(name, id=-1){
    this.name=name;
    this.houseId=id;
    this.fitness=0;
    this.rooms=[];
    this.sims=[];
  }
  getName(){ return this.name; }
  getRooms(){ return [...this.rooms]; }
  getFitness(){ return this.fitness; }
  getId(){ return this.houseId; }
  setFitness(f){ this.fitness=f; }
  setName(n){ this.name=n; }
  setId(i){ this.houseId=i; }

  add_room(room){
    if (this.roomInside(room)) return;
    this.rooms.push(room);
    room.changeHouse(this);
  }
  roomInside(room){ return this.rooms.includes(room); }

  placeSim(sim){
    if (this.sims.includes(sim)) return;
    this.sims.push(sim);
    sim.current_house(this);
  }
  removeSim(sim){
    const i=this.sims.indexOf(sim);
    if(i>=0) this.sims.splice(i,1);
  }
  getObjectCt(){
    const m={};
    for(const r of this.rooms){
      for(const o of r.getObjects()){
        m[o.getName()] = (m[o.getName()]||0)+1;
      }
    }
    return m;
  }
  toJSON(){
    return {
      house: this.name,
      id: this.houseId,
      fitness: this.fitness,
      rooms: this.rooms.map(r=>r.toJSON())
    };
  }
}
