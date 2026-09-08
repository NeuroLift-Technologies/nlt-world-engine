using UnrealBuildTool;
using System.IO;

public class NLTGovernanceSubsystem : ModuleRules
{
    public NLTGovernanceSubsystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        // bEnforceIWYU = false;  // Deprecated in UE 5.2; using default IWYU settings instead
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

        string ASFDKPath = Path.Combine(ModuleDirectory, "ThirdParty", "ASFDK");
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "asfdk", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "toi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "otoi", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "rrt-advocate", "include"));
        PublicIncludePaths.Add(Path.Combine(ASFDKPath, "sleepwalker", "include"));
    }
}
