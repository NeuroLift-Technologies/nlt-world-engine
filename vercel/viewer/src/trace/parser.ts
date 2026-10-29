import { SCHEMA_VERSION } from './types.js';
import type {
  ParsedTrace,
  TraceHeader,
  ParsedRecord,
  UnknownRecord,
  RecordKind,
  Stage,
  TickRecord,
  PerceptionSentRecord,
  IntentRecord,
  ResultRecord,
  DecisionFailedRecord,
  SceneTransitionRecord,
  SceneEntitiesRecord,
} from './types.js';

const KNOWN_KINDS: Record<string, RecordKind> = {
  tick: 'tick',
  perception_sent: 'perception_sent',
  intent: 'intent',
  result: 'result',
  decision_failed: 'decision_failed',
  scene_transition: 'scene_transition',
  scene_entities: 'scene_entities',
};

function isObject(value: unknown): value is Record<string, unknown> {
  return typeof value === 'object' && value !== null && !Array.isArray(value);
}

function asNumber(value: unknown, fallback: number): number {
  const n = Number(value);
  return Number.isFinite(n) ? n : fallback;
}

function asString(value: unknown, fallback: string): string {
  return typeof value === 'string' ? value : fallback;
}

function asPosition(value: unknown): { x: number; y: number; z: number } {
  const obj = isObject(value) ? value : {};
  return {
    x: asNumber(obj.x, 0),
    y: asNumber(obj.y, 0),
    z: asNumber(obj.z, 0),
  };
}

function asScene(value: unknown): { id: string; kind: string } {
  const obj = isObject(value) ? value : {};
  return { id: asString(obj.id, ''), kind: asString(obj.kind, '') };
}

function asEntity(value: unknown): { id: string; kind: string; position: { x: number; y: number; z: number }; affordances: string[] } {
  const obj = isObject(value) ? value : {};
  const aff = Array.isArray(obj.affordances)
    ? obj.affordances.filter((a): a is string => typeof a === 'string')
    : [];
  return {
    id: asString(obj.id, ''),
    kind: asString(obj.kind, ''),
    position: asPosition(obj.position),
    affordances: aff,
  };
}

function parseHeader(line: string, lineNo: number): { header: TraceHeader; error?: string } {
  let parsed: any;
  try {
    parsed = JSON.parse(line);
  } catch {
    return {
      header: {
        schemaVersion: '',
        runId: '',
        engineCommit: '',
        godotVersion: '',
        startTime: '',
        agentRoster: [],
        cadenceHz: 0,
      },
      error: `Line ${lineNo}: header is not valid JSON`,
    };
  }

  if (!isObject(parsed)) {
    return {
      header: {
        schemaVersion: '',
        runId: '',
        engineCommit: '',
        godotVersion: '',
        startTime: '',
        agentRoster: [],
        cadenceHz: 0,
      },
      error: `Line ${lineNo}: header must be a JSON object`,
    };
  }

  const header: TraceHeader = {
    schemaVersion: asString(parsed.schemaVersion, ''),
    runId: asString(parsed.runId, ''),
    engineCommit: asString(parsed.engineCommit, ''),
    godotVersion: asString(parsed.godotVersion, ''),
    startTime: asString(parsed.startTime, ''),
    agentRoster: Array.isArray(parsed.agentRoster)
      ? parsed.agentRoster.filter((a): a is string => typeof a === 'string')
      : [],
    cadenceHz: asNumber(parsed.cadenceHz, 0),
  };

  // Carry through any unknown keys so nothing is silently dropped.
  for (const [key, value] of Object.entries(parsed)) {
    if (!(key in header)) {
      header[key] = value;
    }
  }

  return { header };
}

function classifyKind(value: unknown): RecordKind {
  if (typeof value !== 'string') return 'unknown';
  return KNOWN_KINDS[value] ?? 'unknown';
}

