// Property of Levi Voris 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyDoorTrigger.generated.h"


UCLASS()
class ESCAPE_ROOM_API AMyDoorTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// constructor sets default values for this actor's properties
	AMyDoorTrigger();

	// overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};