#include "PuzzleButton.h"

#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "ButtonsPuzzle.h"
#include "SimpleAnimatorComponent.h"

// Sets default values
APuzzleButton::APuzzleButton()
{
	PrimaryActorTick.bCanEverTick = true;

	Animator = CreateDefaultSubobject<USimpleAnimatorComponent>(TEXT("Animator"));
	Animator->TargetMesh = StaticMesh;
}

// Called when the game starts or when spawned
void APuzzleButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APuzzleButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzleButton::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	if (bCanInteract)
	{
		Animator->PlayForward();
		if (Puzzle)
		{
			Puzzle->ValidateSolution(this);
			Super::ServerInteract_Implementation(MainCharacter);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("PUZZLE NOT SET"));
		}
	}
}

void APuzzleButton::Release()
{
	Animator->PlayReverse();
}
