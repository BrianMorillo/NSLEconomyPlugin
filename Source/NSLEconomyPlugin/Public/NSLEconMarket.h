// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconMarket.generated.h"

class UNSLEconShop;
/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconMarket : public UObject
{
	GENERATED_BODY()
	

private:
    // Registry of all items
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    TMap<FGuid, UNSLEconItem*> ItemRegistry;

    // Registry of all shops
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    TMap<FGuid, UNSLEconShop*> ShopRegistry;

public:
    // Constructor
    UNSLEconMarket();

    //// Function to add an item to the market
    //UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    //void AddItemToMarket(UNSLEconItem* NewItem);

    //// Function to remove an item from the market by its FGuid
    //UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    //void RemoveItemFromMarket(const FGuid& ItemId);

    // Function to get an item from the market by its FGuid
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    UNSLEconItem* GetItemFromMarket(const FGuid& ItemId) const;

    // Function to add a new shop to the market
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddShopToMarket(UNSLEconShop* NewShop);

    // Function to remove a shop from the market by its FGuid
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void RemoveShopFromMarket(const FGuid& ShopId);

    // Function to get a shop from the market by its FGuid
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    UNSLEconShop* GetShopFromMarket(const FGuid& ShopId) const;
};

