using UnrealBuildTool;
using System.IO;

public class NLTGovernanceSubsystem : ModuleRules
{
    public NLTGovernanceSubsystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseUnity = false;

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

        // ASFDK-C++ ThirdParty include paths via symlink.
        // The symlink lives OUTSIDE the module's Source/ tree (at
        // Plugins/NLTGovernanceSubsystem/ThirdParty/ASFDK) so UnrealBuildTool's
        // source glob never descends into the vendored asfdk-cplus tree and
        // trips over its duplicate standalone_test.cpp filenames.
        // Symlink: ThirdParty/ASFDK -> asfdk-cplus/
        // ModuleDirectory is .../Source/NLTGovernanceSubsystem, so the plugin
        // root is two levels up (.../Plugins/NLTGovernanceSubsystem).
        string ASFDKPath = Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "ASFDK");
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "asfdk", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "toi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "otoi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "rrt-advocate", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "sleepwalker", "include"));

        // Link the ASFDK-C++ static library (libasfdk.a), pre-built from the
        // asfdk-cplus source tree. The header-only vendored deps (nlohmann/json,
        // tl/expected, spdlog shim) are resolved via the include paths above,
        // so only the compiled ASFDK umbrella + four pillars need linking.
        // The library must be built first — see plugin README "Build Requirements".
        if (Target.Platform == UnrealTargetPlatform.Linux) {
            PublicAdditionalLibraries.Add(Path.Combine(ASFDKPath, "lib", "libasfdk.a"));
            PublicAdditionalLibraries.Add("c++");
        }
        // TODO: Add Win64 and Mac library names when cross-platform builds are needed.
    }
}
