// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

struct FAIStimulus;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class TRASNOCHANDOCONMIRNA_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	void OnSensed(AActor* Origin, FAIStimulus Stimulus);
	void HandleSightSense(AActor* Origin, FAIStimulus Stimulus);
	void HandleSoundSense(AActor* Origin, FAIStimulus Stimulus);
};
