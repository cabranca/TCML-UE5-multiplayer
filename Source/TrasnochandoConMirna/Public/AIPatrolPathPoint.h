// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIPatrolPathPoint.generated.h"

class UArrowComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AAIPatrolPathPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPatrolPathPoint();

private:
	friend class UBTTask_Patrol;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	UArrowComponent* Arrow;
};
