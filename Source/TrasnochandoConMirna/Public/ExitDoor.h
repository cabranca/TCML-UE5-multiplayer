#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ExitDoor.generated.h"

// Forward declarations
class USimpleAnimatorComponent;
class USimpleRotatorComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AExitDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExitDoor();

public:	
	void OpenExitDoor();

private:
	/***COMPONENTS***/

	UPROPERTY(VisibleAnyWhere) USimpleAnimatorComponent* GateTranslator; // Opens the gate.

	UPROPERTY(VisibleAnyWhere) USimpleRotatorComponent* DoorRotator; //  Opens the door.

	UPROPERTY(VisibleAnywhere) USimpleRotatorComponent* HandleRotator; // Rotates the handle.

	UPROPERTY(EditAnywhere) UStaticMeshComponent* StructureMesh; // Mesh for the base structure.

	UPROPERTY(EditAnywhere) UStaticMeshComponent* GateMesh; // Mesh for the gate.

	UPROPERTY(EditAnywhere) UStaticMeshComponent* DoorMesh; // Mesh for the door. // TODO: DoorComponent what includes the handle and functionality.

	UPROPERTY(EditAnywhere) UStaticMeshComponent* HandleMesh; // Mesh for the handle.
};
