#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"

#include "StatuesPuzzle.generated.h"

class APuzzleDoor;
class AStatue;

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
	UFUNCTION(Server, Reliable) void ValidateSolution(AActor* Sender) override;

private:
	UPROPERTY(EditAnywhere) UAudioComponent* ClockSFX;

	UPROPERTY(EditAnywhere) UAudioComponent* ErrorSFX;

	UPROPERTY(EditAnywhere) TArray<APuzzleDoor*> Doors;

	UPROPERTY(EditAnywhere) TArray<AStatue*> Statues;

	bool bStatueSet = false;
	bool bPuzzleSolved = false;

	UFUNCTION(NetMulticast, Reliable) void MulticastValidateSolution() override;

	UFUNCTION(NetMulticast, Reliable) void OnClockFinished();
};
