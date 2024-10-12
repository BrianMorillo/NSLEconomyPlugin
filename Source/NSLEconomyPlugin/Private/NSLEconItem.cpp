// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconItem.h"
#include "NSLEconMoney.h"

UNSLEconItem::UNSLEconItem()
    : Name("")
    , Value(nullptr)
{
    Id = FGuid::NewGuid();
    //Value = NewObject<UNSLEconMoney>(this, UNSLEconMoney::StaticClass());
} 

FGuid UNSLEconItem::GetId() const
{
    return Id;
}
