#include "PuzzleButton.h"

#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "ButtonsPuzzle.h"

// Sets default values
APuzzleButton::APuzzleButton()
{
	PrimaryActorTick.bCanEverTick = true;
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

void APuzzleButton::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	if (bCanInteract)
	{
		SetForwardAnimation();
		SetActorTickEnabled(true);
		if (Puzzle)
		{
			Puzzle->ValidateSolution();
			Super::ServerInteract_Implementation(MainCharacter);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("PUZZLE NOT SET"));
		}
	}
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
