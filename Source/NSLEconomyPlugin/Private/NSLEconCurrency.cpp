// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconCurrency.h"
#include "NSLEconCurrencyUnit.h"
#include "NSLEconTypes.h"
#include "NSLEconMoney.h"

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

FGuid UNSLEconCurrency::AddCurrencyUnit(const FString& CurrencyUnitName, int32 UnitConversionFactor)
{
	FGuid NewGuid = FGuid::NewGuid();
	UNSLEconCurrencyUnit* NewCurrencyUnit = NewObject<UNSLEconCurrencyUnit>(this, UNSLEconCurrencyUnit::StaticClass());
	NewCurrencyUnit->Initialize(CurrencyUnitName, UnitConversionFactor);
	CurrencyUnitMap.Add(NewGuid, NewCurrencyUnit);

	return NewGuid;
}


void UNSLEconCurrency::RemoveCurrencyUnit(FGuid CurrencyUnitId)
{
	if (CurrencyUnitMap.Contains(CurrencyUnitId))
	{
		CurrencyUnitMap.Remove(CurrencyUnitId);
	}
}

UNSLEconMoney* UNSLEconCurrency::CreateCurrencyMoney(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList)
{
	// Create a new UNSLEconMoney object
	UNSLEconMoney* NewMoney = NewObject<UNSLEconMoney>(this, UNSLEconMoney::StaticClass());
	NewMoney->Initialize(this);
	NewMoney->AddCurrencyUnits(CurrUnitAmountList);
	return NewMoney;
}

int64 UNSLEconCurrency::CurrencyUnitsToUnits(const TArray<FNSLEconCurrencyUnitAmount> CurrUnitAmountList)
{
	int64 TotalUnits = 0;
	for (const auto& CurrUnitAmount : CurrUnitAmountList)
	{
		UNSLEconCurrencyUnit* CurrencyUnitPtr = (*CurrencyUnitMap.Find(CurrUnitAmount.CurrencyUnitId));

		if (CurrencyUnitPtr == nullptr)
		{
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
	return "";
}

void UNSLEconCurrency::BindUnitsToFormattedCurrencyDelegate(const FUnitsToFormattedCurrencyDelegate& Delegate)
{
	UnitsToFormattedCurrencyDel = Delegate;
}


//void UNSLEconCurrency::CreateCurrencyUnit(const FString& CurrencyUnitName, float ConversionFactor)
//{
//	// Create a new Guid for the currency unit
//	FGuid NewGuid = FGuid::NewGuid();
//
//	// Create a new UNSLEconCurrencyUnit object and initialize it
//	UNSLEconCurrencyUnit* NewCurrencyUnit = NewObject<UNSLEconCurrencyUnit>(this, UNSLEconCurrencyUnit::StaticClass());
//	if (NewCurrencyUnit)
//	{
//		NewCurrencyUnit->Initialize(CurrencyUnitName, ConversionFactor);
//
//		// Add the new unit to the map
//		AddCurrencyUnit(NewGuid, NewCurrencyUnit);
//	}
//}