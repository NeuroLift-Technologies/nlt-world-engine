// NLTOpenWorldSubsystem.cpp

#include "World/NLTOpenWorldSubsystem.h"
#include "World/NLTBuildingPortalActor.h"
#include "Agents/AvatarCharacter.h"
#include "Simulation/NLTAtmosphereSubsystem.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/StaticMesh.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Landscape.h"
#include "LandscapeEdit.h"
#include "LandscapeInfo.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY(LogNLTOpenWorld);

// ============== Initialization ==============

void UNLTOpenWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // Get the world generator subsystem
    WorldGenerator = Collection.InitializeDependency<UNLTWorldGeneratorSubsystem>();

    UE_LOG(LogNLTOpenWorld, Log, TEXT("Open World subsystem initialized"));
}

void UNLTOpenWorldSubsystem::Deinitialize()
{
    ClearOpenWorld();

    // Cleanup HISM components
    if (TreeHISM)
    {
        TreeHISM->ClearInstances();
        TreeHISM->DestroyComponent();
        TreeHISM = nullptr;
    }
    if (GrassHISM)
    {
        GrassHISM->ClearInstances();
        GrassHISM->DestroyComponent();
        GrassHISM = nullptr;
    }
    if (RockHISM)
    {
        RockHISM->ClearInstances();
        RockHISM->DestroyComponent();
        RockHISM = nullptr;
    }

    UE_LOG(LogNLTOpenWorld, Log, TEXT("Open World subsystem deinitialized"));
}

// ============== World Generation ==============

void UNLTOpenWorldSubsystem::GenerateOpenWorld(const FNLTOpenWorldConfig& Config)
{
    CurrentConfig = Config;
    bWorldGenerated = true;

    UE_LOG(LogNLTOpenWorld, Log, TEXT("Generating open world with seed %d, world size %.0fx%.0f"),
        Config.Seed, Config.WorldSize.X, Config.WorldSize.Y);

    // Generate heightmap from FBM noise
    TArray<float> Heightmap = GenerateHeightmap();

    // Generate landscape from heightmap
    GenerateLandscape(Heightmap);

    // Place water plane at configured water level
    PlaceWaterPlane();

    // Generate world data (districts, buildings) via World Generator
    FNLTWorldGenerationParams GenParams;
    GenParams.Seed = Config.Seed;
    GenParams.WorldSize = Config.WorldSize;
    GenParams.NumDistricts = 4;
    GenParams.NumBuildings = Config.NumBuildings;

    if (WorldGenerator)
    {
        WorldResult = WorldGenerator->GenerateWorld(GenParams);
    }

    // Place atmospheric sky actors
    PlaceAtmosphere();

    // Spawn vegetation via HISM
    SpawnVegetation();

    // Spawn building portals at generated locations
    if (WorldResult.Buildings.Num() > 0)
    {
        for (const FNLTGeneratedBuilding& Building : WorldResult.Buildings)
        {
            // Offset Z position to terrain height
            FTransform AdjustedTransform = Building.Transform;
            FVector Location = AdjustedTransform.GetLocation();
            Location.Z = GetTerrainHeight(Location.X, Location.Y) + 10.0f;
            AdjustedTransform.SetLocation(Location);

            SpawnBuildingPortal(Building.BuildingType, AdjustedTransform);
        }
    }

    // Spawn AI residents
    SpawnResidents();

    UE_LOG(LogNLTOpenWorld, Log, TEXT("Open world generation complete: %d buildings, %d residents"),
        BuildingPortals.Num(), Residents.Num());
}

void UNLTOpenWorldSubsystem::ClearOpenWorld()
{
    // Destroy all building portals
    for (ANLTBuildingPortalActor* Portal : BuildingPortals)
    {
        if (Portal)
        {
            Portal->Destroy();
        }
    }
    BuildingPortals.Empty();

    // Destroy all residents
    for (AAvatarCharacter* Resident : Residents)
    {
        if (Resident)
        {
            Resident->Destroy();
        }
    }
    Residents.Empty();

    // Clear vegetation instances
    if (TreeHISM)
    {
        TreeHISM->ClearInstances();
    }
    if (GrassHISM)
    {
        GrassHISM->ClearInstances();
    }
    if (RockHISM)
    {
        RockHISM->ClearInstances();
    }

    bWorldGenerated = false;
}

