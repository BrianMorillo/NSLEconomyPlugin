// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconShop.generated.h"

class UNSLEconContainerItem;
struct FNSLEconContainerEntry;

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

    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    TMap<FGuid, float> ItemMarkupMap;

public:
    // Constructor
    UNSLEconShop();

    // Name of the shop
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    FString Name;

    // Function to add an item to the shop's inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddItemToInventory(int32 AmountOfItems, float PriceMarkupPercentage, UNSLEconItem* NewItem);

    // Function to remove an item from the shop's inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void RemoveItemFromInventory(const FGuid& ItemId);

    // Function to buy an item (removes item from inventory)
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const UNSLEconItem* BuyItem(const FGuid& ItemId, UNSLEconMoney* MoneyToBuyWith);

    // Get inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const TMap<FString, FGuid> GetItemsId() const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const FNSLEconContainerEntry GetItemDetails(const FGuid& ItemId) const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AdjustItemMarkup(const FGuid& ItemId, float PriceMarkupPercentage);
};
