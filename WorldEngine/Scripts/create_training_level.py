#!/usr/bin/env python3
"""
Create a dedicated NLT training level with NLTTrainingManager placed in it.

This script creates a new .umap level file with the training manager actor
placed at origin. The level can then be loaded in headless mode for training.

Usage (inside UE editor Python):
  /path/to/this/script
  
Or via ProgrammaticToolset in MCP.
"""

from __future__ import annotations

import unreal


def create_training_level():
    """Create a new level with NLTTrainingManager placed."""
    
    level_path = "/Game/Scenarios/Levels/Training_Level"
    
    # Check if level already exists
    if unreal.EditorAssetLibrary.does_asset_exist(level_path + ".umap"):
        print(f"Training level already exists: {level_path}")
        return level_path
    
    # Create a new empty level
    # Use EditorLevelLibrary to create and save a new level
    new_level = unreal.EditorLevelLibrary.new_level(level_path)
    if not new_level:
        print("ERROR: Failed to create new level")
        return None
    
    print(f"Created new level: {level_path}")
    
    # Load the NLTTrainingManager class
    # It's a C++ class, not a blueprint - use the class directly
    training_manager_class = unreal.load_class(None, "/Script/WorldEngine.NLTTrainingManager")
    if not training_manager_class:
        print("ERROR: Could not load ANLTTrainingManager class")
        return None
    
    # Spawn the actor
    spawn_loc = unreal.Vector(0, 0, 0)
    spawn_rot = unreal.Rotator()
    
    # Use EditorLevelLibrary to spawn actor in level
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        training_manager_class, spawn_loc, spawn_rot
    )
    
    if actor:
        print(f"Spawned NLTTrainingManager: {actor.get_name()}")
        
        # Configure properties
        actor.set_actor_label("NLTTrainingManager")
        
        # Save the level
        saved = unreal.EditorLevelLibrary.save_current_level()
        if saved:
            print(f"Saved training level: {level_path}")
            return level_path
        else:
            print("ERROR: Failed to save level")
            return None
    else:
        print("ERROR: Failed to spawn NLTTrainingManager")
        return None


if __name__ == "__main__":
    result = create_training_level()
    if result:
        print(f"Training level ready: {result}")
    else:
        print("Failed to create training level")
