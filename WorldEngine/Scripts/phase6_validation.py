#!/usr/bin/env python3
"""
Phase 6 Validation Script — NLT Fusion World Engine
====================================================

Performs comprehensive validation of scenario assets and build integrity:

1. Creates 13 UScenarioDataAsset instances
2. Validates all 4 .umap levels for geometry, spawn points, and missing references
3. Verifies DataAsset -> Level binding (TSoftObjectPtr<UWorld> LevelReference)
4. Measures scenario load times from disk (target: <30s per level)

Run via:
  UnrealEditor-Cmd -project=WorldEngine.uproject -nullrhi \
     -run=PythonScriptCommandlet \
     -Script=/absolute/path/to/phase6_validation.py
"""

import unreal
import time
import json
import os

# ─── CONFIGURATION ───────────────────────────────────────────────────────────

LEVEL_MAP = {
    "Workplace": "/Game/Scenarios/Levels/Workplace_Level.Workplace_Level",
    "Personal":  "/Game/Scenarios/Levels/Personal_Level.Personal_Level",
    "Social":    "/Game/Scenarios/Levels/Social_Level.Social_Level",
    "Academic":  "/Game/Scenarios/Levels/Academic_Level.Academic_Level",
}

SCENARIO_CATEGORY = {
    "Workplace": unreal.ScenarioCategory.WORKPLACE,
    "Personal": unreal.ScenarioCategory.PERSONAL,
    "Social": unreal.ScenarioCategory.SOCIAL,
    "Academic": unreal.ScenarioCategory.ACADEMIC,
}
SCENARIO_COMPLEXITY = {
    "Low": unreal.ScenarioComplexity.LOW,
    "Medium": unreal.ScenarioComplexity.MEDIUM,
    "High": unreal.ScenarioComplexity.HIGH,
}

SCENARIOS = [
    ("Workplace", "EmailProcessing",         "workplace_email_processing",       "Email Processing",     45.0,  "Medium", 0.3, 0.6, 0.7,  True),
    ("Workplace", "ReportWriting",           "workplace_report_writing",         "Report Writing",       120.0, "High",   0.6, 0.9, 0.6,  True),
    ("Workplace", "MeetingParticipation",    "workplace_meeting_participation",  "Meeting Participation", 60.0, "Medium", 0.4, 0.5, 0.75, False),
    ("Workplace", "CodeReview",              "workplace_code_review",            "Code Review",          90.0,  "High",   0.5, 0.8, 0.65, True),
    ("Workplace", "DeadlineCrunch",          "workplace_deadline_crunch",        "Deadline Crunch",     180.0, "High",   0.9, 0.95, 0.5, True),
    ("Personal",  "HouseholdCleaning",       "personal_household_cleaning",      "Household Cleaning",   60.0,  "Low",    0.4, 0.2, 0.85, False),
    ("Personal",  "GroceryShopping",         "personal_grocery_shopping",        "Grocery Shopping",     45.0,  "Medium", 0.3, 0.4, 0.8,  False),
    ("Personal",  "BillPaying",              "personal_bill_paying",             "Bill Paying",          20.0,  "Low",    0.5, 0.6, 0.9,  False),
    ("Personal",  "MorningRoutine",          "personal_morning_routine",         "Morning Routine",      30.0,  "Low",    0.1, 0.3, 0.95, False),
    ("Social",    "PhoneConversation",       "social_phone_conversation",        "Phone Conversation",   15.0,  "Low",    0.7, 0.6, 0.7,  False),
    ("Social",    "SocialEvent",             "social_event",                     "Social Event",        120.0,  "High",   0.85, 0.5, 0.6, True),
    ("Academic",  "StudySession",            "academic_study_session",           "Study Session",       90.0,  "Medium", 0.4, 0.8, 0.75, True),
    ("Academic",  "ProjectWork",             "academic_project_work",            "Project Work",         150.0, "High",   0.5, 0.9, 0.65, True),
]

LEVEL_PATHS = [
    "/Game/Scenarios/Levels/Workplace_Level",
    "/Game/Scenarios/Levels/Personal_Level",
    "/Game/Scenarios/Levels/Social_Level",
    "/Game/Scenarios/Levels/Academic_Level",
]

results = {
    "dataasset_creation": {"created": [], "failed": []},
    "level_validation": {},
    "binding_validation": {},
    "load_time": {},
    "build_integration": {},
}

def log(msg):
    unreal.log(msg)

def log_error(msg):
    unreal.log_error(msg)

def log_warning(msg):
    unreal.log_warning(msg)

