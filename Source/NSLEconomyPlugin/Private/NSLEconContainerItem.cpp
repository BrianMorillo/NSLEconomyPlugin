// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconContainerItem.h"
#include "NSLEconItem.h"
#include "NSLEconTypes.h"
#include "NSLEconMoney.h"
#include "NSLEconItemEntry.h"
#include "NSLEconMoneyUtil.h"

UNSLEconContainerItem::UNSLEconContainerItem(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UNSLEconContainerItem::AddItemEntry(UNSLEconItemEntry* ItemEntry)
{
    if (!UNSLEconMoneyUtil::AreValidForOperation(GetValue(), ItemEntry->ItemPtr->GetValue()))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid or mismatching UNSLEconContainerItem and UNSLEconItemEntry currencies"));
        return;
    }

    // Checks if item is already included and changes quantity instead of reincluding it
    FGuid ItemEntryId = ItemEntry->ItemPtr->GetId();
    UNSLEconItemEntry* FoundEntry = FindEntry(ItemEntryId);
    if (FoundEntry)
    {
        FoundEntry->SetQuantity(FoundEntry->GetQuantity() + ItemEntry->GetQuantity());
        return;
    }

    ItemEntriesMap.Add(ItemEntryId, ItemEntry);
    OrderedEntriesIdList.Add(ItemEntryId);
}
void UNSLEconContainerItem::RemoveItemEntry(const FGuid& ItemId)
{
    if (UNSLEconItemEntry* Entry = FindEntry(ItemId))
    {
        ItemEntriesMap.Remove(Entry->ItemPtr->GetId());
        OrderedEntriesIdList.Remove(ItemId);
    }
}

void UNSLEconContainerItem::SetItemQuantityTo(const FGuid& ItemId, int32 NewQuantity)
{
    UNSLEconItemEntry** Entry = ItemEntriesMap.Find(ItemId);

    if (!Entry) {
        UE_LOG(LogTemp, Error, TEXT("Item not found."));
        return;
    }

    (*Entry)->SetQuantity(NewQuantity);
}

UNSLEconItemEntry* UNSLEconContainerItem::GetEntry(const FGuid& ItemId)
{
    UNSLEconItemEntry* EntryPtr = FindEntry(ItemId);
    if (!EntryPtr) {
        UE_LOG(LogTemp, Error, TEXT("Item not found."));
        return nullptr;
    }

    return EntryPtr;
}

UNSLEconItemEntry* UNSLEconContainerItem::FindEntry(const FGuid& ItemId)
{
    UNSLEconItemEntry** EntryPtr = ItemEntriesMap.Find(ItemId);
    return EntryPtr ? *EntryPtr : nullptr;
}


TArray<UNSLEconItemEntry*> UNSLEconContainerItem::GetEntries()
{
    TArray<UNSLEconItemEntry*> ResultList;
    for (const auto& EntryId : OrderedEntriesIdList)
    {
        UNSLEconItemEntry* Entry = FindEntry(EntryId);
        if (Entry)
        {
            ResultList.Add(Entry);
        }
    }

    return ResultList; // Return by value (copy)
}
