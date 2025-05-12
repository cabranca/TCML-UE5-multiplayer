// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleManager.generated.h"

class IPuzzle;
class AStatuesPuzzle;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APuzzleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleManager();

	UFUNCTION(Server, Reliable) void ServerValidateSolution();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	IPuzzle* CurrentPuzzle;

	UPROPERTY(EditAnywhere, Category = "Puzzles") AStatuesPuzzle* StatuesPuzzle;
};
