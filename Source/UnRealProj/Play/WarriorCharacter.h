// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/URCharacter.h"
#include "Global/UREnum.h"
#include "Components/TimelineComponent.h"
#include "WarriorCharacter.generated.h"

enum class EWarriorComboType
{
	Default,
	ComboA,
	ComboB,
	ComboC
};

enum class EWarriorJumpType
{
	Default,
	Forward,
	Backward,
	Left,
	Right,
	Max
};

UENUM(BlueprintType)
enum class WarriorAnimation : uint8
{
	Default UMETA(DisplayName = "디폴트"),
	ForWardLeft = static_cast<uint8>(DefaultAnimation::Max) UMETA(DisplayName = "왼쪽 앞 대각선"),
	ForWardRight UMETA(DisplayName = "오른쪽 앞 대각선"),
	BackWardLeft UMETA(DisplayName = "왼쪽 뒤 대각선"),
	BackWardRight UMETA(DisplayName = "오른쪽 뒤 대각선"),
	RunLeft UMETA(DisplayName = "왼쪽 달리기"),
	RunRight  UMETA(DisplayName = "오른쪽 달리기"),
	RunForward UMETA(DisplayName = "앞 달리기"),
	RunBackward UMETA(DisplayName = "뒤 달리기"),
	RunForwardLeft UMETA(DisplayName = "왼쪽 앞 대각선 달리기"),
	RunForwardRight UMETA(DisplayName = "오른쪽 앞 대각선 달리기"),
	RunBackwardLeft UMETA(DisplayName = "왼쪽 뒤 대각선 달리기"),
	RunBackwardRight UMETA(DisplayName = "오른쪽 뒤 대각선 달리기"),
	DashLeft UMETA(DisplayName = "왼쪽 대쉬"),
	DashRight UMETA(DisplayName = "오른쪽 대쉬"),
	DashForward UMETA(DisplayName = "앞 대쉬"),
	DashBackward UMETA(DisplayName = "뒤 대쉬"),
	DashForwardLeft UMETA(DisplayName = "왼쪽 앞 대쉬"),
	DashForwardRight UMETA(DisplayName = "오른쪽 앞 대쉬"),
	DashBackwardLeft UMETA(DisplayName = "왼쪽 뒤 대쉬"),
	DashBackwardRight UMETA(DisplayName = "오른쪽 뒤 대쉬"),
	Attack UMETA(DisplayName = "공격모션"),
	Hit UMETA(DisplayName = "히트모션"),
	Skill1 UMETA(DisplayName = "SkillQ"),
	Skill2 UMETA(DisplayName = "SkillE"),
	Skill3 UMETA(DisplayName = "SkillR"),
	Jump UMETA(DisplayName = "Jump"),
	ComboA1 UMETA(DisplayName = "A콤보1"),
	ComboA2 UMETA(DisplayName = "A콤보2"),
	ComboA3 UMETA(DisplayName = "A콤보3"),
	ComboB1 UMETA(DisplayName = "B콤보1"),
	ComboB2 UMETA(DisplayName = "B콤보2"),
	ComboB3 UMETA(DisplayName = "B콤보3"),
	ComboB4 UMETA(DisplayName = "B콤보4"),
	ComboC1 UMETA(DisplayName = "C콤보1"),
	ComboC2 UMETA(DisplayName = "C콤보2"),
	ComboC3 UMETA(DisplayName = "C콤보3"),
	ComboC4 UMETA(DisplayName = "C콤보4"),
	Max UMETA(DisplayName = "최대치")
};

