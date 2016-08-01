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
	//Get the player object pawn
	PlayerObject = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoorController::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If player enter the specific area, open the door
	if (TriggerOpenDoorArea->IsOverlappingActor(PlayerObject)) {
		OpenDoor();
	}
}

void UOpenDoorController::OpenDoor() {
	// Get the object owner
	AActor *ObjectOwner = GetOwner();
	// Rotate the door
	FRotator NewRotator = FRotator(0.0f, 120.0f, 0.0f);
	ObjectOwner->SetActorRotation(NewRotator);
}


