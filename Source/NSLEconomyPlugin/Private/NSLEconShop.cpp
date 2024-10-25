// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconShop.h"
#include "NSLEconContainerItem.h"
#include "NSLEconMoney.h"
#include "NSLEconPricedItemEntry.h"
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
void UNSLEconShop::AddItemEntry(UNSLEconPricedItemEntry* ShopItemEntry)
{
    if (!ShopItemEntry)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid ShopItemEntry"));
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

UNSLEconPricedItemEntry* UNSLEconShop::GetItemEntry(const FGuid& ItemId)
{
    UNSLEconItemEntry* Entry = ShopProfile->GetEntry(ItemId);
    if (!Entry)
    {
        return nullptr;
    }

    return Cast<UNSLEconPricedItemEntry>(Entry);
}


TArray<UNSLEconPricedItemEntry*> UNSLEconShop::GetItems()
{
    TArray<UNSLEconPricedItemEntry *> ResultList;
    for (const auto& ItemEntry : ShopProfile->GetEntries())
    {
        ResultList.Add(Cast<UNSLEconPricedItemEntry>(ItemEntry));
    }

    return ResultList; 
}

void UNSLEconShop::AdjustItemPrice(const FGuid& ItemId, UNSLEconMoney* NewPrice)
{
    UNSLEconItemEntry* ItemEntry = ShopProfile->GetEntry(ItemId);

    if (!ItemEntry) {
        return;
    }

    Cast<UNSLEconPricedItemEntry>(ItemEntry)->GetItemPrice()->SetTo(NewPrice);
}

void UNSLEconShop::BuyItem(const FGuid& ItemId, int32 QuantityToPurchase, UNSLEconProfile* Buyer)
{
    const UNSLEconItemEntry* ItemEntry = ShopProfile->GetEntry(ItemId);

    if (!ItemEntry) {
        return;
    }

    const UNSLEconPricedItemEntry* ShopEntry = Cast<UNSLEconPricedItemEntry>(ItemEntry);
    
    // Creates and executes transaction
    UNSLEconPurchaseTransaction* Transaction = NewObject<UNSLEconPurchaseTransaction>();
    Transaction->Buyer = Buyer;
    Transaction->QuantityToPurchase = QuantityToPurchase;
    Transaction->ItemId = ItemId;
    Transaction->Seller = ShopProfile;
    Transaction->MarketTransactionType = EPurchaseTransactionType::Buy;
    Transaction->PurchasePrice = ShopEntry->GetItemPrice();
    Transaction->Execute();

    if (Market) 
    {
        Market->ProcessTransaction(Transaction);
    }
}


