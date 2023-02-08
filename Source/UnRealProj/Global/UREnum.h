// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UREnum.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUREnum : public UObject
{
	GENERATED_BODY()

};

UENUM(BlueprintType)
enum class UPLAYER_TYPE : uint8
{
	Default UMETA(DisplayName = "선택x"),
	Wizard UMETA(DisplayName = "마법사"),
	Warrior UMETA(DisplayName = "전사")
};

UENUM(BlueprintType)
enum class UMONSTER_TYPE : uint8
{
	Default UMETA(DisplayName = "선택x"),
	Pirate UMETA(DisplayName = "해적"),
	Khaimera UMETA(DisplayhName = "카이메라"),
	Sparrow UMETA(DisplayhName = "스페로우")
};

UENUM(BlueprintType)
enum class EHitType : uint8
{
	Default UMETA(DisplayName = "선택x"),
	NormalHit UMETA(DisplayName = "피격"),
	KnockDownHit UMETA(DisplayName = "넉다운 피격")
};

UENUM(BlueprintType)
enum class EHitDir : uint8
{
	Default UMETA(DisplayName = "디폴트"),
	Forward UMETA(DisplayName = "정면 히트"),
	Backward UMETA(DisplayName = "후면 히트"),
	Left UMETA(DisplayName = "왼쪽 히트"),
	Right UMETA(DisplayName = "오른쪽 히트"),
};


