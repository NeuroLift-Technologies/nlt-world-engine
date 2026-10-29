import { parseTrace } from './trace/parser.js';
import { reduce } from './trace/reducer.js';
import type { ParsedTrace } from './trace/types.js';

const DEFAULT_TRACE = `{"schemaVersion":"nlt.observer-trace.v1","runId":"run-demo-001","engineCommit":"abc1234","godotVersion":"4.7.2","startTime":"2026-10-02T07:00:00Z","agentRoster":["agent_alfa","agent_bravo"],"cadenceHz":10}
{"type":"tick","tick":0,"agentId":"agent_alfa","scene":{"id":"plaza","kind":"open_world"},"position":{"x":0,"y":0,"z":0},"velocity":{"x":1,"y":0,"z":0}}
{"type":"tick","tick":0,"agentId":"agent_bravo","scene":{"id":"plaza","kind":"open_world"},"position":{"x":5,"y":0,"z":2},"velocity":{"x":0,"y":0,"z":0}}
{"type":"perception_sent","tick":0,"agentId":"agent_alfa"}
{"type":"intent","messageId":"m1","agentId":"agent_alfa","observedTick":0,"verb":"approach","targetId":"well_1"}
{"type":"result","intentMessageId":"m1","status":"accepted","stage":"accepted"}
{"type":"tick","tick":10,"agentId":"agent_alfa","scene":{"id":"plaza","kind":"open_world"},"position":{"x":10,"y":0,"z":0},"velocity":{"x":1,"y":0,"z":0}}
{"type":"tick","tick":10,"agentId":"agent_bravo","scene":{"id":"plaza","kind":"open_world"},"position":{"x":5,"y":0,"z":2},"velocity":{"x":0,"y":0,"z":0}}
{"type":"tick","tick":20,"agentId":"agent_alfa","scene":{"id":"office_1","kind":"interior"},"position":{"x":2,"y":0,"z":1},"velocity":{"x":0,"y":0,"z":0}}
{"type":"scene_transition","agentId":"agent_alfa","from":"plaza","to":"office_1","tick":20}
{"type":"intent","messageId":"m2","agentId":"agent_bravo","observedTick":10,"verb":"sit","targetId":"chair_3","ticksBehind":2,"decisionMs":420}
{"type":"result","intentMessageId":"m2","status":"rejected","reason":"occupied","stage":"governance","governanceCode":"G-04"}
{"type":"decision_failed","agentId":"agent_alfa","tick":30,"httpStatus":504,"error":"gateway timeout"}
{"type":"tick","tick":30,"agentId":"agent_alfa","scene":{"id":"office_1","kind":"interior"},"position":{"x":2,"y":0,"z":1},"velocity":{"x":0,"y":0,"z":0}}
{"type":"tick","tick":30,"agentId":"agent_bravo","scene":{"id":"plaza","kind":"open_world"},"position":{"x":5,"y":0,"z":2},"velocity":{"x":0,"y":0,"z":0}}
`;

const SHAPES = ['circle', 'square', 'triangle', 'diamond'] as const;
function agentShapeIndex(agentId: string): number {
  let h = 0;
  for (let i = 0; i < agentId.length; i++) h = (h * 31 + agentId.charCodeAt(i)) | 0;
  return Math.abs(h) % SHAPES.length;
}

function drawMarker(ctx: CanvasRenderingContext2D, x: number, y: number, size: number, shape: string, label: string) {
  const r = size / 2;
  ctx.save();
  ctx.translate(x, y);
  ctx.beginPath();
  switch (shape) {
    case 'circle':
      ctx.arc(0, 0, r, 0, Math.PI * 2);
      break;
    case 'square':
      ctx.rect(-r, -r, size, size);
      break;
    case 'triangle':
      ctx.moveTo(0, -r);
      ctx.lineTo(r, r);
      ctx.lineTo(-r, r);
      ctx.closePath();
      break;
    case 'diamond':
      ctx.moveTo(0, -r);
      ctx.lineTo(r, 0);
      ctx.lineTo(0, r);
      ctx.lineTo(-r, 0);
      ctx.closePath();
      break;
  }
  ctx.fillStyle = '#e6edf3';
  ctx.fill();
  ctx.strokeStyle = '#56b4e9';
  ctx.lineWidth = 1.8;
  ctx.stroke();
  ctx.restore();

  ctx.save();
  ctx.font = 'bold 11px -apple-system, sans-serif';
  ctx.textAlign = 'center';
  ctx.textBaseline = 'bottom';
  ctx.fillStyle = '#e6edf3';
  ctx.fillText(label, x, y - r - 4);
  ctx.restore();
}

