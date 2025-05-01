// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleManager.generated.h"

class AStatue;
class APedestal;
class UAudioComponent;
class APuzzleDoor;
class UBoxComponent;

UCLASS()
class TRASNOCHANDOCONMIRNA_API APuzzleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleManager();

	UFUNCTION(Server, Reliable)
	void ServerOnStatuePosed();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* ClockSFX;

	UPROPERTY(EditAnywhere)
	UAudioComponent* ErrorSFX;

	UPROPERTY(EditAnywhere)
	TArray<APuzzleDoor*> Doors;

	bool bStatueSet = false;
	bool bPuzzleSolved = false;

	UFUNCTION(NetMulticast, Reliable)
	void OnStatuePosed();
	UFUNCTION(NetMulticast, Reliable)
	void OnClockFinished();
};
