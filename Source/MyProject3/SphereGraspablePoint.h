// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SphereGraspableRegion.h"
#include "SphereGraspablePoint.generated.h"

/**
 * A graspable region bounded by a sphere which snaps to a hand Transform.
 */
UCLASS( Blueprintable, meta = ( BlueprintSpawnableComponent ) )
class MYPROJECT3_API USphereGraspablePoint : public USphereGraspableRegion
{
	GENERATED_BODY()
	

public:

    virtual FPrimitiveSceneProxy* CreateSceneProxy( ) override;
    virtual FGripHint GetHint_Implementation( const FHandInformation hand ) override;
	
};
