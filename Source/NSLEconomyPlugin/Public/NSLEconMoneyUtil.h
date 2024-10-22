// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconMoneyUtil.generated.h"

class UNSLEconMoney;
/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconMoneyUtil : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	static bool IsScalingAllowed(const UNSLEconMoney* MoneyToScale, float PercentageToScaleBy);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	static bool IsUnitsScalingAllowed(int64 AmountToScale, float PercentageToScaleBy);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	static bool IsSubstractionAllowed(const UNSLEconMoney* MoneyA, const UNSLEconMoney* MoneyB);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	static bool IsAdditionAllowed(const UNSLEconMoney* MoneyA, const UNSLEconMoney* MoneyB);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	static bool IsUnitsAdditionAllowed(int64 AmountA, int64 AmountB);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	static bool IsUnitsSubstractionAllowed(int64 AmountA, int64 AmountB);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	static bool IsMoneyValid(const UNSLEconMoney* Money);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	static bool AreValidForOperation(const UNSLEconMoney* MoneyA, const UNSLEconMoney* MoneyB);
};
