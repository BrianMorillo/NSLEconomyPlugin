// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconCurrency.generated.h"

class UNSLEconCurrencyUnit;
struct FNSLEconCurrencyUnitAmount;
class UNSLEconMoney;

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FString, FUnitsToFormattedCurrencyDelegate, int64, AmountToFormat);
/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconCurrency : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "NSLEconomy")
		FGuid CurrencyId;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "NSLEconomy")
		FString CurrencyName;

	UPROPERTY()
		TMap<FGuid, UNSLEconCurrencyUnit*> CurrencyUnitMap;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "NSLEconomy")
		FUnitsToFormattedCurrencyDelegate UnitsToFormattedCurrencyDel;

public:
	UNSLEconCurrency();

	// Initialization function
	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
		void Initialize(const FString& InCurrencyName);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
		FString GetCurrencyName() const;

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
		void RemoveCurrencyUnit(FGuid CurrencyUnitId);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
		FGuid AddCurrencyUnit(const FString& CurrencyUnitName, int32 UnitConversionFactor);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
		UNSLEconMoney* CreateCurrencyMoney(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList);

	// Function to execute the delegate
	UFUNCTION(BlueprintCallable)
		FString UnitsToFormattedCurrency(int64 AmountToFormat) const;

	// Function to bind the delegate
	UFUNCTION(BlueprintCallable)
		void BindUnitsToFormattedCurrencyDelegate(const FUnitsToFormattedCurrencyDelegate& Delegate);

	UFUNCTION(BlueprintCallable)
		FGuid GetCurrencyId() const { return CurrencyId; }

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
		int64 CurrencyUnitsToUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList);
};
