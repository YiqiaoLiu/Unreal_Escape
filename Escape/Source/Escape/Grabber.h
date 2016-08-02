// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
private:
	// The info of the player's viewport
	FVector ViewPortLocation;
	FRotator ViewPortRotation;

	// The length of the debug line
	float LineReach = 100.0f;
	// The end point of the debug line
	FVector EndPointOfLine;

	// The physical handler of the owner
	UPhysicsHandleComponent* PhysicalHandler = nullptr;

	/// Function of find the physical handler component
	void FindPhysicalHandlerComponent();

	// The input component
	UInputComponent* InputComponent = nullptr;

	/// Function of find the input component
	void FindInputComponent();

	/// Press the grab button
	void GrabPressed();

	/// Find the first object during the line tracing
	FHitResult FindTheFirstReachingObject();

	/// Release the grab button
	void GrabReleased();
};
