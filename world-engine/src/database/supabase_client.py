"""
Supabase Client Module - STUB IMPLEMENTATION

This is a minimal stub implementation to unblock syntax checking and imports.
Real implementation requires architectural decisions about:
- Database schema design for training sessions, results, coaching actions
- Supabase authentication and connection management
- Privacy considerations (local vs. cloud, data retention, etc.)
- Error handling and retry logic
- Migration strategy from development to production

TODO: Replace with full implementation after architecture is defined.
See: docs/escalations/2026-05-29-python-engine-missing-modules.md

IMPORTANT: Per project README privacy-first design principles:
- Local Processing: All processing happens locally (exempt during development/training)
- No Data Collection: No external data transmission without explicit consent
- No Monetization: User data never monetized
- Transparent: Clear about what data exists and where

Production use of Supabase (cloud database) must align with these principles.
"""

from typing import Any, Dict, List, Optional


class SupabaseClient:
    """
    Client for interacting with Supabase database.

    STUB IMPLEMENTATION - NOT FUNCTIONAL

    Real implementation would:
    - Manage Supabase connection and authentication
    - Provide CRUD operations for:
      - Training sessions
      - Task results
      - Coaching actions
      - Avatar/Aide configurations
      - Fusion readiness assessments
    - Handle errors and connection issues gracefully
    - Respect privacy-first design principles
    """

    def __init__(self, url: Optional[str] = None, key: Optional[str] = None):
        """
        Initialize Supabase client.

        Args:
            url: Supabase project URL (optional, can use env var)
            key: Supabase API key (optional, can use env var)

        STUB: Does not establish real connection.
        """
        self.url = url
        self.key = key
        self._connected = False

    def create_training_session(
        self,
        session_id: str,
        avatar_id: str,
        aide_id: str,
        session_type: str,
        scenario: str,
    ) -> Dict[str, Any]:
        """
        Create a new training session record.

        STUB: Returns empty dict without persisting.
        """
        raise NotImplementedError(
            "SupabaseClient.create_training_session() is a stub. "
            "Real implementation requires database schema and connection."
        )

    def create_task_result(
        self,
        session_id: str,
        avatar_id: str,
        task_type: str,
        success: bool,
        completion_time: Optional[float],
        quality_score: float,
        struggle_indicators: List[str],
        emotional_state: str,
        cognitive_load: float,
        result_data: Dict[str, Any],
    ) -> Dict[str, Any]:
        """
        Record a task attempt result.

        STUB: Returns empty dict without persisting.
        """
        raise NotImplementedError(
            "SupabaseClient.create_task_result() is a stub. "
            "Real implementation requires database schema and connection."
        )

    def create_coaching_action(
        self,
        coaching_id: str,
        session_id: str,
        avatar_id: str,
        aide_id: str,
        coaching_type: str,
        urgency: str,
        strategy: str,
        techniques: List[str],
        expected_outcomes: List[str],
        stress_reduction: float,
        emotional_boost: float,
        cognitive_support: float,
        independence_building: float,
    ) -> Dict[str, Any]:
        """
        Record a coaching intervention.

        STUB: Returns empty dict without persisting.
        """
        raise NotImplementedError(
            "SupabaseClient.create_coaching_action() is a stub. "
            "Real implementation requires database schema and connection."
        )

    def end_training_session(
        self,
        session_id: str,
        duration_seconds: int,
    ) -> Dict[str, Any]:
        """
        Mark a training session as ended.

        STUB: Returns empty dict without persisting.
        """
        raise NotImplementedError(
            "SupabaseClient.end_training_session() is a stub. "
            "Real implementation requires database schema and connection."
        )
