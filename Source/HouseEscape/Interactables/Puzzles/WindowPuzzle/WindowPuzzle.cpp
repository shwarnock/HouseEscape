// Fill out your copyright notice in the Description page of Project Settings.

#include "WindowPuzzle.h"

AWindowPuzzle::AWindowPuzzle()
{
	puzzleType = Puzzles::WindowPuzzle;
	roomPuzzleUnlocks = Rooms::BasementFrontCenterRoom;
	interactType = Interacts::Puzzle;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MainWindow(TEXT("/Game/StaticMeshes/Window/WindowMain.WindowMain"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BottomWindow(TEXT("/Game/StaticMeshes/Window/BottomWindowPane.BottomWindowPane"));

	StaticMeshComponent->SetStaticMesh(MainWindow.Object);
	StaticMeshComponent->SetRelativeLocation(FVector(400, 0, 0));

	CenterWindowTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CenterWindowTop"));
	CenterWindowTop->SetStaticMesh(MainWindow.Object);
	CenterWindowTop->SetupAttachment(RootComponent);
	CenterWindowTop->SetRelativeLocation(FVector(-200, 0, 0));

	RightWindowTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWindowTop"));
	RightWindowTop->SetStaticMesh(MainWindow.Object);
	RightWindowTop->SetupAttachment(RootComponent);
	RightWindowTop->SetRelativeLocation(FVector(-400, 0, 0));

	LeftWindowBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWindowBottom"));
	LeftWindowBottom->SetStaticMesh(BottomWindow.Object);
	LeftWindowBottom->SetupAttachment(RootComponent);
	LeftWindowBottom->SetRelativeLocation(FVector::ZeroVector);

	CenterWindowBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CenterWindowBottom"));
	CenterWindowBottom->SetStaticMesh(BottomWindow.Object);
	CenterWindowBottom->SetupAttachment(CenterWindowTop);
	CenterWindowBottom->SetRelativeLocation(FVector::ZeroVector);

	RightWindowBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWindowBottom"));
	RightWindowBottom->SetStaticMesh(BottomWindow.Object);
	RightWindowBottom->SetupAttachment(RightWindowTop);
	RightWindowBottom->SetRelativeLocation(FVector::ZeroVector);

	CenterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CenterBox"));
	CenterBox->SetupAttachment(CenterWindowTop);
	CenterBox->SetRelativeLocation(FVector(0, -40, 75));

	RightBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightBox"));
	RightBox->SetupAttachment(RightWindowTop);
	RightBox->SetRelativeLocation(FVector(0, -45, 75));

	BoxComponent->SetRelativeLocation(FVector(0, -40, 75));

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/Curve.Curve"));
	check(Curve.Succeeded());

	FloatCurve = Curve.Object;

	solution.Add(WindowStates::Open);
	solution.Add(WindowStates::Closed);
	solution.Add(WindowStates::Open);

	currentStates.Add(WindowStates::Closed);
	currentStates.Add(WindowStates::Closed);
	currentStates.Add(WindowStates::Closed);

	windowOrder.Add(LeftWindowBottom);
	windowOrder.Add(CenterWindowBottom);
	windowOrder.Add(RightWindowBottom);
}

void AWindowPuzzle::OnInteract_Implementation()
{
	switch (CurrentInteraction)
	{
		case Windows::LEFT:
			Timeline->SetPropertySetObject(LeftWindowBottom);
			if (LeftWindowBottom->GetRelativeTransform().GetLocation() == FVector::ZeroVector)
			{
				Timeline->PlayFromStart();
				currentStates[0] = WindowStates::Open;
			}
			else
			{
				Timeline->ReverseFromEnd();
				currentStates[0] = WindowStates::Closed;
			}
			break;
		case Windows::RIGHT:
			Timeline->SetPropertySetObject(RightWindowBottom);
			if (RightWindowBottom->GetRelativeTransform().GetLocation() == FVector::ZeroVector)
			{
				Timeline->PlayFromStart();
				currentStates[2] = WindowStates::Open;
			}
			else
			{
				Timeline->ReverseFromEnd();
				currentStates[2] = WindowStates::Closed;
			}
			break;
		case Windows::CENTER:
			Timeline->SetPropertySetObject(CenterWindowBottom);
			if (CenterWindowBottom->GetRelativeTransform().GetLocation() == FVector::ZeroVector)
			{
				Timeline->PlayFromStart();
				currentStates[1] = WindowStates::Open;
			}
			else
			{
				Timeline->ReverseFromEnd();
				currentStates[1] = WindowStates::Closed;
			}
			break;
	}

	CheckSolution();
}

void AWindowPuzzle::CheckSolution()
{
	if (currentStates != solution)
	{
		return;
	}

	FMessage message;
	message.room = roomPuzzleUnlocks;
	message.puzzleType = puzzleType;
	messenger->PuzzleSolved(message);
	message.interact = this;
	messenger->RemoveInteractTarget(message);
	isSolved = true;
}
void AWindowPuzzle::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPlayerOverlapping() && !isSolved)
	{
		FMessage message;

		if (OverlappedComp == BoxComponent)
		{
			CurrentInteraction = Windows::LEFT;
			meshToRender = StaticMeshComponent;
		}
		else if (OverlappedComp == CenterBox)
		{
			CurrentInteraction = Windows::CENTER;
			meshToRender = CenterWindowTop;
		}
		else
		{
			CurrentInteraction = Windows::RIGHT;
			meshToRender = RightWindowTop;
		}

		message.interact = this;
		message.interactableType = interactType;
		message.uniqueId = uniqueId;
		messenger->AddInteractTarget(message);
	}
}

