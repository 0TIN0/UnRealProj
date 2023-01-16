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
	RunLeft UMETA(DisplayName = "왼쪽 달리기"),
	RunRight  UMETA(DisplayName = "오른쪽 달리기"),
	RunForward UMETA(DisplayName = "앞 달리기"),
	RunBackWard UMETA(DisplayName = "뒤 달리기"),
	Attack UMETA(DisplayName = "공격모션"),
	Hit UMETA(DisplayName = "히트모션"),
	Skill1 UMETA(DisplayName = "SkillQ"),
	Skill2 UMETA(DisplayName = "SkillE"),
	Skill3 UMETA(DisplayName = "SkillR"),
	Teleport UMETA(DisplayName = "Teleport"),
	Jump UMETA(DisplayName = "Jump"),
	Max UMETA(DisplayName = "최대치")
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

	QuestProgress m_QuestProgress;
	float m_Stamina;

	bool m_IsMoveing;

	bool m_IsRun;

	// Key 입력
	bool m_IsForwardDown;
	bool m_IsBackwardDown;
	bool m_IsLeftDown;
	bool m_IsRightDown;
	bool m_IsQSkillAttacking;
	bool m_IsESkillAttacking;
	bool m_IsRSkillAttacking;


	double m_SkillQConsumedMP;
	double m_SkillEConsumedMP;
	double m_SkillRConsumedMP;

	// 마우스 dpi
	float m_MouseXDPI;
	float m_MouseYDPI;


	float m_MoveSpeed;

	float m_TeleportDist;

	// 퀘스트 몬스터 잡았을때 증가
	int m_MonsterCount;

	bool m_IsQuesting;
	bool m_IsQuestCompletion;


	// Skill
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>	m_SpawnActorClass;

	class APlayerController* m_PlayerController;

public:
	APlayCharacter();

	UFUNCTION(BlueprintCallable, Category = RealUn)
		void MouseMoveX(float Value);

	UFUNCTION(BlueprintCallable, Category = RealUn)
		void MouseMoveY(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerPickingMove();

	UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerLeftMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerRightMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerForwardMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
		void PlayerBackwardMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
		void WheelKey(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
		void LeftAttack();

	UFUNCTION(BlueprintCallable, Category = UR)
		void SkillQ();

	UFUNCTION(BlueprintCallable, Category = UR)
		void SkillE();

	UFUNCTION(BlueprintCallable, Category = UR)
		void SkillR();

	UFUNCTION(BlueprintCallable, Category = UR)
		void ForwardKeyEnd();

	UFUNCTION(BlueprintCallable, Category = UR)
		void BackwardKeyEnd();

	UFUNCTION(BlueprintCallable, Category = UR)
		void LeftKeyEnd();

	UFUNCTION(BlueprintCallable, Category = UR)
		void RightKeyEnd();

	UFUNCTION(BlueprintCallable, Category = UR)
		void CtrlKeyDown();

	UFUNCTION(BlueprintCallable, Category = UR)
		void CtrlKeyOn();

	UFUNCTION(BlueprintCallable, Category = UR)
		void ShiftKeyDown();

	UFUNCTION(BlueprintCallable, Category = UR)
		void ShiftKeyOn();

	void DamageOn(bool _IsKnockBack = true) override;

	UFUNCTION(BlueprintCallable, Category = UR)
		FORCEINLINE void SetESkillEnable(bool _WSkillEnable)
	{
		m_IsESkillAttacking = _WSkillEnable;
	}

	void SetIsMoving(bool _Enable)
	{
		m_IsMoveing = _Enable;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
	int GetMonsterCount()
	{
		return m_MonsterCount;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		void SetMonsterCount(int MonsterCount)
	{
		m_MonsterCount = MonsterCount;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		bool GetIsQuesting()
	{
		return m_IsQuesting;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		void SetIsQuesting(bool IsQuesting)
	{
		m_IsQuesting = IsQuesting;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		bool GetIsQuestCompletion()
	{
		return m_IsQuestCompletion;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
	void SetQuestCompletion(bool Completion)
	{
		m_IsQuestCompletion = Completion;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		QuestProgress GetQuestProgress()
	{
		return m_QuestProgress;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		void SetQuestProgress(QuestProgress Progress)
	{
		m_QuestProgress = Progress;
	}
	void AddMonsterCount()
	{
		m_MonsterCount += 1;
	}

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void NotifyActorEndOverlap(AActor* OtherActor) override;

protected:

	void CallDamage(double _Damage, AActor* _Actor = nullptr, bool _IsKnockBack = true, bool _IsCameraShake = true) override;





private:
	void SetDefaultData();
	// 텔레포트 어떤 방향으로 할지 판단하는 함수
	void TeleportToJudge();
	void CoolTimeTick(float DeltaTime);

protected:
	virtual void Jump();
	virtual void StopJumping();

};
