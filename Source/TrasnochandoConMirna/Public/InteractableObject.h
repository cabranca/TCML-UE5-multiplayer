#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "InteractableObject.generated.h"

// Forward declarations
class USphereComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AInteractableObject : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/***IINTERACTABLE***/

	UFUNCTION(Server, Reliable) virtual void ServerInteract() override;

	UFUNCTION(Server, Reliable) virtual void MulticastInteract() override;

	virtual bool CanInteract_Implementation() override;

	virtual bool CanGrab_Implementation() override;

	virtual UStaticMeshComponent* GetMeshToGrab_Implementation() override;

	virtual void Highlight_Implementation(bool bEnabled) override;

	virtual void SetCanInteract_Implementation(bool bEnabled) override;

protected:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) USceneComponent* Scene;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere) USphereComponent* SphereCollision;


	/***MATERIALS***/

	UPROPERTY(EditAnywhere) UMaterialInterface* OutlineOverlay;

	/***VARIABLES***/

	bool bCanInteract = true;
	bool bCanGrab = false;
};
