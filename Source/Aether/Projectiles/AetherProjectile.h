#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AetherProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class AETHER_API AAetherProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAetherProjectile();

public:
	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	bool CanDamageInstigator = false;

protected:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
