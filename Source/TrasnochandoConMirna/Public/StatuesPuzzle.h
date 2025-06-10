#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBase.h"

#include "StatuesPuzzle.generated.h"

// Forward declarations
class APuzzleDoor;
class AStatue;
class ASimpleAnimatedObject;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AStatuesPuzzle : public APuzzleBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatuesPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void ValidateSolution_Implementation(AInteractableObject* Sender) override;

private:
	UPROPERTY(EditAnywhere) UAudioComponent* ClockSFX;

	UPROPERTY(EditAnywhere) UAudioComponent* ErrorSFX;

	UPROPERTY(EditAnywhere) TArray<APuzzleDoor*> Doors;

	UPROPERTY(EditAnywhere) ASimpleAnimatedObject* SecretDoor;

	UFUNCTION(NetMulticast, Reliable) void OnClockFinished();

	UFUNCTION(NetMulticast, Reliable) void PlayClock();

	UFUNCTION(NetMulticast, Reliable) void OnPuzzleFailed();

	UFUNCTION(NetMulticast, Reliable) void OnPuzzleSolved();
};
