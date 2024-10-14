// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSLEconItem.h"
#include "NSLEconContainerItem.generated.h"
class UNSLEconItemEntry;
/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconContainerItem : public UNSLEconItem
{
	GENERATED_BODY()
	
private:

    // Map of contained items using FGuid as key
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    TMap<FGuid, UNSLEconItemEntry*> ItemEntriesMap;

    // Map of contained items using FGuid as key
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    TArray<FGuid> OrderedEntriesIdList;

protected:
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    UNSLEconItemEntry* FindEntry(const FGuid& ItemId);

public:
    UNSLEconContainerItem();

    // Function to add an item
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddItemEntry(UNSLEconItemEntry* ItemEntry);

    // Function to remove an item by its FGuid
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void RemoveItemEntry(const FGuid& ItemId);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void SetItemQuantityTo(const FGuid& ItemId, int32 NewQuantity);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    UNSLEconItemEntry* GetEntry(const FGuid& ItemId);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    TArray<UNSLEconItemEntry*> GetEntries();



    /*
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void Initialize();


    // Function to get an item by its FGuid
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const UNSLEconItem* GetItem(const FGuid& ItemId) const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void SetItemQuantityTo(int32 NewQuantity, const FGuid& ItemId);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    bool IsInitialized() const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void InitializationCheck() const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const FNSLEconContainerEntry GetEntry(const FGuid& ItemId) const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const TMap<FString, FGuid> GetItemsId() const;
    */
};
