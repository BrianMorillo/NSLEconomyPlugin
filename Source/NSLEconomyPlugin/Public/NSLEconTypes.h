// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconTypes.generated.h"

/**
 * 
 */
class UNSLEconItem;

USTRUCT(BlueprintType)
struct NSLECONOMYPLUGIN_API FNSLEconCurrencyUnitAmount
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    int32 Amount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    FGuid CurrencyUnitId;

    // Constructor for convenience
    FNSLEconCurrencyUnitAmount()
        : Amount(0), CurrencyUnitId()
    {}

    // Constructor for convenience
    FNSLEconCurrencyUnitAmount(int32 InAmount)
        : Amount(InAmount), CurrencyUnitId()
    {}

    FNSLEconCurrencyUnitAmount(int32 InAmount, FGuid InCurrencyUnitId)
        : Amount(InAmount), CurrencyUnitId(InCurrencyUnitId)
    {}
};

USTRUCT(BlueprintType)
struct FNSLEconContainerEntry : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSLEconomy")
    int32 Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSLEconomy")
    const UNSLEconItem* ItemPtr;

    // Constructor

    // Example method to set the pointer
    void SetItem(const UNSLEconItem* NewItem)
    {
        ItemPtr = NewItem; // This will change the pointer to point to NewItem
    }

    FNSLEconContainerEntry()
        : Quantity(0), ItemPtr(nullptr)
    {}

    FNSLEconContainerEntry(int32 InQuantity)
        : Quantity(InQuantity), ItemPtr(nullptr)
    {}

    //FNSLEconContainerEntry(int32 InQuantity, UNSLEconItem* InItem)
    //    : Quantity(Quantity), Item(InItem)
    //{}
};