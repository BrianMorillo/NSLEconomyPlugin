// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconCurrencyUnit.h"

UNSLEconCurrencyUnit::UNSLEconCurrencyUnit()
    : UnitName(TEXT("DefaultUnit"))
    , UnitConversionFactor(1)
{
}

void UNSLEconCurrencyUnit::Initialize(const FString& InUnitName, int32 InUnitConversionFactor)
{
    UnitName = InUnitName;
    UnitConversionFactor = InUnitConversionFactor;
}


