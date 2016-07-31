// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape.h"
#include "RotateInitial.h"


// Sets default values for this component's properties
URotateInitial::URotateInitial()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotateInitial::BeginPlay()
{
	Super::BeginPlay();

	// Get the owner
	AActor *ObjectOwner = GetOwner();

	//Set the new rotation of the object at the beginning
	FRotator NewRot = FRotator(0.0f, 120.0f, 0.0f);
	ObjectOwner->SetActorRotation(NewRot);
}


// Called every frame
void URotateInitial::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

