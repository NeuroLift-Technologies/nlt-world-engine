#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "NLTAvatarVisualComponent.generated.h"

/**
 * Visual feedback component for Avatar characters.
 * Drives skeletal mesh material parameters, status ring color,
 * and ambient particles based on cognitive state.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WORLDENGINE_API UNLTAvatarVisualComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNLTAvatarVisualComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Update visuals from cognitive state. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Avatar|Visual")
	void UpdateFromCognitiveState(float Focus, float Stress, float CognitiveLoad, FName EmotionalState);

	/** Set the status ring color (below the avatar). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Avatar|Visual")
	void SetStatusRingColor(const FLinearColor& Color);

	/** Set the emissive glow intensity on the avatar material. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Avatar|Visual")
	void SetEmissiveGlow(float Intensity);

	/** Particle system for stress effect (red sparks). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	TObjectPtr<UParticleSystem> StressParticleTemplate;

	/** Particle system for focus effect (blue aura). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	TObjectPtr<UParticleSystem> FocusParticleTemplate;

	/** Particle system for burnout effect (dark smoke). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	TObjectPtr<UParticleSystem> BurnoutParticleTemplate;

	/** Emissive glow color when focused. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	FLinearColor FocusGlowColor = FLinearColor(0.2f, 0.6f, 1.0f, 1.0f);

	/** Emissive glow color when stressed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	FLinearColor StressGlowColor = FLinearColor(1.0f, 0.3f, 0.1f, 1.0f);

	/** Emissive glow color when burned out. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	FLinearColor BurnoutGlowColor = FLinearColor(0.5f, 0.1f, 0.05f, 1.0f);

	/** Maximum emissive glow intensity. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	float MaxGlowIntensity = 3.0f;

	/** Whether to show the status ring. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	bool bShowStatusRing = true;

	/** Whether to show ambient particles. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	bool bShowParticles = true;

private:
	/** Create the status ring mesh under the avatar. */
	void CreateStatusRing();

	/** Create particle components. */
	void CreateParticleComponents();

	/** Get or create a dynamic material instance on the skeletal mesh. */
	UMaterialInstanceDynamic* GetAvatarMaterial();

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> StatusRingMesh;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> StatusRingMaterial;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> AvatarMaterialInstance;

	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> StressParticles;

	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> FocusParticles;

	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> BurnoutParticles;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	float CurrentGlow = 0.0f;
	float TargetGlow = 0.0f;
};
