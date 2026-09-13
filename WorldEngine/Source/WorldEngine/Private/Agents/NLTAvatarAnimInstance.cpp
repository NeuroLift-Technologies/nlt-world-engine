// NLTAvatarAnimInstance.cpp
//
// Procedural animation driven by the emotion state machine.
//
// In UE 5.8, USkeletalMeshComponent does not expose SetBoneRotationByName /
// SetBoneLocationByName (those live on UPoseableMeshComponent).  This AnimInstance
// therefore takes the standard UE data-provider approach: compute procedural
// pose parameters as BlueprintReadOnly member variables and apply facial
// morph targets via UAnimInstance::SetMorphTarget (which IS available).
//
// An Animation Blueprint in the editor can read these parameters to drive
// bone-level posing.  When no SkeletalMesh is assigned it is a no-op — the
// fallback NLTCharacterAnimationComponent handles SimBody static-mesh posing.
//
// Standard humanoid bone names (for Animation Blueprint reference):
//   pelvis, spine_01, spine_02, spine_03, neck, head
//   clavicle_l/r, upperarm_l/r, lowerarm_l/r, hand_l/r
//   thigh_l/r, calf_l/r, foot_l/r

#include "Agents/NLTAvatarAnimInstance.h"
#include "Agents/NLTEmotionStateComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

void UNLTAvatarAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ProceduralTime = 0.0f;
	CachedExpression = ENLTFacialExpression::Neutral;
	CachedAnimState = ENLTAnimationState::None;
}

void UNLTAvatarAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ProceduralTime += DeltaSeconds;

	// --- Gather state from owning character ---
	APawn* OwningPawn = TryGetPawnOwner();
	if (!OwningPawn)
		return;

	// Read emotion component
	if (!EmotionState)
	{
		EmotionState = OwningPawn->FindComponentByClass<UNLTEmotionStateComponent>();
	}

	if (EmotionState)
	{
		CurrentEmotion = EmotionState->CurrentEmotion;
		CurrentAnimationState = EmotionState->CurrentAnimationState;
		PostureInfluence = EmotionState->PostureInfluence;
		EmotionalIntensity = EmotionState->EmotionalIntensity;
		bIsAide = EmotionState->bIsAide;

		// Detect emotion change for facial expression update
		ENLTFacialExpression NewExpr = EmotionState->CurrentExpression;
		if (NewExpr != CachedExpression)
		{
			OnFacialExpressionChanged(NewExpr, CachedExpression);
			CachedExpression = NewExpr;
		}

		// Detect animation state change
		if (CurrentAnimationState != CachedAnimState)
		{
			OnAnimationStateChanged(CurrentAnimationState, CachedAnimState);
			CachedAnimState = CurrentAnimationState;
		}
	}

	// Movement
	if (const ACharacter* Char = Cast<ACharacter>(OwningPawn))
	{
		if (const UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement())
		{
			bIsMoving = MoveComp->Velocity.Size2D() > 1.0f;
		}
	}

	// Compute procedural pose parameters and facial morph targets
	ApplyProceduralPose(DeltaSeconds);
	UpdateFacialCurves(DeltaSeconds);
}

