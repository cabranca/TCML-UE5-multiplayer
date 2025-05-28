#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

// Game mode only used on the gameplay phase.
UCLASS()
class TRASNOCHANDOCONMIRNA_API AGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
