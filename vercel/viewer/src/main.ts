import { parseTrace } from './trace/parser.js';
import { reduce } from './trace/reducer.js';
import { parseStateFeed } from './state/parser.js';
import type { ParsedTrace, SliceState } from './trace/types.js';
import type { ParsedStateFeed } from './state/types.js';

// Screenshot assets
const SCREENSHOTS: Record<string, string> = {
  'gp1-openworld-simple.png': new URL('./assets/screenshots/gp1-openworld-simple.png', import.meta.url).href,
  'home-interior-1.png': new URL('./assets/screenshots/home-interior-1.png', import.meta.url).href,
  'spectator-peek-inside.png': new URL('./assets/screenshots/spectator-peek-inside.png', import.meta.url).href,
};

// Default embedded trace (no network). Synthetic demo - clearly labeled.
const DEFAULT_TRACE = `{"schemaVersion":"nlt.observer-trace.v1","runId":"run-demo-001","engineCommit":"abc1234","godotVersion":"4.7.2","startTime":"2026-10-02T07:00:00Z","agentRoster":["agent_alfa","agent_bravo"],"cadenceHz":10}
{"type":"tick","tick":0,"agentId":"agent_alfa","scene":{"id":"plaza","kind":"open_world"},"position":{"x":0,"y":0,"z":0},"velocity":{"x":1,"y":0,"z":0}}
{"type":"tick","tick":0,"agentId":"agent_bravo","scene":{"id":"plaza","kind":"open_world"},"position":{"x":5,"y":0,"z":2},"velocity":{"x":0,"y":0,"z":0}}
{"type":"perception_sent","tick":0,"agentId":"agent_alfa"}
{"type":"intent","messageId":"m1","agentId":"agent_alfa","observedTick":0,"verb":"approach","targetId":"well_1"}
{"type":"result","intentMessageId":"m1","status":"accepted","stage":"accepted"}
{"type":"tick","tick":10,"agentId":"agent_alfa","scene":{"id":"plaza","kind":"open_world"},"position":{"x":10,"y":0,"z":0},"velocity":{"x":1,"y":0,"z":0}}
{"type":"tick","tick":20,"agentId":"agent_alfa","scene":{"id":"office_1","kind":"interior"},"position":{"x":2,"y":0,"z":1},"velocity":{"x":0,"y":0,"z":0}}
{"type":"scene_transition","agentId":"agent_alfa","from":"plaza","to":"office_1","tick":20}
{"type":"intent","messageId":"m2","agentId":"agent_bravo","observedTick":10,"verb":"sit","targetId":"chair_3"}
{"type":"result","intentMessageId":"m2","status":"rejected","reason":"occupied","stage":"governance","governanceCode":"G-04"}
{"type":"decision_failed","agentId":"agent_alfa","tick":30,"httpStatus":504,"error":"gateway timeout"}
{"type":"scene_entities","scene":"plaza","entities":[{"id":"well_1","kind":"well","position":{"x":12,"y":0,"z":0},"affordances":["approach","use"]}]}
{"type":"tick","tick":30,"agentId":"agent_alfa","scene":{"id":"office_1","kind":"interior"},"position":{"x":2,"y":0,"z":1},"velocity":{"x":0,"y":0,"z":0}}
{"type":"tick","tick":30,"agentId":"agent_bravo","scene":{"id":"plaza","kind":"open_world"},"position":{"x":5,"y":0,"z":2},"velocity":{"x":0,"y":0,"z":0}}
{"type":"weird_record","tick":99,"agentId":"nope","foo":"bar"}
`;

export class ViewerApp {
  private mode: 'trace' | 'snapshot' = 'trace';
  private trace: ParsedTrace | null = null;
  private snapshot: ParsedStateFeed | null = null;
  
  private ticks: Array<{ tick: number; agentId: string; position: { x: number; y: number; z: number } }> = [];
  private minTick = 0;
  private maxTick = 0;
  private currentTick = 0;
  
  private isPlaying = false;
  private speed = 1;
  private lastFrame = 0;
  private rafId: number | null = null;
  private tickIntervalMs = 100;
  
