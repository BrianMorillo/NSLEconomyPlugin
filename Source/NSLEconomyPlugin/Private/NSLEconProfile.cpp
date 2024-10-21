// Fill out your copyright notice in the Description page of Project Settings.

#include "NSLEconProfile.h"
#include "NSLEconMoney.h"
#include "NSLEconContainerItem.h"
#include "NSLEconItemEntry.h"
#include "NSLEconMoneyUtil.h"

UNSLEconProfile::UNSLEconProfile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) 
{
	Money = ObjectInitializer.CreateDefaultSubobject<UNSLEconMoney>(this, TEXT("NSLEconProfileMoney"));
}

void UNSLEconProfile::SetMoney(const UNSLEconMoney* NewValue)
{
	Money->SetTo(NewValue);
}

UNSLEconMoney* UNSLEconProfile::GetMoney()
{
	return Money;
}

void UNSLEconProfile::AddItemEntry(UNSLEconItemEntry* ItemEntry)
{
	if (ItemEntry->ItemPtr->GetValue()->GetCurrency() != Money->GetCurrency())
	{
		UE_LOG(LogTemp, Error, TEXT("Profile currency mismatch with item entry"));
		return;
	}

	UNSLEconContainerItem::AddItemEntry(ItemEntry);
}
