// AvatarAIController.cpp
#include "Agents/AvatarAIController.h"
#include "Agents/NLTLLMBridge.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

// Maximum relative step a single move_by command may request (world units).
// Keeps the LLM from teleporting avatars across the map in one command.
static constexpr float MaxLLMStepDistance = 2000.0f;

AAvatarAIController::AAvatarAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    WanderRadius = 1000.0f;
    WaitTimeMin = 2.0f;
    WaitTimeMax = 5.0f;
    AcceptanceRadius = 50.0f;
    bIsWaiting = false;
    bLearningAgentsActive = false;
    bLLMControlActive = false;

    // Create the LLM bridge component
    LLMBridge = CreateDefaultSubobject<UNLTLLMBridge>(TEXT("LLMBridge"));
    LLMBridge->RequestCooldown = 3.0f;
}

void AAvatarAIController::SetLLMControlActive(bool bActive)
{
    if (bLLMControlActive == bActive)
    {
        return;
    }

    bLLMControlActive = bActive;
    if (bActive)
    {
        // LLM takes over: stop autonomous wandering/timers immediately,
        // and set up the bridge callback for incoming LLM movement commands.
        StopMovement();
        GetWorldTimerManager().ClearTimer(WaitTimer);
        bIsWaiting = false;

        // Bind the LLM response handler (raw function pointer binding)
        if (LLMBridge)
        {
            LLMBridge->OnLLMResponse.AddDynamic(this, &AAvatarAIController::HandleLLMResponse);
        }
    }
    else
    {
        // LLM relinquishes control: resume autonomous behavior.
        if (LLMBridge)
        {
            LLMBridge->OnLLMResponse.RemoveAll(this);
        }
        Wander();
    }
}

void AAvatarAIController::SetLearningAgentsActive(bool bActive)
{
    bLearningAgentsActive = bActive;
    if (bActive)
    {
        // Stop wandering when LA takes control
        StopMovement();
        GetWorldTimerManager().ClearTimer(WaitTimer);
    }
    else
    {
        // Resume wandering when LA relinquishes control
        Wander();
    }
}

