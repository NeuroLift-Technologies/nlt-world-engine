// Port of world-engine-godot/Observer/PlainLanguage.cs — the observer's vocabulary.
export const stateWord = (s: string) => ({ settled: 'Settled', drifting: 'Drifting', resisting: 'Resisting', hyperfocus: 'Locked in', overwhelmed: 'Overwhelmed', recovering: 'Recovering', coached: 'Being coached' } as Record<string, string>)[s] ?? (s ? s[0].toUpperCase() + s.slice(1) : 'Unknown');
export const stateReading = (s: string) => ({ settled: 'Settled — managing the task', drifting: "Drifting — hasn't really started", resisting: 'Resisting — aware of it, not starting', hyperfocus: 'Locked in — attention on one thing', overwhelmed: 'Overwhelmed — more than they can hold', recovering: 'Recovering — working their way back', coached: 'Being coached — the Aide is stepping in' } as Record<string, string>)[s] ?? stateWord(s);
/** Shape channel, so state never rests on colour alone. */
export const stateGlyph = (s: string) => ({ settled: '●', drifting: '▼', resisting: '■', hyperfocus: '◆', overwhelmed: '▲', recovering: '❯', coached: '⬢' } as Record<string, string>)[s] ?? '▬';
export const stateColour = (s: string) => ({ settled: '#009e73', drifting: '#e69f00', resisting: '#d55e00', hyperfocus: '#0072b2', overwhelmed: '#cc79a7', recovering: '#56b4e9', coached: '#ebc62a' } as Record<string, string>)[s] ?? '#74838f';
export const needWord = (v: number) => (v < 0.35 ? 'not met' : v < 0.65 ? 'partly met' : 'met');
export const needLabel = (k: string) => ({ quiet: 'Quiet', rest: 'Rest', social: 'Company', stimulation: 'Stimulation' } as Record<string, string>)[k] ?? k;
export const levelLabel = (k: string) => ({ attentionEnergy: 'Attention', stressLevel: 'Stress', confidence: 'Confidence', cognitiveLoad: 'Mental load', independenceScore: 'Independence', supportNeedLevel: 'Support wanted' } as Record<string, string>)[k] ?? k;
export const magnitude = (v: number) => (v < 0.35 ? 'low' : v < 0.65 ? 'mid' : 'high');
export const roleWord = (r: string) => ({ avatar: 'Avatar', aide: 'Aide', advocate: 'Advocate' } as Record<string, string>)[r] ?? r;
export const strategyName = (id: string) => ({ body_doubling: 'working alongside someone', time_box_25: '25-minute time box', reset_prompt: 'reset prompt', task_chunking: 'breaking it into steps', environmental_simplification: 'tidying the space first' } as Record<string, string>)[id] ?? id.replace(/_/g, ' ');
export const signalName = (id: string) => ({ sustained_attention_dip: 'attention keeps slipping', task_drift: 'drifting off the task', time_pressure: 'under time pressure', overload: 'more than they can hold' } as Record<string, string>)[id] ?? id.replace(/_/g, ' ');
export const eventWord = (k: string) => ({ scene_enter: 'arrived', scene_exit: 'left', task_start: 'started a task', task_complete: 'finished a task', task_failed: 'task did not get done', struggle_detected: 'got stuck', aide_intervention: 'the Aide stepped in', strategy_internalised: 'kept a strategy', self_recognition: 'noticed their own state', burnout_entered: 'burnout', burnout_recovered: 'recovered', fusion_ready: 'ready to fuse' } as Record<string, string>)[k] ?? k.replace(/_/g, ' ');
export const sceneName = (id: string) => {
  if (id === 'open_world') return 'Open world';
  const [p, n] = id.split('_');
  const base = ({ personal: 'Home', workplace: 'Workplace', social: 'Social', academic: 'School' } as Record<string, string>)[p] ?? p;
  return n && n !== '1' ? `${base} ${n}` : base;
};
/** PlainLanguage.Duration — ticks are ~1 Hz (contract header). */
export function duration(ticks: number): string {
  if (ticks <= 0) return 'just started';
  if (ticks < 60) return `for about ${ticks} seconds`;
  const mins = ticks / 60;
  return mins < 10 ? `for about ${Math.round(mins * 10) / 10} minutes` : `for about ${Math.round(mins)} minutes`;
}
