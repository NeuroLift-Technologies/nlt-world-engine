using UnrealBuildTool;
using System.IO;

public class NLTGovernanceSubsystem : ModuleRules
{
    public NLTGovernanceSubsystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp23;
        bEnableExceptions = true;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
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

        // ASFDK-C++ ThirdParty include paths
        string ASFDKPath = Path.Combine(ModuleDirectory, "ThirdParty", "ASFDK");
        
        // Transitive deps (spdlog, nlohmann, tl)
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "include"));
        
        // ASFDK umbrella + all pillar headers
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "asfdk", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "toi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "otoi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "rrt-advocate", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "packages", "sleepwalker", "include"));
    }
}
