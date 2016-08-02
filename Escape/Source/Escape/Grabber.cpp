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

	FindPhysicalHandlerComponent();
	FindInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Get the viewport
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPortLocation, ViewPortRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *ViewPortLocation.ToString(), *ViewPortRotation.ToString());

	// Calculate of the endpoint of debug line
	EndPointOfLine = ViewPortLocation + ViewPortRotation.Vector() * LineReach;

	// Set the target location
	if (PhysicalHandler->GrabbedComponent) {
		PhysicalHandler->SetTargetLocation(EndPointOfLine);
	}

}

///Define the press grab key operation
void UGrabber::GrabPressed() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed!"));
	// Get the hit object with physical body 
	FHitResult HitObj = FindTheFirstReachingObject();
	auto GrabObjComponent = HitObj.GetComponent();
	auto GrabObjActor = HitObj.GetActor();

	// If hit a object, grab it by using grab component
	if (GrabObjActor) {
		PhysicalHandler->GrabComponent(
			GrabObjComponent,
			NAME_None,
			GrabObjComponent->GetOwner()->GetActorLocation(),
			true
		);
	}
}

///Define the release grab key operation
void UGrabber::GrabReleased() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Released!"));
	PhysicalHandler->ReleaseComponent();
}

/// Implement of finding physical handler component
void UGrabber::FindPhysicalHandlerComponent() {
	// Find the physical handler of the owner
	PhysicalHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicalHandler) {
		UE_LOG(LogTemp, Warning, TEXT("%s has a physical handle component."), *GetOwner()->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s MISSING a physical hanle component!"), *GetOwner()->GetName());
	}
}

/// Implement of finding input component
void UGrabber::FindInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has a input component."), *GetOwner()->GetName());
		// Grab action binding test
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabPressed);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabReleased);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s MISSING a input component!"), *GetOwner()->GetName());
	}
}

FHitResult UGrabber::FindTheFirstReachingObject() {
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

	// The variable store the hit result info
	FHitResult HitResInfo;

	// Some settings of the line tracing
	FCollisionQueryParams CollisionParams(FName(TEXT("")), false, GetOwner());

	// Do the line tracing
	GetWorld()->LineTraceSingleByObjectType(
		HitResInfo,
		ViewPortLocation,
		EndPointOfLine,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		CollisionParams
	);

	// Log the result of the line tracing
	AActor* HitActor = HitResInfo.GetActor();
	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("The hitting object's name is: %s"), *(HitActor->GetName()));
	}

	return HitResInfo;
}