// NLTPairChoreographyComponent.cpp
//
// Avatar↔Aide social choreography implementation.

#include "Agents/NLTPairChoreographyComponent.h"
#include "Agents/NLTEmotionStateComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogNLTPair, Log, All);

UNLTPairChoreographyComponent::UNLTPairChoreographyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
}

void UNLTPairChoreographyComponent::BeginPlay()
{
	Super::BeginPlay();

	// Cache our own emotion component
	CachedEmotion = GetOwner()->FindComponentByClass<UNLTEmotionStateComponent>();
}

void UNLTPairChoreographyComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Partner || !CachedEmotion)
		return;

	// Update facing toward partner
	if (CurrentMode == ENLTPairChoreographyMode::Facing ||
	    CurrentMode == ENLTPairChoreographyMode::Coaching)
	{
		UpdateFacing(DeltaTime);
	}

	// Aide follows Avatar at coaching distance when in coaching mode
	if (CurrentMode == ENLTPairChoreographyMode::Coaching && PairRole == ENLTPairRole::Aide)
	{
		UpdateAidePosition(DeltaTime);
	}

	// React to partner's emotion changes
	if (UNLTEmotionStateComponent* PartnerEmotion = GetPartnerEmotionComponent())
	{
		if (PartnerEmotion->CurrentEmotion != LastPartnerEmotion)
		{
			ReactToPartnerEmotion(PartnerEmotion->CurrentEmotion);
			LastPartnerEmotion = PartnerEmotion->CurrentEmotion;
		}
	}

	// Update reaction timer
	if (ReactionRemainingTime > 0.0f)
	{
		ReactionRemainingTime -= DeltaTime;
	}
}

void UNLTPairChoreographyComponent::SetPartner(AActor* InPartner)
{
	//~ FIX (PR #43 review): swapping partners must invalidate the cached
	//~ partner emotion + reaction state, otherwise we keep reading the old
	//~ partner's component.
	if (Partner != InPartner)
	{
		CachedPartnerEmotion = nullptr;
		LastPartnerEmotion = ENLTEmotionState::Neutral;
		ReactionRemainingTime = -1.0f;
		bIsFacingPartner = false;
	}
	Partner = InPartner;
	bHasPartner = Partner != nullptr;
}

void UNLTPairChoreographyComponent::SetPairRole(ENLTPairRole InRole)
{
	PairRole = InRole;
}

void UNLTPairChoreographyComponent::EnterCoachingMode()
{
	if (CurrentMode == ENLTPairChoreographyMode::Coaching)
		return;

	CurrentMode = ENLTPairChoreographyMode::Coaching;
	OnCoachingStarted.Broadcast(PairRole);

	UE_LOG(LogNLTPair, Log, TEXT("Entered coaching mode as %d"),
		static_cast<int32>(PairRole));
}

void UNLTPairChoreographyComponent::ExitCoachingMode()
{
	if (CurrentMode != ENLTPairChoreographyMode::Coaching)
		return;

	CurrentMode = ENLTPairChoreographyMode::Independent;
	OnCoachingEnded.Broadcast();

	UE_LOG(LogNLTPair, Log, TEXT("Exited coaching mode"));
}

void UNLTPairChoreographyComponent::TriggerSynchronizedReaction(float Duration)
{
	ReactionRemainingTime = Duration;

	// Trigger a celebration on both characters
	if (CachedEmotion)
	{
		CachedEmotion->TriggerCelebration(Duration);
	}

	if (UNLTEmotionStateComponent* PartnerEmotion = GetPartnerEmotionComponent())
	{
		PartnerEmotion->TriggerCelebration(Duration);
	}

	UE_LOG(LogNLTPair, Log, TEXT("Synchronized reaction triggered (duration=%.1f)"), Duration);
}

