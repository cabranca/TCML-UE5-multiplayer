#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"

#include "Statue.generated.h"

UCLASS()
class TRASNOCHANDOCONMIRNA_API AStatue : public AInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatue();

protected:
	virtual void BeginPlay() override;
};
