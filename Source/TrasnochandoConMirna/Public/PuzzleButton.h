#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"

#include "PuzzleButton.generated.h"

/// Forward declarations
class AButtonsPuzzle;
class USimpleAnimatorComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APuzzleButton : public AInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ServerInteract_Implementation(AMainCharacter* MainCharacter) override;

	void Release();

private:
	/***COMPONENTS***/

	UPROPERTY(VisibleAnyWhere) USimpleAnimatorComponent* Animator;

	/***ACTORS***/
	
	UPROPERTY(EditAnywhere) AButtonsPuzzle* Puzzle;
};