# ─── Ensure WorldEngine symbols are available ───────────────────────────────
# In some commandlet runtimes unreal.ModuleManager is not exposed to Python.
if hasattr(unreal, "ModuleManager"):
    module_manager = unreal.ModuleManager.get()
    if not module_manager.is_module_loaded("WorldEngine"):
        module_manager.load_module("WorldEngine")
        log("WorldEngine module loaded.")
    else:
        log("WorldEngine module already loaded.")
else:
    log_warning("unreal.ModuleManager not exposed; assuming WorldEngine module is already loaded")

# ─── PHASE 6a: Create 13 DataAssets ─────────────────────────────────────────

log("")
log("=" * 70)
log("PHASE 6a: Creating 13 Scenario DataAssets")
log("=" * 70)

asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
editor_asset_lib = unreal.EditorAssetLibrary

# Create directories
for cat in ["Workplace", "Personal", "Social", "Academic"]:
    path = "/Game/Scenarios/{}".format(cat)
    if not editor_asset_lib.does_directory_exist(path):
        editor_asset_lib.make_directory(path)
        log("  Created directory: {}".format(path))

# Load the UScenarioDataAsset class
scenario_class = unreal.load_class(None, "/Script/WorldEngine.ScenarioDataAsset")
if not scenario_class:
    scenario_class = unreal.load_class(None, "ScenarioDataAsset")

if not scenario_class:
    log_error("FATAL: UScenarioDataAsset class not found after module load!")
else:
    log("Loaded class: {}".format(scenario_class))
    created_count = 0

    for cat, short_name, scenario_id, display_name, duration, complexity_str, averseness, cognitive, success, sustained in SCENARIOS:
        dir_path = "/Game/Scenarios/{}".format(cat)
        asset_name = "{}_{}".format(cat[:3], short_name)
        full_path = "{}/{}".format(dir_path, asset_name)
        object_path = "{}.{}".format(full_path, asset_name)

        # Delete if exists
        if editor_asset_lib.does_asset_exist(object_path):
            editor_asset_lib.delete_asset(object_path)

        # Create asset
        asset = asset_tools.create_asset(
            asset_name=asset_name,
            package_path=dir_path,
            asset_class=scenario_class,
            factory=None,
        )

        if not asset:
            log("FAILED to create {}".format(asset_name))
            results["dataasset_creation"]["failed"].append(asset_name)
            continue

        # Set properties
        asset.set_editor_property("ScenarioId", unreal.Name(scenario_id))
        asset.set_editor_property("DisplayName", unreal.Text(display_name))
        asset.set_editor_property("Description", unreal.Text("Auto-generated scenario: {}".format(display_name)))
        asset.set_editor_property("Category", SCENARIO_CATEGORY[cat])
        asset.set_editor_property("DurationMinutes", duration)
        asset.set_editor_property("Complexity", SCENARIO_COMPLEXITY[complexity_str])
        asset.set_editor_property("Aversiveness", averseness)
        asset.set_editor_property("CognitiveDemand", cognitive)
        asset.set_editor_property("BaseSuccessRate", success)
        asset.set_editor_property("bRequiresSustainedFocus", sustained)
        level_world = unreal.load_object(None, LEVEL_MAP[cat])
        if not level_world:
            log_warning("  Could not resolve level object: {}".format(LEVEL_MAP[cat]))
        asset.set_editor_property("LevelReference", level_world)

        # Save
        editor_asset_lib.save_asset(object_path)
        log("  Created {}".format(full_path))
        results["dataasset_creation"]["created"].append(asset_name)
        created_count += 1

    log("Done! Created {} scenario DataAssets.".format(created_count))

# ─── PHASE 6b: Validate .umap Levels ────────────────────────────────────────

log("")
log("=" * 70)
log("PHASE 6b: Validating 4 .umap Levels")
log("=" * 70)

editor_level_lib = unreal.EditorLevelLibrary
asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()

