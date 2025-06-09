#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PuzzleDoor.generated.h"

// Forward declarations
class UStaticMeshComponent;
class UArrowComponent;
class UBoxComponent;
class USimpleRotatorComponent;

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

	UFUNCTION(Server, Reliable) void OpenDoor();

private:
	UFUNCTION(Server, Reliable) void CloseDoor();

	
	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* HandleMesh;

	UPROPERTY(EditAnywhere) UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere) UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere) UAudioComponent* Audio;

	UPROPERTY(VisibleAnywhere) USimpleRotatorComponent* DoorRotator;

	UPROPERTY(VisibleAnywhere) USimpleRotatorComponent* HandleRotator;


	/***OVERLAP***/

	UPROPERTY(EditAnywhere) uint8 AllowedPassengers = 0;

	uint8 CurrentPassengers = 0;

	bool bOverlapBegun = false;

	bool bDoorClosed = false;

	// Helper for timing
	FTimerHandle CloseTimerHandle;

	UFUNCTION() void OnDoorCrossingBegin(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() void OnDoorCrossingEnd(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(NetMulticast, Reliable) void PlayAudio();
	/***MISC***/

	friend class PuzzleManager;
};