UENUM(BlueprintType)
enum class WarriorCombatAnimation : uint8
{
	Default UMETA(DisplayName = "디폴트"), 
	CombatIdle = static_cast<uint8>(WarriorAnimation::Max) UMETA(DisplayName = "전투 Idle"),
	CombatIdleToIdle UMETA(DisplayName = "전투 Idle To Idle"),
	IdleToCombatIdle UMETA(DisplayName = "Idle To 전투 Idle"),
	CombatWalkLeft UMETA(DisplayName = "전투 왼쪽 걷기"),
	CombatWalkRight  UMETA(DisplayName = "전투 오른쪽 걷기"),
	CombatWalkForward UMETA(DisplayName = "전투 앞 걷기"),
	CombatWalkBackWard UMETA(DisplayName = "전투 뒤 걷기"),
	CombatWalkForWardLeft UMETA(DisplayName = "전투 왼 앞 대각선 걷기"),
	CombatWalkForWardRight UMETA(DisplayName = "전투 오 앞 대각선 걷기"),
	CombatWalkBackWardLeft UMETA(DisplayName = "전투 왼 뒤 대각선 걷기"),
	CombatWalkBackWardRight UMETA(DisplayName = "전투 오 뒤 대각선 걷기"),
	CombatRunLeft UMETA(DisplayName = "전투 왼쪽 달리기"),
	CombatRunRight  UMETA(DisplayName = "전투 오른쪽 달리기"),
	CombatRunForward UMETA(DisplayName = "전투 앞 달리기"),
	CombatRunBackWard UMETA(DisplayName = "전투 뒤 달리기"),
	CombatRunForWardLeft UMETA(DisplayName = "전투 왼 앞 대각선 달리기"),
	CombatRunForWardRight UMETA(DisplayName = "전투 오 앞 대각선 달리기"),
	CombatRunBackWardLeft UMETA(DisplayName = "전투 왼 뒤 대각선 달리기"),
	CombatRunBackWardRight UMETA(DisplayName = "전투 오 뒤 대각선 달리기"),
	CombatDashLeft UMETA(DisplayName = "전투 왼쪽 대쉬"),
	CombatDashRight UMETA(DisplayName = "전투 오른쪽 대쉬"),
	CombatDashForward UMETA(DisplayName = "전투 앞 대쉬"),
	CombatDashBackward UMETA(DisplayName = "전투 뒤 대쉬"),
	CombatDashForwardLeft UMETA(DisplayName = "전투 왼쪽 앞 대쉬"),
	CombatDashForwardRight UMETA(DisplayName = "전투 오른쪽 앞 대쉬"),
	CombatDashBackwardLeft UMETA(DisplayName = "전투 왼쪽 뒤 대쉬"),
	CombatDashBackwardRight UMETA(DisplayName = "전투 오른쪽 뒤 대쉬"),
	Max UMETA(DisplayName = "최대치")
};

UENUM(BlueprintType)
enum class WarriorJumpAnimation : uint8
{
	Default UMETA(DisplayName = "디폴트"),
	JumpStartLeft = static_cast<uint8>(WarriorCombatAnimation::Max) UMETA(DisplayName = "점프 시작 왼"),
	JumpStartRight UMETA(DisplayName = "점프 시작 오"),
	JumpStartForward UMETA(DisplayName = "점프 시작 앞"),
	JumpStartBackward UMETA(DisplayName = "점프 시작 뒤"),
	JumpLoop UMETA(DisplayName = "점프 루프"),
	JumpEndLeft UMETA(DisplayName = "점프 끝 왼"),
	JumpEndRight UMETA(DisplayName = "점프 끝 오"),
	JumpEndForward UMETA(DisplayName = "점프 끝 앞"),
	JumpEndBackward UMETA(DisplayName = "점프 끝 뒤"),
	JumpCombatStartLeft  UMETA(DisplayName = "전투 상태 점프 시작 왼"),
	JumpCombatStartRight UMETA(DisplayName = "전투 상태 점프 시작 오"),
	JumpCombatStartForward UMETA(DisplayName = "전투 상태 점프 시작 앞"),
	JumpCombatStartBackward UMETA(DisplayName = "전투 상태 점프 시작 뒤"),
	JumpCombatLoop UMETA(DisplayName = "전투 상태 점프 루프"),
	JumpCombatEndLeft UMETA(DisplayName = "전투 상태 점프 끝 왼"),
	JumpCombatEndRight UMETA(DisplayName = "전투 상태 점프 끝 오"),
	JumpCombatEndForward UMETA(DisplayName = "전투 상태 점프 끝 앞"),
	JumpCombatEndBackward UMETA(DisplayName = "전투 상태 점프 끝 뒤"),
	Max UMETA(DisplayName = "최대치")
};

