// Fill out your copyright notice in the Description page of Project Settings.

#include "WirePuzzle.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "EngineGlobals.h"

AWirePuzzle::AWirePuzzle()
{
	//Create WirePuzzleMeshComponents
	BlueA       = AInteractable::CreateDefaultSubobject<UWirePuzzleMeshComponent>(TEXT("BlueA"));
	BlueB       = AInteractable::CreateDefaultSubobject<UWirePuzzleMeshComponent>(TEXT("BlueB"));
	YellowA     = AInteractable::CreateDefaultSubobject<UWirePuzzleMeshComponent>(TEXT("YellowA"));
	YellowB     = AInteractable::CreateDefaultSubobject<UWirePuzzleMeshComponent>(TEXT("YellowB"));
	RedA        = AInteractable::CreateDefaultSubobject<UWirePuzzleMeshComponent>(TEXT("RedA"));
	RedB        = AInteractable::CreateDefaultSubobject<UWirePuzzleMeshComponent>(TEXT("RedB"));
	GreenA      = AInteractable::CreateDefaultSubobject<UWirePuzzleMeshComponent>(TEXT("GreenA"));
	GreenB      = AInteractable::CreateDefaultSubobject<UWirePuzzleMeshComponent>(TEXT("GreenB"));

	TArray<UWirePuzzleMeshComponent*> components;
	AInteractable::GetComponents<UWirePuzzleMeshComponent>(components);

	//Setup Components
	int componentCount = components.Num();
	for (int i = 0; i < componentCount; ++i)
	{
		UWirePuzzleMeshComponent* component = components[i];
		component->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
		component->SetupAttachment(AInteractable::RootComponent);
		component->OnClicked.AddDynamic(this, &AWirePuzzle::HandleComponentClicked);
		component->meshIndex = i;
		currentPuzzleState.Add(Colors::None);
	}

	//Create Solution State
	puzzleSolution.Add(Colors::Blue);
	puzzleSolution.Add(Colors::Blue);
	puzzleSolution.Add(Colors::Yellow);
	puzzleSolution.Add(Colors::Yellow);
	puzzleSolution.Add(Colors::Red);
	puzzleSolution.Add(Colors::Red);
	puzzleSolution.Add(Colors::Green);
	puzzleSolution.Add(Colors::Green);

	//Setup Camera Components
	CameraComponent = AInteractable::CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(AInteractable::RootComponent);
	CameraComponent->SetRelativeLocation(FVector(-400, 0, 0));

	//Create Material References
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BlueMat(TEXT("/Game/Materials/WirePuzzle/Blue.Blue"));
	BlueMaterial = (UMaterialInterface*)BlueMat.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GreenMat(TEXT("/Game/Materials/WirePuzzle/Green.Green"));
	GreenMaterial = (UMaterialInterface*)GreenMat.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> RedMat(TEXT("/Game/Materials/WirePuzzle/Red.Red"));
	RedMaterial = (UMaterialInterface*)RedMat.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> YellowMat(TEXT("/Game/Materials/WirePuzzle/Yellow.Yellow"));
	YellowMaterial = (UMaterialInterface*)YellowMat.Object;

	puzzleType = Puzzles::WirePuzzle;
}

void AWirePuzzle::OnInteract_Implementation()
{
	//If we are not currently overlapping the box component, do not interact
	if (!AInteractable::BoxComponent->IsOverlappingComponent(UGameplayStatics::GetPlayerCharacter(AInteractable::GetWorld(), 0)->GetCapsuleComponent()))
	{
		return;
	}

	messenger->RemoveAllWidgets();
	APlayerController* playerController = AInteractable::GetWorld()->GetFirstPlayerController();

	//Toggle between player controller's camera and this camera when interact button is pressed
	if (playerController->GetViewTarget() == this)
	{
		playerController->SetViewTargetWithBlend((AActor*)UGameplayStatics::GetPlayerCharacter(AInteractable::GetWorld(), 0), 0.5f);
		playerController->bEnableMouseOverEvents = false;
		playerController->bShowMouseCursor = false;
		playerController->bEnableClickEvents = false;
		AInteractable::StaticMeshComponent->SetRenderCustomDepth(true);

		playerController->SetInputMode(FInputModeGameOnly());
	}
	else
	{
		playerController->SetViewTargetWithBlend((AActor*) this, 0.5f);
		playerController->bEnableMouseOverEvents = true;
		playerController->bShowMouseCursor = true;
		playerController->bEnableClickEvents = true;
		AInteractable::StaticMeshComponent->SetRenderCustomDepth(false);

		playerController->SetInputMode(FInputModeGameAndUI());
	}
	
}

void AWirePuzzle::BeginPlay()
{
	Super::BeginPlay();

	isSolved = saveGameUtil->GetPuzzleState(puzzleType);
	if (isSolved)
	{
		InitPuzzleState();
		if (!saveGameUtil->DoesPlayerHaveKey(roomPuzzleUnlocks))
		{
			FMessage message;
			message.room = roomPuzzleUnlocks;
			messenger->PuzzleSolved(message);
		}
	}
}

void AWirePuzzle::HandleComponentClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	UWirePuzzleMeshComponent* meshComponent = Cast<UWirePuzzleMeshComponent>(TouchedComponent);

	switch (currentPuzzleState[meshComponent->meshIndex])
	{
		case Colors::Blue:
			SetWireComponentColor(meshComponent, Colors::Red);
			break;
		case Colors::Red:
			SetWireComponentColor(meshComponent, Colors::Yellow);
			break;
		case Colors::Yellow:
			SetWireComponentColor(meshComponent, Colors::Green);
			break;
		case Colors::None:
		case Colors::Green:
			SetWireComponentColor(meshComponent, Colors::Blue);
			break;
	}
		CheckSolution();
}

void AWirePuzzle::CheckSolution()
{
	int count = puzzleSolution.Num();
	for (int i = 0; i < count; ++i)
	{
		if (currentPuzzleState[i] != puzzleSolution[i])
		{
			return;
		}
	}

	FMessage message;
	message.room = roomPuzzleUnlocks;
	message.puzzleType = puzzleType;
	messenger->PuzzleSolved(message);
}

void AWirePuzzle::InitPuzzleState()
{

	TArray<UWirePuzzleMeshComponent*> components;
	AInteractable::GetComponents<UWirePuzzleMeshComponent>(components);

	for (UWirePuzzleMeshComponent* wireComponent : components)
	{
		Colors color = puzzleSolution[wireComponent->meshIndex];
		SetWireComponentColor(wireComponent, color);
	}
}

void AWirePuzzle::SetWireComponentColor(UWirePuzzleMeshComponent* wireComponent, Colors color)
{
	switch (color)
	{
	case Colors::Blue:
		wireComponent->SetMaterial(0, BlueMaterial);
		currentPuzzleState[wireComponent->meshIndex] = color;
		break;
	case Colors::Red:
		wireComponent->SetMaterial(0, RedMaterial);
		currentPuzzleState[wireComponent->meshIndex] = color;
		break;
	case Colors::Yellow:
		wireComponent->SetMaterial(0, YellowMaterial);
		currentPuzzleState[wireComponent->meshIndex] = Colors::Yellow
			;
		break;
	case Colors::None:
	case Colors::Green:
		wireComponent->SetMaterial(0, GreenMaterial);
		currentPuzzleState[wireComponent->meshIndex] = Colors::Green;
		break;
	}
}