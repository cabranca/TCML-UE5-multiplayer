// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonsPuzzle.h"

// Sets default values
AButtonsPuzzle::AButtonsPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AButtonsPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonsPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonsPuzzle::ValidateSolution_Implementation()
{}

void AButtonsPuzzle::MulticastValidateSolution_Implementation()
{
}

