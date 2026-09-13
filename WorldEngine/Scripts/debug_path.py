import sys
import os

# UE's LearningCore Python package
LEARNING_CORE = os.path.join(
    os.path.expanduser("~"), "Documents", "NLT", "Engine", "Plugins",
    "Experimental", "LearningCore", "Content", "Python"
)
if LEARNING_CORE not in sys.path:
    sys.path.insert(0, LEARNING_CORE)

try:
    import learning_core.ppo as ppo
    print(f"LOADED PPO FILE: {ppo.__file__}")
except Exception as e:
    print(f"Error loading ppo: {e}")
