// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSLEconItem.h"
#include "NSLEconContainerItem.generated.h"
class UNSLEconQuantityItem;
struct FNSLEconContainerEntry;
/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconContainerItem : public UNSLEconItem
{
	GENERATED_BODY()
	
private:
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")

    UDataTable* ItemTable;

public:
    UNSLEconContainerItem();

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void Initialize();

    // Function to add an item
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddItem(int32 QuantityOfItems, UNSLEconItem* NewItem);

    // Function to remove an item by its FGuid
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void RemoveItem(const FGuid& ItemId);

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

};