function drawTrail(ctx: CanvasRenderingContext2D, pts: { x: number; z: number }[], mx: (x: number) => number, mz: (z: number) => number) {
  if (pts.length < 2) return;
  ctx.beginPath();
  ctx.moveTo(mx(pts[0].x), mz(pts[0].z));
  for (let i = 1; i < pts.length; i++) ctx.lineTo(mx(pts[i].x), mz(pts[i].z));
  ctx.strokeStyle = '#74838f';
  ctx.lineWidth = 1.2;
  ctx.globalAlpha = 0.6;
  ctx.stroke();
  ctx.globalAlpha = 1;
}

export class ViewerApp {
  private trace: ParsedTrace | null = null;
  private ticks: Array<{ tick: number; agentId: string; position: { x: number; y: number; z: number } }> = [];
  private minTick = 0;
  private maxTick = 0;
  private currentTick = 0;
  private isPlaying = false;
  private speed = 1;
  private lastFrame = 0;
  private rafId: number | null = null;
  private canvas: HTMLCanvasElement;
  private ctx: CanvasRenderingContext2D;
  private dpr = 1;

  constructor() {
    this.canvas = document.getElementById('plot') as HTMLCanvasElement;
    this.ctx = this.canvas.getContext('2d')!;
    this.bindEvents();
    this.setupLevelButtons();
    this.loadText(DEFAULT_TRACE);
    window.addEventListener('resize', () => this.resizeCanvas());
    this.resizeCanvas();
    this.drawMinimap();
  }

  private resizeCanvas() {
    const rect = this.canvas.getBoundingClientRect();
    this.dpr = window.devicePixelRatio || 1;
    this.canvas.width = rect.width * this.dpr;
    this.canvas.height = rect.height * this.dpr;
    this.ctx.scale(this.dpr, this.dpr);
    this.render();
  }

  private async loadText(text: string) {
    let parsed: ParsedTrace;
    try {
      parsed = parseTrace(text);
    } catch (err) {
      console.error(err);
      return;
    }
    this.trace = parsed;
    this.buildTickIndex();
    this.refreshHeaderMeta();
    this.buildEnvironmentHeader();
    this.currentTick = this.minTick;
    this.updateScrubberBounds();
    this.render();
  }

  private buildTickIndex() {
    this.ticks = [];
    for (const r of this.trace!.records) {
      if (r.kind === 'tick') {
        this.ticks.push({ tick: r.tick, agentId: r.agentId, position: r.position });
      }
    }
    const tickValues = this.ticks.map((t) => t.tick);
    this.minTick = tickValues.length ? Math.min(...tickValues) : 0;
    this.maxTick = tickValues.length ? Math.max(...tickValues) : 0;
    this.currentTick = this.minTick;
  }

  private refreshHeaderMeta() {
    if (!this.trace) return;
    const h = this.trace.header;
    const el = document.getElementById('shell-meta')!;
    el.textContent = `schema: ${h.schemaVersion} · run: ${h.runId} · godot: ${h.godotVersion} · cadence: ${h.cadenceHz} Hz`;
    const fb = document.getElementById('fixture-badge')!;
    fb.textContent = h.runId;
  }

  private buildEnvironmentHeader() {
    const el = document.getElementById('env-header')!;
    el.innerHTML = '';
    const doc = this.trace ? reduce(this.trace.records, this.currentTick) : null;
    const chips = [
      { glyph: 'hexagon', color: '#56b4e9', claim: 'Persistent World', value: `seed ${this.trace?.header.runId?.slice(-4) || '0000'}` },
      { glyph: 'circle', color: '#009e73', claim: 'Multi-Agent', value: `${this.trace?.header.agentRoster.length || 0} agent${(this.trace?.header.agentRoster.length || 0) === 1 ? '' : 's'}` },
      { glyph: 'square', color: '#0072b2', claim: 'Real-Time Physics', value: 'Jolt' },
      { glyph: 'diamond', color: '#cc79a7', claim: 'Scenario', value: doc?.agents.size ? Array.from(doc.agents.values())[0].scene.id : '-' },
    ];
    for (const c of chips) {
      const chip = document.createElement('div');
      chip.className = 'env-chip';
      chip.innerHTML = `
        <div class="env-chip-glyph ${c.glyph}" style="color:${c.color}"></div>
        <div class="env-chip-text">
          <div class="env-chip-claim">${c.claim}</div>
          <div class="env-chip-value">${c.value}</div>
        </div>
      `;
      el.appendChild(chip);
    }
  }

