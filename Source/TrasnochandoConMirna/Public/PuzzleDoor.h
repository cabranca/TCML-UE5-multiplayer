#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PuzzleDoor.generated.h"

// Forward declarations
class UStaticMeshComponent;
class UArrowComponent;
class UBoxComponent;
class USimpleAnimatorComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APuzzleDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	/***ACTIONS***/

	UFUNCTION(NetMulticast, Reliable) void OpenDoor();

private:
	UFUNCTION(NetMulticast, Reliable) void CloseDoor();

	
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere) UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere) UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere) UAudioComponent* Audio;

	UPROPERTY(VisibleAnywhere) USimpleAnimatorComponent* Animator;


	/***OVERLAP***/

	UPROPERTY(EditAnywhere) uint8 AllowedPassengers = 0;

	uint8 CurrentPassengers = 0;

	bool bOverlapBegun = false;

	// Helper for timing
	FTimerHandle SpawnTimerHandle;

	UFUNCTION(NetMulticast, Reliable) void OnDoorCrossingBegin(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(NetMulticast, Reliable) void OnDoorCrossingEnd(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/***MISC***/

	friend class PuzzleManager;
};
