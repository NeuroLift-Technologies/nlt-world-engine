// NLTEnvironmentVariation.h - seeded micro-variation for Workplace_Level
#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Core/NLTSimulationState.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTEnvironmentVariation.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTEnvironmentVariation, Log, All);

/**
 * Deterministic environment state produced from (ScenarioId, RunSeed).
 * Same scenario ID + different run seed => different clutter, lighting, VFX.
 */
USTRUCT(BlueprintType)
struct FNLTEnvironmentState
{
    GENERATED_BODY()

    // ---- Clutter ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    int32 ClutterDensity = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    float ClutterSpread = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    TArray<int32> ClutterVariantIndices;

    // ---- Lighting ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    float LightingIntensity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    FLinearColor LightingColor = FLinearColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    float ColorTemperature = 6500.0f;

    // ---- VFX ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    int32 VfxSeed = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    float VfxIntensity = 1.0f;

    // ---- Ambient ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    float AmbientNoiseLevel = 0.0f;

    // ---- Meta ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment")
    int32 VariationIndex = 0;
};

/**
 * Seeded micro-variation subsystem for Workplace_Level.
 * Extends FNLTRandomStream to env dressing: same scenario ID produces
 * different environmental states (clutter, lighting, VFX seed) per run.
 */
UCLASS()
class UNLTEnvironmentVariationSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /** Generate deterministic environment state from (ScenarioId, RunSeed). */
    UFUNCTION(BlueprintCallable, Category = "NLT|Environment")
    FNLTEnvironmentState GenerateEnvironmentVariation(FName ScenarioId, int32 RunSeed);

    /** Generate and store as the active environment state. */
    UFUNCTION(BlueprintCallable, Category = "NLT|Environment")
    void ApplyEnvironmentVariation(FName ScenarioId, int32 RunSeed);

    UFUNCTION(BlueprintPure, Category = "NLT|Environment")
    const FNLTEnvironmentState& GetActiveEnvironmentState() const { return ActiveEnvironment; }

    /** Number of distinct base variations (moods) the system can produce. */
    UFUNCTION(BlueprintPure, Category = "NLT|Environment")
    static int32 GetVariationCount() { return MaxVariations; }

    static constexpr int32 MaxVariations = 8;

private:
    FNLTEnvironmentState ActiveEnvironment;

    static uint32 HashScenarioRun(FName ScenarioId, int32 RunSeed);
};
