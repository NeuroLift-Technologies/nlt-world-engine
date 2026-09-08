#include "NLTGovernanceSubsystem.h"
#include "AgentGovernanceState.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTGovernance);

void FNLTGovernanceSubsystemModule::StartupModule()
{
    UE_LOG(LogNLTGovernance, Log, TEXT("NLTGovernanceSubsystem: ASFDK governance initialized"));
}

void FNLTGovernanceSubsystemModule::ShutdownModule()
{
    UE_LOG(LogNLTGovernance, Log, TEXT("NLTGovernanceSubsystem: ASFDK governance shutdown"));
}

IMPLEMENT_MODULE(FNLTGovernanceSubsystemModule, NLTGovernanceSubsystem)
