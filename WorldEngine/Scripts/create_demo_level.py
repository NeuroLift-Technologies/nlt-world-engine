import unreal

# Create a new level
level_name = "/Game/Demo/DemoLevel"
editor_subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
level_library = unreal.get_editor_subsystem(unreal.EditorLevelLibrary)

# Create the level
level_library.new_level(level_name)

# Load the cube mesh for ground and buildings
cube_mesh = unreal.EditorAssetLibrary.load_asset("/Engine/BasicShapes/Cube")

# Add a ground plane
ground_actor = editor_subsystem.spawn_actor_from_class(unreal.StaticMeshActor, unreal.Vector(0, 0, -50))
ground_actor.set_actor_scale3d(unreal.Vector(100, 100, 1))
ground_actor.static_mesh_component.set_static_mesh(cube_mesh)

# Add some buildings
building_positions = [
    (500, 0, 100), (-500, 0, 100), (0, 500, 100), (0, -500, 100),
    (1000, 1000, 150), (-1000, -1000, 150), (1000, -1000, 150), (-1000, 1000, 150),
]

for pos in building_positions:
    actor = editor_subsystem.spawn_actor_from_class(unreal.StaticMeshActor, unreal.Vector(pos[0], pos[1], pos[2]))
    actor.set_actor_scale3d(unreal.Vector(2, 2, pos[2] / 50))
    actor.static_mesh_component.set_static_mesh(cube_mesh)

# Save the level
unreal.EditorLevelLibrary.save_current_level()

print(f"Demo level created: {level_name}")
print("Next steps:")
print("1. Open the level: /Game/Demo/DemoLevel")
print("2. Set GameMode override to NLTDemoGameMode in World Settings")
print("3. Press Play to see agents spawn and world generate")
