// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconContainerItem.h"
#include "NSLEconQuantityItem.h"

// Constructor implementation
UNSLEconContainerItem::UNSLEconContainerItem()
{
    // Constructor logic here if needed
}

// Add an item to the container
void UNSLEconContainerItem::AddItem(UNSLEconQuantityItem* NewItem)
{
    if (NewItem)
    {
        ContainedItems.Add(NewItem->GetId(), NewItem);
    }
}

// Remove an item from the container by its ID
void UNSLEconContainerItem::RemoveItem(const FGuid& ItemId)
{
    ContainedItems.Remove(ItemId);
}

// Get an item from the container by its ID
UNSLEconItem* UNSLEconContainerItem::GetItem(const FGuid& ItemId) const
{
    if (ContainedItems.Contains(ItemId))
    {
        return *ContainedItems.Find(ItemId);
    }
    return nullptr;
}