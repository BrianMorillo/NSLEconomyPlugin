// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconCurrencyTypes.generated.h"

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

//USTRUCT(BlueprintType)
//struct NSLECONOMYPLUGIN_API FNSLEconCurrencyAmount
//{
//    GENERATED_USTRUCT_BODY()
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
//    int32 Amount;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
//    TWeakObjectPtr<UNSLEconCurrency> Currency;
//
//    // Constructor for convenience
//    FNSLEconCurrencyAmount()
//        : Amount(0), Currency(nullptr)
//    {}
//
//    FNSLEconCurrencyAmount(int32 InAmount, UNSLEconCurrency* InCurrency)
//        : Amount(InAmount), Currency(InCurrency)
//    {}
//};

