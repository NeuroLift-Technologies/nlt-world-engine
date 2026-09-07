// NLTDoorActor.cpp
#include "World/NLTDoorActor.h"
#include "Agents/NLTPlayerController.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/Font.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ANLTDoorActor::ANLTDoorActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create a visible placeholder mesh (a tall box shaped like a door)
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	// Use the engine's default cube as a placeholder — scaled tall like a door
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh.Succeeded())
	{
		DoorMesh->SetStaticMesh(CubeMesh.Object);
	}
	DoorMesh->SetRelativeScale3D(FVector(0.5f, 0.1f, 2.0f));  // Thin, tall door shape
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// World-space labels above the door showing its destination level.
	// NOTE: DoorMesh is scaled (0.5, 0.1, 2.0). Each label uses ABSOLUTE unit
	// world scale so the non-uniform parent scale can never distort the text
	// metrics, no matter how the label is rotated to face the player.
	// The Z offset stays in parent space, so it is halved for the parent's
	// 2x vertical scale (70 -> 140cm above door center in world).
	// TextRender glyphs are built in the local YZ plane reading along -Y with
	// the readable face toward local -X, so SetLabelFacing aims -X at the player.
	auto MakeLabel = [this](const TCHAR* SubobjectName)
	{
		UTextRenderComponent* Label = CreateDefaultSubobject<UTextRenderComponent>(SubobjectName);
		Label->SetupAttachment(RootComponent);
		Label->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
		Label->SetUsingAbsoluteScale(true);
		Label->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
		static ConstructorHelpers::FObjectFinder<UFont> DoorFont(TEXT("/Engine/EngineFonts/Roboto"));
		if (DoorFont.Succeeded())
		{
			Label->SetFont(DoorFont.Object);
		}
		Label->SetWorldSize(35.0f);
		Label->SetTextRenderColor(FColor(0, 230, 180));
		Label->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
		Label->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		Label->SetText(FText::FromString(TEXT("PORTAL")));
		Label->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Label->SetCastShadow(false);
		Label->SetHiddenInGame(false);
		return Label;
	};

	DoorLabel = MakeLabel(TEXT("DoorLabel"));
	DoorLabelBack = MakeLabel(TEXT("DoorLabelBack"));

	// Create the interaction volume (larger than the mesh so player can walk into it)
	InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
	InteractionVolume->SetupAttachment(RootComponent);
	InteractionVolume->SetBoxExtent(FVector(120.0f, 260.0f, 140.0f));
	InteractionVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	OverlappingPlayer = nullptr;
}

void ANLTDoorActor::BeginPlay()
{
	Super::BeginPlay();

	// Sync the label text with the display name (set by the spawner before BeginPlay).
	UpdateLabelText();

	// Bind overlap events on the interaction volume
	if (InteractionVolume)
	{
		InteractionVolume->OnComponentBeginOverlap.AddDynamic(this, &ANLTDoorActor::OnOverlapBegin);
		InteractionVolume->OnComponentEndOverlap.AddDynamic(this, &ANLTDoorActor::OnOverlapEnd);
	}
}

void ANLTDoorActor::UpdateLabelText()
{
	if (DoorLabel)
	{
		DoorLabel->SetText(DisplayName);
	}
	if (DoorLabelBack)
	{
		DoorLabelBack->SetText(DisplayName);
	}
}

void ANLTDoorActor::SetLabelFacing(const FVector& FaceDirection)
{
	if (!DoorLabel) return;

	const FVector N = FaceDirection.GetSafeNormal();
	const FVector Up(0.0f, 0.0f, 1.0f);
	// TextRender glyphs read along local -Y, upright along local +Z, with the
	// readable face toward local -X. Aim -X at the player (X' = -N), keep the
	// text upright (Z' = world up), and complete the right-handed basis.
	const FVector X = -N;
	const FVector Z = Up;
	const FVector Y = FVector::CrossProduct(Z, X).GetSafeNormal();
	DoorLabel->SetWorldRotation(FMatrix(X, Y, Z, FVector::ZeroVector).ToQuat().Rotator());

	// Back label faces the opposite way so the destination stays readable
	// from behind the door as well.
	if (DoorLabelBack)
	{
		const FRotator BackRelative(0.0f, 180.0f, 0.0f);
		DoorLabelBack->SetWorldRotation((FMatrix(X, Y, Z, FVector::ZeroVector).ToQuat() * BackRelative.Quaternion()).Rotator());
	}
}

void ANLTDoorActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								   bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	// Accept any Pawn (Character or not) — GameModeBase defaults the player
	// to ADefaultPawn, which is NOT a Character.
	if (APawn* Pawn = Cast<APawn>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("NLTDoor: Player entered range of door '%s' (pawn=%s class=%s)"),
			*GetName(), *Pawn->GetName(), *Pawn->GetClass()->GetName());
		OverlappingPlayer = Pawn;

		// Portal behaviour: the local player travels as soon as they walk in.
		if (UWorld* World = GetWorld())
		{
			if (APlayerController* PC = World->GetFirstPlayerController())
			{
				if (Pawn == PC->GetPawn())
				{
					UE_LOG(LogTemp, Log, TEXT("NLTDoor: Player walked through door '%s' -> traveling to '%s'"),
						*GetName(), *TargetLevelId.ToString());
					TryTravel();
				}
			}
		}
	}
}

void ANLTDoorActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	if (Cast<APawn>(OtherActor))
	{
		if (OverlappingPlayer == OtherActor)
		{
			UE_LOG(LogTemp, Log, TEXT("NLTDoor: Player left range of door '%s'"), *GetName());
			OverlappingPlayer = nullptr;
		}
	}
}

void ANLTDoorActor::TryTravel()
{
	if (UWorld* World = GetWorld())
	{
		if (ANLTPlayerController* NltPC = Cast<ANLTPlayerController>(World->GetFirstPlayerController()))
		{
			NltPC->TravelToLevel(TargetLevelId);
		}
		else
		{
			// Fallback if the NLT controller is not in use.
			UGameplayStatics::OpenLevel(World, TargetLevelId);
		}
	}
}
