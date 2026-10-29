import type { AgentState, SceneEntity } from './trace/types.js';

type Point = { x: number; y: number; z: number };
type Building = { x: number; z: number; w: number; d: number; h: number; label: string; color: string };

const BUILDINGS: Building[] = [
  { x: -18, z: -12, w: 10, d: 8, h: 7, label: 'HOME', color: '#d9c7a0' },
  { x: 0, z: -18, w: 13, d: 9, h: 10, label: 'WORK', color: '#b7c8d8' },
  { x: 18, z: -8, w: 11, d: 10, h: 8, label: 'SCHOOL', color: '#d8b6a8' },
  { x: -15, z: 12, w: 12, d: 10, h: 9, label: 'COMMUNITY', color: '#c4d2ae' },
  { x: 12, z: 15, w: 14, d: 10, h: 6, label: 'SHOP', color: '#d8c0d8' },
];

const TREES: Point[] = [
  { x: -34, y: 0, z: -28 }, { x: -28, y: 0, z: -5 }, { x: -33, y: 0, z: 15 },
  { x: -26, y: 0, z: 30 }, { x: -6, y: 0, z: 29 }, { x: 10, y: 0, z: 31 },
  { x: 29, y: 0, z: 26 }, { x: 34, y: 0, z: 10 }, { x: 31, y: 0, z: -14 },
  { x: 25, y: 0, z: -29 }, { x: 4, y: 0, z: -32 }, { x: -17, y: 0, z: -30 },
  { x: -38, y: 0, z: 0 }, { x: 39, y: 0, z: -2 }, { x: 2, y: 0, z: 39 },
];

export class World3DView {
  private canvas: HTMLCanvasElement;
  private ctx: CanvasRenderingContext2D;
  private agents = new Map<string, AgentState>();
  private entities = new Map<string, SceneEntity[]>();
  private dpr = 1;
  private zoom = 1;
  private panX = 0;
  private panY = 0;
  private dragging = false;
  private lastX = 0;
  private lastY = 0;

  constructor(canvas: HTMLCanvasElement) {
    this.canvas = canvas;
    const ctx = canvas.getContext('2d');
    if (!ctx) throw new Error('2D canvas context unavailable for world scene');
    this.ctx = ctx;
    canvas.addEventListener('wheel', (event) => {
      event.preventDefault();
      this.zoom = Math.max(0.55, Math.min(2.1, this.zoom * (event.deltaY < 0 ? 1.08 : 0.92)));
      this.render();
    }, { passive: false });
    canvas.addEventListener('pointerdown', (event) => {
      this.dragging = true; this.lastX = event.clientX; this.lastY = event.clientY;
      canvas.setPointerCapture(event.pointerId);
    });
    canvas.addEventListener('pointermove', (event) => {
      if (!this.dragging) return;
      this.panX += event.clientX - this.lastX; this.panY += event.clientY - this.lastY;
      this.lastX = event.clientX; this.lastY = event.clientY; this.render();
    });
    canvas.addEventListener('pointerup', () => { this.dragging = false; });
    canvas.addEventListener('pointercancel', () => { this.dragging = false; });
    window.addEventListener('resize', () => this.render());
    this.render();
  }

  update(agents: Map<string, AgentState>, entities: Map<string, SceneEntity[]>) {
    this.agents = new Map(agents);
    this.entities = new Map(entities);
    this.render();
  }

  private project(x: number, y: number, z: number): { x: number; y: number } {
    const w = this.canvas.clientWidth || 800;
    const h = this.canvas.clientHeight || 480;
    const scale = Math.min(w / 94, h / 76) * this.zoom;
    return {
      x: w / 2 + this.panX + (x - z) * scale * 0.62,
      y: h / 2 + this.panY + (x + z) * scale * 0.31 - y * scale * 0.78,
    };
  }

  private polygon(points: Point[], fill: string, stroke?: string) {
    const ctx = this.ctx;
    ctx.beginPath();
    points.forEach((p, i) => {
      const q = this.project(p.x, p.y, p.z);
      if (i === 0) ctx.moveTo(q.x, q.y); else ctx.lineTo(q.x, q.y);
    });
    ctx.closePath();
    ctx.fillStyle = fill;
    ctx.fill();
    if (stroke) { ctx.strokeStyle = stroke; ctx.lineWidth = 1; ctx.stroke(); }
  }

