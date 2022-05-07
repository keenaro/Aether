#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AetherDamageExecCalculation.generated.h"

UCLASS()
class AETHER_API UAetherDamageExecCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
	UAetherDamageExecCalculation();

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
