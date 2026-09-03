#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTPersistenceSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTPersistence, Log, All);

USTRUCT(BlueprintType)
struct FNLTSavedGame
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString SlotName;

    UPROPERTY(BlueprintReadWrite)
    int32 SimulationTick = 0;

    UPROPERTY(BlueprintReadWrite)
    double WorldTime = 0.0;

    UPROPERTY(BlueprintReadWrite)
    TArray<FName> ActiveEvents;

    UPROPERTY(BlueprintReadWrite)
    float TimeOfDay = 12.0f;

    UPROPERTY(BlueprintReadWrite)
    int32 RandomSeed = 12345;
};

UCLASS()
class UNLTPersistenceSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "NLT|Persistence")
    bool SaveGame(const FString& SlotName);

    UFUNCTION(BlueprintCallable, Category = "NLT|Persistence")
    bool LoadGame(const FString& SlotName);

    UFUNCTION(BlueprintPure, Category = "NLT|Persistence")
    bool DoesSaveGameExist(const FString& SlotName) const;

    UFUNCTION(BlueprintCallable, Category = "NLT|Persistence")
    bool DeleteSaveGame(const FString& SlotName);

    UFUNCTION(BlueprintPure, Category = "NLT|Persistence")
    TArray<FString> GetAllSaveSlots() const;

private:
    FString GetSaveFilePath(const FString& SlotName) const;
};
