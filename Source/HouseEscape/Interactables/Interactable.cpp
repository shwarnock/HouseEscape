// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"
#include "HouseEscapeGameInstance.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	
	RootComponent = StaticMeshComponent;
	RootComponent->SetRelativeLocation(FVector::ZeroVector);
	
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetRelativeLocation(FVector::ZeroVector);

	uniqueID = FGuid::NewGuid();
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	AActor::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::HandleBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractable::HandleEndOverlap);

	UHouseEscapeGameInstance* gameInstance = Cast<UHouseEscapeGameInstance>(GetWorld()->GetGameInstance());
	messenger = gameInstance->GetMessenger();

	saveGameUtil = gameInstance->GetSaveGameUtil();
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}

void AInteractable::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AInteractable::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AInteractable::OnInteract_Implementation() 
{
}

bool AInteractable::IsPlayerOverlapping()
{
	return BoxComponent->IsOverlappingActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}