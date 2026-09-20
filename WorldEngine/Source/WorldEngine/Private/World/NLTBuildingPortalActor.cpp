// NLTBuildingPortalActor.cpp

#include "World/NLTBuildingPortalActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/AssetManager.h"
#include "EngineUtils.h"
#include "Engine/Font.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY(LogNLTBuildingPortal);

// ============== Constructor ==============

ANLTBuildingPortalActor::ANLTBuildingPortalActor()
    : StreamingHandle(nullptr)
    , SavedPlayerPosition(FVector::ZeroVector)
    , SavedPlayerRotation(FRotator::ZeroRotator)
{
    PrimaryActorTick.bCanEverTick = true;

    // Root scene component; the building mesh is a child so imported Fab meshes can be
    // re-anchored without shifting the interaction volume or labels.
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    // Create the building mesh (visual exterior)
    BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
    BuildingMesh->SetupAttachment(SceneRoot);

    // Use a default cube as placeholder building shell
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        BuildingMesh->SetStaticMesh(CubeMesh.Object);
    }
    BuildingMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 4.0f));  // Tall building shape
    BuildingMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    // Create the interaction volume
    InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
    InteractionVolume->SetupAttachment(RootComponent);
    InteractionVolume->SetBoxExtent(FVector(150.0f, 150.0f, 200.0f));
    InteractionVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // Create front label
    BuildingLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BuildingLabel"));
    BuildingLabel->SetupAttachment(RootComponent);
    BuildingLabel->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
    BuildingLabel->SetUsingAbsoluteScale(true);
    BuildingLabel->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
    static ConstructorHelpers::FObjectFinder<UFont> PortalFont(TEXT("/Engine/EngineFonts/Roboto"));
    if (PortalFont.Succeeded())
    {
        BuildingLabel->SetFont(PortalFont.Object);
    }
    BuildingLabel->SetWorldSize(40.0f);
    BuildingLabel->SetTextRenderColor(FColor(0, 255, 200));
    BuildingLabel->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    BuildingLabel->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    BuildingLabel->SetText(FText::FromString(TEXT("BUILDING")));
    BuildingLabel->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BuildingLabel->SetCastShadow(false);
    BuildingLabel->SetHiddenInGame(false);

    // Create back label (mirrored)
    BuildingLabelBack = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BuildingLabelBack"));
    BuildingLabelBack->SetupAttachment(RootComponent);
    BuildingLabelBack->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
    BuildingLabelBack->SetUsingAbsoluteScale(true);
    BuildingLabelBack->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
    if (PortalFont.Succeeded())
    {
        BuildingLabelBack->SetFont(PortalFont.Object);
    }
    BuildingLabelBack->SetWorldSize(40.0f);
    BuildingLabelBack->SetTextRenderColor(FColor(0, 255, 200));
    BuildingLabelBack->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    BuildingLabelBack->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    BuildingLabelBack->SetText(FText::FromString(TEXT("BUILDING")));
    BuildingLabelBack->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BuildingLabelBack->SetCastShadow(false);
    BuildingLabelBack->SetHiddenInGame(false);

    OverlappingPlayer = nullptr;
    bLevelLoaded = false;
    bIsTransitioning = false;
}

// ============== BeginPlay / Tick ==============

void ANLTBuildingPortalActor::BeginPlay()
{
    Super::BeginPlay();

    // Sync label text with display name
    UpdateLabelText();

    // Bind overlap events
    if (InteractionVolume)
    {
        InteractionVolume->OnComponentBeginOverlap.AddDynamic(this, &ANLTBuildingPortalActor::OnOverlapBegin);
        InteractionVolume->OnComponentEndOverlap.AddDynamic(this, &ANLTBuildingPortalActor::OnOverlapEnd);
    }
}

void ANLTBuildingPortalActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Label facing: orient toward the player if nearby
    if (BuildingLabel && OverlappingPlayer)
    {
        FVector DirectionToPlayer = OverlappingPlayer->GetActorLocation() - BuildingLabel->GetComponentLocation();
        if (!DirectionToPlayer.IsNearlyZero())
        {
            SetLabelFacing(DirectionToPlayer);
        }
    }
}

// ============== Building Type & Label ==============

void ANLTBuildingPortalActor::SetBuildingType(ENLTBuildingType NewType)
{
    BuildingType = NewType;
    TargetLevelName = BuildingTypeToLevelName(NewType);
    DisplayName = BuildingTypeToDisplayName(NewType);
    UpdateLabelText();
    UpdateBuildingMesh();
}

