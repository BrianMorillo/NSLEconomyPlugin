// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconPricedItemEntry.h"
#include "NSLEconMoney.h"

UNSLEconPricedItemEntry::UNSLEconPricedItemEntry(const FObjectInitializer& ObjectInitializer)
{
	Price = ObjectInitializer.CreateDefaultSubobject<UNSLEconMoney>(this, TEXT("NSLEconPricedItemEntryMoney"));
}

UNSLEconMoney* UNSLEconPricedItemEntry::GetItemPrice() const
{
	return Price;
}