#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"

#include "PuzzleButton.generated.h"

/// Forward declarations
class AButtonsPuzzle;

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


	/***ANIMATION***/
	void SetForwardAnimation();

	void SetBackwardsAnimation();

private:
	UPROPERTY(EditAnywhere, Category = "Animation") FVector StartPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Animation") FVector FinishPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Animation") float AnimationSpeed = 0.5f;

	float CurrentPosition = 0.f;

	UPROPERTY(ReplicatedUsing = OnRep_AnimationDirection) int8 AnimationDirection = 1;

	UFUNCTION(NetMulticast, Reliable) void Animate(float DeltaTime);

	UFUNCTION()	void OnRep_AnimationDirection();


	/***ACTORS***/
	
	UPROPERTY(EditAnywhere) AButtonsPuzzle* Puzzle;
};
