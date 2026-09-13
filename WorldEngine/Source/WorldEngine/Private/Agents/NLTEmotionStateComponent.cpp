// NLTEmotionStateComponent.cpp
//
// Emotion state machine: cognitive dimensions → expressive emotional states.
//
// Design rationale (from PLAN.md Phase 2.2/2.3):
//   Sims characters feel alive because their bodies broadcast internal state
//   through posture, fidget, and facial expression — not because of polygon
//   count. The emotion → animation mapping below is the core of that
//   expressiveness. Each cognitive dimension (Focus, Stress, CognitiveLoad,
//   Burnout) contributes to an aggregate emotional state; transitions are
//   smoothed so the character never "snaps" between extremes.

#include "Agents/NLTEmotionStateComponent.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogNLTEmotion, Log, All);

UNLTEmotionStateComponent::UNLTEmotionStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNLTEmotionStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// Cache the cognitive state component on the owning character.
	if (AActor* Owner = GetOwner())
	{
		CognitiveState = Owner->FindComponentByClass<ULTCognitiveStateComponent>();
	}
}

void UNLTEmotionStateComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateFromCognitiveState(DeltaTime);
}

void UNLTEmotionStateComponent::UpdateFromCognitiveState(float DeltaTime)
{
	// --- Gather cognitive inputs ---
	float Focus = 0.5f;
	float Stress = 0.0f;
	float CognitiveLoad = 0.0f;
	float Burnout = 0.0f;
	ENLTAgentIntent Intent = ENLTAgentIntent::Idle;

	if (CognitiveState)
	{
		Focus = CognitiveState->Focus;
		Stress = CognitiveState->Stress;
		CognitiveLoad = CognitiveState->CognitiveLoad;
		Burnout = CognitiveState->Burnout;
		// Derive intent from cognitive context: high cognitive load implies active work
		Intent = (CognitiveLoad > 0.3f) ? ENLTAgentIntent::Work : ENLTAgentIntent::Idle;
	}

	// --- Compute target emotion ---
	ENLTEmotionState NewTarget;

	if (bHasOverride)
	{
		OverrideTimer -= DeltaTime;
		if (OverrideTimer <= 0.0f)
		{
			bHasOverride = false;
		}
		NewTarget = OverrideEmotion;
	}
	else
	{
		NewTarget = ComputeTargetEmotion(Focus, Stress, CognitiveLoad, Burnout, Intent);
	}

	// --- Smooth transition toward target ---
	TargetEmotion = NewTarget;

	// Intensity reflects how "active" the current emotion is (0–1).
	// We interpolate this for visual effect, but commit the discrete
	// emotion state immediately.
	float TargetIntensity = 0.5f;
	switch (TargetEmotion)
	{
	case ENLTEmotionState::Neutral:     TargetIntensity = 0.1f; break;
	case ENLTEmotionState::Focused:     TargetIntensity = 0.7f; break;
	case ENLTEmotionState::Working:     TargetIntensity = 0.5f; break;
	case ENLTEmotionState::Struggling:  TargetIntensity = 0.8f; break;
	case ENLTEmotionState::Overwhelmed: TargetIntensity = 1.0f; break;
	case ENLTEmotionState::Drifting:    TargetIntensity = 0.3f; break;
	case ENLTEmotionState::Hyperfocus:  TargetIntensity = 0.9f; break;
	case ENLTEmotionState::Coached:     TargetIntensity = 0.6f; break;
	case ENLTEmotionState::Fatigued:    TargetIntensity = 0.4f; break;
	case ENLTEmotionState::Celebrating: TargetIntensity = 1.0f; break;
	default:                            TargetIntensity = 0.5f; break;
	}
	EmotionalIntensity = FMath::FInterpTo(EmotionalIntensity, TargetIntensity, DeltaTime, EmotionTransitionSpeed);

	//--- Commit emotion state change ---
	if (CurrentEmotion != TargetEmotion)
	{
		ENLTEmotionState Prev = CurrentEmotion;
		CurrentEmotion = TargetEmotion;
		PreviousEmotion = Prev;

		// Update derived properties
		ENLTFacialExpression NewExpr = MapEmotionToExpression(CurrentEmotion);
		FString NewBubble = MapEmotionToThoughtBubble(CurrentEmotion);
		FVector NewPosture = MapEmotionToPosture(CurrentEmotion);

		CurrentExpression = NewExpr;
		PostureInfluence = NewPosture;

		// Fire thought-bubble event (bubbles only fire on emotion change)
		if (!NewBubble.IsEmpty())
		{
			CurrentThoughtBubble = NewBubble;
			OnThoughtBubbleRequested.Broadcast(NewBubble);
		}
		else
		{
			CurrentThoughtBubble.Empty();
		}

		OnEmotionStateChanged.Broadcast(CurrentEmotion, Prev);

		UE_LOG(LogNLTEmotion, Verbose, TEXT("Emotion: %d -> %d (Focus=%.2f Stress=%.2f CogLoad=%.2f)"),
			static_cast<int32>(Prev), static_cast<int32>(CurrentEmotion),
			Focus, Stress, CognitiveLoad);
	}

	//~ FIX (PR #43 review): recompute the animation state EVERY tick so
	//~ movement-only transitions (idle<->walk) apply immediately instead of
	//~ lagging until the next emotion change.
	const ENLTAnimationState TickAnim = MapEmotionToAnimation(CurrentEmotion);
	if (TickAnim != CurrentAnimationState)
	{
		const ENLTAnimationState PrevAnim = CurrentAnimationState;
		CurrentAnimationState = TickAnim;
		OnAnimationStateChanged.Broadcast(TickAnim, PrevAnim);
	}
}

