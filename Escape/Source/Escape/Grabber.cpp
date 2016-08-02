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

	// Find the physical handler of the owner
	PhysicalHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicalHandler) {
		UE_LOG(LogTemp, Warning, TEXT("%s has a physical handle component."), *GetOwner()->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s MISSING a physical hanle component!"), *GetOwner()->GetName());
	}

	// Find the input component of the owner
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has a input component."), *GetOwner()->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s MISSING a input component!"), *GetOwner()->GetName());
	}

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

	// Grab action binding test
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab check!"));
}

