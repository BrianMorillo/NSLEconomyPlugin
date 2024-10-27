// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSLEconMarketEntry.h"
#include "NSLEconMarketExtendedEntry.generated.h"

/**
 * 
 */
UCLASS()
class NSLECONOMYPLUGIN_API UNSLEconMarketExtendedEntry : public UNSLEconMarketEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSLEconomy")
	int32 Supply = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSLEconomy")
	int32 Demand = 0;
};
