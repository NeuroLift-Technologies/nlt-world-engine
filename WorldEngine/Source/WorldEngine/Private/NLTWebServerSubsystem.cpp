#include "NLTWebServerSubsystem.h"
#include "Simulation/NLTSimulationSubsystem.h"
#include "Simulation/NLTSimulationClockSubsystem.h"
#include "Scenarios/Demo/NLTScenarioManagerSubsystem.h"
#include "Agents/NLTAgentSpawnerSubsystem.h"
#include "Agents/NLTAgentFragments.h"
#include "Core/NLTFusionCore.h"
#include "MassEntitySubsystem.h"
#include "MassEntityQuery.h"
#include "MassExecutionContext.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/CoreDelegates.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTWebServer);

void UNLTWebServerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Host the web server at engine boot so it (and the shared HTTP listeners,
	// including the ModelContextProtocol MCP endpoint on port 8000) are not tied
	// to any single PIE world lifecycle. Engine subsystems initialize before the
	// HTTP module is guaranteed to be loaded, so defer the start to post-engine-init.
	FCoreDelegates::OnPostEngineInit.AddUObject(this, &UNLTWebServerSubsystem::StartServer, 8765);
	UE_LOG(LogNLTWebServer, Log, TEXT("WebServer subsystem initialized"));
}

void UNLTWebServerSubsystem::Deinitialize()
{
	StopServer();
	FCoreDelegates::OnPostEngineInit.RemoveAll(this);
	Super::Deinitialize();
}

bool UNLTWebServerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

UWorld* UNLTWebServerSubsystem::GetSimulationWorld() const
{
	if (!GEngine)
	{
		return nullptr;
	}

	// Prefer an active PIE world so we observe the live simulation when it is running.
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (WorldContext.WorldType == EWorldType::PIE && WorldContext.World())
		{
			return WorldContext.World();
		}
	}

	// Fall back to any available world (e.g. editor world, or game world).
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (WorldContext.World())
		{
			return WorldContext.World();
		}
	}

	return nullptr;
}

void UNLTWebServerSubsystem::StartServer(int32 InPort)
{
	if (bRunning)
	{
		UE_LOG(LogNLTWebServer, Warning, TEXT("Server already running on port %d"), Port);
		return;
	}

	Port = static_cast<uint32>(InPort);

	// FHttpServerModule may not be loaded yet at engine boot (it is loaded
	// lazily). Force-load it so GetHttpRouter/StartAllListeners work regardless
	// of module load order.
	FModuleManager::Get().LoadModuleChecked<FHttpServerModule>("HTTPServer");
	FHttpServerModule& HttpModule = FHttpServerModule::Get();

	HttpRouter = HttpModule.GetHttpRouter(Port, true);
	if (!HttpRouter.IsValid())
	{
		UE_LOG(LogNLTWebServer, Error, TEXT("Failed to get HTTP router for port %d"), Port);
		return;
	}

	// Register routes
	HttpRouter->BindRoute(FHttpPath(TEXT("/api/stream")), EHttpServerRequestVerbs::VERB_GET,
		FHttpRequestHandler::CreateUObject(this, &UNLTWebServerSubsystem::HandleStreamRequest));
	HttpRouter->BindRoute(FHttpPath(TEXT("/api/scene")), EHttpServerRequestVerbs::VERB_GET,
		FHttpRequestHandler::CreateUObject(this, &UNLTWebServerSubsystem::HandleSceneRequest));
	HttpRouter->BindRoute(FHttpPath(TEXT("/api/status")), EHttpServerRequestVerbs::VERB_GET,
		FHttpRequestHandler::CreateUObject(this, &UNLTWebServerSubsystem::HandleStatusRequest));
	HttpRouter->BindRoute(FHttpPath(TEXT("/api/control")), EHttpServerRequestVerbs::VERB_POST,
		FHttpRequestHandler::CreateUObject(this, &UNLTWebServerSubsystem::HandleControlRequest));

	// OPTIONS for CORS
	auto CORSHandler = FHttpRequestHandler::CreateLambda([](const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete) -> bool {
		TUniquePtr<FHttpServerResponse> Response = MakeUnique<FHttpServerResponse>();
		Response->Headers.Add(TEXT("Access-Control-Allow-Origin"), {TEXT("*")});
		Response->Headers.Add(TEXT("Access-Control-Allow-Methods"), {TEXT("GET, POST, OPTIONS")});
		Response->Headers.Add(TEXT("Access-Control-Allow-Headers"), {TEXT("Content-Type")});
		OnComplete(MoveTemp(Response));
		return true;
	});

	HttpRouter->BindRoute(FHttpPath(TEXT("/api/stream")), EHttpServerRequestVerbs::VERB_OPTIONS, CORSHandler);
	HttpRouter->BindRoute(FHttpPath(TEXT("/api/scene")), EHttpServerRequestVerbs::VERB_OPTIONS, CORSHandler);
	HttpRouter->BindRoute(FHttpPath(TEXT("/api/status")), EHttpServerRequestVerbs::VERB_OPTIONS, CORSHandler);
	HttpRouter->BindRoute(FHttpPath(TEXT("/api/control")), EHttpServerRequestVerbs::VERB_OPTIONS, CORSHandler);

	HttpModule.StartAllListeners();
	bRunning = true;

	UE_LOG(LogNLTWebServer, Log, TEXT("Server started on port %d"), Port);
}

