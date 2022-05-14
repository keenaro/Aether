#pragma once

#include "CoreMinimal.h"
#include "Aether/AbilitySystem/Abilities/AetherGameplayAbility.h"
#include "AetherProjectileAbility.generated.h"

class AAetherProjectile;

UCLASS()
class AETHER_API UAetherProjectileAbility : public UAetherGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<AAetherProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Damage;

protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
