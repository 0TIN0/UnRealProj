// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_BossTurnTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Boss/UR_BossMonster.h"
#include "../Boss/UR_KrakenBoss.h"
#include "Play/Controller/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UUR_BossTurnTaskNode::UUR_BossTurnTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_BossTurnTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_LichBoss)
		m_LichBoss = m_Controller->GetPawn<AUR_BossMonster>();

	if (m_LichBoss)
	{
		UAnimMontage* FindMontage = m_LichBoss->GetAnimationInstance()->GetAnimation(BossAnimation::Spawn);
		if (m_LichBoss->GetAnimationInstance()->Montage_IsPlaying(FindMontage))
		{
			return EBTNodeResult::Failed;
		}

		const FURMonsterDataInfo* MonsterInfo = m_LichBoss->GetMonsterData();

		UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

		if (!Target)
		{
			return EBTNodeResult::Succeeded;
		}

		const BossAnimation Anim = BossAnimation::Skill1;

		if (!m_LichBoss->FindBossAnimMontage(Anim))
		{
			return EBTNodeResult::Succeeded;
		}

		AActor* TargetActor = Cast<AActor>(Target);

		m_LichBoss->SetTargetLook(TargetActor);
		m_LichBoss->SetTargetMovementInput(TargetActor);

		auto forwardVect = m_LichBoss->GetActorForwardVector();    // forward 벡터
		FVector A = (TargetActor->GetActorLocation() - m_LichBoss->GetActorLocation());                   // A 벡터
		A.Normalize();

		float dot = FVector::DotProduct(forwardVect, A);
		float angle = FMath::RadiansToDegrees(FMath::Acos(dot));

		if (angle > -5 || angle < 5)
		{
			return EBTNodeResult::Succeeded;
		}
	}
	else
	{
		m_KrakenBoss = m_Controller->GetPawn<AUR_KrakenBoss>();

		const FURMonsterDataInfo* MonsterInfo = m_KrakenBoss->GetKrakenData();

		UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

		if (!Target)
		{
			return EBTNodeResult::Succeeded;
		}

		UAnimMontage* Montage = m_KrakenBoss->GetAnimationInstance()->GetAnimation(DefaultAnimation::Attack);

		if (!m_KrakenBoss->GetAnimationInstance()->Montage_IsPlaying(Montage))
		{
		}

		AActor* TargetActor = Cast<AActor>(Target);

		if (m_KrakenBoss->GetTargetDir(TargetActor).Size() < MonsterInfo->AttRange)
		{
			//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
			return EBTNodeResult::Succeeded;
		}

		//m_KrakenBoss->SetTargetLook(TargetActor);
		//m_KrakenBoss->SetTargetMovementInput(TargetActor);

		FVector ForwardDir = m_KrakenBoss->GetActorForwardVector();    // forward 벡터
		FVector TargetDir = (TargetActor->GetActorLocation() - m_KrakenBoss->GetActorLocation());                   // Target 벡터
		TargetDir = TargetDir.GetSafeNormal();
		FVector UpDir = ForwardDir.Cross(m_KrakenBoss->GetActorRightVector());	// Up 벡터
		// 보스의 정면, 타겟, 업벡터를 이용해서 Target이 왼쪽에 있는지 오른쪽에 있는지 판단
		//float Value = GetBasisDeterminantSign(ForwardDir, TargetDir, UpDir);

		//double Value = FVector::DotProduct(UpDir,ForwardDir.Cross(TargetDir));

		//// 오른쪽
		//if (Value > 0.f)
		//{
		//	FRotator Rot = FRotator(0.f, 0.5f, 0.f);
		//	m_KrakenBoss->AddActorWorldRotation(Rot);
		//}
		//// 왼쪽
		//else if (Value < 0.f)
		//{
		//	FRotator Rot = FRotator(0.f, -0.5f, 0.f);
		//	m_KrakenBoss->AddActorWorldRotation(Rot);
		//}
		//else
		//{
		//	EBTNodeResult::Type::Succeeded;
		//}

		float Dot = FVector::DotProduct(ForwardDir, TargetDir);
		float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));
		FVector CrossPrdt = FVector::CrossProduct(ForwardDir, TargetDir);

		float Delta = GetWorld()->DeltaTimeSeconds;
		float YawDelta = 0;
		if (CrossPrdt.Z < -0.05f)
		{
			YawDelta = Angle * Delta * -1;
		}
		else if(CrossPrdt.Z > 0.05f)
		{
			YawDelta = Angle * Delta;
		}
		else
		{
			return EBTNodeResult::Type::Succeeded;
		}
		YawDelta *= 2.f;
		FRotator DeltaRotation = FRotator(0, YawDelta, 0);   //Yaw

		// 각도가 클 수록 빠르게 회전을 하게된다.
		m_KrakenBoss->AddActorWorldRotation(DeltaRotation);
	}


	return EBTNodeResult::Type::InProgress;
}

void UUR_BossTurnTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
