// SimBodyPawn.cpp
#include "Agents/SimBodyPawn.h"
#include "Agents/AvatarAIController.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

ASimBodyPawn::ASimBodyPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Driven by an AI controller so an external LLM agent can issue goals.
    AIControllerClass = AAvatarAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // Configure character movement (mirrors AAvatarCharacter).
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = 300.0f;
        MoveComp->bOrientRotationToMovement = true;
        MoveComp->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
    }

    // Body representation attached to the capsule. Collision stays on the
    // capsule; the mesh is visual only and must not block navigation.
    BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(GetCapsuleComponent());
    BodyMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BodyMesh->SetCanEverAffectNavigation(false);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshAsset(
        TEXT("/Game/Kits/SimBody/SM_SimBody_Base.SM_SimBody_Base"));
    if (BodyMeshAsset.Succeeded())
    {
        BodyMesh->SetStaticMesh(BodyMeshAsset.Object);
    }
}

void ASimBodyPawn::MoveToWorldLocation(const FVector& Goal, float AcceptanceRadius)
{
    if (AAIController* AIControllerRef = Cast<AAIController>(GetController()))
    {
        AIControllerRef->MoveToLocation(Goal, AcceptanceRadius);
    }
}

void ASimBodyPawn::StopMoving()
{
    if (AAIController* AIControllerRef = Cast<AAIController>(GetController()))
    {
        AIControllerRef->StopMovement();
    }
}