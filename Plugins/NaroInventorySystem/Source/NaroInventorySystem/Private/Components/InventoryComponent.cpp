#include "NaroInventorySystem/Public/Components/InventoryComponent.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	itemArray.Items.SetNum(numberOfColumns * numberOfRows);
	itemArray.MarkArrayDirty();
}

bool UInventoryComponent::AddItem(FItem& itemToAdd)
{
	// Start assigning to same name slots that have some space.
	for (FItem& itemEntry : itemArray.Items)
	{
		if (itemEntry.name == itemToAdd.name && itemEntry.quantity < FItem::GetMaxQuantity())
		{
			itemEntry.Add(itemToAdd);
			itemArray.MarkItemDirty(itemToAdd);
			MarkInventoryDirty();

			if (itemToAdd.quantity == 0) break;
		}
	}

	if (itemToAdd.quantity > 0)
	{
		// Start assigning to empty slots.
		for (FItem& itemEntry : itemArray.Items)
		{
			if (itemEntry.IsEmpty())
			{
				itemEntry = itemToAdd;
				itemEntry.quantity = 0;
				itemEntry.Add(itemToAdd);
				itemArray.MarkItemDirty(itemToAdd);
				MarkInventoryDirty();

				if (itemToAdd.quantity == 0) break;
			}
		}
	}

	return itemToAdd.quantity == 0;
}

void UInventoryComponent::SetInventoryItem(int index, const FItem& newItem, bool informServer)
{
	if (IsNetMode(NM_ListenServer) || !informServer) {
		auto& item = itemArray.Items[index];
		item.name = newItem.name;
		item.quantity = newItem.quantity;

		itemArray.MarkItemDirty(item);
		OnDirtyIndex.Broadcast(index);
	}
}

void UInventoryComponent::ClearInventory()
{
	const FItem emptyItem;

	for (FItem& itemEntry : itemArray.Items)
	{
		itemEntry = emptyItem;
		itemArray.MarkItemDirty(itemEntry);
	}

	MarkInventoryDirty();

	//I wonder if itemArray.MarkArrayDirty would work here? #todo
}

FItem* UInventoryComponent::FindSlot(FName slotName)
{
	for(FItem& itemEntry : itemArray.Items)
	{
		if(itemEntry.name == slotName)
		{
			return &itemEntry;
		}
	}

	return nullptr;
}

void UInventoryComponent::MarkInventoryDirty()
{
	isDirty = true;
	OnDirty.Broadcast();
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, itemArray);
}

