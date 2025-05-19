#include "PuzzleButton.h"

#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "ButtonsPuzzle.h"

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
	if (bInteractEnabled)
	{
		SetForwardAnimation();
		SetActorTickEnabled(true);
		if (Puzzle)
		{
			Puzzle->ValidateSolution();
		}
		bInteractEnabled = false;
	}

	MulticastInteract();
}

void APuzzleButton::MulticastInteract_Implementation()
{
	bInteractEnabled = false;
	StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	StaticMesh->SetOverlayMaterial(nullptr);
}

bool APuzzleButton::IsGrabbable()
{
	return false;
}

void APuzzleButton::SetOverlay(bool bEnabled)
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

void APuzzleButton::EnableInteraction()
{
	bInteractEnabled = true;
	StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

void APuzzleButton::SetForwardAnimation()
{
	AnimationDirection = 1;
}

void APuzzleButton::SetBackwardsAnimation()
{
	AnimationDirection = -1;
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

void APuzzleButton::OnRep_AnimationDirection()
{
	
}

void APuzzleButton::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APuzzleButton, AnimationDirection);
}
