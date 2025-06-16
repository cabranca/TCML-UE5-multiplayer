#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

// Forward delcarations
struct FAIStimulus;
class AMainCharacter;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AMyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere) UBehaviorTree* BehaviorTree;

	UFUNCTION() void OnNoiseHeard(const FNoiseData& Noise);
};
