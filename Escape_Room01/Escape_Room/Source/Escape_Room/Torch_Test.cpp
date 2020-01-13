// Property of Levi Voris 2020


#include "Torch_Test.h"

// Sets default values for this component's properties
UTorch_Test::UTorch_Test()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTorch_Test::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTorch_Test::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

