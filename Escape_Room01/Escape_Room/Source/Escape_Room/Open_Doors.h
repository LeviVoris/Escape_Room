// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerBox.h"
#include "Engine/TriggerVolume.h"
#include "Open_Doors.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_ROOM_API UOpen_Doors : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpen_Doors();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void FindAudioComponent();
	float TotalMassOfActors() const;
	void FindPressurePlate();
	void FindOneTimeDoorTrigger();
	void OneTimeShut(float DeltaTime);

	//Tracks wheather sound has been played or not
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

private:

	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;
	
	UPROPERTY(EditAnywhere)
	float OpenDoorAngle = 90.0f;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 1.f;

	UPROPERTY(EditAnywhere)
		float DoorCloseSpeed = 1.f;

	UPROPERTY(EditAnywhere)
		float DoorClosedDelay = 1.f;

	UPROPERTY(EditAnywhere)
		float MassToOpenDoor = 20.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerBox* DoorTrigger = nullptr;

	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;
};
