#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AetherAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UAetherAbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

class UAetherGameplayAbility;
class AAetherCharacter;

UCLASS()
class AETHER_API UAetherAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void InitialiseAbilities(AAetherCharacter* Character, TArray<TSubclassOf<UAetherGameplayAbility>>& Abilities);

	virtual void ReceiveDamage(UAetherAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);

// Delegates
public:
	FReceivedDamageDelegate ReceivedDamage;

private:
	bool initialisedAbilities = false;
};
