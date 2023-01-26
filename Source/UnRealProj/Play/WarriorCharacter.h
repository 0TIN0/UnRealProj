// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/URCharacter.h"
#include "Components/TimelineComponent.h"
#include "Global/URStructs.h"
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

	// 피격시의 동작들
	UPROPERTY(Category = "PlayerAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<WarriorHitAnimation, UAnimMontage*> m_PlayerHitAnimations;

	// 막기 동작들
	UPROPERTY(Category = "PlayerAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<WarriorBlockAnimation, UAnimMontage*> m_PlayerBlockAnimations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* m_CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* m_CameraSpringArmComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UPostProcessComponent* m_PostProcessComponent;

	FWeightedBlendable m_WeightedBlend;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TMap<CameraShake_Type, TSubclassOf<class UMatineeCameraShake>> m_CameraShakeMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Collision, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class USphereComponent> m_DamageCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Material, meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInterface*> m_ArrayNormalMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Material, meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInterface*> m_ArrayRimLightMat;

	class APlayerController* m_PlayerController;

	UPROPERTY(EditAnywhere, Category = "Firing")
	class UNiagaraSystem* m_ShieldEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UNiagaraComponent* m_Shield;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UNiagaraComponent* m_BlackHoleNiagara;

	class AUR_GlowEffectActor* m_GlowSphere;

	class UNiagaraSystem* m_BlackHoleFX;

	class AActor* m_BlackHoleActor;

	AActor* m_MonsterActor;

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
	bool m_IsQSkill;
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

	// 커맨드 판단
	//FURWarriorCommand m_Command;
	//TQueue<char> m_qCommand;
	//float m_qCommandTime;

	// 광폭화 공속관련
	float m_AttackSpeed;

	// 궁극기 관련
	TArray<AURCharacter*> m_UltimateTargetMonster;
	int m_UltimateAttackCount;
	int m_UltimateTargetCount;
	double m_PrevZ;
	bool m_IsUltimateAttack;
	FRotator m_CameraComponentDefaultRot;
	AURCharacter* m_UltimateCameraTarget;


	// 포스트프로세스 제거 관련
	float m_PostProcessDeleteTime;


	float m_TestTime;


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
		void RightBlock();

	UFUNCTION(BlueprintCallable, Category = UR)
		void RightBlockUp();

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
	void DamageOff() override;

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

	int GetUltimateAttackCount()	const
	{
		return m_UltimateAttackCount;
	}

	AActor* GetMotionWarpingActor()	const
	{
		return m_MonsterActor;
	}

	void SetMotionWarpingActor(AActor* _Actor)
	{
		m_MonsterActor = _Actor;
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

	bool GetIsQSkill()	const
	{
		return m_IsQSkill;
	}

	double GetIsPrevZ()	const
	{
		return m_PrevZ;
	}

	void SetIsInvincibility(bool _Enable)
	{
		m_IsInvincibility = _Enable;
	}

	TArray<AURCharacter*> GetUltimateTarget()
	{
		return m_UltimateTargetMonster;
	}

	void SetIsUltimateAttack(bool _Enable)
	{
		m_IsUltimateAttack = _Enable;
	}

	void SetBlackHole(AActor*_BlackHoleActor)
	{
		m_BlackHoleActor = _BlackHoleActor;
	}

	class UNiagaraComponent* GetBlackHoleBodyComponent()
	{
		return m_BlackHoleNiagara;
	}

	class AUR_GlowEffectActor* GetGlowEffect()
	{
		return m_GlowSphere;
	}

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Jump() override;
	void StopJumping() override;

protected:

	void CallDamage(double _Damage, AActor* _Actor = nullptr, bool _IsKnockBack = true, bool _IsCameraShake = true) override;





private:
	void CommandStructInit();
	void SetDefaultData();
	// 텔레포트 어떤 방향으로 할지 판단하는 함수
	void DashToJudge();
	void CombatTick(float DeltaTime);
	void CoolTimeTick(float DeltaTime);
	bool FirstJudgeFunc();
	bool JudgeFunc();
	bool DashJudgeFunc();
	void StopDashing();

	void DashFunc(const FVector& DashDir, const FVector& DashVelocity);

	void TurnFunc();

	void JumpTrace();

	// 커맨드 시간 판단
	void CommandTimeJudge(float DeltaTime);

	void HitAnimMontageJudge();
	void HitAnimation(bool IsLarge, bool IsKncokDown = false);

	void BlockStaminaTick(float DeltaTime);

	TArray<AActor*> CheckAttackTarget(const TArray<FHitResult>& _HitResult);

	void SetBerserkRateScale();

	void TickPostProcessDeleteFunc(float DeltaTime);

	void DestroyBlockObj();

	
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

public:
	void TraceAttackMonster();

	TArray<AURCharacter*> GetSphereTraceHitActor(float _MinMax, float _Radius, ECollisionChannel _CollisionChannel = ECollisionChannel::ECC_GameTraceChannel2);

	void UltimateAttack();

	void Finished();
	void AdvanceTimer();


	AActor* GetTargetActor();

	void CameraShake(CameraShake_Type _Type) override;

	void AddPostProcessDrunkMat();
	void DeletePostProcessDrunkMat();

	template <typename T>
	void CreateParticleObject(AActor* _Actor)
	{
		FActorSpawnParameters spawnParams;
		FVector vecSpawnPos = _Actor->GetActorLocation();
		FTransform SpawnTransform = FTransform(vecSpawnPos);

		GetWorld()->SpawnActor<T>(T::StaticClass(), SpawnTransform, spawnParams);
	}

	template <typename T>
	T* GetCreateParticleObject(AActor* _Actor)
	{
		FActorSpawnParameters spawnParams;
		FVector vecSpawnPos = _Actor->GetActorLocation();
		FTransform SpawnTransform = FTransform(vecSpawnPos);

		return GetWorld()->SpawnActor<T>(T::StaticClass(), SpawnTransform, spawnParams);
	}
};
