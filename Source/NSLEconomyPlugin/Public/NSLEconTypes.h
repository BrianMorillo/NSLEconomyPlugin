// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconTypes.generated.h"

/**
 * 
 */
class UNSLEconItem;
class UNSLEconMoney;

USTRUCT(BlueprintType)
struct NSLECONOMYPLUGIN_API FNSLEconCurrencyUnitAmount
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    int32 Amount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    FString CurrencyUnitName;

    // Constructor for convenience
    FNSLEconCurrencyUnitAmount()
        : Amount(0), CurrencyUnitName("")
    {}

    // Constructor for convenience
    FNSLEconCurrencyUnitAmount(int32 InAmount)
        : Amount(InAmount), CurrencyUnitName("")
    {}

    FNSLEconCurrencyUnitAmount(int32 InAmount, FString InCurrencyUnitName)
        : Amount(InAmount), CurrencyUnitName(InCurrencyUnitName)
    {}
};

UENUM(BlueprintType)
enum class EPurchaseTransactionType : uint8
{
    Buy UMETA(DisplayName = "Buy"),
    Sell UMETA(DisplayName = "Sell")
};
