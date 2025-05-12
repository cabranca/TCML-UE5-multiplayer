#include "StatuesPuzzle.h"

#include "Components/AudioComponent.h"
#include "PuzzleDoor.h"

AStatuesPuzzle::AStatuesPuzzle()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ClockSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ClockSFX"));
	ClockSFX->SetIsReplicated(true);

	ErrorSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ErrorSFX"));
	ErrorSFX->SetIsReplicated(true);
}

void AStatuesPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	ClockSFX->OnAudioFinished.AddDynamic(this, &AStatuesPuzzle::OnClockFinished);
}

void AStatuesPuzzle::ValidateSolution_Implementation()
{
	MulticastValidateSolution();
}

void AStatuesPuzzle::MulticastValidateSolution_Implementation()
{
	if (!bStatueSet)
	{
		ClockSFX->Play();
		bStatueSet = true;
	}
	else
	{
		bPuzzleSolved = true;
		ClockSFX->Stop();
		for (auto& Door : Doors)
		{
			Door->OpenDoor();
		}
	}
}

void AStatuesPuzzle::OnClockFinished_Implementation()
{
	if (!bPuzzleSolved)
	{
		ErrorSFX->Play();
		bStatueSet = false;
	}
}
