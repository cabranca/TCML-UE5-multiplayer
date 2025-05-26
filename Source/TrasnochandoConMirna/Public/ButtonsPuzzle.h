#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBase.h"

#include "ButtonsPuzzle.generated.h"

/***FORWARD DECLARATIONS***/
class APuzzleButton;
class AEarrings;
class ASimpleAnimatedObject;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AButtonsPuzzle : public APuzzleBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonsPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void ValidateSolution_Implementation(AInteractableObject* Sender) override;

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UAudioComponent* ClockSFX;

	UPROPERTY(EditAnywhere) UAudioComponent* ErrorSFX;

	UPROPERTY(EditAnywhere) UAudioComponent* PedestalSFX;


	/***PUZZLE RESOLUTION***/

	UPROPERTY(EditAnywhere) AEarrings* Earrings;

	UPROPERTY(EditAnywhere) ASimpleAnimatedObject* Pedestal;

	UPROPERTY(EditAnywhere) TArray<APuzzleButton*> Buttons;

	bool bButtonPressed = false;

	UFUNCTION(NetMulticast, Reliable) void PlayClock();

	UFUNCTION(NetMulticast, Reliable) void OnPuzzleFailed();

	UFUNCTION(NetMulticast, Reliable) void OnPuzzleSolved();

	UFUNCTION(NetMulticast, Reliable) void OnClockFinished();
};
