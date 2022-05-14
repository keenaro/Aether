#include "AetherProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Aether/Character/AetherCharacter.h"
#include "GameplayEffect.h"
#include "Aether/AbilitySystem/AetherAbilitySystemComponent.h"

AAetherProjectile::AAetherProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
}

void AAetherProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!IsNetMode(NM_ListenServer)) return;

	AAetherCharacter* Character = Cast<AAetherCharacter>(OtherActor);

	if (!Character) return;
	if (!CanDamageInstigator && OtherActor == GetInstigator()) return;
	
	FGameplayEffectSpec* Spec = DamageEffectSpecHandle.Data.Get();
	UAbilitySystemComponent* InstigatorAbilitySystem = Spec->GetEffectContext().GetInstigatorAbilitySystemComponent();
	InstigatorAbilitySystem->ApplyGameplayEffectSpecToTarget(*Spec, Character->GetAbilitySystemComponent());

	Destroy();
}

