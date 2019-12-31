// Fill out your copyright notice in the Description page of Project Settings.


#include "Open_Doors.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpen_Doors::UOpen_Doors()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpen_Doors::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;	//Determine where actor is
	CurrentYaw = InitialYaw;							//Currently where the actor is in real time
	//TargetYaw = InitialYaw + -90.0f;					//Destination of Door - Hard Coded
	TargetYaw += InitialYaw;							//TargetYaw = TargetYaw + InitialYaw;
	
}


// Called every frame
void UOpen_Doors::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, 0.5f * DeltaTime);		//Setting Start and end point, then setting speed in which is goes - does nothing til told
	FRotator DoorRotation = GetOwner()->GetActorRotation();					//Rotator to actually implament Rotation
	DoorRotation.Yaw = CurrentYaw;											//Getting the Yaw of current actor (CurrentYaw)
	GetOwner()->SetActorRotation(DoorRotation);								//Telling actor to use Door Rotation
}