void UNLTAvatarAnimInstance::ApplyProceduralPose(float DeltaSeconds)
{
	// Compute procedural pose parameters based on emotion state and posture
	// influence.  These are BlueprintReadOnly so an Animation Blueprint can
	// read and apply them to individual bones via the standard UE bone
	// manipulation nodes.

	const float Time = ProceduralTime;
	const float PostureLean = PostureInfluence.X;  // forward/back lean
	const float PostureSlump = PostureInfluence.Y;  // hunch
	const float PostureBounce = PostureInfluence.Z; // idle sway/bounce multiplier

	// --- Spine posture ---
	const float BreathAmt = FMath::Sin(Time * 3.0f) * 0.5f + 0.5f;
	const float BreathRot = (PostureLean * 8.0f + BreathAmt * 1.5f) * 0.5f;

	ProceduralSpine01Rotation = FRotator(0.f, 0.f, BreathRot);
	ProceduralSpine02Rotation = FRotator(BreathRot * 0.5f, 0.f, 0.f);

	const float SlumpRot = PostureSlump * 12.0f;
	ProceduralSpine01Rotation.Pitch += SlumpRot;

	// --- Head pose ---
	const float HeadTilt = PostureSlump * 5.0f - BreathRot * 0.5f;
	ProceduralHeadRotation = FRotator(HeadTilt, 0.f, 0.f);

	// Occasional head micro-nods during focused work
	if (CurrentEmotion == ENLTEmotionState::Focused || CurrentEmotion == ENLTEmotionState::Hyperfocus)
	{
		const float NodAmt = FMath::Sin(Time * 1.3f) * 2.0f;
		ProceduralHeadRotation.Pitch += NodAmt;
	}

	// --- Reset limb pose parameters ---
	ProceduralLeftArmRotation = FRotator::ZeroRotator;
	ProceduralRightArmRotation = FRotator::ZeroRotator;
	ProceduralLeftLegRotation = FRotator::ZeroRotator;
	ProceduralRightLegRotation = FRotator::ZeroRotator;

	// --- Arm / shoulder posing by animation state ---
	switch (CurrentAnimationState)
	{
	case ENLTAnimationState::Idle:
	{
		const float FidgetAmt = FMath::Sin(Time * 0.8f + 0.3f);
		const float ArmSwing = FidgetAmt * 1.5f * PostureBounce;
		ProceduralLeftArmRotation = FRotator(ArmSwing * 0.5f, 0.f, 0.f);
		ProceduralRightArmRotation = FRotator(-ArmSwing * 0.5f, 0.f, 0.f);
		break;
	}
	case ENLTAnimationState::Walk:
	{
		const float WalkCycle = FMath::Sin(Time * 5.0f);
		ProceduralLeftArmRotation = FRotator(0.f, WalkCycle * 10.0f, 0.f);
		ProceduralRightArmRotation = FRotator(0.f, -WalkCycle * 10.0f, 0.f);
		const float LegSwing = FMath::Sin(Time * 5.0f) * 15.0f;
		ProceduralLeftLegRotation = FRotator(LegSwing, 0.f, 0.f);
		ProceduralRightLegRotation = FRotator(-LegSwing, 0.f, 0.f);
		break;
	}
	case ENLTAnimationState::Work:
	{
		ProceduralHeadRotation.Pitch += 5.0f;
		ProceduralLeftArmRotation = FRotator(-30.0f, 0.f, 10.0f);
		ProceduralRightArmRotation = FRotator(-30.0f, 0.f, -10.0f);
		break;
	}
	case ENLTAnimationState::Struggle:
	{
		const float HandsAmount = FMath::Sin(Time * 2.0f) * 0.15f * EmotionalIntensity;
		ProceduralHeadRotation.Pitch += 15.0f + HandsAmount * 10.0f;
		ProceduralHeadRotation.Yaw += FMath::Sin(Time * 1.5f) * 3.0f;
		ProceduralLeftArmRotation = FRotator(-60.0f, 0.f, 15.0f);
		ProceduralRightArmRotation = FRotator(-60.0f, 0.f, -15.0f);
		ProceduralSpine01Rotation.Pitch += 15.0f;
		break;
	}
	case ENLTAnimationState::Hyperfocus:
	{
		const float Tension = FMath::Sin(Time * 15.0f) * 0.05f * EmotionalIntensity;
		ProceduralHeadRotation.Pitch += 3.0f;
		ProceduralLeftArmRotation = FRotator(-20.0f + Tension * 100.0f, 0.f, 5.0f);
		ProceduralRightArmRotation = FRotator(-20.0f + Tension * 100.0f, 0.f, -5.0f);
		ProceduralSpine01Rotation.Pitch += 10.0f;
		break;
	}
	case ENLTAnimationState::CoachGesture:
	{
		if (bIsAide)
		{
			const float GestureAmt = FMath::Sin(Time * 3.0f) * 0.3f;
			ProceduralRightArmRotation = FRotator(-20.0f + GestureAmt * 40.0f, 0.f, 0.f);
			ProceduralSpine01Rotation.Pitch += 5.0f; // lean forward, engaged
		}
		else
		{
			const float NodAmt = FMath::Sin(Time * 2.5f) * 0.02f;
			ProceduralHeadRotation.Pitch += NodAmt * 20.0f;
		}
		break;
	}
	case ENLTAnimationState::Nod:
	{
		const float NodAmt = FMath::Sin(Time * 2.5f) * 0.02f;
		ProceduralHeadRotation.Pitch += NodAmt * 20.0f;
		break;
	}
	case ENLTAnimationState::Celebrate:
	{
		const float Bounce = FMath::Abs(FMath::Sin(Time * 6.0f)) * 0.1f;
		ProceduralLeftArmRotation = FRotator(-90.0f, 0.f, 15.0f);
		ProceduralRightArmRotation = FRotator(-90.0f, 0.f, -15.0f);
		ProceduralSpine01Rotation.Yaw += Bounce * 5.0f;
		break;
	}
	case ENLTAnimationState::IdleTired:
	{
		const float SlowBreath = FMath::Sin(Time * 1.5f) * 0.5f + 0.5f;
		ProceduralSpine01Rotation.Pitch += 5.0f + SlowBreath * 3.0f;
		ProceduralHeadRotation.Pitch += 5.0f;
		ProceduralLeftArmRotation = FRotator(15.0f, 0.f, 5.0f);
		ProceduralRightArmRotation = FRotator(15.0f, 0.f, -5.0f);
		break;
	}
	case ENLTAnimationState::Drift:
	{
		const float Sway = FMath::Sin(Time * 0.8f) * 0.03f;
		ProceduralSpine01Rotation.Yaw += Sway * 100.0f;
		ProceduralHeadRotation.Yaw += Sway * 50.0f;
		break;
	}
	default:
		break;
	}
}

