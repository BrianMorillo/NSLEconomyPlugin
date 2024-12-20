// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconMoneyUtil.h"
#include "NSLEconMoney.h"
#include "NSLEconCurrency.h"

bool UNSLEconMoneyUtil::IsScalingAllowed(const UNSLEconMoney* MoneyToScale, float PercentageToScaleBy)
{
    return IsUnitsScalingAllowed(MoneyToScale->GetValueInUnits(), PercentageToScaleBy);
}

bool UNSLEconMoneyUtil::IsUnitsScalingAllowed(int64 AmountToScale, float PercentageToScaleBy)
{
    if (FMath::Abs(AmountToScale) > (INT64_MAX / FMath::Abs(PercentageToScaleBy)))
    {
        return false;
    }

    return true;
}

bool UNSLEconMoneyUtil::IsAdditionAllowed(const UNSLEconMoney* MoneyA, const UNSLEconMoney* MoneyB)
{
    return IsUnitsAdditionAllowed(MoneyA->GetValueInUnits(), MoneyB->GetValueInUnits());
}

bool UNSLEconMoneyUtil::IsSubstractionAllowed(const UNSLEconMoney* MoneyA, const UNSLEconMoney* MoneyB)
{
    return IsUnitsSubstractionAllowed(MoneyA->GetValueInUnits(), MoneyB->GetValueInUnits());
}

bool UNSLEconMoneyUtil::IsUnitsAdditionAllowed(int64 AmountA, int64 AmountB)
{
    if (AmountA > 0 && AmountB > 0 && AmountA > (INT64_MAX - AmountB))
    {
        return false;
    }
    return true;
}

bool UNSLEconMoneyUtil::IsUnitsSubstractionAllowed(int64 AmountA, int64 AmountB)
{
    if (AmountA < 0 && AmountB < 0 && AmountA < (INT64_MIN - AmountB))
    {
        return false;
    }
    return true;
}

bool UNSLEconMoneyUtil::IsValidMoney(const UNSLEconMoney* Money)
{
    if (!Money || !Money->GetCurrency())
    {
        return false;
    }

    return true;
}

bool UNSLEconMoneyUtil::AreValidMoney(const UNSLEconMoney* MoneyA, const UNSLEconMoney* MoneyB)
{
    if (!IsValidMoney(MoneyA) || !IsValidMoney(MoneyB))
    {
        return false;
    }
    
    return true;
}

bool UNSLEconMoneyUtil::AreValidForOperation(const UNSLEconMoney* MoneyA, const UNSLEconMoney* MoneyB)
{
    if (!AreValidMoney(MoneyA, MoneyB))
    {
        return false;
    }

    // checks if their currencies are not the same
    if (MoneyA->GetCurrency()->GetCurrencyId() != MoneyB->GetCurrency()->GetCurrencyId())
    {
        return false;
    }

    return true;
}
