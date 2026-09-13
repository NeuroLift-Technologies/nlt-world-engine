// NLTTrainingGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "Scenarios/NLTDemoGameMode.h"
#include "NLTTrainingGameMode.generated.h"

UCLASS()
class WORLDENGINE_API ANLTTrainingGameMode : public ANLTDemoGameMode
{
    GENERATED_BODY()

public:
    ANLTTrainingGameMode();

    virtual void BeginPlay() override;
};
