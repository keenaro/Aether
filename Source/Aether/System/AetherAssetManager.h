#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AetherAssetManager.generated.h"

UCLASS()
class AETHER_API UAetherAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	virtual void StartInitialLoading() override;

private:
	void InitializeAbilitySystem();
};
