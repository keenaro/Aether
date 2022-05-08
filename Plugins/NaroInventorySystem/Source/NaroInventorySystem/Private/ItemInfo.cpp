#include "NaroInventorySystem/Public/ItemInfo.h"

void FItem::Add(FItem& itemToAdd, int maxToAdd /*= -1*/)
{
	name = itemToAdd.name;

	const int amount = FMath::Min3(maxToAdd > -1 ? maxToAdd : GetMaxQuantity(), itemToAdd.quantity, GetMaxQuantity() - quantity);
	itemToAdd.quantity -= amount;
	quantity += amount;

	if (itemToAdd.quantity == 0)
	{
		itemToAdd.Empty();
	}
}

void FItem::Split(FItem& itemToSplit)
{
	const int halved = FMath::CeilToInt((float)itemToSplit.quantity / 2.f);
	itemToSplit.quantity -= halved;

	if (itemToSplit.name == name)
	{
		quantity += halved;
	}
	else
	{
		*this = itemToSplit;
		quantity = halved;
	}

	if (itemToSplit.quantity == 0) itemToSplit.Empty();
}

void FItem::Swap(FItem& itemToSwap)
{
	const FItem cachedItemToAdd = *this;
	*this = itemToSwap;
	itemToSwap = cachedItemToAdd;
}

void FItem::AddSwap(FItem& itemToAddSwap, int maxToAdd /*= -1*/)
{
	if (itemToAddSwap.name != name && name != TEXT(""))
	{
		Swap(itemToAddSwap);
		return;
	};

	Add(itemToAddSwap, maxToAdd);
}
