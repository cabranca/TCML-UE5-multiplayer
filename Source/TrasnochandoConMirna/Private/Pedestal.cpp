#include "Pedestal.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "StatuesPuzzle.h"
#include "Statue.h"

// Sets default values
APedestal::APedestal()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(StaticMesh);

	GhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatueGhost"));
	GhostMesh->SetupAttachment(StaticMesh);
}

void APedestal::BeginPlay()
{
	Super::BeginPlay();
}

void APedestal::ShowGhost(UStaticMesh* Mesh)
{
	if (Mesh)
	{
		GhostMesh->SetStaticMesh(Mesh);
		int32 NumMaterials = GhostMesh->GetNumMaterials();
		for (int32 i = 0; i < NumMaterials; ++i)
		{
			GhostMesh->SetMaterial(i, GhostMaterial);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted setting null Mesh"));
	}
}

void APedestal::HideGhost()
{
	GhostMesh->SetStaticMesh(nullptr);
}

void APedestal::PlaceObject(UStaticMeshComponent* Object)
{
	HideGhost();
	Object->SetWorldLocation(GhostMesh->GetComponentLocation());
	if (Puzzle && HasAuthority())
	{
		Puzzle->ValidateSolution();
	}
}
