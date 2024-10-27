// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconCurrencyUnit.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconCurrencyUnit : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "NSLEconomy")
	FString UnitName;

	// Conversion factor to an unit (e.g., dollar is 100 units)
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "NSLEconomy")
	int32 UnitConversionFactor;

public:
	UNSLEconCurrencyUnit();

	// Initialization function
	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	void Initialize(const FString& InUnitName, int32 InUnitConversionFactor);

	// Getter for UnitName
	UFUNCTION(BlueprintPure, Category = "NSLEconomy")
	FString GetUnitName() const { return UnitName; }

	// Getter for UnitConversionFactor
	UFUNCTION(BlueprintPure, Category = "NSLEconomy")
	int32 GetUnitConversionFactor() const { return UnitConversionFactor; }
};
