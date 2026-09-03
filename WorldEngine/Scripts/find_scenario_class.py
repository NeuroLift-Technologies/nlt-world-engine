#!/usr/bin/env python3
"""Find UScenarioDataAsset class in various ways."""

import unreal

# Method 1: load_class with package path
c1 = unreal.load_class(None, "/Script/WorldEngine.ScenarioDataAsset")
print(f"Method 1 (load_class): {c1}")

# Method 2: load_class with just class name
c2 = unreal.load_class(None, "ScenarioDataAsset")
print(f"Method 2 (load_class by name): {c2}")

# Method 3: FindAllAssets with class filter
assets = unreal.EditorAssetLibrary.list_assets("/Game", True, False)
data_asset_paths = [a for a in assets if "Scenario" in a]
print(f"Method 3 - Scenario assets found: {len(data_asset_paths)}")
for p in data_asset_paths[:5]:
    print(f"  {p}")

# Method 4: Use AssetRegistry to find the class
asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
class_names = asset_registry.get_all_class_names()
scenario_classes = [c for c in class_names if "ScenarioDataAsset" in c or "Scenario" in c]
print(f"Method 4 - Scenario classes from registry: {scenario_classes}")

# Method 5: Use get_default_object
all_classes = unreal.__dict__.get("_classes", [])
scenario_in_dict = [k for k in dir(unreal) if "Scenario" in k]
print(f"Method 5 - Scenario in unreal namespace: {scenario_in_dict}")

# Method 6: Try creating directly with factory
factory = unreal.AssetToolsHelpers.get_asset_tools()
# Try using a generic DataAsset factory
data_asset_class = unreal.load_class(None, "UPrimaryDataAsset")
print(f"PrimaryDataAsset class: {data_asset_class}")