  private elements: Record<string, HTMLElement> = {};

  constructor() {
    this.bindElements();
    this.bindEvents();
    this.initScreenshot();
    this.updateProvenance();
    // Load default synthetic trace
    this.loadTraceText(DEFAULT_TRACE, true);
    window.addEventListener('keydown', (e) => this.handleKeydown(e));
  }

  private bindElements() {
    // Mode buttons
    document.getElementById('btn-mode-trace')?.addEventListener('click', () => this.setMode('trace'));
    document.getElementById('btn-mode-snapshot')?.addEventListener('click', () => this.setMode('snapshot'));
    
    // Load buttons
    document.getElementById('btn-load-trace')?.addEventListener('click', () => this.openTraceFile());
    document.getElementById('btn-load-snapshot')?.addEventListener('click', () => this.openSnapshotFile());
    
    // Screenshot selector
    document.getElementById('screenshot-select')?.addEventListener('change', (e) => {
      this.changeScreenshot((e.target as HTMLSelectElement).value);
    });
    
    // Transport
    document.getElementById('btn-play')?.addEventListener('click', () => this.setPlaying(true));
    document.getElementById('btn-pause')?.addEventListener('click', () => this.setPlaying(false));
    document.getElementById('btn-step-back')?.addEventListener('click', () => this.seek(this.currentTick - 1));
    document.getElementById('btn-step-fwd')?.addEventListener('click', () => this.seek(this.currentTick + 1));
    document.getElementById('sel-speed')?.addEventListener('change', (e) => {
      this.speed = Number((e.target as HTMLSelectElement).value || 1);
    });
    document.getElementById('scrubber')?.addEventListener('input', (e) => {
      this.seek(Number((e.target as HTMLInputElement).value));
    });
    
    // Timeline click
    document.getElementById('timeline')?.addEventListener('click', (e: MouseEvent) => {
      const tl = document.getElementById('timeline')!;
      const rect = tl.getBoundingClientRect();
      const x = e.clientX - rect.left;
      const pad = 26;
      const min = this.minTick;
      const max = this.maxTick;
      const span = max - min || 1;
      const w = rect.width;
      const t = min + ((x - pad) / Math.max(w - 2 * pad, 1)) * span;
      this.seek(Math.round(t));
    });
  }

  private bindEvents() {}

  private initScreenshot() {
    const select = document.getElementById('screenshot-select') as HTMLSelectElement;
    if (select && select.value) {
      this.changeScreenshot(select.value);
    }
  }

  private changeScreenshot(filename: string) {
    const img = document.getElementById('world-screenshot') as HTMLImageElement;
    if (img && SCREENSHOTS[filename]) {
      img.src = SCREENSHOTS[filename];
      img.alt = `Verified Godot simulation environment - ${filename}`;
    }
    this.updateProvenance();
  }

  private setMode(mode: 'trace' | 'snapshot') {
    this.mode = mode;
    document.getElementById('btn-mode-trace')?.classList.toggle('active', mode === 'trace');
    document.getElementById('btn-mode-snapshot')?.classList.toggle('active', mode === 'snapshot');
    
    const replaySection = document.getElementById('replay-section');
    if (replaySection) {
      replaySection.style.display = mode === 'trace' ? 'block' : 'none';
    }
    
    document.getElementById('snapshot-details')!.style.display = mode === 'snapshot' ? 'block' : 'none';
    document.getElementById('trace-details')!.style.display = mode === 'trace' ? 'block' : 'none';
    
    this.updateProvenance();
    this.renderInspector();
  }

