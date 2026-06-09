"""
Sims-world demo: an AI agent living a day in the environment.

Run it:

    cd world-engine
    python3 demo.py

A `UtilityAgent` (classic Sims-style AI: satisfy the most pressing need)
perceives the world, decides, and acts purely through `AgentInterface` —
the same seam an LLM-driven agent would use. Swap `UtilityAgent.decide`
for a model call and nothing in the engine changes; decisions stay outside
the deterministic tick.
"""

from typing import Dict, Any, List, Optional

from src.simulation.environment.world_engine import WorldEngine, EventType
from src.simulation.environment.world_builder import (
    build_world, engine_for_spec, DEFAULT_NEEDS, DEFAULT_HOME_SPEC,
)
from src.simulation.environment.agent_interface import AgentInterface
from src.simulation.environment.ecs import Needs


class UtilityAgent:
    """
    Minimal cognitive layer: look at my needs, find the visible object that
    best restores the most pressing one, walk over, use it.

    This is the seam for real AI — `decide()` receives the same observation
    dict an LLM would, and returns a plan. Nothing else touches the world.
    """

    def __init__(self, interface: AgentInterface):
        self.interface = interface
        self.plan: Optional[Dict[str, Any]] = None  # {"target_id", "affordance", "phase"}

    def decide(self, needs: Dict[str, float],
               surroundings: List[Dict[str, Any]]) -> Optional[Dict[str, Any]]:
        """Pick the (object, affordance) that best restores the lowest need."""
        if not needs:
            return None
        pressing = min(needs, key=lambda need: needs[need])
        if needs[pressing] > 0.55:
            return None  # Comfortable; idle

        best, best_gain = None, 0.0
        for thing in surroundings:
            effects = thing.get("need_effects") or {}
            gain = effects.get(pressing, 0.0)
            if gain > best_gain and not thing.get("in_use"):
                best, best_gain = thing, gain
        if best is None:
            return None
        return {
            "target_id": best["entity_id"],
            "target_name": best.get("name", "?"),
            "affordance": best["affordances"][0],
            "need": pressing,
            "phase": "approach",
        }

    def step(self) -> None:
        """Advance the agent's plan; called once per tick, outside the engine."""
        if self.interface.is_busy():
            return

        if self.plan and self.plan["phase"] == "approach":
            result = self.interface.last_result()
            if result and result["status"] == "completed":
                self.plan["phase"] = "use"
                self.interface.use(self.plan["target_id"], self.plan["affordance"])
                return
            self.plan = None  # Approach failed; re-plan

        if self.plan and self.plan["phase"] == "use":
            self.plan = None  # Use finished (or failed); re-plan next tick

        if self.plan is None:
            perception = self.interface.perceive(vision_radius=25)
            self.plan = self.decide(self.interface.needs(),
                                    perception.describe_surroundings())
            if self.plan:
                if not self.interface.move_adjacent_to(self.plan["target_id"]):
                    self.plan = None


def render_map(engine: WorldEngine, spec: Dict[str, Any]) -> str:
    """Tiny ASCII view of the world grid."""
    width = spec["grid"]["width"]
    height = spec["grid"]["height"]
    snapshot = engine.get_snapshot()
    grid = [["." for _ in range(width)] for _ in range(height)]
    for record in snapshot["entities"].values():
        x, y = record["position"]
        char = "@" if record.get("kind") == "agent" else record.get("name", "?")[0].upper()
        grid[y][x] = char
    return "\n".join("".join(row) for row in grid)


def main() -> None:
    engine = engine_for_spec(DEFAULT_HOME_SPEC, seed=42, seconds_per_tick=60.0)
    build_world(engine, DEFAULT_HOME_SPEC)

    needs = Needs(
        levels={"energy": 0.5, "hunger": 0.35, "hygiene": 0.6,
                "fun": 0.45, "social": 0.4},
        decay_per_s=DEFAULT_NEEDS,
    )
    interface = AgentInterface(engine, agent_id="demo_agent", x=4, y=12,
                               name="Avery", needs=needs)
    agent = UtilityAgent(interface)

    names = {}  # entity_id -> display name, for the event log
    for entity_id, record in engine.get_snapshot()["entities"].items():
        names[entity_id] = record.get("name", entity_id[:8])

    def log_interaction(event_type, data):
        verb = "starts" if event_type == EventType.INTERACTION_STARTED else "finishes"
        print(f"  [{engine.simulation_time.strftime('%H:%M')}] "
              f"{names.get(data['entity_id'], '?')} {verb} "
              f"'{data['affordance']}' at {names.get(data['target_id'], '?')}")

    engine.subscribe(EventType.INTERACTION_STARTED, log_interaction)
    engine.subscribe(EventType.INTERACTION_COMPLETED, log_interaction)

    print("World at 08:00:")
    print(render_map(engine, DEFAULT_HOME_SPEC))
    print("\nA day in the life of Avery:")

    ticks_per_day = int(24 * 3600 / engine.time_per_tick.total_seconds())
    for _ in range(ticks_per_day):
        agent.step()                  # cognition (outside the tick)
        engine.run_simulation_step()  # physics/needs/intents (inside the tick)

    print("\nWorld at 08:00 next day:")
    print(render_map(engine, DEFAULT_HOME_SPEC))
    print("\nFinal needs:")
    for need, level in sorted(interface.needs().items()):
        bar = "#" * int(level * 20)
        print(f"  {need:<8} {level:5.2f} |{bar:<20}|")


if __name__ == "__main__":
    main()
