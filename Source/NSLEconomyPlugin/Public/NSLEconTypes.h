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
struct FShopItemInfo
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSLEconomy")
    int32 Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSLEconomy")
    const UNSLEconItem* ItemPtr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSLEconomy")
    const UNSLEconMoney* ShopPrice;
    
    void SetItem(const UNSLEconItem* NewItem)
    {
        ItemPtr = NewItem; // This will change the pointer to point to NewItem
    }

    void SetPrice(const UNSLEconMoney* Price)
    {
        ShopPrice = Price; // This will change the pointer to point to NewItem
    }

    // Constructor

    FShopItemInfo()
        : Quantity(0), ItemPtr(nullptr), ShopPrice(nullptr)
    {}

    FShopItemInfo(int32 InQuantity, const UNSLEconItem* InItem, const UNSLEconMoney* Price)
        : Quantity(InQuantity), ItemPtr(InItem), ShopPrice(Price)
    {}
};

UENUM(BlueprintType)
enum class ETransactionType : uint8
{
    Buy UMETA(DisplayName = "Buy"),
    Sell UMETA(DisplayName = "Sell")
};