void UNLTWebServerSubsystem::StopServer()
{
	if (HttpRouter.IsValid())
	{
		HttpRouter.Reset();
	}
	bRunning = false;
	UE_LOG(LogNLTWebServer, Log, TEXT("Server stopped"));
}

bool UNLTWebServerSubsystem::HandleStreamRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)
{
	TUniquePtr<FHttpServerResponse> Response = MakeUnique<FHttpServerResponse>();
	Response->Headers.Add(TEXT("Content-Type"), {TEXT("text/event-stream")});
	Response->Headers.Add(TEXT("Cache-Control"), {TEXT("no-cache")});
	Response->Headers.Add(TEXT("Connection"), {TEXT("keep-alive")});
	Response->Headers.Add(TEXT("Access-Control-Allow-Origin"), {TEXT("*")});

	FString SnapshotJson = JsonToStr(BuildSnapshotObject());
	FString EventData = FString::Printf(TEXT("{\"snapshot\":%s,\"events\":[]}"), *SnapshotJson);
	FString SSEData = FString::Printf(TEXT("event: init\ndata: %s\n\n"), *EventData);
	FTCHARToUTF8 Converter(*SSEData);
	Response->Body = TArray<uint8>((const uint8*)Converter.Get(), Converter.Length());

	OnComplete(MoveTemp(Response));
	return true;
}

bool UNLTWebServerSubsystem::HandleSceneRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)
{
	FString SceneJson = BuildSceneJson();
	TUniquePtr<FHttpServerResponse> Response = MakeUnique<FHttpServerResponse>();
	Response->Headers.Add(TEXT("Content-Type"), {TEXT("application/json")});
	Response->Headers.Add(TEXT("Access-Control-Allow-Origin"), {TEXT("*")});
	FTCHARToUTF8 Converter(*SceneJson);
	Response->Body = TArray<uint8>((const uint8*)Converter.Get(), Converter.Length());
	OnComplete(MoveTemp(Response));
	return true;
}

bool UNLTWebServerSubsystem::HandleStatusRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)
{
	FString StatusJson = BuildStatusJson();
	TUniquePtr<FHttpServerResponse> Response = MakeUnique<FHttpServerResponse>();
	Response->Headers.Add(TEXT("Content-Type"), {TEXT("application/json")});
	Response->Headers.Add(TEXT("Access-Control-Allow-Origin"), {TEXT("*")});
	FTCHARToUTF8 Converter(*StatusJson);
	Response->Body = TArray<uint8>((const uint8*)Converter.Get(), Converter.Length());
	OnComplete(MoveTemp(Response));
	return true;
}

