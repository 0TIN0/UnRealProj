// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraMoveTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"

UUR_KhaimeraMoveTaskNode::UUR_KhaimeraMoveTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_KhaimeraMoveTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_KhaimeraBoss>();

	if (AnimMontageJudge(m_Boss))
	{
		return EBTNodeResult::Failed;
	}

	const FURMonsterDataInfo* MonsterInfo = m_Boss->GetKhaimeraData();

	int AttackNumb = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("RandAttackNumb"));

	// 3번보다 높은 공격들은 전부 멀리 있어도 동작되는 스킬들이기 때문에
	// 해당 번호의 값이라면 MoveTaskNode를 실패하도록 해야함
	if (AttackNumb > 4)
	{
		UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

		if (!Target)
		{
			return EBTNodeResult::Succeeded;
		}

		AActor* TargetActor = Cast<AActor>(Target);

		FVector Dir = TargetActor->GetActorLocation() - m_Boss->GetActorLocation();

		if (m_Boss->GetTargetDir(TargetActor).Size() < MonsterInfo->SkillRange)
		{
			//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
			return EBTNodeResult::Failed;
		}


		m_Boss->SetTargetLook(TargetActor);
		m_Boss->SetTargetMovementInput(TargetActor);
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);


		return EBTNodeResult::Type::InProgress;
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (!Target)
	{
		return EBTNodeResult::Succeeded;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	FVector Dir = TargetActor->GetActorLocation() - m_Boss->GetActorLocation();

	if (!m_Boss->GetIsBerserk())
	{
		if (m_Boss->GetTargetDir(TargetActor).Size() < MonsterInfo->AttRange)
		{
			//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		if (m_Boss->GetTargetDir(TargetActor).Size() < MonsterInfo->SkillRange)
		{
			//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
			return EBTNodeResult::Failed;
		}
	}
	FVector ForwardDir = m_Boss->GetActorForwardVector();    // forward 벡터
	FVector TargetDir = (TargetActor->GetActorLocation() - m_Boss->GetActorLocation());                   // Target 벡터
	TargetDir = TargetDir.GetSafeNormal();
	FVector UpDir = ForwardDir.Cross(m_Boss->GetActorRightVector());	// Up 벡터
	float dot = FVector::DotProduct(ForwardDir, TargetDir);
	float angle = FMath::RadiansToDegrees(FMath::Acos(dot));
	FVector crossPrdt = FVector::CrossProduct(ForwardDir, TargetDir);

	float delta = GetWorld()->DeltaTimeSeconds;
	float yawDelta = 0;
	if (crossPrdt.Z < -0.05f)
	{
		yawDelta = angle * delta * -1;
	}
	else if (crossPrdt.Z > 0.05f)
	{
		yawDelta = angle * delta;
	}
	yawDelta *= 2.f;
	FRotator deltaRotation = FRotator(0, yawDelta, 0);   //Yaw

	// 각도가 클 수록 빠르게 회전을 하게된다.
	m_Boss->AddActorWorldRotation(deltaRotation);

	//m_Boss->SetTargetLook(TargetActor);
	m_Boss->SetTargetMovementInput(TargetActor);
	m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);


	return EBTNodeResult::Type::InProgress;
}

void UUR_KhaimeraMoveTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_KhaimeraMoveTaskNode::AnimMontageJudge(AUR_KhaimeraBoss* _Monster)
{
	if (_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack1) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack2) || 
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack3) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack1Recovery) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack2Recovery) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack3Recovery) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardFastComboAttack) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashStart) || 
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashAttack) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::BerserkStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::RushAttackStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::RushAttack) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::GetUp))
	{
		return true;
	}

	return false;
}
