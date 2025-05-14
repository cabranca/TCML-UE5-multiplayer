#include "PuzzleButton.h"

#include "Components/SphereComponent.h"
#include "MainCharacter.h"

// Sets default values
APuzzleButton::APuzzleButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetIsReplicated(true);
	StaticMesh->SetupAttachment(RootComponent);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APuzzleButton::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorTickEnabled(false);

	UE_LOG(LogTemp, Warning, TEXT("SUBSCRIBING"))

	FScriptDelegate BeginDelegateSubscriber;
	BeginDelegateSubscriber.BindUFunction(this, "OnSphereBeginOverlap");
	SphereCollision->OnComponentBeginOverlap.Add(BeginDelegateSubscriber);

	FScriptDelegate EndDelegateSubscriber;
	EndDelegateSubscriber.BindUFunction(this, "OnSphereEndOverlap");
	SphereCollision->OnComponentEndOverlap.Add(EndDelegateSubscriber);
}

// Called every frame
void APuzzleButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Animate(DeltaTime);
}

void APuzzleButton::ServerInteract_Implementation()
{
	SetActorTickEnabled(true);
}

bool APuzzleButton::IsGrabbable()
{
	return false;
}

void APuzzleButton::Animate_Implementation(float DeltaTime)
{
	CurrentPosition += AnimationSpeed * AnimationDirection * DeltaTime;
	if (CurrentPosition > 1.f || CurrentPosition < 0.f)
	{
		CurrentPosition = FMath::Clamp(CurrentPosition, 0.f, 1.f);
		SetActorTickEnabled(false);
	}
	StaticMesh->SetRelativeLocation(StartPosition + (FinishPosition - StartPosition) * CurrentPosition);
}

void APuzzleButton::OnSphereBeginOverlap(USphereComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(MainCharacter->GetController()))
		{
			if (PlayerController->IsLocalPlayerController())
			{
				StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
				StaticMesh->SetOverlayMaterial(OutlineOverlay);
			}
		}
	}
}

void APuzzleButton::OnSphereEndOverlap(USphereComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(MainCharacter->GetController()))
		{
			if (PlayerController->IsLocalPlayerController())
			{
				StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
				StaticMesh->SetOverlayMaterial(nullptr);
			}
		}
	}
}

