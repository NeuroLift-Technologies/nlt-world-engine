// NLTTrainingManager.h — Extended for dual-model, dual-actor RL training
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LearningAgentsManager.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsCritic.h"
#include "LearningAgentsPPOTrainer.h"
#include "LearningAgentsTrainingEnvironment.h"
#include "NLTAvatarInteractor.h"
#include "NLTAideInteractor.h"
#include "NLTTrainingEnvironment.h"
#include "NLTEpisodeManager.h"
#include "NLTTrainingManager.generated.h"

USTRUCT()
struct FNLTAgentModelGroup
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, Category = "NLT|ModelGroup")
    int32 GroupId = 0;

    UPROPERTY(VisibleAnywhere, Category = "NLT|ModelGroup")
    FName GroupName;

    UPROPERTY(VisibleAnywhere, Category = "NLT|ModelGroup")
    UNLTAvatarInteractor* Interactor = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "NLT|ModelGroup")
    ULearningAgentsPolicy* Policy = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "NLT|ModelGroup")
    ULearningAgentsCritic* Critic = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "NLT|ModelGroup")
    ULearningAgentsPPOTrainer* Trainer = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "NLT|ModelGroup")
    FVector SpawnLocation = FVector::ZeroVector;

    UPROPERTY(VisibleAnywhere, Category = "NLT|ModelGroup")
    int32 AgentId = INDEX_NONE;

    UPROPERTY(VisibleAnywhere, Category = "NLT|ModelGroup")
    FName GovernanceAgentId;
};

/**
 * Dual-Model Dual-Actor Training Manager.
 * 
 * Spawns two physically separate actors (Actor A, Actor B), each controlled
 * by its own RL policy/model, each with its own ASFDK-C++ governance context.
 * 
 * Architecture:
 *   Model A (Policy A) -> Interactor A -> Actor A (governance context A)
 *   Model B (Policy B) -> Interactor B -> Actor B (governance context B)
 */
UCLASS()
class WORLDENGINE_API ANLTTrainingManager : public AActor
{
    GENERATED_BODY()

public:
    ANLTTrainingManager();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "NLT|DualModel")
    FVector ActorAStartLocation = FVector(-500.0f, 0.0f, 100.0f);

    UPROPERTY(EditAnywhere, Category = "NLT|DualModel")
    FVector ActorBStartLocation = FVector(500.0f, 0.0f, 100.0f);

    UPROPERTY(EditAnywhere, Category = "NLT|DualModel")
    float TickInterval = 0.1f;

    UPROPERTY(EditAnywhere, Category = "NLT|DualModel")
    bool bRunInference = true;

    UPROPERTY(EditAnywhere, Category = "NLT|DualModel")
    bool bRunTraining = true;

    UPROPERTY(EditAnywhere, Category = "NLT|DualModel")
    int32 MaxEpisodeSteps = 512;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|DualModel")
    ULearningAgentsManager* AgentManager = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|DualModel")
    UNLTEpisodeManager* EpisodeManager = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|DualModel")
    ULearningAgentsTrainingEnvironment* TrainingEnvironment = nullptr;

    // Internal model groups (not exposed to Blueprints — TArray<USTRUCT> is not blueprint-supported)
    TArray<FNLTAgentModelGroup> ModelGroups;

    UFUNCTION(BlueprintCallable, Category = "NLT|DualModel")
    int32 GetModelGroupCount() const { return ModelGroups.Num(); }

    UFUNCTION(BlueprintPure, Category = "NLT|DualModel")
    int32 GetActorAgentId(int32 GroupIndex) const;

protected:
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    void InitializeModelGroups();
    void SpawnDualActors();
    void InitializeGovernanceForGroup(int32 GroupIndex, class AAvatarCharacter* Actor);
    void RunDualInference();
    void RunDualTraining();

    float TrainingTimer = 0.0f;
    bool bGovernanceInitialized = false;
};
