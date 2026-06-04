# World Engine Contract v1 Draft

This directory defines a provider-neutral transport and replay contract for the
NLT Fusion World Engine.

**Status:** Draft. It does not select a database, network transport, game engine,
LLM provider, or learned world model.

## Files

- `common.schema.json` - shared identifiers, clocks, metrics, positions, and sources
- `snapshot.schema.json` - complete saveable simulation state
- `action.schema.json` - intent submitted by a human, agent, aide, or engine
- `event.schema.json` - ordered fact emitted by the simulation
- `intervention.schema.json` - structured Aide coaching record
- `replay.schema.json` - initial state, ordered records, and expected final state
- `../examples/stay-alert-coaching.replay.json` - deterministic reference replay

## Design Rules

1. The deterministic simulation owns truth. Renderers and model adapters consume
   snapshots and events.
2. Snapshot collections are keyed by stable IDs. Browser arrays can be converted
   with `Object.fromEntries(items.map(item => [item.id, item]))`.
3. Normalized metrics use the inclusive `0..1` range.
4. Unknown implementation-specific data belongs under `extensions`.
5. Replays use ordered events with explicit `state_changes`. These are audit and
   verification records, not a recommendation that the production engine must use
   JSON-pointer mutation internally.
6. A replay hash is SHA-256 over the canonical expected final snapshot:
   sorted object keys, no insignificant whitespace, and UTF-8 encoding.

## Life Sim v1 (browser)

The browser prototype implements a minimal life-simulation loop:

- **Objects** with affordances (`work`, `rest`, `meet`, …) on the lot (`data.js` → `OBJECTS`)
- **Motives** including `energy` plus focus / stress / cognitive load
- **Flow:** walk to object → `INTERACTION_STARTED` / `USE_OBJECT` → scenario task → complete
- **Actions (contract):** `move_to`, `use_object`, `rest`, `assign_scenario`

Genre packs (city builder, open-world RPG) can reuse the same action/event surface with different object and scenario catalogs.

## Compatibility Targets

- Browser prototype: `world-engine/data.js` and `world-engine/sim.jsx`
- Product shell: `studio/`
- Python event bus and session concepts: `world-engine/src/`

The contract intentionally captures their shared surface while leaving richer ECS,
controller, and model-specific state in `extensions`.

## Human-Centered Constraint

The schemas describe simulation records, not clinical truth. Behavior, coaching
effectiveness, and fusion readiness must remain reviewable, evidence-linked, and
clearly labeled as simulated or inferred.
