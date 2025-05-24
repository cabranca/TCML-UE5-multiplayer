#include "Bell.h"

#include "Components/AudioComponent.h"

ABell::ABell()
{
	SFX = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX"));
	SFX->bAutoActivate = false;
}

void ABell::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	MulticastPlaySFX();
}

void ABell::MulticastPlaySFX_Implementation()
{
	SFX->Play();
}