for level_path in LEVEL_PATHS:
    level_name = level_path.split("/")[-1]
    log("--- Validating: {} ---".format(level_name))

    level_result = {
        "actors_total": 0,
        "has_geometry": False,
        "geometry_types": [],
        "player_starts": 0,
        "spawn_point_labels": [],
        "lighting_types": [],
        "navmesh_present": False,
        "missing_references": [],
        "errors": [],
    }

    # Check if level exists in asset registry first (using correct API)
    try:
        # get_assets with a path filter
        ar_filter = unreal.ARFilter(
            package_paths=[level_path],
            recursive_paths=True,
        )
        assets = asset_registry.get_assets(ar_filter)

        if len(assets) == 0:
            level_result["errors"].append("Level not found in asset registry: {}".format(level_path))
            results["level_validation"][level_name] = level_result
            log_error("  Level not found in registry: {}".format(level_path))
            continue

        asset_data = assets[0]
        log("  Level found in asset registry: {} (class: {})".format(
            asset_data.object_path, asset_data.asset_class))
    except Exception as e:
        level_result["errors"].append("Asset registry lookup error: {}".format(str(e)))
        log_error("  Asset registry error: {}".format(str(e)))
        results["level_validation"][level_name] = level_result
        continue

    # Load the level
    try:
        success = editor_level_lib.load_level(level_path)
        if not success:
            level_result["errors"].append("editor_level_lib.load_level() returned False")
            results["level_validation"][level_name] = level_result
            log_error("  Failed to load level")
            continue

        # Get the editor world
        world = editor_level_lib.get_editor_world()

        if world:
            actors = unreal.GameplayStatics.get_all_actors(world)
        else:
            actors = []

        level_result["actors_total"] = len(actors)
        log("  Total actors: {}".format(len(actors)))

        for actor in actors:
            actor_class = actor.get_class()
            class_name = actor_class.get_name()
            actor_label = actor.get_actor_label() if actor.get_actor_label() else class_name

            # Check for geometry (StaticMeshActor, Brush)
            if class_name in ("StaticMeshActor", "Brush"):
                level_result["has_geometry"] = True
                if class_name not in level_result["geometry_types"]:
                    level_result["geometry_types"].append(class_name)

                # Check if static mesh is valid
                if class_name == "StaticMeshActor":
                    sm_components = actor.get_components_by_class(unreal.StaticMeshComponent)
                    for sm_comp in sm_components:
                        static_mesh = sm_comp.get_editor_property("static_mesh")
                        if static_mesh is None or not static_mesh.get_path_name():
                            level_result["missing_references"].append(
                                "StaticMeshActor '{}' has missing/unresolved static mesh".format(actor_label)
                            )

            # Check for PlayerStart (spawn points)
            if "PlayerStart" in class_name:
                level_result["player_starts"] += 1
                level_result["spawn_point_labels"].append(actor_label)

            # Check for lighting
            lighting_classes = ["DirectionalLight", "PointLight", "SpotLight", "SkyLight",
                               "SkyAtmosphere", "ExponentialHeightFog", "VolumetricCloud",
                               "RectLight", "SphereDirectionalLight"]
            if class_name in lighting_classes:
                if class_name not in level_result["lighting_types"]:
                    level_result["lighting_types"].append(class_name)

            # Check for NavMesh
            if "NavMeshBoundsVolume" in class_name:
                level_result["navmesh_present"] = True

        # Check for NavMesh via navigation system
        if world:
            nav_data = unreal.NavigationSystemV1.get_current(world)
            if nav_data:
                level_result["navmesh_present"] = True

        # Check for spawn point count (requirement: >= 10 per level per SCENARIO_PLAN.md)
        if level_result["player_starts"] < 10:
            level_result["errors"].append(
                "Insufficient spawn points: {} found, need >= 10 (per SCENARIO_PLAN.md Phase 2)".format(
                    level_result["player_starts"])
            )

        if not level_result["has_geometry"]:
            level_result["errors"].append("No geometry found (StaticMeshActor or Brush)")

        if not level_result["navmesh_present"]:
            level_result["errors"].append("No NavMesh bounds volume found")

        # Summary
        log("  Geometry: {} (types: {})".format(
            "YES" if level_result["has_geometry"] else "NO",
            level_result["geometry_types"]))
        log("  PlayerStarts: {}".format(level_result["player_starts"]))
        log("  Spawn point labels: {}".format(level_result["spawn_point_labels"]))
        log("  Lighting: {}".format(level_result["lighting_types"]))
        log("  NavMesh present: {}".format(level_result["navmesh_present"]))
        log("  Missing references: {}".format(len(level_result["missing_references"])))
        for mr in level_result["missing_references"][:10]:
            log("    - {}".format(mr))
        log("  Errors: {}".format(len(level_result["errors"])))
        for err in level_result["errors"]:
            log("    ERROR: {}".format(err))

        results["level_validation"][level_name] = level_result

        # Unload the level
        editor_level_lib.unload_current_level()

    except Exception as e:
        level_result["errors"].append("Exception during validation: {}".format(str(e)))
        log_error("  Exception validating {}: {}".format(level_name, str(e)))
        results["level_validation"][level_name] = level_result

