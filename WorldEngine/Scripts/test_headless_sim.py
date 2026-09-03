import unreal
print("=== World Engine Headless Test ===")
asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
ar_filter = unreal.ARFilter(package_paths=["/Game/Scenarios"], recursive_paths=True)
assets = asset_registry.get_assets(ar_filter)
print("All assets in /Game/Scenarios found: " + str(len(assets)))
if assets:
    a = assets[0]
    print("AssetData attributes: " + str([x for x in dir(a) if not x.startswith('_')]))
print("=== Test Complete ===")
