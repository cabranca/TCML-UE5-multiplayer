#include "Phonograph.h"

#include "Components/AudioComponent.h"

APhonograph::APhonograph()
{
	ShowOST = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX"));
	ShowOST->SetupAttachment(RootComponent);
	ShowOST->bAutoActivate = false;
	ShowOST->bAllowSpatialization = true;

	ShowOST->bOverrideAttenuation = true;

	ShowOST->AttenuationOverrides.bAttenuate = true;
	ShowOST->AttenuationOverrides.bSpatialize = true;
	ShowOST->AttenuationOverrides.AttenuationShape = EAttenuationShape::Sphere;
	ShowOST->AttenuationOverrides.FalloffDistance = 1500.0f;
	ShowOST->AttenuationOverrides.AttenuationShapeExtents = FVector(400.f);
}

void APhonograph::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	MulticastPlaySFX();
}

void APhonograph::MulticastPlaySFX_Implementation()
{
	if (ShowOST->IsPlaying())
	{
		ShowOST->Stop();
	}
	else
	{
		ShowOST->Play();
	}
}
