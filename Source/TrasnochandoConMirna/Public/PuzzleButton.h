#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"

#include "PuzzleButton.generated.h"

/// Forward declarations
class AButtonsPuzzle;
class USimpleAnimatorComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APuzzleButton : public AInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleButton();

	void ServerInteract_Implementation(AMainCharacter* MainCharacter) override;

	// Calls the rotator animation.
	void Release();

private:
	/***COMPONENTS***/

	UPROPERTY(VisibleAnyWhere) USimpleAnimatorComponent* Translator;

	/***ACTORS***/
	
	UPROPERTY(EditAnywhere) AButtonsPuzzle* Puzzle;
};
