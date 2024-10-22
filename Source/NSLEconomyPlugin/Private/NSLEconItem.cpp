// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconItem.h"
#include "NSLEconMoney.h"
#include "NSLEconCurrency.h"

//UNSLEconItem::UNSLEconItem()
//: Name("")
//, Value(nullptr)
//{
//}

UNSLEconItem::UNSLEconItem(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , Name("")
    , Value(ObjectInitializer.CreateDefaultSubobject<UNSLEconMoney>(this, TEXT("UNSLEconItemMoney")))
{
    Id = FGuid::NewGuid();
    //Value = NewObject<UNSLEconMoney>(this, UNSLEconMoney::StaticClass());
} 

void UNSLEconItem::SetCurrency(UNSLEconCurrency* Currency)
{
    Value->Initialize(Currency);
}

void UNSLEconItem::SetValue(const UNSLEconMoney* NewValue)
{
    Value->SetTo(NewValue);
}
/*
UNSLEconMoney* UNSLEconItem::AddValue(const UNSLEconMoney* Other)
{
    return Value->Add(Other);
}

UNSLEconMoney* UNSLEconItem::SubstractValue(const UNSLEconMoney* Other)
{
    return Value->Substract(Other);
}*/

UNSLEconMoney* UNSLEconItem::GetValue() const
{
    return Value;
}

FGuid UNSLEconItem::GetId() const
{
    return Id;
}


