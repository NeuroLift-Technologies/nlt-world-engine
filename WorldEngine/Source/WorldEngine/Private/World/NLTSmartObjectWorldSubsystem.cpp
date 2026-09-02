#include "World/NLTSmartObjectWorldSubsystem.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTSmartObjectWorldSubsystem);

void UNLTSmartObjectWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogNLTSmartObjectWorldSubsystem, Log, TEXT("SmartObject world subsystem initialized"));
}

void UNLTSmartObjectWorldSubsystem::Deinitialize()
{
    Locations.Empty();
    Super::Deinitialize();
}

void UNLTSmartObjectWorldSubsystem::RegisterLocation(AActor* Actor, const FNLTWorldLocation& Location)
{
    if (!Actor) return;
    Locations.Add(Actor, Location);
    UE_LOG(LogNLTSmartObjectWorldSubsystem, Log, TEXT("Registered location: %s (Type: %s)"),
        *Location.DisplayName, *Location.LocationType.ToString());
}

void UNLTSmartObjectWorldSubsystem::UnregisterLocation(AActor* Actor)
{
    Locations.Remove(Actor);
}

void UNLTSmartObjectWorldSubsystem::ReserveLocation(AActor* Actor, FName AgentId)
{
    FNLTWorldLocation* Location = Locations.Find(Actor);
    if (Location && !Location->bIsOccupied && Location->CurrentOccupants.Num() < Location->MaxOccupants)
    {
        Location->bIsOccupied = true;
        Location->CurrentOccupants.Add(AgentId);
    }
}

void UNLTSmartObjectWorldSubsystem::ReleaseLocation(AActor* Actor, FName AgentId)
{
    FNLTWorldLocation* Location = Locations.Find(Actor);
    if (Location)
    {
        Location->CurrentOccupants.Remove(AgentId);
        if (Location->CurrentOccupants.Num() == 0)
        {
            Location->bIsOccupied = false;
        }
    }
}

TArray<FNLTWorldLocation> UNLTSmartObjectWorldSubsystem::FindLocationsByActivity(FName Activity) const
{
    TArray<FNLTWorldLocation> Result;
    for (const auto& Pair : Locations)
    {
        if (Pair.Value.AvailableActivities.Contains(Activity))
        {
            Result.Add(Pair.Value);
        }
    }
    return Result;
}

TArray<FNLTWorldLocation> UNLTSmartObjectWorldSubsystem::FindLocationsByType(FName LocationType) const
{
    TArray<FNLTWorldLocation> Result;
    for (const auto& Pair : Locations)
    {
        if (Pair.Value.LocationType == LocationType)
        {
            Result.Add(Pair.Value);
        }
    }
    return Result;
}

TArray<FNLTWorldLocation> UNLTSmartObjectWorldSubsystem::FindLocationsByNeed(ENLTAgentNeed Need) const
{
    TArray<FNLTWorldLocation> Result;
    for (const auto& Pair : Locations)
    {
        if (MatchesNeed(Pair.Value, Need))
        {
            Result.Add(Pair.Value);
        }
    }
    return Result;
}

bool UNLTSmartObjectWorldSubsystem::FindBestLocationForAgent(FName AgentId, ENLTAgentNeed Need, FNLTWorldLocation& OutLocation) const
{
    const FNLTWorldLocation* BestLocation = nullptr;
    float BestScore = -1.0f;

    for (const auto& Pair : Locations)
    {
        if (MatchesNeed(Pair.Value, Need) && !Pair.Value.bIsOccupied)
        {
            float Score = ScoreLocation(Pair.Value, Need);
            if (Score > BestScore)
            {
                BestScore = Score;
                BestLocation = &Pair.Value;
            }
        }
    }

    if (BestLocation)
    {
        OutLocation = *BestLocation;
        return true;
    }
    return false;
}

bool UNLTSmartObjectWorldSubsystem::MatchesNeed(const FNLTWorldLocation& Location, ENLTAgentNeed Need) const
{
    switch (Need)
    {
    case ENLTAgentNeed::Quiet:
        return Location.NoiseLevel < 0.3f;
    case ENLTAgentNeed::Social:
        return Location.SocialDensity > 0.6f;
    case ENLTAgentNeed::Rest:
        return Location.Privacy > 0.5f;
    case ENLTAgentNeed::Privacy:
        return Location.Privacy > 0.7f;
    case ENLTAgentNeed::Stimulation:
        return Location.SocialDensity > 0.5f || Location.NoiseLevel > 0.5f;
    default:
        return false;
    }
}

float UNLTSmartObjectWorldSubsystem::ScoreLocation(const FNLTWorldLocation& Location, ENLTAgentNeed Need) const
{
    float Score = 0.0f;
    switch (Need)
    {
    case ENLTAgentNeed::Quiet:
        Score = 1.0f - Location.NoiseLevel;
        break;
    case ENLTAgentNeed::Social:
        Score = Location.SocialDensity;
        break;
    case ENLTAgentNeed::Rest:
        Score = Location.Privacy;
        break;
    case ENLTAgentNeed::Privacy:
        Score = Location.Privacy;
        break;
    case ENLTAgentNeed::Stimulation:
        Score = Location.SocialDensity + Location.NoiseLevel * 0.5f;
        break;
    default:
        break;
    }
    return Score;
}