  private line(points: Point[], color: string, width: number) {
    const ctx = this.ctx;
    ctx.beginPath();
    points.forEach((p, i) => {
      const q = this.project(p.x, p.y, p.z);
      if (i === 0) ctx.moveTo(q.x, q.y); else ctx.lineTo(q.x, q.y);
    });
    ctx.strokeStyle = color; ctx.lineWidth = width; ctx.lineCap = 'round'; ctx.stroke();
  }

  private drawBuilding(b: Building) {
    const x0 = b.x - b.w / 2, x1 = b.x + b.w / 2;
    const z0 = b.z - b.d / 2, z1 = b.z + b.d / 2;
    const wall = b.color;
    this.polygon([{x:x1,y:0,z:z0},{x:x1,y:b.h,z:z0},{x:x1,y:b.h,z:z1},{x:x1,y:0,z:z1}], '#9b9a91', '#66665f');
    this.polygon([{x:x0,y:0,z:z1},{x:x1,y:0,z:z1},{x:x1,y:b.h,z:z1},{x:x0,y:b.h,z:z1}], '#b4b1a6', '#66665f');
    this.polygon([{x:x0,y:0,z:z0},{x:x1,y:0,z:z0},{x:x1,y:0,z:z1},{x:x0,y:0,z:z1}], '#b9b39e', '#8b8778');
    this.polygon([{x:x0,y:0,z:z0},{x:x1,y:0,z:z0},{x:x1,y:b.h,z:z0},{x:x0,y:b.h,z:z0}], wall, '#66665f');
    this.polygon([{x:x0,y:b.h,z:z0},{x:x1,y:b.h,z:z0},{x:x1,y:b.h,z:z1},{x:x0,y:b.h,z:z1}], '#e5e2d7', '#77766e');
    const center = this.project(b.x, b.h + 1.5, b.z);
    this.ctx.fillStyle = '#25313a'; this.ctx.font = '700 10px system-ui'; this.ctx.textAlign = 'center';
    this.ctx.fillText(b.label, center.x, center.y);
  }

  private drawTree(p: Point, i: number) {
    const base = this.project(p.x, 0, p.z);
    const height = 18 + (i % 3) * 4;
    this.ctx.fillStyle = '#76614a';
    this.ctx.fillRect(base.x - 2, base.y - height * 0.36, 4, height * 0.42);
    const crown = this.project(p.x, height, p.z);
    this.ctx.beginPath(); this.ctx.arc(crown.x, crown.y, 10 + (i % 3) * 2, 0, Math.PI * 2);
    this.ctx.fillStyle = i % 2 ? '#487a50' : '#5c8a58'; this.ctx.fill();
    this.ctx.strokeStyle = '#355c3a'; this.ctx.lineWidth = 1; this.ctx.stroke();
  }

  private drawAgent(agent: AgentState, index: number) {
    const p = agent.position;
    const base = this.project(p.x, p.y, p.z);
    const height = 17;
    this.ctx.strokeStyle = '#263238'; this.ctx.lineWidth = 1.5;
    this.ctx.beginPath(); this.ctx.moveTo(base.x, base.y - 4); this.ctx.lineTo(base.x - 3, base.y + 2);
    this.ctx.moveTo(base.x, base.y - 4); this.ctx.lineTo(base.x + 4, base.y + 2);
    this.ctx.moveTo(base.x, base.y - 4); this.ctx.lineTo(base.x - 3, base.y + 7);
    this.ctx.moveTo(base.x, base.y - 4); this.ctx.lineTo(base.x + 4, base.y + 7); this.ctx.stroke();
    this.ctx.fillStyle = ['#f4d35e', '#65c3ba', '#f28f3b', '#9b8de5'][index % 4];
    this.ctx.fillRect(base.x - 3, base.y - height, 7, 12);
    this.ctx.beginPath(); this.ctx.arc(base.x, base.y - height - 4, 4, 0, Math.PI * 2); this.ctx.fill();
    this.ctx.strokeStyle = '#23313a'; this.ctx.lineWidth = 1; this.ctx.stroke();
    this.ctx.font = '700 10px system-ui'; this.ctx.textAlign = 'center';
    const label = this.ctx.measureText(agent.agentId).width + 10;
    this.ctx.fillStyle = 'rgba(255,255,255,0.9)';
    this.ctx.fillRect(base.x - label / 2, base.y - height - 22, label, 13);
    this.ctx.fillStyle = '#17242b'; this.ctx.fillText(agent.agentId, base.x, base.y - height - 12);
  }

