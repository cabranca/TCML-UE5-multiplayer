#include "ButtonsPuzzle.h"

#include "Components/AudioComponent.h"
#include "PuzzleButton.h"
#include "SimpleAnimatedObject.h"
#include "Earrings.h"

AButtonsPuzzle::AButtonsPuzzle()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ClockSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ClockSFX"));
	ClockSFX->SetIsReplicated(true);

	ErrorSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ErrorSFX"));
	ErrorSFX->SetIsReplicated(true);

	PedestalSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("PedestalSFX"));
	PedestalSFX->SetIsReplicated(true);
}

void AButtonsPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	ClockSFX->OnAudioFinished.AddDynamic(this, &AButtonsPuzzle::OnClockFinished);
}

void AButtonsPuzzle::ValidateSolution_Implementation(AInteractableObject* Trigger)
{
	if (bPuzzleSolved) return;

	if (ValidationTrigger && Trigger != ValidationTrigger)
	{
		bPuzzleSolved = true;
		Pedestal->PlayForward();
		Earrings->PlayForward();
		OnPuzzleSolved();
	}
	else if (!ValidationTrigger)
	{
		ValidationTrigger = Trigger;
		PlayClock();
	}
}

void AButtonsPuzzle::PlayClock_Implementation()
{
	ClockSFX->Play();
}

void AButtonsPuzzle::OnPuzzleFailed_Implementation()
{
	ValidationTrigger = nullptr;
	ErrorSFX->Play();
	for (auto& Button : Buttons)
	{
		Button->Release();
		IInteractable::Execute_SetCanInteract(Button, true);
	}
}

void AButtonsPuzzle::OnPuzzleSolved_Implementation()
{
	ClockSFX->Stop();
	PedestalSFX->Play();
}

void AButtonsPuzzle::OnClockFinished_Implementation()
{
	if (HasAuthority() && !bPuzzleSolved)
	{
		OnPuzzleFailed();
	}
}

