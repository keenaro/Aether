#include "AetherProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AAetherProjectile::AAetherProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
}

