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
};
