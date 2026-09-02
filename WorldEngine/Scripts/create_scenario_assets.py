"""Create 13 UScenarioDataAsset instances (mirrors scenarios.py).
Run: unrealEditor-Cmd <uproject> -game -nullrhi -run=PythonScriptCommandlet create_scenario_assets.py
"""
import unreal

asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
editor_asset_lib = unreal.EditorAssetLibrary

scenario_class = unreal.load_class(None, "/Script/WorldEngine.ScenarioDataAsset")
if not scenario_class:
    scenario_class = unreal.load_class(None, "UScenarioDataAsset")

# EScenarioCategory: Workplace=0, Personal=1, Social=2, Academic=3 (from UScenarioDataAsset.h)
# EScenarioComplexity: Low=0, Medium=1, High=2
CAT = {"Workplace": 0, "Personal": 1, "Social": 2, "Academic": 3}
COMP = {"Low": 0, "Medium": 1, "High": 2}

SCENARIOS = [
    ("Workplace", "wp_1", "Email Processing", "Process and respond to 20 emails", 30.0, "Medium", 0.4, 0.5, 0.7, True,
     {"email_count": 20, "priority_emails": 5, "interruptions": True, "deadline_pressure": False}),
    ("Workplace", "wp_2", "Report Writing", "Write a comprehensive project report (2000 words)", 90.0, "High", 0.6, 0.8, 0.5, True,
     {"word_count": 2000, "research_required": True, "deadline_pressure": True, "interruptions": False}),
    ("Workplace", "wp_3", "Meeting Participation", "Participate actively in 1-hour team meeting", 60.0, "Medium", 0.3, 0.6, 0.6, True,
     {"participants": 8, "social_elements": True, "structured_agenda": True, "note_taking": True}),
    ("Workplace", "wp_4", "Code Review", "Review and provide feedback on 500 lines of code", 45.0, "High", 0.4, 0.85, 0.6, True,
     {"lines_of_code": 500, "complexity": "medium", "time_limit": True, "interactive": False}),
    ("Workplace", "wp_5", "Deadline Crunch", "Complete urgent task under pressure before end of day", 120.0, "High", 0.8, 0.9, 0.4, True,
     {"urgency": "critical", "pressure": "high", "interruptions": True, "multiple_dependencies": True}),
    ("Personal", "pers_1", "Household Cleaning", "Clean and organize bedroom (1-2 hours)", 120.0, "Medium", 0.7, 0.3, 0.5, False,
     {"room_size": "medium", "organization_needed": True, "motivation_challenge": True}),
    ("Personal", "pers_2", "Grocery Shopping", "Plan, shop, and prepare dinner", 90.0, "Medium", 0.5, 0.6, 0.6, False,
     {"meal_complexity": "medium", "ingredients": 8, "shopping_needed": True}),
    ("Personal", "pers_3", "Bill Paying", "Review bills and pay monthly expenses", 45.0, "Low", 0.8, 0.7, 0.5, True,
     {"bills_count": 8, "complexity": "routine", "avoidance_tendency": True}),
    ("Personal", "pers_4", "Morning Routine", "Complete full morning routine before 8 AM", 60.0, "Medium", 0.4, 0.4, 0.5, False,
     {"components": ["shower", "breakfast", "getting_ready"], "time_limit": True, "motivation": "moderate"}),
    ("Social", "soc_1", "Phone Conversation", "Make and complete important phone call", 15.0, "Medium", 0.6, 0.5, 0.6, True,
     {"caller": "unknown", "duration": 15, "urgency": "normal", "anxiety_level": 0.6}),
    ("Social", "soc_2", "Social Event", "Attend and participate in social gathering", 120.0, "High", 0.7, 0.8, 0.5, False,
     {"group_size": "large", "structured": False, "anxiety_level": 0.7}),
    ("Academic", "acad_1", "Study Session", "Study for exam (2 hours focused study)", 120.0, "High", 0.5, 0.8, 0.5, True,
     {"material_volume": "large", "difficulty": "high", "deadline": 5}),
    ("Academic", "acad_2", "Project Work", "Work on long-term project milestone", 180.0, "High", 0.6, 0.9, 0.4, True,
     {"project_phase": "mid", "deadline_days": 7, "dependencies": True}),
]

if not scenario_class:
    print("ERROR: UScenarioDataAsset class not found - module may need recompilation first")
else:
    print(f"Class: {scenario_class}")
    for cat in ["Workplace", "Personal", "Social", "Academic"]:
        p = f"/Game/Scenarios/{cat}"
        if not editor_asset_lib.does_directory_exist(p):
            editor_asset_lib.make_directory(p)

    count = 0
    for cat, sid, name, desc, dur, cx, av, cog, suc, sf, ctx in SCENARIOS:
        pkg = f"/Game/Scenarios/{cat}/{cat[:3]}_{sid}"
        obj = f"{pkg}.{cat[:3]}_{sid}"
        if editor_asset_lib.does_asset_exist(obj):
            editor_asset_lib.delete_asset(obj)
        asset = asset_tools.create_asset(asset_name=f"{cat[:3]}_{sid}", package_path=f"/Game/Scenarios/{cat}",
                                         asset_class=scenario_class, factory=None)
        if not asset:
            print(f"  FAILED: {cat[:3]}_{sid}")
            continue
        asset.set_editor_property("ScenarioId", unreal.Name(sid))
        asset.set_editor_property("DisplayName", unreal.Text(name))
        asset.set_editor_property("Description", unreal.Text(desc))
        asset.set_editor_property("Category", CAT[cat])
        asset.set_editor_property("DurationMinutes", dur)
        asset.set_editor_property("Complexity", COMP[cx])
        asset.set_editor_property("Aversiveness", av)
        asset.set_editor_property("CognitiveDemand", cog)
        asset.set_editor_property("BaseSuccessRate", suc)
        asset.set_editor_property("bRequiresSustainedFocus", sf)
        ctx_map = {unreal.Name(k): str(v) for k, v in ctx.items()}
        asset.set_editor_property("ContextParams", ctx_map)
        editor_asset_lib.save_asset(obj)
        print(f"  OK: {sid} ({cat}) -> {pkg}")
        count += 1
    print(f"\nDone! Created {count}/13 scenarios.")
