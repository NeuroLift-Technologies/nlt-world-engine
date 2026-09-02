import json
import time
import math

# ─── Asset data ─────────────────────────────────────────────────────────
ASSETS = [
    ("workplace_email_processing", "Email Processing", "Workplace",
     "/Game/Scenarios/Workplace/Wor_EmailProcessing.Wor_EmailProcessing",
     "/Game/Scenarios/Levels/Workplace_Level.Workplace_Level"),
    ("workplace_report_writing", "Report Writing", "Workplace",
     "/Game/Scenarios/Workplace/Wor_ReportWriting.Wor_ReportWriting",
     "/Game/Scenarios/Levels/Workplace_Level.Workplace_Level"),
    ("workplace_meeting_participation", "Meeting Participation", "Workplace",
     "/Game/Scenarios/Workplace/Wor_MeetingParticipation.Wor_MeetingParticipation",
     "/Game/Scenarios/Levels/Workplace_Level.Workplace_Level"),
    ("workplace_code_review", "Code Review", "Workplace",
     "/Game/Scenarios/Workplace/Wor_CodeReview.Wor_CodeReview",
     "/Game/Scenarios/Levels/Workplace_Level.Workplace_Level"),
    ("workplace_deadline_crunch", "Deadline Crunch", "Workplace",
     "/Game/Scenarios/Workplace/Wor_DeadlineCrunch.Wor_DeadlineCrunch",
     "/Game/Scenarios/Levels/Workplace_Level.Workplace_Level"),
    ("personal_household_cleaning", "Household Cleaning", "Personal",
     "/Game/Scenarios/Personal/Per_HouseholdCleaning.Per_HouseholdCleaning",
     "/Game/Scenarios/Levels/Personal_Level.Personal_Level"),
    ("personal_grocery_shopping", "Grocery Shopping", "Personal",
     "/Game/Scenarios/Personal/Per_GroceryShopping.Per_GroceryShopping",
     "/Game/Scenarios/Levels/Personal_Level.Personal_Level"),
    ("personal_bill_paying", "Bill Paying", "Personal",
     "/Game/Scenarios/Personal/Per_BillPaying.Per_BillPaying",
     "/Game/Scenarios/Levels/Personal_Level.Personal_Level"),
    ("personal_morning_routine", "Morning Routine", "Personal",
     "/Game/Scenarios/Personal/Per_MorningRoutine.Per_MorningRoutine",
     "/Game/Scenarios/Levels/Personal_Level.Personal_Level"),
    ("social_phone_conversation", "Phone Conversation", "Social",
     "/Game/Scenarios/Social/Soc_PhoneConversation.Soc_PhoneConversation",
     "/Game/Scenarios/Levels/Social_Level.Social_Level"),
    ("social_event", "Social Event", "Social",
     "/Game/Scenarios/Social/Soc_SocialEvent.Soc_SocialEvent",
     "/Game/Scenarios/Levels/Social_Level.Social_Level"),
    ("academic_study_session", "Study Session", "Academic",
     "/Game/Scenarios/Academic/Aca_StudySession.Aca_StudySession",
     "/Game/Scenarios/Levels/Academic_Level.Academic_Level"),
    ("academic_project_work", "Project Work", "Academic",
     "/Game/Scenarios/Academic/Aca_ProjectWork.Aca_ProjectWork",
     "/Game/Scenarios/Levels/Academic_Level.Academic_Level"),
]