FName ANLTBuildingPortalActor::BuildingTypeToLevelName(ENLTBuildingType Type) const
{
    switch (Type)
    {
    case ENLTBuildingType::Office:    return TEXT("Workplace_Level");
    case ENLTBuildingType::Apartment: return TEXT("Personal_Level");
    case ENLTBuildingType::Shop:      return TEXT("Social_Level");
    case ENLTBuildingType::School:    return TEXT("Academic_Level");
    case ENLTBuildingType::Hut:       return TEXT("OpenWorld_Level");  // Return to open world hub
    default:                          return TEXT("Workplace_Level");
    }
}

FText ANLTBuildingPortalActor::BuildingTypeToDisplayName(ENLTBuildingType Type) const
{
    switch (Type)
    {
    case ENLTBuildingType::Office:    return NSLOCTEXT("NLT", "PortalOffice", "Office Building");
    case ENLTBuildingType::Apartment: return NSLOCTEXT("NLT", "PortalApartment", "Apartment");
    case ENLTBuildingType::Shop:      return NSLOCTEXT("NLT", "PortalShop", "Shop");
    case ENLTBuildingType::School:    return NSLOCTEXT("NLT", "PortalSchool", "School");
    case ENLTBuildingType::Hut:       return NSLOCTEXT("NLT", "PortalHut", "Hut");
    default:                          return NSLOCTEXT("NLT", "PortalDefault", "Building");
    }
}

void ANLTBuildingPortalActor::UpdateLabelText()
{
    if (BuildingLabel)
    {
        BuildingLabel->SetText(DisplayName);
    }
    if (BuildingLabelBack)
    {
        BuildingLabelBack->SetText(DisplayName);
    }
}

void ANLTBuildingPortalActor::SetLabelFacing(const FVector& FaceDirection)
{
    if (!BuildingLabel) return;

    const FVector N = FaceDirection.GetSafeNormal();
    const FVector Up(0.0f, 0.0f, 1.0f);
    // TextRender reads along -Y, readable face toward -X
    const FVector X = -N;
    const FVector Z = Up;
    const FVector Y = FVector::CrossProduct(Z, X).GetSafeNormal();
    BuildingLabel->SetWorldRotation(FMatrix(X, Y, Z, FVector::ZeroVector).ToQuat().Rotator());

    if (BuildingLabelBack)
    {
        const FRotator BackRelative(0.0f, 180.0f, 0.0f);
        BuildingLabelBack->SetWorldRotation(
            (FMatrix(X, Y, Z, FVector::ZeroVector).ToQuat() * BackRelative.Quaternion()).Rotator());
    }
}

