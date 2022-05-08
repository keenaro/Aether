#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "ItemInfo.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* icon = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<AActor> actorItem;
};

USTRUCT(BlueprintType)
struct FItem : public FFastArraySerializerItem
{
	GENERATED_BODY()
	FItem(FName inName = TEXT(""), int inQuantity = 0) : name(inName), quantity(inQuantity) {};

	UPROPERTY(BlueprintReadOnly)
	FName name = TEXT("");

	UPROPERTY(BlueprintReadOnly)
	int quantity = 0;

	bool IsEmpty() const { return name == TEXT("") || quantity == 0; };
	bool IsFull() const { return quantity == GetMaxQuantity(); };
	void Empty() { name = TEXT(""); quantity = 0; };
	static int GetMaxQuantity() { return 1024; };
	void Add(FItem& itemToAdd, int maxToAdd = -1);
	void Split(FItem& itemToSplit);
	void Swap(FItem& itemToSwap);
	void AddSwap(FItem& itemToAddSwap, int maxToAdd = -1);
};

USTRUCT()
struct FItemArray : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FItem>	Items;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FItem, FItemArray>(Items, DeltaParms, *this);
	}
};

template<>
struct TStructOpsTypeTraits<FItemArray> : public TStructOpsTypeTraitsBase2<FItemArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};

UCLASS()
class NAROINVENTORYSYSTEM_API UItemBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintPure, Category = "Item")
	static bool IsEmpty(UPARAM(ref) FItem& item) { return item.IsEmpty(); };

	UFUNCTION(BlueprintPure, Category = "Item")
	static bool IsFull(UPARAM(ref) FItem& item) { return item.IsFull(); };

	UFUNCTION(BlueprintCallable, Category = "Item")
	static void Empty(UPARAM(ref) FItem& item) { item.Empty(); };

	UFUNCTION(BlueprintCallable, Category = "Item")			
	static void Split(UPARAM(ref) FItem& itemToSplit, UPARAM(ref) FItem& itemToGetSplit) { itemToGetSplit.Split(itemToSplit); }

	UFUNCTION(BlueprintCallable, Category = "Item")
	static void Swap(UPARAM(ref) FItem& swapA, UPARAM(ref) FItem& swapB) { swapA.Swap(swapB); }

	UFUNCTION(BlueprintCallable, Category = "Item")
	static void AddSwap(UPARAM(ref) FItem& itemToAdd, UPARAM(ref) FItem& itemToReceive, int maxToAdd = -1) { itemToReceive.AddSwap(itemToAdd, maxToAdd); }
};


