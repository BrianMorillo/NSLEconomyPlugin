// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconMarket.h"
#include "NSLEconItem.h"
#include "NSLEconShop.h"

UNSLEconMarket::UNSLEconMarket()
{
    // Registries start out empty
}
/*
UNSLEconItem* UNSLEconMarket::GetItemFromMarket(const FGuid& ItemId) const
{
    if (ItemRegistry.Contains(ItemId))
    {
        return ItemRegistry[ItemId];
    }
    return nullptr;
}

// Add a new shop to the market's registry
void UNSLEconMarket::AddShopToMarket(UNSLEconShop* NewShop)
{
    if (NewShop)
    {
        FGuid ShopId = FGuid::NewGuid();
        ShopRegistry.Add(ShopId, NewShop);
    }
}

// Remove a shop from the market's registry by its FGuid
void UNSLEconMarket::RemoveShopFromMarket(const FGuid& ShopId)
{
    ShopRegistry.Remove(ShopId);
}

// Get a shop from the market by its FGuid
UNSLEconShop* UNSLEconMarket::GetShopFromMarket(const FGuid& ShopId) const
{
    if (ShopRegistry.Contains(ShopId))
    {
        return ShopRegistry[ShopId];
    }
    return nullptr;
}
*/