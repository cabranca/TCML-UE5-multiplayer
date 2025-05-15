#include "Pedestal.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "StatuesPuzzle.h"

// Sets default values
APedestal::APedestal()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

void APedestal::ServerInteract_Implementation()
{
	if (Puzzle)
	{
		Puzzle->ValidateSolution();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Puzzle not set"));
	}
}

bool APedestal::IsGrabbable()
{
	return false;
}
