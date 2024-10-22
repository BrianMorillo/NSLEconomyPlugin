// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconShop.h"
#include "NSLEconContainerItem.h"
#include "NSLEconMoney.h"
#include "NSLEconShopItemEntry.h"
#include "NSLEconTypes.h"
#include "NSLEconPurchaseTransaction.h"
#include "NSLEconProfile.h"
#include "NSLEconMarket.h"
#include "NSLEconMoneyUtil.h"

UNSLEconShop::UNSLEconShop(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ShopProfile = ObjectInitializer.CreateDefaultSubobject<UNSLEconProfile>(this, TEXT("UNSLEconShopProfile"));
    Market = nullptr;
}

// Add item to shop's inventory
void UNSLEconShop::AddItemEntry(UNSLEconShopItemEntry* ShopItemEntry)
{
    if (!ShopProfile)
    {
        UE_LOG(LogTemp, Error, TEXT("ShopProfile not initialized"));
        return;
    }

    if (!ShopItemEntry)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid ShopItemEntry"));
        return;
    }
    
    int64 ItemValueInUnits = FMath::Abs(ShopItemEntry->ItemPtr->GetValue()->GetValueInUnits());
    if (ItemValueInUnits > (INT64_MAX / ShopItemEntry->GetPriceMarkup()))
    {
        UE_LOG(LogTemp, Error, TEXT("Item addition failed: Item value * price markup > allowable max amount"));
        return;
    }

    ShopProfile->AddItemEntry(ShopItemEntry);
}

// Remove item from shop's inventory by its FGuid
void UNSLEconShop::RemoveItemEntry(const FGuid& ItemId)
{
    if (ShopProfile)
    {
        ShopProfile->RemoveItemEntry(ItemId);
    }
}

const FShopItemInfo UNSLEconShop::GetItemInfo(const FGuid& ItemId)
{
    UNSLEconItemEntry* Entry = ShopProfile->GetEntry(ItemId);
    if (!Entry)
    {
        return FShopItemInfo();
    }

    UNSLEconShopItemEntry* ItemEntry = Cast<UNSLEconShopItemEntry>(Entry);
    FShopItemInfo ItemInfo(
        ItemEntry->GetQuantity(),
        ItemEntry->ItemPtr,
        UNSLEconMoney::ScaledBy(ItemEntry->ItemPtr->GetValue(), ItemEntry->GetPriceMarkup()));
    return ItemInfo;
}


TArray<FShopItemInfo> UNSLEconShop::GetItems()
{
    TArray<FShopItemInfo> ResultList;
    for (const auto& ItemEntry : ShopProfile->GetEntries())
    {
        UNSLEconShopItemEntry* ShopItemEntry = Cast<UNSLEconShopItemEntry>(ItemEntry);
        if (ItemEntry)
        {
            FShopItemInfo ItemInfo(
                ItemEntry->GetQuantity(),
                ItemEntry->ItemPtr,
                UNSLEconMoney::ScaledBy(ItemEntry->ItemPtr->GetValue(), ShopItemEntry->GetPriceMarkup()));
            ResultList.Add(ItemInfo);
        }
    }

    return ResultList; // Return by value (copy)
}

void UNSLEconShop::AdjustItemMarkup(const FGuid& ItemId, float PriceMarkupPercentage)
{
    UNSLEconShopItemEntry* ItemEntry = Cast<UNSLEconShopItemEntry>(ShopProfile->GetEntry(ItemId));
    ItemEntry->SetPriceMarkup(PriceMarkupPercentage);
}

void UNSLEconShop::BuyItem(const FGuid& ItemId, int32 QuantityToPurchase, UNSLEconProfile* Buyer)
{

    UNSLEconShopItemEntry* ShopEntry = Cast<UNSLEconShopItemEntry>(ShopProfile->GetEntry(ItemId));
    if (!ShopEntry || !ShopEntry->ItemPtr)
    {
        UE_LOG(LogTemp, Error, TEXT("No entry for item found in seller profile"));
        return;
    }

    UNSLEconMoney* TotalMoneyToPay = 
        UNSLEconMoney::ScaledBy(ShopEntry->ItemPtr->GetValue(), ShopEntry->GetPriceMarkup());
    if (!TotalMoneyToPay)
    {
        return;
    }

    // Creates and executes transaction
    UNSLEconPurchaseTransaction* Transaction = NewObject<UNSLEconPurchaseTransaction>();
    Transaction->Buyer = Buyer;
    Transaction->QuantityToPurchase = QuantityToPurchase;
    Transaction->ItemId = ItemId;
    Transaction->Seller = ShopProfile;
    Transaction->MarketTransactionType = ETransactionType::Buy;
    Transaction->PurchasePrice = TotalMoneyToPay;
    Transaction->Execute();

    if (Market) 
    {
        Market->RegisterTransaction(Transaction);
    }
}


