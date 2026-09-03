#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "World/NLTWorldData.h"
#include "NLTSmartObjectWorldSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTSmartObjectWorldSubsystem, Log, All);

USTRUCT(BlueprintType)
struct FNLTWorldLocation
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    AActor* Actor = nullptr;

    UPROPERTY(BlueprintReadWrite)
    FName LocationType;

    UPROPERTY(BlueprintReadWrite)
    FString DisplayName;

    UPROPERTY(BlueprintReadWrite)
    float NoiseLevel = 0.5f;

    UPROPERTY(BlueprintReadWrite)
    float SocialDensity = 0.5f;

    UPROPERTY(BlueprintReadWrite)
    float Privacy = 0.5f;

    UPROPERTY(BlueprintReadWrite)
    FVector WorldLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite)
    TArray<FName> AvailableActivities;

    UPROPERTY(BlueprintReadWrite)
    FBox Bounds;

    UPROPERTY(BlueprintReadWrite)
    bool bIsOccupied = false;

    UPROPERTY(BlueprintReadWrite)
    int32 MaxOccupants = 1;

    UPROPERTY(BlueprintReadWrite)
    TArray<FName> CurrentOccupants;
};

UCLASS()
class UNLTSmartObjectWorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "NLT|World")
    void RegisterLocation(AActor* Actor, const FNLTWorldLocation& Location);

    UFUNCTION(BlueprintCallable, Category = "NLT|World")
    void UnregisterLocation(AActor* Actor);

    UFUNCTION(BlueprintCallable, Category = "NLT|World")
    void ReserveLocation(AActor* Actor, FName AgentId);

    UFUNCTION(BlueprintCallable, Category = "NLT|World")
    void ReleaseLocation(AActor* Actor, FName AgentId);

    UFUNCTION(BlueprintPure, Category = "NLT|World")
    TArray<FNLTWorldLocation> FindLocationsByActivity(FName Activity) const;

    UFUNCTION(BlueprintPure, Category = "NLT|World")
    TArray<FNLTWorldLocation> FindLocationsByType(FName LocationType) const;

    UFUNCTION(BlueprintPure, Category = "NLT|World")
    TArray<FNLTWorldLocation> FindLocationsByNeed(ENLTAgentNeed Need) const;

    UFUNCTION(BlueprintPure, Category = "NLT|World")
    bool FindBestLocationForAgent(FName AgentId, ENLTAgentNeed Need, FNLTWorldLocation& OutLocation) const;

    UFUNCTION(BlueprintPure, Category = "NLT|World")
    int32 GetLocationCount() const { return Locations.Num(); }

private:
    TMap<AActor*, FNLTWorldLocation> Locations;

    bool MatchesNeed(const FNLTWorldLocation& Location, ENLTAgentNeed Need) const;
    float ScoreLocation(const FNLTWorldLocation& Location, ENLTAgentNeed Need) const;
};
