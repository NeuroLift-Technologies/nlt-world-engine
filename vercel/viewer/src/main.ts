import { parseTrace } from './trace/parser.js';
import { World3DView } from './world3d.js';
import { reduce } from './trace/reducer.js';
import type { ParsedTrace, SliceState, Stage, IntentRecord, ResultRecord, DecisionFailedRecord, SceneTransitionRecord } from './trace/types.js';

// ---------------------------------------------------------------------------
// Default embedded trace (no network). Exercises every record kind so the
// viewer can be demonstrated without a file. CC owns the real contract.
// ---------------------------------------------------------------------------
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
{"type":"scene_entities","scene":"plaza","entities":[{"id":"well_1","kind":"well","position":{"x":12,"y":0,"z":0},"affordances":["approach","use"]},{"id":"plaza_light","kind":"lamp","position":{"x":-3,"y":0,"z":4},"affordances":[]}]}
{"type":"tick","tick":30,"agentId":"agent_alfa","scene":{"id":"office_1","kind":"interior"},"position":{"x":2,"y":0,"z":1},"velocity":{"x":0,"y":0,"z":0}}
{"type":"tick","tick":30,"agentId":"agent_bravo","scene":{"id":"plaza","kind":"open_world"},"position":{"x":5,"y":0,"z":2},"velocity":{"x":0,"y":0,"z":0}}
{"type":"weird_record","tick":99,"agentId":"nope","foo":"bar"}
`;

// Marker shapes (identity channel 1 — colour is never the sole channel).
const SHAPES = ['circle', 'square', 'triangle', 'diamond', 'pentagon', 'hexagon'] as const;
function agentShapeIndex(agentId: string): number {
  let h = 0;
  for (let i = 0; i < agentId.length; i++) h = (h * 31 + agentId.charCodeAt(i)) | 0;
  return Math.abs(h) % SHAPES.length;
}

function drawMarker(
  ctx: CanvasRenderingContext2D,
  x: number,
  y: number,
  size: number,
  shape: string,
  label: string,
) {
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
    case 'pentagon': {
      const steps = 5;
      for (let i = 0; i <= steps; i++) {
        const a = (-Math.PI / 2) + (i * 2 * Math.PI) / steps;
        ctx.lineTo(Math.cos(a) * r, Math.sin(a) * r);
      }
      ctx.closePath();
      break;
    }
    case 'hexagon': {
      const steps = 6;
      for (let i = 0; i <= steps; i++) {
        const a = (-Math.PI / 2) + (i * 2 * Math.PI) / steps;
        ctx.lineTo(Math.cos(a) * r, Math.sin(a) * r);
      }
      ctx.closePath();
      break;
    }
  }
  ctx.fillStyle = '#ffffff';
  ctx.fill();
  ctx.strokeStyle = '#1a1a1a';
  ctx.lineWidth = 1.6;
  ctx.stroke();
  ctx.restore();

  // Label: identity channel 2 — text, never colour alone.
  ctx.save();
  ctx.font = 'bold 11px sans-serif';
  ctx.textAlign = 'center';
  ctx.textBaseline = 'bottom';
  ctx.fillStyle = '#1a1a1a';
  ctx.fillText(label, 0, y - r - 5);
  ctx.restore();
}

function drawTrail(
  ctx: CanvasRenderingContext2D,
  pts: { x: number; z: number }[],
  mx: (x: number) => number,
  mz: (z: number) => number,
) {
  if (pts.length < 2) return;
  ctx.beginPath();
  ctx.moveTo(mx(pts[0].x), mz(pts[0].z));
  for (let i = 1; i < pts.length; i++) ctx.lineTo(mx(pts[i].x), mz(pts[i].z));
  ctx.strokeStyle = '#9aa0a6';
  ctx.lineWidth = 1.4;
  ctx.globalAlpha = 0.55;
  ctx.stroke();
  ctx.globalAlpha = 1;
}

// ---------------------------------------------------------------------------
// App
// ---------------------------------------------------------------------------
export class ViewerApp {
  private trace: ParsedTrace | null = null;
  private ticks: Array<{ tick: number; agentId: string; position: { x: number; y: number; z: number } }> = [];
  private minTick = 0;
  private maxTick = 0;
  private currentTick = 0;
  private sceneFilter = 'all';

  private isPlaying = false;
  private speed = 1;
  private lastFrame = 0;
  private rafId: number | null = null;

  private worldView: World3DView;
  private canvas: HTMLCanvasElement;
  private ctx: CanvasRenderingContext2D | null = null;
  private dpr = 1;

  private elements: Record<string, HTMLElement> = {};

  constructor() {
    this.canvas = document.getElementById('plot') as HTMLCanvasElement;
    this.worldView = new World3DView(document.getElementById('world3d') as HTMLCanvasElement);
    this.bindElements();
    this.bindEvents();
    this.loadText(DEFAULT_TRACE);
    window.addEventListener('resize', () => this.render());
    this.tickIntervalMs = 1000 / Math.max(this.trace?.header.cadenceHz ?? 10, 1);
  }

  // --- loading -----------------------------------------------------------
  private async loadText(text: string) {
    this.clearError();
    let parsed: ParsedTrace;
    try {
      parsed = parseTrace(text);
    } catch (err) {
      this.showError([`Parser threw: ${err}`]);
      return;
    }

    // Fail LOUDLY on unknown schemaVersion (parser records it, we surface it).
    const schemaErrors = parsed.errors.filter((e) => e.includes('schemaVersion'));
    if (schemaErrors.length) {
      this.showError(schemaErrors);
      // Still render so the user sees the header as loaded.
    }
    if (parsed.errors.length && !schemaErrors.length) {
      // non-fatal parse problems: show in unrecognized list, continue
    }

    this.trace = parsed;
    this.buildTickIndex();
    this.refreshHeaderMeta();
    this.refreshUnrecognized();
    this.setupSceneFilter();
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

  private clearError() {
    let el = document.getElementById('error-banner');
    if (el) el.remove();
  }

  private showError(messages: string[]) {
    const banner = document.createElement('div');
    banner.id = 'error-banner';
    banner.className = 'error-banner';
    banner.setAttribute('role', 'alert');
    banner.setAttribute('aria-live', 'assertive');
    const title = document.createElement('div');
    title.className = 'title';
    title.textContent = 'Trace could not be loaded';
    banner.appendChild(title);
    const ul = document.createElement('ul');
    for (const m of messages) {
      const li = document.createElement('li');
      li.textContent = m;
      ul.appendChild(li);
    }
    banner.appendChild(ul);
    const app = document.getElementById('app')!;
    app.insertBefore(banner, app.firstChild);
  }

  // --- header / meta -----------------------------------------------------
  private refreshHeaderMeta() {
    if (!this.trace) return;
    const h = this.trace.header;
    const el = document.getElementById('shell-meta')!;
    el.textContent = `schemaVersion: ${h.schemaVersion}  ·  runId: ${h.runId}  ·  engine: ${h.engineCommit}  ·  Godot: ${h.godotVersion}  ·  start: ${h.startTime}  ·  cadence: ${h.cadenceHz} Hz  ·  agents: ${h.agentRoster.join(', ')}`;
  }

  // --- scene filter ------------------------------------------------------
  private setupSceneFilter() {
    const sel = document.getElementById('plot-scene') as HTMLSelectElement;
    const scenes = new Set<string>();
    for (const t of this.ticks) scenes.add(''); // placeholder
    // Collect scene ids from tick records.
    for (const r of this.trace!.records) {
      if (r.kind === 'tick') scenes.add(r.scene.id);
    }
    sel.innerHTML = '<option value="all">All scenes</option>';
    for (const s of [...scenes].filter(Boolean)) {
      const o = document.createElement('option');
      o.value = s;
      o.textContent = s;
      sel.appendChild(o);
    }
    sel.addEventListener('change', (e) => {
      this.sceneFilter = (e.target as HTMLSelectElement).value;
      this.render();
    });
  }

  private tickValueOfScene(agentScene: string): boolean {
    return this.sceneFilter === 'all' || agentScene === this.sceneFilter;
  }

  // --- render ------------------------------------------------------------
  private render() {
    if (!this.trace) return;
    const state = reduce(this.trace.records, this.currentTick);
    this.worldView.update(state.agents, state.entitiesByScene);
    this.renderPlot(state);
    this.renderLog(state);
    this.renderSummary(state);
    this.renderTimeline();
    this.updateTickDisplay();
  }

  private renderPlot(state: SliceState) {
    if (!this.trace || !this.ctx) return;
    const canvas = this.canvas;
    if (!canvas) return;
    const dpr = (this.dpr = window.devicePixelRatio || 1);
    const cssW = canvas.clientWidth || 600;
    const cssH = canvas.clientHeight || 400;
    canvas.width = cssW * dpr;
    canvas.height = cssH * dpr;
    const ctx = (this.ctx = canvas.getContext('2d')!)!;
    ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    ctx.clearRect(0, 0, cssW, cssH);

    if (this.ticks.length === 0) {
      ctx.fillStyle = '#6b6b6b';
      ctx.font = '14px sans-serif';
      ctx.textAlign = 'center';
      ctx.textBaseline = 'middle';
      ctx.fillText('No tick records in trace', cssW / 2, cssH / 2);
      return;
    }

    // Build per-agent position history (<= current tick).
    const history = new Map<string, { x: number; z: number }[]>();
    const pts: { x: number; z: number }[] = [];
    for (const t of this.ticks) {
      if (t.tick > this.currentTick) continue;
      let arr = history.get(t.agentId);
      if (!arr) { arr = []; history.set(t.agentId, arr); }
      arr.push({ x: t.position.x, z: t.position.z });
      pts.push({ x: t.position.x, z: t.position.z });
    }

    let minX = 0, maxX = 100, minZ = 0, maxZ = 100;
    if (pts.length) {
      minX = Math.min(...pts.map((p) => p.x));
      maxX = Math.max(...pts.map((p) => p.x));
      minZ = Math.min(...pts.map((p) => p.z));
      maxZ = Math.max(...pts.map((p) => p.z));
    }
    const padX = (maxX - minX) * 0.12 + 2;
    const padZ = (maxZ - minZ) * 0.12 + 2;
    minX -= padX; maxX += padX; minZ -= padZ; maxZ += padZ;
    const worldW = maxX - minX || 100;
    const worldH = maxZ - minZ || 100;
    const scale = Math.min(cssW / worldW, cssH / worldH) * 0.9;
    const ox = (cssW - worldW * scale) / 2 - minX * scale;
    const oy = (cssH - worldH * scale) / 2 - minZ * scale;
    const mx = (x: number) => ox + x * scale;
    const mz = (z: number) => oy + z * scale;

    // Axes (faint) + origin.
    ctx.strokeStyle = '#d8d8d8';
    ctx.lineWidth = 1;
    ctx.beginPath();
    ctx.moveTo(mx(minX), mz(0)); ctx.lineTo(mx(maxX), mz(0)); // x axis
    ctx.moveTo(mx(0), mz(minZ)); ctx.lineTo(mx(0), mz(maxZ)); // z axis
    ctx.stroke();
    ctx.fillStyle = '#6b6b6b';
    ctx.font = '10px sans-serif';
    ctx.textAlign = 'left';
    ctx.fillText('x', mx(maxX) + 4, mz(0) - 4);
    ctx.textBaseline = 'top';
    ctx.fillText('z', mx(0) + 4, mz(maxZ) + 4);

    // Determine latest scene per agent (for scene filter).
    const latestSceneByAgent = new Map<string, string>();
    for (const r of this.trace.records) {
      if (r.kind !== 'tick' || r.tick > this.currentTick) continue;
      latestSceneByAgent.set(r.agentId, r.scene.id);
    }

    // Trails first (behind markers).
    for (const [agentId, hist] of history) {
      if (!this.tickValueOfScene(latestSceneByAgent.get(agentId) ?? '')) continue;
      drawTrail(ctx, hist, mx, mz);
    }

    // Current markers from reducer state.
    for (const [agentId, st] of state.agents) {
      if (!this.tickValueOfScene(st.scene.id)) continue;
      const shape = SHAPES[agentShapeIndex(agentId)];
      drawMarker(ctx, mx(st.position.x), mz(st.position.z), 16, shape, agentId);
    }

    // Entity markers for the shown scene(s).
    for (const [sceneId, entities] of state.entitiesByScene) {
      if (this.sceneFilter !== 'all' && sceneId !== this.sceneFilter) continue;
      for (const ent of entities) {
        ctx.save();
        ctx.strokeStyle = '#1a1a1a';
        ctx.lineWidth = 1;
        ctx.setLineDash([4, 3]);
        ctx.strokeRect(mx(ent.position.x) - 5, mz(ent.position.z) - 5, 10, 10);
        ctx.setLineDash([]);
        ctx.restore();
        ctx.save();
        ctx.font = '10px sans-serif';
        ctx.textAlign = 'center';
        ctx.textBaseline = 'bottom';
        ctx.fillStyle = '#1a1a1a';
        ctx.fillText(ent.id, mx(ent.position.x), mz(ent.position.z) - 7);
        ctx.restore();
      }
    }

    // Legend.
    this.renderLegend();
  }

  private renderLegend() {
    const el = document.getElementById('plot-legend')!;
    // Rebuild compact legend of agents shown at current tick.
    const shown = new Map<string, string>();
    for (const r of this.trace!.records) {
      if (r.kind !== 'tick' || r.tick > this.currentTick) continue;
      if (!this.tickValueOfScene(r.scene.id)) continue;
      shown.set(r.agentId, r.scene.id);
    }
    el.innerHTML = '';
    const title = document.createElement('span');
    title.textContent = 'Agents: ';
    title.style.fontSize = '11.5px';
    title.style.color = '#1a1a1a';
    title.style.fontWeight = '700';
    el.appendChild(title);
    let first = true;
    for (const [agentId] of shown) {
      if (!first) {
        const sep = document.createTextNode('   ');
        el.appendChild(sep);
      }
      first = false;
      const item = document.createElement('span');
      item.className = 'legend-item';
      item.setAttribute('aria-label', `Agent ${agentId}`);
      const shape = document.createElement('span');
      shape.className = 'legend-shape';
      const cls = ['circle','square','triangle','diamond','pentagon','hexagon'][agentShapeIndex(agentId)];
      shape.classList.add(cls);
      const name = document.createElement('span');
      name.textContent = agentId;
      item.appendChild(shape);
      item.appendChild(name);
      el.appendChild(item);
    }
  }

  private renderLog(state: SliceState) {
    const list = document.getElementById('log-list')!;
    const empty = document.getElementById('log-empty')!;
    list.innerHTML = '';

    // Compose intent/result rows for agents whose latest intent is at current tick
    // OR whose latest result is at current tick — show all intents/results known
    // at this tick, ordered by observed tick then message id.
    const rows: Array<{ agentId: string; intentTick: number; messageId: string; verb: string; targetId?: string; resultStage?: Stage; governanceCode?: string; status?: string; reason?: string; ticksBehind?: number; decisionMs?: number; hasResult: boolean }> = [];

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
        ticksBehind: intent.ticksBehind,
        decisionMs: intent.decisionMs,
        hasResult: !!result,
      });
    }
    // Also include results not tied to a shown intent at this tick.
    for (const [agentId, result] of state.results) {
      if (state.intents.has(agentId)) continue;
      rows.push({
        agentId, intentTick: result.lastTick, messageId: result.intentMessageId,
        verb: '(unknown intent)', targetId: undefined, resultStage: result.stage,
        governanceCode: result.governanceCode, status: result.status, reason: result.reason,
        ticksBehind: undefined, decisionMs: undefined, hasResult: true,
      });
    }

    rows.sort((a, b) => a.intentTick - b.intentTick || a.messageId.localeCompare(b.messageId));

    if (rows.length === 0) {
      empty.hidden = false;
    } else {
      empty.hidden = true;
      for (const row of rows) {
        const el = document.createElement('div');
        el.className = 'log-row';
        el.setAttribute('role', 'listitem');

        const line1 = document.createElement('div');
        line1.className = 'line1';
        const tick = document.createElement('span');
        tick.className = 'tick';
        tick.textContent = `tick ${row.intentTick}`;
        const agent = document.createElement('span');
        agent.className = 'agent';
        agent.textContent = row.agentId;
        agent.style.fontWeight = '700';
        const verb = document.createElement('span');
        verb.className = 'verb';
        verb.textContent = row.verb;
        const target = row.targetId ? ` → ${row.targetId}` : '';
        verb.textContent += target;
        line1.appendChild(tick);
        line1.appendChild(document.createTextNode(' · '));
        line1.appendChild(agent);
        line1.appendChild(document.createTextNode(' · '));
        line1.appendChild(verb);

        const badge = document.createElement('span');
        badge.className = 'stage-badge';
        const stageText = row.resultStage ?? '—';
        const shape = document.createElement('span');
        shape.className = `stage-shape ${row.resultStage ?? 'accepted'}`;
        shape.setAttribute('aria-label', stageText);
        shape.setAttribute('aria-hidden', 'true');
        const txt = document.createElement('span');
        txt.textContent = stageText;
        badge.appendChild(shape);
        badge.appendChild(txt);

        const meta = document.createElement('div');
        meta.className = 'meta';
        const parts: string[] = [];
        if (row.status !== undefined) parts.push(`status: ${row.status}`);
        if (row.governanceCode) parts.push(`gov: ${row.governanceCode}`);
        if (row.ticksBehind !== undefined) parts.push(`ticksBehind: ${row.ticksBehind}`);
        if (row.decisionMs !== undefined) parts.push(`decisionMs: ${row.decisionMs}`);
        if (parts.length) meta.textContent = parts.join('   ');

        const note = document.createElement('div');
        note.className = 'note';
        if (row.reason) note.textContent = `reason: ${row.reason}`;
        else if (!row.hasResult) note.textContent = 'pending result';

        el.appendChild(line1);
        el.appendChild(badge);
        if (meta.textContent) el.appendChild(meta);
        if (note.textContent) el.appendChild(note);
        list.appendChild(el);
      }
    }

    const count = document.getElementById('log-count')!;
    count.textContent = `${rows.length} row${rows.length === 1 ? '' : 's'} at tick ${this.currentTick}`;
  }

  private renderSummary(state: SliceState) {
    const grid = document.getElementById('summary-grid')!;
    // Compute over the whole trace (all intents/results/failures/transitions).
    const all = this.trace!.records;
    const intents = all.filter((r): r is IntentRecord => r.kind === 'intent');
    const results = all.filter((r): r is ResultRecord => r.kind === 'result');
    const failures = all.filter((r): r is DecisionFailedRecord => r.kind === 'decision_failed');
    const transitions = all.filter((r): r is SceneTransitionRecord => r.kind === 'scene_transition');

    const acceptedByStage: Record<Stage, number> = { protocol: 0, governance: 0, physical: 0, accepted: 0 };
    const rejectedByStage: Record<Stage, number> = { protocol: 0, governance: 0, physical: 0, accepted: 0 };
    for (const r of results) {
      const target = r.status && r.status.toLowerCase() === 'accepted' ? acceptedByStage : rejectedByStage;
      target[r.stage] = (target[r.stage] ?? 0) + 1;
    }

    const failuresByStatus: Record<string, number> = {};
    for (const f of failures) {
      const key = f.httpStatus !== undefined ? String(f.httpStatus) : f.error ?? 'unknown';
      failuresByStatus[key] = (failuresByStatus[key] ?? 0) + 1;
    }

    const cells: Array<{ label: string; value: string | number; sub?: string }> = [
      { label: 'Intents', value: intents.length },
      { label: 'Results', value: results.length, sub: `${acceptedByStage.accepted + acceptedByStage.governance + acceptedByStage.physical + acceptedByStage.protocol} accepted` },
      { label: 'Accepted (stage)', value: Object.values(acceptedByStage).reduce((a, b) => a + b, 0) },
      { label: 'Rejected (stage)', value: Object.values(rejectedByStage).reduce((a, b) => a + b, 0) },
      { label: 'Failures', value: failures.length, sub: Object.entries(failuresByStatus).map(([k, v]) => `${k}×${v}`).join(', ') || '—' },
      { label: 'Scene transitions', value: transitions.length },
    ];

    grid.innerHTML = '';
    for (const c of cells) {
      const cell = document.createElement('div');
      cell.className = 'summary-cell';
      const lab = document.createElement('div');
      lab.className = 'label';
      lab.textContent = c.label;
      const val = document.createElement('div');
      val.className = 'value';
      val.textContent = String(c.value);
      cell.appendChild(lab);
      cell.appendChild(val);
      if (c.sub) {
        const sub = document.createElement('div');
        sub.className = 'sub';
        sub.textContent = c.sub;
        cell.appendChild(sub);
      }
      grid.appendChild(cell);
    }
  }

  private renderTimeline() {
    const el = document.getElementById('timeline')!;
    el.innerHTML = '';
    el.setAttribute('tabindex', '0');
    el.setAttribute('role', 'region');
    el.setAttribute('aria-label', 'Event timeline');
    const all = this.trace!.records;
    const transitions = all.filter((r): r is SceneTransitionRecord => r.kind === 'scene_transition');
    const failures = all.filter((r): r is DecisionFailedRecord => r.kind === 'decision_failed');

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
    const w = el.clientWidth || 560;

    const line = document.createElement('div');
    line.className = 'timeline-line';
    el.appendChild(line);

    const playhead = document.createElement('div');
    playhead.className = 'timeline-playhead';
    el.appendChild(playhead);

    const hint = document.createElement('span');
    hint.className = 'timeline-hint';
    hint.textContent = '▲ transition   ✕ decision failed   · click to jump   Space play/pause   ← → step';
    el.appendChild(hint);

    const place = (tick: number) => pad + ((tick - min) / span) * (w - 2 * pad);

    for (const ev of events) {
      const m = document.createElement('button');
      m.className = `timeline-marker ${ev.type}`;
      m.type = 'button';
      m.setAttribute('aria-label', `${ev.label} at tick ${ev.tick}`);
      m.style.left = `${place(ev.tick)}px`;
      m.title = `${ev.label} (tick ${ev.tick})`;
      m.addEventListener('click', () => this.seek(ev.tick));
      m.addEventListener('keydown', (e: KeyboardEvent) => {
        if (e.key === 'Enter' || e.key === ' ') this.seek(ev.tick);
      });
      el.appendChild(m);
    }

    const px = pad + ((this.currentTick - min) / span) * (w - 2 * pad);
    playhead.style.left = `${px}px`;
    playhead.style.top = '0';
    playhead.style.bottom = '0';
  }

  private updateTickDisplay() {
    const v = document.getElementById('tick-value')!;
    v.textContent = String(this.currentTick);
    const r = document.getElementById('tick-range')!;
    r.textContent = `/ ${this.maxTick}`;
    const scr = document.getElementById('scrubber') as HTMLInputElement;
    scr.setAttribute('aria-valuenow', String(this.currentTick));
    const mode = document.getElementById('plot-mode')!;
    mode.textContent = this.isPlaying ? 'playing' : 'paused';
    mode.setAttribute('aria-live', 'polite');
  }

  // --- transport ---------------------------------------------------------
  private bindElements() {
    const ids = ['btn-play', 'btn-pause', 'btn-step-back', 'btn-step-fwd', 'sel-speed', 'scrubber', 'file-input'];
    for (const id of ids) {
      const el = document.getElementById(id);
      if (el) this.elements[id] = el;
    }
    // file input is created in markup? not present — create it.
  }

  private bindEvents() {
    const play = document.getElementById('btn-play')!;
    const pause = document.getElementById('btn-pause')!;
    const back = document.getElementById('btn-step-back')!;
    const fwd = document.getElementById('btn-step-fwd')!;
    const speed = document.getElementById('sel-speed') as HTMLSelectElement;
    const scrub = document.getElementById('scrubber') as HTMLInputElement;

    play.addEventListener('click', () => this.setPlaying(true));
    pause.addEventListener('click', () => this.setPlaying(false));
    back.addEventListener('click', () => this.seek(this.currentTick - 1));
    fwd.addEventListener('click', () => this.seek(this.currentTick + 1));
    speed.addEventListener('change', () => { this.speed = Number(speed.value || 1); });
    scrub.addEventListener('input', () => this.seek(Number(scrub.value)));
    scrub.addEventListener('change', () => this.seek(Number(scrub.value)));

    // Drag timeline container to jump (already buttons; add click on track).
    const tl = document.getElementById('timeline')!;
    tl.addEventListener('click', (e: MouseEvent) => {
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

    // File input: create and attach.
    const fileInput = document.createElement('input');
    fileInput.type = 'file';
    fileInput.accept = '.jsonl,.json,.txt';
    fileInput.hidden = true;
    fileInput.setAttribute('aria-label', 'Open a trace file (JSONL)');
    document.body.appendChild(fileInput);
    fileInput.addEventListener('change', (e) => {
      const f = (e.target as HTMLInputElement).files?.[0];
      if (!f) return;
      f.text().then((text) => this.loadText(text));
    });
    const openBtn = document.createElement('button');
    openBtn.type = 'button';
    openBtn.textContent = 'Open trace…';
    openBtn.setAttribute('aria-label', 'Open a trace file');
    openBtn.className = 'tp-button';
    openBtn.addEventListener('click', () => fileInput.click());
    const firstRow = document.querySelector('.transport-row')!;
    firstRow.insertBefore(openBtn, firstRow.firstChild);

    // Keyboard: Space play/pause, arrows step (when no input focused).
    window.addEventListener('keydown', (e: KeyboardEvent) => {
      const active = document.activeElement as HTMLElement | null;
      const isInput = active && (active.tagName === 'INPUT' || active.tagName === 'SELECT' || active.isContentEditable);
      if (e.key === ' ' && !isInput) {
        e.preventDefault();
        this.setPlaying(!this.isPlaying);
        return;
      }
      if (e.key === 'ArrowLeft' && !isInput) { e.preventDefault(); this.seek(this.currentTick - 1); return; }
      if (e.key === 'ArrowRight' && !isInput) { e.preventDefault(); this.seek(this.currentTick + 1); return; }
    });
  }

  private tickIntervalMs = 100;

  private setPlaying(playing: boolean) {
    this.isPlaying = playing;
    const play = document.getElementById('btn-play')!;
    const pause = document.getElementById('btn-pause')!;
    play.hidden = playing;
    pause.hidden = !playing;
    play.setAttribute('aria-pressed', String(playing));
    pause.setAttribute('aria-pressed', String(!playing));
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
    const t = Math.min(Math.max(tick, this.minTick), this.maxTick);
    if (t === this.currentTick) return;
    this.currentTick = t;
    (document.getElementById('scrubber') as HTMLInputElement).value = String(t);
    this.render();
  }

  private updateScrubberBounds() {
    const scr = document.getElementById('scrubber') as HTMLInputElement;
    scr.min = String(this.minTick);
    scr.max = String(this.maxTick);
    scr.value = String(this.currentTick);
    scr.setAttribute('aria-valuemin', String(this.minTick));
    scr.setAttribute('aria-valuemax', String(this.maxTick));
  }

  private refreshUnrecognized() {
    const countEl = document.getElementById('unrec-count')!;
    const list = document.getElementById('unrec-list')!;
    const unrec = (this.trace?.errors ?? []).filter((e) => e.includes('unknown record type'));
    // Also surface unknown records parsed as kind 'unknown'.
    const unknownRecords = (this.trace?.records ?? []).filter((r) => r.kind === 'unknown');
    const total = Math.max(unrec.length, unknownRecords.length);
    countEl.textContent = `${total} unrecognized record${total === 1 ? '' : 's'}`;
    list.innerHTML = '';
    if (total === 0) {
      const li = document.createElement('li');
      li.textContent = '(none)';
      list.appendChild(li);
      return;
    }
    // Show parsed unknown records (with line + reason). Errors-only cases too.
    const shown = new Set<string>();
    for (const r of unknownRecords) {
      const key = `line ${r.line}: ${r.reason}`;
      if (shown.has(key)) continue;
      shown.add(key);
      const li = document.createElement('li');
      li.textContent = `line ${r.line} — ${r.reason} (${JSON.stringify(r.raw).slice(0, 120)})`;
      list.appendChild(li);
    }
    // Any schema/parse errors not already shown.
    for (const e of this.trace!.errors) {
      if (e.includes('unknown record type')) continue;
      const key = `err: ${e}`;
      if (shown.has(key)) continue;
      shown.add(key);
      const li = document.createElement('li');
      li.textContent = e;
      list.appendChild(li);
    }
  }
}

declare global {
  interface Window { ViewerApp: typeof ViewerApp; }
}

// Start once DOM is ready.
if (document.readyState === 'loading') {
  document.addEventListener('DOMContentLoaded', () => {
    (window as any).ViewerApp = ViewerApp;
    new ViewerApp();
  });
} else {
  (window as any).ViewerApp = ViewerApp;
  new ViewerApp();
}
