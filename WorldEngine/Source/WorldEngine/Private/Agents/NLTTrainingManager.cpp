// NLTTrainingManager.cpp — Single shared policy, single critic, two actors
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

ANLTTrainingManager::ANLTTrainingManager()
{
    PrimaryActorTick.bCanEverTick = true;
    TickInterval = 0.1f;
    bRunInference = true;
    bRunTraining = true;
    MaxEpisodeSteps = 512;
    TrainingTimer = 0.0f;
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

    // 2. Create shared Manager
    AgentManager = NewObject<ULearningAgentsManager>(this);
    AgentManager->SetMaxAgentNum(2);

    // 3. Create shared Training Environment
    TrainingEnvironment = NewObject<UNLTTrainingEnvironment>(this);
    TrainingEnvironment->SetupTrainingEnvironment(AgentManager);

    // 4. Initialize training
    InitializeTraining();

    // 5. Spawn the two actors
    SpawnDualActors();

    // 6. Start episode
    if (EpisodeManager)
    {
        EpisodeManager->StartEpisode();
    }

    UE_LOG(LogTemp, Log, TEXT("NLTTrainingManager: Training initialized"));
}

void ANLTTrainingManager::InitializeTraining()
{
    // Shared interactor
    UNLTAvatarInteractor* AvatInteractor = NewObject<UNLTAvatarInteractor>(this);
    ULearningAgentsInteractor* LearningInteractor = AvatInteractor;
    AvatInteractor->SetupInteractor(AgentManager);

    // Shared policy
    Policy = NewObject<ULearningAgentsPolicy>(this);
    FLearningAgentsPolicySettings PolicySettings;
    PolicySettings.HiddenLayerNum = 2;
    PolicySettings.HiddenLayerSize = 128;
    PolicySettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    Policy->SetupPolicy(AgentManager, LearningInteractor, nullptr, nullptr, nullptr, true, true, true, PolicySettings, 1234);

    // Shared critic
    Critic = NewObject<ULearningAgentsCritic>(this);
    FLearningAgentsCriticSettings CriticSettings;
    CriticSettings.HiddenLayerNum = 2;
    CriticSettings.HiddenLayerSize = 128;
    CriticSettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    Critic->SetupCritic(AgentManager, LearningInteractor, Policy, nullptr, true, CriticSettings, 1234);

    // Shared PPO trainer
    Trainer = NewObject<ULearningAgentsPPOTrainer>(this);
    FLearningAgentsCommunicator Communicator = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryTrainingProcess();
    FLearningAgentsPPOTrainerSettings TrainerSettings;
    TrainerSettings.MaxEpisodeStepNum = MaxEpisodeSteps;
    TrainerSettings.MaximumRecordedEpisodesPerIteration = 1000;
    TrainerSettings.MaximumRecordedStepsPerIteration = 10000;
    Trainer->SetupPPOTrainer(AgentManager, LearningInteractor, TrainingEnvironment, Policy, Critic, Communicator, TrainerSettings);

    UE_LOG(LogTemp, Log, TEXT("NLTTrainingManager: Training initialized"));
}

void ANLTTrainingManager::SpawnDualActors()
{
    UWorld* World = GetWorld();
    if (!World) return;

    TArray<FVector> SpawnLocations = { ActorAStartLocation, ActorBStartLocation };
    TArray<FName> GovIds = { TEXT("ActorA"), TEXT("ActorB") };

    for (int32 i = 0; i < SpawnLocations.Num(); i++)
    {
        FVector SpawnPos = SpawnLocations[i];
        FRotator SpawnRot = FRotator::ZeroRotator;

        AAvatarCharacter* Actor = World->SpawnActor<AAvatarCharacter>(AAvatarCharacter::StaticClass(), SpawnPos, SpawnRot);
        if (Actor)
        {
            int32 AgentId = AgentManager->AddAgent(Actor);
            if (AgentId == INDEX_NONE)
            {
                UE_LOG(LogTemp, Error, TEXT("NLTTrainingManager: Failed to register actor %d"), i);
                Actor->Destroy();
                continue;
            }

            UE_LOG(LogTemp, Log, TEXT("NLTTrainingManager: Spawned actor %d at (%s), AgentId=%d"),
                i, *SpawnPos.ToString(), AgentId);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("NLTTrainingManager: Failed to spawn actor %d"), i);
        }
    }
}

void ANLTTrainingManager::OnEpisodeComplete()
{
    UE_LOG(LogTemp, Log, TEXT("NLTTrainingManager: Episode complete"));
}

void ANLTTrainingManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Tick cognitive decay
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

    // Run inference
    if (bRunInference && Policy)
    {
        RunInference();
    }

    // Throttle training
    TrainingTimer += DeltaTime;
    if (bRunTraining && TrainingTimer >= 1.0f)
    {
        TrainingTimer = 0.0f;
        RunTrainingStep();
    }
}

void ANLTTrainingManager::RunInference()
{
    if (Policy)
    {
        Policy->RunInference(1.0f);
    }
}

void ANLTTrainingManager::RunTrainingStep()
{
    if (!Trainer) return;

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

    Trainer->RunTraining(TrainingSettings, GameSettings, true, true);
}

void ANLTTrainingManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UWorld* World = GetWorld();
    if (World)
    {
        UNLTGovernanceSubsystem* Governance = UNLTGovernanceSubsystem::Get(World);
        if (Governance)
        {
            Governance->ShutdownAgent(TEXT("ActorA"));
            Governance->ShutdownAgent(TEXT("ActorB"));
        }
    }

    Super::EndPlay(EndPlayReason);
}