  private setupLevelButtons() {
    const btns = document.querySelectorAll('.level-btn');
    btns.forEach(btn => {
      btn.addEventListener('click', () => {
        btns.forEach(b => b.classList.remove('active'));
        btn.classList.add('active');
      });
    });
  }

  private render() {
    if (!this.trace) return;
    const rect = this.canvas.getBoundingClientRect();
    const ctx = this.ctx;
    ctx.clearRect(0, 0, rect.width, rect.height);
    
    const slice = reduce(this.trace.records, this.currentTick);
    this.renderViewport(ctx, rect, slice);
    this.renderAvatarPanel(slice);
    this.renderEvents(slice);
    this.renderLog(slice);
    this.updateTickDisplay();
    this.drawMinimap();
  }

  private renderViewport(ctx: CanvasRenderingContext2D, rect: DOMRect, slice: any) {
    const mx = (x: number) => rect.width / 2 + x * 12;
    const mz = (z: number) => rect.height / 2 + z * 12;
    
    // Grid
    ctx.strokeStyle = 'rgba(47, 59, 73, 0.4)';
    ctx.lineWidth = 1;
    ctx.beginPath();
    for (let x = -20; x <= 20; x += 2) {
      ctx.moveTo(mx(x), 0);
      ctx.lineTo(mx(x), rect.height);
    }
    for (let z = -20; z <= 20; z += 2) {
      ctx.moveTo(0, mz(z));
      ctx.lineTo(rect.width, mz(z));
    }
    ctx.stroke();
    
    // Trails
    for (const agentId of this.trace!.header.agentRoster) {
      const pts = this.ticks.filter(t => t.agentId === agentId && t.tick <= this.currentTick).map(t => ({x: t.position.x, z: t.position.z}));
      drawTrail(ctx, pts, mx, mz);
    }
    
    // Agents
    for (const [agentId, agent] of slice.agents) {
      const shape = SHAPES[agentShapeIndex(agentId)];
      drawMarker(ctx, mx(agent.position.x), mz(agent.position.z), 12, shape, agentId.split('_')[1] || agentId);
    }
  }

  private renderAvatarPanel(slice: any) {
    const body = document.getElementById('avatar-body')!;
    const subtitle = document.getElementById('avatar-subtitle')!;
    body.innerHTML = '';
    if (slice.agents.size === 0) {
      body.innerHTML = '<div style="color: var(--text-dim); font-size: 12px;">Waiting for a state feed.</div>';
      subtitle.textContent = 'no document yet';
      return;
    }
    const agent = Array.from(slice.agents.values())[0];
    subtitle.textContent = agent.agentId;
    
    const state = document.createElement('div');
    state.innerHTML = `
      <div class="chip" style="color: #009e73;">
        <div class="chip-glyph circle" style="color: #009e73;"></div>
        <span>Calm</span>
      </div>
      <div style="font-size: 12px; color: var(--text-dim); margin-top: 6px;">Settled and oriented. Duration: steady.</div>
    `;
    body.appendChild(state);
    
    const section = document.createElement('div');
    section.innerHTML = `
      <div style="font-size: 11px; text-transform: uppercase; letter-spacing: 0.1em; color: var(--text-muted); margin: 8px 0 6px;">Working on</div>
      <div style="font-size: 12px;"><span style="color: var(--text-muted);">Goal:</span> <span style="color: var(--text-dim);">Explore the habitat</span></div>
      <div style="font-size: 12px; margin-top: 4px;"><span style="color: var(--text-muted);">Now:</span> Observe surroundings</div>
    `;
    body.appendChild(section);
  }

