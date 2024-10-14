// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconShop.h"
#include "NSLEconContainerItem.h"
#include "NSLEconMoney.h"
#include "NSLEconShopItemEntry.h"
#include "NSLEconTypes.h"

// Constructor - Initializes an empty inventory
UNSLEconShop::UNSLEconShop()
{
    // Create an empty container item for the inventory
    Inventory = NewObject<UNSLEconContainerItem>();
    //Inventory->Initialize();
}

// Add item to shop's inventory
void UNSLEconShop::AddItem(UNSLEconShopItemEntry* ShopItemEntry)
{
    if (Inventory && ShopItemEntry)
    {
        Inventory->AddItemEntry(ShopItemEntry);
    }
}

// Remove item from shop's inventory by its FGuid
void UNSLEconShop::RemoveItem(const FGuid& ItemId)
{
    if (Inventory)
    {
        Inventory->RemoveItemEntry(ItemId);
    }
}

const UNSLEconShopItemEntry* UNSLEconShop::GetItem(const FGuid& ItemId)
{
    return Cast<UNSLEconShopItemEntry>(Inventory->GetEntry(ItemId));
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

//
//// Buy an item from the shop (removes it from inventory and returns the item)
//const UNSLEconItem* UNSLEconShop::BuyItem(const FGuid& ItemId, UNSLEconMoney* MoneyToBuyWith)
//{
//    if (!Inventory)
//    {
//        UE_LOG(LogTemp, Error, TEXT("Inventory not initialized"));
//        return nullptr;
//    }
//
//    FNSLEconContainerEntry Entry = Inventory->GetEntry(ItemId);
//    if (!Entry.ItemPtr)
//    {
//        UE_LOG(LogTemp, Error, TEXT("No Entry found"));
//        return nullptr;
//    }
//
//    if (Entry.Quantity < 1)
//    {
//        UE_LOG(LogTemp, Error, TEXT("No items remaining in shop"));
//        return nullptr;
//    }
//
//    int64 PriceToPay = Entry.ItemPtr->Value->GetValueInUnits();
//
//    if (MoneyToBuyWith->GetValueInUnits() < PriceToPay)
//    {
//        UE_LOG(LogTemp, Error, TEXT("Not enough money"));
//        return nullptr;
//    }
//
//    MoneyToBuyWith->Substract(Entry.ItemPtr->Value);
//    Inventory->SetItemQuantityTo(Entry.Quantity - 1, ItemId);
//    return Entry.ItemPtr;
//}
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


