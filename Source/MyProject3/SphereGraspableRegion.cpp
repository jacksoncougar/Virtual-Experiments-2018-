// Fill out your copyright notice in the Description page of Project Settings.

#include "SphereGraspableRegion.h"

FPrimitiveSceneProxy* USphereGraspableRegion::CreateSceneProxy( )
{
    /** Represents a DrawLightRadiusComponent to the scene manager. */
    class FSphereSceneProxy : public FPrimitiveSceneProxy
    {
    public:

        /** Initialization constructor. */
        FSphereSceneProxy( const USphereGraspableRegion* InComponent )
            : FPrimitiveSceneProxy( InComponent )
            , region(InComponent)
            , bDrawOnlyIfSelected( false )
            , SphereColor( FColor() )
            , SphereRadius( InComponent->SphereRadius )
            , bGraspable( InComponent->CanBeGrasped )
        {
            bWillEverBeLit = false;
        }

        // FPrimitiveSceneProxy interface.

        virtual void GetDynamicMeshElements( const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector ) const override
        {
            QUICK_SCOPE_CYCLE_COUNTER( STAT_SphereSceneProxy_GetDynamicMeshElements );

            for ( int32 ViewIndex = 0; ViewIndex < Views.Num( ); ViewIndex++ )
            {
                if ( VisibilityMap & ( 1 << ViewIndex ) )
                {
                    const FSceneView* View = Views[ViewIndex];
                    FPrimitiveDrawInterface* PDI = Collector.GetPDI( ViewIndex );

                    const FMatrix& LocalToWorld = GetLocalToWorld( );
                    const FLinearColor DrawSphereColor = GetViewSelectionColor( SphereColor, *View, IsSelected( ), IsHovered( ), false, IsIndividuallySelected( ) );

                    // Taking into account the min and maximum drawing distance
                    const float DistanceSqr = ( View->ViewMatrices.GetViewOrigin( ) - LocalToWorld.GetOrigin( ) ).SizeSquared( );
                    if ( DistanceSqr < FMath::Square( GetMinDrawDistance( ) ) || DistanceSqr > FMath::Square( GetMaxDrawDistance( ) ) )
                    {
                        continue;
                    }

                    float AbsScaleX = LocalToWorld.GetScaledAxis( EAxis::X ).Size( );
                    float AbsScaleY = LocalToWorld.GetScaledAxis( EAxis::Y ).Size( );
                    float AbsScaleZ = LocalToWorld.GetScaledAxis( EAxis::Z ).Size( );
                    float MinAbsScale = FMath::Min3( AbsScaleX, AbsScaleY, AbsScaleZ );

                    FVector ScaledX = LocalToWorld.GetUnitAxis( EAxis::X ) * MinAbsScale;
                    FVector ScaledY = LocalToWorld.GetUnitAxis( EAxis::Y ) * MinAbsScale;
                    FVector ScaledZ = LocalToWorld.GetUnitAxis( EAxis::Z ) * MinAbsScale;

                    const int32 SphereSides = FMath::Clamp<int32>( SphereRadius / 4.f, 16, 64 );
                    FLinearColor color = region->CanBeGrasped ? FLinearColor::Green : FLinearColor::Red;

                    DrawCircle( PDI, LocalToWorld.GetOrigin( ), ScaledX, ScaledY, color, SphereRadius, SphereSides, SDPG_World );
                    DrawCircle( PDI, LocalToWorld.GetOrigin( ), ScaledX, ScaledZ, color, SphereRadius, SphereSides, SDPG_World );
                    DrawCircle( PDI, LocalToWorld.GetOrigin( ), ScaledY, ScaledZ, color, SphereRadius, SphereSides, SDPG_World );
                }
            }
        }

        virtual FPrimitiveViewRelevance GetViewRelevance( const FSceneView* View ) const override
        {
            const bool bVisibleForSelection = !bDrawOnlyIfSelected || IsSelected( );
            const bool bVisibleForShowFlags = true; // @TODO

                                                    // Should we draw this because collision drawing is enabled, and we have collision
            const bool bShowForCollision = View->Family->EngineShowFlags.Collision && IsCollisionEnabled( );

            FPrimitiveViewRelevance Result;
            Result.bDrawRelevance = ( IsShown( View ) && bVisibleForSelection && bVisibleForShowFlags ) || bShowForCollision;
            Result.bDynamicRelevance = true;
            Result.bShadowRelevance = IsShadowCast( View );
            Result.bEditorPrimitiveRelevance = UseEditorCompositing( View );
            return Result;
        }

        virtual uint32 GetMemoryFootprint( void ) const override { return( sizeof( *this ) + GetAllocatedSize( ) ); }
        uint32 GetAllocatedSize( void ) const { return( FPrimitiveSceneProxy::GetAllocatedSize( ) ); }

    private:
        const USphereGraspableRegion* region;
        const uint32				bDrawOnlyIfSelected : 1;
        const FColor				SphereColor;
        const float					SphereRadius;
        const uint32                bGraspable : 1;
    };

    return new FSphereSceneProxy( this );
}

/**
 * Returns hinting information of a sphere shaped graspable region.
 *
 * <p> Returns the current object transform as the preferred grip transform. 
 * The grip is graspable if the hand is within the radius of the sphere.
 * </P>
 * 
 * @param handLocation: the location of the grasping hand.
 */
FGripHint USphereGraspableRegion::GetHint_Implementation( const FHandInformation hand )
{
    FGripHint hint = Super::GetHint_Implementation( hand );
    UPrimitiveComponent* object = GetGraspedComponent( );
    FVector location = hand.Transform.GetLocation( );
    FVector origin = GetComponentLocation( );
    FVector rayFromOrigin = location - origin;
    FVector start;    
    FHitResult result;
    FCollisionQueryParams params;
    float distance;

    // if the vector is degenerate just use a default value.
    if ( !rayFromOrigin.Normalize( ) )
        rayFromOrigin = FVector::UpVector;

    // project a point on the sphere surface and trace backwards to find a 
    // grip location on the gripped component.
    start = origin + rayFromOrigin * SphereRadius;
    
    if ( nullptr != object )
    {
        object->LineTraceComponent( result, start, origin, params );

        if ( result.Time < 1.0 )
        {
            // calculate the distance from the grip to the hit point on the component
            distance = FVector::Distance( result.Location, origin );

            hint.Transform = object->GetComponentTransform( );
            hint.CanBeGrasped = ( distance < SphereRadius ? true : false ) && CanBeGrasped;
        }
    }

    return hint;
}


