// Trace data model for nlt.observer-trace.v1.
// Mirrors docs/contracts/observer-trace-v1.md, which is the source of truth. The
// producer is world-engine-godot/Observer/Trace/ObserverTrace.cs.

export const SCHEMA_VERSION = 'nlt.observer-trace.v1';

export type Stage = 'protocol' | 'governance' | 'physical' | 'accepted';

export type RecordKind =
  | 'tick'
  | 'perception_sent'
  | 'intent'
  | 'result'
  | 'decision_failed'
  | 'scene_transition'
  | 'scene_entities'
  | 'unknown';

export interface TraceHeader {
  schemaVersion: string;
  runId: string;
  engineCommit: string;
  godotVersion: string;
  startTime: string;
  agentRoster: string[];
  cadenceHz: number;
  // Tolerate unknown keys: captured verbatim.
  [key: string]: unknown;
}

export interface SceneRef {
  id: string;
  kind: string;
}

export interface Position3 {
  x: number;
  y: number;
  z: number;
}

export interface TickRecord {
  kind: 'tick';
  tick: number;
  agentId: string;
  scene: SceneRef;
  position: Position3;
  velocity: Position3;
}

export interface PerceptionSentRecord {
  kind: 'perception_sent';
  tick: number;
  agentId: string;
}

export interface IntentRecord {
  kind: 'intent';
  messageId: string;
  agentId: string;
  observedTick: number;
  verb: string;
  targetId?: string;
  ticksBehind?: number;
  decisionMs?: number;
}

export interface ResultRecord {
  kind: 'result';
  intentMessageId: string;
  status: string;
  reason?: string;
  stage: Stage;
  governanceCode?: string;
  // Added in v1 over the draft; absent in older traces.
  agentId?: string;
  tick?: number;
}

export interface DecisionFailedRecord {
  kind: 'decision_failed';
  agentId: string;
  tick: number;
  httpStatus?: number;
  error?: string;
}

export interface SceneTransitionRecord {
  kind: 'scene_transition';
  agentId: string;
  from: string;
  to: string;
  tick: number;
}

export interface SceneEntity {
  id: string;
  kind: string;
  position: Position3;
  affordances: string[];
}

export interface SceneEntitiesRecord {
  kind: 'scene_entities';
  scene: string;
  entities: SceneEntity[];
}

export interface UnknownRecord {
  kind: 'unknown';
  line: number;
  raw: any;
  reason: string;
}

export type ParsedRecord =
  | TickRecord
  | PerceptionSentRecord
  | IntentRecord
  | ResultRecord
  | DecisionFailedRecord
  | SceneTransitionRecord
  | SceneEntitiesRecord
  | UnknownRecord;

export interface ParsedTrace {
  header: TraceHeader;
  records: ParsedRecord[];
  errors: string[];
}

export interface AgentState {
  agentId: string;
  scene: SceneRef;
  position: Position3;
  velocity: Position3;
  lastTick: number;
}

export interface IntentState extends IntentRecord {
  lastTick: number;
}

export interface ResultState extends ResultRecord {
  lastTick: number;
}

export interface FailureState extends DecisionFailedRecord {}

export interface TransitionState extends SceneTransitionRecord {}

export interface SliceState {
  tick: number;
  agents: Map<string, AgentState>;
  intents: Map<string, IntentState>;
  results: Map<string, ResultState>;
  failures: FailureState[];
  transitions: TransitionState[];
  entitiesByScene: Map<string, SceneEntity[]>;
  unrecognized: UnknownRecord[];
}

export interface IntentRow {
  messageId: string;
  agentId: string;
  tick: number;
  verb: string;
  targetId?: string;
  resultStage?: Stage;
  governanceCode?: string;
  status?: string;
  reason?: string;
  ticksBehind?: number;
  decisionMs?: number;
  hasResult: boolean;
}

export interface SummaryStats {
  acceptedByStage: Record<Stage, number>;
  rejectedByStage: Record<Stage, number>;
  failuresByStatus: Record<string, number>;
  totalIntents: number;
  totalResults: number;
  totalFailures: number;
  totalTransitions: number;
}