bool UNLTWebServerSubsystem::HandleControlRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)
{
	FString BodyStr;
	for (uint8 Byte : Request.Body)
	{
		BodyStr += (TCHAR)Byte;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);

	FString Action;
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		JsonObject->TryGetStringField(TEXT("action"), Action);
	}

	FString ResultJson = TEXT("{\"ok\":true}");

	UWorld* World = GetSimulationWorld();
	UNLTSimulationSubsystem* SimSub = World ? World->GetSubsystem<UNLTSimulationSubsystem>() : nullptr;

	if (Action == TEXT("pause"))
	{
		if (SimSub) SimSub->PauseSimulation();
	}
	else if (Action == TEXT("resume"))
	{
		if (SimSub) SimSub->ResumeSimulation();
	}
	else if (Action == TEXT("step"))
	{
		if (SimSub) SimSub->StepTick();
	}
	else if (Action == TEXT("toggle"))
	{
		if (SimSub)
		{
			if (SimSub->IsRunning()) SimSub->PauseSimulation();
			else SimSub->ResumeSimulation();
		}
	}
	else if (Action == TEXT("pace"))
	{
		float NewPace = 1.0f;
		JsonObject->TryGetNumberField(TEXT("pace"), NewPace);
		if (SimSub) SimSub->SetSimulationRate(NewPace);
	}
	else if (Action == TEXT("assign_scenario"))
	{
		FString AgentId, ScenarioId;
		JsonObject->TryGetStringField(TEXT("agent_id"), AgentId);
		JsonObject->TryGetStringField(TEXT("scenario_id"), ScenarioId);
	}
	else if (Action == TEXT("reset"))
	{
	}

	TUniquePtr<FHttpServerResponse> Response = MakeUnique<FHttpServerResponse>();
	Response->Headers.Add(TEXT("Content-Type"), {TEXT("application/json")});
	Response->Headers.Add(TEXT("Access-Control-Allow-Origin"), {TEXT("*")});
	FTCHARToUTF8 Converter(*ResultJson);
	Response->Body = TArray<uint8>((const uint8*)Converter.Get(), Converter.Length());
	OnComplete(MoveTemp(Response));
	return true;
}

