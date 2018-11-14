// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandInterface.generated.h"

class UGraspableRegion;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHandInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * An object which can interact with UGraspableRegion's on game objects.
 *
 * PUBLIC CLASS MEMBERS:
 *
 * Grasp Region:
 * Grasp the given region with this hand.
 * @param return: true if the region was successfully grasped by this hand.
 *
 * Release Region:
 * Release the given region from this hand.
 * @param return: true if the region was successfully released from this hand.
 *
 * GetWorldTransform:
 * Get world transform of this hand.
 * @param return: the world transform of the hand.
 *
 * GetRelativeTransform:
 * Get the transform of the hand relative to its parent actor.
 * @param return: the transfrom of the hand relative to its parent actor.
 */
class MYPROJECT3_API IHandInterface
{
    GENERATED_IINTERFACE_BODY( )

public:    
    UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Hand Interface" )
    bool GraspRegion( UGraspableRegion* region );

    UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Hand Interface" )
    bool ReleaseRegion( UGraspableRegion* region );

    UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Hand Interface" )
    FTransform GetHandWorldTransform( ) const;

    UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Hand Interface" )
    FTransform GetHandRelativeTransform( ) const;
};
