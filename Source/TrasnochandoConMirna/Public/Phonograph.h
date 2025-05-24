// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Phonograph.generated.h"

/**
 * 
 */
UCLASS()
class TRASNOCHANDOCONMIRNA_API APhonograph : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	APhonograph();

	void ServerInteract_Implementation(AMainCharacter* MainCharacter) override;

private:
	UPROPERTY(EditAnywhere) UAudioComponent* ShowOST;

	UFUNCTION(NetMulticast, Reliable) void MulticastPlaySFX();
};
