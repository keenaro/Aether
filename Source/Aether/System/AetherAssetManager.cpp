#include "AetherAssetManager.h"
#include "AbilitySystemGlobals.h"

void UAetherAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	InitializeAbilitySystem();
}

void UAetherAssetManager::InitializeAbilitySystem()
{
	UAbilitySystemGlobals::Get().InitGlobalData();
}