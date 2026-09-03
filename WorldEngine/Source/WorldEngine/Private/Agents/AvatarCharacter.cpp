// AvatarCharacter.cpp
#include "Agents/AvatarCharacter.h"
#include "Agents/AvatarAIController.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAvatarCharacter::AAvatarCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set default AI controller
    AIControllerClass = AAvatarAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // Configure character movement
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = 300.0f;
        MoveComp->bOrientRotationToMovement = true;
        MoveComp->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
    }
}

void AAvatarCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AAvatarCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // AI wandering is handled by AAvatarAIController — this character is a pure physical substrate
}

void AAvatarCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // No player input — AI controlled
}
