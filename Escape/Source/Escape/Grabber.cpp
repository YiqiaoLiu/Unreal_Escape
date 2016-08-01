// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get the viewport
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPortLocation, ViewPortRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *ViewPortLocation.ToString(), *ViewPortRotation.ToString());

	// Calculate of the endpoint of debug line
	EndPointOfLine = ViewPortLocation + ViewPortRotation.Vector() * LineReach;

	// Draw the debug line
	DrawDebugLine(
		GetWorld(),
		ViewPortLocation,
		EndPointOfLine,
		FColor(255.0f, 0.0f, 0.0f),
		false,
		0.0f,
		0.0f,
		10.0f
	);
}