  private updateProvenance() {
    const visual = document.getElementById('prov-visual')!;
    const data = document.getElementById('prov-data')!;
    const live = document.getElementById('prov-live')!;
    
    visual.textContent = 'VISUAL SOURCE: Verified Godot screenshot';
    
    if (this.mode === 'trace' && this.trace) {
      const isSynthetic = this.trace.header.runId === 'run-demo-001';
      data.textContent = `DATA SOURCE: nlt.observer-trace.v1 — ${isSynthetic ? 'synthetic demo trace' : 'trace file'}`;
    } else if (this.mode === 'snapshot' && this.snapshot) {
      data.textContent = 'DATA SOURCE: nlt.state-feed.v1 — static snapshot';
    } else if (this.mode === 'trace') {
      data.textContent = 'DATA SOURCE: nlt.observer-trace.v1 — synthetic demo trace (default)';
    } else {
      data.textContent = 'DATA SOURCE: None';
    }
    
    live.textContent = 'LIVE GODOT CONNECTION: Unavailable';
  }

  private openTraceFile() {
    const input = document.createElement('input');
    input.type = 'file';
    input.accept = '.jsonl,.json,.txt';
    input.onchange = (e) => {
      const file = (e.target as HTMLInputElement).files?.[0];
      if (file) {
        file.text().then((text) => {
          this.loadTraceText(text, false);
          this.setMode('trace');
        });
      }
    };
    input.click();
  }

  private openSnapshotFile() {
    const input = document.createElement('input');
    input.type = 'file';
    input.accept = '.json';
    input.onchange = (e) => {
      const file = (e.target as HTMLInputElement).files?.[0];
      if (file) {
        file.text().then((text) => {
          this.loadSnapshotText(text);
          this.setMode('snapshot');
        });
      }
    };
    input.click();
  }

  private loadTraceText(text: string, isSynthetic: boolean) {
    this.clearError();
    let parsed: ParsedTrace;
    try {
      parsed = parseTrace(text);
    } catch (err) {
      this.showError([`Parser threw: ${err}`]);
      return;
    }

    const schemaErrors = parsed.errors.filter((e) => e.includes('schemaVersion'));
    if (schemaErrors.length) {
      this.showError(schemaErrors);
    }

    this.trace = parsed;
    this.snapshot = null;
    this.buildTickIndex();
    this.currentTick = this.minTick;
    this.updateScrubberBounds();
    document.getElementById('replay-status')!.textContent = 
      `${isSynthetic ? 'Synthetic demo' : 'File loaded'} - ${parsed.header.runId}`;
    this.updateProvenance();
    this.renderInspector();
    this.render();
  }

  private loadSnapshotText(text: string) {
    this.clearError();
    let parsed: ParsedStateFeed;
    try {
      parsed = parseStateFeed(text);
    } catch (err) {
      this.showError([`Parser threw: ${err}`]);
      return;
    }

    if (parsed.errors.length) {
      this.showError(parsed.errors);
    }

    this.snapshot = parsed;
    this.trace = null;
    this.updateProvenance();
    this.renderInspector();
  }

  private buildTickIndex() {
    if (!this.trace) return;
    this.ticks = [];
    for (const r of this.trace.records) {
      if (r.kind === 'tick') {
        this.ticks.push({ tick: r.tick, agentId: r.agentId, position: r.position });
      }
    }
    const tickValues = this.ticks.map((t) => t.tick);
    this.minTick = tickValues.length ? Math.min(...tickValues) : 0;
    this.maxTick = tickValues.length ? Math.max(...tickValues) : 0;
    this.currentTick = this.minTick;
  }

  private clearError() {
    document.getElementById('error-banner')?.remove();
  }

  private showError(messages: string[]) {
    const banner = document.createElement('div');
    banner.id = 'error-banner';
    banner.className = 'error-banner';
    banner.setAttribute('role', 'alert');
    banner.innerHTML = `<div class="title">Error</div><ul>${messages.map(m => `<li>${this.escapeHtml(m)}</li>`).join('')}</ul>`;
    document.getElementById('app')!.insertBefore(banner, document.getElementById('app')!.firstChild);
  }

  private escapeHtml(text: string): string {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
  }

