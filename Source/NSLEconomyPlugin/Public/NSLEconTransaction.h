// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconTransaction.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconTransaction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSLEconomy")
	FGuid ItemId;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "NSLEconomy")
	void Execute();

	virtual void Execute_Implementation();
};
