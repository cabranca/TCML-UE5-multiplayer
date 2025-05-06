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

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(StaticMesh);
}

void AStatue::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate BeginDelegateSubscriber;
	BeginDelegateSubscriber.BindUFunction(this, "OnSphereBeginOverlap");
	SphereCollision->OnComponentBeginOverlap.Add(BeginDelegateSubscriber);
	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AStatue::OnSphereBeginOverlap);

	FScriptDelegate EndDelegateSubscriber;
	EndDelegateSubscriber.BindUFunction(this, "OnSphereEndOverlap");
	SphereCollision->OnComponentEndOverlap.Add(EndDelegateSubscriber);

	//SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AStatue::OnDoorCrossingBegin);
}

void AStatue::OnSphereBeginOverlap(USphereComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor))
	{
		StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
		StaticMesh->SetOverlayMaterial(OutlineOverlay);
	}
}

void AStatue::OnSphereEndOverlap(USphereComponent * Component, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AMainCharacter>(OtherActor))
	{
		StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
		StaticMesh->SetOverlayMaterial(nullptr);
	}
}
