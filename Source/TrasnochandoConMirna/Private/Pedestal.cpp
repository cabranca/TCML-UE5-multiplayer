#include "Pedestal.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "StatuesPuzzle.h"
#include "Statue.h"

// Sets default values
APedestal::APedestal()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

void APedestal::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate BeginDelegateSubscriber;
	BeginDelegateSubscriber.BindUFunction(this, "OnBoxBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(BeginDelegateSubscriber);

	FScriptDelegate EndDelegateSubscriber;
	EndDelegateSubscriber.BindUFunction(this, "OnBoxEndOverlap");
	BoxCollision->OnComponentEndOverlap.Add(EndDelegateSubscriber);
}

void APedestal::ServerInteract_Implementation()
{
	if (Puzzle)
	{
		Puzzle->ValidateSolution();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Puzzle not set"));
	}
}

bool APedestal::IsGrabbable()
{
	return false;
}

void APedestal::OnBoxBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bStatuePosed && Cast<AStatue>(OtherActor))
	{
		if (HasAuthority())
		{
			ServerInteract();
		}
		
		bStatuePosed = true;
	}
}

void APedestal::OnBoxEndOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AStatue>(OtherActor))
	{
		bStatuePosed = false;
	}
}
