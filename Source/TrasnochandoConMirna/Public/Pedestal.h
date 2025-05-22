#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Pedestal.generated.h"

class AInteractableObject;
class USphereComponent;
class AStatuesPuzzle;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APedestal : public AActor
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

	UPROPERTY(EditAnywhere) UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere) USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* GhostMesh;


	/***ACTORS***/

	UPROPERTY(EditAnywhere) AStatuesPuzzle* Puzzle;


	/***MATERIALS***/

	UPROPERTY(EditDefaultsOnly) UMaterialInterface* GhostMaterial;
};