ENLTEmotionState UNLTEmotionStateComponent::ComputeTargetEmotion(
	float Focus, float Stress, float CognitiveLoad, float Burnout,
	ENLTAgentIntent Intent) const
{
	// Priority-ordered emotion computation.
	// The most salient cognitive dimension wins — this mirrors how Sims
	// moodlets stack priority.

	// Explicit intent overrides (set by the decision engine)
	switch (Intent)
	{
	case ENLTAgentIntent::Coached:
		return ENLTEmotionState::Coached;
	case ENLTAgentIntent::Overwhelmed:
		return ENLTEmotionState::Overwhelmed;
	case ENLTAgentIntent::Drifting:
		return ENLTEmotionState::Drifting;
	case ENLTAgentIntent::Hyperfocus:
		return ENLTEmotionState::Hyperfocus;
	case ENLTAgentIntent::Work:
	case ENLTAgentIntent::Study:
		// Fall through to value-based logic — working intent but the emotion
		// depends on whether the sim is actually managing it.
		break;
	default:
		break;
	}

	// Stress-driven emotions (highest priority)
	if (Stress > StressOverwhelmedThreshold || CognitiveLoad > CogLoadOverwhelmedThreshold)
	{
		return ENLTEmotionState::Overwhelmed;
	}
	if (Stress > StressStrugglingThreshold)
	{
		return ENLTEmotionState::Struggling;
	}

	// Burnout → fatigue (overrides other low-priority states)
	if (Burnout > BurnoutFatiguedThreshold)
	{
		return ENLTEmotionState::Fatigued;
	}

	// Hyperfocus: high cognitive load + high focus
	if (CognitiveLoad > 0.7f && Focus > 0.7f && Intent == ENLTAgentIntent::Work)
	{
		return ENLTEmotionState::Hyperfocus;
	}

	// Drifting: low focus, no active task
	if (Focus < FocusDriftingThreshold && Intent != ENLTAgentIntent::Work)
	{
		return ENLTEmotionState::Drifting;
	}

	// Focused: high focus with moderate cognitive load
	if (Focus > FocusFocusedThreshold && CognitiveLoad > 0.2f)
	{
		return ENLTEmotionState::Focused;
	}

	// Working: on a task, managing ok
	if (Intent == ENLTAgentIntent::Work || Intent == ENLTAgentIntent::Study)
	{
		return ENLTEmotionState::Working;
	}

	return ENLTEmotionState::Neutral;
}

ENLTAnimationState UNLTEmotionStateComponent::MapEmotionToAnimation(ENLTEmotionState Emotion) const
{
	if (bIsMoving)
	{
		return ENLTAnimationState::Walk;
	}

	switch (Emotion)
	{
	case ENLTEmotionState::Neutral:     return ENLTAnimationState::Idle;
	case ENLTEmotionState::Focused:     return ENLTAnimationState::Work;
	case ENLTEmotionState::Working:     return ENLTAnimationState::Work;
	case ENLTEmotionState::Struggling:  return ENLTAnimationState::Struggle;
	case ENLTEmotionState::Overwhelmed: return ENLTAnimationState::Struggle;
	case ENLTEmotionState::Drifting:    return ENLTAnimationState::Drift;
	case ENLTEmotionState::Hyperfocus:  return ENLTAnimationState::Hyperfocus;
	case ENLTEmotionState::Coached:
		return bIsAide ? ENLTAnimationState::CoachGesture : ENLTAnimationState::Nod;
	case ENLTEmotionState::Fatigued:    return ENLTAnimationState::IdleTired;
	case ENLTEmotionState::Celebrating: return ENLTAnimationState::Celebrate;
	default:                            return ENLTAnimationState::Idle;
	}
}