void ANLTBuildingPortalActor::UpdateBuildingMesh()
{
    // Fab "Modern_City_Environment" (AI-usable) building meshes - geometry-only GLB imports.
    // Each building type maps to a city tower archetype; Park uses the city grove; the Hut
    // keeps the placeholder cube (isolated camp structure).
    static const TCHAR* OfficeMeshPath    = TEXT("/Game/City/Buildings/Building11/Building_11/StaticMeshes/Building_11.Building_11");
    static const TCHAR* ApartmentMeshPath = TEXT("/Game/City/Buildings/Building12/Building_12/StaticMeshes/Building_12.Building_12");
    static const TCHAR* ShopMeshPath      = TEXT("/Game/City/Buildings/Building12/Building_12/StaticMeshes/Building_12.Building_12");
    static const TCHAR* SchoolMeshPath    = TEXT("/Game/City/Buildings/Building11/Building_11/StaticMeshes/Building_11.Building_11");
    static const TCHAR* FactoryMeshPath   = TEXT("/Game/City/Buildings/Building12/Building_12/StaticMeshes/Building_12.Building_12");
    static const TCHAR* ParkMeshPath      = TEXT("/Game/City/Buildings/GridTrees/Grid_Trees__Low_Poly_/StaticMeshes/Grid_Trees__Low_Poly_.Grid_Trees__Low_Poly_");

    const TCHAR* MeshPath = nullptr;
    switch (BuildingType)
    {
    case ENLTBuildingType::Office:    MeshPath = OfficeMeshPath;    break;
    case ENLTBuildingType::Apartment: MeshPath = ApartmentMeshPath; break;
    case ENLTBuildingType::Shop:      MeshPath = ShopMeshPath;      break;
    case ENLTBuildingType::School:    MeshPath = SchoolMeshPath;    break;
    case ENLTBuildingType::Factory:   MeshPath = FactoryMeshPath;   break;
    case ENLTBuildingType::Park:      MeshPath = ParkMeshPath;      break;
    case ENLTBuildingType::Hut:
    default:
        MeshPath = nullptr;
        break;
    }

    UStaticMesh* CityMesh = MeshPath ? LoadObject<UStaticMesh>(nullptr, MeshPath) : nullptr;
    if (MeshPath && !CityMesh)
    {
        UE_LOG(LogNLTBuildingPortal, Warning,
            TEXT("UpdateBuildingMesh: city mesh '%s' failed to load (type %d) - using placeholder cube"),
            MeshPath, (int32)BuildingType);
    }

    if (CityMesh)
    {
        BuildingMesh->SetStaticMesh(CityMesh);

        // Target footprint (half extents, UE cm) per type - city-block proportions for the
        // 5000x5000 open world: towers ~20-26m, low-rise ~12m, park grove wide and low.
        FVector TargetHalfExtent(1000.0f, 900.0f, 800.0f);
        switch (BuildingType)
        {
        case ENLTBuildingType::Office:    TargetHalfExtent = FVector(1100.0f, 1100.0f, 1200.0f); break;
        case ENLTBuildingType::Apartment: TargetHalfExtent = FVector(1200.0f,  900.0f, 1100.0f); break;
        case ENLTBuildingType::Shop:      TargetHalfExtent = FVector( 800.0f,  600.0f,  600.0f); break;
        case ENLTBuildingType::School:    TargetHalfExtent = FVector(1200.0f,  900.0f, 1000.0f); break;
        case ENLTBuildingType::Factory:   TargetHalfExtent = FVector(1300.0f, 1000.0f,  950.0f); break;
        case ENLTBuildingType::Park:      TargetHalfExtent = FVector(1500.0f, 1100.0f,  700.0f); break;
        default:                          break;
        }

        const FBox SourceBounds = CityMesh->GetBoundingBox();
        const FVector SourceCenter = SourceBounds.GetCenter();
        const FVector SourceExtent = SourceBounds.GetExtent();

        // Scale the source mesh up/down so its half-extents match the target footprint.
        FVector MeshScale(1.0f, 1.0f, 1.0f);
        if (BuildingType == ENLTBuildingType::Park)
        {
            // Park grove: the GridTrees mesh is a wide low carpet (233x181x4m) - scale uniformly
            // on X so the tree proportions stay natural.
            const float ParkScale = (SourceExtent.X > 1.0f) ? (TargetHalfExtent.X / SourceExtent.X) : 1.0f;
            MeshScale = FVector(ParkScale, ParkScale, ParkScale);
        }
        else
        {
            if (SourceExtent.X > 1.0f) { MeshScale.X = TargetHalfExtent.X / SourceExtent.X; }
            if (SourceExtent.Y > 1.0f) { MeshScale.Y = TargetHalfExtent.Y / SourceExtent.Y; }
            if (SourceExtent.Z > 1.0f) { MeshScale.Z = TargetHalfExtent.Z / SourceExtent.Z; }
        }

        // Anchor the imported mesh to the actor origin *at its base*: X/Y re-center the mesh,
        // Z puts the base exactly on the spawn point (terrain + teleport offset).
        BuildingMesh->SetRelativeLocation(FVector(
            -SourceCenter.X * MeshScale.X,
            -SourceCenter.Y * MeshScale.Y,
            (SourceExtent.Z - SourceCenter.Z) * MeshScale.Z));
        BuildingMesh->SetRelativeScale3D(MeshScale);

        // Interaction volume: footprint + margin, but low enough that a ground-level pawn
        // overlaps it while approaching the entrance.
        const FVector ScaledExtent = SourceExtent * MeshScale;
        const FVector VolumeExtent(
            FMath::Clamp(ScaledExtent.X + 300.0f, 500.0f, 1600.0f),
            FMath::Clamp(ScaledExtent.Y + 300.0f, 500.0f, 1600.0f),
            FMath::Clamp(ScaledExtent.Z * 0.35f, 400.0f, 900.0f));
        InteractionVolume->SetRelativeLocation(FVector(0.0f, 0.0f, VolumeExtent.Z * 0.5f));
        InteractionVolume->SetBoxExtent(VolumeExtent);

        // Labels float above the roof.
        const float LabelZ = ScaledExtent.Z * 2.0f + 500.0f;
        BuildingLabel->SetRelativeLocation(FVector(0.0f, 0.0f, LabelZ));
        BuildingLabelBack->SetRelativeLocation(FVector(0.0f, 0.0f, LabelZ));
    }
    else
    {
        // Placeholder cube fallback (Hut / failed load). Keep original type-based scaling.
        FVector CubeScale(3.0f, 3.0f, 4.0f);
        switch (BuildingType)
        {
        case ENLTBuildingType::Office:    CubeScale = FVector(4.0f, 4.0f, 6.0f); break;
        case ENLTBuildingType::Apartment: CubeScale = FVector(5.0f, 3.0f, 8.0f); break;
        case ENLTBuildingType::Shop:      CubeScale = FVector(6.0f, 4.0f, 3.0f); break;
        case ENLTBuildingType::School:    CubeScale = FVector(7.0f, 5.0f, 4.0f); break;
        case ENLTBuildingType::Hut:       CubeScale = FVector(3.0f, 3.0f, 2.5f); break;
        default:                          break;
        }

        if (UStaticMesh* Cube = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube")))
        {
            BuildingMesh->SetStaticMesh(Cube);
        }
        BuildingMesh->SetRelativeLocation(FVector::ZeroVector);
        BuildingMesh->SetRelativeScale3D(CubeScale);

        InteractionVolume->SetRelativeLocation(FVector::ZeroVector);
        InteractionVolume->SetBoxExtent(FVector(150.0f, 150.0f, 200.0f));
        BuildingLabel->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
        BuildingLabelBack->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
    }
}

// ============== Overlap Events ==============

void ANLTBuildingPortalActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || !bIsActive || bIsTransitioning)
    {
        return;
    }

    if (APawn* Pawn = Cast<APawn>(OtherActor))
    {
        UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': Pawn '%s' entered range"),
            *GetName(), *Pawn->GetName());
        OverlappingPlayer = Pawn;

        // Check if this is the local player (auto-enter)
        if (UWorld* World = GetWorld())
        {
            if (APlayerController* PC = World->GetFirstPlayerController())
            {
                if (Pawn == PC->GetPawn())
                {
                    UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': Player entered — auto-streaming"),
                        *GetName());
                    OnInteract();
                }
            }
        }
        else
        {
            // For AI residents: trigger level streaming when they enter
            // AI residents use this to enter buildings for their daily routines
            UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': AI resident entered — triggering stream"),
                *GetName());
            StreamInTargetLevel();
        }
    }
}

void ANLTBuildingPortalActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!OtherActor)
    {
        return;
    }

    if (Cast<APawn>(OtherActor))
    {
        if (OverlappingPlayer == OtherActor)
        {
            UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': Pawn '%s' left range"),
                *GetName(), *OtherActor->GetName());
            OverlappingPlayer = nullptr;

            // If we were streaming, start a timer to unload
            if (bLevelLoaded && !bIsTransitioning)
            {
                FTimerHandle UnloadTimer;
                FTimerDelegate UnloadDelegate;
                UnloadDelegate.BindLambda([this]()
                {
                    if (!OverlappingPlayer)
                    {
                        ReturnPlayerToOpenWorld();
                    }
                });
                GetWorldTimerManager().SetTimer(UnloadTimer, UnloadDelegate, 5.0f, false);
            }
        }
    }
}

// ============== Interaction & Streaming ==============

void ANLTBuildingPortalActor::OnInteract()
{
    if (bIsTransitioning)
    {
        return;
    }

    if (OverlappingPlayer)
    {
        if (bLevelLoaded)
        {
            // Already loaded — teleport to level
            TeleportPlayerToLevel();
        }
        else
        {
            // Stream in the target level
            StreamInTargetLevel();
        }
    }
}

void ANLTBuildingPortalActor::StreamInTargetLevel()
{
    if (bLevelLoaded || bIsTransitioning)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    if (TargetLevelName.IsNone())
    {
        return;
    }

    bIsTransitioning = true;

    FString LevelPath = FString::Printf(TEXT("/Game/Scenarios/Levels/%s"), *TargetLevelName.ToString());

    // Save player position for return
    if (OverlappingPlayer)
    {
        SavedPlayerPosition = OverlappingPlayer->GetActorLocation();
        SavedPlayerRotation = OverlappingPlayer->GetActorRotation();
    }

    // Async load the target level
    FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
    StreamingHandle = StreamableManager.RequestAsyncLoad(
        FSoftObjectPath(LevelPath),
        FStreamableDelegate::CreateUObject(this, &ANLTBuildingPortalActor::OnLevelLoadComplete),
        FStreamableManager::AsyncLoadHighPriority
    );

    if (!StreamingHandle.IsValid())
    {
        UE_LOG(LogNLTBuildingPortal, Warning, TEXT("Portal '%s': Failed to start async load for '%s'"),
            *GetName(), *TargetLevelName.ToString());
        bIsTransitioning = false;
    }
    else
    {
        UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': Streaming in level '%s'"),
            *GetName(), *TargetLevelName.ToString());
    }
}

