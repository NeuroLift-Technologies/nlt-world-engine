#!/usr/bin/env python3
"""Minimal test to check if WorldEngine module and UScenarioDataAsset class are available."""

import unreal

log = unreal.log
log_error = unreal.log_error

log("=" * 60)
log("Python environment test")
log("=" * 60)

# Check available attributes
log("Checking unreal module attributes...")
attrs = [a for a in dir(unreal) if 'odule' in a.lower() or 'lass' in a.lower()]
log("Module/Class related attributes: {}".format(attrs))

# Try loading class directly
log("Attempting to load UScenarioDataAsset class...")
cls = unreal.load_class(None, "/Script/WorldEngine.ScenarioDataAsset")
if cls:
    log("SUCCESS: Found class {}".format(cls))
else:
    log_error("FAILED: Could not find UScenarioDataAsset")
    # Try alternative
    log("Trying alternative: load_class(None, 'ScenarioDataAsset')")
    cls2 = unreal.load_class(None, "ScenarioDataAsset")
    if cls2:
        log("SUCCESS: Found class {}".format(cls2))
    else:
        log_error("Also failed with just class name")

# Check if WorldEngine module packages are loaded
log("Checking loaded packages...")
try:
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    log("AssetRegistry available: True")
    
    # Check if the class exists in registry
    class_path = unreal.TopLevelAssetPath("/Script/WorldEngine", "ScenarioDataAsset")
    filter = unreal.ARFilter(class_paths=[class_path], recursive_paths=True)
    assets = asset_registry.get_assets(filter)
    log("Assets of type UScenarioDataAsset found: {}".format(len(assets)))
except Exception as e:
    log_error("AssetRegistry error: {}".format(str(e)))
