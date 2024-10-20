// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSLEconTransaction.h"
#include "NSLEconTypes.h"
#include "NSLEconPurchaseTransaction.generated.h"
class UNSLEconProfile;
class UNSLEconMoney;

/**
 * 
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconPurchaseTransaction : public UNSLEconTransaction
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	UNSLEconProfile* Buyer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	UNSLEconProfile* Seller;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	int32 QuantityToPurchase;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	ETransactionType MarketTransactionType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	UNSLEconMoney* PurchasePrice;

	virtual void Execute_Implementation() override;
};
