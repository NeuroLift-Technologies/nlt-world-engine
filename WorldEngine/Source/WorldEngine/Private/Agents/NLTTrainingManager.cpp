// NLTTrainingManager.cpp
#include "Agents/NLTTrainingManager.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/AvatarAIController.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "LearningAgentsManager.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsCritic.h"
#include "LearningAgentsPPOTrainer.h"
#include "LearningAgentsCommunicator.h"
#include "Core/NLTFusionCore.h"

ANLTTrainingManager::ANLTTrainingManager()
{
    PrimaryActorTick.bCanEverTick = true;
    MaxAgentNum = 40;
    TickInterval = 0.1f;
    bRunInference = false;
    bRunTraining = false;
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

    // 2. Create Manager
    AgentManager = NewObject<ULearningAgentsManager>(this);
    AgentManager->SetMaxAgentNum(MaxAgentNum);

    // 3. Setup Interactors
    AvatarInteractor = NewObject<UNLTAvatarInteractor>(this);
    AideInteractor = NewObject<UNLTAideInteractor>(this);

    ULearningAgentsManager* ManagerPtr = AgentManager;
    ULearningAgentsInteractor* AvatarInteractorPtr = AvatarInteractor;
    ULearningAgentsInteractor* AideInteractorPtr = AideInteractor;
    AvatarInteractor->SetupInteractor(ManagerPtr);
    AideInteractor->SetupInteractor(ManagerPtr);

    // 4. Setup Avatar Policy/Critic
    AvatarPolicy = NewObject<ULearningAgentsPolicy>(this);
    FLearningAgentsPolicySettings AvatarPolicySettings;
    AvatarPolicySettings.HiddenLayerNum = 1;
    AvatarPolicySettings.HiddenLayerSize = 128;
    AvatarPolicySettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    AvatarPolicy->SetupPolicy(ManagerPtr, AvatarInteractorPtr, nullptr, nullptr, nullptr, true, true, true, AvatarPolicySettings, 1234);

    AvatarCritic = NewObject<ULearningAgentsCritic>(this);
    FLearningAgentsCriticSettings AvatarCriticSettings;
    AvatarCriticSettings.HiddenLayerNum = 1;
    AvatarCriticSettings.HiddenLayerSize = 128;
    AvatarCriticSettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    AvatarCritic->SetupCritic(ManagerPtr, AvatarInteractorPtr, AvatarPolicy, nullptr, true, AvatarCriticSettings, 1234);

    // 5. Setup Aide Policy/Critic
    AidePolicy = NewObject<ULearningAgentsPolicy>(this);
    FLearningAgentsPolicySettings AidePolicySettings;
    AidePolicySettings.HiddenLayerNum = 1;
    AidePolicySettings.HiddenLayerSize = 128;
    AidePolicySettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    AidePolicy->SetupPolicy(ManagerPtr, AideInteractorPtr, nullptr, nullptr, nullptr, true, true, true, AidePolicySettings, 5678);

    AideCritic = NewObject<ULearningAgentsCritic>(this);
    FLearningAgentsCriticSettings AideCriticSettings;
    AideCriticSettings.HiddenLayerNum = 1;
    AideCriticSettings.HiddenLayerSize = 128;
    AideCriticSettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    AideCritic->SetupCritic(ManagerPtr, AideInteractorPtr, AidePolicy, nullptr, true, AideCriticSettings, 5678);

    // 6. Setup Training Environment
    TrainingEnvironment = NewObject<UNLTTrainingEnvironment>(this);
    TrainingEnvironment->SetupTrainingEnvironment(ManagerPtr);

    // 7. Create shared memory communicators for Python training processes
    FLearningAgentsCommunicator AvatarCommunicator = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryTrainingProcess();
    FLearningAgentsCommunicator AideCommunicator = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryTrainingProcess();

    // 8. Setup Avatar PPO Trainer
    AvatarTrainer = NewObject<ULearningAgentsPPOTrainer>(this);
    FLearningAgentsPPOTrainerSettings TrainerSettings;
    TrainerSettings.MaxEpisodeStepNum = MaxEpisodeSteps;
    TrainerSettings.MaximumRecordedEpisodesPerIteration = 1000;
    TrainerSettings.MaximumRecordedStepsPerIteration = 10000;
    AvatarTrainer->SetupPPOTrainer(ManagerPtr, AvatarInteractorPtr, TrainingEnvironment, AvatarPolicy, AvatarCritic, AvatarCommunicator, TrainerSettings);

    // 9. Setup Aide PPO Trainer
    AideTrainer = NewObject<ULearningAgentsPPOTrainer>(this);
    AideTrainer->SetupPPOTrainer(ManagerPtr, AideInteractorPtr, TrainingEnvironment, AidePolicy, AideCritic, AideCommunicator, TrainerSettings);

    // 10. Spawn agent pairs
    SpawnAndRegisterPairs();

    // 11. Start training automatically
    bRunTraining = true;
    bRunInference = true;
    if (EpisodeManager)
    {
        EpisodeManager->StartEpisode();
    }

    UE_LOG(LogNLTFusion, Log, TEXT("NLTTrainingManager: LA components initialized with Avatar+Aide dual-policy training"));
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

    // Run inference every tick
    if (bRunInference)
    {
        AvatarPolicy->RunInference(1.0f);
        AidePolicy->RunInference(1.0f);
    }

    // Throttle training to episode completion or timer
    TrainingTimer += DeltaTime;
    if (bRunTraining && TrainingTimer >= 1.0f)
    {
        TrainingTimer = 0.0f;
        
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

        AvatarTrainer->RunTraining(TrainingSettings, GameSettings, true, true);
        AideTrainer->RunTraining(TrainingSettings, GameSettings, true, true);
    }

    // Check cognitive-based episode completion
    if (EpisodeManager && EpisodeManager->bEpisodeActive)
    {
        for (const auto& Pair : PairMap)
        {
            int32 AvatarId = Pair.Value;
            UObject* Agent = AgentManager->GetAgent(AvatarId);
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

void ANLTTrainingManager::SetPairMapping(int32 AideAgentId, int32 AvatarAgentId)
{
    PairMap.Add(AideAgentId, AvatarAgentId);
    if (AideInteractor)
    {
        AideInteractor->SetPairMapping(PairMap);
    }
}

int32 ANLTTrainingManager::GetPairedAvatarId(int32 AideAgentId) const
{
    const int32* Found = PairMap.Find(AideAgentId);
    return Found ? *Found : INDEX_NONE;
}

void ANLTTrainingManager::SpawnAndRegisterPairs()
{
    UWorld* World = GetWorld();
    if (!World) return;

    for (int32 i = 0; i < 20; i++)
    {
        FVector AvatarPos(i * 200.0f, 0.0f, 0.0f);
        AAvatarCharacter* Avatar = World->SpawnActor<AAvatarCharacter>(AAvatarCharacter::StaticClass(), AvatarPos, FRotator::ZeroRotator);
        
        if (Avatar)
        {
            int32 AvatarId = AgentManager->AddAgent(Avatar);

            FVector AidePos = AvatarPos + FVector(100.0f, 0.0f, 0.0f);
            AAvatarCharacter* Aide = World->SpawnActor<AAvatarCharacter>(AAvatarCharacter::StaticClass(), AidePos, FRotator::ZeroRotator);
            
            if (Aide)
            {
                int32 AideId = AgentManager->AddAgent(Aide);
                PairMap.Add(AideId, AvatarId);
            }
        }
    }

    if (AideInteractor)
    {
        AideInteractor->SetPairMapping(PairMap);
    }

    UE_LOG(LogNLTFusion, Log, TEXT("NLTTrainingManager: Spawned %d agent pairs"), PairMap.Num());
}

void ANLTTrainingManager::OnEpisodeComplete()
{
    UE_LOG(LogNLTFusion, Log, TEXT("NLTTrainingManager: Episode complete after %d steps"), 
        EpisodeManager ? EpisodeManager->CurrentStep : 0);
    
    // Reset all agents for next episode
    if (AgentManager)
    {
        const TArray<int32>& AllAgentIds = AgentManager->GetAllAgentIds();
        AgentManager->ResetAgents(AllAgentIds);
    }

    // Restart episode
    if (EpisodeManager)
    {
        EpisodeManager->StartEpisode();
    }
}