  private renderEvents(slice: any) {
    const body = document.getElementById('events-body')!;
    body.innerHTML = '';
    if (slice.transitions.length === 0 && slice.failures.length === 0) {
      body.innerHTML = '<div style="color: var(--text-dim); font-size: 12px;">No recent events.</div>';
      return;
    }
    for (const t of slice.transitions) {
      const div = document.createElement('div');
      div.className = 'log-entry';
      div.innerHTML = `<div class="log-line1"><span class="log-tick">t${t.tick}</span><span style="color: var(--text);">Scene transition</span></div><div style="font-size: 11px; color: var(--text-dim); font-family: var(--mono);">${t.from} → ${t.to}</div>`;
      body.appendChild(div);
    }
    for (const f of slice.failures) {
      const div = document.createElement('div');
      div.className = 'log-entry';
      div.innerHTML = `<div class="log-line1"><span class="log-tick">t${f.tick}</span><span style="color: var(--alert);">Decision failed</span></div><div style="font-size: 11px; color: var(--text-dim);">${f.error || 'timeout'}</div>`;
      body.appendChild(div);
    }
  }

  private renderLog(slice: any) {
    const list = document.getElementById('log-list')!;
    const count = document.getElementById('log-count')!;
    list.innerHTML = '';
    const entries = [];
    for (const [agentId, intent] of slice.intents) {
      const res = slice.results.get(agentId);
      entries.push({ intent, result: res });
    }
    count.textContent = `${entries.length} entr${entries.length === 1 ? 'y' : 'ies'}`;
    if (entries.length === 0) {
      list.innerHTML = '<div style="color: var(--text-dim); font-size: 12px;">No intents or results.</div>';
      return;
    }
    for (const e of entries) {
      const div = document.createElement('div');
      div.className = 'log-entry';
      div.innerHTML = `
        <div class="log-line1">
          <span class="log-tick">t${e.intent.observedTick}</span>
          <span class="log-verb">${e.intent.verb}</span>
          ${e.intent.targetId ? `<span class="log-target">${e.intent.targetId}</span>` : ''}
          <span style="color: ${e.result?.status === 'accepted' ? '#009e73' : '#d55e00'};">${e.result?.status || 'pending'}</span>
        </div>
        <div class="log-meta">
          <span>${e.intent.agentId}</span>
          ${e.result?.stage ? `<span>stage:${e.result.stage}</span>` : ''}
          ${e.result?.reason ? `<span>reason:${e.result.reason}</span>` : ''}
        </div>
      `;
      list.appendChild(div);
    }
  }

  private updateTickDisplay() {
    document.getElementById('tick-value')!.textContent = String(this.currentTick);
    document.getElementById('tick-range')!.textContent = String(this.maxTick);
    const scr = document.getElementById('scrubber') as HTMLInputElement;
    scr.value = String(this.currentTick);
  }

  private bindEvents() {
    document.getElementById('btn-play')!.addEventListener('click', () => this.setPlaying(true));
    document.getElementById('btn-pause')!.addEventListener('click', () => this.setPlaying(false));
    document.getElementById('btn-step-back')!.addEventListener('click', () => this.seek(this.currentTick - 1));
    document.getElementById('btn-step-fwd')!.addEventListener('click', () => this.seek(this.currentTick + 1));
    document.getElementById('btn-live')!.addEventListener('click', () => { this.seek(this.maxTick); this.setPlaying(false); });
    document.getElementById('btn-replay')!.addEventListener('click', () => { this.seek(this.minTick); this.setPlaying(false); });
    const speed = document.getElementById('sel-speed') as HTMLSelectElement;
    speed.addEventListener('change', () => { this.speed = Number(speed.value || 1); });
    const scrub = document.getElementById('scrubber') as HTMLInputElement;
    scrub.addEventListener('input', () => this.seek(Number(scrub.value)));
    
    const tl = document.getElementById('timeline');
    tl?.addEventListener('click', (e: MouseEvent) => {
      const rect = tl.getBoundingClientRect();
      const x = e.clientX - rect.left;
      const min = this.minTick;
      const max = this.maxTick;
      const span = max - min || 1;
      const t = min + (x / rect.width) * span;
      this.seek(Math.round(t));
    });

    const fileInput = document.createElement('input');
    fileInput.type = 'file';
    fileInput.accept = '.jsonl,.json,.txt';
    fileInput.hidden = true;
    document.body.appendChild(fileInput);
    fileInput.addEventListener('change', (e) => {
      const f = (e.target as HTMLInputElement).files?.[0];
      if (!f) return;
      f.text().then((text) => this.loadText(text));
    });
    const openBtn = document.createElement('button');
    openBtn.type = 'button';
    openBtn.textContent = 'Open trace…';
    openBtn.className = 'tp-button';
    openBtn.addEventListener('click', () => fileInput.click());
    document.querySelector('.transport')!.insertBefore(openBtn, document.getElementById('btn-play'));

    window.addEventListener('keydown', (e: KeyboardEvent) => {
      const active = document.activeElement as HTMLElement | null;
      const isInput = active && (active.tagName === 'INPUT' || active.tagName === 'SELECT');
      if (e.key === ' ' && !isInput) {
        e.preventDefault();
        this.setPlaying(!this.isPlaying);
      }
      if (e.key === 'ArrowLeft' && !isInput) { e.preventDefault(); this.seek(this.currentTick - 1); }
      if (e.key === 'ArrowRight' && !isInput) { e.preventDefault(); this.seek(this.currentTick + 1); }
    });
  }

