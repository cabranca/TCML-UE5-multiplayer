// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleManager.h"

#include "Statue.h"
#include "Pedestal.h"
#include "Components/AudioComponent.h"
#include "PuzzleDoor.h"
#include "Components/BoxComponent.h"

// Sets default values
APuzzleManager::APuzzleManager()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ClockSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ClockSFX"));
	ClockSFX->SetupAttachment(RootComponent);
	ClockSFX->SetIsReplicated(true);

	ErrorSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ErrorSFX"));
	ErrorSFX->SetupAttachment(RootComponent);
	ErrorSFX->SetIsReplicated(true);
}

void APuzzleManager::ServerOnStatuePosed_Implementation()
{
	OnStatuePosed();
}

// Called when the game starts or when spawned
void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate ClockDelegateSubscriber;
	ClockDelegateSubscriber.BindUFunction(this, "OnClockFinished");
	ClockSFX->OnAudioFinished.Add(ClockDelegateSubscriber);
}

void APuzzleManager::OnStatuePosed_Implementation()
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

void APuzzleManager::OnClockFinished_Implementation()
{
	if (!bPuzzleSolved)
	{
		ErrorSFX->Play();
		bStatueSet = false;
	}
}
