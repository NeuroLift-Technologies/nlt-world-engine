// AvatarCharacter.cpp
#include "Agents/AvatarCharacter.h"
#include "Agents/AvatarAIController.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AAvatarCharacter::AAvatarCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set default AI controller
    MyAIControllerClass = AAvatarAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // Configure character movement
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = 300.0f;
        MoveComp->bOrientRotationToMovement = true;
        MoveComp->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
    }

    // Scale to match SimBody size (~1.795m tall)
    SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void AAvatarCharacter::BeginPlay()
{
    Super::BeginPlay();
    HomeLocation = GetActorLocation();
}

void AAvatarCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Handle interaction cooldown
    if (InteractCooldown > 0)
    {
        InteractCooldown--;
    }

    // AI-driven wandering when controlled by AAvatarAIController
    AAIController* MyController = Cast<AAIController>(GetController());
    if (MyController && !bIsWaiting)
    {
        Wander();
    }
}

void AAvatarCharacter::Wander()
{
    FVector TargetLocation;
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    
    if (NavSys)
    {
        FNavLocation NavLocation;
        if (NavSys->GetRandomPointInNavigableRadius(HomeLocation, WanderRadius, NavLocation))
        {
            TargetLocation = NavLocation.Location;
        }
        else
        {
            TargetLocation = HomeLocation + FVector(
                FMath::FRandRange(-WanderRadius, WanderRadius),
                FMath::FRandRange(-WanderRadius, WanderRadius),
                0.0f
            );
        }
    }
    else
    {
        TargetLocation = HomeLocation + FVector(
            FMath::FRandRange(-WanderRadius, WanderRadius),
            FMath::FRandRange(-WanderRadius, WanderRadius),
            0.0f
        );
    }

    // Move using AI controller
    if (AAIController* AIController = Cast<AAIController>(GetController()))
    {
        AIController->MoveToLocation(TargetLocation, 50.0f, true, true, true, true);
    }

    bIsWaiting = true;
    float WaitTime = FMath::FRandRange(WaitTimeMin, WaitTimeMax);
    GetWorldTimerManager().SetTimer(WaitTimer, this, &AAvatarCharacter::Wait, WaitTime, false);
}

void AAvatarCharacter::Wait()
{
    bIsWaiting = false;
    GetWorldTimerManager().ClearTimer(WaitTimer);
}

void AAvatarCharacter::Interact()
{
    if (InteractCooldown > 0) return;

    // Simple interaction: print nearby actors
    TArray<FHitResult> HitResults;
    FVector Start = GetActorLocation();
    FVector End = Start + FVector(0.0f, 0.0f, 100.0f);
    
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    
    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults, Start, End, FQuat::Identity,
        ECC_WorldDynamic, FCollisionShape::MakeSphere(InteractionRange), QueryParams);

    if (bHit)
    {
        for (const FHitResult& Hit : HitResults)
        {
            if (AActor* HitActor = Hit.GetActor())
            {
                UE_LOG(LogTemp, Log, TEXT("%s interacted with: %s"), 
                    *GetName(), *HitActor->GetName());
            }
        }
    }

    InteractCooldown = 60; // 1 second cooldown at 60fps
}

void AAvatarCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // No player input — AI controlled
}