UCLASS()
class UNREALPROJ_API AWarriorCharacter : public AURCharacter
{
	GENERATED_BODY()
public:
	AWarriorCharacter();

private:
	FRandomStream m_Stream;

	FTimerHandle m_TimerHandle;

	// 기본이외의 동작들
	UPROPERTY(Category = "PlayerAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<WarriorAnimation, UAnimMontage*> m_PlayerAnimations;

	// 전투상태시의 동작들
	UPROPERTY(Category = "PlayerAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<WarriorCombatAnimation, UAnimMontage*> m_PlayerCombatAnimations;

	// 점프시의 동작들
	UPROPERTY(Category = "PlayerAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<WarriorJumpAnimation, UAnimMontage*> m_PlayerJumpAnimations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* m_CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* m_CameraSpringArmComponent;

	class APlayerController* m_PlayerController;

	class UAnimMontage* m_CombatIdleMontage;

	QuestProgress m_QuestProgress;

	EWarriorComboType m_ComboType;

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

	bool m_IsComboAttack;

	// 전투상태
	bool m_IsCombating;
	float m_CombatTime;

	double m_SkillQConsumedMP;
	double m_SkillEConsumedMP;
	double m_SkillRConsumedMP;

	// 마우스 dpi
	float m_MouseXDPI;
	float m_MouseYDPI;


	float m_MoveSpeed;

	float m_DashDist;

	// 퀘스트 몬스터 잡았을때 증가
	int m_MonsterCount;

	bool m_IsQuesting;
	bool m_IsQuestCompletion;

	// 대쉬
	FVector m_DashDir;
	FVector m_DashVelocity;

	bool m_OnDash;

	// 점프
	bool m_IsJump;
	EWarriorJumpType m_JumpType;



public:
	void ResetDash()
	{
		m_OnDash = false;
	}

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
		void LeftAttackUp();

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

	void DamageOn() override;

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

	UFUNCTION(BlueprintCallable, Category = UR)
		bool GetIsComboAttack()
	{
		return m_IsComboAttack;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		void SetIsComboAttack(bool IsComboAttack)
	{
		m_IsComboAttack = IsComboAttack;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		bool GetIsCombating()
	{
		return m_IsCombating;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		void SetIsCombating(bool IsCombating)
	{
		m_IsCombating = IsCombating;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		bool GetIsJumping()
	{
		return m_IsJump;
	}

	UFUNCTION(BlueprintCallable, Category = UR)
		void SetIsJumping(bool IsJump)
	{
		m_IsJump = IsJump;
	}


	void AddMonsterCount()
	{
		m_MonsterCount += 1;
	}

	bool GetForwardDown()	const
	{
		return m_IsForwardDown;
	}
	bool GetBackwardDown()	const
	{
		return m_IsBackwardDown;
	}
	bool GetLeftDown()	const
	{
		return m_IsLeftDown;
	}
	bool GetRightDown()	const
	{
		return m_IsRightDown;
	}

	bool GetCtrlDown()	const
	{
		return m_IsRun;
	}

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Jump() override;
	void StopJumping() override;

protected:

	void CallDamage(double _Damage, AActor* _Actor = nullptr) override;





private:
	void SetDefaultData();
	// 텔레포트 어떤 방향으로 할지 판단하는 함수
	void DashToJudge();
	void CombatTick(float DeltaTime);
	void CoolTimeTick(float DeltaTime);
	bool JudgeFunc();
	bool DashJudgeFunc();
	void StopDashing();

	void DashFunc(const FVector& DashDir, const FVector& DashVelocity);

	void TurnFunc();

	void JumpTrace();




	
protected:
	UPROPERTY()
		UTimelineComponent* MyTimeline;

	UPROPERTY()
		UCurveFloat* FloatCurve;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UFUNCTION()
		void TimelineCallback(float val);

	UFUNCTION()
		void TimelineFinishedCallback();

	void PlayTimeline();
};
