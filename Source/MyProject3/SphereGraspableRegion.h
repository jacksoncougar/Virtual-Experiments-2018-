// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraspableRegion.h"
#include "SceneManagement.h"
#include "PrimitiveSceneProxy.h"
#include "SphereGraspableRegion.generated.h"

/**
 * A graspable region bounded by a sphere which can be grasped at any location
 */
UCLASS( Blueprintable, meta = ( BlueprintSpawnableComponent ) )
class MYPROJECT3_API USphereGraspableRegion : public UGraspableRegion
{
	GENERATED_BODY()
	

protected:

public:
    virtual FPrimitiveSceneProxy* CreateSceneProxy( ) override;

    virtual FGripHint GetHint_Implementation( const FHandInformation hand ) override;
	
};
