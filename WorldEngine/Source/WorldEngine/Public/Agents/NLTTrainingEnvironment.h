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

    // Begin ULearningAgentsTrainingEnvironment Interface
    virtual void GatherAgentReward_Implementation(float& OutReward, const int32 AgentId) override;
    virtual void GatherAgentCompletion_Implementation(ELearningAgentsCompletion& OutCompletion, const int32 AgentId) override;
    // End ULearningAgentsTrainingEnvironment Interface
};
