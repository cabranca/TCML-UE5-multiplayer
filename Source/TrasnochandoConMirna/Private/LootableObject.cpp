#include "LootableObject.h"

void ALootableObject::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	MulticastDestroyObject();
}

void ALootableObject::MulticastDestroyObject_Implementation()
{
	Destroy();
}