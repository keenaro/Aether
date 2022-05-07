#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AetherPlayerState.generated.h"

class UAetherAbilitySystemComponent;
class UAetherAttributeSet;

UCLASS()
class AETHER_API AAetherPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AAetherPlayerState();

// Getters
public:
	UAetherAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; };
	UAetherAttributeSet* GetAttributeSet() const { return AttributeSet; };

protected:
	UPROPERTY()
	UAetherAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UAetherAttributeSet* AttributeSet;
};