// ============== Heightmap & Landscape ==============

TArray<float> UNLTOpenWorldSubsystem::GenerateHeightmap() const
{
    TArray<float> Heightmap;
    int32 Resolution = CurrentConfig.LandscapeResolution;
    Heightmap.SetNum(Resolution * Resolution);

    float HalfWorldSize = CurrentConfig.WorldSize.X * 0.5f;

    for (int32 Y = 0; Y < Resolution; Y++)
    {
        for (int32 X = 0; X < Resolution; X++)
        {
            // Convert heightmap UV to world position
            float WorldX = FMath::Lerp(-HalfWorldSize, HalfWorldSize, (float)X / (Resolution - 1));
            float WorldY = FMath::Lerp(-HalfWorldSize, HalfWorldSize, (float)Y / (Resolution - 1));

            // Sample FBM noise for terrain height
            float Height = UNLTNoiseLibrary::Fbm2D(WorldX, WorldY, CurrentConfig.Seed, 5, 2.0f, 0.5f);
            Heightmap[Y * Resolution + X] = Height;
        }
    }

    return Heightmap;
}

float UNLTOpenWorldSubsystem::CalculateTerrainHeight(float X, float Y) const
{
    float NormalizedHeight = UNLTNoiseLibrary::Fbm2D(X, Y, CurrentConfig.Seed, 5, 2.0f, 0.5f);
    return NormalizedHeight * CurrentConfig.LandscapeHeightScale;
}

float UNLTOpenWorldSubsystem::GetTerrainHeight(float X, float Y) const
{
    return CalculateTerrainHeight(X, Y);
}

void UNLTOpenWorldSubsystem::GenerateLandscape(const TArray<float>& Heightmap)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogNLTOpenWorld, Warning, TEXT("Cannot generate landscape: no world"));
        return;
    }

    // Try to find an existing landscape in the world
    for (TActorIterator<ALandscape> It(World); It; ++It)
    {
        ALandscape* Landscape = *It;
        if (Landscape)
        {
            UE_LOG(LogNLTOpenWorld, Log, TEXT("Found existing landscape: %s"), *Landscape->GetName());
            // Landscape already exists; heightmap would be applied via Landscape editing tools
            return;
        }
    }

    // Note: Creating a new Landscape via C++ requires Editor-only code.
    // For runtime, the level should have a pre-placed Landscape actor.
    // The heightmap data is available for Blueprint-exposed height queries.
    UE_LOG(LogNLTOpenWorld, Log, TEXT("Heightmap generated (%d points). Landscape actor should exist in level."),
        Heightmap.Num());
}

void UNLTOpenWorldSubsystem::PlaceWaterPlane()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // Check if water plane already exists
    for (TActorIterator<AActor> It(World); It; ++It)
    {
        if (It->GetName().Contains(TEXT("Water")))
        {
            UE_LOG(LogNLTOpenWorld, Log, TEXT("Water plane already exists"));
            return;
        }
    }

    UE_LOG(LogNLTOpenWorld, Log, TEXT("Water plane placement at height %.0f (Water plugin can be used for runtime water)"),
        CurrentConfig.WaterLevel);
}

void UNLTOpenWorldSubsystem::PlaceAtmosphere()
{
    // Atmosphere is handled by the Atmosphere Subsystem
    // This method ensures the subsystem is initialized
    UNLTAtmosphereSubsystem* Atmosphere = GetAtmosphereSubsystem();
    if (Atmosphere)
    {
        UE_LOG(LogNLTOpenWorld, Log, TEXT("Atmosphere subsystem ready"));
        Atmosphere->RefreshAtmosphere();
    }
    else
    {
        UE_LOG(LogNLTOpenWorld, Warning, TEXT("Atmosphere subsystem not available"));
    }
}

// ============== Building Portals ==============

