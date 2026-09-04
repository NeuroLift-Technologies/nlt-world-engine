#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "NLTAvatarVisualComponent.generated.h"

class USkeletalMeshComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WORLDENGINE_API UNLTAvatarVisualComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNLTAvatarVisualComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "NLT|Avatar|Visual")
	void UpdateFromCognitiveState(float Focus, float Stress, float CognitiveLoad, FName EmotionalState);

	UFUNCTION(BlueprintCallable, Category = "NLT|Avatar|Visual")
	void SetStatusRingColor(const FLinearColor& Color);

	UFUNCTION(BlueprintCallable, Category = "NLT|Avatar|Visual")
	void SetEmissiveGlow(float Intensity);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	TObjectPtr<UParticleSystem> StressParticleTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	TObjectPtr<UParticleSystem> FocusParticleTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	TObjectPtr<UParticleSystem> BurnoutParticleTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	FLinearColor FocusGlowColor = FLinearColor(0.2f, 0.6f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	FLinearColor StressGlowColor = FLinearColor(1.0f, 0.3f, 0.1f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	FLinearColor BurnoutGlowColor = FLinearColor(0.5f, 0.1f, 0.05f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	float MaxGlowIntensity = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	bool bShowStatusRing = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Avatar|Visual")
	bool bShowParticles = true;

private:
	void CreateStatusRing();
	void CreateParticleComponents();
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

	UPROPERTY()
	TObjectPtr<UStaticMesh> StatusRingMeshAsset;

	float CurrentGlow = 0.0f;
	float TargetGlow = 0.0f;
};
