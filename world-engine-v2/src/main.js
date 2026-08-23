import * as THREE from 'three';
import { createScene } from './viewer/scene.js';
import { HouseMesh } from './viewer/houseMesh.js';
import { SimAvatar } from './viewer/simAvatar.js';
import { House } from './core/House.js';
import { Room } from './core/Room.js';
import { Sim } from './core/Sim.js';
import { SimObject } from './core/Object.js';
import { OBJECT_FX, NEED_LABELS } from './data/objects.js';
import { randPos } from './core/utils.js';
import { stepTick, calculateFitness, DEFAULT_RATE, DEFAULT_RANKING, DEFAULT_THRESHOLD, DEFAULT_MAX_TICKS } from './core/simulation.js';

// --- DOM ---
const canvas = document.getElementById('c');
const needsEl = document.getElementById('needs');
const lblTick = document.getElementById('lblTick');
const lblMax = document.getElementById('lblMax');
const lblFit = document.getElementById('lblFit');
const lblBurn = document.getElementById('lblBurn');
const lblStatus = document.getElementById('lblStatus');
const lblTarget = document.getElementById('lblTarget');
const lblSpeed = document.getElementById('lblSpeed');
const lblRecovery = document.getElementById('lblRecovery');
const logEl = document.getElementById('log');
const btnPlay = document.getElementById('btnPlay');
const btnStep = document.getElementById('btnStep');
const btnReset = document.getElementById('btnReset');
const btnRandom = document.getElementById('btnRandom');
const rngSpeed = document.getElementById('rngSpeed');
const rngRecovery = document.getElementById('rngRecovery');

lblMax.textContent = String(DEFAULT_MAX_TICKS);

// --- three ---
const { renderer, scene, camera, resize, setTarget } = createScene(canvas);
const houseMesh = new HouseMesh(scene);
const simAvatar = new SimAvatar(scene);

// needs HUD
const needRows = [];
function buildNeedsHUD(){
  needsEl.innerHTML='';
  needRows.length=0;
  NEED_LABELS.forEach((label, i)=>{
    const name=document.createElement('div');
    name.textContent=label; name.className='small mono'; name.style.textTransform='capitalize';
    const bar=document.createElement('div'); bar.className='bar';
    const fill=document.createElement('i'); bar.appendChild(fill);
    const val=document.createElement('div'); val.className='mono small'; val.style.textAlign='right';
    needsEl.append(name, bar, val);
    needRows.push({ bar, fill, val });
  });
}
buildNeedsHUD();
function updateNeedsHUD(sim){
  const needs=sim.getNeeds();
  needs.forEach((v,i)=>{
    const r=needRows[i];
    const pct=Math.max(0, Math.min(100, v*10));
    r.fill.style.width=pct+'%';
    r.val.textContent=String(v.toFixed(1));
    r.bar.classList.toggle('crit', v<=2);
    r.bar.classList.toggle('warn', v>2 && v<=4);
    r.bar.classList.remove('warn','crit');
    if(v<=2) r.bar.classList.add('crit');
    else if(v<=4) r.bar.classList.add('warn');
  });
}

// --- sim world ---
let house, room, sim;
let tick=0;
let maxTicks=DEFAULT_MAX_TICKS;
let rate=[...DEFAULT_RATE];
let ranking=[...DEFAULT_RANKING];
let threshold=DEFAULT_THRESHOLD;
let playing=true;
let recoveryTicks=8;
let pendingInteractFlash=false;

function log(msg){
  const line=document.createElement('div');
  line.textContent=`[${String(tick).padStart(3,'0')}] ${msg}`;
  logEl.prepend(line);
  while(logEl.children.length>18) logEl.removeChild(logEl.lastChild);
}