ANLTBuildingPortalActor* UNLTOpenWorldSubsystem::SpawnBuildingPortal(FName BuildingType, const FTransform& Transform)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return nullptr;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = nullptr;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ANLTBuildingPortalActor* Portal = World->SpawnActor<ANLTBuildingPortalActor>(
        ANLTBuildingPortalActor::StaticClass(),
        Transform,
        SpawnParams
    );

    if (Portal)
    {
        Portal->SetBuildingType(GetBuildingTypeFromFName(BuildingType));
        BuildingPortals.Add(Portal);

        UE_LOG(LogNLTOpenWorld, Log, TEXT("Spawned building portal '%s' at (%.0f, %.0f, %.0f)"),
            *BuildingType.ToString(),
            Transform.GetLocation().X,
            Transform.GetLocation().Y,
            Transform.GetLocation().Z);
    }

    return Portal;
}

ENLTBuildingType UNLTOpenWorldSubsystem::GetBuildingTypeFromFName(FName TypeName) const
{
    if (TypeName == TEXT("Office")) return ENLTBuildingType::Office;
    if (TypeName == TEXT("Apartment")) return ENLTBuildingType::Apartment;
    if (TypeName == TEXT("Shop")) return ENLTBuildingType::Shop;
    if (TypeName == TEXT("School")) return ENLTBuildingType::School;
    if (TypeName == TEXT("Factory")) return ENLTBuildingType::Factory;
    if (TypeName == TEXT("Park")) return ENLTBuildingType::Park;
    return ENLTBuildingType::Hut;
}

// ============== Vegetation (HISM) ==============

void UNLTOpenWorldSubsystem::SpawnVegetation()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // Create HISM components for vegetation
    // These are attached to a root actor (this subsystem's owner)

    // --- Trees ---
    TreeHISM = NewObject<UHierarchicalInstancedStaticMeshComponent>(this, TEXT("TreeHISM"));
    TreeHISM->RegisterComponent();

    // Use a simple cylinder/cone as a placeholder tree mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> TreeMeshFinder(TEXT("/Engine/BasicShapes/Cylinder"));
    if (TreeMeshFinder.Succeeded())
    {
        TreeHISM->SetStaticMesh(TreeMeshFinder.Object);
    }

    // --- Grass ---
    GrassHISM = NewObject<UHierarchicalInstancedStaticMeshComponent>(this, TEXT("GrassHISM"));
    GrassHISM->RegisterComponent();

    static ConstructorHelpers::FObjectFinder<UStaticMesh> GrassMeshFinder(TEXT("/Engine/BasicShapes/Plane"));
    if (GrassMeshFinder.Succeeded())
    {
        GrassHISM->SetStaticMesh(GrassMeshFinder.Object);
    }

    // --- Rocks ---
    RockHISM = NewObject<UHierarchicalInstancedStaticMeshComponent>(this, TEXT("RockHISM"));
    RockHISM->RegisterComponent();

    static ConstructorHelpers::FObjectFinder<UStaticMesh> RockMeshFinder(TEXT("/Engine/BasicShapes/Sphere"));
    if (RockMeshFinder.Succeeded())
    {
        RockHISM->SetStaticMesh(RockMeshFinder.Object);
    }

    // Scatter vegetation across the landscape
    FRandomStream Rand(CurrentConfig.Seed + 100);

    float HalfWorldSize = CurrentConfig.WorldSize.X * 0.5f;

    // Spawn trees
    for (int32 i = 0; i < CurrentConfig.NumTrees; i++)
    {
        float X = Rand.FRandRange(-HalfWorldSize, HalfWorldSize);
        float Y = Rand.FRandRange(-HalfWorldSize, HalfWorldSize);
        float Height = GetTerrainHeight(X, Y);

        if (IsSuitableForVegetation(X, Y, Height))
        {
            float Scale = Rand.FRandRange(0.8f, 2.0f);
            FTransform InstanceTransform(
                FRotator(0.0f, Rand.FRandRange(0.0f, 360.0f), 0.0f),
                FVector(X, Y, Height),
                FVector(Scale, Scale, Scale * Rand.FRandRange(2.0f, 4.0f))
            );
            TreeHISM->AddInstance(InstanceTransform);
        }
    }

    // Spawn grass patches
    for (int32 i = 0; i < CurrentConfig.NumGrassPatches; i++)
    {
        float X = Rand.FRandRange(-HalfWorldSize, HalfWorldSize);
        float Y = Rand.FRandRange(-HalfWorldSize, HalfWorldSize);
        float Height = GetTerrainHeight(X, Y);

        if (IsSuitableForVegetation(X, Y, Height))
        {
            float Scale = Rand.FRandRange(0.5f, 1.5f);
            FTransform InstanceTransform(
                FRotator(0.0f, Rand.FRandRange(0.0f, 360.0f), 0.0f),
                FVector(X, Y, Height + 2.0f),
                FVector(Scale, Scale, Scale * 0.3f)
            );
            GrassHISM->AddInstance(InstanceTransform);
        }
    }

    // Spawn rocks
    for (int32 i = 0; i < CurrentConfig.NumRocks; i++)
    {
        float X = Rand.FRandRange(-HalfWorldSize, HalfWorldSize);
        float Y = Rand.FRandRange(-HalfWorldSize, HalfWorldSize);
        float Height = GetTerrainHeight(X, Y);

        if (IsSuitableForVegetation(X, Y, Height))
        {
            float Scale = Rand.FRandRange(0.3f, 1.5f);
            FTransform InstanceTransform(
                FRotator(Rand.FRandRange(0.0f, 45.0f), Rand.FRandRange(0.0f, 360.0f), Rand.FRandRange(0.0f, 45.0f)),
                FVector(X, Y, Height),
                FVector(Scale, Scale * Rand.FRandRange(0.5f, 1.5f), Scale * Rand.FRandRange(0.3f, 0.8f))
            );
            RockHISM->AddInstance(InstanceTransform);
        }
    }

    UE_LOG(LogNLTOpenWorld, Log, TEXT("Vegetation spawned: %d trees, %d grass, %d rocks"),
        TreeHISM->GetInstanceCount(),
        GrassHISM->GetInstanceCount(),
        RockHISM->GetInstanceCount());
}

