#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"

#include "GemLock.generated.h"

// Forward declarations.
class AGemsPuzzle;
class USimpleAnimatorComponent;
class USimpleRotatorComponent;

// Object that can translate its gem and can rotate its lock
UCLASS()
class TRASNOCHANDOCONMIRNA_API AGemLock : public AInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGemLock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void ServerInteract_Implementation(AMainCharacter* MainCharacter) override;

	// Calls the rotator animation.
	void OpenLock();

private:
	/***COMPONENTS***/

	UPROPERTY(VisibleAnyWhere) USimpleAnimatorComponent* Translator; // Moves the gems.

	UPROPERTY(VisibleAnywhere) USimpleRotatorComponent* Rotator; // Opens the lock.

	UPROPERTY(EditAnywhere) UStaticMeshComponent* GemMesh; // Mesh for the gem.

	UPROPERTY(EditAnywhere) UStaticMeshComponent* LockMesh; // Mesh for the lock.
	
	
	/***ACTORS***/

	UPROPERTY(EditAnywhere) AGemsPuzzle* Puzzle; // Puzzle that validates the solution.


private:
	friend class AGemsPuzzle;

	TArray<FVector> GemPositions; // The user must indicate bottom and top positions and the middle one will be interpolated.
	int32 CurrentIndex = 0; // Current index of the gem position.
};
