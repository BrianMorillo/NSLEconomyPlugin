// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconShopItemEntry.h"
#include "NSLEconItemEntry.h"
#include "NSLEconItem.h"
#include "NSLEconMoney.h"

UNSLEconShopItemEntry::UNSLEconShopItemEntry()
	: PriceMarkup(1.0)
{

}

float UNSLEconShopItemEntry::GetPriceMarkup()
{
	return PriceMarkup;
}

void UNSLEconShopItemEntry::SetPriceMarkup(float NewPriceMarkup)
{
	// Round the float value to 2 decimal places
	float RoundedPriceMarkup = FMath::RoundToFloat(NewPriceMarkup * 100.0f) / 100.0f;

	// Set the price markup using the rounded value
	PriceMarkup = RoundedPriceMarkup;
}
