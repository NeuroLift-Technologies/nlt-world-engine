// NLTOpenWorldGameMode.cpp
#include "Scenarios/NLTOpenWorldGameMode.h"
#include "Engine/World.h"

ANLTOpenWorldGameMode::ANLTOpenWorldGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANLTOpenWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Generate the open world (landscape, buildings, vegetation, residents)
	if (UNLTOpenWorldSubsystem* OWS = GetOpenWorldSubsystem())
	{
		if (!OWS->IsWorldGenerated())
		{
			OWS->GenerateOpenWorld(OpenWorldConfig);
			UE_LOG(LogTemp, Log, TEXT("[OpenWorld] Generated open world with seed=%d"), OpenWorldConfig.Seed);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[OpenWorld] NLTOpenWorldSubsystem not available — skipping generation"));
	}
}

UNLTOpenWorldSubsystem* ANLTOpenWorldGameMode::GetOpenWorldSubsystem() const
{
	UWorld* World = GetWorld();
	if (!World) return nullptr;
	return World->GetSubsystem<UNLTOpenWorldSubsystem>();
}
