#include "PuzzleButton.h"

#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "ButtonsPuzzle.h"
#include "SimpleAnimatorComponent.h"

// Sets default values
APuzzleButton::APuzzleButton()
{
	PrimaryActorTick.bCanEverTick = true;

	Translator = CreateDefaultSubobject<USimpleAnimatorComponent>(TEXT("Translator"));
	Translator->TargetMesh = StaticMesh;
}

void APuzzleButton::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	if (bCanInteract)
	{
		Translator->PlayForward();
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
	Translator->PlayReverse();
}
