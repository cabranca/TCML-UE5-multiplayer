// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pedestal.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APedestal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APedestal();

private:
	friend class APuzzleManager;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;
};