bool AAvatarAIController::ExecuteLLMCommand(const FString& Command, const TSharedPtr<FJsonObject>& Args, FString& OutMessage)
{
    const FString Cmd = Command.TrimStartAndEnd().ToLower();
    OutMessage.Reset();

    // Control handoff commands that are valid without a possessed pawn.
    if (Cmd == TEXT("release"))
    {
        StopMovement();
        SetLLMControlActive(false);
        OutMessage = TEXT("released: LLM control off, autonomous wander resumed");
        return true;
    }
    if (Cmd == TEXT("stop"))
    {
        StopMovement();
        OutMessage = TEXT("stopped");
        return true;
    }

    APawn* MyPawn = GetPawn();
    if (!MyPawn)
    {
        OutMessage = TEXT("controller has no possessed pawn");
        return false;
    }

    if (Cmd == TEXT("move_to") || Cmd == TEXT("move_by") || Cmd == TEXT("face_towards"))
    {
        float X = 0.0f;
        float Y = 0.0f;
        const FVector Origin = MyPawn->GetActorLocation();

        if (Cmd == TEXT("move_to") || Cmd == TEXT("face_towards"))
        {
            if (!Args.IsValid() || !Args->TryGetNumberField(TEXT("x"), X) || !Args->TryGetNumberField(TEXT("y"), Y))
            {
                OutMessage = TEXT("move_to/face_towards requires numeric x and y args");
                return false;
            }
        }
        else // move_by: relative offset, clamped radially to MaxLLMStepDistance.
        {
            if (!Args.IsValid() || !Args->TryGetNumberField(TEXT("dx"), X) || !Args->TryGetNumberField(TEXT("dy"), Y))
            {
                OutMessage = TEXT("move_by requires numeric dx and dy args");
                return false;
            }
            //~ FIX (PR #43 review): radial clamp — per-axis clamp allowed
            //~ (2000,2000) ~= 2828uu, defeating the max-step guard.
            FVector2D Offset(X, Y);
            if (Offset.Size() > MaxLLMStepDistance)
            {
                Offset = Offset.GetSafeNormal() * MaxLLMStepDistance;
                X = Offset.X;
                Y = Offset.Y;
            }
            X += Origin.X;
            Y += Origin.Y;
        }

        const FVector Destination(X, Y, Origin.Z);

        if (Cmd == TEXT("face_towards"))
        {
            const FVector Direction = (Destination - Origin).GetSafeNormal();
            SetControlRotation(Direction.Rotation());
            SetFocalPoint(Destination);
            OutMessage = FString::Printf(TEXT("facing (%f, %f)"), Destination.X, Destination.Y);
            return true;
        }

        //~ FIX (PR #43 review): validate BEFORE SetLLMControlActive so a
        //~ rejected command can't flip control state, and apply the anti-echo
        //~ minimum-distance guard to move_by as well as move_to.
        //~ (A stuck LLM emitting dx=0,dy=0 used to loop forever.)
        static constexpr float MinLLMStepDistSq = 2500.0f; // 50uu — "didn't move"
        const float DistSq = FVector::DistSquared2D(Destination, Origin);
        if (DistSq < MinLLMStepDistSq)
        {
            OutMessage = FString::Printf(TEXT("%s target too close to current position"), *Cmd);
            return false;
        }

        // move_to / move_by: nav path-following via the AI controller.
        SetLLMControlActive(true);

        const EPathFollowingRequestResult::Type Result = MoveToLocation(Destination, AcceptanceRadius, true, true, true, true);
        if (Result == EPathFollowingRequestResult::Failed)
        {
            OutMessage = FString::Printf(TEXT("move failed: destination (%f, %f) unreachable"), Destination.X, Destination.Y);
            return false;
        }
        OutMessage = FString::Printf(TEXT("moving to (%f, %f)"), Destination.X, Destination.Y);
        return true;
    }

    if (Cmd == TEXT("move_to_object"))
    {
        FString ObjectId;
        if (!Args.IsValid() || !Args->TryGetStringField(TEXT("object_id"), ObjectId) || ObjectId.IsEmpty())
        {
            OutMessage = TEXT("move_to_object requires a string object_id arg");
            return false;
        }

        AActor* Target = nullptr;
        for (TActorIterator<AActor> It(GetWorld()); It; ++It)
        {
            if (It->GetName() == ObjectId)
            {
                Target = *It;
                break;
            }
        }
        if (!Target)
        {
            OutMessage = FString::Printf(TEXT("object not found: %s"), *ObjectId);
            return false;
        }

        SetLLMControlActive(true);
        const EPathFollowingRequestResult::Type Result = MoveToActor(Target, AcceptanceRadius, true, true, true);
        if (Result == EPathFollowingRequestResult::Failed)
        {
            OutMessage = FString::Printf(TEXT("move failed: %s unreachable"), *ObjectId);
            return false;
        }
        OutMessage = FString::Printf(TEXT("moving to object %s"), *ObjectId);
        return true;
    }

    OutMessage = FString::Printf(TEXT("unknown command: %s"), *Command);
    return false;
}

void AAvatarAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (InPawn)
    {
        HomeLocation = InPawn->GetActorLocation();
        // Only start wandering if neither LA nor the LLM is in control
        if (!bLearningAgentsActive && !bLLMControlActive)
        {
            Wander();
        }
    }
}

void AAvatarAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // When LLM control is active and the bridge is ready, request the next
    // movement command asynchronously. The bridge has its own cooldown timer
    // so we won't flood the LLM.
    if (bLLMControlActive && LLMBridge && LLMBridge->IsReady())
    {
        RequestLLMMovementCommand();
    }
}

