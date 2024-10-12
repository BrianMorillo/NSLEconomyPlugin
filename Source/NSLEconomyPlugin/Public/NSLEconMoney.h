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
        TWeakObjectPtr<UNSLEconCurrency> Currency;

    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "NSLEconomy")
        int64 Units;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        int64 CalcCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        bool IsOperationValid(const UNSLEconMoney* Other);

public:
    UNSLEconMoney();

    //UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    //    void Initialize(int64 InUnits, UNSLEconCurrency* InCurrency);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        FString ToFormattedString();

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* Add(const UNSLEconMoney* Other);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* Substract(const UNSLEconMoney* Other);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        void SetCurrency(UNSLEconCurrency* InCurrency);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* AddCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        UNSLEconMoney* SubstractCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList);
    
    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
        FGuid GetCurrencyId() const { return Currency->GetCurrencyId(); }

};