void ANLTBuildingPortalActor::OnLevelLoadComplete()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        bIsTransitioning = false;
        return;
    }

    FString LevelPath = FString::Printf(TEXT("/Game/Scenarios/Levels/%s"), *TargetLevelName.ToString());

    // Load the level via ULevelStreamingDynamic
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
        bLevelLoaded = true;
        StreamingLevel->SetShouldBeVisible(true);
        StreamingLevel->SetShouldBeLoaded(true);

        UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': Level '%s' loaded successfully"),
            *GetName(), *TargetLevelName.ToString());

        // Teleport the player to the level
        if (OverlappingPlayer)
        {
            TeleportPlayerToLevel();
        }
    }
    else
    {
        UE_LOG(LogNLTBuildingPortal, Warning, TEXT("Portal '%s': Failed to load level '%s'"),
            *GetName(), *TargetLevelName.ToString());
    }

    bIsTransitioning = false;

    // Release the streaming handle
    if (StreamingHandle)
    {
        StreamingHandle.Reset();
        StreamingHandle = nullptr;
    }
}

void ANLTBuildingPortalActor::TeleportPlayerToLevel()
{
    if (!OverlappingPlayer)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // Find the teleport actor in the loaded level
    // Convention: a TargetPoint named "PortalEntrance" exists in the target level
    AActor* TeleportTarget = nullptr;
    for (TActorIterator<AActor> It(World); It; ++It)
    {
        if (It->GetName().Contains(TEXT("PortalEntrance")) ||
            It->GetName().Contains(TEXT("SpawnPoint")) ||
            It->GetName().Contains(TEXT("TeleportTarget")))
        {
            TeleportTarget = *It;
            break;
        }
    }

    if (TeleportTarget)
    {
        // Teleport to the target actor's location
        FVector TargetLocation = TeleportTarget->GetActorLocation();
        FRotator TargetRotation = TeleportTarget->GetActorRotation();

        OverlappingPlayer->TeleportTo(TargetLocation, TargetRotation, false, true);

        UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': Teleported pawn to '%s' at (%.0f, %.0f, %.0f)"),
            *GetName(), *TeleportTarget->GetName(),
            TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
    }
    else
    {
        // Fallback: teleport in front of the portal building with an offset
        FVector TeleportOffset(0.0f, 0.0f, 100.0f);
        FVector TargetLocation = OverlappingPlayer->GetActorLocation() + TeleportOffset;

        OverlappingPlayer->TeleportTo(TargetLocation, OverlappingPlayer->GetActorRotation(), false, true);

        UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': No teleport target found — teleported with offset"),
            *GetName());
    }
}

void ANLTBuildingPortalActor::StreamOutTargetLevel()
{
    if (!bLevelLoaded)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // Find and unload the streaming level
    for (ULevelStreaming* StreamingLevel : World->GetStreamingLevels())
    {
        if (StreamingLevel && StreamingLevel->GetWorldAssetPackageName().Contains(TargetLevelName.ToString()))
        {
            StreamingLevel->SetShouldBeLoaded(false);
            StreamingLevel->SetShouldBeVisible(false);
            break;
        }
    }

    bLevelLoaded = false;

    UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': Level '%s' streamed out"),
        *GetName(), *TargetLevelName.ToString());
}

void ANLTBuildingPortalActor::ReturnPlayerToOpenWorld()
{
    if (!OverlappingPlayer)
    {
        return;
    }

    // Teleport back to saved position
    OverlappingPlayer->TeleportTo(SavedPlayerPosition, SavedPlayerRotation, false, true);

    UE_LOG(LogNLTBuildingPortal, Log, TEXT("Portal '%s': Returned pawn to open world at (%.0f, %.0f, %.0f)"),
        *GetName(), SavedPlayerPosition.X, SavedPlayerPosition.Y, SavedPlayerPosition.Z);

    // Stream out the level
    StreamOutTargetLevel();
}
