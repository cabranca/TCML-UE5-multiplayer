#include "PuzzleDoor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
APuzzleDoor::APuzzleDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(StaticMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	CollisionBox->SetupAttachment(StaticMesh);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(StaticMesh);
	Arrow->SetRelativeLocation(FVector::ZeroVector);
}

// Called when the game starts or when spawned
void APuzzleDoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (StaticMesh)
	{
		FScriptDelegate BeginDelegateSubscriber;
		BeginDelegateSubscriber.BindUFunction(this, "OnDoorCrossingBegin");
		CollisionBox->OnComponentBeginOverlap.Add(BeginDelegateSubscriber);

		FScriptDelegate EndDelegateSubscriber;
		EndDelegateSubscriber.BindUFunction(this, "OnDoorCrossingEnd");
		CollisionBox->OnComponentEndOverlap.Add(EndDelegateSubscriber);
	}
}

void APuzzleDoor::OnDoorCrossingBegin_Implementation(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (Character)
	{
		double DotProduct = FVector::DotProduct(Character->GetActorForwardVector(), Arrow->GetForwardVector());
		if (DotProduct > 0)
		{
			bOverlapBegun = true;
		}
	}
}

void APuzzleDoor::OnDoorCrossingEnd_Implementation(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (Character)
	{
		double DotProduct = FVector::DotProduct(Character->GetActorForwardVector(), Arrow->GetForwardVector());
		if (DotProduct > 0)
		{
			CurrentPassengers++;
		}
		else if (DotProduct < 0 && CurrentPassengers != 0)
		{
			CurrentPassengers--;
		}
		bOverlapBegun = false;
		if (CurrentPassengers == AllowedPassengers)
		{
			GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APuzzleDoor::CloseDoor, 0.5f, false);
		}
	}
}

void APuzzleDoor::CloseDoor_Implementation()
{
	StaticMesh->SetVisibility(true);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	Audio->Play();
}

void APuzzleDoor::OpenDoor()
{
	StaticMesh->SetVisibility(false);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Audio->Play();
}
