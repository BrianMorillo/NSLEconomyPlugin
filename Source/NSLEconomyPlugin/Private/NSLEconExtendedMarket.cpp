// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconExtendedMarket.h"
#include "NSLEconPurchaseTransaction.h"
#include "NSLEconMarketEntry.h"
#include "NSLEconItem.h"
#include "NSLEconMoney.h"
#include "NSLEconCurrency.h"
#include "NSLEconMarketExtendedEntry.h"

UNSLEconExtendedMarket::UNSLEconExtendedMarket()
{
}

/*
	Returns Adjusted Item Market Value:
	New Price = Current Price * (1 + alpha * ((Demand - Supply) / Supply))
*/
UNSLEconMoney* UNSLEconExtendedMarket::GetAdjustedItemMarketValue(
	UNSLEconMarketEntry* MarketItemEntry) const
{
	UNSLEconMarketExtendedEntry* ItemEntry = Cast<UNSLEconMarketExtendedEntry>(MarketItemEntry);
	UNSLEconMoney* ItemCurrentPrice = ItemEntry->ItemPtr->GetValue();
	int32 Demand = ItemEntry->Demand;
	int32 Supply = ItemEntry->Supply;

	UNSLEconMoney* NewItemPrice = UNSLEconMoney::ScaledBy(
		ItemCurrentPrice,
		1 + Alpha * ((float)(Demand - Supply) / Supply)
	);

	return NewItemPrice;
}
