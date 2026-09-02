#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTFusionRoleManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTFusionRoleManager, Log, All);

UENUM(BlueprintType)
enum class ENLTFusionRoleState : uint8
{
    Inactive    UMETA(DisplayName = "Inactive"),
    Active      UMETA(DisplayName = "Active"),
    Coaching    UMETA(DisplayName = "Coaching"),
    Monitoring  UMETA(DisplayName = "Monitoring"),
    Fused       UMETA(DisplayName = "Fused")
};

USTRUCT(BlueprintType)
struct FNLTFusionPair
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FName PairId;

    UPROPERTY(BlueprintReadWrite)
    FName AvatarId;

    UPROPERTY(BlueprintReadWrite)
    FName AideId;

    UPROPERTY(BlueprintReadWrite)
    float BondStrength = 0.0f;

    UPROPERTY(BlueprintReadWrite)
    float FusionReadiness = 0.0f;

    UPROPERTY(BlueprintReadWrite)
    ENLTFusionRoleState AvatarState = ENLTFusionRoleState::Active;

    UPROPERTY(BlueprintReadWrite)
    ENLTFusionRoleState AideState = ENLTFusionRoleState::Coaching;
};

USTRUCT(BlueprintType)
struct FNLTAdvocate
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FName AdvocateId;

    UPROPERTY(BlueprintReadWrite)
    TArray<FName> MonitoredPairs;

    UPROPERTY(BlueprintReadWrite)
    int32 MaxMonitoringCapacity = 5;

    UPROPERTY(BlueprintReadWrite)
    ENLTFusionRoleState State = ENLTFusionRoleState::Monitoring;
};

UCLASS()
class UNLTFusionRoleManager : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "NLT|Roles")
    FName CreatePair(FName AvatarId, FName AideId);

    UFUNCTION(BlueprintCallable, Category = "NLT|Roles")
    void DestroyPair(FName PairId);

    UFUNCTION(BlueprintPure, Category = "NLT|Roles")
    bool GetPair(FName PairId, FNLTFusionPair& OutPair) const;

    UFUNCTION(BlueprintCallable, Category = "NLT|Roles")
    FName CreateAdvocate(FName AdvocateId);

    UFUNCTION(BlueprintCallable, Category = "NLT|Roles")
    void AssignPairToAdvocate(FName PairId, FName AdvocateId);

    UFUNCTION(BlueprintCallable, Category = "NLT|Roles")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintPure, Category = "NLT|Roles")
    int32 GetPairCount() const { return Pairs.Num(); }

    UFUNCTION(BlueprintPure, Category = "NLT|Roles")
    int32 GetAdvocateCount() const { return Advocates.Num(); }

private:
    TMap<FName, FNLTFusionPair> Pairs;
    TMap<FName, FNLTAdvocate> Advocates;

    void UpdatePair(FNLTFusionPair& Pair, float DeltaTime);
    void UpdateAdvocate(FNLTAdvocate& Advocate, float DeltaTime);
    void CheckFusionReadiness(FNLTFusionPair& Pair);
};
