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

	// Métodos para disparar la animación
	void PlayForward();

	void PlayReverse();


	/***COMPONENTS***/

	// Mesh a animar
	UPROPERTY(EditAnywhere, Category = "Animation") UStaticMeshComponent* TargetMesh;

	// Posiciones de inicio y fin
	UPROPERTY(EditAnywhere, Category = "Animation") FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "Animation") FVector EndLocation;

	// Duración total de la animación
	UPROPERTY(EditAnywhere, Category = "Animation") float AnimationDuration = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Animation") bool bBeginsAtStart = true;


private:
	float ElapsedTime = 0.0f;
	bool bIsAnimating = false;
	bool bForward = true;
};
