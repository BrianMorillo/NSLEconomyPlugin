// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconItem.generated.h"

class UNSLEconMoney;
class UNSLEconCurrency;
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

protected:
    // Value of the item
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    UNSLEconMoney* Value;
	
public:
    // Constructor
    //UNSLEconItem();
    UNSLEconItem(const FObjectInitializer& ObjectInitializer);

    // Name of the item
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
    FString Name;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void SetCurrency(UNSLEconCurrency* NewValue);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    void SetValue(const UNSLEconMoney* NewValue);

    //UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    //UNSLEconMoney* AddValue(const UNSLEconMoney* Other);

    //UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    //UNSLEconMoney* SubstractValue(const UNSLEconMoney* Other);

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    UNSLEconMoney* GetValue() const;

    UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
    FGuid GetId() const;
};
