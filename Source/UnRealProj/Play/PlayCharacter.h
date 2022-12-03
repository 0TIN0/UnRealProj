// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "URCharacter.h"
#include "PlayCharacter.generated.h"

UENUM(BlueprintType)
enum class PlayerAnimationEx : uint8
{
	// 1100 
	Default UMETA(DisplayName = "애니메이션 지정안됨"),
	Idle UMETA(DisplayName = "서있는 모션"),
	Left UMETA(DisplayName = "왼쪽"),
	Right  UMETA(DisplayName = "오른쪽"),
	Forward UMETA(DisplayName = "앞"),
	BackWard UMETA(DisplayName = "뒤"),
	Attack UMETA(DisplayName = "공격모션"),
	Hit UMETA(DisplayName = "히트모션"),
	Max UMETA(DisplayName = "최대치"),
	Skill1 UMETA(DisplayName = "SkillQ"),
	Skill2 UMETA(DisplayName = "SkillW"),
	Skill3 UMETA(DisplayName = "SkillE")
};

UCLASS()
class UNREALPROJ_API APlayCharacter : public AURCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = "PlayerAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<PlayerAnimationEx, UAnimMontage*> m_PlayerAnimations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* m_CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_CameraSpringArmComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* m_ElevatorCamera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_ElevatorArmComponent;

	struct FURPlayerDataInfo* m_PlayerInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = User, meta = (AllowPrivateAccess = "true"))
	double m_HPPercent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = User, meta = (AllowPrivateAccess = "true"))
	double m_MPPercent;

	double m_MP;

	bool m_IsMoveing;

	bool m_IsSkillW;

	double m_SkillQConsumedMP;
	double m_SkillWConsumedMP;


	// Skill
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>	m_SpawnActorClass;

	class APlayerController* m_PlayerController;

public:
	APlayCharacter();

	UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerPickingMove();

	/*UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerLeftMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerRightMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerForwardMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerBackwardMove(float Value);*/

	UFUNCTION(BlueprintCallable, Category = UR)
		void LeftAttack();

	UFUNCTION(BlueprintCallable, Category = UR)
		void SkillQ();

	UFUNCTION(BlueprintCallable, Category = UR)
		void SkillW();

	UFUNCTION(BlueprintCallable, Category = UR)
		void MoveKeyEnd();

	void DamageOn() override;

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
		FORCEINLINE double GetMPPercent()
	{
		return m_MPPercent;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		FORCEINLINE void SetSkillWEnable(bool _WSkillEnable)
	{
		m_IsSkillW = _WSkillEnable;
	}

	void SetIsMoving(bool _Enable)
	{
		m_IsMoveing = _Enable;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		double GetMaxHP();

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void NotifyActorEndOverlap(AActor* OtherActor) override;

protected:

	void CallDamage(double _Damage, AActor* _Actor = nullptr) override;

};
