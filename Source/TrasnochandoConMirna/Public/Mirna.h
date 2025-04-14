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

private:
	UPROPERTY(EditAnywhere)
	UAIBehavior* AIBehavior;
};
