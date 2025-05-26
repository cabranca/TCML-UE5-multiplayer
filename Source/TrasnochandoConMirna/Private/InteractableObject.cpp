#include "InteractableObject.h"

#include "Components/SphereComponent.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = false; //TODO: see if this can be set to false and then a child set to true.
	bReplicates = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetIsReplicated(true);
	StaticMesh->SetupAttachment(RootComponent);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableObject::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	//MulticastInteract(MainCharacter);
}

void AInteractableObject::MulticastInteract_Implementation(AMainCharacter* MainCharacter)
{
	bCanInteract = false;
	SphereCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	StaticMesh->SetOverlayMaterial(nullptr);
}

bool AInteractableObject::CanInteract_Implementation()
{
	return bCanInteract;
}

bool AInteractableObject::CanGrab_Implementation()
{
	return bCanInteract && bCanGrab;
}

UStaticMeshComponent* AInteractableObject::GetMeshToGrab_Implementation()
{
	return StaticMesh;
}

void AInteractableObject::Highlight_Implementation(bool bEnabled)
{
	if (OutlineOverlay)
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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OUTLINE MATERIAL NOT SET"));
	}
}

void AInteractableObject::SetCanInteract_Implementation(bool bEnabled)
{
	if (HasAuthority())
	{
		MulticastSetCanInteract(bEnabled);
	}
}


void AInteractableObject::MulticastSetCanInteract_Implementation(bool bEnabled)
{
	bCanInteract = bEnabled;
	ECollisionResponse Response = bEnabled ? ECR_Block : ECR_Ignore;
	SphereCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, Response);
}
