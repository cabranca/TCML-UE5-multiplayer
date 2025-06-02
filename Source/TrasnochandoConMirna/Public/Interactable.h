#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainCharacter.h"

#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

// Interface for the objects that accept an interaction.
class TRASNOCHANDOCONMIRNA_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void ServerInteract(AMainCharacter* MainCharacter) = 0;

	virtual void MulticastInteract(AMainCharacter* MainCharacter) = 0;

	/***GETTERS***/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) bool CanInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) bool CanGrab();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) UStaticMeshComponent* GetMeshToGrab();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) bool IsLootable();


	/***SETTERS***/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) void Highlight(bool bEnabled);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) void SetCanInteract(bool bEnabled);
};
