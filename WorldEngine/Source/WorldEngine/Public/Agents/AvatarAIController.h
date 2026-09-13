// AvatarAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Dom/JsonObject.h"
#include "AvatarAIController.generated.h"

UCLASS()
class WORLDENGINE_API AAvatarAIController : public AAIController
{
    GENERATED_BODY()

public:
    AAvatarAIController();

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WanderRadius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WaitTimeMin = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WaitTimeMax = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AcceptanceRadius = 50.0f;

    // Learning Agents integration
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
    bool bLearningAgentsActive = false;

    UFUNCTION(BlueprintCallable, Category = "LearningAgents")
    void SetLearningAgentsActive(bool bActive);

    // ============== LLM Control Integration ==============
    // An external LLM controller (the "brain" in neurolift-ai-fusion style
    // pipelines) issues high-level semantic commands. The physical locomotion
    // still runs through this AIController: MoveToLocation / path-following on
    // the AI controller drives the CharacterMovementComponent underneath, so the
    // CMC remains the movement authority (no raw velocity writes from the LLM).

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LLM Control")
    bool bLLMControlActive = false;

    /** The LLM REST API bridge component. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LLM Control")
    class UNLTLLMBridge* LLMBridge;

    UFUNCTION(BlueprintCallable, Category = "LLM Control")
    void SetLLMControlActive(bool bActive);

    UFUNCTION(BlueprintPure, Category = "LLM Control")
    bool IsLLMControlActive() const { return bLLMControlActive; }

    /**
     * Called by the web server when an external LLM sends a movement command.
     * This is separate from the internal REST bridge — external LLM co-pilots
     * can POST commands to the UE HTTP server.
     */
    bool ExecuteLLMCommand(const FString& Command, const TSharedPtr<FJsonObject>& Args, FString& OutMessage);

    /**
     * Process a JSON response from the LLM bridge and execute the movement command.
     * Expected JSON: {"command": "move_to", "x": 100, "y": 500}
     */
    UFUNCTION()
    void HandleLLMResponse(const FString& JsonResponse);

    /** Request the next movement command from the LLM based on current state. */
    void RequestLLMMovementCommand();

private:
    void Wander();
    void Wait();

    FVector HomeLocation;
    FTimerHandle WaitTimer;
    bool bIsWaiting = false;
};
