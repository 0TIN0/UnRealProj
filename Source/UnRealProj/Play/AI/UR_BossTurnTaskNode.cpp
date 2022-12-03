// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_BossTurnTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../UR_BossMonster.h"
#include "Play/Controller/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"

UUR_BossTurnTaskNode::UUR_BossTurnTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_BossTurnTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_BossMonster>();

	UAnimMontage* FindMontage = m_Boss->GetAnimationInstance()->GetAnimation(BossAnimation::Spawn);
	if (m_Boss->GetAnimationInstance()->Montage_IsPlaying(FindMontage))
	{
		return EBTNodeResult::Failed;
	}

	const FURMonsterDataInfo* MonsterInfo = m_Boss->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (!Target)
	{
		return EBTNodeResult::Succeeded;
	}

	const BossAnimation Anim = BossAnimation::Skill1;

	if (!m_Boss->FindBossAnimMontage(Anim))
	{
		return EBTNodeResult::Succeeded;
	}


	AActor* TargetActor = Cast<AActor>(Target);

	//FVector Dir = TargetActor->GetActorLocation() - m_Boss->GetActorLocation();

	//if (m_Boss->GetTargetDir(TargetActor).Size() < MonsterInfo->SkillRange)
	//{
	//	//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
	//	return EBTNodeResult::Failed;
	//}


	m_Boss->SetTargetLook(TargetActor);
	m_Boss->SetTargetMovementInput(TargetActor);
	//m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);

	//FVector Dir = TargetActor->GetActorLocation() - m_Boss->GetActorLocation();

	//if (m_Boss->GetTargetDir(TargetActor).Size() < MonsterInfo->SkillRange)
	//{
	//	//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
	//	return EBTNodeResult::Failed;
	//}
	auto forwardVect = m_Boss->GetActorForwardVector();    // forward บคลอ
	FVector A = (TargetActor->GetActorLocation() - m_Boss->GetActorLocation());                   // A บคลอ
	A.Normalize();

	float dot = FVector::DotProduct(forwardVect, A);
	float angle = FMath::RadiansToDegrees(FMath::Acos(dot));

	if (angle > -5 || angle < 5)
	{
		return EBTNodeResult::Succeeded;
	}
	//m_Boss->SetTargetLook(TargetActor);
	//m_Boss->SetTargetMovementInput(TargetActor);


	return EBTNodeResult::Type::InProgress;
}

void UUR_BossTurnTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