# ─── PHASE 6c: Validate DataAsset -> Level Binding ──────────────────────────

log("")
log("=" * 70)
log("PHASE 6c: Validating DataAsset -> Level Binding")
log("=" * 70)

# Find all scenario DataAssets using asset registry
scenario_class_path = unreal.TopLevelAssetPath("/Script/WorldEngine", "ScenarioDataAsset")
ar_filter = unreal.ARFilter(
    class_paths=[scenario_class_path],
    recursive_paths=True,
)
asset_data_array = asset_registry.get_assets(ar_filter)

log("Found {} scenario DataAssets".format(len(asset_data_array)))

# If no DataAssets found via registry, reload them
if len(asset_data_array) == 0:
    log("  No DataAssets found via registry, scanning /Game/Scenarios/...")
    editor_asset_lib = unreal.EditorAssetLibrary
    asset_paths = editor_asset_lib.list_assets("/Game/Scenarios", True, False)
    log("  Found {} assets in /Game/Scenarios: {}".format(len(asset_paths), asset_paths))

    for path in asset_paths:
        ar_filter2 = unreal.ARFilter(
            object_paths=[path],
        )
        assets = asset_registry.get_assets(ar_filter2)
        asset_data_array.extend(assets)

    log("  Total after scan: {}".format(len(asset_data_array)))

for asset_data in asset_data_array:
    asset = asset_data.get_asset()
    if not asset:
        asset = asset_data.get_asset()
        if not asset:
            log_warning("  Could not load asset: {}".format(asset_data.object_path))
            continue

    try:
        scenario_id = str(asset.get_editor_property("ScenarioId"))
    except Exception:
        scenario_id = str(asset_data.asset_name)

    try:
        level_ref = asset.get_editor_property("LevelReference")
    except Exception:
        level_ref = None

    try:
        display_name = str(asset.get_editor_property("DisplayName"))
    except Exception:
        display_name = ""

    try:
        category = str(asset.get_editor_property("Category"))
    except Exception:
        category = ""

    binding_result = {
        "scenario_id": scenario_id,
        "display_name": display_name,
        "category": category,
        "level_reference_soft": level_ref.get_path_name() if level_ref else "",
        "is_null": level_ref is None,
        "resolves": False,
        "loaded_level_path": "",
        "valid": False,
    }

    if level_ref:
        level_obj_path = level_ref.get_path_name()
        binding_result["level_reference_soft"] = level_obj_path

        # Check if the referenced level exists in the asset registry
        ar_filter_check = unreal.ARFilter(
            object_paths=[level_obj_path],
        )
        level_assets = asset_registry.get_assets(ar_filter_check)

        if len(level_assets) > 0:
            level_asset_data = level_assets[0]
            binding_result["resolves"] = True
            binding_result["loaded_level_path"] = level_asset_data.object_path
            binding_result["valid"] = True
            log("  [OK] {} -> {}".format(scenario_id, level_asset_data.object_path))
        else:
            log_warning("  [WARN] {} -> {} (not found in asset registry)".format(scenario_id, level_obj_path))

            # Check if file exists on disk
            level_filename = LEVEL_MAP.get(category.split(".")[-1], "")
            if level_filename:
                disk_path = level_filename.replace("/Game/", "/home/joshd/Desktop/nlt-repos/nlt-fusion/WorldEngine/Content/").replace(".", "/") + ".umap"
                if os.path.exists(disk_path):
                    binding_result["resolves"] = True
                    binding_result["valid"] = True
                    log("    Asset exists on disk: {}".format(disk_path))
                else:
                    log_error("    Asset does NOT exist on disk: {}".format(disk_path))

    else:
        binding_result["valid"] = False
        log_error("  [FAIL] {} -> LevelReference is null".format(scenario_id))

    results["binding_validation"][scenario_id] = binding_result

log("Validated {} DataAsset -> Level bindings".format(len(asset_data_array)))

# ─── PHASE 6d: Load Time Testing ────────────────────────────────────────────

log("")
log("=" * 70)
log("PHASE 6d: Load Time Testing (target: <30s per level)")
log("=" * 70)

