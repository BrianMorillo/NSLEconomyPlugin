// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSLEconItemEntry.h"
#include "NSLEconShopItemEntry.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconShopItemEntry : public UNSLEconItemEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "NSLEconomy")
	float PriceMarkup;

public:
	UNSLEconShopItemEntry();

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	float GetPriceMarkup();

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	void SetPriceMarkup(float NewPriceMarkup);

};
