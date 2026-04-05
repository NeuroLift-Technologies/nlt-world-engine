"""
test_training_loop.py — interactive training loop demo / smoke test

Status: Stub — see README.md troubleshooting for known issues with this script.
Currently reaches scenario execution, then fails during coaching context construction.
Use to validate setup path and reproduce current integration behavior.
"""

import sys
import os

# Add src to path for module resolution
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))


def main():
    print("=== nlt-fusion Training Loop Demo ===")
    print("Status: Stub — full training loop pending Phase 3 implementation.")
    print("")
    print("For the current reference orchestration interface, see:")
    print("  tests/test_simulation/test_session_orchestrator.py")
    print("")
    print("Known issues:")
    print("  - CoachingContext call pattern may be outdated (see README.md troubleshooting)")
    print("  - Relative import errors in src/avatars when called directly")


if __name__ == "__main__":
    main()
