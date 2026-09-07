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

    UFUNCTION(BlueprintCallable, Category = "LLM Control")
    void SetLLMControlActive(bool bActive);

    UFUNCTION(BlueprintPure, Category = "LLM Control")
    bool IsLLMControlActive() const { return bLLMControlActive; }

    /**
     * Execute a semantic command emitted by an LLM controller.
     *
     * Supported commands (Args is a JSON object, may be empty):
     *   move_to         { "x": float, "y": float }       -> nav-move to waypoint
     *   move_by         { "dx": float, "dy": float }     -> nav-move by relative offset (clamped)
     *   move_to_object  { "object_id": string }          -> nav-move to first actor with that name
     *   face_towards    { "x": float, "y": float }       -> rotate to face a world point
     *   stop            {}                               -> StopMovement() (keep LLM control)
     *   release         {}                               -> stop + hand control back to wander AI
     *
     * @param Command   The command name (case-insensitive).
     * @param Args      JSON args object (may be null).
     * @param OutMessage Human-readable outcome for logging / HTTP response.
     * @return true when the command was recognized and dispatched.
     *
     * NOTE: intentionally NOT a UFUNCTION — TSharedPtr<FJsonObject> cannot be
     * reflected by UHT. This is called from C++ (e.g. the web server).
     */
    bool ExecuteLLMCommand(const FString& Command, const TSharedPtr<FJsonObject>& Args, FString& OutMessage);

private:
    void Wander();
    void Wait();

    FVector HomeLocation;
    FTimerHandle WaitTimer;
    bool bIsWaiting = false;
};
