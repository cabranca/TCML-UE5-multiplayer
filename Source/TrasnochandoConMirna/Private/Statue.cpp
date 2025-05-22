// Fill out your copyright notice in the Description page of Project Settings.


#include "Statue.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "MainCharacter.h"

// Sets default values
AStatue::AStatue()
{
	SetReplicateMovement(true);
	SphereCollision->SetIsReplicated(true);
	bCanGrab = true;
}

void AStatue::BeginPlay()
{
	Super::BeginPlay();
}
