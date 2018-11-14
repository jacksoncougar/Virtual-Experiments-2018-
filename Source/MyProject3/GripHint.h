// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GripHint.generated.h"

USTRUCT( BlueprintType )
struct MYPROJECT3_API FGripHint
{
    GENERATED_USTRUCT_BODY( )

    /**
    * The name of the graspable region.
    * 
    * Details: 
    * The name is used for hinting what the region is (i.e: "handle", "wheel") and 
    * should be unique for each region on an object.
    */
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Grip Hint" )
        /// <summary>
        /// The name of the graspable region.
        /// </summary>
        FName Name;

    /**
    * The transform that the graspable component should be gripped using.
    */
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Grip Hint" )
        /// <summary>
        /// The transform to use when grasping
        /// </summary>
        FTransform Transform;

    /**
    * True if the Transform is relative to the hand.
    */
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Grip Hint" )
        bool RelativeTransform;

    /**
    * The location of this grip in World-space.
    */
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Grip Hint" )
        FVector Location;

    /**
    * True if the graspable component is already gripped.
    */
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Grip Hint" )
        bool IsGrasped;

    /**
    * True if the graspable component is ready to be gripped.
    */
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Grip Hint" )
        bool CanBeGrasped;


    FGripHint( ) :Name( ), Transform( ), IsGrasped( false ), Location( ), CanBeGrasped( false ), RelativeTransform( false )
    {
    }
};
