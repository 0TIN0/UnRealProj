// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayCharacter.h"
#include "PlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class PlayerAnimation : uint8
{
	// 1100 
	Idle UMETA(DisplayName = "서있는 모션"),
	Left UMETA(DisplayName = "왼쪽"),      // 0001
	Right  UMETA(DisplayName = "오른쪽"),  // 0010
	Forward UMETA(DisplayName = "앞"), // 0100
	BackWard UMETA(DisplayName = "뒤"),  // 1000
};

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
