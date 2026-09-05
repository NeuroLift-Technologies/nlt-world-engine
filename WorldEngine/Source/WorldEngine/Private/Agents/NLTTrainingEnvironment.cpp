// NLTTrainingEnvironment.cpp
#include "Agents/NLTTrainingEnvironment.h"
#include "LearningAgentsManager.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/LTCognitiveStateComponent.h"

UNLTTrainingEnvironment::UNLTTrainingEnvironment()
{
}

void UNLTTrainingEnvironment::GatherAgentReward(float& OutReward, const int32 AgentId)
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

    // Reward: encourage independence, penalize burnout and high stress
    OutReward = 0.0f;
    OutReward += Cognitive->Independence * 1.0f;
    OutReward -= Cognitive->Burnout * 1.0f;
    OutReward -= Cognitive->Stress * 0.5f;
    OutReward += Cognitive->Focus * 0.3f;
    OutReward += Cognitive->SuccessRate * 0.5f;
}

void UNLTTrainingEnvironment::GatherAgentCompletion(ELearningAgentsCompletion& OutCompletion, const int32 AgentId)
{
    // Return Running during active episodes, Termination only when episode actually ends
    // LA's trainer uses MaxEpisodeStepNum for truncation
    OutCompletion = ELearningAgentsCompletion::Running;
}
