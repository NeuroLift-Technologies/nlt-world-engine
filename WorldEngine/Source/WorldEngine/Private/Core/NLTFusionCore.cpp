// NLTFusion module implementation
// This module is part of WorldEngine — no separate IMPLEMENT_MODULE needed.

#include "Core/NLTFusionCore.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTFusion);

void FNLTFusionModule::StartupModule()
{
	UE_LOG(LogNLTFusion, Log, TEXT("NLTFusion module started"));
}

void FNLTFusionModule::ShutdownModule()
{
	UE_LOG(LogNLTFusion, Log, TEXT("NLTFusion module shutdown"));
}
