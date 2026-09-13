// NLTPairChoreographyComponent.h
//
// Avatar↔Aide social choreography.
//
// When an Avatar and Aide are paired, this component handles:
//  - Facing: each character turns to face their partner
//  - Co-reaction: when one character's emotion changes, the other reacts
//  - Coaching gestures: synchronized nod + gesture cycles
//
// This is the "social choreography" that makes the pair feel like a
// collaborative duo rather than two independent agents — a core piece of
// the Sims "feel alive" loop.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/NLTFusionCore.h"
#include "NLTPairChoreographyComponent.generated.h"

class AActor;
class UNLTEmotionStateComponent;

/** The role this character plays in a choreographed pair. */
UENUM(BlueprintType)
enum class ENLTPairRole : uint8
{
	None    UMETA(DisplayName = "None"),
	Avatar  UMETA(DisplayName = "Avatar"),
	Aide    UMETA(DisplayName = "Aide")
};

/** Mode of social choreography currently active. */
UENUM(BlueprintType)
enum class ENLTPairChoreographyMode : uint8
{
	Independent UMETA(DisplayName = "Independent"),
	Facing      UMETA(DisplayName = "Facing"),
	Coaching    UMETA(DisplayName = "Coaching")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WORLDENGINE_API UNLTPairChoreographyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNLTPairChoreographyComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/** Assign the partner actor for this pair. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Choreography")
	void SetPartner(AActor* InPartner);

	/** Set whether this character is the Avatar or the Aide in the pair. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Choreography")
	void SetPairRole(ENLTPairRole InRole);

	/** Enter coaching mode: both characters face each other and the
	    Aide performs a coaching gesture while the Avatar nods. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Choreography")
	void EnterCoachingMode();

	/** Exit coaching mode and return to independent behavior. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Choreography")
	void ExitCoachingMode();

	/** Trigger a one-shot synchronized reaction (e.g. both nod at once). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Choreography")
	void TriggerSynchronizedReaction(float Duration = 1.5f);

	/// --- Read-only state ---

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Choreography")
	ENLTPairChoreographyMode CurrentMode = ENLTPairChoreographyMode::Independent;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Choreography")
	ENLTPairRole PairRole = ENLTPairRole::None;

	UPROPERTY(BlueprintReadOnly, Category = "NLT|Choreography")
	bool bHasPartner = false;

	/** Whether this character is currently facing their partner. */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Choreography")
	bool bIsFacingPartner = false;

	/** How recently a synchronized reaction was triggered (< 0 means inactive). */
	UPROPERTY(BlueprintReadOnly, Category = "NLT|Choreography")
	float ReactionRemainingTime = 0.0f;

	/// --- Events ---

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoachingStarted, ENLTPairRole, InitiatorRole);
	UPROPERTY(BlueprintAssignable, Category = "NLT|Choreography")
	FOnCoachingStarted OnCoachingStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCoachingEnded);
	UPROPERTY(BlueprintAssignable, Category = "NLT|Choreography")
	FOnCoachingEnded OnCoachingEnded;

	/// --- Tuning ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Choreography|Tuning")
	float FaceTurnSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Choreography|Tuning")
	float CoachingDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Choreography|Tuning")
	float AideFollowSpeed = 200.0f;

	/** If true, the Aide automatically walks to coaching distance when entering coaching mode. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Choreography|Tuning")
	bool bAideAutoPositions = true;

protected:
	/** Update facing: rotate toward partner. */
	void UpdateFacing(float DeltaTime);

	/** Update Aide's position: follow Avatar at CoachingDistance. */
	void UpdateAidePosition(float DeltaTime);

	/** React to partner's emotion changes. */
	void ReactToPartnerEmotion(ENLTEmotionState PartnerEmotion);

	/** Get the emotion component of this character or the partner. */
	UNLTEmotionStateComponent* GetEmotionComponent();
	UNLTEmotionStateComponent* GetPartnerEmotionComponent();

private:
	UPROPERTY()
	TObjectPtr<AActor> Partner;

	UPROPERTY()
	TObjectPtr<UNLTEmotionStateComponent> CachedEmotion;

	UPROPERTY()
	TObjectPtr<UNLTEmotionStateComponent> CachedPartnerEmotion;

	/** Last emotion the partner was in (for change detection). */
	ENLTEmotionState LastPartnerEmotion = ENLTEmotionState::Neutral;

	/** Whether the previous tick had a valid emotion component. */
	bool bEmotionBound = false;
};
