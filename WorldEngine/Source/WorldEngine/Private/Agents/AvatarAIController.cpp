// AvatarAIController.cpp
#include "Agents/AvatarAIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"

AAvatarAIController::AAvatarAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    WanderRadius = 1000.0f;
    WaitTimeMin = 2.0f;
    WaitTimeMax = 5.0f;
    AcceptanceRadius = 50.0f;
    bIsWaiting = false;
    bLearningAgentsActive = false;
}

void AAvatarAIController::SetLearningAgentsActive(bool bActive)
{
    bLearningAgentsActive = bActive;
    if (bActive)
    {
        // Stop wandering when LA takes control
        StopMovement();
        GetWorldTimerManager().ClearTimer(WaitTimer);
    }
    else
    {
        // Resume wandering when LA relinquishes control
        Wander();
    }
}

void AAvatarAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (InPawn)
    {
        HomeLocation = InPawn->GetActorLocation();
        // Only start wandering if LA is not active
        if (!bLearningAgentsActive)
        {
            Wander();
        }
    }
}

void AAvatarAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAvatarAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    // Only continue wandering if LA is not active
    if (!bLearningAgentsActive)
    {
        bIsWaiting = true;
        float WaitTime = FMath::FRandRange(WaitTimeMin, WaitTimeMax);
        GetWorldTimerManager().SetTimer(WaitTimer, this, &AAvatarAIController::Wait, WaitTime, false);
    }
}

void AAvatarAIController::Wander()
{
    // Don't wander if LA is controlling
    if (bLearningAgentsActive) return;

    APawn* MyPawn = GetPawn();
    if (!MyPawn) return;

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

    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, true, true);
}

void AAvatarAIController::Wait()
{
    bIsWaiting = false;
    GetWorldTimerManager().ClearTimer(WaitTimer);
    // Pick next destination
    Wander();
}
