"""
Base Avatar Module - STUB IMPLEMENTATION

This is a minimal stub implementation to unblock syntax checking and imports.
Real implementation requires architectural decisions about:
- Avatar trait modeling and state management
- Task execution simulation mechanics
- Stress/burnout/independence tracking
- Event bus integration patterns

TODO: Replace with full implementation after architecture is defined.
See: docs/escalations/2026-05-29-python-engine-missing-modules.md
"""

from dataclasses import dataclass, field
from datetime import timedelta
from typing import Any, Dict, List, Optional
from enum import Enum


class EmotionalState(Enum):
    """Placeholder for emotional state representation."""
    CALM = "calm"
    STRESSED = "stressed"
    FRUSTRATED = "frustrated"
    OVERWHELMED = "overwhelmed"


@dataclass
class TaskResult:
    """
    Result of a single task attempt by an Avatar.

    STUB: Minimal fields inferred from usage in session_orchestrator.py
    and training_session.py.
    """
    success: bool
    quality_score: float = 0.0
    completion_time: Optional[timedelta] = None
    struggle_indicators: List[str] = field(default_factory=list)
    emotional_state: str = "calm"
    cognitive_load: float = 0.0

    def to_dict(self) -> Dict[str, Any]:
        """Convert to dictionary for serialization."""
        return {
            "success": self.success,
            "quality_score": self.quality_score,
            "completion_time": (
                self.completion_time.total_seconds() if self.completion_time else None
            ),
            "struggle_indicators": self.struggle_indicators,
            "emotional_state": self.emotional_state,
            "cognitive_load": self.cognitive_load,
        }


class BaseAvatar:
    """
    Base class for AI Avatars experiencing ADHD traits in simulation.

    STUB IMPLEMENTATION - NOT FUNCTIONAL

    Real implementation would include:
    - ADHD trait modeling (task initiation, sustained attention, etc.)
    - State machine integration for internal state
    - Event bus integration for observation
    - Realistic task execution simulation with trait-based failures
    - Stress/burnout accumulation mechanics
    - Independence level tracking based on coaching dependency
    """

    def __init__(
        self,
        avatar_id: str,
        trait_name: str,
        event_bus: Optional[Any] = None,
    ):
        """
        Initialize a base avatar.

        Args:
            avatar_id: Unique identifier for this avatar
            trait_name: Name of the ADHD trait being modeled
            event_bus: Event bus for state observation (from core.events)
        """
        self.avatar_id = avatar_id
        self.trait_name = trait_name
        self.event_bus = event_bus
        self.stress_level = 0.0

    def attempt_task(self, task_context: Dict[str, Any]) -> TaskResult:
        """
        Attempt to complete a task within the simulation.

        STUB: Always returns a failed result with placeholder data.
        """
        raise NotImplementedError(
            "BaseAvatar.attempt_task() is a stub. "
            "Real implementation requires Avatar behavior modeling."
        )

    def receive_coaching(self, coaching_action: Dict[str, Any]) -> None:
        """
        Receive and process coaching from an Aide.

        STUB: No-op placeholder.
        """
        raise NotImplementedError(
            "BaseAvatar.receive_coaching() is a stub. "
            "Real implementation requires coaching integration logic."
        )

    def assess_burnout_risk(self) -> Dict[str, Any]:
        """
        Assess current burnout risk level.

        STUB: Returns minimal safe values.
        """
        raise NotImplementedError(
            "BaseAvatar.assess_burnout_risk() is a stub. "
            "Real implementation requires burnout modeling."
        )

    def get_independence_level(self) -> float:
        """
        Get current independence level (1.0 = fully independent).

        STUB: Returns 0.0 (fully dependent).
        """
        raise NotImplementedError(
            "BaseAvatar.get_independence_level() is a stub. "
            "Real implementation requires independence tracking."
        )

    def return_to_idle(self) -> None:
        """
        Return avatar to idle state between scenarios.

        STUB: No-op placeholder.
        """
        raise NotImplementedError(
            "BaseAvatar.return_to_idle() is a stub. "
            "Real implementation requires state management."
        )
