#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "NLTWorldData.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTWorld, Log, All);

USTRUCT(BlueprintType)
struct FNLTLocationSemanticData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LocationType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float NoiseLevel = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float SocialDensity = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Privacy = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Accessibility = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> AvailableActivities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FBox Bounds;
};

USTRUCT(BlueprintType)
struct FNLTWorldState
{
    GENERATED_BODY()

    UPROPERTY()
    int32 SimulationTick = 0;

    UPROPERTY()
    double WorldTime = 0.0;

    UPROPERTY()
    TArray<FName> ActiveEvents;

    UPROPERTY()
    float TimeOfDay = 12.0f;
};
