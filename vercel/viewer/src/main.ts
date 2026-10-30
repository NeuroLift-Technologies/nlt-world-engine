// NLT World Engine — Observer (browser). Presentation and viewer-side interaction only.
//
//   Godot / World Engine  owns physical state           -> not reachable from a browser yet
//   AI-Fusion             owns semantic state           -> arrives inside nlt.state-feed.v1
//   this viewer           draws what a FeedSource says  -> never simulates, never derives
import * as THREE from 'three';
import { WorldView, sceneKeyFor } from './scene/world';
import { Minimap } from './scene/minimap';
import { ReplaySource, REPLAYS } from './feed/replay';
import { TraceSource, TRACE_SAMPLE } from './feed/trace';
import { LiveRelaySource } from './feed/live';
import type { FeedSource } from './feed/source';
import type { Agent, FeedEvent, StateFeedDoc } from './feed/types';
import * as P from './feed/plain';
import { SEED } from './world/geometry';
import { initRunControl } from './run/runControl';

const $ = <T extends HTMLElement>(id: string) => document.getElementById(id) as T;
const esc = (s: unknown) => String(s ?? '').replace(/[&<>"']/g, (c) => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;' })[c]!);
const params = new URLSearchParams(location.search);

const app = $('app');
const statusEl = $('status');
function setStatus(text: string | null, kind: 'loading' | 'error' = 'loading') {
  if (text === null) {
    statusEl.classList.add('fade');
    setTimeout(() => (statusEl.hidden = true), 400);
    return;
  }
  statusEl.hidden = false;
  statusEl.classList.remove('fade');
  statusEl.dataset.kind = kind;
  $('status-text').textContent = text;
}

// ------------------------------------------------------------------ boot
function hasWebGL(): boolean {
  try {
    const c = document.createElement('canvas');
    return !!(c.getContext('webgl2') || c.getContext('webgl'));
  } catch {
    return false;
  }
}

if (!hasWebGL()) {
  setStatus('This viewer needs WebGL, which this browser or device has turned off. The World Engine itself is unaffected.', 'error');
  throw new Error('WebGL unavailable');
}

// Let the status paint before the (synchronous) island build.
await new Promise((r) => requestAnimationFrame(() => setTimeout(r, 30)));
const world = new WorldView($('world') as HTMLCanvasElement);
const minimap = new Minimap($('minimap') as HTMLCanvasElement, world);
const live = new LiveRelaySource();

const state = {
  source: null as FeedSource | null,
  pos: 0, // fractional frame index
  playing: false,
  speed: 1,
  selected: null as string | null,
  sceneMode: 'follow' as string, // 'follow' or a scene id ('open_world', 'workplace_7', …)
  lastFrame: -1,
  switching: false,
  seenEvents: new Set<string>(),
};

const labelLayer = $('labels');
const labels = new Map<string, HTMLDivElement>();

// ------------------------------------------------------------------ feed
async function openReplay(id: string) {
  const entry = REPLAYS.find((r) => r.id === id) ?? REPLAYS[0];
  await openSource(new ReplaySource(entry), entry.label, `?replay=${entry.id}`);
}

/** True when the shown recording has positions and decisions only (feed/trace.ts). */
const physicalOnly = () => state.source?.info.content === 'physical-trace';

/** Open any source: the authored replays and recorded engine runs share one path. Returns false
 *  when it could not be opened; what was shown stays shown and the reason is on screen. */
async function openSource(src: FeedSource, label: string, query: string | null): Promise<boolean> {
  setStatus(`Loading recording “${label}”…`);
  state.playing = false;
  try {
    await src.open();
  } catch (e) {
    setStatus(`Could not load this recording: ${e instanceof Error ? e.message : e}`, 'error');
    return false;
  }
  state.source = src;
  state.pos = 0;
  state.lastFrame = -1;
  state.seenEvents.clear();
  state.selected = src.frame(0).agents.find((a) => a.role === 'avatar')?.id ?? src.frame(0).agents[0]?.id ?? null;
  for (const l of labels.values()) l.remove();
  labels.clear();
  const sc = $('scrubber') as HTMLInputElement;
  sc.max = String(Math.max(0, src.frameCount() - 1));
  sc.value = '0';
  buildTimeline();
  updateSourceBadge();
  const startFrame = Number(params.get('frame'));
  if (Number.isFinite(startFrame) && startFrame > 0) state.pos = Math.min(startFrame, src.frameCount() - 1);
  await syncScene(true);
  setStatus(null);
  state.playing = params.get('play') !== '0';
  updatePlayButton();
  // A local file has no URL of its own; leave the address as it was rather than point at nothing.
  if (query !== null && location.search !== query) history.replaceState(null, '', query);
  return true;
}

function updateSourceBadge() {
  const s = state.source;
  const badge = $('source-badge');
  badge.dataset.kind = s?.info.kind ?? 'replay';
  // A recorded engine run is real engine output, so it is not labelled authored; neither is live.
  $('source-badge-text').textContent =
    s?.info.kind === 'live' ? 'Live simulation' : physicalOnly() ? 'Recording · engine run · not live' : 'Replay · authored fixture · not live';
}

function frameAt(i: number): StateFeedDoc {
  return state.source!.frame(i);
}

/** Positions between two feed frames. The engine interpolates between ~1 Hz ticks the same way. */
function interpolatedAgents(): { agent: Agent; pos: THREE.Vector3; vel: THREE.Vector3 }[] {
  const n = state.source!.frameCount();
  const i = Math.min(Math.floor(state.pos), n - 1);
  const j = Math.min(i + 1, n - 1);
  const t = state.pos - i;
  const a = frameAt(i), b = frameAt(j);
  return a.agents.map((ag) => {
    const nb = b.agents.find((x) => x.id === ag.id && x.scene === ag.scene);
    const p0 = ag.position, p1 = nb?.position ?? p0;
    return {
      agent: ag,
      pos: new THREE.Vector3(p0.x + (p1.x - p0.x) * t, p0.y + (p1.y - p0.y) * t, p0.z + (p1.z - p0.z) * t),
      vel: new THREE.Vector3(ag.velocity.x, ag.velocity.y, ag.velocity.z),
    };
  });
}

/** The scene id to show: the feed's, unless the observer picked one. */
function shownSceneFor(doc: StateFeedDoc): string {
  return state.sceneMode === 'follow' ? doc.scene.id : state.sceneMode;
}

async function syncScene(force = false) {
  if (!state.source || state.switching) return;
  const doc = frameAt(Math.floor(state.pos));
  const want = shownSceneFor(doc);
  if (!force && want === world.currentId) return;
  state.switching = true;
  const wasPlaying = state.playing;
  state.playing = false;
  if (want !== 'open_world' && !force) setStatus('Loading interior level…');
  else if (want !== 'open_world') $('status-text').textContent = 'Loading interior level…';
  try {
    await world.showScene(want);
    app.dataset.scene = world.current;
  } catch (e) {
    setStatus(`This interior could not be loaded: ${e instanceof Error ? e.message : e}`, 'error');
    state.switching = false;
    return;
  }
  if (!force) setStatus(null);
  state.switching = false;
  state.playing = wasPlaying;
}

// ------------------------------------------------------------------ per-frame
let lastT = performance.now();
let minimapClock = 0;
world.onFrame = () => {
  const now = performance.now();
  // Wall-clock time, capped at 1 s so a backgrounded tab does not jump the replay.
  const dt = Math.min((now - lastT) / 1000, 1);
  lastT = now;
  const src = state.source;
  if (!src) return;
  const n = src.frameCount();
  if (state.playing && !state.switching) {
    // Bundles replay at ~1 frame per second (fixtures/README.md); a recorded engine run at its
    // sampling rate (cadenceHz). Both are scaled by the speed control.
    state.pos = Math.min(n - 1, state.pos + dt * state.speed * (src.framesPerSecond?.() ?? 1));
    if (state.pos >= n - 1) { state.playing = false; updatePlayButton(); }
    ($('scrubber') as HTMLInputElement).value = String(state.pos);
  }
  const fi = Math.floor(state.pos);
  const doc = frameAt(fi);
  if (fi !== state.lastFrame) {
    state.lastFrame = fi;
    onFrameChanged(doc);
    void syncScene();
  }

  const agents = interpolatedAgents();
  const shown = world.current;
  const items = agents.map((a) => ({ ...a, visible: sceneKeyFor(a.agent.scene) === shown && !state.switching }));
  world.syncAgents(items, state.selected);

  if (world.followId) {
    const f = items.find((x) => x.agent.id === world.followId && x.visible);
    if (f) world.focusOn(f.pos);
  }

  for (const it of items) {
    let el = labels.get(it.agent.id);
    if (!el) {
      el = document.createElement('div');
      el.className = 'agent-label';
      el.addEventListener('click', () => select(it.agent.id));
      labelLayer.appendChild(el);
      labels.set(it.agent.id, el);
    }
    const anchor = world.residentAnchor(it.agent.id);
    const pr = anchor ? world.project(anchor) : null;
    if (!pr || !pr.visible) { el.style.display = 'none'; continue; }
    el.style.display = '';
    el.style.left = `${pr.x}px`;
    el.style.top = `${pr.y}px`;
    el.classList.toggle('sel', it.agent.id === state.selected);
    el.dataset.role = it.agent.role;
    const html = `<div class="n">${esc(it.agent.name)} <span class="r">${esc(P.roleWord(it.agent.role))}</span></div>` +
      `<div class="s" style="color:${P.stateColour(it.agent.state)}">${P.stateGlyph(it.agent.state)} ${esc(P.stateWord(it.agent.state))}</div>`;
    if (el.dataset.h !== html) { el.innerHTML = html; el.dataset.h = html; }
  }

  declutterLabels();
  minimapClock += dt;
  if (shown === 'open_world' && minimapClock > 0.2) {
    minimapClock = 0;
    minimap.draw(items.filter((x) => x.visible).map((x) => ({ x: x.pos.x, z: x.pos.z, selected: x.agent.id === state.selected, role: x.agent.role })));
  }
  positionBuildingTip();
};

/** Stack name labels that would overlap, nearest-to-ground first, so two agents side by side stay readable. */
function declutterLabels() {
  const placed: DOMRect[] = [];
  const els = [...labels.values()].filter((e) => e.style.display !== 'none');
  els.sort((a, b) => parseFloat(b.style.top) - parseFloat(a.style.top));
  for (const el of els) {
    el.style.transform = '';
    let r = el.getBoundingClientRect();
    let shift = 0;
    for (let guard = 0; guard < 6; guard++) {
      const hit = placed.find((p) => r.left < p.right && r.right > p.left && r.top < p.bottom && r.bottom > p.top);
      if (!hit) break;
      shift += r.bottom - hit.top + 4;
      r = new DOMRect(r.x, r.y - (r.bottom - hit.top + 4), r.width, r.height);
    }
    if (shift) el.style.transform = `translate(-50%, calc(-100% - ${shift}px))`;
    placed.push(r);
  }
}

function onFrameChanged(doc: StateFeedDoc) {
  const n = state.source!.frameCount();
  const fi = Math.floor(state.pos);
  $('frame-label').textContent = `tick ${doc.tick} · frame ${fi + 1}/${n}`;
  const shownScene = sceneKeyFor(shownSceneFor(doc));
  const time = doc.simTimeIso ? new Date(doc.simTimeIso).toISOString().slice(11, 16) : '';
  $('hud-scene').innerHTML = `<strong>${esc(P.sceneName(shownSceneFor(doc)))}</strong>`;
  $('hud-tick').innerHTML = `tick <strong>${doc.tick}</strong>${time ? ` · sim ${time} UTC` : ''}`;
  const note = $('hud-note');
  const inShown = doc.agents.filter((a) => sceneKeyFor(a.scene) === shownScene).length;
  if (inShown === 0) {
    note.hidden = false;
    note.textContent = `Static scene — the feed's agents are in ${P.sceneName(doc.agents[0]?.scene ?? doc.scene.id)}`;
  } else note.hidden = true;
  renderRoster(doc);
  renderInspector(doc);
  renderEvents(doc);
}


// ------------------------------------------------------------------ roster + inspector
function select(id: string | null) {
  state.selected = id;
  if (world.followId && id) world.followId = id;
  if (state.source) {
    const doc = frameAt(Math.floor(state.pos));
    renderRoster(doc);
    renderInspector(doc);
  }
}

function renderRoster(doc: StateFeedDoc) {
  const shown = world.current;
  $('roster-count').textContent = `${doc.agents.length} in this recording`;
  $('roster').innerHTML = doc.agents
    .map((a) => {
      const here = sceneKeyFor(a.scene) === shown;
      return `<li><button class="agent-btn${here ? '' : ' elsewhere'}" data-id="${esc(a.id)}" aria-pressed="${a.id === state.selected}">
        <span class="role-badge" data-role="${esc(a.role)}"><span>${esc(P.roleWord(a.role)[0])}</span></span>
        <span class="agent-text"><span class="agent-name">${esc(a.name)}</span> <span class="agent-sub">${esc(P.roleWord(a.role))} · ${esc(P.sceneName(a.scene))}</span><br>
        <span class="state-pill" style="color:${P.stateColour(a.state)}">${P.stateGlyph(a.state)} ${esc(P.stateWord(a.state))}</span></span>
      </button></li>`;
    })
    .join('');
  $('roster').querySelectorAll<HTMLButtonElement>('.agent-btn').forEach((b) =>
    b.addEventListener('click', () => {
      const id = b.dataset.id!;
      select(state.selected === id ? null : id);
      const a = interpolatedAgents().find((x) => x.agent.id === id);
      if (a && sceneKeyFor(a.agent.scene) === world.current && state.selected) world.focusOn(a.pos, world.current === 'open_world' ? 34 : undefined);
    }),
  );
}

let detailsOpen = !window.matchMedia('(max-width: 700px)').matches;
function renderInspector(doc: StateFeedDoc) {
  const el = $('inspector');
  $('roster-toggle').setAttribute('aria-expanded', String(detailsOpen));
  const panel = $('inspector-panel');
  const a = doc.agents.find((x) => x.id === state.selected);
  if (!a || !detailsOpen) { panel.hidden = true; return; }
  panel.hidden = false;
  if (!a || !detailsOpen) { el.hidden = true; return; }
  el.hidden = false;
  if (physicalOnly()) {
    // No needs, state or readiness in a recorded run: say so, never fill them in.
    const speed = Math.hypot(a.velocity.x, a.velocity.z);
    el.innerHTML = `
      <div class="insp-title"><h3>${esc(a.name)}</h3><span class="muted">${esc(P.roleWord(a.role))} · recorded engine run</span></div>
      <div class="insp-section"><h4>Where</h4><dl class="kv"><dt>Scene</dt><dd>${esc(P.sceneName(a.scene))}</dd><dt>Moving</dt><dd>${speed > 0.05 ? `${speed.toFixed(1)} m/s` : 'standing'}</dd></dl></div>
      <div class="insp-section muted">Physical recording: this file has positions and decisions only. Needs, state and readiness are Fusion's and aren't recorded in it.</div>
      <div class="insp-section muted">Position ${a.position.x.toFixed(1)}, ${a.position.y.toFixed(1)}, ${a.position.z.toFixed(1)} m in ${esc(P.sceneName(a.scene))}</div>`;
    return;
  }
  const needs = ['quiet', 'rest', 'social', 'stimulation']
    .map((k) => {
      const v = a.needs[k] ?? 0;
      return `<span>${P.needLabel(k)}</span><span class="bar need${v < 0.35 ? ' low' : ''}"><i style="width:${(v * 100).toFixed(0)}%"></i></span><span class="muted">${P.needWord(v)}</span>`;
    })
    .join('');
  const met = ['quiet', 'rest', 'social', 'stimulation'].filter((k) => (a.needs[k] ?? 0) >= 0.65).length;
  const levels = Object.entries(a.levels ?? {})
    .map(([k, v]) => `<span>${esc(P.levelLabel(k))}${k === 'independenceScore' ? '<span class="fusion-tag" title="Fusion-owned; display only">·F</span>' : ''}</span><span class="bar"><i style="width:${(v * 100).toFixed(0)}%"></i></span><span class="muted">${P.magnitude(v)}</span>`)
    .join('');
  const pair = doc.pairs.find((p) => p.avatarId === a.id || p.aideId === a.id);
  const gate = pair
    ? `<div class="gate">${pair.ready ? '<strong style="color:var(--pass)">● Ready to fuse</strong>' : '<strong style="color:var(--warn)">◐ Not ready yet</strong>'} · overall ${(pair.overallScore * 100).toFixed(0)}%</div>` +
      (pair.blockingDimensions.length ? `<div class="gate-note">Still building: ${pair.blockingDimensions.map((d) => esc(d.toLowerCase().replace(/_/g, ' '))).join(', ')}</div>` : '') +
      `<div class="gate-note">Readiness is computed by AI-Fusion and shown as received.</div>`
    : '';
  const moreOpen = (el.querySelector('details.more') as HTMLDetailsElement | null)?.open ?? false;
  el.innerHTML = `
    <div class="card-col">
      <div class="insp-title"><h3>${esc(a.name)}</h3><span class="role-tag" data-role="${esc(a.role)}">${esc(P.roleWord(a.role))}</span></div>
      <div class="insp-state" style="color:${P.stateColour(a.state)}">${P.stateGlyph(a.state)} ${esc(P.stateReading(a.state))}</div>
      <div class="insp-since">${esc(P.duration(doc.tick - a.stateSince))}${a.burnout ? ' · <strong style="color:var(--alert)">▲ in burnout</strong>' : ''}</div>
      <div class="insp-section"><h4>Working on</h4><dl class="kv"><dt>Goal</dt><dd>${esc(a.currentGoal || '—')}</dd><dt>Now</dt><dd>${esc(a.currentTask || '—')}</dd></dl></div>
      ${a.struggleSignals.length ? `<div class="insp-section"><h4>Signals Fusion is seeing</h4><div class="tags">${a.struggleSignals.map((s) => `<span class="tag">${esc(P.signalName(s))}</span>`).join('')}</div></div>` : ''}
      ${a.learnedStrategies.length ? `<div class="insp-section"><h4>Strategies kept</h4><div class="tags">${a.learnedStrategies.map((s) => `<span class="tag">${esc(P.strategyName(s))}</span>`).join('')}</div></div>` : ''}
    </div>
    <div class="card-col">
      <div class="insp-section first"><h4>Needs · ${met} of 4 met</h4><div class="bars">${needs}</div></div>
      ${gate ? `<div class="insp-section"><h4>Fusion gate</h4>${gate}</div>` : ''}
      <details class="insp-section more"><summary>Levels &amp; position</summary>
        <div class="bars">${levels}</div>
        <div class="muted pos">${a.position.x.toFixed(1)}, ${a.position.y.toFixed(1)}, ${a.position.z.toFixed(1)} m in ${esc(P.sceneName(a.scene))}</div>
      </details>
    </div>`;
  if (moreOpen) (el.querySelector('details.more') as HTMLDetailsElement).open = true;
}

// ------------------------------------------------------------------ events
const EVENT_GLYPH: Record<string, string> = {
  burnout_entered: '▲', burnout_recovered: '❯', self_recognition: '◆', aide_intervention: '⬢', strategy_internalised: '●',
  task_failed: '□', task_complete: '●', task_start: '▏', scene_enter: '→', scene_exit: '←', struggle_detected: '■', fusion_ready: '★',
  // Recorded engine runs (feed/trace.ts): the agent loop's decisions as the engine logged them.
  decision: '◇', decision_failed: '✕',
};
const EVENT_COLOUR: Record<string, string> = { burnout_entered: '#d55e00', burnout_recovered: '#009e73', self_recognition: '#cc79a7', aide_intervention: '#ebc62a', struggle_detected: '#e69f00', fusion_ready: '#009e73', decision: '#56b4e9', decision_failed: '#d55e00' };
const evKey = (e: FeedEvent) => `${e.tick}|${e.agentId}|${e.kind}`;

function renderEvents(doc: StateFeedDoc) {
  const list = $('events-list');
  const evs = [...doc.events].sort((a, b) => b.tick - a.tick);
  $('events-count').textContent = evs.length ? String(evs.length) : '';
  if (!evs.length) {
    list.innerHTML = `<li class="ev-empty">No events in the feed at this tick.</li>`;
    return;
  }
  const names = new Map(doc.agents.map((a) => [a.id, a.name]));
  list.innerHTML = evs
    .map((e) => {
      const fresh = !state.seenEvents.has(evKey(e));
      const ago = doc.tick - e.tick;
      return `<li class="ev${fresh && state.lastFrame > 0 ? ' new' : ''}"><span class="g" style="color:${EVENT_COLOUR[e.kind] ?? 'var(--dim)'}">${EVENT_GLYPH[e.kind] ?? '•'}</span>
        <span>${esc(e.text)}<div class="meta">${esc(names.get(e.agentId) ?? e.agentId)} · ${esc(P.eventWord(e.kind))} · ${ago <= 0 ? 'just now' : `${ago} ticks ago`}</div></span></li>`;
    })
    .join('');
  evs.forEach((e) => state.seenEvents.add(evKey(e)));
}

function buildTimeline() {
  const src = state.source!;
  const n = src.frameCount();
  const tl = $('timeline');
  const seen = new Map<string, { pos: number; e: FeedEvent }>();
  for (let i = 0; i < n; i++)
    for (const e of src.frame(i).events) if (!seen.has(evKey(e))) seen.set(evKey(e), { pos: i, e });
  tl.innerHTML = [...seen.values()]
    .map(({ pos, e }) => `<i style="left:${n > 1 ? (pos / (n - 1)) * 100 : 0}%;color:${EVENT_COLOUR[e.kind] ?? 'var(--muted)'}" title="${esc(e.text)}">${EVENT_GLYPH[e.kind] ?? '•'}</i>`)
    .join('');
}

// ------------------------------------------------------------------ buildings
let tip: { el: HTMLDivElement; at: THREE.Vector3 } | null = null;
world.onClick = (x, y) => {
  tip?.el.remove();
  tip = null;
  const b = world.pickBuilding(x, y);
  if (!b) return;
  const el = document.createElement('div');
  el.className = 'building-tip';
  el.innerHTML = `<strong>${esc(b.label)}</strong> <span class="muted">building ${b.index + 1} · ${esc(b.sceneId)}</span><br><button class="chip">View inside (static scene)</button>`;
  el.querySelector('button')!.addEventListener('click', () => {
    setSceneMode(b.sceneId);
    tip?.el.remove();
    tip = null;
  });
  app.appendChild(el);
  tip = { el, at: b.door.clone().add(new THREE.Vector3(0, 3.4, 0)) };
  positionBuildingTip();
};
function positionBuildingTip() {
  if (!tip) return;
  const p = world.project(tip.at);
  tip.el.style.display = p.visible && world.current === 'open_world' ? '' : 'none';
  tip.el.style.left = `${p.x}px`;
  tip.el.style.top = `${p.y}px`;
}

// ------------------------------------------------------------------ controls
function updatePlayButton() {
  const b = $('btn-play');
  b.textContent = state.playing ? '⏸' : '▶';
  b.setAttribute('aria-label', state.playing ? 'Pause' : 'Play');
}
function togglePlay() {
  if (!state.source) return;
  if (!state.playing && state.pos >= state.source.frameCount() - 1) state.pos = 0;
  state.playing = !state.playing;
  updatePlayButton();
}
function step(d: number) {
  if (!state.source) return;
  state.playing = false;
  updatePlayButton();
  state.pos = Math.max(0, Math.min(state.source.frameCount() - 1, Math.round(state.pos) + d));
  ($('scrubber') as HTMLInputElement).value = String(state.pos);
}
function setSceneMode(mode: string) {
  state.sceneMode = mode;
  const sel = $('scene-select') as HTMLSelectElement;
  if (![...sel.options].some((o) => o.value === mode)) sel.add(new Option(`${P.sceneName(mode)} (interior)`, mode));
  sel.value = mode;
  state.lastFrame = -1; // refresh HUD + roster
  void syncScene(true).then(() => setStatus(null));
}

$('btn-play').addEventListener('click', togglePlay);
$('btn-back').addEventListener('click', () => step(-1));
$('btn-fwd').addEventListener('click', () => step(1));
($('scrubber') as HTMLInputElement).addEventListener('input', (e) => {
  state.playing = false;
  updatePlayButton();
  state.pos = Number((e.target as HTMLInputElement).value);
});
($('speed') as HTMLSelectElement).addEventListener('change', (e) => (state.speed = Number((e.target as HTMLSelectElement).value)));
($('scene-select') as HTMLSelectElement).addEventListener('change', (e) => setSceneMode((e.target as HTMLSelectElement).value));
const replaySel = $('replay-select') as HTMLSelectElement;
const TRACE_OPT = 'trace:sample';
const FILE_OPT = 'trace:file';
const LOCAL_OPT = 'trace:local';
replaySel.innerHTML =
  `<optgroup label="Authored fixtures">${REPLAYS.map((r) => `<option value="${r.id}">${esc(r.label)}</option>`).join('')}</optgroup>` +
  `<optgroup label="Recorded engine runs"><option value="${TRACE_OPT}">${esc(TRACE_SAMPLE.label)}</option><option value="${FILE_OPT}">Open a recording file…</option></optgroup>`;

// A recording file (nlt.observer-trace.v1 .jsonl) is read in the browser and sent nowhere.
const fileInput = document.createElement('input');
fileInput.type = 'file';
fileInput.accept = '.jsonl,.json,.txt';
fileInput.hidden = true;
fileInput.setAttribute('aria-label', 'Open a recorded engine run (.jsonl)');
document.body.appendChild(fileInput);
let lastChoice = replaySel.value;
// The last file opened, kept so its menu entry can reopen it after another recording was shown.
let localFile: { name: string; text: string } | null = null;
function showLocalChoice(name: string) {
  let opt = replaySel.querySelector<HTMLOptionElement>(`option[value="${LOCAL_OPT}"]`);
  if (!opt) {
    opt = new Option('', LOCAL_OPT);
    replaySel.querySelector('optgroup:last-of-type')!.insertBefore(opt, replaySel.querySelector(`option[value="${FILE_OPT}"]`));
  }
  opt.textContent = `File: ${name}`;
  replaySel.value = lastChoice = LOCAL_OPT;
}
async function openLocal(name: string, text: string) {
  state.sceneMode = 'follow';
  ($('scene-select') as HTMLSelectElement).value = 'follow';
  if (!(await openSource(new TraceSource({ kind: 'text', text, name }, name), name, null))) return;
  localFile = { name, text };
  showLocalChoice(name);
}
async function openTraceFile(f: File) {
  await openLocal(f.name, await f.text());
}
fileInput.addEventListener('change', () => {
  const f = fileInput.files?.[0];
  fileInput.value = '';
  if (f) void openTraceFile(f);
});
replaySel.addEventListener('change', () => {
  if (replaySel.value === FILE_OPT) {
    replaySel.value = lastChoice; // stay on what is shown until a file is actually chosen
    fileInput.click();
    return;
  }
  if (replaySel.value === LOCAL_OPT) {
    if (localFile) void openLocal(localFile.name, localFile.text);
    return;
  }
  lastChoice = replaySel.value;
  state.sceneMode = 'follow';
  ($('scene-select') as HTMLSelectElement).value = 'follow';
  if (replaySel.value === TRACE_OPT) void openSource(new TraceSource({ kind: 'url', url: TRACE_SAMPLE.url }, TRACE_SAMPLE.label), TRACE_SAMPLE.label, '?trace=sample');
  else void openReplay(replaySel.value);
});
// Drop a recording anywhere on the view to open it.
window.addEventListener('dragover', (e) => {
  if (!e.dataTransfer?.types.includes('Files')) return;
  e.preventDefault();
  e.dataTransfer.dropEffect = 'copy';
  app.classList.add('drop-target');
});
window.addEventListener('dragleave', (e) => { if (e.relatedTarget === null) app.classList.remove('drop-target'); });
window.addEventListener('drop', (e) => {
  app.classList.remove('drop-target');
  const f = e.dataTransfer?.files?.[0];
  if (!f) return;
  e.preventDefault();
  void openTraceFile(f);
});
const followBtn = $('btn-follow');
followBtn.addEventListener('click', () => {
  world.followId = world.followId ? null : state.selected;
  followBtn.setAttribute('aria-pressed', String(!!world.followId));
});
setInterval(() => followBtn.setAttribute('aria-pressed', String(!!world.followId)), 500);
$('btn-reset').addEventListener('click', () => { world.followId = null; world.resetCamera(); });
const lookSel = $('look') as HTMLSelectElement;
lookSel.addEventListener('change', () => world.setLook(lookSel.value as 'golden' | 'midday'));
const qualitySel = $('quality') as HTMLSelectElement;
const qParam = params.get('quality');
if (qParam === 'fast' || qParam === 'high') world.setQuality(qParam);
const lParam = params.get('look');
if (lParam === 'golden' || lParam === 'midday') { world.setLook(lParam); lookSel.value = lParam; }
qualitySel.value = world.quality;
qualitySel.addEventListener('change', () => world.setQuality(qualitySel.value as 'high' | 'fast'));
const rm = $('reduced-motion') as HTMLInputElement;
rm.checked = window.matchMedia('(prefers-reduced-motion: reduce)').matches;
world.reducedMotion = rm.checked;
rm.addEventListener('change', () => (world.reducedMotion = rm.checked));
$('roster-toggle').addEventListener('click', () => {
  detailsOpen = !detailsOpen;
  if (state.source) renderInspector(frameAt(Math.floor(state.pos)));
});
const evToggle = $('events-toggle');
evToggle.addEventListener('click', () => {
  const open = evToggle.getAttribute('aria-expanded') !== 'true';
  evToggle.setAttribute('aria-expanded', String(open));
  $('events-list').hidden = !open;
});
window.addEventListener('keydown', (e) => {
  if ((e.target as HTMLElement)?.closest?.('input,select,textarea,dialog')) return;
  if (e.key === ' ') { e.preventDefault(); togglePlay(); }
  else if (e.key === ',' || e.key === '[') step(-1);
  else if (e.key === '.' || e.key === ']') step(1);
  else if (e.key === 'Escape') { tip?.el.remove(); tip = null; }
});

// ------------------------------------------------------------------ about / provenance
const about = $('about') as HTMLDialogElement;
function openAbout() {
  const s = state.source;
  const diag = s?.diagnostics() ?? [];
  $('about-body').innerHTML = `
    <p>A spectator window onto the <strong>NLT World Engine</strong>: a persistent island where AI Avatars, Aides and Advocates live, move and work through scenarios. The engine itself is a Godot 4.7 (C#) desktop application; this page is a separate browser projection of it.</p>
    <h3>Where each thing on screen comes from</h3>
    <table>
      <tr><td>Island, settlement, trees</td><td><strong>Static scene data.</strong> Rebuilt in your browser from the World Engine's own builders (WorldGeometry, TerrainBuilder, SettlementBuilder, BuildingArchetypes, VegetationBuilder), same seed ${SEED}. Not rendered by Godot. Sky and lighting are an approximation of Godot's Sky3D.</td></tr>
      <tr><td>Interiors</td><td><strong>Static scene data.</strong> The project-owned level files Godot loads (assets/levels/*.fbx). Per-building colour schemes (InteriorStyle) are not ported.</td></tr>
      ${
        s?.info.content === 'physical-trace'
          ? `<tr><td>Agents and decisions</td><td><strong>${esc(s.info.provenance)}.</strong> ${esc(s.info.title)}. ${esc(s.info.detail ?? '')} The panels show no needs, states or readiness for this recording.</td></tr>`
          : `<tr><td>Agents, states, events</td><td><strong>${esc(s?.info.provenance ?? '—')}.</strong> ${esc(s?.info.title ?? '')} — nlt.state-feed.v1 frames from world-engine-godot/fixtures/replay. ${esc(s?.info.detail ?? '')}</td></tr>`
      }
      <tr><td>Resident figure</td><td>The self-authored pipeline-probe character Godot uses (deliberately primitive), with its walk cycle. It plays only while the feed says the agent is moving.</td></tr>
      <tr><td>Live simulation</td><td><strong>Unavailable.</strong> ${esc(live.info.detail ?? '')}</td></tr>
    </table>
    <h3>Responsibilities</h3>
    <p>Godot owns physical reality. AI-Fusion owns semantic reality — states, needs, readiness. This viewer only draws what a feed says; it never simulates, and it never computes Fusion's numbers.</p>
    <h3>Controls</h3>
    <p>Drag to orbit · scroll or pinch to zoom · W A S D / arrows to pan · click a building for its doorway · Space plays and pauses · , and . step frames.</p>
    ${diag.length ? `<h3>Feed diagnostics</h3><div class="diag">${diag.map(esc).join('<br>')}</div>` : ''}
    <p class="muted">Recorded engine runs (nlt.observer-trace.v1) can be opened here from the Recording menu or by dropping the .jsonl file on the view; <a href="./trace.html" style="color:var(--accent)">trace.html</a> shows the same file as a top-down plot with every decision.</p>`;
  about.showModal();
}
['about-btn', 'source-badge', 'live-btn'].forEach((id) => $(id).addEventListener('click', openAbout));
$('about-close').addEventListener('click', () => about.close());

// ------------------------------------------------------------------ run control
// Asks /api/run to start or stop an engine run. It does not change what the view shows.
initRunControl($<HTMLButtonElement>('run-btn'), (message) => {
  $('run-status').textContent = message;
});

// ------------------------------------------------------------------ go
try {
  await world.loadResidentModel('godot/characters/nlt_resident_walk.glb');
} catch (e) {
  console.warn('Resident model unavailable; using a plain marker.', e);
}
const initial = params.get('replay') ?? 'open-world-day';
replaySel.value = REPLAYS.some((r) => r.id === initial) ? initial : REPLAYS[0].id;
const sceneParam = params.get('scene');
if (sceneParam && /^(open_world|(personal|workplace|social|academic)_\d+)$/.test(sceneParam)) setSceneMode(sceneParam);
if (params.get('trace') === 'sample') {
  replaySel.value = lastChoice = TRACE_OPT;
  await openSource(new TraceSource({ kind: 'url', url: TRACE_SAMPLE.url }, TRACE_SAMPLE.label), TRACE_SAMPLE.label, null);
} else {
  lastChoice = replaySel.value;
  await openReplay(replaySel.value);
}
if (params.get('about') === '1') openAbout();
if (params.has('debug')) (window as unknown as Record<string, unknown>).__nlt = { world, state };
