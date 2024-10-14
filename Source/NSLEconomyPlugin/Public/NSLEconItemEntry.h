// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NSLEconItemEntry.generated.h"

class UNSLEconItem;
/**
 * Represents an element on an NSLEconContainerItem
 */
UCLASS(Blueprintable)
class NSLECONOMYPLUGIN_API UNSLEconItemEntry : public UObject
{
	GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, Category = "NSLEconomy")
    int32 Quantity;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSLEconomy")
    const UNSLEconItem* ItemPtr;

    // Constructor

    // Example method to set the pointer
    void SetItem(const UNSLEconItem* NewItem)
    {
        ItemPtr = NewItem; // This will change the pointer to point to NewItem
    }

    void SetQuantity(int32 NewQuantity)
    {
        Quantity = FMath::Max(0, NewQuantity); 
    }

    int32 GetQuantity() const
    {
        return Quantity;
    }

    UNSLEconItemEntry()
        : Quantity(0), ItemPtr(nullptr)
    {}
	
};
