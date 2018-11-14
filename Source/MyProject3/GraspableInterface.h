// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "GripHint.h"
#include "FHandInformation.h"
#include "GraspableInterface.generated.h"

class UGraspableRegion;
class UHandComponent;

// This class does not need to be modified.
UINTERFACE( MinimalAPI )
class UGraspableInterface : public UInterface
{
    GENERATED_BODY( )
};

/**
* Object which can be grasped by a hand object and manipulated physically in the world.
*/
class MYPROJECT3_API IGraspableInterface
{
    GENERATED_IINTERFACE_BODY( )

public:

    /**
    * Returns all graspable regions on the implementing object.
    */
    UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Graspable Interface" )
        TArray<UGraspableRegion*> GetGraspableRegions( ) const;

    /**
    * Finds the nearest graspable region to the given hand on this actor which can be grasped by the hand.
    */
    UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Graspable Interface" )
        UGraspableRegion* FindGraspableRegionNearestTo( const FHandInformation hand, FGripHint& outHint, float distance = 10 ) const;

};



