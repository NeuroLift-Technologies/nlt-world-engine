#!/usr/bin/env python3
"""
Spawn NLTTrainingManager into the running sim and start training.

Usage:
  python3 WorldEngine/Scripts/spawn_training_manager.py
"""

from __future__ import annotations
import sys
import os

# UE's bundled Python paths
PIP_INSTALL = os.path.join(
    os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
    "Intermediate", "PipInstall", "lib", "python3.11", "site-packages"
)
if PIP_INSTALL not in sys.path:
    sys.path.insert(0, PIP_INSTALL)

LEARNING_CORE = os.path.join(
    os.path.expanduser("~"), "Documents", "NLT", "Engine", "Plugins",
    "Experimental", "LearningCore", "Content", "Python"
)
if LEARNING_CORE not in sys.path:
    sys.path.insert(0, LEARNING_CORE)

import unreal


def main():
    editor = unreal.get_editor_subsystem(unreal.UnrealEditorSubsystem)
    world = editor.get_editor_world()
    if not world:
        print("ERROR: Could not get editor world")
        return

    # Load the native NLTTrainingManager class once (no A prefix, 
    # no load_blueprint_class for native C++ classes)
    training_manager_class = unreal.EditorAssetLibrary.find_asset("/Script/WorldEngine.NLTTrainingManager")
    if not training_manager_class:
        print("ERROR: Could not find NLTTrainingManager class")
        return

    # Check if NLTTrainingManager already exists in the level
    existing = unreal.GameplayStatics.get_actor_of_class(world, training_manager_class)
    if existing:
        print(f"NLTTrainingManager already in level: {existing.get_name()}")
        return

    # Spawn location
    spawn_loc = unreal.Vector(0, 0, 500)

    # Spawn the actor
    spawn_params = unreal.ActorSpawnParameters()
    spawn_params.name = "NLTTrainingManager_0"
    spawn_params.spawn_collision_handling_override = unreal.ESpawnActorCollisionHandlingMethod.always_spawn

    actor = world.spawn_actor(training_manager_class, spawn_loc, unreal.Rotator(), spawn_params)
    if actor:
        print(f"Spawned NLTTrainingManager: {actor.get_name()} at {spawn_loc.to_tuple()}")
        
        # Configure — must be set BEFORE begin_play() to take effect.
        # PPO training mode: disable LLM control so the LearningAgents
        # policy provides actions instead of the REST bridge.
        actor.b_use_llm_control = False
        actor.b_run_inference = True
        actor.b_run_training = True
        actor.max_episode_steps = 512
        
        print("NLTTrainingManager configured and started")
    else:
        print("ERROR: Failed to spawn NLTTrainingManager")


if __name__ == "__main__":
    main()
