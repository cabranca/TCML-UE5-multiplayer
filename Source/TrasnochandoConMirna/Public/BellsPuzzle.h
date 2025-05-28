#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBase.h"

#include "BellsPuzzle.generated.h"

// Forward declarations.
class AEarrings;
class ASimpleAnimatedObject;

// Class that manages the bells puzzle.
UCLASS()
class TRASNOCHANDOCONMIRNA_API ABellsPuzzle : public APuzzleBase
{
	GENERATED_BODY()
	
public:	
	ABellsPuzzle(); // Sets default values for this component's properties

protected:
	virtual void BeginPlay() override;

public:	
	void ValidateSolution_Implementation(AInteractableObject* Sender) override;

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UAudioComponent* BookshelfSFX; // SFX for when the bookshelf is moved.
	UPROPERTY(EditAnywhere) UAudioComponent* ErrorSFX; // SFX for when the puzzle is failed (Not in use for now).


	/***PUZZLE***/

	TArray<FName> PuzzleSolution; // Sequence of notes that solves the puzzle.
	uint8 SolutionIndex; // Index to iterate the PuzzleSolution.
	UPROPERTY(EditAnywhere) AEarrings* Salt; // Reward of the puzzle.
	UPROPERTY(EditAnywhere) ASimpleAnimatedObject* Bookshelf; // Object that hides the salt and must be moved.

	UFUNCTION(NetMulticast, Reliable) void OnPuzzleFailed();

	UFUNCTION(NetMulticast, Reliable) void OnPuzzleSolved();
};
