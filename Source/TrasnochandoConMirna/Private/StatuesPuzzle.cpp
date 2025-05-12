// Fill out your copyright notice in the Description page of Project Settings.


#include "StatuesPuzzle.h"

#include "Components/AudioComponent.h"
#include "PuzzleDoor.h"

// Sets default values
AStatuesPuzzle::AStatuesPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ClockSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ClockSFX"));
	ClockSFX->SetIsReplicated(true);

	ErrorSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ErrorSFX"));
	ErrorSFX->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AStatuesPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	ClockSFX->OnAudioFinished.AddDynamic(this, &AStatuesPuzzle::OnClockFinished);
}

// Called every frame
void AStatuesPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStatuesPuzzle::ValidateSolution_Implementation()
{
	MulticastValidateSolution();
}

void AStatuesPuzzle::MulticastValidateSolution_Implementation()
{
	if (!bStatueSet)
	{
		ClockSFX->Play();
		bStatueSet = true;
	}
	else
	{
		bPuzzleSolved = true;
		ClockSFX->Stop();
		for (auto& Door : Doors)
		{
			Door->OpenDoor();
		}
	}
}

void AStatuesPuzzle::OnClockFinished_Implementation()
{
	if (!bPuzzleSolved)
	{
		ErrorSFX->Play();
		bStatueSet = false;
	}
}
