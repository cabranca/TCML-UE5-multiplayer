#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Mirna.generated.h"

class UAIBehavior;

UCLASS()
class TRASNOCHANDOCONMIRNA_API AMirna : public ACharacter
{
	GENERATED_BODY()

public:
	AMirna();

protected:
	virtual void BeginPlay() override;
	
private:
	friend class UBTTask_Patrol;

	UPROPERTY(EditAnywhere)
	UAIBehavior* AIBehavior;

	UPROPERTY(EditAnywhere, Category = "Speed") float WalkSpeed = 200.f;
};
