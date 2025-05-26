#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"

#include "Pedestal.generated.h"

// Forward declarations
class USphereComponent;
class AStatuesPuzzle;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APedestal : public AInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APedestal();

protected:
	virtual void BeginPlay() override;

public:
	void ShowGhost(UStaticMesh* Mesh);

	void HideGhost();

	void PlaceObject(AInteractableObject* Object);

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UStaticMeshComponent* GhostMesh;


	/***ACTORS***/

	UPROPERTY(EditAnywhere) AStatuesPuzzle* Puzzle;


	/***MATERIALS***/

	UPROPERTY(EditDefaultsOnly) UMaterialInterface* GhostMaterial;
};