ENLTFacialExpression UNLTEmotionStateComponent::MapEmotionToExpression(ENLTEmotionState Emotion) const
{
	switch (Emotion)
	{
	case ENLTEmotionState::Neutral:     return ENLTFacialExpression::Neutral;
	case ENLTEmotionState::Focused:
	case ENLTEmotionState::Working:
	case ENLTEmotionState::Hyperfocus:  return ENLTFacialExpression::Focused;
	case ENLTEmotionState::Struggling:
	case ENLTEmotionState::Overwhelmed: return ENLTFacialExpression::Stressed;
	case ENLTEmotionState::Drifting:    return ENLTFacialExpression::Thinking;
	case ENLTEmotionState::Coached:     return ENLTFacialExpression::Happy;
	case ENLTEmotionState::Fatigued:    return ENLTFacialExpression::Tired;
	case ENLTEmotionState::Celebrating: return ENLTFacialExpression::Happy;
	default:                            return ENLTFacialExpression::Neutral;
	}
}

FString UNLTEmotionStateComponent::MapEmotionToThoughtBubble(ENLTEmotionState Emotion) const
{
	switch (Emotion)
	{
	case ENLTEmotionState::Focused:     return TEXT("💡");
	case ENLTEmotionState::Working:     return TEXT("💻");
	case ENLTEmotionState::Struggling:  return TEXT("😣");
	case ENLTEmotionState::Overwhelmed: return TEXT("❗");
	case ENLTEmotionState::Drifting:    return TEXT("😰");
	case ENLTEmotionState::Hyperfocus:  return TEXT("🎯");
	case ENLTEmotionState::Coached:     return TEXT("✦");
	case ENLTEmotionState::Fatigued:    return TEXT("😴");
	case ENLTEmotionState::Celebrating: return TEXT("🎉");
	default:                            return FString();
	}
}

FVector UNLTEmotionStateComponent::MapEmotionToPosture(ENLTEmotionState Emotion) const
{
	// Returns (LeanForward, Slump, BounceMultiplier)
	// LeanForward > 0 = leaning forward (engaged)
	// Slump > 0 = hunched/back leaning (disengaged/stressed)
	// BounceMultiplier modulates idle sway amplitude
	switch (Emotion)
	{
	case ENLTEmotionState::Neutral:     return FVector(0.0f,  0.0f,  1.0f);
	case ENLTEmotionState::Focused:     return FVector(0.15f, 0.0f,  0.7f);
	case ENLTEmotionState::Working:     return FVector(0.10f, 0.02f, 0.6f);
	case ENLTEmotionState::Struggling:  return FVector(0.20f, 0.15f, 0.5f);
	case ENLTEmotionState::Overwhelmed: return FVector(0.30f, 0.25f, 0.3f);
	case ENLTEmotionState::Drifting:    return FVector(-0.10f, 0.10f, 0.8f);
	case ENLTEmotionState::Hyperfocus:  return FVector(0.25f, 0.10f, 1.5f);
	case ENLTEmotionState::Coached:     return FVector(-0.05f, -0.05f, 1.2f);
	case ENLTEmotionState::Fatigued:    return FVector(0.10f, 0.20f, 0.3f);
	case ENLTEmotionState::Celebrating: return FVector(0.0f, -0.20f, 2.0f);
	default:                            return FVector(0.0f, 0.0f, 1.0f);
	}
}

void UNLTEmotionStateComponent::SetOverrideEmotion(ENLTEmotionState InOverrideEmotion, float Duration)
{
	OverrideEmotion = InOverrideEmotion;
	OverrideTimer = Duration;
	bHasOverride = Duration > 0.0f;
	if (!bHasOverride)
	{
		//~ FIX (PR #43 review nit): don't leave a stale timer behind.
		OverrideTimer = 0.0f;
	}
}

void UNLTEmotionStateComponent::TriggerCelebration(float Duration)
{
	SetOverrideEmotion(ENLTEmotionState::Celebrating, Duration);
}
