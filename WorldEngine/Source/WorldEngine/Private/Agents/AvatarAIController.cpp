// AvatarAIController.cpp
#include "Agents/AvatarAIController.h"
#include "NavigationSystem.h"

AAvatarAIController::AAvatarAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAvatarAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (InPawn)
    {
        HomeLocation = InPawn->GetActorLocation();
    }
}

void AAvatarAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!bIsWaiting)
    {
        Wander();
    }
}

void AAvatarAIController::Wander()
{
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

    bIsWaiting = true;
    float WaitTime = FMath::FRandRange(WaitTimeMin, WaitTimeMax);
    GetWorldTimerManager().SetTimer(WaitTimer, this, &AAvatarAIController::Wait, WaitTime, false);
}

void AAvatarAIController::Wait()
{
    bIsWaiting = false;
    GetWorldTimerManager().ClearTimer(WaitTimer);
}
