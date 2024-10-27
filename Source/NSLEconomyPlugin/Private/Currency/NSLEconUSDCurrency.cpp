// Fill out your copyright notice in the Description page of Project Settings.

#include "NSLEconUSDCurrency.h"
#include "NSLEconTypes.h"
#include "NSLEconCurrencyUnit.h"

UNSLEconUSDCurrency::UNSLEconUSDCurrency(const FObjectInitializer& ObjectInitializer)
{
	Initialize("USD");

	// Creates currency units
	UNSLEconCurrencyUnit* Dollar = ObjectInitializer.CreateDefaultSubobject<UNSLEconCurrencyUnit>(this, TEXT("UNSLEconUSDCurrencyDollar"));
	Dollar->Initialize("Dollar", 100);

	UNSLEconCurrencyUnit* Quarter = ObjectInitializer.CreateDefaultSubobject<UNSLEconCurrencyUnit>(this, TEXT("UNSLEconUSDCurrencyQuarter"));
	Quarter->Initialize("Quarter", 25);
	
	UNSLEconCurrencyUnit* Dime = ObjectInitializer.CreateDefaultSubobject<UNSLEconCurrencyUnit>(this, TEXT("UNSLEconUSDCurrencyDime"));
	Dime->Initialize("Dime", 10);

	UNSLEconCurrencyUnit* Nickle = ObjectInitializer.CreateDefaultSubobject<UNSLEconCurrencyUnit>(this, TEXT("UNSLEconUSDCurrencyNickle"));
	Nickle->Initialize("Nickle", 5);

	UNSLEconCurrencyUnit* Cent = ObjectInitializer.CreateDefaultSubobject<UNSLEconCurrencyUnit>(this, TEXT("UNSLEconUSDCurrencyCent"));
	Cent->Initialize("Cent", 1);

	// Adds currency units to USD Currency
	AddCurrencyUnit(Dollar);
	AddCurrencyUnit(Quarter);
	AddCurrencyUnit(Dime);
	AddCurrencyUnit(Nickle);
	AddCurrencyUnit(Cent);

	// Binding currency formatting delegate 
	FUnitsToFormattedCurrencyDelegate Delegate;
	Delegate.BindUFunction(this, FName("USDCurrencyUnitsFormat"));
	BindUnitsToFormattedCurrencyDelegate(Delegate);

	// Binding currency formatting to money delegate 
	FStrToMoneyDelegate StrToMoneyDelegate;
	StrToMoneyDelegate.BindUFunction(this, FName("FormattedUSDToMoney"));
	BindFormattedCurrencyToMoneyDelegate(StrToMoneyDelegate);
}

// Example function to be called when the delegate is executed
FString UNSLEconUSDCurrency::USDCurrencyUnitsFormat(int64 AmountToFormat)
{
	bool isNegative = AmountToFormat < 0;
	AmountToFormat = FMath::Abs(AmountToFormat);

	// Extract dollars and cents
	int32 Dollars = AmountToFormat / 100;            // Get the dollar part
	int32 Cents = AmountToFormat % 100;              // Get the cents part

	// Add dollar sign
	FString FormattedUnits = FString::Printf(TEXT("%s$"), isNegative ? TEXT("-") : TEXT(""));

	// Format the dollar part with commas
	FString DollarString = FString::Printf(TEXT("%d"), Dollars);
	int32 Length = DollarString.Len();

	for (int32 i = 0; i < Length; ++i)
	{
		// Insert a comma every three digits
		if (i > 0 && (Length - i) % 3 == 0)
		{
			FormattedUnits += TEXT(",");
		}
		FormattedUnits += DollarString[i];
	}

	// Add cents, ensuring two digits
	FormattedUnits += FString::Printf(TEXT(".%02d"), Cents);


	return FormattedUnits;
}

UNSLEconMoney* UNSLEconUSDCurrency::FormattedUSDToMoney(FString FormattedCurrency)
{
	// Removes anything that is not a number or a '.'
	FString CleanedString;
	for (TCHAR Character : FormattedCurrency)
	{
		if (FChar::IsDigit(Character) || Character == TEXT('.'))
		{
			CleanedString.AppendChar(Character);
		}
	}

	// Splits dollars and cents
	TArray<FString> Substrings;
	CleanedString.ParseIntoArray(Substrings, TEXT("."), true);

	if (Substrings.Num() != 1 && Substrings.Num() != 2)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid FormattedCurrency"));
		return CreateCurrencyMoney({});
	}

	int32 Dollars = FCString::Atoi(*Substrings[0]);
	int32 Cents = 0;

	if (Substrings.Num() == 2)
	{
		FString CentsString = Substrings[1];

		// If the cents part has only 1 digit, append a zero to make it 2 digits
		if (CentsString.Len() == 1)
		{
			CentsString.AppendChar(TEXT('0'));
		}
		// Ensure we only take the first two digits, in case more than two digits are provided (like "2.345")
		Cents = FCString::Atoi(*CentsString.Left(2));
	}

	// Converts to currency units
	TArray<FNSLEconCurrencyUnitAmount> Amount = {
		FNSLEconCurrencyUnitAmount{
			Dollars, "Dollar"},
		FNSLEconCurrencyUnitAmount{
			Cents, "Cent"}
	};

	return CreateCurrencyMoney(Amount);
}