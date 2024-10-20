// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconProfile.h"
#include "NSLEconMoney.h"
#include "NSLEconContainerItem.h"

UNSLEconProfile::UNSLEconProfile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) 
{
	Money = ObjectInitializer.CreateDefaultSubobject<UNSLEconMoney>(this, TEXT("NSLEconProfileMoney"));
	Items = ObjectInitializer.CreateDefaultSubobject<UNSLEconContainerItem>(this, TEXT("NSLEconProfileItems"));
}
