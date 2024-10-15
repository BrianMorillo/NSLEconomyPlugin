// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconMarket.generated.h"

class UNSLEconMarketEntry;

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(const UNSLEconMarketEntry*, FMarketItemUpdateDelegate, const UNSLEconMarketEntry*, MarketEntry);

/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconMarket : public UObject
{
	GENERATED_BODY()
	

private:
    // Registry of all item entries
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    TMap<FGuid, UNSLEconMarketEntry*> ItemRegistry;

    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    FMarketItemUpdateDelegate MarketItemUpdateDel;

    TQueue<const UNSLEconMarketEntry*> ItemsChangeQueue;

    // Function to execute the delegate
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void RegisterItemChange(FGuid ItemId, int32 QuantityChange);

public:
    // Constructor
    UNSLEconMarket();

    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    bool AdjustMarketOnItemUpdate = true;

    // Function to add an item to the market
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddItemToMarket(UNSLEconMarketEntry* NewMarketEntry);

    UFUNCTION(BlueprintCallable)
    void ItemBuy(FGuid ItemId, int32 QuantityBought);

    UFUNCTION(BlueprintCallable)
    void ItemSell(FGuid ItemId, int32 QuantitySold);

    UFUNCTION(BlueprintCallable)
    void BindMarketItemUpdateDelegate(const FMarketItemUpdateDelegate& Delegate);

    UFUNCTION(BlueprintCallable)
    void UpdateMarket();

};

