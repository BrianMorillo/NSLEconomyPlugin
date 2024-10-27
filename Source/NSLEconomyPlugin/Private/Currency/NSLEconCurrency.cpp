// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconCurrency.h"
#include "NSLEconCurrencyUnit.h"
#include "NSLEconTypes.h"
#include "NSLEconMoney.h"
#include "NSLEconMoneyUtil.h"

UNSLEconCurrency::UNSLEconCurrency()
	: CurrencyName(TEXT("DefaultCurrency"))
{
	CurrencyId = FGuid::NewGuid();
}

void UNSLEconCurrency::Initialize(const FString& InCurrencyName)
{
	CurrencyName = InCurrencyName;
}

FString UNSLEconCurrency::GetCurrencyName() const
{
	return CurrencyName;
}

UNSLEconCurrencyUnit* UNSLEconCurrency::AddCurrencyUnit(UNSLEconCurrencyUnit* CurrencyUnit)
{
	if (!CurrencyUnit) {
		UE_LOG(LogTemp, Error, TEXT("Invalid UNSLEconCurrencyUnit"));
		return nullptr;
	}

	CurrencyUnitMap.Add(CurrencyUnit->GetUnitName(), CurrencyUnit);

	return *CurrencyUnitMap.Find(CurrencyUnit->GetUnitName());
}


void UNSLEconCurrency::RemoveCurrencyUnit(const FString& CurrencyUnitName)
{
	if (CurrencyUnitMap.Contains(CurrencyUnitName))
	{
		CurrencyUnitMap.Remove(CurrencyUnitName);
	}
}

UNSLEconMoney* UNSLEconCurrency::CreateCurrencyMoney(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList)
{
	// Create a new UNSLEconMoney object
	UNSLEconMoney* NewMoney = NewObject<UNSLEconMoney>(this, UNSLEconMoney::StaticClass());
	NewMoney->SetCurrency(this);
	NewMoney->AddCurrencyUnits(CurrUnitAmountList);
	return NewMoney;
}

int64 UNSLEconCurrency::CurrencyUnitsToUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList) const
{
	int64 TotalUnits = 0;
	for (const auto& CurrUnitAmount : CurrUnitAmountList)
	{
		UNSLEconCurrencyUnit* CurrencyUnitPtr = (*CurrencyUnitMap.Find(CurrUnitAmount.CurrencyUnitName));

		if (CurrencyUnitPtr == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("%s Not a %s valid currency unit"), *CurrUnitAmount.CurrencyUnitName, *CurrencyName);
			return 0;
		}

		if (!UNSLEconMoneyUtil::IsUnitsScalingAllowed(
				CurrUnitAmount.Amount,
				CurrencyUnitPtr->GetUnitConversionFactor()) || 
			!UNSLEconMoneyUtil::IsUnitsAdditionAllowed(
				TotalUnits,
				CurrUnitAmount.Amount * CurrencyUnitPtr->GetUnitConversionFactor()))
		{
			UE_LOG(LogTemp, Error, TEXT("CurrencyUnits conversion exceeds the allowable max result"));
			return 0;
		}

		TotalUnits += static_cast<int64>(CurrUnitAmount.Amount) * CurrencyUnitPtr->GetUnitConversionFactor();
	}

	return TotalUnits;
}

FString UNSLEconCurrency::UnitsToFormattedCurrency(int64 AmountToFormat) const
{
	if (UnitsToFormattedCurrencyDel.IsBound())
	{
		return UnitsToFormattedCurrencyDel.Execute(AmountToFormat);
	}

	return FString::Printf(TEXT("%lld"), AmountToFormat);
}

void UNSLEconCurrency::BindUnitsToFormattedCurrencyDelegate(const FUnitsToFormattedCurrencyDelegate& Delegate)
{
	UnitsToFormattedCurrencyDel = Delegate;
}

UNSLEconMoney* UNSLEconCurrency::FormattedCurrencyToMoney(FString FormattedCurrency) const
{
	if (StrToMoneyDel.IsBound())
	{
		return StrToMoneyDel.Execute(FormattedCurrency);
	}
	UE_LOG(LogTemp, Error, TEXT("No delegate bound"));
	return nullptr;
}

void UNSLEconCurrency::BindFormattedCurrencyToMoneyDelegate(const FStrToMoneyDelegate& Delegate)
{
	StrToMoneyDel = Delegate;
}
