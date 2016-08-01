// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoorController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoorController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoorController();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Open door operation
	void OpenDoor();

	// Close door operation
	void CloseDoor();

private:
	// The object owner
	AActor* ObjectOwner;

	// The open degree of the door
	UPROPERTY(EditAnywhere)
		float OpenDegree = 120.0f;

	// The variable of the trigger area to open the door
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TriggerOpenDoorArea;

	// The player pawn
	AActor* PlayerObject;

	//Store last time open the door
	float LastOpenDoorTime;

	// When player leave the trigger area, 0.5s the door will close automatically
	UPROPERTY(EditAnywhere)
		float OpenDoorDelay = 0.5f;

};
