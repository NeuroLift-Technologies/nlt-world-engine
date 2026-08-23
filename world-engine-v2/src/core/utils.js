export function tupKey([x,y]) { return `${x},${y}`; }
export function vecAvg(arr){ return arr.length ? arr.reduce((a,b)=>a+b,0)/arr.length : 0; }
export function randPos([w,h]){ return [Math.floor(Math.random()*w), Math.floor(Math.random()*h)]; }
export function randVal([a,b]){ return Math.floor(Math.random()*(b-a+1))+a; }
export function clamp(v, lo, hi){ return Math.max(lo, Math.min(hi, v)); }
