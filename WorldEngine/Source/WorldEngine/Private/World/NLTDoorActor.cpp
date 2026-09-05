// NLTDoorActor.cpp
#include "World/NLTDoorActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

ANLTDoorActor::ANLTDoorActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the door mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	// Create the interaction volume
	InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
	InteractionVolume->SetupAttachment(RootComponent);
	InteractionVolume->SetBoxExtent(FVector(150.0f, 100.0f, 200.0f));
	InteractionVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	OverlappingPlayer = nullptr;
}

void ANLTDoorActor::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap events on the interaction volume
	if (InteractionVolume)
	{
		InteractionVolume->OnComponentBeginOverlap.AddDynamic(this, &ANLTDoorActor::OnOverlapBegin);
		InteractionVolume->OnComponentEndOverlap.AddDynamic(this, &ANLTDoorActor::OnOverlapEnd);
	}
}

void ANLTDoorActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								   bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	// Check if this is a player character
	if (Cast<ACharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("NLTDoor: Player entered range of door '%s'"), *GetName());
		OverlappingPlayer = OtherActor;
	}
}

void ANLTDoorActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	if (Cast<ACharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("NLTDoor: Player left range of door '%s'"), *GetName());
		OverlappingPlayer = nullptr;
	}
}
