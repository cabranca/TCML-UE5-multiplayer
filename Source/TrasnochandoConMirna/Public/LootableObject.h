#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "LootableObject.generated.h"

/**
 * 
 */
UCLASS()
class TRASNOCHANDOCONMIRNA_API ALootableObject : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	void ServerInteract_Implementation(AMainCharacter* MainCharacter) override;
	virtual bool IsLootable_Implementation() override;

private:
	UFUNCTION(NetMulticast, Reliable) void MulticastDestroyObject();
};
