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
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetIsReplicated(true);
	StaticMesh->SetupAttachment(RootComponent);
	

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	CollisionBox->SetupAttachment(RootComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->SetRelativeLocation(FVector::ZeroVector);
}

// Called when the game starts or when spawned
void APuzzleDoor::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);

	StaticMesh->SetRelativeLocation(OpenPosition);
	
	FScriptDelegate BeginDelegateSubscriber;
	BeginDelegateSubscriber.BindUFunction(this, "OnDoorCrossingBegin");
	CollisionBox->OnComponentBeginOverlap.Add(BeginDelegateSubscriber);

	FScriptDelegate EndDelegateSubscriber;
	EndDelegateSubscriber.BindUFunction(this, "OnDoorCrossingEnd");
	CollisionBox->OnComponentEndOverlap.Add(EndDelegateSubscriber);
}

void APuzzleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		Animate(DeltaTime);
	}
}

void APuzzleDoor::OpenDoor()
{
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SetActorTickEnabled(true);
	Audio->Play();
}

void APuzzleDoor::CloseDoor_Implementation()
{
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	SetActorTickEnabled(true);
	Audio->Play();
}

void APuzzleDoor::Animate_Implementation(float DeltaTime)
{
	CurrentPosition += AnimationSpeed * AnimationDirection * DeltaTime;
	if (CurrentPosition > 1.f || CurrentPosition < 0.f)
	{
		CurrentPosition = FMath::Clamp(CurrentPosition, 0.f, 1.f);
		SetActorTickEnabled(false);
	}
	StaticMesh->SetRelativeLocation(OpenPosition + (ClosedPosition - OpenPosition) * CurrentPosition);
}

void APuzzleDoor::OnDoorCrossingBegin_Implementation(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (Character)
	{
		double DotProduct = FVector::DotProduct(Character->GetVelocity(), Arrow->GetForwardVector());
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
		double DotProduct = FVector::DotProduct(Character->GetVelocity(), Arrow->GetForwardVector());
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
