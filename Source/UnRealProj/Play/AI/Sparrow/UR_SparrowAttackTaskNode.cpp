// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Sparrow/UR_SparrowAttackTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../WarriorCharacter.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_SparrowSubBoss.h"
#include "Global/URStructs.h"

UUR_SparrowAttackTaskNode::UUR_SparrowAttackTaskNode()	:
	m_Enable(false)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_SparrowAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_SparrowSubBoss>();

	if (!m_Player)
		m_Player = m_Boss->GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();


	const FURMonsterDataInfo* KhaimeraInfo = m_Boss->GetSparrowData();

	// ���� ���° ���������� �Ǵ����ش�.
	int AttackNumb = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("RandAttackNumb"));

	/*
	1�� : �⺻ ��¡ ����
	2�� : ��¡ ���� SP2 End;
	3�� : ��¡ ���� SP2 End;
	4�� : ��¡ ���� SP2 End;
	5�� : ��¡ ���� SP2 End;
	*/

	// 4�����ݺ��� ���� �����̶�°��� ���� �ڼ����� �Ѿ���Ѵٴ� �ǹ��̴�.
	if (AttackNumb > 4)
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

	if (!m_Enable)
	{
		m_Enable = true;
		m_Boss->AttackOn();
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(SparrowBossAnimation::SPShootStart);
	}

	if (m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::SP1) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::SP2End) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::SP3End) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::SP4End) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::SP5End) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::SPShootStart) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::SPShootHold) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::SPShootEnd) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::BurstShoot))
	{
		return EBTNodeResult::InProgress;
	}

	m_Enable = false;

	return EBTNodeResult::Succeeded;
}

void UUR_SparrowAttackTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_SparrowAttackTaskNode::AnimMontageJudge()
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