  private renderInspector() {
    if (this.mode === 'snapshot' && this.snapshot) {
      const s = this.snapshot.snapshot;
      document.getElementById('scene-id')!.textContent = s.scene.id;
      document.getElementById('scene-kind')!.textContent = s.scene.kind;
      document.getElementById('sim-time')!.textContent = s.simTimeIso;
      document.getElementById('inspector-tick')!.textContent = String(s.tick);
      document.getElementById('viewport-scene')!.textContent = `Scene: ${s.scene.id} (${s.scene.kind})`;
      
      const agentsList = document.getElementById('agents-list')!;
      agentsList.innerHTML = '';
      if (s.agents.length === 0) {
        agentsList.innerHTML = '<p class="inspector-empty">No agent data available</p>';
      } else {
        for (const agent of s.agents) {
          const card = document.createElement('div');
          card.className = 'agent-card';
          card.innerHTML = `
            <div class="agent-name">${this.escapeHtml(agent.name)} <span class="agent-role">[${agent.role}]</span></div>
            <div class="agent-detail">State: ${agent.state} | Task: ${agent.currentTask}</div>
            <div class="agent-detail">Pos: (${agent.position.x.toFixed(1)}, ${agent.position.y.toFixed(1)}, ${agent.position.z.toFixed(1)})</div>
            <div class="agent-detail">Stress: ${(agent.levels.stressLevel*100).toFixed(0)}% | Energy: ${(agent.levels.attentionEnergy*100).toFixed(0)}%</div>
            ${agent.struggleSignals.length > 0 ? `<div class="agent-detail" style="color:var(--warn)">⚠ ${agent.struggleSignals.join(', ')}</div>` : ''}
          `;
          agentsList.appendChild(card);
        }
      }
      
      document.getElementById('pairs-count')!.textContent = String(s.pairs.length);
      document.getElementById('events-count')!.textContent = String(s.events.length);
      document.getElementById('burnout-count')!.textContent = String(s.burnoutEpisodes.length);
      
      const pairsDiv = document.getElementById('pairs-details')!;
      pairsDiv.innerHTML = '';
      for (const pair of s.pairs) {
        const card = document.createElement('div');
        card.className = 'pair-card';
        card.innerHTML = `
          <div class="pair-header">${pair.avatarId} ↔ ${pair.aideId} (Score: ${(pair.overallScore*100).toFixed(0)}%)</div>
          <div>Ready: ${pair.ready ? 'Yes' : 'No'}</div>
          ${pair.blockingDimensions.length > 0 ? `<div style="color:var(--warn)">Blocking: ${pair.blockingDimensions.join(', ')}</div>` : ''}
        `;
        pairsDiv.appendChild(card);
      }
    } else if (this.mode === 'trace' && this.trace) {
      document.getElementById('trace-runid')!.textContent = this.trace.header.runId;
      document.getElementById('trace-agents')!.textContent = this.trace.header.agentRoster.join(', ');
      document.getElementById('trace-cadence')!.textContent = this.trace.header.cadenceHz + ' Hz';
      
      const state = reduce(this.trace.records, this.currentTick);
      document.getElementById('scene-id')!.textContent = Array.from(state.agents.values())[0]?.scene.id || '-';
      document.getElementById('scene-kind')!.textContent = Array.from(state.agents.values())[0]?.scene.kind || '-';
      document.getElementById('sim-time')!.textContent = this.trace.header.startTime;
      document.getElementById('inspector-tick')!.textContent = String(this.currentTick);
      document.getElementById('viewport-scene')!.textContent = `Scene: ${Array.from(state.agents.values())[0]?.scene.id || 'Unknown'}`;
      
      const agentsList = document.getElementById('agents-list')!;
      agentsList.innerHTML = '';
      if (state.agents.size === 0) {
        agentsList.innerHTML = '<p class="inspector-empty">No agent data available</p>';
      } else {
        for (const [agentId, agent] of state.agents) {
          const card = document.createElement('div');
          card.className = 'agent-card';
          card.innerHTML = `
            <div class="agent-name">${this.escapeHtml(agentId)}</div>
            <div class="agent-detail">Scene: ${agent.scene.id}</div>
            <div class="agent-detail">Pos: (${agent.position.x.toFixed(1)}, ${agent.position.y.toFixed(1)}, ${agent.position.z.toFixed(1)})</div>
            <div class="agent-detail">Vel: (${agent.velocity.x.toFixed(1)}, ${agent.velocity.y.toFixed(1)}, ${agent.velocity.z.toFixed(1)})</div>
          `;
          agentsList.appendChild(card);
        }
      }
    } else {
      document.getElementById('scene-id')!.textContent = '-';
      document.getElementById('scene-kind')!.textContent = '-';
      document.getElementById('sim-time')!.textContent = '-';
      document.getElementById('inspector-tick')!.textContent = '-';
      document.getElementById('viewport-scene')!.textContent = 'Scene: Unknown';
      document.getElementById('agents-list')!.innerHTML = '<p class="inspector-empty">No agent data available</p>';
    }
  }

