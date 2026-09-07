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
            "MassEntity",
            "MassCore",
            "MassSignals",
            "MassEngine",
            "MassCommon",
            "MassSimulation",
            "AIModule",
            "Json",
            "JsonUtilities",
            "GameplayTasks"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Projects",
            "NavigationSystem",
            "Navmesh",
            "Sockets",
            "Networking"
        });

        // ASFDK-C++ ThirdParty include paths
        string ASFDKPath = Path.Combine(ModuleDirectory, "ThirdParty", "ASFDK");
        
        // Transitive deps (spdlog, nlohmann, tl)
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "include"));
        
        // ASFDK umbrella + all pillar headers
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "asfdk", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "toi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "otoi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "rrt-advocate", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "sleepwalker", "include"));

        // ASFDK static library (prebuilt)
        string ASFDKLibPath = Path.Combine(ASFDKPath, "asfdk", "lib");
        if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ASFDKLibPath, "libasfdk.a"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ASFDKLibPath, "asfdk.lib"));
        }
    }
}
