// NLTAvatarAnimInstance.h
//
// Animation instance that bridges emotion state → procedural bone posing.
//
// When a rigged SkeletalMesh is available (MetaHuman, Quaternius CC0, or
// Mixamo retargeted rig), this class drives the skeleton procedurally
// from the emotion state machine. When paired with an Animation Blueprint
// (created in the editor), it also exposes BlueprintImplementableEvent
// hooks so asset-based montages can be layered on top.
//
// The goal: characters that broadcast internal state through posture,
// idle fidgets, and facial micro-expressions — the Sims "feel alive" lever.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Core/NLTFusionCore.h"
#include "NLTAvatarAnimInstance.generated.h"

class UNLTEmotionStateComponent;

UCLASS()
class WORLDENGINE_API UNLTAvatarAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/// --- Blueprint-readable state (set by NativeUpdateAnimation) ---

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim")
	ENLTEmotionState CurrentEmotion = ENLTEmotionState::Neutral;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim")
	ENLTAnimationState CurrentAnimationState = ENLTAnimationState::None;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim")
	FVector PostureInfluence = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim")
	float EmotionalIntensity = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim")
	bool bIsMoving = false;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim")
	bool bIsAide = false;

	/// --- Facial blend-shape / curve targets (0–1) ---

	/**  0 = neutral,  1 = smile, -1 = frown */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Face")
	float MouthSmile = 0.0f;

	/**  0 = open, 1 = closed (blink) */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Face")
	float EyeBlink = 0.0f;

	/**  0 = neutral,  1 = fully furrowed */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Face")
	float BrowFurrow = 0.0f;

	/**  0 = center,  1 = wide-eyed (surprise/stress) */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Face")
	float EyeWide = 0.0f;

	/// --- Blueprint-readable procedural pose parameters ---
	/** These are computed per-frame from emotion state and exposed to
	    Animation Blueprints. An ABP can read these to drive bone
	    transforms, or the NLTCharacterAnimationComponent can apply them
	    as a static-mesh fallback. */

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Procedural")
	FRotator ProceduralSpine01Rotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Procedural")
	FRotator ProceduralSpine02Rotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Procedural")
	FRotator ProceduralHeadRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Procedural")
	FRotator ProceduralLeftArmRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Procedural")
	FRotator ProceduralRightArmRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Procedural")
	FRotator ProceduralLeftLegRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Anim|Procedural")
	FRotator ProceduralRightLegRotation = FRotator::ZeroRotator;

	/// --- Blueprint hooks (called when emotion/animation state changes) ---

	/** Called when the animation state changes. An Animation Blueprint can
	    play the appropriate montage or blend-space here. */
	UFUNCTION(BlueprintImplementableEvent, Category = "NLT|Anim")
	void OnAnimationStateChanged(ENLTAnimationState NewState, ENLTAnimationState PreviousState);

	/** Called when the facial expression changes. An Animation Blueprint can
	    drive blend-shape targets here. */
	UFUNCTION(BlueprintImplementableEvent, Category = "NLT|Anim|Face")
	void OnFacialExpressionChanged(ENLTFacialExpression NewExpression, ENLTFacialExpression PreviousExpression);

	/** Called when a thought bubble should appear above the head. */
	UFUNCTION(BlueprintImplementableEvent, Category = "NLT|Anim")
	void OnThoughtBubbleRequested(const FString& BubbleText);

protected:
	/** Compute procedural pose parameters from emotion + posture.
	    Called every frame in NativeUpdateAnimation. */
	void ApplyProceduralPose(float DeltaSeconds);

	/** Compute facial blend-shape values from the current emotion. */
	void UpdateFacialCurves(float DeltaTime);

	/** Cached reference to the emotion component */
	UPROPERTY()
	TObjectPtr<UNLTEmotionStateComponent> EmotionState;

	/** Procedural animation time accumulator */
	float ProceduralTime = 0.0f;

	/** Current facial expression (for change detection) */
	ENLTFacialExpression CachedExpression = ENLTFacialExpression::Neutral;

	/** Cached animation state (for change detection) */
	ENLTAnimationState CachedAnimState = ENLTAnimationState::None;

	/** Cached thought bubble text (for change detection) */
	FString CachedThoughtBubble;
};
