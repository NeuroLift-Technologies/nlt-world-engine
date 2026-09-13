#include "AgentGovernanceState.h"

FAgentGovernanceState::FAgentGovernanceState(const FName& InAgentId, const FString& InAgentName)
    : AgentId(InAgentId)
    , AgentName(InAgentName)
{}

FAgentGovernanceState::~FAgentGovernanceState() = default;

FString FAgentGovernanceState::ProcessInteraction(const FString& Input, const FString& Channel)
{
    std::string InputStr = std::string(TCHAR_TO_UTF8(*Input));
    std::string ChannelStr = std::string(TCHAR_TO_UTF8(*Channel));

    asfdk::Envelope Envelope = Asfdk.process(InputStr, ChannelStr);

    nlohmann::json Result;
    Result["trusted"] = Envelope.trusted;
    Result["channel"] = Envelope.channel;
    Result["consentLevel"] = Envelope.consentLevel;
    Result["flagged"] = Envelope.flagged;
    Result["flagReason"] = Envelope.flagReason;
    Result["payload"] = Envelope.payload;

    return FString(Result.dump().c_str());
}

FString FAgentGovernanceState::Assess(const FString& Input)
{
    std::string InputStr = std::string(TCHAR_TO_UTF8(*Input));

    asfdk::AssessmentResult Result = Asfdk.assess(InputStr);

    nlohmann::json Json;
    Json["requiresRrtaHandoff"] = Result.requiresRrtaHandoff;

    if (Result.crisis.has_value())
    {
        nlohmann::json CrisisJson;
        CrisisJson["crisisLevel"] = static_cast<int>(Result.crisis->crisisLevel);
        CrisisJson["confidenceScore"] = Result.crisis->confidenceScore;
        Json["crisis"] = CrisisJson;
    }

    nlohmann::json EmoJson;
    EmoJson["stateType"] = static_cast<int>(Result.emotionalState.stateType);
    EmoJson["protective"] = Result.emotionalState.protective;
    EmoJson["requiresCheckIn"] = Result.emotionalState.requiresCheckIn;
    EmoJson["confidence"] = Result.emotionalState.confidence;
    Json["emotionalState"] = EmoJson;

    return FString(Json.dump().c_str());
}

FString FAgentGovernanceState::GetStatusJson()
{
    asfdk::FoundationStatus Status = Asfdk.getStatus();

    nlohmann::json Json;
    Json["toiActive"] = Status.toi_active;
    Json["otoiActive"] = Status.otoi_active;
    Json["otoiMode"] = Status.otoi_mode;
    Json["rrtActive"] = Status.rrt_active;
    Json["swpActive"] = Status.swp_active;
    Json["overall"] = Status.overall;

    return FString(Json.dump().c_str());
}
