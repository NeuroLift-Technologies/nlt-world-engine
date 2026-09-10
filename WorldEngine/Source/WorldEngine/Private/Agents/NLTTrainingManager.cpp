// NLTTrainingManager.cpp — Dual-model, dual-actor RL training
#include "Agents/NLTTrainingManager.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/AvatarAIController.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "NLTGovernanceSubsystem.h"
#include "LearningAgentsManager.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsCritic.h"
#include "LearningAgentsPPOTrainer.h"
#include "LearningAgentsCommunicator.h"
#include "Core/NLTFusionCore.h"

DEFINE_LOG_CATEGORY(LogNLTFusion);

ANLTTrainingManager::ANLTTrainingManager()
{
    PrimaryActorTick.bCanEverTick = true;
    TickInterval = 0.1f;
    bRunInference = true;
    bRunTraining = true;
    MaxEpisodeSteps = 512;
    TrainingTimer = 0.0f;
    bGovernanceInitialized = false;
}

void ANLTTrainingManager::BeginPlay()
{
    Super::BeginPlay();

    // 1. Create Episode Manager
    EpisodeManager = NewObject<UNLTEpisodeManager>(this);
    EpisodeManager->RegisterComponent();
    EpisodeManager->MaxEpisodeSteps = MaxEpisodeSteps;
    EpisodeManager->StepInterval = TickInterval;
    EpisodeManager->OnEpisodeComplete.AddDynamic(this, &ANLTTrainingManager::OnEpisodeComplete);

    // 2. Create Manager
    AgentManager = NewObject<ULearningAgentsManager>(this);
    AgentManager->SetMaxAgentNum(4); // 2 actors + room for expansion

    // 3. Create shared Training Environment
    TrainingEnvironment = NewObject<UNLTTrainingEnvironment>(this);
    TrainingEnvironment->SetupTrainingEnvironment(AgentManager);

    // 4. Initialize model groups (A and B)
    InitializeModelGroups();

    // 5. Spawn the two actors
    SpawnDualActors();

    // 6. Start episode
    if (EpisodeManager)
    {
        EpisodeManager->StartEpisode();
    }

    UE_LOG(LogNLTFusion, Log, TEXT("NLTTrainingManager: Dual-model training initialized with %d model groups"), ModelGroups.Num());
}

