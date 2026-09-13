// NLTEmotionStateComponent.h
//
// The emotion state machine that translates cognitive dimensions
// (Focus, Stress, CognitiveLoad, Burnout) into expressive emotional states.
//
// This is the bridge between the sim layer (LTCognitiveStateComponent) and
// the animation / visual layer (NLTCharacterAnimationComponent,
// UNLTAvatarAnimInstance, NLTAvatarVisualComponent).
//
// A Sims-like character's expressiveness lives in the animation state
// machine, not the polygon count. This component owns THAT state machine.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/NLTFusionCore.h"
#include "NLTEmotionStateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEmotionStateChanged, ENLTEmotionState, NewEmotion, ENLTEmotionState, PrevEmotion);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnimationStateChanged, ENLTAnimationState, NewAnim, ENLTAnimationState, PrevAnim);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThoughtBubbleRequested, const FString&, BubbleText);

/**
 * Reads cognitive values from ULTCognitiveStateComponent each tick and
 * derives a discrete emotional state with smooth transitions.
 *
 * The derived state drives animation, facial expression, posture, and
 * thought-bubble selection — mirroring how The Sims characters broadcast
 * their internal state through body language rather than polygon count.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WORLDENGINE_API UNLTEmotionStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNLTEmotionStateComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/** Read cognitive values from the owning character's CognitiveState component
	    and recompute the emotional state. Called internally each tick, but also
	    callable manually when cognitive values change outside of tick. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Emotion")
	void UpdateFromCognitiveState(float DeltaTime);

	/** Force an immediate emotional state (bypasses the sim-driven computation).
	    Useful for one-shot events like celebrations. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Emotion")
	void SetOverrideEmotion(ENLTEmotionState OverrideEmotion, float Duration);

	/** Trigger a temporary celebration state that decays back to the sim-driven emotion. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Emotion")
	void TriggerCelebration(float Duration = 3.0f);

	/// --- Blueprint-readable outputs ---

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Emotion")
	ENLTEmotionState CurrentEmotion = ENLTEmotionState::Neutral;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Emotion")
	ENLTEmotionState PreviousEmotion = ENLTEmotionState::Neutral;

	/** The animation state derived from the current emotion + movement context. */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Emotion")
	ENLTAnimationState CurrentAnimationState = ENLTAnimationState::Idle;

	/** How intense the current emotion is (0–1). Drives blend weights on
	    procedural pose adjustments and particle spawn rates. */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Emotion")
	float EmotionalIntensity = 0.0f;

	/** A Simlish-style thought-bubble emoji for the current emotion. */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Emotion")
	FString CurrentThoughtBubble;

	/** Current facial expression target for blend-shape / curve drivers. */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Emotion")
	ENLTFacialExpression CurrentExpression = ENLTFacialExpression::Neutral;

	/** Posture influence vector: (LeanForward, Slump, BounceMultiplier).
	    Consumed by procedural animation and AnimInstance. */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Emotion")
	FVector PostureInfluence = FVector::ZeroVector;

	// --- Events ---

	UPROPERTY(BlueprintAssignable, Category = "NLT|Emotion")
	FOnEmotionStateChanged OnEmotionStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "NLT|Emotion")
	FOnAnimationStateChanged OnAnimationStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "NLT|Emotion")
	FOnThoughtBubbleRequested OnThoughtBubbleRequested;

	/// --- Tuning parameters (exposed to editor / Blueprint) ---

	/** How quickly the emotion blends to its target (units: 1/s). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion|Tuning")
	float EmotionTransitionSpeed = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion|Tuning")
	float ThoughtBubbleDuration = 4.0f;

	// Thresholds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion|Thresholds")
	float StressOverwhelmedThreshold = 0.70f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion|Thresholds")
	float CogLoadOverwhelmedThreshold = 0.85f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion|Thresholds")
	float StressStrugglingThreshold = 0.50f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion|Thresholds")
	float BurnoutFatiguedThreshold = 0.60f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion|Thresholds")
	float FocusDriftingThreshold = 0.30f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion|Thresholds")
	float FocusFocusedThreshold = 0.70f;

	/** Is this character an aide (vs. an avatar)? Affects the coaching animation mapping. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion")
	bool bIsAide = false;

	/** Whether the character is currently moving (drives walk vs. idle animation). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Emotion")
	bool bIsMoving = false;

	/** The cognitive state component to read from (set by owning character). */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Emotion")
	TObjectPtr<class ULTCognitiveStateComponent> CognitiveState;

protected:
	/** Compute the target emotion from raw cognitive values + intent. */
	ENLTEmotionState ComputeTargetEmotion(float Focus, float Stress, float CognitiveLoad,
	                                      float Burnout, ENLTAgentIntent Intent) const;

	/** Map an emotion + movement context to an animation state. */
	ENLTAnimationState MapEmotionToAnimation(ENLTEmotionState Emotion) const;

	/** Map an emotion to a facial expression. */
	ENLTFacialExpression MapEmotionToExpression(ENLTEmotionState Emotion) const;

	/** Map an emotion to a thought-bubble string. */
	FString MapEmotionToThoughtBubble(ENLTEmotionState Emotion) const;

	/** Map an emotion to posture influence (LeanForward, Slump, Bounce). */
	FVector MapEmotionToPosture(ENLTEmotionState Emotion) const;

private:
	ENLTEmotionState TargetEmotion = ENLTEmotionState::Neutral;
	ENLTEmotionState OverrideEmotion = ENLTEmotionState::Neutral;
	float OverrideTimer = 0.0f;
	bool bHasOverride = false;
};
