"""
setup_environment.py — nlt-fusion environment setup script

Status: Stub — full implementation pending Phase 3.
See README.md Quick Start for usage instructions.
"""

import sys
import os


def check_python_version():
    """Verify Python 3.10+ is being used."""
    if sys.version_info < (3, 10):
        print(f"ERROR: Python 3.10+ required. Found: {sys.version}")
        sys.exit(1)
    print(f"Python version OK: {sys.version}")


def create_data_directory():
    """Create local data directory for simulation storage."""
    data_dir = os.path.join(os.path.dirname(__file__), "..", "data")
    os.makedirs(data_dir, exist_ok=True)
    print(f"Data directory ready: {os.path.abspath(data_dir)}")


def main():
    print("=== nlt-fusion Environment Setup ===")
    check_python_version()
    create_data_directory()
    print("\nSetup complete. Run 'python3 scripts/test_training_loop.py' to validate.")


if __name__ == "__main__":
    main()