void AAvatarAIController::HandleLLMResponse(const FString& JsonResponse)
{
    // Parse the JSON the LLM returned and dispatch the command.
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonResponse);
    TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);

    if (!FJsonSerializer::Deserialize(Reader, JsonObj) || !JsonObj.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("AvatarAIController: Failed to parse LLM JSON: %s"), *JsonResponse);
        return;
    }

    FString Command;
    if (!JsonObj->TryGetStringField(TEXT("command"), Command) || Command.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("AvatarAIController: LLM response missing command field"));
        return;
    }

    FString OutMessage;
    if (!ExecuteLLMCommand(Command, JsonObj, OutMessage))
    {
        UE_LOG(LogTemp, Warning, TEXT("AvatarAIController: LLM command failed: %s"), *OutMessage);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("AvatarAIController: LLM command OK: %s"), *OutMessage);
    }
}

void AAvatarAIController::RequestLLMMovementCommand()
{
    APawn* MyPawn = GetPawn();
    if (!MyPawn || !LLMBridge) return;

    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(MyPawn);
    if (!Avatar) return;

    // Gather cognitive state from the avatar's component
    TMap<FString, float> CognitiveStateMap;
    if (Avatar->CognitiveState)
    {
        TArray<float> StateValues = Avatar->CognitiveState->GetObservationValues();
        static const TArray<FName> StateNames = {
            TEXT("boredom"), TEXT("curiosity"), TEXT("focus"),
            TEXT("stress"), TEXT("burnout"), TEXT("emotional_state"),
            TEXT("success_rate")
        };
        for (int32 i = 0; i < StateValues.Num() && i < StateNames.Num(); ++i)
        {
            CognitiveStateMap.Add(StateNames[i].ToString(), StateValues[i]);
        }
    }

    const FVector Location = MyPawn->GetActorLocation();
    const FVector Velocity = MyPawn->GetVelocity();

    LLMBridge->RequestMovementCommand(
        MyPawn->GetName(),
        Location,
        Velocity,
        CognitiveStateMap,
        TEXT("Choose a new destination nearby that you haven't visited recently. Respond with move_to, move_by, face_towards, or stop."),
        TEXT("You are in a simulated training environment with doors leading to Personal, Social, and Academic areas. There is a NavMeshBoundsVolume covering the level.")
    );
}

void AAvatarAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    // Only continue wandering if neither LA nor the LLM is in control.
    if (!bLearningAgentsActive && !bLLMControlActive)
    {
        bIsWaiting = true;
        float WaitTime = FMath::FRandRange(WaitTimeMin, WaitTimeMax);
        GetWorldTimerManager().SetTimer(WaitTimer, this, &AAvatarAIController::Wait, WaitTime, false);
    }
}

void AAvatarAIController::Wander()
{
    // Don't wander if LA or the LLM is controlling
    if (bLearningAgentsActive || bLLMControlActive) return;

    APawn* MyPawn = GetPawn();
    if (!MyPawn) return;

    FVector TargetLocation;
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    
    if (NavSys)
    {
        FNavLocation NavLocation;
        if (NavSys->GetRandomPointInNavigableRadius(HomeLocation, WanderRadius, NavLocation))
        {
            TargetLocation = NavLocation.Location;
        }
        else
        {
            TargetLocation = HomeLocation + FVector(
                FMath::FRandRange(-WanderRadius, WanderRadius),
                FMath::FRandRange(-WanderRadius, WanderRadius),
                0.0f
            );
        }
    }
    else
    {
        TargetLocation = HomeLocation + FVector(
            FMath::FRandRange(-WanderRadius, WanderRadius),
            FMath::FRandRange(-WanderRadius, WanderRadius),
            0.0f
        );
    }

    MoveToLocation(TargetLocation, AcceptanceRadius, true, true, true, true);
}

void AAvatarAIController::Wait()
{
    bIsWaiting = false;
    GetWorldTimerManager().ClearTimer(WaitTimer);
    // Pick next destination
    Wander();
}