  private setPlaying(playing: boolean) {
    this.isPlaying = playing;
    document.getElementById('btn-play')!.hidden = playing;
    document.getElementById('btn-pause')!.hidden = !playing;
    if (playing) {
      this.lastFrame = performance.now();
      this.loop();
    } else {
      if (this.rafId) cancelAnimationFrame(this.rafId);
      this.rafId = null;
    }
  }

  private loop = () => {
    if (!this.isPlaying) { this.rafId = null; return; }
    const now = performance.now();
    let dt = now - this.lastFrame;
    this.lastFrame = now;
    const interval = 100 / this.speed;
    let adv = 0;
    while (dt >= interval && adv < 10) {
      this.seek(this.currentTick + 1);
      dt -= interval;
      adv++;
    }
    if (this.currentTick >= this.maxTick) {
      this.setPlaying(false);
    } else {
      this.rafId = requestAnimationFrame(this.loop);
    }
  };

  private seek(tick: number) {
    const t = Math.min(Math.max(Math.round(tick), this.minTick), this.maxTick);
    if (t === this.currentTick) return;
    this.currentTick = t;
    (document.getElementById('scrubber') as HTMLInputElement).value = String(t);
    this.buildEnvironmentHeader();
    this.render();
  }

  private updateScrubberBounds() {
    const scr = document.getElementById('scrubber') as HTMLInputElement;
    scr.min = String(this.minTick);
    scr.max = String(this.maxTick);
  }

  private drawMinimap() {
    const canvas = document.getElementById('minimap') as HTMLCanvasElement;
    const ctx = canvas.getContext('2d')!;
    ctx.fillStyle = '#0d1f26';
    ctx.fillRect(0, 0, 192, 214);
    ctx.strokeStyle = '#2f3b49';
    ctx.strokeRect(0, 0, 192, 214);
    
    // Simple grid
    ctx.strokeStyle = 'rgba(47, 59, 73, 0.5)';
    ctx.beginPath();
    for (let i = 0; i < 192; i += 16) { ctx.moveTo(i, 0); ctx.lineTo(i, 214); }
    for (let i = 0; i < 214; i += 16) { ctx.moveTo(0, i); ctx.lineTo(192, i); }
    ctx.stroke();
    
    if (!this.trace) return;
    const slice = reduce(this.trace.records, this.currentTick);
    for (const [agentId, agent] of slice.agents) {
      const x = 96 + agent.position.x * 6;
      const y = 107 + agent.position.z * 6;
      ctx.fillStyle = '#56b4e9';
      ctx.beginPath();
      ctx.arc(x, y, 3, 0, Math.PI * 2);
      ctx.fill();
    }
  }
}

declare global {
  interface Window { ViewerApp: typeof ViewerApp; }
}

if (document.readyState === 'loading') {
  document.addEventListener('DOMContentLoaded', () => {
    (window as any).ViewerApp = ViewerApp;
    new ViewerApp();
  });
} else {
  (window as any).ViewerApp = ViewerApp;
  new ViewerApp();
}
