// NLTTrainingEnvironment.cpp
#include "Agents/NLTTrainingEnvironment.h"
#include "LearningAgentsManager.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/LTCognitiveStateComponent.h"

UNLTTrainingEnvironment::UNLTTrainingEnvironment()
{
}

void UNLTTrainingEnvironment::ResetAgentEpisode_Implementation(const int32 AgentId)
{
    UObject* Agent = GetAgent(AgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (Avatar && Avatar->CognitiveState)
    {
        Avatar->CognitiveState->ResetCognitiveState();
    }
}

void UNLTTrainingEnvironment::GatherAgentReward_Implementation(float& OutReward, const int32 AgentId)
{
    UObject* Agent = GetAgent(AgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (!Avatar)
    {
        OutReward = 0.0f;
        return;
    }

    ULTCognitiveStateComponent* Cognitive = Avatar->FindComponentByClass<ULTCognitiveStateComponent>();
    if (!Cognitive)
    {
        OutReward = 0.0f;
        return;
    }

    OutReward = 0.0f;
    OutReward += Cognitive->Independence * 1.0f;
    OutReward -= Cognitive->Burnout * 1.0f;
    OutReward -= Cognitive->Stress * 0.5f;
    OutReward += Cognitive->Focus * 0.3f;
    OutReward += Cognitive->SuccessRate * 0.5f;
}

void UNLTTrainingEnvironment::GatherAgentCompletion_Implementation(ELearningAgentsCompletion& OutCompletion, const int32 AgentId)
{
    OutCompletion = ELearningAgentsCompletion::Running;
}
