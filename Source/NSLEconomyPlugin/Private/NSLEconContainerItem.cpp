// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconContainerItem.h"
#include "NSLEconItem.h"
#include "NSLEconTypes.h"
#include "NSLEconItemEntry.h"

UNSLEconContainerItem::UNSLEconContainerItem()
{
}

void UNSLEconContainerItem::AddItemEntry(UNSLEconItemEntry* ItemEntry)
{
    if (!ItemEntry || !(ItemEntry->ItemPtr))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid UNSLEconItemEntry argument"));
    }

    FGuid ItemEntryId = ItemEntry->ItemPtr->GetId();
    if (FindEntry(ItemEntryId))
    {
        UE_LOG(LogTemp, Error, TEXT("Item already included"));
        return;
    }

    ItemEntriesMap.Add(ItemEntryId, ItemEntry);
    OrderedEntriesIdList.Add(ItemEntryId);
}
void UNSLEconContainerItem::RemoveItemEntry(const FGuid& ItemId)
{
    ItemEntriesMap.Remove(FindEntry(ItemId)->ItemPtr->GetId());
    OrderedEntriesIdList.Remove(ItemId);
}

void UNSLEconContainerItem::SetItemQuantityTo(const FGuid& ItemId, int32 NewQuantity)
{
    UNSLEconItemEntry* Entry = *ItemEntriesMap.Find(ItemId);

    if (!Entry) {
        UE_LOG(LogTemp, Error, TEXT("Item not found."));
        return;
    }

    Entry->SetQuantity(NewQuantity);
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
        const UNSLEconItemEntry* Entry = FindEntry(EntryId);
        if (Entry)
        {
            ResultList.Add(const_cast<UNSLEconItemEntry*>(Entry)); // Cast to non-const to fit the API
        }
    }

    return ResultList; // Return by value (copy)
}