void AWindowPuzzle::BeginPlay()
{
	Super::BeginPlay();

	CenterBox->OnComponentBeginOverlap.AddDynamic(this, &AWindowPuzzle::HandleBeginOverlap);
	RightBox->OnComponentBeginOverlap.AddDynamic(this, &AWindowPuzzle::HandleBeginOverlap);

	CenterBox->OnComponentEndOverlap.AddDynamic(this, &AWindowPuzzle::HandleEndOverlap);
	RightBox->OnComponentEndOverlap.AddDynamic(this, &AWindowPuzzle::HandleEndOverlap);

	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	if (FloatCurve != NULL)
	{
		Timeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		Timeline->SetDirectionPropertyName(FName("TimelineDirection"));
		Timeline->SetLooping(false);
		Timeline->SetTimelineLength(1.0f);
		Timeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		Timeline->SetPlaybackPosition(0.0f, false);
		//Add the float curve to the timeline and connect it to your timelines's interpolation function
		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		Timeline->AddInterpFloat(FloatCurve, onTimelineCallback);
		Timeline->RegisterComponent();
	}
}

void AWindowPuzzle::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APuzzle::HandleEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

void AWindowPuzzle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Timeline != NULL)
	{
		Timeline->TickComponent(DeltaSeconds, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void AWindowPuzzle::TimelineCallback(float interpolatedVal)
{
	float newZ = 50 * interpolatedVal;
	switch (CurrentInteraction)
	{
	case Windows::CENTER:
		CenterWindowBottom->SetRelativeLocation(FVector(0, 0, newZ));
		break;
	case Windows::LEFT:
		LeftWindowBottom->SetRelativeLocation(FVector(0, 0, newZ));
		break;
	case Windows::RIGHT:
		RightWindowBottom->SetRelativeLocation(FVector(0, 0, newZ));
		break;
	}
}

void AWindowPuzzle::InitPuzzleState()
{
	int count = windowOrder.Num();
	for (int i = 0; i < count; ++i)
	{
		currentStates[i] = solution[i];
		if (currentStates[i] == WindowStates::Open)
		{
			windowOrder[i]->SetRelativeLocation(FVector(0, 0, 50));
		}
	}
}