using UnrealBuildTool;
using System.IO;

public class NLTGovernanceSubsystem : ModuleRules
{
    public NLTGovernanceSubsystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "LearningAgents",
            "Json",
            "JsonUtilities",
            "GameplayTasks"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Projects",
            "NavigationSystem",
            "AIModule",
            "MassEntity",
            "MassCore",
            "MassSignals",
            "MassEngine",
            "MassCommon",
            "MassSimulation",
            "Sockets",
            "Networking"
        });


        // UE 5.8 scans include paths for source files and would pick up duplicate
        // standalone_test.cpp filenames from ASFDK packages if they existed.
        // The tests directories have been renamed to tests_disabled to avoid this.
        string ASFDKPath = Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "ASFDK");
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "asfdk", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "toi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "otoi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "rrt-advocate", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "sleepwalker", "include"));

        // Link the ASFDK-C++ static library (libasfdk.a), pre-built from the
        // asfdk-cplus source tree. The header-only vendored deps (nlohmann/json,
        // tl::expected, spdlog shim) are resolved via the include paths above,
        // so only the compiled ASFDK umbrella + four pillars need linking.
        // The library must be built first — see plugin README "Build Requirements".
        if (Target.Platform == UnrealTargetPlatform.Linux) {
            PublicAdditionalLibraries.Add(Path.Combine(ASFDKPath, "lib", "libasfdk.a"));
            PublicAdditionalLibraries.Add("c++");
        }
        // Win64: Use stub implementations for ASFDK (TODO: build ASFDK lib for Win64)
        else if (Target.Platform == UnrealTargetPlatform.Win64) {
            // Stubs compile inline — no external lib needed
        }
    }
}
