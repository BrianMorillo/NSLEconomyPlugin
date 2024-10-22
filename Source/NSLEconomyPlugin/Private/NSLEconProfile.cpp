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
	if (!UNSLEconMoneyUtil::IsMoneyValid(GetValue()))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid UNSLEconProfile value currency"));
		return;
	}

	if (!UNSLEconMoneyUtil::AreValidForOperation(GetValue(), NewValue))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid or mismatching UNSLEconProfile and UNSLEconMoney currencies"));
		return;
	}

	GetMoney()->SetTo(NewValue);
}

UNSLEconMoney* UNSLEconProfile::GetMoney()
{
	return Money;
}

void UNSLEconProfile::AddItemEntry(UNSLEconItemEntry* ItemEntry)
{
	if (!UNSLEconMoneyUtil::AreValidForOperation(GetMoney(), ItemEntry->ItemPtr->GetValue()))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid or mismatching UNSLEconProfile and UNSLEconItemEntry currencies"));
		return;
	}

	UNSLEconContainerItem::AddItemEntry(ItemEntry);
}