  private render() {
    if (this.mode === 'trace' && this.trace) {
      const state = reduce(this.trace.records, this.currentTick);
      this.renderLog(state);
      this.renderSummary(state);
      this.renderTimeline();
      this.updateTickDisplay();
      this.renderInspector();
    }
  }

  private renderLog(state: SliceState) {
    const list = document.getElementById('log-list')!;
    const empty = document.getElementById('log-empty')!;
    list.innerHTML = '';
    
    const rows: any[] = [];
    for (const [agentId, intent] of state.intents) {
      const result = state.results.get(agentId);
      rows.push({
        agentId,
        intentTick: intent.lastTick,
        messageId: intent.messageId,
        verb: intent.verb,
        targetId: intent.targetId,
        resultStage: result?.stage,
        governanceCode: result?.governanceCode,
        status: result?.status,
        reason: result?.reason,
        hasResult: !!result,
      });
    }
    rows.sort((a, b) => a.intentTick - b.intentTick);
    
    if (rows.length === 0) {
      empty.hidden = false;
    } else {
      empty.hidden = true;
      for (const row of rows) {
        const el = document.createElement('div');
        el.className = 'log-row';
        el.innerHTML = `
          <div class="line1">
            <span class="tick">tick ${row.intentTick}</span> · 
            <span style="font-weight:700">${this.escapeHtml(row.agentId)}</span> · 
            <span class="verb">${this.escapeHtml(row.verb)}${row.targetId ? ' → ' + this.escapeHtml(row.targetId) : ''}</span>
          </div>
          ${row.resultStage ? `<span class="stage-badge"><span class="stage-shape ${row.resultStage}"></span>${row.resultStage}</span>` : ''}
          <div class="meta">${row.status ? 'status: '+row.status : ''} ${row.governanceCode ? 'gov: '+row.governanceCode : ''}</div>
          ${row.reason ? `<div class="note">reason: ${this.escapeHtml(row.reason)}</div>` : (!row.hasResult ? '<div class="note">pending result</div>' : '')}
        `;
        list.appendChild(el);
      }
    }
  }

  private renderSummary(state: SliceState) {
    const grid = document.getElementById('summary-grid')!;
    const all = this.trace!.records;
    const intents = all.filter((r: any) => r.kind === 'intent');
    const results = all.filter((r: any) => r.kind === 'result');
    const failures = all.filter((r: any) => r.kind === 'decision_failed');
    const transitions = all.filter((r: any) => r.kind === 'scene_transition');
    
    const accepted = results.filter((r: any) => r.status?.toLowerCase() === 'accepted').length;
    const rejected = results.length - accepted;
    
    grid.innerHTML = `
      <div class="summary-cell"><div class="label">Intents</div><div class="value">${intents.length}</div></div>
      <div class="summary-cell"><div class="label">Results</div><div class="value">${results.length}</div><div class="sub">${accepted} acc / ${rejected} rej</div></div>
      <div class="summary-cell"><div class="label">Failures</div><div class="value">${failures.length}</div></div>
      <div class="summary-cell"><div class="label">Transitions</div><div class="value">${transitions.length}</div></div>
    `;
  }

