// NLTTrainingManager.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LearningAgentsManager.h"
#include "LearningAgentsInteractor.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsCritic.h"
#include "LearningAgentsPPOTrainer.h"
#include "LearningAgentsTrainingEnvironment.h"
#include "NLTAvatarInteractor.h"
#include "NLTTrainingEnvironment.h"
#include "NLTLLMBridge.h"
#include "NLTEpisodeManager.h"
#include "NLTTrainingManager.generated.h"

UCLASS()
class WORLDENGINE_API ANLTTrainingManager : public AActor
{
    GENERATED_BODY()

public:
    ANLTTrainingManager();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "NLT|Training")
    FVector ActorAStartLocation = FVector(-500.0f, 0.0f, 100.0f);

    UPROPERTY(EditAnywhere, Category = "NLT|Training")
    FVector ActorBStartLocation = FVector(500.0f, 0.0f, 100.0f);

    UPROPERTY(EditAnywhere, Category = "NLT|Training")
    float TickInterval = 0.1f;

    UPROPERTY(EditAnywhere, Category = "NLT|Training")
    bool bRunInference = true;

    UPROPERTY(EditAnywhere, Category = "NLT|Training")
    bool bRunTraining = true;

    /** If true, LLM control via REST API bridge is enabled. When enabled,
     *  after the first training iteration (or immediately in inference-only
     *  mode), the avatar's AIController will request movement commands from
     *  the LLM instead of using the LearningAgents policy. */
    UPROPERTY(EditAnywhere, Category = "NLT|LLM")
    bool bUseLLMControl = true;

    /** LLM endpoint URL the bridge will call (e.g. http://localhost:11434/api/generate). */
    UPROPERTY(EditAnywhere, Category = "NLT|LLM")
    FString LLMEndpoint = TEXT("http://localhost:11434/api/generate");

    /** LLM model name to send in the API request. */
    UPROPERTY(EditAnywhere, Category = "NLT|LLM")
    FString LLMModel = TEXT("qwen3:0.6b");

    UPROPERTY(EditAnywhere, Category = "NLT|Training")
    int32 MaxEpisodeSteps = 512;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Training")
    ULearningAgentsManager* AgentManager = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Training")
    UNLTEpisodeManager* EpisodeManager = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Training")
    ULearningAgentsTrainingEnvironment* TrainingEnvironment = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Training")
    ULearningAgentsPolicy* Policy = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Training")
    ULearningAgentsCritic* Critic = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Training")
    ULearningAgentsPPOTrainer* Trainer = nullptr;

protected:
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    void SpawnSingleActor();
    void InitializeTraining();
    void RunTrainingStep();

    UFUNCTION()
    void OnEpisodeComplete();

    float TrainingTimer = 0.0f;

    /** Tracks whether the first training iteration has completed.
     *  After the first RunTraining call with bTrain=true, the Python subprocess
     *  exits. Subsequent Ticks should only run inference (bTrain=false) to
     *  avoid "Unexpected communication received" / "Training has failed". */
    bool bTrainingCompleted = false;
};
