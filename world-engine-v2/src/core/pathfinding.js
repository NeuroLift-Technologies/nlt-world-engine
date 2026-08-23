function tupKey([x,y]){ return `${x},${y}`; }
function inSet(set, e){
  return set.some(([x,y])=> x===e[0] && y===e[1]);
}

function getNeighbors(node, bounds){
  const [x,y]=node;
  const [w,h]=bounds;
  const out=[];
  if (y-1 >=0) out.push([x, y-1]);
  if (x-1 >=0) out.push([x-1, y]);
  if (x+1 < w) out.push([x+1, y]);
  if (y+1 < h) out.push([x, y+1]);
  return out;
}

/**
 * BFS path from start to end avoiding xs.
 * @param {[number,number]} start
 * @param {[number,number]} end
 * @param {[number,number]} boundary [w,h]
 * @param {[number,number][]} xs blocked cells
 * @returns {[number,number][]}
 */
export function getBFSPath(start, end, boundary, xs){
  const startKey = tupKey(start);
  const endKey = tupKey(end);
  const queue = [ { xy:[...start], parentKey: "" } ];
  const visited = new Set([startKey]);
  const famTree = new Map(); // childKey -> parent xy

  let matchKey = "";

  while(queue.length>0){
    const cur = queue.shift();
    const curKey = tupKey(cur.xy);
    const neighbors = getNeighbors(cur.xy, boundary);
    for(const nb of neighbors){
      const nbKey = tupKey(nb);
      if (!famTree.has(nbKey)) famTree.set(nbKey, cur.xy);
      if (!visited.has(nbKey) && !inSet(xs, nb)){
        visited.add(nbKey);
        queue.push({ xy: nb, parentKey: curKey });
      }
      if (nbKey === endKey){
        matchKey = nbKey;
        break;
      }
    }
    if (matchKey) break;
  }
  if (!matchKey) return [];
  // trace back
  const back=[ [...end] ];
  let curKey = matchKey;
  while(curKey !== startKey){
    const p = famTree.get(curKey);
    if (!p) break; // no path
    back.unshift([...p]);
    curKey = tupKey(p);
  }
  return back;
}

export function objDist(sim, obj){
  const [ox,oy]=obj.getCoordinates();
  const [sx,sy]=sim.getCoordinates();
  return Math.hypot(sx-ox, sy-oy);
}
export function objDistManhattan(sim, obj){
  const [ox,oy]=obj.getCoordinates();
  const [sx,sy]=sim.getCoordinates();
  return Math.abs(sx-ox)+Math.abs(sy-oy);
}
