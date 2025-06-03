#include "GameplayGameMode.h"


void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	LootedObjects = { {"PAINTING", false}, {"SALT", false}, {"EARRINGS", false}, {"DYE", true} };
}

void AGameplayGameMode::SetLootedObject(FName Tag)
{
	LootedObjects[Tag] = true;
	for (auto& [ObjectTag, Looted] : LootedObjects)
	{
		if (!Looted)
		{
			UE_LOG(LogTemp, Warning, TEXT("OBJECT NOT LOOTED YET"));
		}
	}
}

bool AGameplayGameMode::PlayerHasWon() const
{
	for (auto& [Tag, Looted] : LootedObjects)
	{
		if (!Looted)
		{
			UE_LOG(LogTemp, Warning, TEXT("OBJECT NOT LOOTED YET"));
			return false;
		}
	}
	return true;
}
