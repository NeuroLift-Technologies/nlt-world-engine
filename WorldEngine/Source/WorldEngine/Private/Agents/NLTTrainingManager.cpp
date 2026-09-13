// NLTTrainingManager.cpp — Single shared policy/critic/trainer, single actor
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

void ANLTTrainingManager::SpawnSingleActor()
{
    UWorld* World = GetWorld();
    if (!World) return;

    AAvatarCharacter* Actor = World->SpawnActor<AAvatarCharacter>(
        AAvatarCharacter::StaticClass(),
        ActorAStartLocation,
        FRotator::ZeroRotator
    );
    
    if (Actor)
    {
        int32 AgentId = AgentManager->AddAgent(Actor);
        if (AgentId == INDEX_NONE)
        {
            UE_LOG(LogTemp, Error, TEXT("NLTTrainingManager: Failed to register actor"));
            Actor->Destroy();
            return;
        }

        UE_LOG(LogTemp, Log, TEXT("NLTTrainingManager: Spawned actor at (%s), AgentId=%d"),
            *ActorAStartLocation.ToString(), AgentId);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("NLTTrainingManager: Failed to spawn actor"));
    }
}

void ANLTTrainingManager::BeginPlay()
{
    Super::BeginPlay();

    EpisodeManager = NewObject<UNLTEpisodeManager>(this);
    EpisodeManager->RegisterComponent();
    EpisodeManager->MaxEpisodeSteps = MaxEpisodeSteps;
    EpisodeManager->StepInterval = TickInterval;
    EpisodeManager->OnEpisodeComplete.AddDynamic(this, &ANLTTrainingManager::OnEpisodeComplete);

    AgentManager = NewObject<ULearningAgentsManager>(this);
    AgentManager->SetMaxAgentNum(1);
    AgentManager->RegisterComponent();

    TrainingEnvironment = NewObject<UNLTTrainingEnvironment>(this);
    TrainingEnvironment->SetupTrainingEnvironment(AgentManager);

    InitializeTraining();
    SpawnSingleActor();

    if (EpisodeManager)
    {
        EpisodeManager->StartEpisode();
    }

    UE_LOG(LogTemp, Log, TEXT("NLTTrainingManager: Training initialized"));
}

void ANLTTrainingManager::InitializeTraining()
{
    UNLTAvatarInteractor* AvatInteractor = NewObject<UNLTAvatarInteractor>(this);
    ULearningAgentsInteractor* LearningInteractor = AvatInteractor;
    AvatInteractor->SetupInteractor(AgentManager);

    Policy = NewObject<ULearningAgentsPolicy>(this);
    FLearningAgentsPolicySettings PolicySettings;
    PolicySettings.HiddenLayerNum = 2;
    PolicySettings.HiddenLayerSize = 128;
    PolicySettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    Policy->SetupPolicy(AgentManager, LearningInteractor, nullptr, nullptr, nullptr, true, true, true, PolicySettings, 1234);

    Critic = NewObject<ULearningAgentsCritic>(this);
    FLearningAgentsCriticSettings CriticSettings;
    CriticSettings.HiddenLayerNum = 2;
    CriticSettings.HiddenLayerSize = 128;
    CriticSettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    Critic->SetupCritic(AgentManager, LearningInteractor, Policy, nullptr, true, CriticSettings, 1234);

    Trainer = NewObject<ULearningAgentsPPOTrainer>(this);
    FLearningAgentsTrainerProcessSettings TPS;
    TPS.TaskName = TEXT("NLTTraining");
    TPS.TrainerFileName = TEXT("train_ppo");
    FLearningAgentsCommunicator Communicator = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryTrainingProcess(TPS);
    FLearningAgentsPPOTrainerSettings TrainerSettings;
    TrainerSettings.MaxEpisodeStepNum = MaxEpisodeSteps;
    TrainerSettings.MaximumRecordedEpisodesPerIteration = 1000;
    TrainerSettings.MaximumRecordedStepsPerIteration = 10000;
    Trainer->SetupPPOTrainer(AgentManager, LearningInteractor, TrainingEnvironment, Policy, Critic, Communicator, TrainerSettings);
}

void ANLTTrainingManager::OnEpisodeComplete()
{
    UE_LOG(LogTemp, Log, TEXT("NLTTrainingManager: Episode complete"));
}

void ANLTTrainingManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

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

    // Run inference at every step
    if (bRunInference && Policy)
    {
        Policy->RunInference(1.0f);
    }

    // Run training at every step (must match inference frequency for experience recording)
    if (bRunTraining && Trainer)
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

        Trainer->RunTraining(TrainingSettings, GameSettings, true, true);
    }
}

void ANLTTrainingManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}