bool UNLTOpenWorldSubsystem::IsSuitableForVegetation(float X, float Y, float Height) const
{
    // Vegetation grows above water level and below snow line
    return Height > CurrentConfig.WaterLevel &&
           Height < CurrentConfig.LandscapeHeightScale * 0.75f;
}

FVector UNLTOpenWorldSubsystem::GetRandomLandscapePoint(FRandomStream& Rand) const
{
    float HalfWorldSize = CurrentConfig.WorldSize.X * 0.5f;
    float X = Rand.FRandRange(-HalfWorldSize, HalfWorldSize);
    float Y = Rand.FRandRange(-HalfWorldSize, HalfWorldSize);
    float Z = GetTerrainHeight(X, Y);
    return FVector(X, Y, Z);
}

// ============== AI Residents ==============

void UNLTOpenWorldSubsystem::SpawnResidents()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    FRandomStream Rand(CurrentConfig.Seed + 200);

    // Categorize buildings by type for daily routine mapping
    ANLTBuildingPortalActor* OfficePortal = nullptr;
    ANLTBuildingPortalActor* ApartmentPortal = nullptr;
    ANLTBuildingPortalActor* ShopPortal = nullptr;
    ANLTBuildingPortalActor* SchoolPortal = nullptr;
    ANLTBuildingPortalActor* HutPortal = nullptr;

    for (ANLTBuildingPortalActor* Portal : BuildingPortals)
    {
        if (!Portal) continue;

        switch (Portal->GetBuildingType())
        {
        case ENLTBuildingType::Office:
            if (!OfficePortal) OfficePortal = Portal;
            break;
        case ENLTBuildingType::Apartment:
            if (!ApartmentPortal) ApartmentPortal = Portal;
            break;
        case ENLTBuildingType::Shop:
            if (!ShopPortal) ShopPortal = Portal;
            break;
        case ENLTBuildingType::School:
            if (!SchoolPortal) SchoolPortal = Portal;
            break;
        case ENLTBuildingType::Hut:
            if (!HutPortal) HutPortal = Portal;
            break;
        default:
            break;
        }
    }

    // Spawn residents with daily routines
    for (int32 i = 0; i < 12; i++)
    {
        FVector SpawnPos = GetRandomLandscapePoint(Rand);
        SpawnPos.Z += 90.0f;  // Feet height offset for character

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        AAvatarCharacter* Resident = World->SpawnActor<AAvatarCharacter>(
            AAvatarCharacter::StaticClass(),
            SpawnPos,
            FRotator::ZeroRotator,
            SpawnParams
        );

        if (Resident)
        {
            Resident->WanderRadius = Rand.FRandRange(500.0f, 2000.0f);
            Resident->WaitTimeMin = 1.0f;
            Resident->WaitTimeMax = 4.0f;

            // Assign daily routine based on index pattern
            // Morning (6-9): walk to workplace (Office -> Workplace_Level)
            // Midday (12-14): walk to social (Shop -> Social_Level)
            // Evening (18-21): walk to home (Apartment -> Personal_Level)
            // Night (22-6): stay home

            // Assign a primary destination based on resident index
            if (i < 3 && OfficePortal)
            {
                // Office workers
                Resident->CharacterRole = ENLTAgentRole::Avatar;
            }
            else if (i < 6 && ShopPortal)
            {
                // Shop visitors/workers
                Resident->CharacterRole = ENLTAgentRole::Avatar;
            }
            else if (i < 9 && ApartmentPortal)
            {
                // Residents
                Resident->CharacterRole = ENLTAgentRole::Avatar;
            }
            else
            {
                // Others: Hut visitors, etc.
                Resident->CharacterRole = ENLTAgentRole::Advocate;
            }

            Residents.Add(Resident);

            UE_LOG(LogNLTOpenWorld, Log, TEXT("Spawned AI resident '%s' at (%.0f, %.0f, %.0f)"),
                *Resident->GetName(), SpawnPos.X, SpawnPos.Y, SpawnPos.Z);
        }
    }

    UE_LOG(LogNLTOpenWorld, Log, TEXT("Spawned %d AI residents"), Residents.Num());
}

