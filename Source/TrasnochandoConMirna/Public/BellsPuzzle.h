// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"

#include "BellsPuzzle.generated.h"

UCLASS()
class TRASNOCHANDOCONMIRNA_API ABellsPuzzle : public AActor, public IPuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABellsPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(Server, Reliable) void ValidateSolution(AActor* Sender) override;

private:
	TArray<FName> PuzzleSolution;
	uint8 SolutionIndex;
	bool bPuzzleSolved;

	UFUNCTION(NetMulticast, Reliable) void MulticastValidateSolution() override;
};