void UNLTAvatarAnimInstance::UpdateFacialCurves(float DeltaTime)
{
	// Set morph target values on the AnimInstance.  UAnimInstance::SetMorphTarget
	// routes these to the associated SkeletalMeshComponent's morph target curves.
	const float TargetBlink = (FMath::Sin(ProceduralTime * 4.0f) > 0.95f) ? 1.0f : 0.0f;
	EyeBlink = FMath::FInterpTo(EyeBlink, TargetBlink, DeltaTime, 20.0f);

	// Map emotion to facial blend-shape values
	switch (CurrentEmotion)
	{
	case ENLTEmotionState::Coached:
	case ENLTEmotionState::Celebrating:
		MouthSmile = FMath::FInterpTo(MouthSmile, 0.8f, DeltaTime, 3.0f);
		BrowFurrow = FMath::FInterpTo(BrowFurrow, 0.0f, DeltaTime, 3.0f);
		EyeWide = FMath::FInterpTo(EyeWide, 0.3f, DeltaTime, 3.0f);
		break;
	case ENLTEmotionState::Focused:
	case ENLTEmotionState::Working:
	case ENLTEmotionState::Hyperfocus:
		MouthSmile = FMath::FInterpTo(MouthSmile, 0.0f, DeltaTime, 3.0f);
		BrowFurrow = FMath::FInterpTo(BrowFurrow, 0.3f, DeltaTime, 3.0f);
		EyeWide = FMath::FInterpTo(EyeWide, 0.0f, DeltaTime, 3.0f);
		break;
	case ENLTEmotionState::Struggling:
	case ENLTEmotionState::Overwhelmed:
		MouthSmile = FMath::FInterpTo(MouthSmile, -0.4f, DeltaTime, 3.0f);
		BrowFurrow = FMath::FInterpTo(BrowFurrow, 0.7f, DeltaTime, 3.0f);
		EyeWide = FMath::FInterpTo(EyeWide, 0.5f, DeltaTime, 3.0f);
		break;
	case ENLTEmotionState::Fatigued:
		MouthSmile = FMath::FInterpTo(MouthSmile, -0.3f, DeltaTime, 3.0f);
		BrowFurrow = FMath::FInterpTo(BrowFurrow, 0.5f, DeltaTime, 3.0f);
		EyeWide = FMath::FInterpTo(EyeWide, 0.0f, DeltaTime, 3.0f);
		break;
	case ENLTEmotionState::Drifting:
		MouthSmile = FMath::FInterpTo(MouthSmile, 0.0f, DeltaTime, 3.0f);
		BrowFurrow = FMath::FInterpTo(BrowFurrow, 0.4f, DeltaTime, 3.0f);
		EyeWide = FMath::FInterpTo(EyeWide, 0.2f, DeltaTime, 3.0f);
		break;
	default:
		MouthSmile = FMath::FInterpTo(MouthSmile, 0.0f, DeltaTime, 3.0f);
		BrowFurrow = FMath::FInterpTo(BrowFurrow, 0.0f, DeltaTime, 3.0f);
		EyeWide = FMath::FInterpTo(EyeWide, 0.0f, DeltaTime, 3.0f);
		break;
	}

	// Apply morph target values via the AnimInstance (routes to SkelMeshComponent)
	SetMorphTarget(TEXT("mouthSmile"), MouthSmile);
	SetMorphTarget(TEXT("eyeBlink"), EyeBlink);
	SetMorphTarget(TEXT("browFurrow"), BrowFurrow);
	SetMorphTarget(TEXT("eyeWide"), EyeWide);
}
