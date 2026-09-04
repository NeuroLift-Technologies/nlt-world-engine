using UnrealBuildTool;
using System.IO;

public class WorldEngine : ModuleRules
{
    public WorldEngine(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "MassEntity",
            "MassCore",
            "MassSignals",
            "MassEngine",
            "MassCommon",
            "MassSimulation",
            "MassMovement",
            "MassCrowd",
            "MassActors",
            "MassRepresentation",
            "MassSpawner",
            "MassSmartObjects",
            "MassLOD",
            "MassReplication",
            "MassAIBehavior",
            "SmartObjectsModule",
            "GameplayTasks",
            "PCG",
            "Json",
            "JsonUtilities",
            "WebSockets",
            "Networking",
            "Sockets",
            "Niagara",
            "NiagaraCore",
            "LearningAgents",
            "LearningAgentsTraining",
            "Learning",
            "LearningTraining"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Projects",
            "NavigationSystem",
            "Navmesh",
            "AudioMixer",
            "AudioMixerCore",
            "HTTPServer",
            "HTTP",
            "Sockets"
        });
    }
}
