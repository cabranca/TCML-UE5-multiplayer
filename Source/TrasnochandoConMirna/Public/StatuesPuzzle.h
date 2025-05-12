// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"

#include "StatuesPuzzle.generated.h"

class APuzzleDoor;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AStatuesPuzzle : public AActor, public IPuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatuesPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	void ValidateSolution() override;

private:
	UPROPERTY(EditAnywhere)
	UAudioComponent* ClockSFX;

	UPROPERTY(EditAnywhere)
	UAudioComponent* ErrorSFX;

	UPROPERTY(EditAnywhere)
	TArray<APuzzleDoor*> Doors;

	bool bStatueSet = false;
	bool bPuzzleSolved = false;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastValidateSolution() override;

	UFUNCTION(NetMulticast, Reliable)
	void OnClockFinished() ;
};
