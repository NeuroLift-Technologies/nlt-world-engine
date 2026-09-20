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

    // Create the building mesh (visual exterior)
    BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
    RootComponent = BuildingMesh;

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
    // Could swap static mesh based on building type
    // For now, scale varies by type
    switch (BuildingType)
    {
    case ENLTBuildingType::Office:
        BuildingMesh->SetRelativeScale3D(FVector(4.0f, 4.0f, 6.0f));
        break;
    case ENLTBuildingType::Apartment:
        BuildingMesh->SetRelativeScale3D(FVector(5.0f, 3.0f, 8.0f));
        break;
    case ENLTBuildingType::Shop:
        BuildingMesh->SetRelativeScale3D(FVector(6.0f, 4.0f, 3.0f));
        break;
    case ENLTBuildingType::School:
        BuildingMesh->SetRelativeScale3D(FVector(7.0f, 5.0f, 4.0f));
        break;
    case ENLTBuildingType::Hut:
        BuildingMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 2.5f));
        break;
    default:
        BuildingMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 4.0f));
        break;
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
