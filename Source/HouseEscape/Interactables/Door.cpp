// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Engine.h"

void ADoor::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPlayerOverlapping())
	{
		FMessage message;
		message.interactableType = interactType;
		message.room = neededKey;
		message.interact = this;
		message.doorState = doorState;
		messenger->AddInteractTarget(message);
	}
}

void ADoor::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsPlayerOverlapping())
	{
		FMessage message;
		message.interact = this;
		message.interactableType = interactType;
		messenger->RemoveInteractTarget(message);
	}
}

void ADoor::OnInteract_Implementation()
{
	//If we are not currently overlapping the box component, do not interact
	if (!BoxComponent->IsOverlappingComponent(UGameplayStatics::GetPlayerCharacter(AInteractable::GetWorld(), 0)->GetCapsuleComponent()))
	{
		return;
	}

	if (saveGameUtil->DoesPlayerHaveKey(neededKey) && MyTimeline != NULL)
	{
		DoorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		switch (doorState)
		{
			case DoorStates::Open:
				doorState = DoorStates::Closed;
				MyTimeline->ReverseFromEnd();
				break;
			case DoorStates::Closed:
				doorState = DoorStates::Open;
				MyTimeline->PlayFromStart();
				break;
		}

		messenger->RemoveAllWidgets();
	}
}

ADoor::ADoor()
{
	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Door(TEXT("/Game/StarterContent/Props/SM_Door.SM_Door"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Frame(TEXT("/Game/StarterContent/Props/SM_DoorFrame.SM_DoorFrame"));

	StaticMeshComponent->SetStaticMesh(Frame.Object);
	StaticMeshComponent->SetRelativeScale3D(FVector(1, 1.05, 1.05));

	DoorComponent->SetStaticMesh(Door.Object);

	DoorComponent->SetupAttachment(RootComponent);
	DoorComponent->SetRelativeLocation(FVector(0, 45, 0));

	BoxComponent->SetRelativeLocation(FVector(0, 0, 100));
	BoxComponent->SetRelativeScale3D(FVector(1.5f, 1.75f, 3.0f));

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/Curve.Curve"));
	check(Curve.Succeeded());

	FloatCurve = Curve.Object;

	doorState = DoorStates::NoKey;
	interactType = Interacts::Door;

	meshToRender = DoorComponent;

	TimerDel.BindUFunction(this, FName{ TEXT("CloseDoor") });
}

void ADoor::BeginPlay()
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	AInteractable::BeginPlay();

	if (FloatCurve != NULL)
	{
		MyTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		MyTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
		this->BlueprintCreatedComponents.Add(MyTimeline); // Add to array so it gets saved
		MyTimeline->SetNetAddressable();	// This component has a stable name that can be referenced for replication

		MyTimeline->SetPropertySetObject(DoorComponent); // Set which object the timeline should drive properties on
		MyTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		MyTimeline->SetLooping(false);
		MyTimeline->SetTimelineLength(5.0f);
		MyTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		MyTimeline->SetPlaybackPosition(0.0f, false);

		//Add the float curve to the timeline and connect it to your timelines's interpolation function
		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		MyTimeline->AddInterpFloat(FloatCurve, onTimelineCallback);
		MyTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		MyTimeline->RegisterComponent();
	}

	messenger->OnKeyPickedUp.AddDynamic(this, &ADoor::HandleKeyPickedUp);

	if (saveGameUtil->DoesPlayerHaveKey(neededKey))
	{
		doorState = DoorStates::Closed;
	}
}

void ADoor::Tick(float DeltaSeconds)
{
	AInteractable::Tick(DeltaSeconds);

	if (MyTimeline != NULL)
	{
		MyTimeline->TickComponent(DeltaSeconds, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void ADoor::TimelineCallback(float interpolatedVal)
{
	float newZ = 90 * interpolatedVal;
	DoorComponent->SetRelativeRotation(FRotator(0, newZ, 0));
}

void ADoor::TimelineFinishedCallback()
{
	if (doorState == DoorStates::Open)
	{
		GetWorldTimerManager().SetTimer(UnusedHandle, TimerDel, 1.0f, false);
	}

	DoorComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ADoor::CloseDoor()
{
	doorState = DoorStates::Closed;
	MyTimeline->ReverseFromEnd();
}

void ADoor::HandleKeyPickedUp(FMessage message)
{
	if (message.room == neededKey)
	{
		doorState = DoorStates::Closed;
	}
}

TEnumAsByte<DoorStates> ADoor::GetDoorState()
{
	return doorState;
}