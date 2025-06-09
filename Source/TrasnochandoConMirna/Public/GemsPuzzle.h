#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBase.h"

#include "GemsPuzzle.generated.h"

// Forward declarations.
class AGemLock;
class AExitDoor;
class UAudioComponent;

// Validates the value of the gems positions.
UCLASS()
class TRASNOCHANDOCONMIRNA_API AGemsPuzzle : public APuzzleBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGemsPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void ValidateSolution_Implementation(AInteractableObject* Sender) override;

private:
	UPROPERTY(EditAnywhere) TArray<AGemLock*> GemLocks; //Locks used to solve the puzzle.
	UPROPERTY(EditAnywhere) AExitDoor* ExitDoor;
	UPROPERTY(EditAnywhere) UAudioComponent* DoorSFX;

	//TODO: Add exit door.

	TMap<FName, int8> PuzzleSolution;
	TMap<FName, int8> CurrentGemPositions;

	UFUNCTION(NetMulticast, Reliable) void OnPuzzleSolved();
};
