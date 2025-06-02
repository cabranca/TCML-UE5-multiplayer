#include "GemLock.h"

#include "SimpleAnimatorComponent.h"
#include "SimpleRotatorComponent.h"
#include "GemsPuzzle.h"

// Sets default values
AGemLock::AGemLock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GemMesh"));
	GemMesh->SetIsReplicated(true);
	GemMesh->SetupAttachment(RootComponent);

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	LockMesh->SetIsReplicated(true);
	LockMesh->SetupAttachment(RootComponent);

	Translator = CreateDefaultSubobject<USimpleAnimatorComponent>(TEXT("Translator"));
	Translator->TargetMesh = GemMesh;

	Rotator = CreateDefaultSubobject<USimpleRotatorComponent>(TEXT("Rotator"));
	Rotator->TargetMesh = LockMesh;
}

void AGemLock::BeginPlay()
{
	Super::BeginPlay();

	GemPositions = { Translator->StartLocation, FMath::Lerp(Translator->StartLocation, Translator->EndLocation, 0.5), Translator->EndLocation };
}

void AGemLock::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	if (bCanInteract)
	{
		Translator->StartLocation = GemPositions[CurrentIndex % 3];
		Translator->EndLocation = GemPositions[(CurrentIndex + 1) % 3];
		Translator->PlayForward();
		CurrentIndex++;
		if (Puzzle)
		{
			Puzzle->ValidateSolution(this);
			Super::ServerInteract_Implementation(MainCharacter);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("PUZZLE NOT SET"));
		}
	}
}

void AGemLock::OpenLock()
{
	Rotator->PlayForward();
}
