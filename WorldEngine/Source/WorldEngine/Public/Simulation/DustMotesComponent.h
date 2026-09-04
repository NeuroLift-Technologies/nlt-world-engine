#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "DustMotesComponent.generated.h"

/**
 * Atmospheric dust motes — floating particles that drift through the scene.
 * Density and visibility respond to time-of-day and environment state.
 * Uses a soft round particle material for a natural look.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WORLDENGINE_API UDustMotesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDustMotesComponent();

	UFUNCTION(BlueprintCallable, Category = "Dust Motes")
	void SetVisibility(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "Dust Motes")
	void SetDensity(float Density);

	UFUNCTION(BlueprintCallable, Category = "Dust Motes")
	void SetParticleSystem(UParticleSystem* Template);

	UFUNCTION(BlueprintPure, Category = "Dust Motes")
	bool GetVisibility() const;

	UFUNCTION(BlueprintPure, Category = "Dust Motes")
	float GetDensity() const;

	/** Set the drift speed of dust particles. */
	UFUNCTION(BlueprintCallable, Category = "Dust Motes")
	void SetDriftSpeed(float Speed);

	/** Set the color tint of dust particles. */
	UFUNCTION(BlueprintCallable, Category = "Dust Motes")
	void SetColorTint(const FLinearColor& Color);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/** Create a procedural dust particle system if no template is provided. */
	void CreateProceduralDustSystem();

	UPROPERTY(EditAnywhere, Category = "Dust Motes", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DustDensity = 0.5f;
	UPROPERTY()
	bool bIsVisible = true;

	UPROPERTY(EditAnywhere, Category = "Dust Motes", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float DriftSpeed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Dust Motes")
	FLinearColor DustColor = FLinearColor(0.9f, 0.85f, 0.7f, 1.0f);

	UPROPERTY(EditAnywhere, Category = "Dust Motes")
	FVector VolumeSize = FVector(2000.0f, 2000.0f, 500.0f);

	UPROPERTY()
	bool bIsVisible = false;

	UPROPERTY()
	UParticleSystemComponent* DustParticles = nullptr;

	UPROPERTY()
	UParticleSystem* DustTemplate = nullptr;
};
