// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconMoney.h"
#include "NSLEconTypes.h"
#include "NSLEconMoneyUtil.h"

UNSLEconMoney::UNSLEconMoney()
    : Currency(nullptr)
    , Units(0)
{
}

UNSLEconMoney* UNSLEconMoney::SetCurrency(const UNSLEconCurrency* InCurrency)
{
    if (!InCurrency)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid UNSLEconCurrency argument"));
        return nullptr;
    }

    if (Currency.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Currency already initialized"));
        return nullptr;
    }

    Currency = InCurrency;
    return this;
}

const FString UNSLEconMoney::ToFormattedString() const
{
    return Currency.IsValid() ? 
        Currency->UnitsToFormattedCurrency(Units) : FString::Printf(TEXT("%lld"), Units);
}

UNSLEconMoney* UNSLEconMoney::SetTo(const UNSLEconMoney* Other)
{
    if (!MatchesCurrency(Other))
    {
        return nullptr;
    }

    Units = Other->Units;
    return this;
}

bool UNSLEconMoney::MatchesCurrency(const UNSLEconMoney* Other)
{
    if (!UNSLEconMoneyUtil::IsValidMoney(Other))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid UNSLEconMoney argument"));
        return false;
    }

    if (!UNSLEconMoneyUtil::IsValidMoney(this))
    {
        SetCurrency(Other->GetCurrency());
    }
    else if (GetCurrencyId() != Other->GetCurrencyId())
    {
        UE_LOG(LogTemp, Error, TEXT("Currency Mismatch"));
        return false;
    }

    return true;
}


UNSLEconMoney* UNSLEconMoney::Add(const UNSLEconMoney* Other)
{
    if (!MatchesCurrency(Other))
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
    if (!MatchesCurrency(Other))
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

FGuid UNSLEconMoney::GetCurrencyId() const
{
    return GetCurrency() ? Currency->GetCurrencyId() : FGuid();
}

int64 UNSLEconMoney::CalcCurrencyUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList)
{
    if (!UNSLEconMoneyUtil::IsValidMoney(this)) 
    {
        UE_LOG(LogTemp, Error, TEXT("This UNSLEconMoney object is invalid"));
        return 0;
    }

    return Currency->CurrencyUnitsToUnits(CurrUnitAmountList);;
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
    if (!UNSLEconMoneyUtil::IsValidMoney(MoneyToScale)) {
        UE_LOG(LogTemp, Error, TEXT("Invalid Money"));
        return nullptr;
    }

    if (!UNSLEconMoneyUtil::IsScalingAllowed(MoneyToScale, PercentageToScaleBy)) {
        UE_LOG(LogTemp, Error, TEXT("Scaling operation exceeds the allowable max result"));
        return nullptr;
    }

    UNSLEconMoney* ScaledMoney = NewObject<UNSLEconMoney>();
    ScaledMoney->SetCurrency(MoneyToScale->Currency.Get());
    int IPercentageToScaleBy = (PercentageToScaleBy * 100);
    ScaledMoney->Units = (MoneyToScale->Units * IPercentageToScaleBy) / 100;
    return ScaledMoney;
}
