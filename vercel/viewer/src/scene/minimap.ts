// Island map in the spirit of Observer/Minimap.cs: terrain from the same height grid,
// buildings by kind, the camera's target, and agents the feed places in the open world.
import { TERRAIN_SEGMENTS, WATER, WORLD } from '../world/geometry';
import { kindColour } from '../world/settlement';
import type { WorldView } from './world';

export class Minimap {
  private base: HTMLCanvasElement;
  private ctx: CanvasRenderingContext2D;
  constructor(private canvas: HTMLCanvasElement, private world: WorldView) {
    this.ctx = canvas.getContext('2d')!;
    const dpr = Math.min(window.devicePixelRatio || 1, 2);
    canvas.width = 168 * dpr;
    canvas.height = 168 * dpr;
    this.base = this.paintTerrain();
    canvas.addEventListener('click', (e) => {
      const r = canvas.getBoundingClientRect();
      const x = ((e.clientX - r.left) / r.width - 0.5) * WORLD;
      const z = ((e.clientY - r.top) / r.height - 0.5) * WORLD;
      world.followId = null;
      world.target.set(x, Math.max(world.target.y, 4), z);
      world.updateCamera();
    });
  }

  private paintTerrain(): HTMLCanvasElement {
    const n = TERRAIN_SEGMENTS + 1;
    const c = document.createElement('canvas');
    c.width = n; c.height = n;
    const g = c.getContext('2d')!;
    const img = g.createImageData(n, n);
    for (let j = 0; j < n; j++)
      for (let i = 0; i < n; i++) {
        const h = this.world.grid[j * n + i];
        const k = (j * n + i) * 4;
        let r: number, gg: number, b: number;
        if (h < WATER) { const d = Math.min(1, -h / 9); r = 30 - d * 14; gg = 84 - d * 34; b = 98 - d * 30; }
        else if (h < WATER + 1.5) { r = 190; gg = 172; b = 132; }
        else { const t = Math.min(1, h / 24); r = 84 + t * 60; gg = 112 + t * 34; b = 66 + t * 48; }
        img.data.set([r, gg, b, 255], k);
      }
    g.putImageData(img, 0, 0);
    return c;
  }

  draw(agents: { x: number; z: number; selected: boolean; role: string }[]) {
    const { ctx, canvas } = this;
    const W = canvas.width, toPx = (v: number) => (v / WORLD + 0.5) * W;
    ctx.imageSmoothingEnabled = true;
    ctx.drawImage(this.base, 0, 0, W, W);
    for (const b of this.world.buildings) {
      ctx.fillStyle = '#' + kindColour(b.kind).toString(16).padStart(6, '0');
      ctx.fillRect(toPx(b.group.position.x) - 2, toPx(b.group.position.z) - 2, 4, 4);
    }
    // Camera: where it looks, and which way.
    const t = this.world.target, cam = this.world.camera.position;
    ctx.strokeStyle = 'rgba(255,255,255,0.85)';
    ctx.lineWidth = 1.5 * (W / 168);
    ctx.beginPath();
    ctx.moveTo(toPx(cam.x), toPx(cam.z));
    ctx.lineTo(toPx(t.x), toPx(t.z));
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(toPx(t.x), toPx(t.z), 4 * (W / 168), 0, Math.PI * 2);
    ctx.stroke();
    for (const a of agents) {
      ctx.beginPath();
      ctx.arc(toPx(a.x), toPx(a.z), (a.selected ? 4.5 : 3.2) * (W / 168), 0, Math.PI * 2);
      ctx.fillStyle = a.role === 'aide' ? '#9cc7e4' : '#ffffff';
      ctx.fill();
      ctx.strokeStyle = a.selected ? '#56b4e9' : '#0e1116';
      ctx.lineWidth = 1.5 * (W / 168);
      ctx.stroke();
    }
    ctx.fillStyle = 'rgba(230,237,243,0.85)';
    ctx.font = `${10 * (W / 168)}px system-ui`;
    ctx.fillText('N ↑', W - 26 * (W / 168), 13 * (W / 168));
  }
}