function makeStarterHouse(){
  const h=new House("Rachel's House", 1);
  const r=new Room("Living Room", [10,10]);
  h.add_room(r);
  // a few canonical objects + some random like original test
  const starters=[
    ["fridge", [2,2]],
    ["toilet", [7,7]],
    ["bed", [8,1]],
    ["stove", [1,7]],
    ["tv", [5,5]],
    ["sink", [7,8]],
  ];
  for(const [name, xy] of starters){
    const fx=OBJECT_FX[name];
    if(!fx) continue;
    const o=new SimObject(name, fx, xy);
    r.add_object(o);
  }
  // add 2 random extras
  for(let i=0;i<2;i++){
    const keys=Object.keys(OBJECT_FX);
    const n=keys[Math.floor(Math.random()*keys.length)];
    const xy=randPos(r.getDimensions());
    r.place_object(n, xy);
  }
  return { h, r };
}

function makeRandomHouse(){
  const h=new House("House "+Math.floor(Math.random()*9000+1000), Math.floor(Math.random()*9000));
  const w= 8 + Math.floor(Math.random()*5);
  const h2= 8 + Math.floor(Math.random()*5);
  const r=new Room("Room", [w,h2]);
  h.add_room(r);
  const n= 5 + Math.floor(Math.random()*5);
  const keys=Object.keys(OBJECT_FX);
  for(let i=0;i<n;i++){
    const name=keys[Math.floor(Math.random()*keys.length)];
    const xy=randPos(r.getDimensions());
    r.place_object(name, xy);
  }
  return { h, r };
}

function spawnSimInRoom(r){
  const s=new Sim("Rachel");
  r.placeSim(s);
  // place at random free cell
  let tries=40;
  while(tries-->0){
    const xy=randPos(r.getDimensions());
    if(r.check_position(xy)){
      s.changeCoordinates(xy);
      break;
    }
  }
  if(r.check_position(s.getCoordinates())===false){
    // fallback to 0,0 search
    for(let x=0;x<r.getDimensions()[0];x++) for(let y=0;y<r.getDimensions()[1];y++){
      if(r.check_position([x,y])){ s.changeCoordinates([x,y]); break; }
    }
  }
  return s;
}

function resetWorld({ random=false }={}){
  const built = random ? makeRandomHouse() : makeStarterHouse();
  house=built.h; room=built.r;
  sim=spawnSimInRoom(room);
  tick=0;
  houseMesh.buildFromRoom(room);
  const [rw,rh]=room.getDimensions();
  setTarget(new THREE.Vector3(rw/2, 0, rh/2));
  simAvatar.setCell(sim.getCoordinates(), true);
  simAvatar.setBurnout(false);
  logEl.innerHTML='';
  log(random ? 'Randomized house' : 'Reset house');
  updateHUD();
  houseMesh.highlightTarget(null);
}

function updateHUD(){
  lblTick.textContent=String(tick);
  const fit=calculateFitness(sim);
  lblFit.textContent=fit.toFixed(3);
  lblBurn.textContent=String(sim.burnoutCount);
  const needs=sim.getNeeds();
  updateNeedsHUD(sim);
  const tgt=sim.getTarget();
  lblTarget.textContent = tgt ? `Target: ${tgt.getName()} @ ${tgt.getCoordinates().join(',')}  (need: ${NEED_LABELS[ranking.find(idx=> tgt.getNeedValue(idx)>0) ?? 0]})` : 'Target: —';
  if(sim.isBurntOut){
    const pct = Math.min(1, sim.burnoutTicks / recoveryTicks);
    lblStatus.innerHTML=`<span class="burnout">● BURNOUT (${sim.burnoutReason})</span> <span class="mono small">recovering ${sim.burnoutTicks}/${recoveryTicks} ${(pct*100).toFixed(0)}%</span>`;
    lblStatus.style.display='';
  } else {
    lblStatus.textContent='';
  }
  // status color
  if(tick>=maxTicks){
    lblStatus.innerHTML=`<span class="small">— run complete (fitness ${fit.toFixed(3)})</span>`;
  }
}

