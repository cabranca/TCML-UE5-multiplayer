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
	ABell(); // Sets default values for this component's properties

	void ServerInteract_Implementation(AMainCharacter* MainCharacter) override;

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UAudioComponent* SFX; // Bell SFX to play.
	

private:
	UPROPERTY(EditAnywhere) ABellsPuzzle* Puzzle; // Puzzle that validates the solution.

	UFUNCTION(NetMulticast, Reliable) void MulticastPlaySFX(); // Plays the bell SFX in every client.
};
