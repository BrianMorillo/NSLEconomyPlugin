// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconProfile.generated.h"
class UNSLEconMoney;
class UNSLEconContainerItem;
/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconProfile : public UObject
{
	GENERATED_BODY()
public:
	UNSLEconProfile(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	UNSLEconMoney* Money;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	UNSLEconContainerItem* Items;

};