// one tick wrapper with visuals
function doTick(){
  if(tick>=maxTicks){
    playing=false;
    btnPlay.textContent='Play';
    return;
  }
  const beforeNeeds=[...sim.getNeeds()];
  const beforeTarget=sim.getTarget()?.getName() ?? null;
  const beforeBurnt=sim.isBurntOut;
  const beforePos=[...sim.getCoordinates()];

  const res=stepTick(sim, tick, rate, threshold, ranking, recoveryTicks);

  // visuals
  const afterPos=sim.getCoordinates();
  const moved = beforePos[0]!==afterPos[0] || beforePos[1]!==afterPos[1];
  if(moved) simAvatar.setCell(afterPos, false);

  // burnout visuals
  if(sim.isBurntOut){
    simAvatar.setBurnout(true, sim.burnoutTicks / recoveryTicks);
  } else if(beforeBurnt && !sim.isBurntOut){
    simAvatar.setBurnout(false);
    log(`Recovered from burnout (total ${sim.burnoutCount})`);
    simAvatar.flashInteract();
  } else {
    simAvatar.setBurnout(false);
  }

  if(res.entered){
    log(`Burnout entered: ${res.reason} → stalling ${recoveryTicks} ticks`);
  }

  // target changes
  const tgt=sim.getTarget();
  houseMesh.highlightTarget(tgt);
  if(tgt && beforeTarget!==tgt.getName()){
    log(`New target: ${tgt.getName()} for need < ${threshold}`);
    houseMesh.pulseObject(tgt);
  }
  // interaction detection — atTarget clears target after moving onto it
  if(beforeTarget && !tgt){
    // we just interacted
    simAvatar.flashInteract();
    houseMesh.pulseObject({ getName:()=>beforeTarget } ); // no-op if not found
    const nidx = ranking.find(i=> true); // not precise but log needs delta
    const delta = sim.getNeeds().map((v,i)=> (v - beforeNeeds[i]).toFixed(1));
    log(`Interacted with ${beforeTarget}  needs Δ [${delta.join(',')}]`);
  }

  tick++;
  updateHUD();
}

// controls
btnPlay.addEventListener('click', ()=>{
  playing=!playing;
  btnPlay.textContent=playing ? 'Pause' : 'Play';
});
btnStep.addEventListener('click', ()=>{
  playing=false; btnPlay.textContent='Play';
  doTick();
});
btnReset.addEventListener('click', ()=> resetWorld({ random:false }));
btnRandom.addEventListener('click', ()=> resetWorld({ random:true }));
rngSpeed.addEventListener('input', ()=>{
  lblSpeed.textContent=rngSpeed.value;
});
rngRecovery.addEventListener('input', ()=>{
  recoveryTicks=parseInt(rngRecovery.value,10);
  lblRecovery.textContent=String(recoveryTicks);
});
lblSpeed.textContent=rngSpeed.value;
lblRecovery.textContent=String(recoveryTicks);

// init
resetWorld({ random:false });

// loop
let last=performance.now();
let acc=0;
function frame(now){
  requestAnimationFrame(frame);
  resize();
  const dt=Math.min(0.05, (now-last)/1000);
  last=now;
  simAvatar.update(dt);
  renderer.render(scene, camera);

  if(!playing || tick>=maxTicks) return;
  const speed=parseInt(rngSpeed.value,10); // 0..10
  if(speed===0) return;
  // map speed to ticks per second: 1 -> 1.5 tps, 5 -> 8 tps, 10 -> 26 tps
  const tps = speed<=5 ? (0.9 + speed*1.4) : (8 + (speed-5)*3.6);
  acc += dt * tps;
  while(acc >= 1){
    acc -= 1;
    doTick();
    if(!playing || tick>=maxTicks) break;
  }
}
requestAnimationFrame(frame);

// expose for debug
window._sim={ get house(){return house}, get room(){return room}, get sim(){return sim}, get tick(){return tick}, resetWorld, doTick };
