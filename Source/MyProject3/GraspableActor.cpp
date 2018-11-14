// Fill out your copyright notice in the Description page of Project Settings.

#include "GraspableActor.h"

/**
 * Returns all the graspable regions of the Actor.
 */
TArray<UGraspableRegion*> AGraspableActor::GetGraspableRegions_Implementation( ) const
{
    TArray<UGraspableRegion*> regions;
    auto components = GetComponentsByClass( UGraspableRegion::StaticClass( ) );
    
    for ( auto& region : components )
    {
        regions.Add( Cast<UGraspableRegion>( region ) );
    }
    
    return regions;
}

/**
* Returns the nearest graspable region to the given location.
*
* @param location: the location of the grasping hand.
* @param outHint: optional grip hinting information for the given location.
* @param distance: maximum distance of graspable region to return.
* @return: the nearest graspable region.
*
*/
UGraspableRegion* AGraspableActor::FindGraspableRegionNearestTo_Implementation( const FHandInformation hand, FGripHint& outHint, float distance ) const
{

    UGraspableRegion* nearestRegion = nullptr;
    auto graspableRegions = GetGraspableRegions( );
    
    outHint = FGripHint( );

    for ( auto sub = 0; sub < graspableRegions.Num( ); ++sub )
    {
        UGraspableRegion* region = graspableRegions[sub];

        if ( nullptr == region ) continue;

        FGripHint hint = region->GetHint( hand );
        FVector locationOfGrip = hint.Location;

        float distanceToGrip = FVector::Distance( locationOfGrip, hand.Transform.GetLocation( ) );

        if ( distanceToGrip < distance && hint.CanBeGrasped )
        {
            nearestRegion = region;
            distance = distanceToGrip;
            outHint = hint;
        }
    }

    return nearestRegion;
}

/**
 * Returns true if this actor is being grasped by any of its graspable regions.
 * @return: true if this actor is being grasped by any of its graspable regions.
 */
bool AGraspableActor::IsGrasped( ) const
{
    bool isGrasped = false;
    TArray<UGraspableRegion*> regions = GetGraspableRegions( );

    for ( auto* region : regions )
    {
        if ( region->GetIsGrasped() )
        {
            isGrasped = true;
            break;
        }
    }

    return isGrasped;
}

// Sets default values
AGraspableActor::AGraspableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGraspableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGraspableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