function parseRecord(line: string, lineNo: number): ParsedRecord {
  let parsed: any;
  try {
    parsed = JSON.parse(line);
  } catch {
    return {
      kind: 'unknown',
      line: lineNo,
      raw: line,
      reason: 'not valid JSON',
    };
  }

  if (!isObject(parsed)) {
    return { kind: 'unknown', line: lineNo, raw: parsed, reason: 'record is not a JSON object' };
  }

  const kind = classifyKind(parsed.type);

  if (kind === 'unknown') {
    return {
      kind: 'unknown',
      line: lineNo,
      raw: parsed,
      reason: `unknown record type ${asString(parsed.type, '<missing>')}`,
    };
  }

  switch (kind) {
    case 'tick': {
      return {
        kind: 'tick',
        tick: asNumber(parsed.tick, -1),
        agentId: asString(parsed.agentId, ''),
        scene: asScene(parsed.scene),
        position: asPosition(parsed.position),
        velocity: asPosition(parsed.velocity),
      } as TickRecord;
    }
    case 'perception_sent': {
      return {
        kind: 'perception_sent',
        tick: asNumber(parsed.tick, -1),
        agentId: asString(parsed.agentId, ''),
      } as PerceptionSentRecord;
    }
    case 'intent': {
      return {
        kind: 'intent',
        messageId: asString(parsed.messageId, ''),
        agentId: asString(parsed.agentId, ''),
        observedTick: asNumber(parsed.observedTick, -1),
        verb: asString(parsed.verb, ''),
        targetId: typeof parsed.targetId === 'string' ? parsed.targetId : undefined,
        ticksBehind:
          typeof parsed.ticksBehind === 'number'
            ? parsed.ticksBehind
            : typeof parsed.ticksBehind === 'string'
              ? asNumber(parsed.ticksBehind, NaN)
              : undefined,
        decisionMs:
          typeof parsed.decisionMs === 'number'
            ? parsed.decisionMs
            : typeof parsed.decisionMs === 'string'
              ? asNumber(parsed.decisionMs, NaN)
              : undefined,
      } as IntentRecord;
    }
    case 'result': {
      return {
        kind: 'result',
        intentMessageId: asString(parsed.intentMessageId, ''),
        status: asString(parsed.status, ''),
        reason: typeof parsed.reason === 'string' ? parsed.reason : undefined,
        stage: (parsed.stage as Stage) ?? 'accepted',
        governanceCode:
          typeof parsed.governanceCode === 'string' ? parsed.governanceCode : undefined,
      } as ResultRecord;
    }
    case 'decision_failed': {
      const httpStatus =
        typeof parsed.httpStatus === 'number'
          ? parsed.httpStatus
          : typeof parsed.httpStatus === 'string'
            ? asNumber(parsed.httpStatus, NaN)
            : undefined;
      return {
        kind: 'decision_failed',
        agentId: asString(parsed.agentId, ''),
        tick: asNumber(parsed.tick, -1),
        httpStatus: Number.isFinite(httpStatus ?? NaN) ? httpStatus : undefined,
        error: typeof parsed.error === 'string' ? parsed.error : undefined,
      } as DecisionFailedRecord;
    }
    case 'scene_transition': {
      return {
        kind: 'scene_transition',
        agentId: asString(parsed.agentId, ''),
        from: asString(parsed.from, ''),
        to: asString(parsed.to, ''),
        tick: asNumber(parsed.tick, -1),
      } as SceneTransitionRecord;
    }
    case 'scene_entities': {
      const entities = Array.isArray(parsed.entities)
        ? parsed.entities.map(asEntity)
        : [];
      return {
        kind: 'scene_entities',
        scene: asString(parsed.scene, ''),
        entities,
      } as SceneEntitiesRecord;
    }
    default: {
      return { kind: 'unknown', line: lineNo, raw: parsed, reason: 'unhandled kind' };
    }
  }
}

export function parseTrace(text: string): ParsedTrace {
  const errors: string[] = [];
  const lines = text.split(/\r?\n/);

  if (lines.length === 0) {
    errors.push('Trace is empty.');
    return {
      header: {
        schemaVersion: '',
        runId: '',
        engineCommit: '',
        godotVersion: '',
        startTime: '',
        agentRoster: [],
        cadenceHz: 0,
      },
      records: [],
      errors,
    };
  }

  const headerResult = parseHeader(lines[0], 1);
  if (headerResult.error) {
    errors.push(headerResult.error);
  }
  const header = headerResult.header;

  // Fail LOUDLY on unknown schemaVersion.
  if (header.schemaVersion !== SCHEMA_VERSION) {
    errors.push(
      `Unsupported schemaVersion "${header.schemaVersion}". Viewer supports ${SCHEMA_VERSION} only.`,
    );
  }

  const records: ParsedRecord[] = [];
  for (let i = 1; i < lines.length; i++) {
    const line = lines[i];
    if (line.trim() === '') continue;
    records.push(parseRecord(line, i + 1));
  }

  return { header, records, errors };
}