void ANLTTrainingManager::InitializeModelGroups()
{
    ModelGroups.SetNum(2);

    // Model Group A
    ModelGroups[0].GroupId = 0;
    ModelGroups[0].GroupName = TEXT("ModelA");
    ModelGroups[0].SpawnLocation = ActorAStartLocation;
    ModelGroups[0].GovernanceAgentId = TEXT("ActorA");

    ModelGroups[0].Interactor = NewObject<UNLTAvatarInteractor>(this);
    ModelGroups[0].Interactor->SetupInteractor(AgentManager);

    ModelGroups[0].Policy = NewObject<ULearningAgentsPolicy>(this);
    FLearningAgentsPolicySettings PolicySettingsA;
    PolicySettingsA.HiddenLayerNum = 2;
    PolicySettingsA.HiddenLayerSize = 128;
    PolicySettingsA.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    ModelGroups[0].Policy->SetupPolicy(AgentManager, ModelGroups[0].Interactor, nullptr, nullptr, nullptr, true, true, true, PolicySettingsA, 1234);

    ModelGroups[0].Critic = NewObject<ULearningAgentsCritic>(this);
    FLearningAgentsCriticSettings CriticSettingsA;
    CriticSettingsA.HiddenLayerNum = 2;
    CriticSettingsA.HiddenLayerSize = 128;
    CriticSettingsA.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    ModelGroups[0].Critic->SetupCritic(AgentManager, ModelGroups[0].Interactor, ModelGroups[0].Policy, nullptr, true, CriticSettingsA, 1234);

    ModelGroups[0].Trainer = NewObject<ULearningAgentsPPOTrainer>(this);
    FLearningAgentsCommunicator CommunicatorA = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryTrainingProcess();
    FLearningAgentsPPOTrainerSettings TrainerSettingsA;
    TrainerSettingsA.MaxEpisodeStepNum = MaxEpisodeSteps;
    TrainerSettingsA.MaximumRecordedEpisodesPerIteration = 1000;
    TrainerSettingsA.MaximumRecordedStepsPerIteration = 10000;
    ModelGroups[0].Trainer->SetupPPOTrainer(AgentManager, ModelGroups[0].Interactor, TrainingEnvironment, ModelGroups[0].Policy, ModelGroups[0].Critic, CommunicatorA, TrainerSettingsA);

    // Model Group B
    ModelGroups[1].GroupId = 1;
    ModelGroups[1].GroupName = TEXT("ModelB");
    ModelGroups[1].SpawnLocation = ActorBStartLocation;
    ModelGroups[1].GovernanceAgentId = TEXT("ActorB");

    ModelGroups[1].Interactor = NewObject<UNLTAvatarInteractor>(this);
    ModelGroups[1].Interactor->SetupInteractor(AgentManager);

    ModelGroups[1].Policy = NewObject<ULearningAgentsPolicy>(this);
    FLearningAgentsPolicySettings PolicySettingsB;
    PolicySettingsB.HiddenLayerNum = 2;
    PolicySettingsB.HiddenLayerSize = 128;
    PolicySettingsB.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    ModelGroups[1].Policy->SetupPolicy(AgentManager, ModelGroups[1].Interactor, nullptr, nullptr, nullptr, true, true, true, PolicySettingsB, 5678);

    ModelGroups[1].Critic = NewObject<ULearningAgentsCritic>(this);
    FLearningAgentsCriticSettings CriticSettingsB;
    CriticSettingsB.HiddenLayerNum = 2;
    CriticSettingsB.HiddenLayerSize = 128;
    CriticSettingsB.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    ModelGroups[1].Critic->SetupCritic(AgentManager, ModelGroups[1].Interactor, ModelGroups[1].Policy, nullptr, true, CriticSettingsB, 5678);

    ModelGroups[1].Trainer = NewObject<ULearningAgentsPPOTrainer>(this);
    FLearningAgentsCommunicator CommunicatorB = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryTrainingProcess();
    FLearningAgentsPPOTrainerSettings TrainerSettingsB;
    TrainerSettingsB.MaxEpisodeStepNum = MaxEpisodeSteps;
    TrainerSettingsB.MaximumRecordedEpisodesPerIteration = 1000;
    TrainerSettingsB.MaximumRecordedStepsPerIteration = 10000;
    ModelGroups[1].Trainer->SetupPPOTrainer(AgentManager, ModelGroups[1].Interactor, TrainingEnvironment, ModelGroups[1].Policy, ModelGroups[1].Critic, CommunicatorB, TrainerSettingsB);

    UE_LOG(LogNLTFusion, Log, TEXT("NLTTrainingManager: Initialized 2 model groups (A and B)"));
}

void ANLTTrainingManager::SpawnDualActors()
{
    UWorld* World = GetWorld();
    if (!World) return;

    for (int32 i = 0; i < ModelGroups.Num(); i++)
    {
        FVector SpawnPos = ModelGroups[i].SpawnLocation;
        FRotator SpawnRot = FRotator::ZeroRotator;

        AAvatarCharacter* Actor = World->SpawnActor<AAvatarCharacter>(AAvatarCharacter::StaticClass(), SpawnPos, SpawnRot);
        if (Actor)
        {
            int32 AgentId = AgentManager->AddAgent(Actor);
            ModelGroups[i].AgentId = AgentId;

            // Initialize governance for this actor
            InitializeGovernanceForGroup(i, Actor);

            UE_LOG(LogNLTFusion, Log, TEXT("NLTTrainingManager: Spawned %s at (%s), AgentId=%d"),
                *ModelGroups[i].GroupName.ToString(), *SpawnPos.ToString(), AgentId);
        }
        else
        {
            UE_LOG(LogNLTFusion, Error, TEXT("NLTTrainingManager: Failed to spawn %s"), *ModelGroups[i].GroupName.ToString());
        }
    }
}

