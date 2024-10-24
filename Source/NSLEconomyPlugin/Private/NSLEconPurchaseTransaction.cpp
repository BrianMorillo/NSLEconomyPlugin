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
    if (!IsValidTransaction()) 
    {
        return;
    }

    UNSLEconMoney* TotalMoneyToPay = UNSLEconMoney::ScaledBy(PurchasePrice, QuantityToPurchase);

    Seller->GetMoney()->Add(TotalMoneyToPay);
    Buyer->GetMoney()->Substract(TotalMoneyToPay);

    UNSLEconItemEntry* SellerItemEntry = Cast<UNSLEconItemEntry>(Seller->GetEntry(ItemId));
    // Handle seller transaction side
    SellerItemEntry->SetQuantity(SellerItemEntry->GetQuantity() - QuantityToPurchase);

    // Handle buyer transaction side
    UNSLEconItemEntry* BoughtItemEntry = DuplicateObject(SellerItemEntry, GetTransientPackage());
    BoughtItemEntry->SetQuantity(QuantityToPurchase);
    Buyer->AddItemEntry(BoughtItemEntry);
}

bool UNSLEconPurchaseTransaction::IsValidTransaction_Implementation() const
{
    if (!Seller)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Seller"));
        return false;
    }

    if (!Buyer)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Buyer"));
        return false;
    }

    if (!PurchasePrice)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid PurchasePrice"));
        return false;
    }

    if (!ItemId.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid item id"));
        return false;
    }

    if (QuantityToPurchase <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Quantity"));
        return false;
    }

    if (MarketTransactionType != EPurchaseTransactionType::Buy && MarketTransactionType != EPurchaseTransactionType::Sell)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid transaction type"));
        return false;
    }

    if (!UNSLEconMoneyUtil::AreValidForOperation(Buyer->GetMoney(), Seller->GetMoney()))
    {
        UE_LOG(LogTemp, Error, TEXT("Transaction buyer and seller mismatching currencies"));
        return false;
    }

    UNSLEconItemEntry* SellerItemEntry = Cast<UNSLEconItemEntry>(Seller->GetEntry(ItemId));
    if (!SellerItemEntry || !SellerItemEntry->ItemPtr)
    {
        UE_LOG(LogTemp, Error, TEXT("No entry for item found in seller profile"));
        return false;
    }

    if (SellerItemEntry->GetQuantity() < QuantityToPurchase)
    {
        UE_LOG(LogTemp, Error, TEXT("Not enough items remaining in seller profile"));
        return false;
    }

    // Scales the item price by the amount of items wanted
    UNSLEconMoney* TotalMoneyToPay = UNSLEconMoney::ScaledBy(PurchasePrice, QuantityToPurchase);

    // checks if scaling was not successful 
    if (TotalMoneyToPay == nullptr)
    {
        return false;
    }

    // Checks if money substraction from buyer operation is possible
    if (!UNSLEconMoneyUtil::IsSubstractionAllowed(Buyer->GetMoney(), TotalMoneyToPay))
    {
        return false;
    }

    // Checks if money addition to seller operation is possible
    if (!UNSLEconMoneyUtil::IsAdditionAllowed(Seller->GetMoney(), TotalMoneyToPay))
    {
        return false;
    }

    return true;

}
