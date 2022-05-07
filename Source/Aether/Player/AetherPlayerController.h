#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AetherPlayerController.generated.h"

UCLASS()
class AETHER_API AAetherPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void AcknowledgePossession(class APawn* P) override;
};
