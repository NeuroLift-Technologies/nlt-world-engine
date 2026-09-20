#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Core/NLTNoiseLibrary.h"
#include "World/NLTWorldGenerator.h"
#include "World/NLTWorldData.h"
#include "NLTOpenWorldSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTOpenWorld, Log, All);

/**
 * Configuration for open world landscape generation.
 */
USTRUCT(BlueprintType)
struct FNLTOpenWorldConfig
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 Seed = 42;

    UPROPERTY(BlueprintReadWrite)
    FVector WorldSize = FVector(5000.0f, 5000.0f, 0.0f);

    UPROPERTY(BlueprintReadWrite)
    int32 LandscapeResolution = 513;

    UPROPERTY(BlueprintReadWrite)
    float LandscapeHeightScale = 800.0f;

    UPROPERTY(BlueprintReadWrite)
    int32 NumBuildings = 12;

    UPROPERTY(BlueprintReadWrite)
    int32 NumResidents = 8;

    UPROPERTY(BlueprintReadWrite)
    int32 NumTrees = 200;

    UPROPERTY(BlueprintReadWrite)
    int32 NumRocks = 50;

    UPROPERTY(BlueprintReadWrite)
    int32 NumGrassPatches = 300;

    UPROPERTY(BlueprintReadWrite)
    float WaterLevel = 50.0f;

    UPROPERTY(BlueprintReadWrite)
    float TreeDensity = 0.0001f;

    UPROPERTY(BlueprintReadWrite)
    float GrassDensity = 0.0002f;
};

/**
 * Open World subsystem that manages the persistent open-world level.
 * Generates landscape from FBM noise, places buildings, spawns vegetation
 * via HISM, spawns AI residents, and manages day/night cycle.
 */
UCLASS()
class WORLDENGINE_API UNLTOpenWorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /** Generate the complete open world: landscape, buildings, vegetation, residents. */
    UFUNCTION(BlueprintCallable, Category = "NLT|OpenWorld")
    void GenerateOpenWorld(const FNLTOpenWorldConfig& Config);

    /** Clear all generated world content. */
    UFUNCTION(BlueprintCallable, Category = "NLT|OpenWorld")
    void ClearOpenWorld();

    /** Check if the open world has been generated. */
    UFUNCTION(BlueprintPure, Category = "NLT|OpenWorld")
    bool IsWorldGenerated() const { return bWorldGenerated; }

    /** Get the current open world configuration. */
    UFUNCTION(BlueprintPure, Category = "NLT|OpenWorld")
    const FNLTOpenWorldConfig& GetConfig() const { return CurrentConfig; }

    /** Get the generated world result from the world generator. */
    UFUNCTION(BlueprintPure, Category = "NLT|OpenWorld")
    const FNLTWorldGenerationResult& GetGeneratedWorld() const { return WorldResult; }

    /** Spawn a building portal at the specified transform. */
    UFUNCTION(BlueprintCallable, Category = "NLT|OpenWorld")
    class ANLTBuildingPortalActor* SpawnBuildingPortal(FName BuildingType, const FTransform& Transform);

    /** Spawn vegetation instances across the landscape. */
    UFUNCTION(BlueprintCallable, Category = "NLT|OpenWorld")
    void SpawnVegetation();

    /** Spawn AI residents that wander the open world. */
    UFUNCTION(BlueprintCallable, Category = "NLT|OpenWorld")
    void SpawnResidents();

    /** Generate the landscape heightmap from FBM noise. */
    UFUNCTION(BlueprintCallable, Category = "NLT|OpenWorld")
    TArray<float> GenerateHeightmap() const;

    /** Get the terrain height at a world position. */
    UFUNCTION(BlueprintPure, Category = "NLT|OpenWorld")
    float GetTerrainHeight(float X, float Y) const;

    /** Stream in a scenario level by name. */
    UFUNCTION(BlueprintCallable, Category = "NLT|OpenWorld|Streaming")
    void StreamInLevel(const FName& LevelName);

    /** Stream out a scenario level by name. */
    UFUNCTION(BlueprintCallable, Category = "NLT|OpenWorld|Streaming")
    void StreamOutLevel(const FName& LevelName);

    /** Get the atmosphere subsystem for day/night control. */
    UFUNCTION(BlueprintPure, Category = "NLT|OpenWorld")
    class UNLTAtmosphereSubsystem* GetAtmosphereSubsystem() const;

private:
    bool bWorldGenerated = false;
    FNLTOpenWorldConfig CurrentConfig;
    FNLTWorldGenerationResult WorldResult;

    /** HISM components for vegetation. */
    UPROPERTY()
    class UHierarchicalInstancedStaticMeshComponent* TreeHISM;

    UPROPERTY()
    class UHierarchicalInstancedStaticMeshComponent* GrassHISM;

    UPROPERTY()
    class UHierarchicalInstancedStaticMeshComponent* RockHISM;

    /** Spawned building portals. */
    UPROPERTY()
    TArray<class ANLTBuildingPortalActor*> BuildingPortals;

    /** Spawned AI residents. */
    UPROPERTY()
    TArray<class AAvatarCharacter*> Residents;

    /** The world generator subsystem. */
    UPROPERTY()
    UNLTWorldGeneratorSubsystem* WorldGenerator;

    /** Generate landscape from heightmap data. */
    void GenerateLandscape(const TArray<float>& Heightmap);

    /** Place water plane at the configured water level. */
    void PlaceWaterPlane();

    /** Place atmospheric sky actors. */
    void PlaceAtmosphere();

    /** Calculate terrain height from FBM noise. */
    float CalculateTerrainHeight(float X, float Y) const;

    /** Determine if a position is suitable for vegetation. */
    bool IsSuitableForVegetation(float X, float Y, float Height) const;

    /** Get a random point on the landscape. */
    FVector GetRandomLandscapePoint(FRandomStream& Rand) const;
};
