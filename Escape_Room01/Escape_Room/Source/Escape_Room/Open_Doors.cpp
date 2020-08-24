// Fill out your copyright notice in the Description page of Project Settings.

#include "Open_Doors.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework\PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpen_Doors::UOpen_Doors()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpen_Doors::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;	//Determine where actor is
	CurrentYaw = InitialYaw;							//Currently where the actor is in real time
	//OpenDoorAngle = InitialYaw + -90.0f;					//Destination of Door - Hard Coded
	OpenDoorAngle += InitialYaw;							//OpenDoorAngle = OpenDoorAngle + InitialYaw;

	FindPressurePlate();
	FindAudioComponent();
	FindOneTimeDoorTrigger();
}

// Called every frame
void UOpen_Doors::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		//DoorLastOpened = When the door was opened
	}
	else
	{
		//if the door has been open for longer than DoorCloseDelay
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorClosedDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpen_Doors::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenDoorAngle, DoorOpenSpeed * DeltaTime);		//Setting Start and end point, then setting speed in which is goes - does nothing til told
	FRotator DoorRotation = GetOwner()->GetActorRotation();					//Rotator to actually implament Rotation
	DoorRotation.Yaw = CurrentYaw;											//Getting the Yaw of current actor (CurrentYaw)
	GetOwner()->SetActorRotation(DoorRotation);								//Telling actor to use Door Rotation

	CloseDoorSound = false;
	if (!AudioComponent) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}
}

void UOpen_Doors::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DoorCloseSpeed * DeltaTime);		//Setting Start and end point, then setting speed in which is goes - does nothing til told
	FRotator DoorRotation = GetOwner()->GetActorRotation();								//Rotator to actually implament Rotation
	DoorRotation.Yaw = CurrentYaw;														//Getting the Yaw of current actor (CurrentYaw)
	GetOwner()->SetActorRotation(DoorRotation);											//Telling actor to use Door Rotation

	OpenDoorSound = false;
	if (!AudioComponent) { return; }
	if (!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}

float UOpen_Doors::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	};
	return TotalMass;
}

void UOpen_Doors::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Missing Audio Component!"), *GetOwner()->GetName());
	}
}

void UOpen_Doors::FindPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Has Open Door, but no Pressure plate: %s"), *GetOwner()->GetName());
	}
}

void UOpen_Doors::FindOneTimeDoorTrigger()
{
	if (!DoorTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("Has Open Door, but no Box Trigger: %s"), *GetOwner()->GetName());
	}
}

void UOpen_Doors::OneTimeShut(float DeltaTime)
{
	if (DoorTrigger)
	{
		//DoorTrigger(OnActorBeginOverlap)->OnActorBeginOverlap->TickComponent->CloseDoor;
	}
}