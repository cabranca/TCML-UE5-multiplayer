#pragma once

#include "CoreMinimal.h"
#include "LootableObject.h"

#include "Earrings.generated.h"

// Forward declarations
class USimpleAnimatorComponent;

/**
 * 
 */
UCLASS()
class TRASNOCHANDOCONMIRNA_API AEarrings : public ALootableObject
{
	GENERATED_BODY()
	
public:
	AEarrings();

	void PlayForward();

private:
	UPROPERTY(VisibleAnywhere) USimpleAnimatorComponent* Animator;
};
