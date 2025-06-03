#include "GameplayGameMode.h"


void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	LootedObjects = { {"PAINTING", false}, {"SALT", false}, {"EARRINGS", false}, {"DYE", true}, {"BRACELET_MIRNA", false}, {"BRACELET_GOLDINA", false} };
}

void AGameplayGameMode::SetLootedObject(FName Tag)
{
	LootedObjects[Tag] = true;
}

bool AGameplayGameMode::PlayerHasWon() const
{
	for (auto& [Tag, Looted] : LootedObjects)
	{
		if (!Looted)
		{
			return false;
		}
	}
	return true;
}
