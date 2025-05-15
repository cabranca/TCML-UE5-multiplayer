#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "PuzzleButton.generated.h"

/// Forward declarations
class USphereComponent;
class AButtonsPuzzle;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APuzzleButton : public AActor, public IInteractable
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

	UFUNCTION(Server, Reliable) void ServerInteract() override;

	bool IsGrabbable() override;

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


	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere) USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere) UMaterialInterface* OutlineOverlay;


	/***ACTORS***/
	
	UPROPERTY(EditAnywhere) AButtonsPuzzle* Puzzle;


	/***OVERLAP***/

	UFUNCTION() void OnSphereBeginOverlap(USphereComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() void OnSphereEndOverlap(USphereComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
