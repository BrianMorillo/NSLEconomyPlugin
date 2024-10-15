// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconMarket.h"
#include "NSLEconItem.h"
#include "NSLEconMarketEntry.h"
#include "Containers/Queue.h"

UNSLEconMarket::UNSLEconMarket()
{
}

void UNSLEconMarket::AddItemToMarket(UNSLEconMarketEntry* NewMarketEntry)
{
    if (!NewMarketEntry)
    {
        UE_LOG(LogTemp, Error, TEXT("UNSLEconMarketEntry is invalid"));
        return;
    }

    if (!NewMarketEntry->ItemPtr || !NewMarketEntry->ItemPtr->Value) 
    {
        UE_LOG(LogTemp, Error, TEXT("UNSLEconItem associated with entry is invalid"));
        return;
    }

    if (ItemRegistry.Find(NewMarketEntry->ItemPtr->GetId()))
    {
        UE_LOG(LogTemp, Error, TEXT("UNSLEconItem associated with entry is already included in the market"));
        return;
    }

    ItemRegistry.Add(NewMarketEntry->ItemPtr->GetId(), NewMarketEntry);
}

void UNSLEconMarket::ItemBuy(FGuid ItemId, int32 QuantityBought)
{
    RegisterItemChange(ItemId, QuantityBought);
}

void UNSLEconMarket::ItemSell(FGuid ItemId, int32 QuantitySold)
{
    RegisterItemChange(ItemId, -QuantitySold);
}

void UNSLEconMarket::RegisterItemChange(FGuid ItemId, int32 QuantityChange)
{
    UNSLEconMarketEntry* Entry = *ItemRegistry.Find(ItemId);
    if (!Entry)
    {
        UE_LOG(LogTemp, Error, TEXT("Item not found in market registry"));
        return;
    }

    if (!MarketItemUpdateDel.IsBound())
    {
        UE_LOG(LogTemp, Error, TEXT("No delegate bound to market item update"));
        return;
    }
    
    ItemsChangeQueue.Enqueue(Entry);

    if (AdjustMarketOnItemUpdate) 
    {
        UpdateMarket();
    }

}

void UNSLEconMarket::UpdateMarket()
{
    const UNSLEconMarketEntry* Entry;
    while (ItemsChangeQueue.Dequeue(Entry))
    {
        MarketItemUpdateDel.Execute(Entry);
    }
}


void UNSLEconMarket::BindMarketItemUpdateDelegate(const FMarketItemUpdateDelegate& Delegate)
{
    MarketItemUpdateDel = Delegate;
}

