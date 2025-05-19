// Fill out your copyright notice in the Description page of Project Settings.


#include "Statue.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "MainCharacter.h"

// Sets default values
AStatue::AStatue()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetIsReplicated(true);

	PickUpCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollision"));
	PickUpCollision->SetupAttachment(StaticMesh);
	PickUpCollision->SetIsReplicated(true);
}

void AStatue::BeginPlay()
{
	Super::BeginPlay();
}

void AStatue::ServerInteract_Implementation()
{
	MulticastInteract();
}

void AStatue::MulticastInteract_Implementation()
{
	bInteractEnabled = false;
	PickUpCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	StaticMesh->SetOverlayMaterial(nullptr);
}

bool AStatue::IsGrabbable()
{
	return bInteractEnabled;
}

void AStatue::SetOverlay(bool bEnabled)
{
	if (bEnabled)
	{
		StaticMesh->SetOverlayMaterial(OutlineOverlay);
	}
	else
	{
		StaticMesh->SetOverlayMaterial(nullptr);
	}
}

void AStatue::EnableInteraction()
{
	bInteractEnabled = true;
	StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}
