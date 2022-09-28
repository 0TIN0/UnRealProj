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
	Max UMETA(DisplayName = "최대치"),  // 1000
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

	FORCEINLINE double GetHP()
	{
		return m_HP;
	}


	FORCEINLINE bool IsDeath()
	{
		return m_HP <= 0;
	}

	// 타겟과의 거리가 2번인자의 Legnth보다 가깝게 있는지 판단
	bool GetIsRangeInTarget(AActor* _Target, float _Length);

	// 타겟의 방향을 얻어옴
	FVector GetTargetDir(AActor* _Target);

	// 타겟의 방향값을 정규화한 값
	FVector GetTargetDirNormalize(AActor* _Target);

	// 타겟의 방향으로 이동
	void SetTargetMovementInput(AActor* _Target, float Value = 1.f);

	// 타겟을 바라보도록 설정
	void SetTargetLook(AActor* _Target);
	
	template<typename T>
	T* TargetSearch(FName _Name, float _Range = -1.f)
	{
		return Cast<T>(_Name, _Range);
	}

	AActor* TargetSearch(FName _Name, float _Range = -1.f);

	TArray<AActor*> TargetsSearch(FName _Name, float _Range = -1.f);

	UFUNCTION(BlueprintCallable, Category = UR)
	virtual void CallDamage(double _Damage);

	FORCEINLINE void SetHP(double _HP)
	{
		m_HP = _HP;
	}

	FORCEINLINE	void SetAnimations(const TMap<DefaultAnimation, UAnimMontage*> _Animations)
	{
		m_Animations.Empty();
		m_Animations = _Animations;
	}

	virtual void DamageOn() {};
	virtual void DamageOff() {};


	TArray<FHitResult> CollisionCheck(const FVector& Pos, FName ProfileName, const struct FCollisionShape& CollisionShape)
	{
		return CollisionCheck(Pos, Pos, FQuat::Identity, ProfileName, CollisionShape);
	}

	TArray<FHitResult> CollisionCheck(const FVector& Start, const FVector& End, const FQuat& Rot, FName ProfileName, const struct FCollisionShape& CollisionShape);

	TArray<UActorComponent*> GetDamageCollision();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationData", meta = (AllowPrivateAccess = "true"))
	TMap<DefaultAnimation, UAnimMontage*>	m_Animations;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	DefaultAnimation AnimationState;

	class UURAnimInstance* m_AnimationInstance;

	bool m_IsAttack;
	double m_HP;
};
