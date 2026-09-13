// NLTTrainingEnvironment.h
#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsTrainingEnvironment.h"
#include "NLTTrainingEnvironment.generated.h"

UCLASS()
class WORLDENGINE_API UNLTTrainingEnvironment : public ULearningAgentsTrainingEnvironment
{
    GENERATED_BODY()

public:
    UNLTTrainingEnvironment();

    // Begin ULearningAgentsManagerListener Interface
    virtual void OnAgentsAdded_Implementation(const TArray<int32>& AgentIds) override;
    // End ULearningAgentsManagerListener Interface

    // Begin ULearningAgentsTrainingEnvironment Interface
    virtual void ResetAgentEpisode_Implementation(const int32 AgentId) override;
    virtual void GatherAgentReward_Implementation(float& OutReward, const int32 AgentId) override;
    virtual void GatherAgentCompletion_Implementation(ELearningAgentsCompletion& OutCompletion, const int32 AgentId) override;
    // End ULearningAgentsTrainingEnvironment Interface

private:
    /** Initial transforms captured when agents are added, used to restore the
     *  complete episode state (position, velocity, movement request) on reset. */
    UPROPERTY()
    TMap<int32, FTransform> InitialAgentTransforms;
};
