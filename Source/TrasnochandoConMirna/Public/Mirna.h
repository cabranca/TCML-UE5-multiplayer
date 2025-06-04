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

public:
	void PlayFootstepNotify();
	
private:
	friend class UBTTask_Patrol;

	UPROPERTY(EditAnywhere) UAIBehavior* AIBehavior;

	UPROPERTY(EditAnywhere, Category = "Speed") float WalkSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Audio") USoundBase* FootstepSFX;

	UPROPERTY(EditAnywhere, Category = "Audio") USoundAttenuation* FootstepSFXAttenuation;

	UFUNCTION(NetMulticast, Reliable) void MulticastPlayFootstepSound(const FVector& Location);
};
