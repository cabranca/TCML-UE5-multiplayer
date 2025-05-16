#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "Pedestal.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class AStatuesPuzzle;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APedestal : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APedestal();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable) void ServerInteract() override;

	bool IsGrabbable() override;

private:

	/***COMPONENTS***/

	UPROPERTY(EditAnywhere) UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere) UBoxComponent* BoxCollision;


	/***ACTORS***/

	UPROPERTY(EditAnywhere) AStatuesPuzzle* Puzzle;


	bool bStatuePosed = false;

	UFUNCTION() void OnBoxBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() void OnBoxEndOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
