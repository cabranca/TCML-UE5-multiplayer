// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Bell.generated.h"

// Forward declarations
class ABellsPuzzle;

// Puzzle item that plays a sound and has a tag referencing its tone.
UCLASS()
class TRASNOCHANDOCONMIRNA_API ABell : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	ABell();

	void ServerInteract_Implementation(AMainCharacter* MainCharacter) override;

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UAudioComponent* SFX; // Bell SFX to play.
	

	/***PUZZLE***/

public:
	UPROPERTY(EditAnywhere) FName Tag; // Tone of the sound, used by the Puzzle to validate the solution.

private:
	UPROPERTY(EditAnywhere) ABellsPuzzle* Puzzle; // Puzzle that validates the solution.

	UFUNCTION(NetMulticast, Reliable) void MulticastPlaySFX(); // Plays the bell SFX in every client.
};
