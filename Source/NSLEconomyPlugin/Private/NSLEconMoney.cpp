// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconMoney.h"
#include "NSLEconCurrencyTypes.h"

UNSLEconMoney::UNSLEconMoney()
    : Currency(nullptr)
    , Units(0)
{
}

void UNSLEconMoney::Initialize(UNSLEconCurrency* InCurrency) 
{
    if (Currency.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Currency already initialized"));
        return;
    }

    Currency = InCurrency;
    Units = 0;
}

FString UNSLEconMoney::ToFormattedString()
{
    return Currency.IsValid() ? 
        Currency->UnitsToFormattedCurrency(Units) : FString::Printf(TEXT("%lld"), Units);
}

UNSLEconMoney* UNSLEconMoney::Add(const UNSLEconMoney* Other)
{
    if (!IsOperationValid(Other))
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot add different currency types!"));
    }

    Units += Other->Units;
    return this;
}

UNSLEconMoney* UNSLEconMoney::Substract(const UNSLEconMoney* Other)
{
    if (!IsOperationValid(Other))
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot substract different currency types!"));
    }

    Units -= Other->Units;
    return this;
}

UNSLEconMoney* UNSLEconMoney::AddCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList)
{
    Units += CalcCurrencyUnits(CurrUnitAmountList);
    return this;
}

UNSLEconMoney* UNSLEconMoney::SubstractCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList)
{
    Units -= CalcCurrencyUnits(CurrUnitAmountList);
    return this;
}

int64 UNSLEconMoney::CalcCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList)
{
    int64 CalculatedUnits = 0;
    if (Currency.IsValid())
    {
        CalculatedUnits = Currency->CurrencyUnitsToUnits(CurrUnitAmountList);
    }
    else {
        for (const FNSLEconCurrencyUnitAmount& CurrUnitAmount : CurrUnitAmountList)
        {
            if (!CurrUnitAmount.CurrencyUnitId.IsValid())
            {
                CalculatedUnits += CurrUnitAmount.Amount;
            }
        }
    }

    return CalculatedUnits;
}

bool UNSLEconMoney::IsOperationValid(const UNSLEconMoney* Other)
{
    // checks if one has currency but the other does not
    if (Currency.IsValid() != Other->Currency.IsValid())
    {
        return false;
    }

    // checks if their currencies are not the same
    if (Currency.IsValid() && GetCurrencyId() != Other->GetCurrencyId())
    {
        return false;
    }

    return true;
}

