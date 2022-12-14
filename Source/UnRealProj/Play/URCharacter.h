// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/URAnimInstance.h"
#include "Global/UREnum.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "URCharacter.generated.h"


UCLASS()
class UNREALPROJ_API AURCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AURCharacter();

	UFUNCTION(BlueprintCallable, Category = UR)
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

	UFUNCTION(BlueprintCallable, Category = UR)
	FORCEINLINE double GetHP()
	{
		return m_HP;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		FORCEINLINE double GetCharacterMaxHP()
	{
		return m_MaxHP;
	}


	FORCEINLINE bool IsDeath()
	{
		return m_HP <= 0;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		FORCEINLINE void SetHPPercent(double _Perc)
	{
		m_HPPercent = _Perc;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		void ReSetHPPercent();


	UFUNCTION(BlueprintCallable, Category = UR)
		FORCEINLINE double GetHPPercent()
	{
		return m_HPPercent;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		FORCEINLINE void SetMPPercent(double _Perc)
	{
		m_MPPercent = _Perc;
	}


	UFUNCTION(BlueprintCallable, Category = UR)
		double GetMaxHP();

	UFUNCTION(BlueprintCallable, Category = UR)
		FORCEINLINE double GetMPPercent()
	{
		return m_MPPercent;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		double GetStamina();

	UFUNCTION(BlueprintCallable, Category = UR)
		double GetMaxStamina();

	UFUNCTION(BlueprintCallable, Category = UR)
		float GetQSkillCoolTime()
	{
		return m_QSkillCurCollTime;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		float GetESkillCoolTime()
	{
		return m_ESkillCurCollTime;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		float GetRSkillCoolTime()
	{
		return m_RSkillCurCollTime;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		float GetQSkillMaxCoolTime()
	{
		return m_QSkillMaxCollTime;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		float GetESkillMaxCoolTime()
	{
		return m_ESkillMaxCollTime;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		float GetRSkillMaxCoolTime()
	{
		return m_RSkillMaxCollTime;
	}

	void SetHitType(EHitType _HitType)
	{
		m_HitType = _HitType;
	}

	EHitType GetHitType()	const
	{
		return m_HitType;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
	bool GetIsBlocking()	const
	{
		return m_IsBlocking;
	}


	void SetKnockDown(bool _HitType)
	{
		m_IsKnockDown = _HitType;
	}

	bool IsHitType()	const
	{
		return m_IsKnockDown;
	}

	struct FURPlayerDataInfo* GetPlayerInfo()	const
	{
		return m_PlayerInfo;
	}

	// 타겟과의 거리가 2번인자의 Legnth보다 가깝게 있는지 판단
	bool GetIsRangeInTarget(AActor* _Target, float _Length);

	// 타겟의 방향을 얻어옴
	FVector GetTargetDir(AActor* _Target);

	FVector GetTargetDir(const FVector& _TargetPos);

	// 타겟의 방향값을 정규화한 값
	FVector GetTargetDirNormalize(AActor* _Target);

	FVector GetTargetDirNormalize(const FVector& _TargetPos);

	// 타겟의 방향으로 이동
	void SetTargetMovementInput(AActor* _Target, float Value = 1.f);

	// 인자로 들어온 방향으로 이동
	void SetDirMovementInput(const FVector& _Dir, float Value = 1.f);

	// 타겟을 바라보도록 설정
	void SetTargetLook(AActor* _Target);

	// 인자로 들어온 방향을 바라보도록 설정
	void SetDirLook(const FVector& _Dir);
	
	template<typename T>
	T* TargetSearch(FName _Name, float _Range = -1.f)
	{
		return Cast<T>(_Name, _Range);
	}

	AActor* TargetSearch(FName _Name, float _Range = -1.f);

	TArray<AActor*> TargetsSearch(FName _Name, float _Range = -1.f);

	UFUNCTION(BlueprintCallable, Category = UR)
	virtual void CallDamage(double _Damage, AActor* _Actor = nullptr, bool _IsKnockBack = true);

	UFUNCTION(BlueprintCallable, Category = UR)
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

	void ItemDrop(const TArray<const struct FURItemData*>& _Array);

	float GetLastPathPointToTargetDis(const FVector& _TargetPos);

	UNavigationPath* PathFind(AActor* _Actor);

	UNavigationPath* PathFind(const FVector& _TargetPosition);

	bool PathMove();

	void SetPath(UNavigationPath* _Path, bool _Debug/* = false*/);

	void ResetPath();

	FORCEINLINE class UNavigationPath* GetPath()
	{
		return m_Path;
	}


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

	// 네비게이션 경로 정보를 저장하는 변수
	UNavigationPath* m_Path;

protected:
	struct FURPlayerDataInfo* m_PlayerInfo;

	EHitType m_HitType;

	EHitDir m_HitDir;
	// 막기 (워리어 전용인데 HP계산을 부모인 URCharacter에서 하기때문에 여기서 변수설정
	bool m_IsBlocking;

	bool m_IsInvincibility;
	bool m_IsKnockDown;

	bool m_IsAttack;

	double m_HP;
	double m_MaxHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = User, meta = (AllowPrivateAccess = "true"))
		float m_HPPercent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = User, meta = (AllowPrivateAccess = "true"))
		float m_MPPercent;

	double m_MP;

	float m_Stamina;

	// Skill coll
	float m_QSkillCurCollTime;
	float m_ESkillCurCollTime;
	float m_RSkillCurCollTime;

	int m_QSkillMaxCollTime;
	int m_ESkillMaxCollTime;
	int m_RSkillMaxCollTime;

	float m_KnockBackHitPower;
	float m_KnockDownHitPower;


protected:
	void HitDirJudge(AActor* _Actor);

public:
	virtual void CameraShake(CameraShake_Type _Type) {};

};
