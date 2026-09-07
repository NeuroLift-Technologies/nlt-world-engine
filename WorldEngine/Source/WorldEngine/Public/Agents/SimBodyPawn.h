// SimBodyPawn.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimBodyPawn.generated.h"

/**
 * Embodied pawn backed by the Kits/SimBody static mesh.
 *
 * Serves as a navigable body for an LLM-driven agent (e.g. "Hermes"): it is a
 * proper pawn with a CharacterMovementComponent and is possessed by an
 * AAvatarAIController, so an external agent runtime can issue MoveTo goals the
 * same way the web server already drives AAvatarCharacter.
 */
UCLASS()
class WORLDENGINE_API ASimBodyPawn : public ACharacter
{
    GENERATED_BODY()

public:
    ASimBodyPawn();

    // ============== LLM Command Hooks ==============

    // Moves this body toward a world-space goal via the possessed AI controller.
    UFUNCTION(BlueprintCallable, Category = "NLT|SimBody")
    void MoveToWorldLocation(const FVector& Goal, float AcceptanceRadius = 50.0f);

    // Halts any navigation the controller is currently executing.
    UFUNCTION(BlueprintCallable, Category = "NLT|SimBody")
    void StopMoving();

    // The SimBody mesh representation, attached to the capsule.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|SimBody")
    class UStaticMeshComponent* BodyMesh;
};