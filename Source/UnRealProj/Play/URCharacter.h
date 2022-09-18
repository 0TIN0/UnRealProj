// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/URAnimInstance.h"
#include "URCharacter.generated.h"

UENUM(BlueprintType)
enum class DefaultAnimation : uint8
{
	// 1100 
	Default UMETA(DisplayName = "애니메이션 지정안됨"),
	Idle UMETA(DisplayName = "서있는 모션"),
	Left UMETA(DisplayName = "왼쪽"),      // 0001
	Right  UMETA(DisplayName = "오른쪽"),  // 0010
	Forward UMETA(DisplayName = "앞"), // 0100
	BackWard UMETA(DisplayName = "뒤"),  // 1000
	Attack UMETA(DisplayName = "공격모션"),  // 1000
};

UCLASS()
class UNREALPROJ_API AURCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AURCharacter();

	FORCEINLINE UURAnimInstance* GetAnimationInstance()	const
	{
		return m_AnimationInstance;
	}

	FORCEINLINE bool IsAttack()	const
	{
		return m_IsAttack;
	}

	FORCEINLINE void AttackOn()
	{
		m_IsAttack = true;
	}

	FORCEINLINE void AttackOff()
	{
		m_IsAttack = false;
	}

	template<typename T>
	AActor* TargetSearch(FName _Name, float _Range = -1.f)
	{
		return Cast<T>(_Name, _Range);
	}

	AActor* TargetSearch(FName _Name, float _Range = -1.f);

	TArray<AActor*> TargetsSearch(FName _Name, float _Range = -1.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	DefaultAnimation AnimationState;

	bool m_IsAttack;

	class UURAnimInstance* m_AnimationInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationData", meta = (AllowPrivateAccess = "true"))
	TMap<DefaultAnimation, UAnimMontage*>	m_Animations;
};
