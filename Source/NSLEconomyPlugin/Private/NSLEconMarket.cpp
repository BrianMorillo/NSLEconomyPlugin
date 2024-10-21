// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconMarket.h"
#include "NSLEconItem.h"
#include "NSLEconTransaction.h"
#include "NSLEconMarketEntry.h"
//#include "Containers/Queue.h"

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

    if (!NewMarketEntry->ItemPtr || !NewMarketEntry->ItemPtr->GetValue()) 
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

void UNSLEconMarket::RegisterTransaction(const UNSLEconTransaction* Transaction)
{
    const UNSLEconMarketEntry* Entry = *ItemRegistry.Find(Transaction->ItemId);
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

    ItemsChangeQueue.Enqueue(Transaction);

    if (AdjustMarketOnItemUpdate)
    {
        UpdateMarket();
    }

}

void UNSLEconMarket::BindMarketItemUpdateDelegate(const FMarketItemUpdateDelegate& Delegate)
{
    MarketItemUpdateDel = Delegate;
}

void UNSLEconMarket::UpdateMarket()
{
    const UNSLEconTransaction* Transaction;
    while (ItemsChangeQueue.Dequeue(Transaction))
    {
        MarketItemUpdateDel.Execute(*ItemRegistry.Find(Transaction->ItemId), Transaction);
    }
}

const UNSLEconMarketEntry* UNSLEconMarket::GetEntry(const FGuid& ItemId)
{
    UNSLEconMarketEntry* EntryPtr = *ItemRegistry.Find(ItemId);
    if (!EntryPtr) {
        UE_LOG(LogTemp, Error, TEXT("Item not found."));
        return nullptr;
    }

    return EntryPtr;
}


