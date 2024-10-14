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

UNSLEconMoney* UNSLEconMoney::Add(const UNSLEconMoney* Other)
{
    if (!IsOperationValid(Other))
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot add different currency types!"));
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
    if (!IsOperationValid(Other))
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot substract different currency types!"));
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

int64 UNSLEconMoney::GetValueInUnits() const
{
    return Units;
}

const UNSLEconCurrency* UNSLEconMoney::GetCurrency()
{
    return Currency.Get();
}

UNSLEconMoney* UNSLEconMoney::ScaledBy(UNSLEconMoney* MoneyToScale, float PercentageToScaleBy)
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


//bool UNSLEconMoney::IsAdditionAllowed(int64 AmountA, int64 AmountB)
//{
//    if (AmountA > 0 && AmountB > 0 && AmountA > (INT64_MAX - AmountB)) 
//    {
//        return false;
//    }
//    return true;
//}
//
//bool UNSLEconMoney::IsSubstractionAllowed(int64 AmountA, int64 AmountB)
//{
//    if (AmountA < 0 && AmountB < 0 && AmountA < (INT64_MIN - AmountB))
//    {
//        return false;
//    }
//    return true;
//}

/*
bool UNSLEconMoney::IsSubstractionAllowed(int64 AmountA, int64 AmountB)
{
    if (AmountA > (INT64_MAX - AmountB)) {
        UE_LOG(LogTemp, Error, TEXT("Amount exceeds the allowable max cost"));
        return false;
    }

    return true;


   int64 PriceToPay = Entry->ItemPtr->Value->GetValueInUnits() * QuantityToBuy;
    if (Entry->ItemPtr->Value->GetValueInUnits() > INT64_MAX / QuantityToBuy) {
        UE_LOG(LogTemp, Error, TEXT("Amount exceeds the allowable max cost"));
        return false;
    }

    if (FMath::Abs(MoneyToBuyWith->GetValueInUnits()) > (INT64_MAX - PriceToPay))
    {
        UE_LOG(LogTemp, Error, TEXT("Purchase exceeds the allowable max transaction result"));
        return FShopItemInfo();
    }
}*/