UENUM(BlueprintType)
enum class DefaultAnimation : uint8
{
	// 1100 
	Default UMETA(DisplayName = "애니메이션 지정안됨"),
	Idle UMETA(DisplayName = "서있는 모션"),
	Left UMETA(DisplayName = "왼쪽"),
	Right  UMETA(DisplayName = "오른쪽"),
	Forward UMETA(DisplayName = "앞"),
	BackWard UMETA(DisplayName = "뒤"),
	Attack UMETA(DisplayName = "공격모션"),
	ForwardHit UMETA(DisplayName = "정면 히트모션"),
	BackwardHit UMETA(DisplayName = "후면 히트모션"),
	LeftHit UMETA(DisplayName = "왼쪽 히트모션"),
	RightHit UMETA(DisplayName = "오른쪽 히트모션"),
	HitAirLoop UMETA(DisplayName = "공중 히트 루프모션"),
	HitAirToFloorStart UMETA(DisplayName = "공중 to 바닥 시작"),
	HitAirToFloorEnd UMETA(DisplayName = "공중 to 바닥 끝"),
	KnockDown UMETA(DisplayName = "넉다운"),
	DeathStart UMETA(DisplayName = "사망 시작"),
	DeathLoop UMETA(DisplayName = "사망 루프"),
	GetUp UMETA(DisplayName = "일어나기"),
	ExecutionTarget UMETA(DisplayName = "처형 타겟"),
	Max UMETA(DisplayName = "최대치"),
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
	SkillQ UMETA(DisplayName = "SkillQ"),
	SkillEStart UMETA(DisplayName = "SkillE시작"),
	SkillELoop UMETA(DisplayName = "SkillE루프"),
	SkillEEnd UMETA(DisplayName = "SkillE끝"),
	SkillRStart UMETA(DisplayName = "SkillRStart"),
	SkillRLoop UMETA(DisplayName = "SkillRLoop"),
	SkillREnd UMETA(DisplayName = "SkillREnd"),
	SkillRAttack UMETA(DisplayName = "SkillRAttack"),
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
	CommandDashAttack UMETA(DisplayName = "대쉬어택"),
	Execution1 UMETA(DisplayName = "처형1"),
	Execution2 UMETA(DisplayName = "처형2"),
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

UENUM(BlueprintType)
enum class WarriorHitAnimation : uint8
{
	Default UMETA(DisplayName = "디폴트"),
	HitLeft = static_cast<uint8>(WarriorJumpAnimation::Max) UMETA(DisplayName = "피격 왼"),
	HitRight UMETA(DisplayName = "피격 오"),
	HitForward UMETA(DisplayName = "피격 앞"),
	HitBackward UMETA(DisplayName = "피격 뒤"),
	CombatHitLeft UMETA(DisplayName = "전투 피격 왼"),
	CombatHitRight UMETA(DisplayName = "전투 피격 오"),
	CombatHitForward UMETA(DisplayName = "전투 피격 앞"),
	CombatHitBackward UMETA(DisplayName = "전투 피격 뒤"),
	HitLargeLeft UMETA(DisplayName = "큰 피격 왼"),
	HitLargeRight UMETA(DisplayName = "큰 피격 오"),
	HitLargeForward UMETA(DisplayName = "큰 피격 앞"),
	HitLargeBackward UMETA(DisplayName = "큰 피격 뒤"),
	CombatHitLargeLeft UMETA(DisplayName = "전투 큰 피격 왼"),
	CombatHitLargeRight UMETA(DisplayName = "전투 큰 피격 오"),
	CombatHitLargeForward UMETA(DisplayName = "전투 큰 피격 앞"),
	CombatHitLargeBackward UMETA(DisplayName = "전투 큰 피격 뒤"),
	HitLargeToFallDown UMETA(DisplayName = "큰 피격 후 넘어짐"),
	CombatHitLargeToFallDown UMETA(DisplayName = "전투 큰 피격 후 넘어짐"),
	Dead UMETA(DisplayName = "사망"),
	CombatDead UMETA(DisplayName = "전투시 사망"),
	GetUp UMETA(DisplayName = "일어나는 동작"),
	CombatGetUp UMETA(DisplayName = "전투시 일어나는 동작"),
	Max UMETA(DisplayName = "최대치")
};

UENUM(BlueprintType)
enum class WarriorBlockAnimation : uint8
{
	Default UMETA(DisplayName = "디폴트"),
	BlockHit = static_cast<uint8>(WarriorHitAnimation::Max) UMETA(DisplayName = "피격 막기"),
	BlockHitBreak UMETA(DisplayName = "피격 막기 부러짐"),
	BlockStart UMETA(DisplayName = "막기시작"),
	BlockEnd UMETA(DisplayName = "막기 끝"),
	BlockLoop UMETA(DisplayName = "막기 루프"),
	BlockWalkStartLeft UMETA(DisplayName = "막기 걷기 시작 왼"),
	BlockWalkStartRight UMETA(DisplayName = "막기 걷기 시작 오"),
	BlockWalkStartForward UMETA(DisplayName = "막기 걷기 시작 앞"),
	BlockWalkStartBackward UMETA(DisplayName = "막기 걷기 시작 뒤"),
	BlockWalkStartLF UMETA(DisplayName = "막기 걷기 시작 왼앞"),
	BlockWalkStartRF UMETA(DisplayName = "막기 걷기 시작 우앞"),
	BlockWalkStartLB UMETA(DisplayName = "막기 걷기 시작 왼뒤"),
	BlockWalkStartRB UMETA(DisplayName = "막기 걷기 시작 우뒤"),
	BlockWalkLoopLeft UMETA(DisplayName = "막기 걷기 반복 왼"),
	BlockWalkLoopRight UMETA(DisplayName = "막기 걷기 반복 우"),
	BlockWalkLoopForward UMETA(DisplayName = "막기 걷기 반복 앞"),
	BlockWalkLoopBackward UMETA(DisplayName = "막기 걷기 반복 뒤"),
	BlockWalkLoopLF UMETA(DisplayName = "막기 걷기 반복 왼앞"),
	BlockWalkLoopRF UMETA(DisplayName = "막기 걷기 반복 우앞"),
	BlockWalkLoopLB UMETA(DisplayName = "막기 걷기 반복 왼뒤"),
	BlockWalkLoopRB UMETA(DisplayName = "막기 걷기 반복 우뒤"),
	BlockWalkStopLeft UMETA(DisplayName = "막기 걷기 멈춤 왼"),
	BlockWalkStopRight UMETA(DisplayName = "막기 걷기 멈춤 우"),
	BlockWalkStopForward UMETA(DisplayName = "막기 걷기 멈춤 앞"),
	BlockWalkStopBackward UMETA(DisplayName = "막기 걷기 멈춤 뒤"),
	BlockWalkStopLF UMETA(DisplayName = "막기 걷기 멈춤 왼앞"),
	BlockWalkStopRF UMETA(DisplayName = "막기 걷기 멈춤 우앞"),
	BlockWalkStopLB UMETA(DisplayName = "막기 걷기 멈춤 왼뒤"),
	BlockWalkStopRB UMETA(DisplayName = "막기 걷기 멈춤 우뒤"),
	Max UMETA(DisplayName = "최대치")
};

UENUM(BlueprintType)
enum class PirateAnimation : uint8
{
	Default UMETA(DisplayName = "디폴트"),
	CombatIdle = static_cast<uint8>(DefaultAnimation::Max) UMETA(DisplayName = "전투 Idle"),
	CombatIdleToIdle UMETA(DisplayName = "전투 Idle To Idle"),
	IdleToCombatIdle UMETA(DisplayName = "Idle To 전투 Idle"),
	CombatWalkForward UMETA(DisplayName = "전투 앞 걷기"),
	CombatWalkBackward UMETA(DisplayName = "전투 뒤 걷기"),
	CombatRunForward UMETA(DisplayName = "전투 앞 달리기"),
	CombatRunBackWard UMETA(DisplayName = "전투 뒤 달리기"),
	AttackCombo1 UMETA(DisplayName = "콤보1"),
	AttackCombo2 UMETA(DisplayName = "콤보2"),
	IdleToBlock UMETA(DisplayName = "Idle To 막기"),
	BlockToIdle UMETA(DisplayName = "막기 To Idle"),
	BlockLoop UMETA(DisplayName = "막기 루프"),
	BlockHit UMETA(DisplayName = "막기 상태 히트"),
	BlockHitBreak UMETA(DisplayName = "막기 상태 깨짐"),
	BlockWalkForward UMETA(DisplayName = "막기 상태 앞으로 걷기"),
	BlockWalkBackward UMETA(DisplayName = "막기 상태 뒤로 걷기"),
	BlockWalkLeft UMETA(DisplayName = "막기 상태 왼쪽 걷기"),
	BlockWalkRight UMETA(DisplayName = "막기 상태 오른쪽 걷기"),
	Max UMETA(DisplayName = "최대치")
};


UENUM(BlueprintType)
enum class ContentsItemType : uint8
{
	// 사용x
	Default UMETA(DisplayName = "사용x"),
	// 겹칠 수 없는 아이템
	Equip UMETA(DisplayName = "장비"),
	// 겹칠 수 있는 아이템
	Consumable UMETA(DisPlayName = "소비")
};

UENUM(BlueprintType)
enum class QuestProgress : uint8
{
	Default UMETA(DisplayName = "디폴트"),
	FirstStageMonster UMETA(DisplayName = "1Stage 몬스터"),
	FirstStageBoss UMETA(DisplayName = "1Stage 보스"),
	SecondStageMonster UMETA(DisplayName = "2Stage 몬스터"),
	SecondStageBoss UMETA(DisplayName = "2Stage 보스"),
};


UENUM(BlueprintType)
enum class CameraShake_Type : uint8
{
	Default UMETA(DisplayName = "디폴트"),
	HitShake UMETA(DisplayName = "히트 카메라 쉐이크"),
	UltimateShake UMETA(DisplayName = "궁극기 카메라 쉐이크"),
	BigShake UMETA(DisplayName = "강력한 카메라 쉐이크")
};

UENUM(BlueprintType)
enum class KhaimeraAttack : uint8
{
	Default,
	Attack1,
	Attack2,
	Attack3,
	Combo1,
	FastCombo,
	DashAttack,
	RushAttack,
	Max
};

UENUM(BlueprintType)
enum class SparrowAttack_Type : uint8
{
	Default,
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	RainBowShoot,
	RainBowBurstShoot,
	Max
};

UENUM(BlueprintType)
enum class PirateAttack_Type : uint8
{
	Default,
	Attack,
	AttackCombo1,
	AttackCombo2,
	Max
};
