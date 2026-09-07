// NLTDoorActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "NLTDoorActor.generated.h"

/**
 * Interactive door that allows the player to travel to another level.
 * Place one in each level. Walking through the door travels the player.
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
	FText InteractPrompt = NSLOCTEXT("NLT", "DoorPrompt", "Press F to travel");

protected:
	/** Visual mesh for the door. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Door")
	UStaticMeshComponent* DoorMesh;

	/** Trigger volume — player must be inside to interact. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Door")
	UBoxComponent* InteractionVolume;

	/** World-space text label above the door showing the destination level. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Door")
	UTextRenderComponent* DoorLabel;

	/**
	 * Mirrored copy of DoorLabel facing the opposite way, so the destination
	 * stays readable whether the player approaches from the front or back.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NLT|Door")
	UTextRenderComponent* DoorLabelBack;

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

	/** Travel to the target level when the player walks through the door. */
	void TryTravel();

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

	/**
	 * Orients the label so its readable face points toward FaceDirection
	 * (world space), keeping the text upright. FaceDirection should point
	 * from the door toward the area the player approaches from.
	 */
	UFUNCTION(BlueprintCallable, Category = "NLT|Door")
	void SetLabelFacing(const FVector& FaceDirection);

	/** Refresh the label text from the current DisplayName. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Door")
	void UpdateLabelText();
};
