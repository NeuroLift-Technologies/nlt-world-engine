import { getBFSPath, objDist } from './pathfinding.js';

export const DEFAULT_RATE = [5,10,5,7,15,15];
export const DEFAULT_RANKING = [0,2,3,1,4,5];
export const DEFAULT_THRESHOLD = 3;
export const DEFAULT_MAX_TICKS = 100;

export function calculateFitness(sim){
  // recoverable burnout: not auto 0, penalize per burnout
  const needs = sim.getNeeds();
  let avg = needs.reduce((a,b)=>a+b,0) / 60;
  if (sim.burnoutCount) {
    avg -= sim.burnoutCount * 0.05;
  }
  if (avg < 0) avg = 0;
  if (avg > 1) avg = 1;
  return avg;
}

export function findNeedObj(sim, needIndex){
  const curRoom = sim.getRoom();
  if (!curRoom) return;
  const roomObjs = curRoom.getObjects();
  const beneficial = roomObjs.filter(o=> o.getNeedValue(needIndex) > 0);
  if (beneficial.length===0) return;
  let best = beneficial[0];
  let bestD = objDist(sim, best);
  for(let i=1;i<beneficial.length;i++){
    const d = objDist(sim, beneficial[i]);
    if (d < bestD){ bestD=d; best=beneficial[i]; }
  }
  sim.setTarget(best);
}

/**
 * Single-tick advance — recoverable burnout aware.
 * Mirrors simulation.cpp but burnout stalls instead of break.
 */
export function stepTick(sim, tick, rate, threshold, needsRanking, recoveryTicks=8){
  // 0) burnout recovery branch — stall, heal, skip everything else
  if (sim.isBurntOut){
    const recovered = sim.tickBurnoutRecovery({ recoveryTicks });
    return { burntOut: true, recovered, tick };
  }
  // 0b) check if we just hit burnout trigger
  const reason = sim.checkBurnoutTrigger();
  if (reason){
    sim.enterBurnout(reason);
    return { burntOut: true, entered: true, reason, tick };
  }

  // 1) set path if needed
  if (sim.hasTarget() && !sim.hasNavPath()){
    const roomObjs = sim.getRoom().getObjects();
    const objCoords = roomObjs.map(o=> o.getCoordinates());
    const path = getBFSPath(sim.getCoordinates(), sim.getTarget().getCoordinates(), sim.getRoom().getDimensions(), objCoords);
    sim.setNavPath(path);
  }

  // 1.2 go to target
  sim.goToNext();

  // 2) at target -> interact
  sim.atTarget(false);

  // 3) apply needs decrement (skip tick 0 like C++)
  if (tick !== 0){
    for(let n=0; n<rate.length; n++){
      if ((tick+1) % rate[n] === 0) sim.alterNeed(n, -1);
    }
  }

  // check burnout again after decay — if we just hit 0, next tick will enter burnout
  // (we let it enter next tick so HUD can show the dip, but also handle immediate)
  const postReason = sim.checkBurnoutTrigger();
  if (postReason && !sim.isBurntOut){
    // don't immediately enter, let viewer show 0 for a frame — but we can enter now to stall next move
    // unify: enter now
    sim.enterBurnout(postReason);
    return { burntOut: true, entered: true, reason: postReason, tick };
  }

  // 4) if has target, ignore other needs
  if (sim.hasTarget()) return { burntOut:false, tick };

  // 5) find next need to fulfill
  for(const needIndex of needsRanking){
    const needs = sim.getNeeds();
    if (needs[needIndex] < threshold){
      findNeedObj(sim, needIndex);
      if (sim.hasTarget()) break; // take first that finds target (like original loop but with break)
    }
  }
  return { burntOut:false, tick };
}

// Legacy full-run (like C++ simulate) but with recoverable burnout — runs to maxTicks
export function simulate(sim, maxTicks=DEFAULT_MAX_TICKS, rate=DEFAULT_RATE, threshold=DEFAULT_THRESHOLD, needsRanking=DEFAULT_RANKING, recoveryTicks=8){
  for(let tick=0; tick<maxTicks; tick++){
    stepTick(sim, tick, rate, threshold, needsRanking, recoveryTicks);
  }
  const f = calculateFitness(sim);
  // keep house fitness in sync if needed
  if (sim.getHouse()) sim.getHouse().setFitness(f);
  return f;
}
