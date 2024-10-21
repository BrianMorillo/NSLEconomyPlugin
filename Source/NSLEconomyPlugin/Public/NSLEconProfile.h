// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconContainerItem.h"
#include "NSLEconProfile.generated.h"
class UNSLEconMoney;
/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconProfile : public UNSLEconContainerItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	UNSLEconMoney* Money;
public:
	UNSLEconProfile(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	void SetMoney(const UNSLEconMoney* NewValue);

	UFUNCTION(BlueprintCallable, Category = "NSLEconomy")
	UNSLEconMoney* GetMoney();

	virtual void AddItemEntry(UNSLEconItemEntry* ItemEntry) override;

};
