// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"

#include "Wardrobe.generated.h"

// Forward declarations
class UCameraComponent;
class USphereComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AWardrobe : public AInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWardrobe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ServerInteract_Implementation(AMainCharacter* MainCharacter) override;

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere) UCameraComponent* Camera;


	/***HIDING***/

	AMainCharacter* HiddenCharacter;
	bool bPlayerHidden = false;

	UFUNCTION(NetMulticast, Reliable) void MulticastHidePlayer(AMainCharacter* MainCharacter);
};
