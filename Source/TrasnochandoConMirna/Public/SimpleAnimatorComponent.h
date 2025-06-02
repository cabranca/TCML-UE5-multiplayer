#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleAnimatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRASNOCHANDOCONMIRNA_API USimpleAnimatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimpleAnimatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/***COMPONENTS***/

	UPROPERTY(EditAnywhere, Category = "Animation") UStaticMeshComponent* TargetMesh; // Mesh to translate.

	UPROPERTY(EditAnywhere, Category = "Animation") FVector StartLocation; // Initial position of the translation.

	UPROPERTY(EditAnywhere, Category = "Animation") FVector EndLocation; // End position of the Translation.


	/***EXPOSED VARIABLES***/

	UPROPERTY(EditAnywhere, Category = "Animation") float AnimationDuration = 1.0f; // Duration of the rotation in seconds.

	UPROPERTY(EditAnywhere, Category = "Animation") bool bBeginsAtStart = true; // Whether the mesh starts at the StartLocation or EndLocation.
	

	/***METHODS***/

	void PlayForward(); // Translates towards the end.

	void PlayReverse(); // Translates towards the start.


private:
	float ElapsedTime = 0.0f; // Current time since translation started.
	bool bIsAnimating = false; // Whether the translation is in motion or not.
	bool bForward = true; // Whether the translation goes towards the end or the start.
	FVector RuntimeStartLocation; // Initial position when translation is called.
	FVector RuntimeEndLocation; // End postion when translation is called.
};
