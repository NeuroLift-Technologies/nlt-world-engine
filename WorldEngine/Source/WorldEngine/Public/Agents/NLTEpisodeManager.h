// NLTEpisodeManager.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NLTEpisodeManager.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WORLDENGINE_API UNLTEpisodeManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UNLTEpisodeManager();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Episode")
    int32 MaxEpisodeSteps = 512;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Episode")
    float StepInterval = 0.1f;

    UPROPERTY(BlueprintReadOnly, Category = "Episode")
    int32 CurrentStep = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Episode")
    bool bEpisodeActive = false;

    UFUNCTION(BlueprintCallable, Category = "Episode")
    void StartEpisode();

    UFUNCTION(BlueprintCallable, Category = "Episode")
    void EndEpisode();

    UFUNCTION(BlueprintCallable, Category = "Episode")
    void ResetEpisode();

    UFUNCTION(BlueprintPure, Category = "Episode")
    bool IsEpisodeComplete() const;

    // Check cognitive-based completion
    UFUNCTION(BlueprintCallable, Category = "Episode")
    void CheckCognitiveCompletion(float Independence, float Burnout);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEpisodeComplete);
    UPROPERTY(BlueprintAssignable, Category = "Episode")
    FOnEpisodeComplete OnEpisodeComplete;

private:
    float StepTimer = 0.0f;
};
