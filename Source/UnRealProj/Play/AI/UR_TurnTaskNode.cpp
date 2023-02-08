// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_TurnTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../URCharacter.h"
#include "Play/Controller/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UUR_TurnTaskNode::UUR_TurnTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_TurnTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	m_Monster = m_Controller->GetPawn<AURCharacter>();

	if (m_Monster->IsDeath())
	{
		return EBTNodeResult::Failed;
	}

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

	FVector ForwardDir = m_Monster->GetActorForwardVector();    // forward 벡터
	FVector TargetDir = (TargetActor->GetActorLocation() - m_Monster->GetActorLocation());                   // Target 벡터
	TargetDir = TargetDir.GetSafeNormal();
	FVector UpDir = ForwardDir.Cross(m_Monster->GetActorRightVector());	// Up 벡터


	float Dot = FVector::DotProduct(ForwardDir, TargetDir);
	float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));
	FVector CrossPrdt = FVector::CrossProduct(ForwardDir, TargetDir);

	float Delta = GetWorld()->DeltaTimeSeconds;
	float YawDelta = 0;
	if (CrossPrdt.Z < -0.08f)
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

	YawDelta *= 5.f;
	FRotator DeltaRotation = FRotator(0, YawDelta, 0);   //Yaw

	// 각도가 클 수록 빠르게 회전을 하게된다.
	m_Monster->AddActorWorldRotation(DeltaRotation);

	return EBTNodeResult::Type::InProgress;
}

void UUR_TurnTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_TurnTaskNode::AnimMontageJudge()
{
	if (m_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		m_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		m_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		m_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		m_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop) ||
		m_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown) ||
		m_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::GetUp))
	{
		return true;
	}

	return false;
}
