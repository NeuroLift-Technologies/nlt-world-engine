#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Core/NLTSimulationState.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTDeterministicSeedSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTDeterministicSeed, Log, All);

/** Categories of deterministic RNG streams for environment-only mode. */
UENUM(BlueprintType)
enum class ENLTSeedCategory : uint8
{
	Dress           UMETA(DisplayName = "Dress"),           // Character appearance/outfit variations
	VFX             UMETA(DisplayName = "VFX"),             // Visual effects (particles, lighting)
	Ambient         UMETA(DisplayName = "Ambient"),         // Ambient environment variations
	Weather         UMETA(DisplayName = "Weather"),         // Weather pattern variations
	Lighting        UMETA(DisplayName = "Lighting"),        // Lighting variations
	Props           UMETA(DisplayName = "Props"),           // Prop placement variations
	Flora           UMETA(DisplayName = "Flora")            // Vegetation/flora variations
};

/**
 * Deterministic seed management for environment-only mode.
 * Provides separate RNG streams per visual category (dress, VFX, etc.)
 * so that environment variations are reproducible from a single master seed.
 */
UCLASS()
class UNLTDeterministicSeedSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Set the master seed. Derives all category seeds from it. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	void SetMasterSeed(int32 InMasterSeed);

	/** Get the current master seed. */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Seed")
	int32 GetMasterSeed() const { return MasterSeed; }

	/** Get the seed for a specific category. */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Seed")
	int32 GetCategorySeed(ENLTSeedCategory Category) const;

	/** Get the RNG stream for a specific category (const access). */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Seed")
	const FNLTRandomStream& GetCategoryRNG(ENLTSeedCategory Category) const;

	/** Get the RNG stream for a specific category (mutable access). */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Seed")
	FNLTRandomStream& GetCategoryRNGMutable(ENLTSeedCategory Category);

	/** Reset all category streams to their initial derived seeds. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	void ResetAllStreams();

	/** Reset a single category stream to its derived seed. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	void ResetStream(ENLTSeedCategory Category);

	/** Get a deterministic float [0,1) for a category (advances that stream). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	float GetDeterministicFloat(ENLTSeedCategory Category);

	/** Get a deterministic float in [Min, Max) for a category. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	float GetDeterministicRange(ENLTSeedCategory Category, float Min, float Max);

	/** Get a deterministic int in [Min, Max] for a category. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	int32 GetDeterministicInt(ENLTSeedCategory Category, int32 Min, int32 Max);

	/** Get a deterministic bool for a category (50/50). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	bool GetDeterministicBool(ENLTSeedCategory Category);

	/** Get a deterministic index into an array for a category. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	int32 GetDeterministicIndex(ENLTSeedCategory Category, int32 ArraySize);

	/** Serialize seed state for persistence. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	void SerializeSeedState(TArray<uint8>& OutData) const;

	/** Deserialize and restore seed state. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Seed")
	bool DeserializeSeedState(const TArray<uint8>& InData);

private:
	/** Derive a category seed from the master seed using a hash. */
	static int32 DeriveCategorySeed(int32 InMasterSeed, ENLTSeedCategory Category);

	int32 MasterSeed = 0;

	/** Number of seed categories (must match ENLTSeedCategory count). */
	static constexpr int32 NumCategories = 7;
	TArray<FNLTRandomStream> CategoryStreams;
};
