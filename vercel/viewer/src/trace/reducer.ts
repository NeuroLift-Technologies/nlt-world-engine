import type {
  ParsedRecord,
  SliceState,
  AgentState,
  IntentState,
  ResultState,
  FailureState,
  TransitionState,
  IntentRecord,
  ResultRecord,
  DecisionFailedRecord,
  SceneTransitionRecord,
  SceneEntity,
  TickRecord,
  SceneEntitiesRecord,
  UnknownRecord,
} from './types.js';

// Pure reducer: reconstruct the viewer's slice of simulation state at tick N
// from the full record list. Does not mutate inputs; returns a fresh state.

function latestAtOrBefore<T>(records: T[], tick: number, tickOf: (r: T) => number): T | undefined {
  let best: T | undefined;
  let bestTick = -1;
  for (const r of records) {
    const t = tickOf(r);
    if (t <= tick && t > bestTick) {
      best = r;
      bestTick = t;
    }
  }
  return best;
}

export function reduce(records: ParsedRecord[], tick: number): SliceState {
  const ticks = records.filter((r): r is TickRecord => r.kind === 'tick');
  const intents = records.filter((r): r is IntentRecord => r.kind === 'intent');
  const results = records.filter((r): r is ResultRecord => r.kind === 'result');
  const failures = records.filter((r): r is DecisionFailedRecord => r.kind === 'decision_failed');
  const transitions = records.filter((r): r is SceneTransitionRecord => r.kind === 'scene_transition');
  const entityRecords = records.filter((r): r is SceneEntitiesRecord => r.kind === 'scene_entities');
  const unrecognized = records.filter((r): r is UnknownRecord => r.kind === 'unknown');

  // Latest tick record per agent at or before tick.
  const agents = new Map<string, AgentState>();
  const agentIds = new Set(ticks.map((t) => t.agentId));
  for (const agentId of agentIds) {
    const latest = latestAtOrBefore(ticks.filter((t) => t.agentId === agentId), tick, (t) => t.tick);
    if (latest) {
      agents.set(agentId, {
        agentId,
        scene: latest.scene,
        position: latest.position,
        velocity: latest.velocity,
        lastTick: latest.tick,
      });
    }
  }

  // Latest intent per agent at or before tick.
  const intentMap = new Map<string, IntentState>();
  const intentAgentIds = new Set(intents.map((i) => i.agentId));
  for (const agentId of intentAgentIds) {
    const latest = latestAtOrBefore(intents.filter((i) => i.agentId === agentId), tick, (i) => i.observedTick);
    if (latest) {
      intentMap.set(agentId, { ...latest, lastTick: latest.observedTick });
    }
  }

  // Attribute results to agents via intent.messageId. A result may arrive before
  // or after its intent in record order, so index all results by message id.
  const resultByMessage = new Map<string, ResultRecord>();
  for (const r of results) {
    resultByMessage.set(r.intentMessageId, r);
  }
  const resultMap = new Map<string, ResultState>();
  for (const [agentId, intent] of intentMap) {
    const result = resultByMessage.get(intent.messageId);
    if (result) {
      resultMap.set(agentId, { ...result, lastTick: intent.lastTick });
    }
  }

  // Failures at or before tick (each failure carries its own tick).
  const failuresAtTick = failures.filter((f) => f.tick <= tick);

  // Transitions occurring exactly at tick (instantaneous scene change).
  const transitionsAtTick = transitions.filter((t) => t.tick === tick);

  // Scene entities: latest scene_entities record per scene (no tick field;
  // keep the last one encountered in record order).
  const entitiesByScene = new Map<string, SceneEntity[]>();
  for (const er of entityRecords) {
    entitiesByScene.set(er.scene, er.entities);
  }

  return {
    tick,
    agents,
    intents: intentMap,
    results: resultMap,
    failures: failuresAtTick,
    transitions: transitionsAtTick,
    entitiesByScene,
    unrecognized: unrecognized.map((u) => ({
      kind: 'unknown',
      line: u.line,
      raw: u.raw,
      reason: u.reason,
    })),
  };
}
