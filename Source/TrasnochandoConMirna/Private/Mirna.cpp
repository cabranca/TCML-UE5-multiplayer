#include "Mirna.h"

#include "AIBehavior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMirna::AMirna()
{
	PrimaryActorTick.bCanEverTick = true;

	AIBehavior = CreateDefaultSubobject<UAIBehavior>(TEXT("AIBehavior"));
}

void AMirna::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMirna::PlayFootstepNotify()
{
	MulticastPlayFootstepSound(GetActorLocation());
}

void AMirna::MulticastPlayFootstepSound_Implementation(const FVector& Location)
{
	if (FootstepSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FootstepSFX, Location, 1.f, 1.f, 0.f, FootstepSFXAttenuation);
	}
}
