#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PlayFootstepMulticast.generated.h"

/**
 * 
 */
UCLASS()
class TRASNOCHANDOCONMIRNA_API UAnimNotify_PlayFootstepMulticast : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