SCENARIO_PARAMS = {
    "workplace_email_processing": {"durationMinutes": 45.0, "complexity": "Medium", "aversiveness": 0.3, "cognitiveDemand": 0.6, "baseSuccessRate": 0.7, "bRequiresSustainedFocus": True},
    "workplace_report_writing": {"durationMinutes": 120.0, "complexity": "High", "aversiveness": 0.6, "cognitiveDemand": 0.9, "baseSuccessRate": 0.6, "bRequiresSustainedFocus": True},
    "workplace_meeting_participation": {"durationMinutes": 60.0, "complexity": "Medium", "aversiveness": 0.4, "cognitiveDemand": 0.5, "baseSuccessRate": 0.75, "bRequiresSustainedFocus": False},
    "workplace_code_review": {"durationMinutes": 90.0, "complexity": "High", "aversiveness": 0.5, "cognitiveDemand": 0.8, "baseSuccessRate": 0.65, "bRequiresSustainedFocus": True},
    "workplace_deadline_crunch": {"durationMinutes": 180.0, "complexity": "High", "aversiveness": 0.9, "cognitiveDemand": 0.95, "baseSuccessRate": 0.5, "bRequiresSustainedFocus": True},
    "personal_household_cleaning": {"durationMinutes": 60.0, "complexity": "Low", "aversiveness": 0.4, "cognitiveDemand": 0.2, "baseSuccessRate": 0.85, "bRequiresSustainedFocus": False},
    "personal_grocery_shopping": {"durationMinutes": 45.0, "complexity": "Medium", "aversiveness": 0.3, "cognitiveDemand": 0.4, "baseSuccessRate": 0.8, "bRequiresSustainedFocus": False},
    "personal_bill_paying": {"durationMinutes": 20.0, "complexity": "Low", "aversiveness": 0.5, "cognitiveDemand": 0.6, "baseSuccessRate": 0.9, "bRequiresSustainedFocus": False},
    "personal_morning_routine": {"durationMinutes": 30.0, "complexity": "Low", "aversiveness": 0.1, "cognitiveDemand": 0.3, "baseSuccessRate": 0.95, "bRequiresSustainedFocus": False},
    "social_phone_conversation": {"durationMinutes": 15.0, "complexity": "Low", "aversiveness": 0.7, "cognitiveDemand": 0.6, "baseSuccessRate": 0.7, "bRequiresSustainedFocus": False},
    "social_event": {"durationMinutes": 120.0, "complexity": "High", "aversiveness": 0.85, "cognitiveDemand": 0.5, "baseSuccessRate": 0.6, "bRequiresSustainedFocus": True},
    "academic_study_session": {"durationMinutes": 90.0, "complexity": "Medium", "aversiveness": 0.4, "cognitiveDemand": 0.8, "baseSuccessRate": 0.75, "bRequiresSustainedFocus": True},
    "academic_project_work": {"durationMinutes": 150.0, "complexity": "High", "aversiveness": 0.5, "cognitiveDemand": 0.9, "baseSuccessRate": 0.65, "bRequiresSustainedFocus": True},
}

LEVELS = [
    ("Workplace_Level", "/Game/Scenarios/Levels/Workplace_Level"),
    ("Personal_Level", "/Game/Scenarios/Levels/Personal_Level"),
    ("Social_Level", "/Game/Scenarios/Levels/Social_Level"),
    ("Academic_Level", "/Game/Scenarios/Levels/Academic_Level"),
]

PLAYER_START_CLASS = {"refPath": "/Script/Engine.PlayerStart"}
NAVMESH_CLASS = {"refPath": "/Script/Engine.NavMeshBoundsVolume"}


def get_retval(result):
    """Extract returnValue from MCP tool result, handling StrictDict."""
    if isinstance(result, dict):
        if "returnValue" in result:
            return result["returnValue"]
        if "result" in result:
            inner = result["result"]
            if isinstance(inner, dict) and "returnValue" in inner:
                return inner["returnValue"]
    return None


def safe_call(toolset, tool_name, args_dict):
    """Call an MCP tool safely, returning the result or error string."""
    try:
        result = execute_tool(
            toolset,
            json.dumps(args_dict) if not isinstance(args_dict, str) else args_dict
        )
        return {"success": True, "result": result}
    except Exception as e:
        return {"success": False, "error": str(e), "result": None}


