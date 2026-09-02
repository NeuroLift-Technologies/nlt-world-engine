#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTFusion, Log, All);

class FNLTFusionModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

UENUM(BlueprintType)
enum class ENLTAgentRole : uint8
{
    None        UMETA(DisplayName = "None"),
    Avatar      UMETA(DisplayName = "Avatar"),
    Aide        UMETA(DisplayName = "Aide"),
    Advocate    UMETA(DisplayName = "Advocate")
};

UENUM(BlueprintType)
enum class ESimulationMode : uint8
{
    Realtime           UMETA(DisplayName = "Realtime"),
    Paused             UMETA(DisplayName = "Paused"),
    FastForward        UMETA(DisplayName = "FastForward"),
    SlowMotion         UMETA(DisplayName = "SlowMotion"),
    Headless           UMETA(DisplayName = "Headless"),
    Replay             UMETA(DisplayName = "Replay"),
    DeterministicTest  UMETA(DisplayName = "DeterministicTest")
};

UENUM(BlueprintType)
enum class ENLTAgentIntent : uint8
{
    None            UMETA(DisplayName = "None"),
    Idle            UMETA(DisplayName = "Idle"),
    FindQuietPlace  UMETA(DisplayName = "FindQuietPlace"),
    Work            UMETA(DisplayName = "Work"),
    Socialize       UMETA(DisplayName = "Socialize"),
    Rest            UMETA(DisplayName = "Rest"),
    Study           UMETA(DisplayName = "Study"),
    MoveToLocation  UMETA(DisplayName = "MoveToLocation"),
    Interact        UMETA(DisplayName = "Interact"),
    Coached         UMETA(DisplayName = "Coached"),
    Overwhelmed     UMETA(DisplayName = "Overwhelmed"),
    Drifting        UMETA(DisplayName = "Drifting"),
    Hyperfocus      UMETA(DisplayName = "Hyperfocus")
};

UENUM(BlueprintType)
enum class ENLTAgentNeed : uint8
{
    None        UMETA(DisplayName = "None"),
    Quiet       UMETA(DisplayName = "Quiet"),
    Rest        UMETA(DisplayName = "Rest"),
    Social      UMETA(DisplayName = "Social"),
    Stimulation UMETA(DisplayName = "Stimulation"),
    Food        UMETA(DisplayName = "Food"),
    Movement    UMETA(DisplayName = "Movement"),
    Privacy     UMETA(DisplayName = "Privacy")
};

namespace NLTFusion
{
    constexpr float NeedThreshold = 0.7f;
    constexpr float CognitiveLoadMax = 1.0f;
    constexpr float StressMax = 1.0f;
    constexpr float FocusMax = 1.0f;
    constexpr float BurnoutMax = 1.0f;
    constexpr float IndependenceMax = 1.0f;
    constexpr float FusionReadyMax = 1.0f;
    constexpr float SuccessRateMax = 1.0f;
}
