// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Bell.generated.h"

/**
 * 
 */
UCLASS()
class TRASNOCHANDOCONMIRNA_API ABell : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	ABell();

	void ServerInteract_Implementation(AMainCharacter* MainCharacter) override;

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UAudioComponent* SFX;


private:
	UPROPERTY(EditAnywhere) FName Tag;

	/***PUZZLE***/

	UFUNCTION(NetMulticast, Reliable) void MulticastPlaySFX();
};
