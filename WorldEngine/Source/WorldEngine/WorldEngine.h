#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Core/NLTFusionCore.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWorldEngine, Log, All);

class FWorldEngineModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
