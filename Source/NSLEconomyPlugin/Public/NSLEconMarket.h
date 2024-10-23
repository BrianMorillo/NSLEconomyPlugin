// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconMarket.generated.h"

class UNSLEconMarketEntry;
class UNSLEconTransaction;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FMarketItemUpdateDelegate, UNSLEconMarketEntry*, MarketItemEntry, const UNSLEconTransaction*, Transaction);

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

    TQueue<const UNSLEconTransaction*> ItemsChangeQueue;

public:
    // Constructor
    UNSLEconMarket();

    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    bool AdjustMarketOnItemUpdate = true;

    // Function to add an item to the market
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void AddItemToMarket(UNSLEconMarketEntry* NewMarketEntry);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void UpdateMarket();

    // Function to execute the delegate
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void ProcessTransaction(const UNSLEconTransaction* Transaction);

    UFUNCTION(BlueprintCallable)
    void BindMarketItemUpdateDelegate(const FMarketItemUpdateDelegate& Delegate);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    const UNSLEconMarketEntry* GetEntry(const FGuid& ItemId);

};

