"""
Database package - Data persistence layer.

STUB: Database client implementations pending architectural decisions.
See: docs/escalations/2026-05-29-python-engine-missing-modules.md

IMPORTANT: Production use must align with privacy-first design principles:
- Local Processing (exempt during development/training only)
- No Data Collection without explicit consent
- No Monetization of user data
- Transparent about data existence and location
"""

from .supabase_client import SupabaseClient

__all__ = ["SupabaseClient"]
