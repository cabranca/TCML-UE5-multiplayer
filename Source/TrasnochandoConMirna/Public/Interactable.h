#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRASNOCHANDOCONMIRNA_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(Server, Reliable) virtual void ServerInteract() = 0;

	UFUNCTION(NetMulticast, Reliable) virtual void MulticastInteract() = 0;

	/***GETTERS***/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) bool CanInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) bool CanGrab();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) UStaticMeshComponent* GetMeshToGrab();


	/***SETTERS***/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) void Highlight(bool bEnabled);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) void SetCanInteract(bool bEnabled);
};
