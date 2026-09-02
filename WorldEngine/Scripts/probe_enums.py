import unreal
import sys

# Write output to a file since UE5 Python print() goes to log
with open("/tmp/probe_enums_output.txt", "w") as f:
    # Find anything that looks like an enum related to Scenario
    candidates = [x for x in dir(unreal) if 'scenario' in x.lower() or 'Scenario' in x]
    f.write("=== Scenario candidates ===\n")
    for c in candidates:
        obj = getattr(unreal, c, None)
        f.write(f"  {c}: {type(obj).__name__} = {obj}\n")

    # Also check if enums are accessible via the module's _unreal or other paths
    f.write("\n=== All enum-like things ===\n")
    for c in dir(unreal):
        obj = getattr(unreal, c, None)
        if obj is not None and type(obj).__name__ == 'EnumType':
            f.write(f"  EnumType: {c} = {obj}\n")

    # Try specific patterns
    f.write("\n=== Direct enum probe ===\n")
    for name in ['EScenarioCategory', 'EScenarioComplexity', 'ScenarioCategory', 'ScenarioComplexity']:
        obj = getattr(unreal, name, 'NOT_FOUND')
        f.write(f"  {name}: {type(obj).__name__ if obj != 'NOT_FOUND' else 'NOT_FOUND'} = {obj}\n")

    # Check all available asset-related enums
    f.write("\n=== Asset/Blueprint enums ===\n")
    for c in sorted(dir(unreal)):
        if 'Asset' in c or 'Blueprint' in c:
            obj = getattr(unreal, c, None)
            if obj is not None and type(obj).__name__ == 'EnumType':
                f.write(f"  {c} = {obj}\n")

    f.write("\nDONE\n")
