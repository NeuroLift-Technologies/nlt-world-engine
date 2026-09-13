// NLTLLMBridge.cpp
#include "Agents/NLTLLMBridge.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"

UNLTLLMBridge::UNLTLLMBridge()
{
    PrimaryComponentTick.bCanEverTick = true;
    // Default to Ollama on localhost
    EndpointURL = TEXT("http://localhost:11434/api/generate");
    ModelName = TEXT("qwen3:0.6b");
}

void UNLTLLMBridge::Initialize(const FString& InEndpoint, const FString& InModel)
{
    EndpointURL = InEndpoint;
    ModelName = InModel;
}

void UNLTLLMBridge::BeginPlay()
{
    Super::BeginPlay();
}

void UNLTLLMBridge::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, Tick, ThisTickFunction);
    if (CooldownTimer > 0.0f)
    {
        CooldownTimer -= DeltaTime;
    }
}

bool UNLTLLMBridge::IsReady() const
{
    return !bPendingRequest && EndpointURL.Len() > 0 && CooldownTimer <= 0.0f;
}

void UNLTLLMBridge::SendPrompt(const FString& Prompt)
{
    if (!IsReady()) return;

    bPendingRequest = true;

    // Build the Ollama /api/generate JSON payload
    TSharedRef<FJsonObject> RequestBody = MakeShareable(new FJsonObject);
    RequestBody->SetStringField(TEXT("model"), ModelName);
    RequestBody->SetBoolField(TEXT("stream"), false);

    // Ollama expects a "prompt" field. We embed structured context inside
    // the prompt text so the model can reason over it.
    RequestBody->SetStringField(TEXT("prompt"), Prompt);

    FString RequestBodyStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBodyStr);
    FJsonSerializer::Serialize(RequestBody, Writer);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(EndpointURL);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetContentAsString(RequestBodyStr);
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UNLTLLMBridge::OnProcessRequestComplete);

    if (!HttpRequest->ProcessRequest())
    {
        bPendingRequest = false;
        CooldownTimer = RequestCooldown;
    }
}

void UNLTLLMBridge::RequestMovementCommand(
    const FString& ActorName,
    const FVector& CurrentLocation,
    const FVector& CurrentVelocity,
    const TMap<FString, float>& CognitiveState,
    const FString& GoalDescription,
    const FString& EnvironmentContext)
{
    if (!IsReady()) return;

    FString Prompt = BuildPrompt(ActorName, CurrentLocation, CurrentVelocity, CognitiveState, GoalDescription, EnvironmentContext);
    SendPrompt(Prompt);
}

FString UNLTLLMBridge::BuildPrompt(
    const FString& ActorName,
    const FVector& CurrentLocation,
    const FVector& CurrentVelocity,
    const TMap<FString, float>& CognitiveState,
    const FString& GoalDescription,
    const FString& EnvironmentContext) const
{
    FString CognitiveStr;
    for (const auto& Pair : CognitiveState)
    {
        CognitiveStr += FString::Printf(TEXT("%s: %.3f, "), *Pair.Key, Pair.Value);
    }
    CognitiveStr.RemoveFromEnd(TEXT(", "));

    // We instruct the LLM to respond ONLY in valid JSON with a specific schema.
    return FString::Printf(
        TEXT("You are the brain of an AI agent in a Unreal Engine 5 simulation. "
             "Your only job is to decide the next movement action. "
             "Respond with ONLY valid JSON — no prose, no explanations.\n\n"
             "Actor: %s\n"
             "Location: {x: %.1f, y: %.1f, z: %.1f}\n"
             "Velocity: {x: %.1f, y: %.1f, z: %.1f}\n"
             "Cognitive State: %s\n"
             "Environment: %s\n"
             "Goal: %s\n\n"
             "Available commands: \"move_to\", \"move_by\", \"face_towards\", \"stop\".\n"
             "JSON schema: {\"command\": string, \"x\": float, \"y\": float}\n"
             "For \"move_by\", x/y are relative dx/dy. For \"move_to\"/\"face_towards\", x/y are world coordinates.\n"
             "Only respond with JSON. No markdown, no extra fields.\n"
             "{\"command\": "),
        *ActorName,
        CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z,
        CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z,
        *CognitiveStr, *EnvironmentContext, *GoalDescription
    );
}

void UNLTLLMBridge::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    bPendingRequest = false;
    CooldownTimer = RequestCooldown;

    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("NLTLLMBridge: HTTP request failed."));
        return;
    }

    if (Response->GetResponseCode() != 200)
    {
        UE_LOG(LogTemp, Warning, TEXT("NLTLLMBridge: HTTP %d: %s"),
            Response->GetResponseCode(), *Response->GetContentAsString());
        return;
    }

    FString Body = Response->GetContentAsString();
    ParseResponse(Body);
}

void UNLTLLMBridge::ParseResponse(const FString& ResponseBody)
{
    // Ollama's /api/generate returns: {"model":"...","response":"...","done":true}
    // The actual model output is in the "response" field.
    TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

    if (!FJsonSerializer::Deserialize(Reader, JsonObj) || !JsonObj.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("NLTLLMBridge: Failed to parse response JSON: %s"), *ResponseBody);
        return;
    }

    FString ModelResponse;
    if (JsonObj->HasField(TEXT("response")))
    {
        ModelResponse = JsonObj->GetStringField(TEXT("response"));
    }
    else
    {
        // Some APIs (e.g. /api/chat) return {"message":{"content":"..."}} 
        if (JsonObj->HasField(TEXT("message")) && JsonObj->GetObjectField(TEXT("message")) && JsonObj->GetObjectField(TEXT("message"))->HasField(TEXT("content")))
        {
            ModelResponse = JsonObj->GetObjectField(TEXT("message"))->GetStringField(TEXT("content"));
        }
        else
        {
            // The raw body might itself be the JSON we want
            ModelResponse = ResponseBody;
        }
    }

    // Trim whitespace and potential markdown fences
    ModelResponse = ModelResponse.TrimStartAndEnd();
    if (ModelResponse.StartsWith(TEXT("```json")))
    {
        ModelResponse = ModelResponse.Mid(7);
    }
    if (ModelResponse.EndsWith(TEXT("```")))
    {
        ModelResponse.LeftChopInline(3);
    }
    ModelResponse = ModelResponse.TrimStartAndEnd();

    // Validate that we have JSON by trying to parse it
    TSharedRef<TJsonReader<>> Validator = TJsonReaderFactory<>::Create(ModelResponse);
    TSharedPtr<FJsonObject> CommandJson = MakeShareable(new FJsonObject);
    if (!FJsonSerializer::Deserialize(Validator, CommandJson) || !CommandJson.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("NLTLLMBridge: LLM response is not valid JSON: %s"), *ModelResponse);
        return;
    }

    // Broadcast the validated JSON string so Blueprint listeners can dispatch the command
    OnLLMResponse.Broadcast(ModelResponse);
}
