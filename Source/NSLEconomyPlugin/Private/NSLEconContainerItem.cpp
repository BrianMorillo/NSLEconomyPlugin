// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconContainerItem.h"
#include "NSLEconItem.h"
#include "NSLEconTypes.h"

UNSLEconContainerItem::UNSLEconContainerItem()
    : ItemTable(nullptr)
{
}

// Constructor implementation
void UNSLEconContainerItem::Initialize()
{
    if (ItemTable)
    {
        ItemTable->ConditionalBeginDestroy(); // or simply set to nullptr if needed
    }

    ItemTable = NewObject<UDataTable>(this, UDataTable::StaticClass());
    ItemTable->RowStruct = FNSLEconContainerEntry::StaticStruct();
}

// Add an item to the container
void UNSLEconContainerItem::AddItem(int32 AmountOfItems, UNSLEconItem* NewItem)
{
    InitializationCheck();

    if (GetItem(NewItem->GetId())) {
        UE_LOG(LogTemp, Error, TEXT("Item already added."));
        return;
    }

    FNSLEconContainerEntry Row;
    Row.Quantity = FMath::Max(0, AmountOfItems);
    Row.ItemPtr = NewItem;
    ItemTable->AddRow(FName(*NewItem->GetId().ToString()), Row);
}

// Remove an item from the container by its ID
void UNSLEconContainerItem::RemoveItem(const FGuid& ItemId)
{
    InitializationCheck();

    if (!GetItem(ItemId)) {
        UE_LOG(LogTemp, Error, TEXT("Item not found"));
        return;
    }

    // Create a new DataTable
    UDataTable* NewItemTable = NewObject<UDataTable>(ItemTable->GetOuter(), UDataTable::StaticClass());

    // Copy the original DataTable's RowStruct
    NewItemTable->RowStruct = ItemTable->RowStruct;

    // Iterate through the existing rows
    for (const auto& RowPair : ItemTable->GetRowMap())
    {
        const FName& RowName = RowPair.Key;

        // Skip the row to remove
        if (RowName != *ItemId.ToString())
        {
            FTableRowBase* RowData = reinterpret_cast<FTableRowBase*>(RowPair.Value);

            // Add the row to the new DataTable
            NewItemTable->AddRow(RowName, *RowData);
        }
    }

    ItemTable = NewItemTable;
}

// Get an item from the container by its ID
const UNSLEconItem* UNSLEconContainerItem::GetItem(const FGuid& ItemId) const
{
    InitializationCheck();

    FNSLEconContainerEntry* Row = ItemTable->FindRow<FNSLEconContainerEntry>
        (FName(*ItemId.ToString()), TEXT("Getting an item"));

    return Row ? Row->ItemPtr : nullptr;
}

void UNSLEconContainerItem::SetItemQuantityTo(int32 NewQuantity, const FGuid& ItemId)
{
    InitializationCheck();

    FNSLEconContainerEntry* Row = ItemTable->FindRow<FNSLEconContainerEntry>
        (FName(*ItemId.ToString()), TEXT("Changing an item quantity"));

    if (Row)
    {
        Row->Quantity = FMath::Max(0, NewQuantity);
    }
}

const FNSLEconContainerEntry UNSLEconContainerItem::GetEntry(const FGuid& ItemId) const 
{
    FNSLEconContainerEntry* Row = ItemTable->FindRow<FNSLEconContainerEntry>
        (FName(*ItemId.ToString()), TEXT("Getting an entry"));

    return *Row;
}

bool UNSLEconContainerItem::IsInitialized() const
{
    return ItemTable != nullptr;
}

void UNSLEconContainerItem::InitializationCheck() const
{
    if (!IsInitialized()) {
        UE_LOG(LogTemp, Fatal, TEXT("UNSLEconContainerItem not initialized. Do Initialize()"));
        return;
    }
}

const TMap<FString, FGuid> UNSLEconContainerItem::GetItemsId() const
{
    TMap<FString, FGuid> itemsNamesAndIds;

    // Iterate through all rows
    for (auto& Row : ItemTable->GetRowMap())
    {
        FNSLEconContainerEntry* Data = (FNSLEconContainerEntry*)Row.Value;
        if (Data)
        {
            itemsNamesAndIds.Add(Data->ItemPtr->Name, Data->ItemPtr->GetId());
        }
    }

    return itemsNamesAndIds;
}