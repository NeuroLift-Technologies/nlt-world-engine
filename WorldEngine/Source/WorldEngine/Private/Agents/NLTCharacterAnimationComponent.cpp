// NLTCharacterAnimationComponent.cpp
//
// Animation state machine implementation. Drives either SkeletalMesh
// montages (when a rigged character is available) or procedural static-mesh
// rotation offsets (SimBody fallback).

#include "Agents/NLTCharacterAnimationComponent.h"
#include "Agents/NLTEmotionStateComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimTypes.h"

DEFINE_LOG_CATEGORY_STATIC(LogNLTAnim, Log, All);

UNLTCharacterAnimationComponent::UNLTCharacterAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
}

void UNLTCharacterAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	// Auto-bind: try to find the SkeletalMeshComponent on the owning character
	if (AActor* Owner = GetOwner())
	{
		if (ACharacter* Char = Cast<ACharacter>(Owner))
		{
			BindSkeletalMesh(Char->GetMesh());
		}

		// Cache the emotion component
		EmotionComponent = Owner->FindComponentByClass<UNLTEmotionStateComponent>();
	}
}

void UNLTCharacterAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!EmotionComponent)
		return;

	// --- Determine movement state ---
	bIsMoving = false;
	if (const ACharacter* Char = Cast<ACharacter>(GetOwner()))
	{
		if (const UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement())
		{
			bIsMoving = MoveComp->Velocity.Size2D() > 5.0f;
		}
	}

	// Sync bIsMoving into the emotion component so it can map to Walk animation
	EmotionComponent->bIsMoving = bIsMoving;

	// --- Update target posture from emotion ---
	TargetPosture = EmotionComponent->PostureInfluence;

	// --- Check for state transition ---
	const ENLTAnimationState NewState = EmotionComponent->CurrentAnimationState;
	if (NewState != CurrentState)
	{
		TransitionTo(NewState);
	}

	// --- Apply animation ---
	if (SkelMesh)
	{
		// SkeletalMesh path: montages are driven by the AnimInstance.
		// The NLTAvatarAnimInstance reads emotion state directly and
		// applies procedural bone offsets in NativeUpdateAnimation.
		// Here we just ensure the right montage is playing.
		PlayMontageForState(CurrentState);
	}
	else if (StaticMesh)
	{
		// Procedural fallback: adjust the static mesh orientation to
		// approximate the emotional posture.
		ApplyProceduralPosture(DeltaTime);
	}

	StateTime += DeltaTime;
}

void UNLTCharacterAnimationComponent::BindSkeletalMesh(USkeletalMeshComponent* InSkelMesh)
{
	SkelMesh = InSkelMesh;
	if (SkelMesh)
	{
		UE_LOG(LogNLTAnim, Log, TEXT("Bound SkeletalMesh for animation"));
	}
}

void UNLTCharacterAnimationComponent::BindStaticMesh(UStaticMeshComponent* InStaticMesh)
{
	StaticMesh = InStaticMesh;
	if (StaticMesh)
	{
		UE_LOG(LogNLTAnim, Log, TEXT("Bound StaticMesh fallback for procedural animation"));
	}
}

void UNLTCharacterAnimationComponent::SetEmotionComponent(UNLTEmotionStateComponent* InEmotion)
{
	EmotionComponent = InEmotion;
}

UAnimMontage* UNLTCharacterAnimationComponent::GetMontageForState(ENLTAnimationState State) const
{
	switch (State)
	{
	case ENLTAnimationState::Idle:        return Montage_Idle;
	case ENLTAnimationState::Walk:        return Montage_Walk;
	case ENLTAnimationState::Work:        return Montage_Work;
	case ENLTAnimationState::Struggle:    return Montage_Struggle;
	case ENLTAnimationState::Hyperfocus:  return Montage_Hyperfocus;
	case ENLTAnimationState::CoachGesture: return Montage_CoachGesture;
	case ENLTAnimationState::IdleTired:   return Montage_IdleTired;
	case ENLTAnimationState::Celebrate:   return Montage_Celebrate;
	case ENLTAnimationState::Drift:       return Montage_Drift;
	case ENLTAnimationState::Nod:         return Montage_Nod;
	default:                              return Montage_Idle;
	}
}

void UNLTCharacterAnimationComponent::TransitionTo(ENLTAnimationState NewState)
{
	if (bDebugLogTransitions)
	{
		UE_LOG(LogNLTAnim, Log, TEXT("Animation transition: %d -> %d"),
			static_cast<int32>(CurrentState), static_cast<int32>(NewState));
	}

	CurrentState = NewState;
	StateTime = 0.0f;

	if (SkelMesh)
	{
		PlayMontageForState(NewState);
	}
}

void UNLTCharacterAnimationComponent::PlayMontageForState(ENLTAnimationState State)
{
	if (!SkelMesh)
		return;

	UAnimMontage* Montage = GetMontageForState(State);
	if (!Montage)
		return;

	UAnimInstance* AnimInst = SkelMesh->GetAnimInstance();
	if (!AnimInst)
		return;

	// Only play if a different montage is playing (avoid restarting the same loop)
	if (CurrentMontage == Montage)
	{
		// Still need to keep it playing
		if (!AnimInst->Montage_IsPlaying(Montage))
		{
			AnimInst->Montage_Play(Montage, 1.0f);
		}
		return;
	}

	CurrentMontage = Montage;

	// Crossfade from current montage to new one
	constexpr float FadeTime = 0.2f;
	if (CurrentMontage && AnimInst->Montage_IsPlaying(CurrentMontage))
	{
		AnimInst->Montage_Play(Montage, 1.0f, EMontagePlayReturnType::MontageLength, FadeTime);
	}
	else
	{
		AnimInst->Montage_Play(Montage, 1.0f);
	}
}

void UNLTCharacterAnimationComponent::ApplyProceduralPosture(float DeltaTime)
{
	if (!StaticMesh)
		return;

	// Spring-interpolate toward target posture
	CurrentPosture = FMath::VInterpTo(CurrentPosture, TargetPosture, DeltaTime, ProceduralSpringSpeed);

	// Apply posture as mesh rotation (SimBody is a static mesh; we tilt it
	// to approximate emotional body language).
	const float LeanForward = CurrentPosture.X * MaxProceduralTilt;
	const float Slump = CurrentPosture.Y * MaxProceduralTilt * 0.5f;

	const FRotator TargetRot(0.0f, 0.0f, Slump);
	FRotator CurrentRot = StaticMesh->GetRelativeRotation();
	FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, 5.0f);
	StaticMesh->SetRelativeRotation(NewRot);

	// Subtle vertical bob for idle states
	if (CurrentState == ENLTAnimationState::Idle || CurrentState == ENLTAnimationState::IdleTired)
	{
		const float BobAmount = CurrentPosture.Z * 2.0f;
		float CurrentZ = StaticMesh->GetRelativeLocation().Z;
		float TargetZ = BobAmount;
		CurrentZ = FMath::FInterpTo(CurrentZ, TargetZ, DeltaTime, 3.0f);
		StaticMesh->SetRelativeLocation(FVector(0, 0, CurrentZ));
	}
}
