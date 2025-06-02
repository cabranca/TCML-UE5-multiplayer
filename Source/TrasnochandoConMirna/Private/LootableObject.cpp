#include "LootableObject.h"

void ALootableObject::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	MulticastDestroyObject();
}

void ALootableObject::MulticastDestroyObject_Implementation()
{
	Destroy();
}

bool ALootableObject::IsLootable_Implementation()
{
	return true;
}
