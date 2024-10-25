// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconCurrency.h"
#include "NSLEconMoney.generated.h"

struct FNSLEconCurrencyUnitAmount;
/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconMoney : public UObject
{
	GENERATED_BODY()
private:
    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "NSLEconomy")
        TWeakObjectPtr<const UNSLEconCurrency> Currency;

    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "NSLEconomy")
        int64 Units;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        int64 CalcCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList);

public:
    UNSLEconMoney();

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        const FString ToFormattedString() const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* SetTo(const UNSLEconMoney* Other);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* Add(const UNSLEconMoney* Other);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* Substract(const UNSLEconMoney* Other);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* SetCurrency(const UNSLEconCurrency* InCurrency);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* AddCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* SubstractCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList);
    
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        FGuid GetCurrencyId() const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        int64 GetValueInUnits() const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        const UNSLEconCurrency* GetCurrency() const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        static UNSLEconMoney* ScaledBy(const UNSLEconMoney* MoneyToScale, float PercentageToScaleBy);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        bool MatchesCurrency(const UNSLEconMoney* Other);
};
