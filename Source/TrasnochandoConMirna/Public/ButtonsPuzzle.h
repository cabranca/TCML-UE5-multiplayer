#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"

#include "ButtonsPuzzle.generated.h"

/***FORWARD DECLARATIONS***/
class APuzzleButton;
class AEarrings;
class ASimpleAnimatedObject;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AButtonsPuzzle : public AActor, public IPuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonsPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(Server, Reliable) void ValidateSolution() override;

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

	bool bPuzzleSolved = false;

	UFUNCTION(NetMulticast, Reliable) void MulticastValidateSolution() override;

	UFUNCTION(NetMulticast, Reliable) void OnClockFinished();
};
