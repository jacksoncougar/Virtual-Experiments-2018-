// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "HandInterface.h"
#include "HandComponent.h"
#include "GripHint.h"
#include "FHandInformation.h"
#include "Classes/Components/SphereComponent.h"
#include "GraspableRegion.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FGraspedDelegate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FReleasedDelegate );

/**
* PUBLIC CLASS MEMBER DATA:
*
* RegionName:
* The name of the region, which should describe what the object or thing being grasped is
* because it is used for context hinting (animations, events, etc).
*
* CanBeGrasped (DEPRECATE):
* True when the region can be grasped by any hand (deprecate this).
*
* OnGrasped:
* Multicast delegate fired after the Grasp function completes.
*
* OnGraspReleased:
* Multicast delegate fired after the Release function completes.
*
*/
UCLASS( Blueprintable, meta = ( BlueprintSpawnableComponent ) )
class MYPROJECT3_API UGraspableRegion : public USphereComponent
{
    GENERATED_BODY( )

public:

    UGraspableRegion( );
    ~UGraspableRegion( );

    // The name of the region (should be descriptive and unique per region).
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Graspable Region" )
        FName RegionName;

    // Flag indicates if this grip can be grasped.
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Graspable Region" )
        bool CanBeGrasped = true;

    // Called when this region is grasped by a hand.
    UPROPERTY( BlueprintAssignable, Category = "Graspable Interface" )
        FGraspedDelegate OnGrasped;

    // Called when this region is released by a hand.
    UPROPERTY( BlueprintAssignable, Category = "Graspable Interface" )
        FReleasedDelegate OnGraspReleased;

    // Called when this region is no longer being grasped by any hands.
    UPROPERTY( BlueprintAssignable, Category = "Graspable Interface" )
        FReleasedDelegate OnAllGraspsReleased;


protected:

    /** the collision type of the object before being grasped */
    ECollisionChannel graspedComponentCollisionObjectType;

public:

    // Disables this region for grasping
    UFUNCTION( BlueprintCallable, Category = "Graspable Region" )
        void Disable( );

    // Enables this region for grasping
    UFUNCTION( BlueprintCallable, Category = "Graspable Region" )
        void Enable( );

    /**
     * Returns the hinting data for the given hand.
     * @param transform: world transform of the grasping hand.
     */
    UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Graspable Region" )
        FGripHint GetHint( const FHandInformation hand );
    virtual FGripHint GetHint_Implementation( const FHandInformation hand );

    /**
     * Returns the component that should be grasped by this region.
     * @param return - the component that should be grasped by this region.
     */
    UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Graspable Region" )
        UPrimitiveComponent * GetGraspedComponent( ) const;
    virtual UPrimitiveComponent * GetGraspedComponent_Implementation( ) const;

    /**
     * Returns true if this region is being grasped.
     * @return: returns true if this region is being grasped.
     */
    UFUNCTION( BlueprintCallable, Category = "Graspable Region" )
        bool GetIsGrasped( );

    /**
     * Returns true if the given hand is holding this region.
     * @param hand: the hand to check.
     */
    UFUNCTION( BlueprintCallable, Category = "Graspable Region" )
        bool CheckBeingHeld( const UObject* hand ) const;

    /**
     * Returns all hands holding this region.
     * @return: array of hand objects holding this region.
     */
    UFUNCTION( BlueprintCallable, Category = "Graspable Region" )
        TArray<UObject*> GetHands( ) const;

    /**
    * Returns the name of the graspable region.
    * @param return - the name of the graspable region.
    */
    UFUNCTION( BlueprintCallable, Category = "Graspable Region" )
        FName const GetRegionName( ) const;

    /**
    * Call this function when a region is grasped by a hand.
    */
    UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Graspable Interface" )
        void Grasp( UObject* hand, ECollisionChannel collisionObjectType = ECollisionChannel::ECC_EngineTraceChannel2 );
    virtual void Grasp_Implementation( UObject* hand, ECollisionChannel collisionObjectType = ECollisionChannel::ECC_EngineTraceChannel2 );

    /**
    * Call this function when a region is released by a hand.
    */
    UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Graspable Interface" )
        void Release( UObject* hand );
    virtual void Release_Implementation( UObject* hand );


    bool operator==( const UGraspableRegion& other ) const
    {
        return RegionName == other.RegionName;
    }

private:
    TArray<UObject*> graspers;
    TArray<UObject*> pendingOverlaps;
    FTimerHandle releaseTimer;
    FTimerDelegate func;

    UFUNCTION()
    void GraspedComponentEndOverlap( UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex );

    UFUNCTION()
    void ResetReleasedObject( UPrimitiveComponent* object );

};



