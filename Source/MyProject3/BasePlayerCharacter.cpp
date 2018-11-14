// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerCharacter.h"

FName ABasePlayerCharacter::RightMotionControllerComponentName( TEXT( "Right Graspable Motion Controller" ) );
FName ABasePlayerCharacter::LeftMotionControllerComponentName( TEXT( "Left Graspable Motion Controller" ) );

ABasePlayerCharacter::ABasePlayerCharacter( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    LeftGraspMotionController = CreateDefaultSubobject<UGripMotionControllerComponent>( ABasePlayerCharacter::LeftMotionControllerComponentName );
    if ( LeftGraspMotionController )
    {
        LeftGraspMotionController->SetupAttachment( RootComponent );
        LeftGraspMotionController->Hand = EControllerHand::Left;
        LeftGraspMotionController->bOffsetByHMD = false;
        // Keep the controllers ticking after movement
        if ( VRReplicatedCamera )
        {
            LeftGraspMotionController->AddTickPrerequisiteComponent( GetCharacterMovement( ) );
        }
    }

    RightGraspMotionController = CreateDefaultSubobject<UGripMotionControllerComponent>( ABasePlayerCharacter::RightMotionControllerComponentName );
    if ( RightGraspMotionController )
    {
        RightGraspMotionController->SetupAttachment( RootComponent );
        RightGraspMotionController->Hand = EControllerHand::Right;
        RightGraspMotionController->bOffsetByHMD = false;
        // Keep the controllers ticking after movement
        if ( VRReplicatedCamera )
        {
            RightGraspMotionController->AddTickPrerequisiteComponent( GetCharacterMovement( ) );
        }
    }
}