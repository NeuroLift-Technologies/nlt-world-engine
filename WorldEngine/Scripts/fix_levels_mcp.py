import json
import time

def run():
    results = {
        "level_package_fix": {},
        "dataasset_properties": [],
        "binding_validation": [],
        "level_validation": {},
        "load_time": {},
        "save_results": {},
        "duplication_results": {},
    }

    # ─── Step 1: Move /Game/ScenarioStage to correct paths ───────────────────
    # First, let's see what exists
    print("Step 1: Checking existing levels in asset registry")

    # Check if ScenarioStage exists
    stage_exists = execute_tool(
        "editor_toolset.toolsets.asset.AssetTools.exists",
        json.dumps({"path": "/Game/ScenarioStage"})
    )
    print("  /Game/ScenarioStage exists: {}".format(stage_exists))

    # Check current level paths
    for level_name in ["Workplace_Level", "Personal_Level", "Social_Level", "Academic_Level"]:
        path = "/Game/Scenarios/Levels/" + level_name
        exists = execute_tool(
            "editor_toolset.toolsets.asset.AssetTools.exists",
            json.dumps({"path": path})
        )
        print("  {} exists: {}".format(path, exists))
        results["level_package_fix"][level_name] = {"exists_before": exists}

    # ─── Step 2: Move /Game/ScenarioStage -> /Game/Scenarios/Levels/Workplace_Level ──
    print("\nStep 2: Moving /Game/ScenarioStage -> Workplace_Level")
    # First delete old file from disk (all 4 umaps have same package name)
    import os
    # We can't use os module... let me check
    pass

    # Actually, let me try the move operation
    for i, level_name in enumerate(["Workplace_Level", "Personal_Level", "Social_Level", "Academic_Level"]):
        target_path = "/Game/Scenarios/Levels/" + level_name
        source_path = "/Game/ScenarioStage"

        # First try to move
        try:
            move_result = execute_tool(
                "editor_toolset.toolsets.asset.AssetTools.move",
                json.dumps({"path": source_path, "new_path": target_path})
            )
            print("  Move {} -> {}: {}".format(source_path, target_path, move_result))
            results["level_package_fix"][level_name]["move_result"] = move_result

            # After moving, we can duplicate the fixed level for the remaining ones
            break  # Only move the first one; rest will be duplicated
        except Exception as e:
            print("  Move failed: {}".format(str(e)))
            results["level_package_fix"][level_name]["move_error"] = str(e)

    # ─── Step 3: Delete remaining old .umap files ────────────────────────────
    # We can't use os module, but we can use AssetTools.delete
    print("\nStep 3: Checking remaining .umap files")

    # ─── Step 4: Duplicate fixed level for others ─────────────────────────────
    print("\nStep 4: Duplicating Workplace_Level for other scenarios")
    source = "/Game/Scenarios/Levels/Workplace_Level"
    for level_name in ["Personal_Level", "Social_Level", "Academic_Level"]:
        target = "/Game/Scenarios/Levels/" + level_name
        try:
            dup_result = execute_tool(
                "editor_toolset.toolsets.asset.AssetTools.duplicate",
                json.dumps({"path": source, "new_path": target})
            )
            print("  Duplicated {} -> {}: {}".format(source, target, dup_result))
            results["duplication_results"][level_name] = {
                "source": source, "target": target, "result": dup_result
            }
        except Exception as e:
            print("  Duplicate failed: {}".format(str(e)))
            results["duplication_results"][level_name] = {
                "source": source, "target": target, "error": str(e)
            }

    return results
