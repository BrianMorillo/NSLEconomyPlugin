// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconShop.h"
#include "NSLEconContainerItem.h"


// Constructor - Initializes an empty inventory
UNSLEconShop::UNSLEconShop()
{
    // Create an empty container item for the inventory
    Inventory = NewObject<UNSLEconContainerItem>();
}

// Add item to shop's inventory
void UNSLEconShop::AddItemToInventory(UNSLEconQuantityItem* NewItem)
{
    if (Inventory && NewItem)
    {
        Inventory->AddItem(NewItem);
    }
}

// Remove item from shop's inventory by its FGuid
void UNSLEconShop::RemoveItemFromInventory(const FGuid& ItemId)
{
    if (Inventory)
    {
        Inventory->RemoveItem(ItemId);
    }
}

// Buy an item from the shop (removes it from inventory and returns the item)
UNSLEconItem* UNSLEconShop::BuyItem(const FGuid& ItemId)
{
    if (Inventory)
    {
        UNSLEconItem* Item = Inventory->GetItem(ItemId);
        if (Item)
        {
            Inventory->RemoveItem(ItemId);
            return Item;
        }
    }
    return nullptr; // Item not found or not available
}

// Get the shop's inventory
UNSLEconContainerItem* UNSLEconShop::GetInventory() const
{
    return Inventory;
}