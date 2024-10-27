// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Market/NSLEconMarket.h"
#include "NSLEconExtendedMarket.generated.h"

class UNSLEconMarketEntry;
class UNSLEconTransaction;

/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconExtendedMarket : public UNSLEconMarket
{
	GENERATED_BODY()


public:
	UNSLEconExtendedMarket();

	// multiplier that determines the degree of price adjustment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSLEconomy")
	float Alpha = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	UNSLEconMoney* GetAdjustedItemMarketValue(
		UNSLEconMarketEntry* MarketItemEntry) const;
};