void ANLTTrainingManager::InitializeGovernanceForGroup(int32 GroupIndex, AAvatarCharacter* Actor)
{
    if (!Actor || !AgentManager) return;

    // Get the governance subsystem for this world
    UNLTGovernanceSubsystem* Governance = UNLTGovernanceSubsystem::Get(Actor->GetWorld());
    if (Governance)
    {
        FName GovId = ModelGroups[GroupIndex].GovernanceAgentId;
        FString GovName = ModelGroups[GroupIndex].GroupName.ToString();
        Governance->InitializeAgent(GovId, GovName);
        UE_LOG(LogNLTFusion, Log, TEXT("NLTTrainingManager: Governance initialized for %s"), *GovId.ToString());
    }
    else
    {
        UE_LOG(LogNLTFusion, Warning, TEXT("NLTTrainingManager: No NLTGovernanceSubsystem found for %s"),
            *ModelGroups[GroupIndex].GroupName.ToString());
    }
}

void ANLTTrainingManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Tick cognitive decay for all agents
    if (AgentManager)
    {
        const TArray<int32>& AllAgentIds = AgentManager->GetAllAgentIds();
        for (int32 AgentId : AllAgentIds)
        {
            UObject* Agent = AgentManager->GetAgent(AgentId);
            AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
            if (Avatar && Avatar->CognitiveState)
            {
                Avatar->CognitiveState->TickCognitiveDecay(DeltaTime);
            }
        }
    }

    // Run inference for both models
    if (bRunInference)
    {
        RunDualInference();
    }

    // Throttle training
    TrainingTimer += DeltaTime;
    if (bRunTraining && TrainingTimer >= 1.0f)
    {
        TrainingTimer = 0.0f;
        RunDualTraining();
    }

    // Check cognitive-based episode completion
    if (EpisodeManager && EpisodeManager->bEpisodeActive)
    {
        for (const auto& Group : ModelGroups)
        {
            if (Group.AgentId == INDEX_NONE) continue;
            UObject* Agent = AgentManager->GetAgent(Group.AgentId);
            AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
            if (Avatar && Avatar->CognitiveState)
            {
                EpisodeManager->CheckCognitiveCompletion(
                    Avatar->CognitiveState->Independence,
                    Avatar->CognitiveState->Burnout);
            }
        }
    }
}

void ANLTTrainingManager::RunDualInference()
{
    for (const auto& Group : ModelGroups)
    {
        if (Group.Policy)
        {
            Group.Policy->RunInference(1.0f);
        }
    }
}

void ANLTTrainingManager::RunDualTraining()
{
    FLearningAgentsPPOTrainingSettings TrainingSettings;
    TrainingSettings.NumberOfIterations = 1;
    TrainingSettings.LearningRatePolicy = 1e-4f;
    TrainingSettings.LearningRateCritic = 1e-3f;
    TrainingSettings.DiscountFactor = 0.99f;
    TrainingSettings.GaeLambda = 0.95f;
    TrainingSettings.EpsilonClip = 0.2f;

    FLearningAgentsTrainingGameSettings GameSettings;
    GameSettings.bUseFixedTimeStep = true;
    GameSettings.FixedTimeStepFrequency = 60.0f;

    for (const auto& Group : ModelGroups)
    {
        if (Group.Trainer)
        {
            Group.Trainer->RunTraining(TrainingSettings, GameSettings, true, true);
        }
    }
}

int32 ANLTTrainingManager::GetActorAgentId(int32 GroupIndex) const
{
    if (ModelGroups.IsValidIndex(GroupIndex))
    {
        return ModelGroups[GroupIndex].AgentId;
    }
    return INDEX_NONE;
}

void ANLTTrainingManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Shutdown governance for all agents
    UWorld* World = GetWorld();
    if (World)
    {
        UNLTGovernanceSubsystem* Governance = UNLTGovernanceSubsystem::Get(World);
        if (Governance)
        {
            for (const auto& Group : ModelGroups)
            {
                if (Group.GovernanceAgentId != NAME_None)
                {
                    Governance->ShutdownAgent(Group.GovernanceAgentId);
                }
            }
        }
    }

    Super::EndPlay(EndPlayReason);
}
