// Fill out your copyright notice in the Description page of Project Settings.


#include "NSLEconPurchaseTransaction.h"
#include "NSLEconProfile.h"
#include "NSLEconContainerItem.h"
#include "NSLEconItemEntry.h"
#include "NSLEconTypes.h"
#include "NSLEconMoney.h"
#include "NSLEconMoneyUtil.h"

void UNSLEconPurchaseTransaction::Execute_Implementation()
{
    if (!Seller)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Seller"));
        return;
    }

    if (!Buyer)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Buyer"));
        return;
    }

    if (!PurchasePrice)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid PurchasePrice"));
        return;
    }

    if (!ItemId.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid item id"));
        return;
    }

    if (QuantityToPurchase <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Quantity"));
        return;
    }

    if (MarketTransactionType != ETransactionType::Buy && MarketTransactionType != ETransactionType::Sell)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid transaction type"));
        return;
    }

    if (!UNSLEconMoneyUtil::AreValidForOperation(Buyer->GetMoney(), Seller->GetMoney()))
    {
        UE_LOG(LogTemp, Error, TEXT("Transaction buyer and seller mismatching currencies"));
        return;
    }

    UNSLEconItemEntry* SellerItemEntry = Cast<UNSLEconItemEntry>(Seller->GetEntry(ItemId));
    if (!SellerItemEntry || !SellerItemEntry->ItemPtr)
    {
        UE_LOG(LogTemp, Error, TEXT("No entry for item found in seller profile"));
        return;
    }

    if (SellerItemEntry->GetQuantity() < QuantityToPurchase)
    {
        UE_LOG(LogTemp, Error, TEXT("Not enough items remaining in seller profile"));
        return;
    }

    // Scales the item price by the amount of items wanted
    UNSLEconMoney* TotalMoneyToPay = UNSLEconMoney::ScaledBy(PurchasePrice, QuantityToPurchase);

    // checks if scaling was not successful 
    if (TotalMoneyToPay == nullptr)
    {
        return;
    }

    // Attempts money substraction operation and checks if it was successful
    if (Buyer->GetMoney()->Substract(TotalMoneyToPay) == nullptr)
    {
        return;
    }

    // Attempts money addition operation and checks if it was successful
    if (Seller->GetMoney()->Add(TotalMoneyToPay) == nullptr)
    {
        return;
    }

    // Handle seller transaction side
    SellerItemEntry->SetQuantity(SellerItemEntry->GetQuantity() - QuantityToPurchase);

    // Handle buyer transaction side
    UNSLEconItemEntry* BoughtItemEntry = DuplicateObject(SellerItemEntry, GetTransientPackage());
    BoughtItemEntry->SetQuantity(QuantityToPurchase);
    Buyer->AddItemEntry(BoughtItemEntry);
}
