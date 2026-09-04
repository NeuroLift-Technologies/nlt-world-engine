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
}

void ANLTTrainingManager::BeginPlay()
{
    Super::BeginPlay();

    // 1. Create Episode Manager
    EpisodeManager = NewObject<UNLTEpisodeManager>(this);
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

    // 4. Setup Policy
    Policy = NewObject<ULearningAgentsPolicy>(this);
    FLearningAgentsPolicySettings PolicySettings;
    PolicySettings.HiddenLayerNum = 1;
    PolicySettings.HiddenLayerSize = 128;
    PolicySettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    Policy->SetupPolicy(ManagerPtr, AvatarInteractorPtr, nullptr, nullptr, nullptr, true, true, true, PolicySettings, 1234);

    // 5. Setup Critic
    Critic = NewObject<ULearningAgentsCritic>(this);
    FLearningAgentsCriticSettings CriticSettings;
    CriticSettings.HiddenLayerNum = 1;
    CriticSettings.HiddenLayerSize = 128;
    CriticSettings.ActivationFunction = ELearningAgentsActivationFunction::ELU;
    Critic->SetupCritic(ManagerPtr, AvatarInteractorPtr, Policy, nullptr, true, CriticSettings, 1234);

    // 6. Setup Training Environment
    TrainingEnvironment = NewObject<UNLTTrainingEnvironment>(this);
    TrainingEnvironment->SetupTrainingEnvironment(ManagerPtr);

    // 7. Create shared memory communicator for Python training process
    FLearningAgentsCommunicator Communicator = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryTrainingProcess();

    // 8. Setup PPO Trainer
    Trainer = NewObject<ULearningAgentsPPOTrainer>(this);
    FLearningAgentsPPOTrainerSettings TrainerSettings;
    TrainerSettings.MaxEpisodeStepNum = MaxEpisodeSteps;
    TrainerSettings.MaximumRecordedEpisodesPerIteration = 1000;
    TrainerSettings.MaximumRecordedStepsPerIteration = 10000;
    Trainer->SetupPPOTrainer(ManagerPtr, AvatarInteractorPtr, TrainingEnvironment, Policy, Critic, Communicator, TrainerSettings);

    // 9. Spawn agent pairs
    SpawnAndRegisterPairs();

    // 10. Start training automatically
    bRunTraining = true;
    if (EpisodeManager)
    {
        EpisodeManager->StartEpisode();
    }

    UE_LOG(LogNLTFusion, Log, TEXT("NLTTrainingManager: LA components initialized, training started"));
}

void ANLTTrainingManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Check cognitive-based episode completion
    if (EpisodeManager && EpisodeManager->bEpisodeActive)
    {
        for (const auto& Pair : PairMap)
        {
            int32 AvatarId = Pair.Value;
            UObject* Agent = AgentManager->GetAgent(AvatarId);
            AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
            if (Avatar)
            {
                ULTCognitiveStateComponent* Cognitive = Avatar->FindComponentByClass<ULTCognitiveStateComponent>();
                if (Cognitive)
                {
                    EpisodeManager->CheckCognitiveCompletion(Cognitive->Independence, Cognitive->Burnout);
                }
            }
        }
    }

    if (bRunInference)
    {
        Policy->RunInference(1.0f);
    }

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
