#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "Statue.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UCapsuleComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AStatue : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatue();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Server, Reliable) void ServerInteract() override;

	UFUNCTION(NetMulticast, Reliable) void MulticastInteract();

	bool IsGrabbable() override;

	void EnableCapsuleOverlap(bool bEnabled);


private:
	/***COMPONENTS***/
	UPROPERTY(EditAnywhere) UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere) USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere) UCapsuleComponent* CapsuleCollision;


	/***MATERIALS***/
	UPROPERTY(EditAnywhere) UMaterialInterface* OutlineOverlay;


	/***OVERLAP***/

	UFUNCTION() void OnSphereBeginOverlap(USphereComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() void OnSphereEndOverlap(USphereComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
