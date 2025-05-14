#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"

#include "ButtonsPuzzle.generated.h"

UCLASS()
class TRASNOCHANDOCONMIRNA_API AButtonsPuzzle : public AActor, public IPuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonsPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable) void ValidateSolution() override;

protected:
	UFUNCTION(NetMulticast, Reliable) void MulticastValidateSolution() override;

};