TSharedPtr<FJsonObject> UNLTWebServerSubsystem::BuildSnapshotObject()
{
	UWorld* World = GetSimulationWorld();
	auto* SimSub = World ? World->GetSubsystem<UNLTSimulationSubsystem>() : nullptr;
	auto* ClockSub = World ? World->GetSubsystem<UNLTSimulationClockSubsystem>() : nullptr;

	TSharedPtr<FJsonObject> SnapshotObject = MakeShareable(new FJsonObject());
	SnapshotObject->SetStringField(TEXT("contract_version"), TEXT("nlt.world-engine.v1"));
	SnapshotObject->SetStringField(TEXT("snapshot_id"), FString::Printf(TEXT("snapshot-%d"), RequestCounter++));

	// Simulation state
	TSharedPtr<FJsonObject> SimObject = MakeShareable(new FJsonObject());
	SimObject->SetStringField(TEXT("simulation_id"), TEXT("ue5-sim"));
	SimObject->SetStringField(TEXT("state"), SimSub && SimSub->IsRunning() ? TEXT("running") : TEXT("paused"));
	SimObject->SetNumberField(TEXT("tick"), SimSub ? SimSub->GetCurrentTick() : 0);
	SimObject->SetNumberField(TEXT("sim_time"), ClockSub ? (ClockSub->GetWorldTimeSeconds() / 60.0) : 0.0);
	SimObject->SetNumberField(TEXT("seed"), 42);
	SimObject->SetNumberField(TEXT("pace"), SimSub ? SimSub->GetSimulationRate() : 1.0f);
	SnapshotObject->SetObjectField(TEXT("simulation"), SimObject);

	// Avatars - get from Mass Entity system
	TSharedPtr<FJsonObject> AvatarsObject = MakeShareable(new FJsonObject());
	auto* MassSub = World ? World->GetSubsystem<UMassEntitySubsystem>() : nullptr;
	if (MassSub)
	{
		FMassEntityManager& EntityManager = MassSub->GetMutableEntityManager();
		FMassEntityQuery Query;
		Query.AddRequirement<FNLTAgentIdentityFragment>(EMassFragmentAccess::ReadOnly);
		Query.AddRequirement<FNLTAgentLocationFragment>(EMassFragmentAccess::ReadOnly);
		Query.AddRequirement<FNLTAgentCognitiveFragment>(EMassFragmentAccess::ReadOnly);

		FMassExecutionContext ExecutionContext(EntityManager);
		Query.ForEachEntityChunk(EntityManager, ExecutionContext, [this, &AvatarsObject](FMassExecutionContext& Context)
		{
			const TArrayView<const FNLTAgentIdentityFragment>& Identities = Context.GetFragmentView<FNLTAgentIdentityFragment>();
			const TArrayView<const FNLTAgentLocationFragment>& Locations = Context.GetFragmentView<FNLTAgentLocationFragment>();
			const TArrayView<const FNLTAgentCognitiveFragment>& Cognitives = Context.GetFragmentView<FNLTAgentCognitiveFragment>();

			for (int32 i = 0; i < Context.GetNumEntities(); ++i)
			{
				const FNLTAgentIdentityFragment& Identity = Identities[i];
				if (Identity.Role == ENLTAgentRole::Avatar)
				{
					TSharedPtr<FJsonObject> AvatarObject = MakeShareable(new FJsonObject());
					AvatarObject->SetStringField(TEXT("id"), Identity.AgentId.ToString());
					AvatarObject->SetStringField(TEXT("name"), Identity.DisplayName.ToString());
					AvatarObject->SetStringField(TEXT("trait"), TEXT("ADHD Trait"));
					AvatarObject->SetStringField(TEXT("state"), TEXT("working"));
					AvatarObject->SetStringField(TEXT("emotional_state"), TEXT("neutral"));

					const FNLTAgentCognitiveFragment& Cognitive = Cognitives[i];
					TSharedPtr<FJsonObject> MetricsObject = MakeShareable(new FJsonObject());
					MetricsObject->SetNumberField(TEXT("focus"), Cognitive.Focus);
					MetricsObject->SetNumberField(TEXT("cognitive_load"), Cognitive.CognitiveLoad);
					MetricsObject->SetNumberField(TEXT("stress"), Cognitive.Stress);
					MetricsObject->SetNumberField(TEXT("burnout_risk"), Cognitive.Burnout);
					MetricsObject->SetNumberField(TEXT("independence"), Cognitive.Independence);
					MetricsObject->SetNumberField(TEXT("fusion_readiness"), Cognitive.FusionReady);
					MetricsObject->SetNumberField(TEXT("success_rate"), Cognitive.SuccessRate);
					AvatarObject->SetObjectField(TEXT("metrics"), MetricsObject);

					const FNLTAgentLocationFragment& Location = Locations[i];
					TSharedPtr<FJsonObject> PosObject = MakeShareable(new FJsonObject());
					PosObject->SetStringField(TEXT("room_id"), TEXT("workplace"));
					PosObject->SetNumberField(TEXT("x"), Location.Position.X);
					PosObject->SetNumberField(TEXT("y"), Location.Position.Y);
					PosObject->SetNumberField(TEXT("target_x"), Location.TargetPosition.X);
					PosObject->SetNumberField(TEXT("target_y"), Location.TargetPosition.Y);
					PosObject->SetStringField(TEXT("facing"), TEXT("south"));
					AvatarObject->SetObjectField(TEXT("position"), PosObject);

					TSharedPtr<FJsonObject> CountersObject = MakeShareable(new FJsonObject());
					CountersObject->SetNumberField(TEXT("minutes_focused"), 0.0f);
					CountersObject->SetNumberField(TEXT("false_starts"), 0);
					CountersObject->SetNumberField(TEXT("interventions"), 0);
					CountersObject->SetNumberField(TEXT("successes"), 0);
					CountersObject->SetNumberField(TEXT("failures"), 0);
					AvatarObject->SetObjectField(TEXT("counters"), CountersObject);

					TSharedPtr<FJsonObject> ExtObject = MakeShareable(new FJsonObject());
					ExtObject->SetNumberField(TEXT("hue"), 200.0f);
					ExtObject->SetStringField(TEXT("tag"), TEXT("SA"));
					AvatarObject->SetObjectField(TEXT("extensions"), ExtObject);

					AvatarsObject->SetObjectField(Identity.AgentId.ToString(), AvatarObject);
				}
			}
		});
	}
	SnapshotObject->SetObjectField(TEXT("avatars"), AvatarsObject);

	// Entities
	TSharedPtr<FJsonObject> EntitiesObject = MakeShareable(new FJsonObject());
	SnapshotObject->SetObjectField(TEXT("entities"), EntitiesObject);

	// Extensions
	TSharedPtr<FJsonObject> ExtObject = MakeShareable(new FJsonObject());
	ExtObject->SetStringField(TEXT("scene_id"), TEXT("ue5_world"));
	auto* ClockSub2 = World ? World->GetSubsystem<UNLTSimulationClockSubsystem>() : nullptr;
	if (ClockSub2)
	{
		float TimeOfDay = ClockSub2->GetTimeOfDayHours();
		int32 Days = ClockSub2->GetDaysElapsed();
		int32 Hours = FMath::FloorToInt(TimeOfDay);
		int32 Minutes = FMath::FloorToInt((TimeOfDay - Hours) * 60.0f);
		FString IsoTime = FString::Printf(TEXT("2026-01-%02dT%02d:%02d:00"), Days + 1, Hours, Minutes);
		ExtObject->SetStringField(TEXT("simulation_time_iso"), IsoTime);
	}
	SnapshotObject->SetObjectField(TEXT("extensions"), ExtObject);

	return SnapshotObject;
}