def run():
    r = {
        "level_fix": {}, "level_actors": {}, "level_save": {},
        "duplication": {}, "dataasset_properties": [], "asset_save": {},
        "binding_validation": [], "level_validation": {}, "load_time": {},
        "summary": {},
    }

    # ─── Phase 1: Move /Game/ScenarioStage -> Workplace_Level ──────────────
    print("=== Phase 1: Moving /Game/ScenarioStage ===")

    stage_exists = safe_call(
        "editor_toolset.toolsets.asset.AssetTools", "exists",
        {"path": "/Game/ScenarioStage"}
    )
    r["level_fix"]["scenario_stage_exists"] = get_retval(stage_exists["result"])

    if r["level_fix"]["scenario_stage_exists"]:
        target = "/Game/Scenarios/Levels/Workplace_Level"
        move_result = safe_call(
            "editor_toolset.toolsets.asset.AssetTools", "move",
            {"path": "/Game/ScenarioStage", "new_path": target}
        )
        r["level_fix"]["move_result"] = move_result
        print("  Move: {}".format(json.dumps(move_result)[:300]))

        time.sleep(2)

        # Verify
        check_new = safe_call(
            "editor_toolset.toolsets.asset.AssetTools", "exists",
            {"path": target}
        )
        r["level_fix"]["workplace_exists"] = get_retval(check_new["result"])
        print("  Workplace_Level exists: {}".format(r["level_fix"]["workplace_exists"]))
    else:
        r["level_fix"]["move_error"] = "ScenarioStage does not exist"

    # ─── Phase 2: Duplicate for other levels ──────────────────────────────
    print("\n=== Phase 2: Duplicating levels ===")
    source = "/Game/Scenarios/Levels/Workplace_Level"
    for level_name in ["Personal_Level", "Social_Level", "Academic_Level"]:
        target = "/Game/Scenarios/Levels/" + level_name
        check = safe_call(
            "editor_toolset.toolsets.asset.AssetTools", "exists",
            {"path": target}
        )
        already = get_retval(check["result"])

        if not already:
            dup_r = safe_call(
                "editor_toolset.toolsets.asset.AssetTools", "duplicate",
                {"path": source, "new_path": target}
            )
            r["duplication"][level_name] = {"result": str(dup_r["result"])[:200]}
            print("  Duplicated to {}: {}".format(level_name, str(dup_r["result"])[:200]))
        else:
            r["duplication"][level_name] = {"status": "already_exists"}
            print("  {} already exists".format(level_name))

    time.sleep(2)

    # ─── Phase 3: Add actors to each level ─────────────────────────────────
    print("\n=== Phase 3: Adding actors ===")
    for level_name, level_path in LEVELS:
        print("  --- {} ---".format(level_name))
        lvl_r = {}

        load_r = safe_call(
            "editor_toolset.toolsets.scene.SceneTools", "load_level",
            {"level_path": level_path}
        )
        load_ok = get_retval(load_r["result"])
        lvl_r["loaded"] = load_ok
        print("    Loaded: {}".format(load_ok))

        if not load_ok:
            lvl_r["error"] = str(load_r.get("error", ""))
            r["level_actors"][level_name] = lvl_r
            continue

        # Find existing actors
        all_a = safe_call(
            "editor_toolset.toolsets.scene.SceneTools", "find_actors",
            {}
        )
        all_list = all_a["result"]
        total = len(all_list) if isinstance(all_list, list) else 0
        lvl_r["total_actors"] = total
        print("    Total actors: {}".format(total))

        # Count PlayerStarts
        ps_r = safe_call(
            "editor_toolset.toolsets.scene.SceneTools", "find_actors",
            {"actor_type": "PlayerStart"}
        )
        ps_list = ps_r["result"]
        ps_count = len(ps_list) if isinstance(ps_list, list) else 0
        lvl_r["player_starts"] = ps_count
        print("    PlayerStarts: {}".format(ps_count))

        # Count NavMesh
        nav_r = safe_call(
            "editor_toolset.toolsets.scene.SceneTools", "find_actors",
            {"actor_type": "NavMeshBoundsVolume"}
        )
        nav_list = nav_r["result"]
        nav_count = len(nav_list) if isinstance(nav_list, list) else 0
        lvl_r["navmesh"] = nav_count
        print("    NavMesh: {}".format(nav_count))

        # Add PlayerStarts (need >=10)
        needed = max(0, 10 - ps_count)
        added = []
        if needed > 0:
            for i in range(needed):
                x = float((i % 5) * 200 - 400)
                y = float((i // 5) * 200 - 200)
                xform = {"x": x, "y": y, "z": 100.0, "rx": 0, "ry": 0, "rz": 0,
                         "sx": 1.0, "sy": 1.0, "sz": 1.0}
                add_r = safe_call(
                    "editor_toolset.toolsets.scene.SceneTools", "add_to_scene_from_class",
                    {"actor_type": PLAYER_START_CLASS, "name": "PlayerStart_{}".format(i), "xform": xform}
                )
                added.append("PlayerStart_{}_{}".format(i, "ok" if add_r["success"] else "FAIL"))
        lvl_r["added_ps"] = added

        # Add NavMesh if missing
        if nav_count == 0:
            xform = {"x": 0.0, "y": 0.0, "z": 0.0, "rx": 0, "ry": 0, "rz": 0,
                     "sx": 1.0, "sy": 1.0, "sz": 1.0}
            nav_r2 = safe_call(
                "editor_toolset.toolsets.scene.SceneTools", "add_to_scene_from_class",
                {"actor_type": NAVMESH_CLASS, "name": "NavMeshBoundsVolume_0", "xform": xform, "snap_to_ground": False}
            )
            lvl_r["added_navmesh"] = "ok" if nav_r2["success"] else "FAIL: " + str(nav_r2.get("error", ""))
            print("    Added NavMesh: {}".format(lvl_r["added_navmesh"]))
        else:
            lvl_r["added_navmesh"] = "already_present"

        r["level_actors"][level_name] = lvl_r

        # Save level
        asset_path = level_path + "." + level_name
        save_r = safe_call(
            "editor_toolset.toolsets.asset.AssetTools", "save_assets",
            {"asset_paths": [asset_path]}
        )
        lvl_r["save_result"] = str(save_r["result"])[:200] if save_r["success"] else str(save_r.get("error", ""))
        r["level_save"][level_name] = lvl_r["save_result"]
        print("    Save: {}".format(lvl_r["save_result"]))

    # ─── Phase 4: Set DataAsset properties ────────────────────────────────
    print("\n=== Phase 4: Setting DataAsset properties ===")
    for scenario_id, display_name, category, asset_path, level_ref in ASSETS:
        params = SCENARIO_PARAMS[scenario_id]
        values = {
            "scenarioId": scenario_id,
            "displayName": display_name,
            "description": "Auto-generated scenario: " + display_name,
            "category": category,
            "durationMinutes": params["durationMinutes"],
            "complexity": params["complexity"],
            "aversiveness": params["aversiveness"],
            "cognitiveDemand": params["cognitiveDemand"],
            "baseSuccessRate": params["baseSuccessRate"],
            "bRequiresSustainedFocus": params["bRequiresSustainedFocus"],
            "levelReference": level_ref,
        }

        set_r = safe_call(
            "editor_toolset.toolsets.object.ObjectTools", "set_properties",
            {"instance": {"refPath": asset_path}, "values": json.dumps(values)}
        )
        r["dataasset_properties"].append({
            "scenario_id": scenario_id, "set_success": set_r["success"],
            "error": set_r.get("error", "")
        })
        print("  [{}] {}".format("OK" if set_r["success"] else "FAIL", scenario_id))

    # ─── Phase 5: Save DataAssets ──────────────────────────────────────────
    print("\n=== Phase 5: Saving DataAssets ===")
    all_paths = [a[3] for a in ASSETS]
    save_r = safe_call(
        "editor_toolset.toolsets.asset.AssetTools", "save_assets",
        {"asset_paths": all_paths}
    )
    r["asset_save"]["result"] = str(save_r["result"])[:200] if save_r["success"] else str(save_r.get("error", ""))
    r["asset_save"]["count"] = len(all_paths)
    print("  Saved {} assets: {}".format(len(all_paths), r["asset_save"]["result"]))

    # ─── Phase 6: Verify bindings ──────────────────────────────────────────
    print("\n=== Phase 6: Binding verification ===")
    binding_ok = 0
    for scenario_id, display_name, category, asset_path, level_ref in ASSETS:
        props_r = safe_call(
            "editor_toolset.toolsets.object.ObjectTools", "get_properties",
            {"instance": {"refPath": asset_path}, "properties": ["levelReference"]}
        )
        if props_r["success"]:
            result = props_r["result"]
            retval = get_retval(result)
            if retval is not None:
                try:
                    parsed = json.loads(retval) if isinstance(retval, str) else retval
                    actual_ref = parsed.get("levelReference", "") if isinstance(parsed, dict) else ""
                except:
                    actual_ref = str(retval)
                matches = (actual_ref == level_ref)
                if matches:
                    binding_ok += 1
                r["binding_validation"].append({
                    "scenario_id": scenario_id,
                    "level_reference_soft": actual_ref,
                    "expected": level_ref,
                    "matches": matches,
                    "valid": matches,
                })
                print("  {} [{}] {}".format(scenario_id, "OK" if matches else "MISMATCH", actual_ref))
            else:
                r["binding_validation"].append({
                    "scenario_id": scenario_id, "error": "No returnValue", "valid": False
                })
                print("  {} ERROR: no return value".format(scenario_id))
        else:
            r["binding_validation"].append({
                "scenario_id": scenario_id, "error": props_r.get("error", ""),
                "valid": False
            })
            print("  {} ERROR: {}".format(scenario_id, props_r.get("error", "")))

    print("\n  Valid bindings: {}/{}".format(binding_ok, len(ASSETS)))

    # ─── Phase 7: Final level validation ──────────────────────────────────
    print("\n=== Phase 7: Final level validation ===")
    for level_name, level_path in LEVELS:
        print("  --- {} ---".format(level_name))
        lvl_r = {}

        exists_r = safe_call(
            "editor_toolset.toolsets.asset.AssetTools", "exists",
            {"path": level_path}
        )
        lvl_r["exists"] = get_retval(exists_r["result"])

        # Time the load
        start = time.time()
        load_r = safe_call(
            "editor_toolset.toolsets.scene.SceneTools", "load_level",
            {"level_path": level_path}
        )
        elapsed = time.time() - start
        lvl_r["load_success"] = get_retval(load_r["result"])
        lvl_r["load_time"] = round(elapsed, 3)
        lvl_r["within_target"] = elapsed < 30.0
        r["load_time"][level_name] = {
            "seconds": round(elapsed, 3),
            "within_target": elapsed < 30.0,
            "success": lvl_r["load_success"]
        }
        print("    Load: {} in {:.3f}s".format(lvl_r["load_success"], elapsed))

        if lvl_r["load_success"]:
            # Actor counts
            ps_r = safe_call(
                "editor_toolset.toolsets.scene.SceneTools", "find_actors",
                {"actor_type": "PlayerStart"}
            )
            ps_list = ps_r["result"]
            ps_count = len(ps_list) if isinstance(ps_list, list) else 0
            lvl_r["player_starts"] = ps_count
            lvl_r["spawn_points_ok"] = ps_count >= 10

            sm_r = safe_call(
                "editor_toolset.toolsets.scene.SceneTools", "find_actors",
                {"actor_type": "StaticMeshActor"}
            )
            sm_list = sm_r["result"]
            sm_count = len(sm_list) if isinstance(sm_list, list) else 0
            lvl_r["static_meshes"] = sm_count
            lvl_r["geometry_ok"] = sm_count > 0

            nav_r = safe_call(
                "editor_toolset.toolsets.scene.SceneTools", "find_actors",
                {"actor_type": "NavMeshBoundsVolume"}
            )
            nav_list = nav_r["result"]
            nav_count = len(nav_list) if isinstance(nav_list, list) else 0
            lvl_r["navmesh"] = nav_count
            lvl_r["navmesh_ok"] = nav_count > 0

            all_r = safe_call(
                "editor_toolset.toolsets.scene.SceneTools", "find_actors",
                {}
            )
            total = len(all_r["result"]) if isinstance(all_r["result"], list) else 0
            lvl_r["total_actors"] = total

            lvl_r["lighting_types"] = []
            for lt in ["DirectionalLight", "SkyLight", "SkyAtmosphere",
                       "ExponentialHeightFog", "VolumetricCloud"]:
                lt_r = safe_call(
                    "editor_toolset.toolsets.scene.SceneTools", "find_actors",
                    {"actor_type": lt}
                )
                lt_list = lt_r["result"]
                lt_count = len(lt_list) if isinstance(lt_list, list) else 0
                if lt_count > 0:
                    lvl_r["lighting_types"].append("{}({})".format(lt, lt_count))

            lvl_r["valid"] = (lvl_r["spawn_points_ok"] and lvl_r["geometry_ok"]
                              and lvl_r["navmesh_ok"])
            lvl_r["errors"] = []
            if ps_count < 10:
                lvl_r["errors"].append("PlayerStarts: {} (need >=10)".format(ps_count))
            if sm_count == 0:
                lvl_r["errors"].append("No geometry")
            if nav_count == 0:
                lvl_r["errors"].append("No NavMesh")

            print("    PS={}, SM={}, Nav={}, Total={}, Lighting={}".format(
                ps_count, sm_count, nav_count, total, lvl_r["lighting_types"]))

        r["level_validation"][level_name] = lvl_r

    # ─── Summary ──────────────────────────────────────────────────────────
    props_set = sum(1 for d in r["dataasset_properties"] if d.get("set_success"))
    r["summary"] = {
        "dataassets_properties_set": props_set,
        "dataassets_saved": r["asset_save"].get("count", 0),
        "valid_bindings": binding_ok,
        "total_dataassets": len(ASSETS),
        "levels_validated": len(r["level_validation"]),
        "load_times_seconds": {
            name: data.get("seconds", 0) for name, data in r.get("load_time", {}).items()
        },
        "levels_load_within_target": {
            name: data.get("within_target", False) for name, data in r.get("load_time", {}).items()
        },
    }

    print("\n" + "=" * 70)
    print("PHASE 6 VALIDATION SUMMARY")
    print("=" * 70)
    print("  DataAssets properties set: {}/13".format(props_set))
    print("  Valid bindings: {}/{}".format(binding_ok, len(ASSETS)))
    print("  Levels validated: {}".format(len(r["level_validation"])))
    for name, data in r.get("load_time", {}).items():
        print("  Load time {}: {:.3f}s ({})".format(
            name, data["seconds"],
            "PASS" if data["within_target"] else "FAIL"))

    return r
