#include "WorldEngine.h"
#include "Core/NLTFusionCore.h"

DEFINE_LOG_CATEGORY(LogWorldEngine);

void FWorldEngineModule::StartupModule()
{
    UE_LOG(LogWorldEngine, Log, TEXT("WorldEngine module started"));
}

void FWorldEngineModule::ShutdownModule()
{
    UE_LOG(LogWorldEngine, Log, TEXT("WorldEngine module shutdown"));
}

IMPLEMENT_GAME_MODULE(FWorldEngineModule, WorldEngine)
