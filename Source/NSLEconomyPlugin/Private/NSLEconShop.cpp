// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconShop.h"
#include "NSLEconContainerItem.h"
#include "NSLEconMoney.h"
#include "NSLEconShopItemEntry.h"
#include "NSLEconTypes.h"
#include "NSLEconMoneyUtil.h"

// Constructor - Initializes an empty inventory
UNSLEconShop::UNSLEconShop()
{
    // Create an empty container item for the inventory
    Inventory = NewObject<UNSLEconContainerItem>();
    //Inventory->Initialize();
}

// Add item to shop's inventory
void UNSLEconShop::AddItemEntry(UNSLEconShopItemEntry* ShopItemEntry)
{
    if (!Inventory)
    {
        UE_LOG(LogTemp, Error, TEXT("Shop Inventory not initialized"));
        return;
    }

    if (!ShopItemEntry)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid ShopItemEntry"));
        return;
    }
    
    int64 ItemValueInUnits = FMath::Abs(ShopItemEntry->ItemPtr->Value->GetValueInUnits());
    if (ItemValueInUnits > (INT64_MAX / ShopItemEntry->GetPriceMarkup()))
    {
        UE_LOG(LogTemp, Error, TEXT("Item addition failed: Item value * price markup > allowable max amount"));
        return;
    }

    Inventory->AddItemEntry(ShopItemEntry);
}

// Remove item from shop's inventory by its FGuid
void UNSLEconShop::RemoveItemEntry(const FGuid& ItemId)
{
    if (Inventory)
    {
        Inventory->RemoveItemEntry(ItemId);
    }
}

const FShopItemInfo UNSLEconShop::GetItemInfo(const FGuid& ItemId)
{
    UNSLEconItemEntry* Entry = Inventory->GetEntry(ItemId);
    if (!Entry)
    {
        return FShopItemInfo();
    }

    UNSLEconShopItemEntry* ItemEntry = Cast<UNSLEconShopItemEntry>(Entry);
    FShopItemInfo ItemInfo(
        ItemEntry->GetQuantity(),
        ItemEntry->ItemPtr,
        UNSLEconMoney::ScaledBy(ItemEntry->ItemPtr->Value, ItemEntry->GetPriceMarkup()));
    return ItemInfo;
}


TArray<FShopItemInfo> UNSLEconShop::GetItems()
{
    TArray<FShopItemInfo> ResultList;
    for (const auto& ItemEntry : Inventory->GetEntries())
    {
        UNSLEconShopItemEntry* ShopItemEntry = Cast<UNSLEconShopItemEntry>(ItemEntry);
        if (ItemEntry)
        {
            FShopItemInfo ItemInfo(
                ItemEntry->GetQuantity(),
                ItemEntry->ItemPtr,
                UNSLEconMoney::ScaledBy(ItemEntry->ItemPtr->Value, ShopItemEntry->GetPriceMarkup()));
            ResultList.Add(ItemInfo);
        }
    }

    return ResultList; // Return by value (copy)
}

void UNSLEconShop::AdjustItemMarkup(const FGuid& ItemId, float PriceMarkupPercentage)
{
    UNSLEconShopItemEntry* ItemEntry = Cast<UNSLEconShopItemEntry>(Inventory->GetEntry(ItemId));
    ItemEntry->SetPriceMarkup(PriceMarkupPercentage);
}


// Buy an item from the shop (removes it from inventory and returns the item)
const FShopItemInfo UNSLEconShop::BuyItem(const FGuid& ItemId, int32 QuantityToBuy, UNSLEconMoney* MoneyToBuyWith)
{
    if (!Inventory)
    {
        UE_LOG(LogTemp, Error, TEXT("Inventory not initialized"));
        return FShopItemInfo();
    }

    if (QuantityToBuy <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Quantity"));
        return FShopItemInfo();
    }

    UNSLEconShopItemEntry* Entry = Cast<UNSLEconShopItemEntry>(Inventory->GetEntry(ItemId));
    if (!Entry || !Entry->ItemPtr)
    {
        UE_LOG(LogTemp, Error, TEXT("No Entry found"));
        return FShopItemInfo();
    }

    if (Entry->GetQuantity() < QuantityToBuy)
    {
        UE_LOG(LogTemp, Error, TEXT("Not enough items remaining in shop"));
        return FShopItemInfo();
    }

    // Scales the item price by the amount of items wanted
    UNSLEconMoney* TotalMoneyToPay = UNSLEconMoney::ScaledBy(Entry->ItemPtr->Value, QuantityToBuy);

    // checks if scaling was not successful 
    if (TotalMoneyToPay == nullptr)
    {
        return FShopItemInfo();
    }

    // Attempts money substraction operation and checks if it was successful
    if (MoneyToBuyWith->Substract(TotalMoneyToPay) == nullptr)
    {
        return FShopItemInfo();
    }

    Entry->SetQuantity(Entry->GetQuantity() - QuantityToBuy);
    return FShopItemInfo(QuantityToBuy, Entry->ItemPtr, TotalMoneyToPay);
}
//
//// Get the shop's inventory
//const TMap<FString, FGuid> UNSLEconShop::GetItemsId() const
//{
//    return Inventory->GetItemsId();
//}
//
//const FNSLEconContainerEntry UNSLEconShop::GetItemDetails(const FGuid& ItemId) const
//{
//    return Inventory->GetEntry(ItemId);
//}


