// AvatarCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "AvatarCharacter.generated.h"

UCLASS()
class WORLDENGINE_API AAvatarCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AAvatarCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WanderRadius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WaitTimeMin = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WaitTimeMax = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float InteractionRange = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AAIController> MyAIControllerClass;

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void Wander();
    void Wait();
    void Interact();

    FVector HomeLocation;
    FTimerHandle WaitTimer;
    bool bIsWaiting = false;
    int32 InteractCooldown = 0;
};
