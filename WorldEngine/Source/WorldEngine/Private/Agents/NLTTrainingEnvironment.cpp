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
    OutReward += Cognitive->Independence * 1.0f;      // Encourage independence
    OutReward -= Cognitive->Burnout * 1.0f;            // Penalize burnout
    OutReward -= Cognitive->Stress * 0.5f;             // Penalize stress
    OutReward += Cognitive->Focus * 0.3f;              // Encourage focus
    OutReward += Cognitive->SuccessRate * 0.5f;        // Encourage success
}

void UNLTTrainingEnvironment::GatherAgentCompletion(ELearningAgentsCompletion& OutCompletion, const int32 AgentId)
{
    // Episode completes after a fixed number of steps (handled by MaxEpisodeStepNum in TrainerSettings)
    OutCompletion = ELearningAgentsCompletion::Termination;
}
