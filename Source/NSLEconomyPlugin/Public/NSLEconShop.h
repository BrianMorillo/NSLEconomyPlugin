// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconShop.generated.h"

class UNSLEconContainerItem;
class UNSLEconPricedItemEntry;
class UNSLEconMarket;
class UNSLEconProfile;
struct FShopItemInfo;

/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconShop : public UObject
{
	GENERATED_BODY()

public:
    // Constructor
    //UNSLEconShop();
    UNSLEconShop(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    UNSLEconProfile* ShopProfile;

    // Name of the shop
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    FString Name;

    // Market in which the shop participates in
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    UNSLEconMarket* Market;

    // Function to add an item to the shop's inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddItemEntry(UNSLEconPricedItemEntry* ShopItemEntry);

    // Function to remove an item from the shop's inventory
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void RemoveItemEntry(const FGuid& ItemId);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const UNSLEconPricedItemEntry* GetItemInfo(const FGuid& ItemId);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    TArray<UNSLEconPricedItemEntry*> GetItems();

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AdjustItemPrice(const FGuid& ItemId, UNSLEconMoney* NewPrice);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void BuyItem(const FGuid& ItemId, int32 QuantityToPurchase, UNSLEconProfile* Buyer);

};
