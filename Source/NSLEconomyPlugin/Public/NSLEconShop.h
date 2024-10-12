// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconShop.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconShop : public UObject
{
	GENERATED_BODY()
	

private:
    // Shop inventory
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    UNSLEconContainerItem* Inventory;

public:
    // Constructor
    UNSLEconShop();

    // Name of the shop
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    FString Name;

    // Function to add an item to the shop's inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddItemToInventory(UNSLEconQuantityItem* NewItem);

    // Function to remove an item from the shop's inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void RemoveItemFromInventory(const FGuid& ItemId);

    // Function to buy an item (removes item from inventory)
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    UNSLEconItem* BuyItem(const FGuid& ItemId);

    // Get inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    UNSLEconContainerItem* GetInventory() const;
};
