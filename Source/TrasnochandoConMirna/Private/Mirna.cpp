#include "Mirna.h"
#include "AIBehavior.h"

AMirna::AMirna()
{
	PrimaryActorTick.bCanEverTick = true;

	AIBehavior = CreateDefaultSubobject<UAIBehavior>(TEXT("AIBehavior"));
}