for level_path in LEVEL_PATHS:
    level_name = level_path.split("/")[-1]
    log("--- Load time test: {} ---".format(level_name))

    # Force GC before each test
    unreal.collect_garbage()

    start_time = time.time()

    try:
        # Load the level
        success = editor_level_lib.load_level(level_path)
        elapsed = time.time() - start_time

        load_result = {
            "level": level_name,
            "load_time_seconds": round(elapsed, 3),
            "target_seconds": 30,
            "within_target": elapsed < 30,
            "success": success,
        }

        if success:
            world = editor_level_lib.get_editor_world()
            actor_count = len(unreal.GameplayStatics.get_all_actors(world)) if world else 0
            load_result["actors_after_load"] = actor_count
            log("  Load time: {:.3f}s (target: <30s) - {}".format(
                elapsed, "PASS" if elapsed < 30 else "FAIL"
            ))
            log("  Actors in loaded level: {}".format(actor_count))
        else:
            load_result["within_target"] = False
            log_error("  FAILED to load level")

        # Unload
        editor_level_lib.unload_current_level()

    except Exception as e:
        elapsed = time.time() - start_time
        load_result = {
            "level": level_name,
            "load_time_seconds": round(elapsed, 3),
            "target_seconds": 30,
            "within_target": False,
            "success": False,
            "error": str(e),
        }
        log_error("  Exception: {}".format(str(e)))

    results["load_time"][level_name] = load_result

# ─── PHASE 6e: Build Integration Check ───────────────────────────────────────

log("")
log("=" * 70)
log("PHASE 6e: Build Integration Check")
log("=" * 70)

# Verify the WorldEngine module is loaded (if Python API exposes ModuleManager)
if hasattr(unreal, "ModuleManager"):
    module_manager = unreal.ModuleManager.get()
    module_loaded = module_manager.is_module_loaded("WorldEngine")
else:
    module_loaded = None

build_result = {
    "module_loaded": module_loaded,
    "dataasset_class_available": scenario_class is not None,
    "dataasset_count": len(asset_data_array),
    "all_bindings_valid": all(r["valid"] for r in results["binding_validation"].values()),
}

log("  WorldEngine module loaded: {}".format(module_loaded))
log("  UScenarioDataAsset class available: {}".format(scenario_class is not None))
log("  Scenario DataAssets created: {}".format(len(asset_data_array)))
log("  All bindings valid: {}".format(build_result["all_bindings_valid"]))

# Verify level packages exist
for level_path in LEVEL_PATHS:
    level_name = level_path.split("/")[-1]
    try:
        ar_filter_lvl = unreal.ARFilter(
            package_paths=[level_path],
            recursive_paths=True,
        )
        assets = asset_registry.get_assets(ar_filter_lvl)
        build_result["level_{}_in_registry".format(level_name)] = len(assets) > 0
        if len(assets) > 0:
            build_result["level_{}_class".format(level_name)] = assets[0].asset_class
    except Exception as e:
        build_result["level_{}_error".format(level_name)] = str(e)

results["build_integration"] = build_result

# ─── SUMMARY ────────────────────────────────────────────────────────────────

log("")
log("=" * 70)
log("PHASE 6 VALIDATION SUMMARY")
log("=" * 70)

log("DataAsset Creation:")
log("  Created: {} / Failed: {}".format(
    len(results["dataasset_creation"]["created"]),
    len(results["dataasset_creation"]["failed"])))

log("Level Validation:")
for level_name, data in results["level_validation"].items():
    log("  {}: actors={}, player_starts={}, geometry_types={}, lighting={}, navmesh={}, missing_refs={}, errors={}".format(
        level_name, data["actors_total"], data["player_starts"],
        data["geometry_types"], len(data["lighting_types"]),
        data["navmesh_present"], len(data["missing_references"]),
        len(data["errors"])
    ))

log("DataAsset -> Level Binding:")
for scenario_id, data in results["binding_validation"].items():
    status = "VALID" if data["valid"] else "INVALID"
    log("  {} -> {} [{}]".format(scenario_id, data.get("loaded_level_path", "N/A"), status))

log("Load Times:")
for level_name, data in results["load_time"].items():
    status = "PASS" if data["within_target"] else "FAIL"
    log("  {}: {:.3f}s (target <30s) [{}]".format(
        level_name, data["load_time_seconds"], status))

log("Build Integration:")
log("  Module loaded: {}".format(build_result["module_loaded"]))
log("  DataAsset class available: {}".format(build_result["dataasset_class_available"]))
log("  All bindings valid: {}".format(build_result["all_bindings_valid"]))

# Save results to JSON
output_path = "/home/joshd/Desktop/nlt-repos/nlt-fusion/WorldEngine/Saved/Phase6ValidationReport.json"
with open(output_path, "w") as f:
    json.dump(results, f, indent=2, default=str)

log("")
log("Validation report saved to: {}".format(output_path))
log("=" * 70)
log("PHASE 6 VALIDATION COMPLETE")
log("=" * 70)
