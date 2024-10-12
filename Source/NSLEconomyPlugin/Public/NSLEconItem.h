// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconItem.generated.h"

class UNSLEconMoney;
/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconItem : public UObject
{
	GENERATED_BODY()

private:
    // Unique identifier for the item
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    FGuid Id;
	
public:
    // Constructor
    UNSLEconItem();

    // Name of the item
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    FString Name;

    // Price of the item
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    UNSLEconMoney* Value;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    FGuid GetId() const;

    //void Initialize(FGuid InId, const FString& InName, UNSLEconMoney* InPrice);q
};