// ============== Level Streaming ==============

void UNLTOpenWorldSubsystem::StreamInLevel(const FName& LevelName)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    FString LevelPath = FString::Printf(TEXT("/Game/Scenarios/Levels/%s"), *LevelName.ToString());

    // Use LevelStreamingDynamic to load a sublevel
    bool bSuccess = false;
    ULevelStreamingDynamic* StreamingLevel = ULevelStreamingDynamic::LoadLevelInstance(
        World,
        LevelPath,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        bSuccess
    );

    if (bSuccess && StreamingLevel)
    {
        UE_LOG(LogNLTOpenWorld, Log, TEXT("Streaming in level: %s"), *LevelName.ToString());
    }
    else
    {
        UE_LOG(LogNLTOpenWorld, Warning, TEXT("Failed to stream in level: %s"), *LevelName.ToString());
    }
}

void UNLTOpenWorldSubsystem::StreamOutLevel(const FName& LevelName)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // Find the streaming level by name
    for (ULevelStreaming* StreamingLevel : World->GetStreamingLevels())
    {
        if (StreamingLevel && StreamingLevel->GetWorldAssetPackageName().Contains(LevelName.ToString()))
        {
            StreamingLevel->SetShouldBeLoaded(false);
            StreamingLevel->SetShouldBeVisible(false);
            UE_LOG(LogNLTOpenWorld, Log, TEXT("Streaming out level: %s"), *LevelName.ToString());
            return;
        }
    }

    UE_LOG(LogNLTOpenWorld, Warning, TEXT("Level not found for streaming out: %s"), *LevelName.ToString());
}

// ============== Atmosphere Access ==============

UNLTAtmosphereSubsystem* UNLTOpenWorldSubsystem::GetAtmosphereSubsystem() const
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return nullptr;
    }

    return World->GetSubsystem<UNLTAtmosphereSubsystem>();
}