  render() {
    const ctx = this.ctx;
    const w = this.canvas.clientWidth || 800, h = this.canvas.clientHeight || 480;
    this.dpr = window.devicePixelRatio || 1;
    this.canvas.width = Math.round(w * this.dpr); this.canvas.height = Math.round(h * this.dpr);
    ctx.setTransform(this.dpr, 0, 0, this.dpr, 0, 0);
    const sky = ctx.createLinearGradient(0, 0, 0, h);
    sky.addColorStop(0, '#c8dce8'); sky.addColorStop(0.55, '#e8ede2'); sky.addColorStop(1, '#b4cba2');
    ctx.fillStyle = sky; ctx.fillRect(0, 0, w, h);

    // Ground plane: stylized isometric 3D projection, not authoritative geometry.
    this.polygon([{x:-48,y:0,z:-42},{x:48,y:0,z:-42},{x:48,y:0,z:42},{x:-48,y:0,z:42}], '#8fb17d', '#6e9565');
    // Soft terrain bands and winding paths.
    this.line([{x:-44,y:0.15,z:5},{x:-25,y:0.15,z:7},{x:-8,y:0.15,z:3},{x:8,y:0.15,z:0},{x:28,y:0.15,z:4},{x:44,y:0.15,z:9}], '#d6c9a6', 11);
    this.line([{x:-3,y:0.16,z:-39},{x:-1,y:0.16,z:-20},{x:2,y:0.16,z:0},{x:0,y:0.16,z:20},{x:3,y:0.16,z:39}], '#d6c9a6', 9);
    this.line([{x:-40,y:0.2,z:-20},{x:-25,y:0.2,z:-18},{x:-10,y:0.2,z:-20},{x:0,y:0.2,z:-22}], '#d6c9a6', 6);
    // Small plaza.
    this.polygon([{x:-8,y:0.3,z:-8},{x:8,y:0.3,z:-8},{x:8,y:0.3,z:8},{x:-8,y:0.3,z:8}], '#c9c5b4', '#a7a392');
    // Water pond at the settlement edge.
    this.polygon([{x:23,y:0.25,z:-36},{x:39,y:0.25,z:-34},{x:41,y:0.25,z:-25},{x:27,y:0.25,z:-22}], '#77b9ce', '#4e9db8');
    // Draw back-to-front to give the scene depth.
    [...TREES].sort((a,b) => a.z - b.z).forEach((tree, i) => this.drawTree(tree, i));
    [...BUILDINGS].sort((a,b) => a.z - b.z).forEach((building) => this.drawBuilding(building));
    for (const [sceneId, list] of this.entities) {
      for (const ent of list) {
        const base = this.project(ent.position.x, ent.position.y, ent.position.z);
        ctx.fillStyle = '#f6f3df'; ctx.fillRect(base.x - 4, base.y - 8, 8, 8);
        ctx.strokeStyle = '#45545a'; ctx.strokeRect(base.x - 4, base.y - 8, 8, 8);
        ctx.font = '9px system-ui'; ctx.textAlign = 'center'; ctx.fillStyle = '#23313a';
        ctx.fillText(ent.id, base.x, base.y - 11);
      }
    }
    [...this.agents.values()].sort((a,b) => a.position.z - b.position.z).forEach((agent, index) => this.drawAgent(agent, index));
    ctx.fillStyle = 'rgba(255,255,255,0.88)'; ctx.fillRect(12, 12, 246, 44);
    ctx.fillStyle = '#22333a'; ctx.font = '700 12px system-ui'; ctx.textAlign = 'left';
    ctx.fillText('NLT WORLD ENGINE · OBSERVER', 22, 30);
    ctx.font = '11px system-ui'; ctx.fillStyle = '#52666c';
    ctx.fillText(`${BUILDINGS.length} structures · ${TREES.length} trees · ${this.agents.size} trace agents`, 22, 46);
    ctx.fillStyle = 'rgba(255,255,255,0.82)'; ctx.fillRect(w - 162, 12, 150, 28);
    ctx.fillStyle = '#31474d'; ctx.font = '10px system-ui'; ctx.textAlign = 'center';
    ctx.fillText('Drag to pan · Scroll to zoom', w - 87, 30);
  }
}
