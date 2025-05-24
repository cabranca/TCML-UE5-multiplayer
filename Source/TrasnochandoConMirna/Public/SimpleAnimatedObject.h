#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleAnimatedObject.generated.h"

// Forward declarations
class USimpleAnimatorComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API ASimpleAnimatedObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleAnimatedObject();

	void PlayForward();

	void PlayReverse();

private:
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) USceneComponent* Scene;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere) USimpleAnimatorComponent* Animator;
};
