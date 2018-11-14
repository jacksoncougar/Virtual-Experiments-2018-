// Fill out your copyright notice in the Description page of Project Settings.

#include "GraspableRegion.h"

UGraspableRegion::UGraspableRegion( )
{
}

UGraspableRegion::~UGraspableRegion( )
{
}

void UGraspableRegion::Disable( )
{
    CanBeGrasped = false;
}

void UGraspableRegion::Enable( )
{
    CanBeGrasped = true;
}

/**
 * Returns the grasping hint for the given hand location
 *
 * @param location: the location of the grasping hand.
 */
FGripHint UGraspableRegion::GetHint_Implementation( const FHandInformation hand )
{
    FGripHint hint;

    hint.CanBeGrasped = CanBeGrasped;
    hint.IsGrasped = GetIsGrasped();
    hint.Name = RegionName;
    hint.Location = GetComponentLocation( );

    return hint;
}

/**
 * Returns the underlying component that responds to this graspable region.
 */
class UPrimitiveComponent * UGraspableRegion::GetGraspedComponent_Implementation( ) const
{
    auto parent = GetAttachParent( );
    
    return Cast<UPrimitiveComponent>( parent );
}

bool UGraspableRegion::GetIsGrasped( )
{
    return graspers.Num( ) > 0;
}

/**
 * Returns true if the given hand is grasping the region.
 */
 bool UGraspableRegion::CheckBeingHeld( const UObject * hand ) const
 {
     return graspers.Contains( hand );
 }

 TArray<UObject*> UGraspableRegion::GetHands( ) const
 {
     return graspers;
 }

/**
 * Returns the name of the graspable region.
 */
FName const UGraspableRegion::GetRegionName( ) const
{
    return RegionName;
}

void UGraspableRegion::Grasp_Implementation( UObject* hand, ECollisionChannel collisionObjectType )
{
    if ( hand )
    {
        graspers.AddUnique( hand );

        UPrimitiveComponent* component = GetGraspedComponent( );

        if ( component )
        {
            graspedComponentCollisionObjectType = component->GetCollisionObjectType( );
            component->SetCollisionObjectType( collisionObjectType );
            component->UpdateCollisionProfile( );
        }
        
        if ( OnGrasped.IsBound( ) )
        {
            OnGrasped.Broadcast( );
        }
    }
}

/**
 * Waits until the released component has stopped overlapping the hand that released 
 * it before setting the collision object type back to one that might block with that hand.
 */
void UGraspableRegion::GraspedComponentEndOverlap( UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex )
{
    // did the released component stop overlapping the hand?
    if( pendingOverlaps.Contains(otherActor) || pendingOverlaps.Contains( otherComp ) )
    {
        overlappedComponent->SetCollisionObjectType( graspedComponentCollisionObjectType );
        pendingOverlaps.Remove( otherActor );
        overlappedComponent->OnComponentEndOverlap.RemoveDynamic( this, &UGraspableRegion::GraspedComponentEndOverlap );
    }
}

void UGraspableRegion::ResetReleasedObject( UPrimitiveComponent* object )
{
    if ( object )
    {
        //object->SetCollisionObjectType( graspedComponentCollisionObjectType );
    }
}

void UGraspableRegion::Release_Implementation( UObject* hand )
{
    const double delay = 0.25;

    if ( hand )
    {
        UPrimitiveComponent* component = GetGraspedComponent( );

        if ( component )
        {            
            component->SetCollisionObjectType( graspedComponentCollisionObjectType );
            //func.BindUFunction( this, FName("ResetReleasedObject"), component );
            //GetWorld( )->GetTimerManager( ).SetTimer( releaseTimer, func, delay, false );
        }

        graspers.Remove( hand );
        
        if ( OnGraspReleased.IsBound( ) )
        {
            OnGraspReleased.Broadcast( );
        }

        if ( OnAllGraspsReleased.IsBound( ) && graspers.Num( ) <= 0 )
        {
            OnAllGraspsReleased.Broadcast( );
        }
    }
}

