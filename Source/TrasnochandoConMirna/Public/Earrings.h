#pragma once

#include "CoreMinimal.h"
#include "LootableObject.h"

#include "Earrings.generated.h"

// Forward declarations.
class USimpleAnimatorComponent;

// Class for the earrings that are lootable and have a simple animation.
// TODO: Changed this class to ASimpleAnimatedLootableObject.
UCLASS()
class TRASNOCHANDOCONMIRNA_API AEarrings : public ALootableObject
{
	GENERATED_BODY()
	
public:
	AEarrings(); // Sets default values for this actor's properties.

	void PlayForward(); // Forwarding to call the Animator PlayForward() method.

private:
	UPROPERTY(VisibleAnywhere) USimpleAnimatorComponent* Animator; // Component to animate the earrings exposure.
};
