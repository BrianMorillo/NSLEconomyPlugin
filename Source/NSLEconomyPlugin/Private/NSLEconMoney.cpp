// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconMoney.h"
#include "NSLEconTypes.h"
#include "NSLEconMoneyUtil.h"

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

const FString UNSLEconMoney::ToFormattedString() const
{
    return Currency.IsValid() ? 
        Currency->UnitsToFormattedCurrency(Units) : FString::Printf(TEXT("%lld"), Units);
}

UNSLEconMoney* UNSLEconMoney::SetTo(const UNSLEconMoney* Other)
{
    if (!IsCurrencyValidated(Other))
    {
        return nullptr;
    }

    Units = Other->Units;
    return this;
}


UNSLEconMoney* UNSLEconMoney::Add(const UNSLEconMoney* Other)
{
    if (!IsCurrencyValidated(Other))
    {
        return nullptr;
    }

    if (!UNSLEconMoneyUtil::IsAdditionAllowed(this, Other)) {
        UE_LOG(LogTemp, Error, TEXT("Addition exceeds the allowable max result"));
        return nullptr;
    }

    Units += Other->Units;
    return this;
}

UNSLEconMoney* UNSLEconMoney::Substract(const UNSLEconMoney* Other)
{
    if (!IsCurrencyValidated(Other))
    {
        return nullptr;
    }

    if (!UNSLEconMoneyUtil::IsSubstractionAllowed(this, Other)) {
        UE_LOG(LogTemp, Error, TEXT("Substraction exceeds the allowable max result"));
        return nullptr;
    }

    Units -= Other->Units;
    return this;
}

UNSLEconMoney* UNSLEconMoney::AddCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList)
{
    int64 CalculatedUnits = CalcCurrencyUnits(CurrUnitAmountList);
    if (!UNSLEconMoneyUtil::IsUnitsAdditionAllowed(Units, CalculatedUnits)) {
        UE_LOG(LogTemp, Error, TEXT("Addition exceeds the allowable max result"));
        return nullptr;
    }
    Units += CalculatedUnits;
    return this;
}

UNSLEconMoney* UNSLEconMoney::SubstractCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList)
{
    int64 CalculatedUnits = CalcCurrencyUnits(CurrUnitAmountList);
    if (!UNSLEconMoneyUtil::IsUnitsSubstractionAllowed(Units, CalculatedUnits)) {
        UE_LOG(LogTemp, Error, TEXT("Substraction exceeds the allowable max result"));
        return nullptr;
    }

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
            if (CurrUnitAmount.CurrencyUnitId.IsValid())
            {
                UE_LOG(LogTemp, Error, TEXT("FNSLEconCurrencyUnitAmount list invalid for operation"));
                return 0;
            }

            if (!UNSLEconMoneyUtil::IsUnitsAdditionAllowed(CalculatedUnits, CurrUnitAmount.Amount)) {
                UE_LOG(LogTemp, Error, TEXT("CurrencyUnitsToUnits conversion exceeds the allowable max result"));
                return 0;
            }

            CalculatedUnits += CurrUnitAmount.Amount;
        }
    }

    return CalculatedUnits;
}

bool UNSLEconMoney::IsCurrencyValidated(const UNSLEconMoney* Other)
{
    if (!Other || !Other->Currency.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid money"));
        return false;
    }

    if (!Currency.IsValid())
    {
        Currency = Other->Currency;
    }
    else if (GetCurrencyId() != Other->GetCurrencyId())
    {
        UE_LOG(LogTemp, Error, TEXT("Currency Mismatch"));
        return false;
    }

    return true;
}

int64 UNSLEconMoney::GetValueInUnits() const
{
    return Units;
}

const UNSLEconCurrency* UNSLEconMoney::GetCurrency() const
{
    return Currency.Get();
}

UNSLEconMoney* UNSLEconMoney::ScaledBy(const UNSLEconMoney* MoneyToScale, float PercentageToScaleBy)
{
    if (!UNSLEconMoneyUtil::IsScalingAllowed(MoneyToScale, PercentageToScaleBy)) {
        UE_LOG(LogTemp, Error, TEXT("Scaling operation exceeds the allowable max result"));
        return nullptr;
    }

    UNSLEconMoney* ScaledMoney = NewObject<UNSLEconMoney>();
    ScaledMoney->Initialize(MoneyToScale->Currency.Get());
    int IPercentageToScaleBy = (PercentageToScaleBy * 100);
    ScaledMoney->Units = (MoneyToScale->Units * IPercentageToScaleBy) / 100;
    return ScaledMoney;
}