  private renderTimeline() {
    const el = document.getElementById('timeline')!;
    el.innerHTML = '';
    const all = this.trace!.records;
    const transitions = all.filter((r: any) => r.kind === 'scene_transition');
    const failures = all.filter((r: any) => r.kind === 'decision_failed');
    
    const events: Array<{ tick: number; type: 'transition' | 'failure'; label: string }> = [];
    for (const t of transitions) events.push({ tick: t.tick, type: 'transition', label: `${t.agentId}: ${t.from}→${t.to}` });
    for (const f of failures) events.push({ tick: f.tick, type: 'failure', label: `${f.agentId} decision failed` });
    
    if (events.length === 0) {
      el.appendChild(document.createTextNode('No events'));
      return;
    }
    
    const min = this.minTick;
    const max = this.maxTick;
    const span = max - min || 1;
    const pad = 26;
    const w = el.clientWidth || 600;
    
    const line = document.createElement('div');
    line.className = 'timeline-line';
    el.appendChild(line);
    
    const playhead = document.createElement('div');
    playhead.className = 'timeline-playhead';
    el.appendChild(playhead);
    
    const place = (tick: number) => pad + ((tick - min) / span) * (w - 2 * pad);
    
    for (const ev of events) {
      const m = document.createElement('button');
      m.className = `timeline-marker ${ev.type}`;
      m.type = 'button';
      m.title = `${ev.label} (tick ${ev.tick})`;
      m.style.left = `${place(ev.tick)}px`;
      m.onclick = () => this.seek(ev.tick);
      el.appendChild(m);
    }
    
    const px = pad + ((this.currentTick - min) / span) * (w - 2 * pad);
    playhead.style.left = `${px}px`;
    playhead.style.top = '0';
    playhead.style.bottom = '0';
  }

  private updateTickDisplay() {
    document.getElementById('tick-value')!.textContent = String(this.currentTick);
    document.getElementById('tick-range')!.textContent = `/ ${this.maxTick}`;
    const scr = document.getElementById('scrubber') as HTMLInputElement;
    scr.value = String(this.currentTick);
  }

  private updateScrubberBounds() {
    const scr = document.getElementById('scrubber') as HTMLInputElement;
    scr.min = String(this.minTick);
    scr.max = String(this.maxTick);
    scr.value = String(this.currentTick);
  }

  private setPlaying(playing: boolean) {
    this.isPlaying = playing;
    document.getElementById('btn-play')!.hidden = playing;
    document.getElementById('btn-pause')!.hidden = !playing;
    if (playing) {
      this.lastFrame = performance.now();
      this.loop();
    } else {
      this.stopLoop();
    }
  }

  private stopLoop() {
    if (this.rafId !== null) {
      cancelAnimationFrame(this.rafId);
      this.rafId = null;
    }
  }

  private loop = () => {
    if (!this.isPlaying) { this.rafId = null; return; }
    const now = performance.now();
    let dt = now - this.lastFrame;
    this.lastFrame = now;
    const interval = this.tickIntervalMs / this.speed;
    let advanced = 0;
    while (dt >= interval && advanced < 10) {
      this.seek(this.currentTick + 1);
      dt -= interval;
      advanced++;
    }
    if (this.currentTick >= this.maxTick) {
      this.setPlaying(false);
    } else {
      this.rafId = requestAnimationFrame(this.loop);
    }
  };

  private seek(tick: number) {
    if (this.mode !== 'trace') return;
    const t = Math.min(Math.max(tick, this.minTick), this.maxTick);
    if (t === this.currentTick) return;
    this.currentTick = t;
    (document.getElementById('scrubber') as HTMLInputElement).value = String(t);
    this.render();
  }

  private handleKeydown(e: KeyboardEvent) {
    const active = document.activeElement as HTMLElement | null;
    const isInput = active && (active.tagName === 'INPUT' || active.tagName === 'SELECT' || active.isContentEditable);
    if (e.key === ' ' && !isInput && this.mode === 'trace') {
      e.preventDefault();
      this.setPlaying(!this.isPlaying);
    } else if (e.key === 'ArrowLeft' && !isInput && this.mode === 'trace') {
      e.preventDefault();
      this.seek(this.currentTick - 1);
    } else if (e.key === 'ArrowRight' && !isInput && this.mode === 'trace') {
      e.preventDefault();
      this.seek(this.currentTick + 1);
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
