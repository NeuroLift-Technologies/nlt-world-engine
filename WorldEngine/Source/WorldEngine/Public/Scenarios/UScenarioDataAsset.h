#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Engine/DataAsset.h"
#include "UScenarioDataAsset.generated.h"

/** Scenario category (maps Python scenario definitions to UE DataAssets). */
UENUM(BlueprintType)
enum class EScenarioCategory : uint8
{
    Workplace    UMETA(DisplayName = "Workplace"),
    Personal     UMETA(DisplayName = "Personal"),
    Social       UMETA(DisplayName = "Social"),
    Academic     UMETA(DisplayName = "Academic")
};

/** Scenario complexity tier. */
UENUM(BlueprintType)
enum class EScenarioComplexity : uint8
{
    Low          UMETA(DisplayName = "Low"),
    Medium       UMETA(DisplayName = "Medium"),
    High         UMETA(DisplayName = "High")
};

/**
 * PrimaryDataAsset representing a scenario definition for the NLT Fusion world engine.
 * Maps Python scenario neurolift-ai-fusion-org/src/simulation/environment/scenarios.py
 * to an editor-configurable UE 5.8 DataAsset.
 */
UCLASS(BlueprintType)
class WORLDENGINE_API UScenarioDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    /** Unique identifier (e.g. "workplace_deadline", "social_networking"). */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario")
    FName ScenarioId;

    /** Human-readable display name. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario")
    FText DisplayName;

    /** Long-form description of the scenario. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario", meta = (MultiLine = true))
    FText Description;

    /** Category bucket. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario")
    EScenarioCategory Category = EScenarioCategory::Workplace;

    /** Expected duration in minutes. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario", meta = (ClampMin = "0.0"))
    float DurationMinutes = 30.0f;

    /** Complexity tier. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario")
    EScenarioComplexity Complexity = EScenarioComplexity::Medium;

    /** Aversiveness factor (0 = pleasant, 1 = highly aversive). */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Aversiveness = 0.5f;

    /** Cognitive demand factor (0 = minimal, 1 = maximal). */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float CognitiveDemand = 0.5f;

    /** Base probability of successful completion (0-1). */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float BaseSuccessRate = 0.5f;

    /** Whether this scenario requires sustained focus to complete. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario")
    bool bRequiresSustainedFocus = false;

    /** Context parameters (arbitrary key-value metadata). */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario")
    TMap<FName, FString> ContextParams;

    /** Soft reference to the level/world to load for this scenario. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scenario")
    TSoftObjectPtr<UWorld> LevelReference;
};