FString UNLTWebServerSubsystem::BuildSceneJson()
{
	TSharedPtr<FJsonObject> SceneObject = MakeShareable(new FJsonObject());
	SceneObject->SetStringField(TEXT("contract_version"), TEXT("nlt.world-engine.v1"));
	SceneObject->SetStringField(TEXT("scene_id"), TEXT("ue5_world"));

	TSharedPtr<FJsonObject> GridObject = MakeShareable(new FJsonObject());
	GridObject->SetNumberField(TEXT("width"), 100);
	GridObject->SetNumberField(TEXT("height"), 100);
	SceneObject->SetObjectField(TEXT("grid"), GridObject);

	TArray<TSharedPtr<FJsonValue>> RoomsArray;
	TArray<FName> RoomNames = {TEXT("workplace"), TEXT("meeting"), TEXT("home"), TEXT("lounge"), TEXT("office")};
	for (const FName& RoomName : RoomNames)
	{
		TSharedPtr<FJsonObject> RoomObject = MakeShareable(new FJsonObject());
		RoomObject->SetStringField(TEXT("id"), RoomName.ToString());
		RoomObject->SetStringField(TEXT("name"), RoomName.ToString());
		RoomsArray.Add(MakeShareable(new FJsonValueObject(RoomObject)));
	}
	SceneObject->SetArrayField(TEXT("rooms"), RoomsArray);

	return JsonToStr(SceneObject);
}

FString UNLTWebServerSubsystem::BuildStatusJson()
{
	UWorld* World = GetSimulationWorld();
	auto* SimSub = World ? World->GetSubsystem<UNLTSimulationSubsystem>() : nullptr;

	TSharedPtr<FJsonObject> StatusObject = MakeShareable(new FJsonObject());
	StatusObject->SetBoolField(TEXT("running"), SimSub ? SimSub->IsRunning() : false);
	StatusObject->SetNumberField(TEXT("pace"), SimSub ? SimSub->GetSimulationRate() : 1.0f);
	StatusObject->SetStringField(TEXT("snapshot"), JsonToStr(BuildSnapshotObject()));

	return JsonToStr(StatusObject);
}

FString UNLTWebServerSubsystem::BuildEventsJson()
{
	FScopeLock Lock(&EventMutex);

	TArray<TSharedPtr<FJsonValue>> EventsArray;
	for (const FString& EventStr : EventBuffer)
	{
		EventsArray.Add(MakeShareable(new FJsonValueString(EventStr)));
	}

	TSharedPtr<FJsonObject> EventsObject = MakeShareable(new FJsonObject());
	EventsObject->SetArrayField(TEXT("events"), EventsArray);

	return JsonToStr(EventsObject);
}

FString UNLTWebServerSubsystem::JsonToStr(TSharedPtr<FJsonObject> Obj)
{
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(Obj.ToSharedRef(), Writer);
	return OutputString;
}

void UNLTWebServerSubsystem::BroadcastEvent(const FString& EventType, const FString& Message, const FString& SourceId, const FString& SourceType)
{
	FScopeLock Lock(&EventMutex);

	TSharedPtr<FJsonObject> EventObject = MakeShareable(new FJsonObject());
	EventObject->SetStringField(TEXT("event_type"), EventType);
	EventObject->SetStringField(TEXT("message"), Message);
	EventObject->SetStringField(TEXT("source_id"), SourceId);
	EventObject->SetStringField(TEXT("source_type"), SourceType);

	FString EventStr = JsonToStr(EventObject);

	EventBuffer.Add(EventStr);
	if (EventBuffer.Num() > EventBufferSize)
	{
		EventBuffer.RemoveAt(0);
	}
}
