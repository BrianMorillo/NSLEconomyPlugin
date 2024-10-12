// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSLEconItem.h"
#include "NSLEconQuantityItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconQuantityItem : public UNSLEconItem
{
	GENERATED_BODY()
	
    // Constructor
    UNSLEconQuantityItem();

    // Quantity of the item
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    int32 Quantity;
};
