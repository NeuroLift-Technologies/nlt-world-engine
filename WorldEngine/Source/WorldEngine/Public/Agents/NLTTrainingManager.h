// NLTTrainingManager.h
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

UCLASS()
class WORLDENGINE_API ANLTTrainingManager : public AActor
{
    GENERATED_BODY()

public:
    ANLTTrainingManager();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
    ULearningAgentsManager* AgentManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
    UNLTAvatarInteractor* AvatarInteractor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
    UNLTAideInteractor* AideInteractor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
    ULearningAgentsPolicy* Policy;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
    ULearningAgentsCritic* Critic;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
    ULearningAgentsTrainingEnvironment* TrainingEnvironment;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
    ULearningAgentsPPOTrainer* Trainer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
    UNLTEpisodeManager* EpisodeManager;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")
    int32 MaxAgentNum = 40;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")
    float TickInterval = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")
    bool bRunInference = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")
    bool bRunTraining = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")
    int32 MaxEpisodeSteps = 512;

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Pair mapping: Aide AgentId -> Avatar AgentId
    UFUNCTION(BlueprintCallable, Category = "LearningAgents")
    void SetPairMapping(int32 AideAgentId, int32 AvatarAgentId);

    UFUNCTION(BlueprintPure, Category = "LearningAgents")
    int32 GetPairedAvatarId(int32 AideAgentId) const;

private:
    void SpawnAndRegisterPairs();
    void OnEpisodeComplete();
    TMap<int32, int32> PairMap; // AideId -> AvatarId
};
