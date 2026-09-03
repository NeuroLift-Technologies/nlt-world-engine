// AvatarAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AvatarAIController.generated.h"

UCLASS()
class WORLDENGINE_API AAvatarAIController : public AAIController
{
    GENERATED_BODY()

public:
    AAvatarAIController();

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WanderRadius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WaitTimeMin = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WaitTimeMax = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AcceptanceRadius = 50.0f;

private:
    void Wander();
    void Wait();

    FVector HomeLocation;
    FTimerHandle WaitTimer;
    bool bIsWaiting = false;
};
