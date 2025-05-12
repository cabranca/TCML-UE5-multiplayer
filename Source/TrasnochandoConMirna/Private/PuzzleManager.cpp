// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleManager.h"

#include "Puzzle.h"
#include "StatuesPuzzle.h"

// Sets default values
APuzzleManager::APuzzleManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();

	CurrentPuzzle = StatuesPuzzle;
}

void APuzzleManager::ServerValidateSolution_Implementation()
{
	CurrentPuzzle->ValidateSolution();
}
