// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconShop.generated.h"

class UNSLEconContainerItem;
class UNSLEconShopItemEntry;
struct FShopItemInfo;

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

    //// Name of the shop
    //UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    //FString Name;

    // Function to add an item to the shop's inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddItemEntry(UNSLEconShopItemEntry* ShopItemEntry);

    // Function to remove an item from the shop's inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void RemoveItemEntry(const FGuid& ItemId);

    // Function to buy an item (removes item from inventory)
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const FShopItemInfo BuyItem(const FGuid& ItemId, int32 QuantityToBuy, UNSLEconMoney* MoneyToBuyWith);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const FShopItemInfo GetItemInfo(const FGuid& ItemId);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    TArray<FShopItemInfo> GetItems();

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AdjustItemMarkup(const FGuid& ItemId, float PriceMarkupPercentage);

};
