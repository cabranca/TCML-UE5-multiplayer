#include "BellsPuzzle.h"

#include "Bell.h"

ABellsPuzzle::ABellsPuzzle()
{
	PrimaryActorTick.bCanEverTick = false;

	PuzzleSolution = { "MI", "FA", "SOL", "SOL", "FA", "MI", "RE", "MI", "RE", "DO" };
	SolutionIndex = 0;
	bPuzzleSolved = false;
}

void ABellsPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABellsPuzzle::ValidateSolution_Implementation(AActor* Sender)
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
		}

		if (SolutionIndex == PuzzleSolution.Num())
		{
			bPuzzleSolved = true;
			UE_LOG(LogTemp, Warning, TEXT("PUZZLE SOLVED"));
		}
	}
}

void ABellsPuzzle::MulticastValidateSolution_Implementation()
{

}
