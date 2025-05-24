#include "Bell.h"

#include "Components/AudioComponent.h"
#include "BellsPuzzle.h"

ABell::ABell()
{
	SFX = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX"));
	SFX->bAutoActivate = false;
}

void ABell::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	MulticastPlaySFX();
	if (Puzzle)
	{
		Puzzle->ValidateSolution(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PUZZLE NOT SET"));
	}
}

void ABell::MulticastPlaySFX_Implementation()
{
	SFX->Play();
}
