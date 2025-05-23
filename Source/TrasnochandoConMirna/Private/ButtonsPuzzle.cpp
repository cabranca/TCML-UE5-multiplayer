#include "ButtonsPuzzle.h"

#include "Components/AudioComponent.h"
#include "PuzzleButton.h"

AButtonsPuzzle::AButtonsPuzzle()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ClockSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ClockSFX"));
	ClockSFX->SetIsReplicated(true);

	ErrorSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ErrorSFX"));
	ErrorSFX->SetIsReplicated(true);
}

void AButtonsPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	ClockSFX->OnAudioFinished.AddDynamic(this, &AButtonsPuzzle::OnClockFinished);
}

void AButtonsPuzzle::ValidateSolution_Implementation()
{
	MulticastValidateSolution();
}

void AButtonsPuzzle::MulticastValidateSolution_Implementation()
{
	if (!bButtonPressed)
	{
		ClockSFX->Play();
		bButtonPressed = true;
	}
	else
	{
		bPuzzleSolved = true;
		ClockSFX->Stop();
	}
}

void AButtonsPuzzle::OnClockFinished_Implementation()
{
	if (!bPuzzleSolved)
	{
		ErrorSFX->Play();
		bButtonPressed = false;
	}
	for (auto& Button : Buttons)
	{
		if (HasAuthority())
		{
			Button->Release();
		}
		if (!bPuzzleSolved)
		{
			IInteractable::Execute_SetCanInteract(Button, true);
		}
	}
}

