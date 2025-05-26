#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBase.h"

#include "BellsPuzzle.generated.h"

// Forward declarations
class AEarrings;
class ASimpleAnimatedObject;

UCLASS()
class TRASNOCHANDOCONMIRNA_API ABellsPuzzle : public APuzzleBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABellsPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void ValidateSolution_Implementation(AInteractableObject* Sender) override;

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UAudioComponent* PedestalSFX;
	UPROPERTY(EditAnywhere) UAudioComponent* ErrorSFX;

	TArray<FName> PuzzleSolution;
	uint8 SolutionIndex;
	UPROPERTY(EditAnywhere) AEarrings* Salt;
	UPROPERTY(EditAnywhere) ASimpleAnimatedObject* Pedestal;

	UFUNCTION(NetMulticast, Reliable) void OnPuzzleFailed();

	UFUNCTION(NetMulticast, Reliable) void OnPuzzleSolved();
};
