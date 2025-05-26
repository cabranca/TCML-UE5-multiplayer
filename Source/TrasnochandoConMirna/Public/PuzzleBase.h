#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"

#include "PuzzleBase.generated.h"

UCLASS()
class TRASNOCHANDOCONMIRNA_API APuzzleBase : public AActor, public IPuzzle
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable) virtual void ValidateSolution(AInteractableObject* Sender) override;

protected:
	bool bPuzzleSolved = false;
	AInteractableObject* ValidationTrigger;
};
