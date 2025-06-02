// Fill out your copyright notice in the Description page of Project Settings.


#include "GemsPuzzle.h"

#include "GemLock.h"

AGemsPuzzle::AGemsPuzzle()
{
	PrimaryActorTick.bCanEverTick = true;

	PuzzleSolution = { {"WHITE", 1}, {"BLUE", 0}, {"GREEN", 2}, {"PURPLE", 0}, {"PINK", 2}, {"RED", 0} };
	CurrentGemPositions = { {"WHITE", 0}, {"BLUE", 0}, {"GREEN", 0}, {"PURPLE", 0}, {"PINK", 0}, {"RED", 0} };
}

void AGemsPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGemsPuzzle::ValidateSolution_Implementation(AInteractableObject* Trigger)
{
	if (bPuzzleSolved) return;

	AGemLock* GemLock = Cast<AGemLock>(Trigger);
	if (GemLock)
	{
		CurrentGemPositions[GemLock->Tag] = (CurrentGemPositions[GemLock->Tag] + 1) % 3;

		bool PuzzleSolved = true;
		for (auto& [Tag, Pos] : CurrentGemPositions)
		{
			if (Pos != PuzzleSolution[Tag])
			{
				PuzzleSolved = false;
			}
		}
		if (PuzzleSolved)
		{
			OnPuzzleSolved();
		}
	}
}

void AGemsPuzzle::OnPuzzleSolved_Implementation()
{
	for (auto& lock : GemLocks)
	{
		lock->OpenLock();
	}
}
