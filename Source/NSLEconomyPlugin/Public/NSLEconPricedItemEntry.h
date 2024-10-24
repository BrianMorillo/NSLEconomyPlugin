// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSLEconItemEntry.h"
#include "NSLEconPricedItemEntry.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconPricedItemEntry : public UNSLEconItemEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	UNSLEconMoney* Price;
public:
	UNSLEconPricedItemEntry(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	UNSLEconMoney* GetItemPrice() const;
};
