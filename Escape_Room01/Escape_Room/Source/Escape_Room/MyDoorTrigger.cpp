// Property of Levi Voris 2020


#include "MyDoorTrigger.h"
#include "DrawDebugHelpers.h"

AMyDoorTrigger::AMyDoorTrigger()
{
	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AMyDoorTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyDoorTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AMyDoorTrigger::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, 999, 0, 5);
}

void AMyDoorTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	// check if Actors do not equal nullptr and that 
	if (OtherActor && OtherActor != this)
	{
			UE_LOG(LogTemp, Error, TEXT("Enter"), *GetOwner()->GetName());
	}
}

void AMyDoorTrigger::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
			UE_LOG(LogTemp, Error, TEXT("Exit"), *GetOwner()->GetName());
	}
}