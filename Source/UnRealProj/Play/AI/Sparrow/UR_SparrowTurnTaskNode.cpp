// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Sparrow/UR_SparrowTurnTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Boss/UR_SparrowSubBoss.h"
#include "Play/Controller/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UUR_SparrowTurnTaskNode::UUR_SparrowTurnTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_SparrowTurnTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	m_Boss = m_Controller->GetPawn<AUR_SparrowSubBoss>();


	const FURMonsterDataInfo* MonsterInfo = m_Boss->GetSparrowData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (!Target)
	{
		return EBTNodeResult::Failed;
	}

	if (AnimMontageJudge())
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	//if (m_Boss->GetTargetDir(TargetActor).Size() < MonsterInfo->AttRange)
	//{
	//	//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
	//	return EBTNodeResult::Succeeded;
	//}

	//m_KrakenBoss->SetTargetLook(TargetActor);
	//m_KrakenBoss->SetTargetMovementInput(TargetActor);

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
	else
	{
		return EBTNodeResult::Type::Succeeded;
	}

	YawDelta *= 10.f;
	FRotator DeltaRotation = FRotator(0, YawDelta, 0);   //Yaw

	// 각도가 클 수록 빠르게 회전을 하게된다.
	m_Boss->AddActorWorldRotation(DeltaRotation);

	return EBTNodeResult::Type::InProgress;
}

void UUR_SparrowTurnTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_SparrowTurnTaskNode::AnimMontageJudge()
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
