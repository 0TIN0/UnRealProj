// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacter.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents")
	PlayerAnimation AnimationState;


	UFUNCTION()
		FORCEINLINE PlayerAnimation GetAnimationState()
	{
		return AnimationState;
	}

	
};
