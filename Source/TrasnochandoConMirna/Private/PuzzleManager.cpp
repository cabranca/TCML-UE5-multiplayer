#include "PuzzleManager.h"

#include "Puzzle.h"
#include "StatuesPuzzle.h"
#include "ButtonsPuzzle.h"

// Sets default values
APuzzleManager::APuzzleManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();

	CurrentPuzzle = ButtonsPuzzle;
}

void APuzzleManager::ServerValidateSolution_Implementation()
{
	CurrentPuzzle->ValidateSolution();
}
