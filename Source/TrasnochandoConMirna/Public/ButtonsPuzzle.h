#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBase.h"

#include "ButtonsPuzzle.generated.h"

// Forward declarations.
class APuzzleButton;
class AEarrings;
class ASimpleAnimatedObject;

// Class that manages the buttons puzzle.
UCLASS()
class TRASNOCHANDOCONMIRNA_API AButtonsPuzzle : public APuzzleBase
{
	GENERATED_BODY()
	
public:	
	AButtonsPuzzle(); // Sets default values for this actor's properties.

protected:
	virtual void BeginPlay() override;

public:	
	void ValidateSolution_Implementation(AInteractableObject* Sender) override;

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UAudioComponent* ClockSFX; // SFX for when the puzzle solution is tried.

	UPROPERTY(EditAnywhere) UAudioComponent* ErrorSFX; // SFX for when the puzzle is failed (Not in use for now).

	UPROPERTY(EditAnywhere) UAudioComponent* PedestalSFX; // SFX for when the bookshelf is moved.


	/***PUZZLE RESOLUTION***/

	UPROPERTY(EditAnywhere) AEarrings* Earrings; // Reward of the puzzle.
	UPROPERTY(EditAnywhere) ASimpleAnimatedObject* Pedestal; // Object that hides the salt and must be moved.
	UPROPERTY(EditAnywhere) TArray<APuzzleButton*> Buttons; // Collection of buttons that must be restored when the puzzle failes or succeeds.
	bool bButtonPressed = false; // Whether or not a button is currently pressed.

	UFUNCTION(NetMulticast, Reliable) void PlayClock(); // Plays the clock sfx.
	UFUNCTION(NetMulticast, Reliable) void OnPuzzleFailed(); // Called when the puzzle validation is not fulfilled.
	UFUNCTION(NetMulticast, Reliable) void OnPuzzleSolved(); // Called when the puzzle validation is fulfilled.
	UFUNCTION(NetMulticast, Reliable) void OnClockFinished(); // Callback for when the Clock SFX is finished.
};
