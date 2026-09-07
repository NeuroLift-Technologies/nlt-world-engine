#include "NLTGovernanceSubsystem.h"
#include "AgentGovernanceState.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTGovernance);

void FNLTGovernanceSubsystemModule::StartupModule()
{
    UE_LOG(LogNLTGovernance, Log, TEXT("NLTGovernanceSubsystem module started"));
}

void FNLTGovernanceSubsystemModule::ShutdownModule()
{
    UE_LOG(LogNLTGovernance, Log, TEXT("NLTGovernanceSubsystem module shutdown"));
}

IMPLEMENT_GAME_MODULE(FNLTGovernanceSubsystemModule, NLTGovernanceSubsystem)
