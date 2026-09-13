// NLTCharacterAnimationComponent.h
//
// Animation state machine: manages transitions between emotional animation
// states, plays montages on SkeletalMeshComponents, and falls back to
// procedural static-mesh posing when no SkeletalMesh is available.
//
// This is the conductor that keeps the character's movement, posture, and
// expression in sync with the emotion state machine (NLTEmotionStateComponent).

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/NLTFusionCore.h"
#include "NLTCharacterAnimationComponent.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UAnimMontage;
class UNLTEmotionStateComponent;

/**
 * Manages the character's animation state machine.
 *
 * When a SkeletalMeshComponent is present (e.g. MetaHuman, Quaternius rig),
 * this component drives animation montages and lets the AnimInstance handle
 * procedural posing. When only a StaticMeshComponent (SimBody fallback) is
 * available, it applies rotation/position offsets to approximate the posture.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WORLDENGINE_API UNLTCharacterAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNLTCharacterAnimationComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/** Bind to a SkeletalMeshComponent (rigged character). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Animation")
	void BindSkeletalMesh(USkeletalMeshComponent* InSkelMesh);

	/** Bind to a StaticMeshComponent (procedural fallback — SimBody). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Animation")
	void BindStaticMesh(UStaticMeshComponent* InStaticMesh);

	/** Register an emotion state component so we can read emotional state. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Animation")
	void SetEmotionComponent(UNLTEmotionStateComponent* InEmotion);

	/// --- Animation montages (configurable per emotion state) ---
	/// These are played when a SkeletalMeshComponent with an AnimInstance
	/// is available. In the editor, assign montages created from your
	/// glTF / Mixamo / MetaHuman animation library.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_Walk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_Work;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_Struggle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_Hyperfocus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_CoachGesture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_Celebrate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_IdleTired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_Drift;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Montages")
	TObjectPtr<UAnimMontage> Montage_Nod;

	/// --- Current state (readable by other components) ---

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Animation")
	ENLTAnimationState CurrentState = ENLTAnimationState::Idle;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Animation")
	float StateTime = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Animation")
	bool bIsMoving = false;

	/// --- Tuning ---

	/** Time (seconds) for crossfading between animation states. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Tuning")
	float BlendTime = 0.3f;

	/** Maximum procedural posture offset (degrees) for static-mesh fallback. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Tuning")
	float MaxProceduralTilt = 15.0f;

	/** How quickly the static mesh catches up to the target posture (spring). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Tuning")
	float ProceduralSpringSpeed = 8.0f;

	/** Whether to log animation state transitions (dev-only). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Animation|Tuning")
	bool bDebugLogTransitions = false;

protected:
	/** Look up the montage for an animation state. */
	UAnimMontage* GetMontageForState(ENLTAnimationState State) const;

	/** Apply procedural posture to the bound static mesh (fallback). */
	void ApplyProceduralPosture(float DeltaTime);

	/** Play the montage for the current state on the SkeletalMesh. */
	void PlayMontageForState(ENLTAnimationState State);

	/** Crossfade to a new animation state. */
	void TransitionTo(ENLTAnimationState NewState);

private:
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkelMesh;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY()
	TObjectPtr<UNLTEmotionStateComponent> EmotionComponent;

	/** Interpolated posture for the static-mesh fallback. */
	FVector TargetPosture;
	FVector CurrentPosture;

	/** The montage currently playing. */
	UPROPERTY()
	TObjectPtr<UAnimMontage> CurrentMontage;

	/** Time remaining in the current transition (0 = no transition in progress). */
	float TransitionTimer = 0.0f;

	/** Whether the last animation play was for the "moving" state. */
	bool bWasMoving = false;
};
