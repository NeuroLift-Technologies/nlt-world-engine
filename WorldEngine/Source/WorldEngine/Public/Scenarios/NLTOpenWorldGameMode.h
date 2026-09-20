// NLTOpenWorldGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "Scenarios/NLTDemoGameMode.h"
#include "World/NLTOpenWorldSubsystem.h"
#include "NLTOpenWorldGameMode.generated.h"

UCLASS()
class WORLDENGINE_API ANLTOpenWorldGameMode : public ANLTDemoGameMode
{
	GENERATED_BODY()

public:
	ANLTOpenWorldGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "NLT|OpenWorld")
	FNLTOpenWorldConfig OpenWorldConfig;

private:
	UNLTOpenWorldSubsystem* GetOpenWorldSubsystem() const;
};
