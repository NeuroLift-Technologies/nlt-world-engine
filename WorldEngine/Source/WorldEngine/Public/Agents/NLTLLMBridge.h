// NLTLLMBridge.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/IHttpRequest.h"
#include "Dom/JsonObject.h"
#include "NLTLLMBridge.generated.h"

/**
 * Asynchronous REST API bridge that connects an Unreal Engine actor to a local
 * LLM (e.g. Ollama on http://localhost:11434/api/generate).
 *
 * The LLM acts as the "brain" — it receives the actor's cognitive state and
 * environment context, and returns a structured JSON movement command. UE
 * handles all physics/navigation; the LLM only decides *what* to do, not *how*
 * the physics executes.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WORLDENGINE_API UNLTLLMBridge : public UActorComponent
{
    GENERATED_BODY()

public:
    /** Blueprint event fired when a parsed JSON response is ready. */
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLLMResponseReceived, const FString&, ResponseJSON);

    UNLTLLMBridge();

    /** Initialize the bridge with an Ollama endpoint and model name. */
    UFUNCTION(BlueprintCallable, Category = "LLM Bridge")
    void Initialize(const FString& InEndpoint, const FString& InModel);

    /** Send a raw prompt to the LLM (simple fire-and-forget). */
    UFUNCTION(BlueprintCallable, Category = "LLM Bridge")
    void SendPrompt(const FString& Prompt);

    /** Send structured actor context + a natural-language instruction. */
    UFUNCTION(BlueprintCallable, Category = "LLM Bridge")
    void RequestMovementCommand(
        const FString& ActorName,
        const FVector& CurrentLocation,
        const FVector& CurrentVelocity,
        const TMap<FString, float>& CognitiveState,
        const FString& GoalDescription,
        const FString& EnvironmentContext
    );

    /** Whether the bridge is ready to send requests (endpoint set + not already pending). */
    UFUNCTION(BlueprintPure, Category = "LLM Bridge")
    bool IsReady() const;

    /** The LLM endpoint URL (e.g. http://localhost:11434/api/generate). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LLM Bridge")
    FString EndpointURL;

    /** The model name to use (e.g. llama3.2, qwen2.5, etc.). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LLM Bridge")
    FString ModelName;

    /** Cooldown between requests in seconds (prevents flooding the LLM). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LLM Bridge")
    float RequestCooldown = 5.0f;

    /** Blueprint event fired when a JSON response is ready to act on. */
    UPROPERTY(BlueprintAssignable, Category = "LLM Bridge")
    FOnLLMResponseReceived OnLLMResponse;

private:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction) override;

    /** Callback when the HTTP request completes. */
    void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    /** Parse the LLM JSON response and dispatch the result. */
    void ParseResponse(const FString& ResponseBody);

    /** Extract the first balanced {...} JSON object (handles prose/fence bleed). */
    static FString ExtractFirstJsonObject(const FString& Text);

    /** Build the prompt string from structured inputs. */
    FString BuildPrompt(
        const FString& ActorName,
        const FVector& CurrentLocation,
        const FVector& CurrentVelocity,
        const TMap<FString, float>& CognitiveState,
        const FString& GoalDescription,
        const FString& EnvironmentContext
    ) const;

    /** Whether we're currently waiting for an LLM response. */
    bool bPendingRequest = false;

    /** Time until the next request is allowed. */
    float CooldownTimer = 0.0f;
};
