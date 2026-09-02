#include "Roles/NLTFusionRoleManager.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTFusionRoleManager);

void UNLTFusionRoleManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogNLTFusionRoleManager, Log, TEXT("Fusion role manager initialized"));
}

void UNLTFusionRoleManager::Deinitialize()
{
    Pairs.Empty();
    Advocates.Empty();
    Super::Deinitialize();
}

FName UNLTFusionRoleManager::CreatePair(FName AvatarId, FName AideId)
{
    FName PairId = FName(*FString::Printf(TEXT("Pair_%s_%s"), *AvatarId.ToString(), *AideId.ToString()));

    FNLTFusionPair Pair;
    Pair.PairId = PairId;
    Pair.AvatarId = AvatarId;
    Pair.AideId = AideId;
    Pair.BondStrength = 0.0f;
    Pair.FusionReadiness = 0.0f;
    Pair.AvatarState = ENLTFusionRoleState::Active;
    Pair.AideState = ENLTFusionRoleState::Coaching;

    Pairs.Add(PairId, Pair);
    UE_LOG(LogNLTFusionRoleManager, Log, TEXT("Created fusion pair: %s"), *PairId.ToString());

    return PairId;
}

void UNLTFusionRoleManager::DestroyPair(FName PairId)
{
    Pairs.Remove(PairId);
}

bool UNLTFusionRoleManager::GetPair(FName PairId, FNLTFusionPair& OutPair) const
{
    const FNLTFusionPair* Found = Pairs.Find(PairId);
    if (Found)
    {
        OutPair = *Found;
        return true;
    }
    return false;
}

FName UNLTFusionRoleManager::CreateAdvocate(FName AdvocateId)
{
    FNLTAdvocate Advocate;
    Advocate.AdvocateId = AdvocateId;
    Advocate.State = ENLTFusionRoleState::Monitoring;
    Advocate.MaxMonitoringCapacity = 5;

    Advocates.Add(AdvocateId, Advocate);
    UE_LOG(LogNLTFusionRoleManager, Log, TEXT("Created advocate: %s"), *AdvocateId.ToString());

    return AdvocateId;
}

void UNLTFusionRoleManager::AssignPairToAdvocate(FName PairId, FName AdvocateId)
{
    FNLTAdvocate* Advocate = Advocates.Find(AdvocateId);
    if (Advocate && Advocate->MonitoredPairs.Num() < Advocate->MaxMonitoringCapacity)
    {
        Advocate->MonitoredPairs.Add(PairId);
    }
}

void UNLTFusionRoleManager::Tick(float DeltaTime)
{
    for (auto& Pair : Pairs)
    {
        UpdatePair(Pair.Value, DeltaTime);
    }

    for (auto& Advocate : Advocates)
    {
        UpdateAdvocate(Advocate.Value, DeltaTime);
    }
}

void UNLTFusionRoleManager::UpdatePair(FNLTFusionPair& Pair, float DeltaTime)
{
    if (Pair.AideState == ENLTFusionRoleState::Coaching && Pair.AvatarState == ENLTFusionRoleState::Active)
    {
        Pair.BondStrength = FMath::Min(1.0f, Pair.BondStrength + DeltaTime * 0.01f);
        Pair.FusionReadiness = FMath::Min(1.0f, Pair.FusionReadiness + DeltaTime * 0.005f);
    }

    CheckFusionReadiness(Pair);
}

void UNLTFusionRoleManager::UpdateAdvocate(FNLTAdvocate& Advocate, float DeltaTime)
{
    if (Advocate.State == ENLTFusionRoleState::Monitoring)
    {
        for (const FName& PairId : Advocate.MonitoredPairs)
        {
            FNLTFusionPair* Pair = Pairs.Find(PairId);
            if (Pair && Pair->FusionReadiness > 0.8f)
            {
                UE_LOG(LogNLTFusionRoleManager, Log, TEXT("Advocate %s: Pair %s ready for fusion!"),
                    *Advocate.AdvocateId.ToString(), *PairId.ToString());
            }
        }
    }
}

void UNLTFusionRoleManager::CheckFusionReadiness(FNLTFusionPair& Pair)
{
    if (Pair.BondStrength > 0.8f && Pair.FusionReadiness > 0.8f)
    {
        UE_LOG(LogNLTFusionRoleManager, Log, TEXT("Pair %s is ready for fusion!"), *Pair.PairId.ToString());
    }
}
