// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape.h"
#include "OpenDoorController.h"


// Sets default values for this component's properties
UOpenDoorController::UOpenDoorController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorController::BeginPlay()
{
	Super::BeginPlay();
	// Get the player object pawn
	PlayerObject = GetWorld()->GetFirstPlayerController()->GetPawn();
	// Get the object owner
	ObjectOwner = GetOwner();
}


// Called every frame
void UOpenDoorController::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (TriggerOpenDoorArea == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Trigger volume * MISSING"));
		return;
	}

	TotalMass = GetTheTotalOverlappingMass();
	// If player enter the specific area, open the door
	if (GetTheTotalOverlappingMass() > 10.0f) {
	
		OpenReq.Broadcast();
	}
	else {
		CloseReq.Broadcast();
	}
}

void UOpenDoorController::CloseDoor() {
	ObjectOwner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Calculate the total mass of overlapping of the trigger volume
float UOpenDoorController::GetTheTotalOverlappingMass() {
	float MassResult = 0.0f;
	TArray<AActor*> OverlappingArray;
	TriggerOpenDoorArea->GetOverlappingActors(OverlappingArray);
	for (AActor* overlap : OverlappingArray) {
		MassResult += overlap->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return MassResult;
}


