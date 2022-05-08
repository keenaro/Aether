#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NaroInventorySystem/Public/ItemInfo.h"
#include "UObject/ObjectMacros.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDirty);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDirtyIndex, int, index);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAROINVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void BeginPlay() override;	

	bool AddItem(FItem& itemToAdd);

	UFUNCTION(BlueprintCallable)
	void ClearInventory();

	void Resize(int inColumnSize, int inRowSize) { numberOfColumns = inColumnSize; numberOfRows = inRowSize; };

	UFUNCTION(BlueprintPure)
	const TArray<FItem>& GetInventoryItems() const { return itemArray.Items; }

	void SetInventoryItem(int index, const FItem& newItem, bool informServer = false);
	
// Event Displatchers
public:
	UPROPERTY(BlueprintAssignable)
	FOnDirty OnDirty;

	UPROPERTY(BlueprintAssignable)
	FOnDirtyIndex OnDirtyIndex;

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	FItem* FindSlot(FName slotName = TEXT(""));

private:
	UFUNCTION()
	void MarkInventoryDirty();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int numberOfColumns = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int numberOfRows = 5;

	UPROPERTY(ReplicatedUsing = MarkInventoryDirty, meta = (AllowPrivateAccess = "true"))
	FItemArray itemArray;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool isDirty = true;
};
