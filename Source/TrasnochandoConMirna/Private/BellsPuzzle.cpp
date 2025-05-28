#include "BellsPuzzle.h"

#include "Bell.h"
#include "Components/AudioComponent.h"
#include "SimpleAnimatedObject.h"
#include "Earrings.h"

ABellsPuzzle::ABellsPuzzle()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BookshelfSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("PedestalSFX"));
	BookshelfSFX->SetIsReplicated(true);

	ErrorSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ErrorSFX"));
	ErrorSFX->SetIsReplicated(true);

	PuzzleSolution = { "MI", "FA", "SOL", "SOL", "FA", "MI", "RE", "MI", "RE", "DO" };
	SolutionIndex = 0;
	bPuzzleSolved = false;
}

void ABellsPuzzle::BeginPlay()
{
	Super::BeginPlay();
}

void ABellsPuzzle::ValidateSolution_Implementation(AInteractableObject* Sender)
{
	if (bPuzzleSolved) return;

	ABell* Bell = Cast<ABell>(Sender);
	if (Bell)
	{
		if (Bell->Tag == PuzzleSolution[SolutionIndex])
		{
			SolutionIndex++;
		}
		else
		{
			SolutionIndex = 0;
			OnPuzzleFailed();
		}

		if (SolutionIndex == PuzzleSolution.Num())
		{
			Bookshelf->PlayForward();
			Salt->PlayForward();
			IInteractable::Execute_SetCanInteract(Salt, true);
			OnPuzzleSolved();
		}
	}
}

void ABellsPuzzle::OnPuzzleFailed_Implementation()
{
	
}

void ABellsPuzzle::OnPuzzleSolved_Implementation()
{ 
	BookshelfSFX->Play();
}