void UNLTPairChoreographyComponent::UpdateFacing(float DeltaTime)
{
	if (!Partner || !GetOwner())
		return;

	const FVector OwnerLoc = GetOwner()->GetActorLocation();
	const FVector PartnerLoc = Partner->GetActorLocation();
	const FVector Direction = PartnerLoc - OwnerLoc;

	if (Direction.IsNearlyZero())
		return;

	//~ FIX (PR #43 review): yaw-only facing — Direction.Rotation() includes
	//~ pitch, which would tilt the whole character when partner Z differs.
	FRotator TargetRot(0.0f, Direction.Rotation().Yaw, 0.0f);
	FRotator CurrentRot = GetOwner()->GetActorRotation();
	CurrentRot.Pitch = 0.0f;
	CurrentRot.Roll = 0.0f;
	const FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, FaceTurnSpeed);

	GetOwner()->SetActorRotation(NewRot);
	bIsFacingPartner = true;
}

void UNLTPairChoreographyComponent::UpdateAidePosition(float DeltaTime)
{
	if (!Partner || PairRole != ENLTPairRole::Aide || !GetOwner())
		return;

	const FVector PartnerLoc = Partner->GetActorLocation();
	const FVector Direction = GetOwner()->GetActorLocation() - PartnerLoc;
	const float Distance = Direction.Size();

	if (Distance > CoachingDistance)
	{
		const FVector ToPartner = PartnerLoc - GetOwner()->GetActorLocation();
		const FVector MoveDir = ToPartner.GetSafeNormal();

		if (ACharacter* AideChar = Cast<ACharacter>(GetOwner()))
		{
			//~ FIX (PR #43 review): drive via movement input so collision/nav
			//~ and CharacterMovementComponent stay authoritative — never
			//~ SetActorLocation a character.
			AideChar->AddMovementInput(MoveDir, 1.0f, false);
		}
		else if (AActor* Owner = GetOwner())
		{
			// Non-character fallback: direct interpolation at an explicit
			// interp speed (tunable via AideFollowInterpSpeed).
			const FVector Normalized = Direction.GetSafeNormal();
			const FVector TargetPos = PartnerLoc + Normalized * CoachingDistance;
			const FVector CurrentPos = Owner->GetActorLocation();
			const FVector NewPos = FMath::VInterpTo(CurrentPos, TargetPos, DeltaTime, AideFollowInterpSpeed);
			Owner->SetActorLocation(NewPos, true);
		}
	}
}

void UNLTPairChoreographyComponent::ReactToPartnerEmotion(ENLTEmotionState PartnerEmotion)
{
	switch (PartnerEmotion)
	{
	case ENLTEmotionState::Overwhelmed:
	case ENLTEmotionState::Struggling:
	{
		// Aide should start coaching
		if (PairRole == ENLTPairRole::Aide && CurrentMode != ENLTPairChoreographyMode::Coaching)
		{
			EnterCoachingMode();
		}
		// Avatar accepts coaching
		if (PairRole == ENLTPairRole::Avatar && CachedEmotion)
		{
			CachedEmotion->SetOverrideEmotion(ENLTEmotionState::Coached, 5.0f);
		}
		break;
	}
	case ENLTEmotionState::Celebrating:
	{
		// Partner is celebrating — react in kind
		if (ReactionRemainingTime <= 0.0f && CachedEmotion)
		{
			TriggerSynchronizedReaction(2.0f);
		}
		break;
	}
	case ENLTEmotionState::Hyperfocus:
	{
		// Aide stays nearby but doesn't interrupt
		if (PairRole == ENLTPairRole::Aide && CurrentMode == ENLTPairChoreographyMode::Independent)
		{
			CurrentMode = ENLTPairChoreographyMode::Facing;
		}
		break;
	}
	default:
		break;
	}
}

UNLTEmotionStateComponent* UNLTPairChoreographyComponent::GetEmotionComponent()
{
	return CachedEmotion.Get();
}

UNLTEmotionStateComponent* UNLTPairChoreographyComponent::GetPartnerEmotionComponent()
{
	if (!Partner || !CachedPartnerEmotion)
	{
		if (Partner)
		{
			CachedPartnerEmotion = Partner->FindComponentByClass<UNLTEmotionStateComponent>();
		}
	}
	return CachedPartnerEmotion.Get();
}
