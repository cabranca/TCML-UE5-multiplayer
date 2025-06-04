#include "Mirna.h"

#include "AIBehavior.h"
#include "GameFramework/CharacterMovementComponent.h"

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
