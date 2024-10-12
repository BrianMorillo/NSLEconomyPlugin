// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSLEconItem.h"
#include "NSLEconContainerItem.generated.h"
class UNSLEconQuantityItem;
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
    TMap<FGuid, UNSLEconQuantityItem*> ContainedItems;
    // Constructor
    UNSLEconContainerItem();

public:
    // Function to add an item
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddItem(UNSLEconQuantityItem* NewItem);

    // Function to remove an item by its FGuid
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void RemoveItem(const FGuid& ItemId);

    // Function to get an item by its FGuid
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    UNSLEconItem* GetItem(const FGuid& ItemId) const;
};
