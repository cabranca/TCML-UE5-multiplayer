#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

struct FAIStimulus;

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

	
	UFUNCTION()
	void OnSensed(AActor* Origin, FAIStimulus Stimulus);
	void HandleSightSense(AActor* Origin, FAIStimulus Stimulus);
	void HandleSoundSense(AActor* Origin, FAIStimulus Stimulus);
};
