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
    // The prompt is engineered for qwen3:0.6b — small models tend to echo back
    // coordinates rather than explore. We use move_by with relative offsets
    // and explicitly tell the model to pick a NEW direction each time.
    return FString::Printf(
        TEXT("You are an AI agent exploring a 2D environment. Pick the next movement. "
             "Respond ONLY with valid JSON.\n\n"
             "Current position: (%.1f, %.1f)\n"
             "Current velocity: (%.1f, %.1f)\n"
             "Cognitive state: %s\n\n"
             "You MUST pick a destination that is different from your current position. "
             "Use move_by with dx and dy in range [-300, 300]. "
             "Each call must move you to a new area. Do not echo back your current coordinates.\n\n"
             "Formats:\n"
             "{\"command\": \"move_by\", \"dx\": <float>, \"dy\": <float>}\n"
             "{\"command\": \"move_to\", \"x\": <float>, \"y\": <float>}\n"
             "{\"command\": \"face_towards\", \"x\": <float>, \"y\": <float>}\n"
             "{\"command\": \"stop\"}\n\n"
             "Respond now:\n"
             "{\"command\": "),
        CurrentLocation.X, CurrentLocation.Y,
        CurrentVelocity.X, CurrentVelocity.Y,
        *CognitiveStr
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

    // Debug: log what the LLM actually returned
    FString Command;
    CommandJson->TryGetStringField(TEXT("command"), Command);
    UE_LOG(LogTemp, Log, TEXT("NLTLLMBridge: LLM returned command='%s', raw: %s"), *Command, *ModelResponse);

    // Broadcast the validated JSON string so Blueprint listeners can dispatch the command
    OnLLMResponse.Broadcast(ModelResponse);
}
