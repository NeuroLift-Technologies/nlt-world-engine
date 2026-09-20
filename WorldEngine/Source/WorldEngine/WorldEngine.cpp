#include "WorldEngine.h"
#include "Core/NLTFusionCore.h"

DEFINE_LOG_CATEGORY(LogWorldEngine);

void FWorldEngineModule::StartupModule()
{
    UE_LOG(LogWorldEngine, Log, TEXT("WorldEngine module started"));
    UE_LOG(LogNLTFusion, Log, TEXT("NLTFusion core started"));
}

void FWorldEngineModule::ShutdownModule()
{
    UE_LOG(LogNLTFusion, Log, TEXT("NLTFusion core shutdown"));
    UE_LOG(LogWorldEngine, Log, TEXT("WorldEngine module shutdown"));
}

// Single module entry point for the "WorldEngine" module declared in WorldEngine.uproject.
// Keep exactly one IMPLEMENT_MODULE / IMPLEMENT_GAME_MODULE for this module name in the whole
// module (unity builds merge the module's .cpp files into one translation unit, so a second
// implementation causes C2084/C2086/C2374 "already has a body" / "redefinition" errors).
IMPLEMENT_GAME_MODULE(FWorldEngineModule, WorldEngine)
