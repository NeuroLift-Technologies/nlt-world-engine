// NLTDoorActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NLTDoorActor.generated.h"

/**
 * Interactive door that allows the player to travel to another level.
 * Place one in each level. When the player presses Interact near it,
 * a level picker widget appears.
 */
UCLASS()
class WORLDENGINE_API ANLTDoorActor : public AActor
{
	GENERATED_BODY()

public:
	ANLTDoorActor();

	virtual void BeginPlay() override;

	/** The level this door leads to (soft reference, loaded on demand). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Door")
	FName TargetLevelId = TEXT("Workplace_Level");

	/** Display name shown in the level picker. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Door")
	FText DisplayName = NSLOCTEXT("NLT", "DoorWorkplace", "Workplace");

	/** Prompt shown when player is near the door. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Door")
	FText InteractPrompt = NSLOCTEXT("NLT", "DoorPrompt", "Press E to travel");

protected:
	/** Visual mesh for the door. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Door")
	UStaticMeshComponent* DoorMesh;

	/** Trigger volume — player must be inside to interact. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Door")
	UBoxComponent* InteractionVolume;

	/** Currently overlapping player (if any). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Door")
	AActor* OverlappingPlayer;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	/** Returns true if a player is currently in range. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Door")
	bool IsPlayerInRange() const { return OverlappingPlayer != nullptr; }

	/** Get the target level ID. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Door")
	FName GetTargetLevelId() const { return TargetLevelId; }

	/** Get the display name. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Door")
	FText GetDisplayName() const { return DisplayName; }

	/** Get the interact prompt. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Door")
	FText GetInteractPrompt() const { return InteractPrompt; }
};
