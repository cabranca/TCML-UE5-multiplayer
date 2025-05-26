#include "StatuesPuzzle.h"

#include "Components/AudioComponent.h"
#include "PuzzleDoor.h"
#include "Statue.h"

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

void AStatuesPuzzle::ValidateSolution_Implementation(AInteractableObject* Trigger)
{
	if (bPuzzleSolved) return;

	if (ValidationTrigger && Trigger != ValidationTrigger)
	{
		bPuzzleSolved = true;
		for (auto& Door : Doors)
		{
			Door->OpenDoor();
		}
		OnPuzzleSolved();
	}
	else if (!ValidationTrigger)
	{
		ValidationTrigger = Trigger;
		IInteractable::Execute_SetCanInteract(Trigger, false);
		PlayClock();
	}
}

void AStatuesPuzzle::OnClockFinished_Implementation()
{
	if (HasAuthority() && !bPuzzleSolved)
	{
		OnPuzzleFailed();
	}
}

void AStatuesPuzzle::PlayClock_Implementation()
{
	ClockSFX->Play();
}

void AStatuesPuzzle::OnPuzzleFailed_Implementation()
{
	
	ErrorSFX->Play();
	if (HasAuthority() && !bPuzzleSolved)
	{
		IInteractable::Execute_SetCanInteract(ValidationTrigger, true);
		ValidationTrigger = nullptr;
	}
}

void AStatuesPuzzle::OnPuzzleSolved_Implementation()
{
	ClockSFX->Stop();
}
