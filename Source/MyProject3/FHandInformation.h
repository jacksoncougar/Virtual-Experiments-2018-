// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FHandInformation.generated.h"

/**
 * Information required for grabbing and dropping items.
 *
 *
 * Notes:
 * Decided to go with a fixed struct because using an interface was a giant pain. 
 * A grip needs basic information about the obeject that wants to grab it to 
 * allow for filtering of the responses. A simple data struct would suffice.
 */
USTRUCT( BlueprintType )
struct MYPROJECT3_API FHandInformation
{
    GENERATED_USTRUCT_BODY( )

        // The name of the "hand" object. Used for filtering with grips.
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Hand Information" )
        FName Name;

    // The current transform of the "hand" object. Used for location based filtering.
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Hand Information" )
        FTransform Transform;
};