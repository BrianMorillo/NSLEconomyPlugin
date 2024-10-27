// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSLEconCurrency.h"
#include "NSLEconUSDCurrency.generated.h"

UENUM(BlueprintType)
enum class ENSLEconUSDCurrencyUnit : uint8
{
	Dollar UMETA(DisplayName = "Dollar"),
	Quarter UMETA(DisplayName = "Quarter"),
	Dime UMETA(DisplayName = "Dime"),
	Nickle UMETA(DisplayName = "Nickle"),
	Cent UMETA(DisplayName = "Cent"),
};
/**
 * 
 */
UCLASS()
class NSLECONOMYPLUGIN_API UNSLEconUSDCurrency : public UNSLEconCurrency
{
	GENERATED_BODY()

private:
	UNSLEconUSDCurrency(const FObjectInitializer& ObjectInitializer);

	FString USDCurrencyUnitsFormat(int64 AmountToFormat);
	UNSLEconMoney* FormattedUSDToMoney(FString FormattedCurrency);
};
