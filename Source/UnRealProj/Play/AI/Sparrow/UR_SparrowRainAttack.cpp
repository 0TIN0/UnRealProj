// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Sparrow/UR_SparrowRainAttack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../WarriorCharacter.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_SparrowSubBoss.h"

UUR_SparrowRainAttack::UUR_SparrowRainAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_SparrowRainAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_SparrowSubBoss>();

	if (!m_Player)
		m_Player = m_Boss->GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();


	const FURMonsterDataInfo* KhaimeraInfo = m_Boss->GetSparrowData();

	// 먼저 몇번째 공격인지를 판단해준다.
	int AttackNumb = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("RandAttackNumb"));

	/*
	* 5번 : Rain Charging Shoot = 1번 기 모아서 공중으로 화살을 날린다 (데칼로 위치를 나타낸후 해당 위치로 공중에서 화살이 떨어지는 형태)
	* 6번 : Rain Burst Shoot = 3번 연달아서 공중 공격을 함 (데칼로 위치를 나타낸후 해당 위치로 공중에서 화살이 떨어지는 형태)
	*/

	// 4번공격보다 높은 공격이라는것은 다음 자손으로 넘어가야한다는 의미이다.
	if (AttackNumb < 5 || AttackNumb > 6)
	{
		return EBTNodeResult::Succeeded;
	}

	if (AnimMontageJudge())
	{
		return EBTNodeResult::Succeeded;
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	FVector ForwardDir = m_Boss->GetActorForwardVector();    // forward 벡터
	FVector TargetDir = (TargetActor->GetActorLocation() - m_Boss->GetActorLocation());                   // Target 벡터
	TargetDir = TargetDir.GetSafeNormal();
	FVector UpDir = ForwardDir.Cross(m_Boss->GetActorRightVector());	// Up 벡터


	float Dot = FVector::DotProduct(ForwardDir, TargetDir);
	float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));
	FVector CrossPrdt = FVector::CrossProduct(ForwardDir, TargetDir);

	float Delta = GetWorld()->DeltaTimeSeconds;
	float YawDelta = 0;
	if (CrossPrdt.Z < 0.f)
	{
		YawDelta = Angle * Delta * -1;
	}
	else if (CrossPrdt.Z > 0.08f)
	{
		YawDelta = Angle * Delta;
	}

	YawDelta *= 10.f;
	FRotator DeltaRotation = FRotator(0, YawDelta, 0);   //Yaw

	// 각도가 클 수록 빠르게 회전을 하게된다.
	m_Boss->AddActorWorldRotation(DeltaRotation);

	if (!m_Enable)
	{
		m_Enable = true;
		m_Boss->AttackOn();
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(SparrowBossAnimation::RainShootStart);
	}

	if (m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::RainShootAndEnd) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::RainShootBurst) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::RainShootHold) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::RainShootStart))
	{
		return EBTNodeResult::InProgress;
	}

	m_Enable = false;

	return EBTNodeResult::Succeeded;
}

void UUR_SparrowRainAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_SparrowRainAttack::AnimMontageJudge()
{
	if (m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::GetUp))
	{
		return true;
	}

	return false;
}
