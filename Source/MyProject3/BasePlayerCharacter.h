// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GripMotionControllerComponent.h"
#include "VRCharacter.h"
#include "BasePlayerCharacter.generated.h"

/**
 * Because reasons.
 */
UCLASS()
class MYPROJECT3_API ABasePlayerCharacter : public AVRCharacter
{
    GENERATED_BODY( )

public:
    ABasePlayerCharacter( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get( ) );	

public:
    UPROPERTY( Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
    UGripMotionControllerComponent* LeftGraspMotionController;

    UPROPERTY( Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
    UGripMotionControllerComponent* RightGraspMotionController;

    /** Name of the LeftMotionController component. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
    static FName LeftMotionControllerComponentName;

    /** Name of the RightMotionController component. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
    static FName RightMotionControllerComponentName;
};
