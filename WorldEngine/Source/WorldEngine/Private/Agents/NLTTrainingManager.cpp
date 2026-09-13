// NLTTrainingManager.cpp — Single shared policy/critic/trainer, single actor
#include "Agents/NLTTrainingManager.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/AvatarAIController.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "Agents/NLTLLMBridge.h"
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
    bUseLLMControl = true;
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

    if (bUseLLMControl)
    {
        // LLM-driven mode: no PPO training, no LearningAgents interactor.
        // The avatar's AIController uses the UNLTLLMBridge to get movement
        // commands from Ollama via async HTTP.
        UE_LOG(LogTemp, Log, TEXT("NLTTrainingManager: LLM control mode active (endpoint: %s, model: %s)"),
            *LLMEndpoint, *LLMModel);

        AgentManager = NewObject<ULearningAgentsManager>(this);
        AgentManager->SetMaxAgentNum(1);
        AgentManager->RegisterComponent();

        SpawnSingleActor();
        return;
    }

    EpisodeManager = NewObject<UNLTEpisodeManager>(this);
    EpisodeManager->RegisterComponent();
    EpisodeManager->MaxEpisodeSteps = MaxEpisodeSteps;
    // Removed StepInterval = TickInterval to avoid desync with AgentManager iterations
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

    // If LLM control is enabled, skip PPO training entirely.
    // The AvatarAIController's Tick will request movement commands from the
    // LLM via the REST API bridge (UNLTLLMBridge).
    if (bUseLLMControl)
    {
        // Ensure LLM control is active on the avatar's controller
        const TArray<int32>& AllAgentIds = AgentManager ? AgentManager->GetAllAgentIds() : TArray<int32>();
        for (int32 AgentId : AllAgentIds)
        {
            UObject* Agent = AgentManager->GetAgent(AgentId);
            AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
            if (Avatar)
            {
                AAvatarAIController* AIController = Cast<AAvatarAIController>(Avatar->GetController());
                if (AIController && !AIController->IsLLMControlActive())
                {
                    AIController->SetLLMControlActive(true);

                    // Configure the LLM bridge endpoint/model
                    if (AIController->LLMBridge)
                    {
                        AIController->LLMBridge->EndpointURL = LLMEndpoint;
                        AIController->LLMBridge->ModelName = LLMModel;
                    }

                    UE_LOG(LogTemp, Log, TEXT("NLTTrainingManager: LLM control activated for avatar"));
                }
            }
        }
        return; // Skip PPO training/inference entirely
    }

    // After the first training iteration, the Python subprocess exits.
    // Calling Trainer->RunTraining() again would try to send the initial
    // policy back to the dead process, causing "Unexpected communication received".
    // Instead, switch to pure inference mode: call Policy->RunInference() each tick.
    if (bRunTraining && Trainer && !bTrainingCompleted)
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

        Trainer->RunTraining(TrainingSettings, GameSettings, false, true);
        bTrainingCompleted = true;
    }

    // After training is done (or if we're only doing inference),
    // run the policy directly to generate actions every tick.
    if (Policy && bRunInference)
    {
        Policy->RunInference(0.0f);
    }
}

void ANLTTrainingManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}
