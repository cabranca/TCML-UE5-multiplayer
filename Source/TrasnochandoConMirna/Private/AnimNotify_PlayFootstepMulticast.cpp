#include "AnimNotify_PlayFootstepMulticast.h"

#include "GameFramework/Actor.h"
#include "Mirna.h"

void UAnimNotify_PlayFootstepMulticast::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	AMirna* Mirna = Cast<AMirna>(Owner);
	if (Mirna && Mirna->HasAuthority())
	{
		Mirna->PlayFootstepNotify();
	}
}
