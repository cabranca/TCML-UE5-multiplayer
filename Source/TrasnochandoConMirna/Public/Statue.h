// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Statue.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UCapsuleComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AStatue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatue();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;
};
