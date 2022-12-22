// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_BossMoveTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Boss/UR_BossMonster.h"
#include "../Boss/UR_KrakenBoss.h"
#include "Play/Controller/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"

UUR_BossMoveTaskNode::UUR_BossMoveTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_BossMoveTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AUR_BossMonster* Boss = Controller->GetPawn<AUR_BossMonster>();

	if (Boss)
	{
		const FURMonsterDataInfo* MonsterInfo = Boss->GetMonsterData();

		UAnimMontage* FindMontage = Boss->GetAnimationInstance()->GetAnimation(BossAnimation::Spawn);
		if (Boss->GetAnimationInstance()->Montage_IsPlaying(FindMontage))
		{
			return EBTNodeResult::Failed;
		}

		UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

		if (!Target)
		{
			return EBTNodeResult::Succeeded;
		}

		AActor* TargetActor = Cast<AActor>(Target);

		FVector Dir = TargetActor->GetActorLocation() - Boss->GetActorLocation();

		if (Boss->GetTargetDir(TargetActor).Size() < MonsterInfo->SkillRange)
		{
			//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
			return EBTNodeResult::Failed;
		}


		Boss->SetTargetLook(TargetActor);
		Boss->SetTargetMovementInput(TargetActor);
		Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);


		return EBTNodeResult::Type::InProgress;
	}
	else
	{
		AUR_KrakenBoss* Kraken = Controller->GetPawn<AUR_KrakenBoss>();

		if (Kraken)
		{
			const FURMonsterDataInfo* MonsterInfo = Kraken->GetKrakenData();

			UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

			if (!Target)
			{
				return EBTNodeResult::Succeeded;
			}

			AActor* TargetActor = Cast<AActor>(Target);

			FVector Dir = TargetActor->GetActorLocation() - Kraken->GetActorLocation();

			if (Kraken->GetTargetDir(TargetActor).Size() < MonsterInfo->AttRange)
			{
				//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
				return EBTNodeResult::Failed;
			}

			FVector ForwardDir = Kraken->GetActorForwardVector();    // forward 벡터
			FVector TargetDir = (TargetActor->GetActorLocation() - Kraken->GetActorLocation());                   // Target 벡터
			TargetDir = TargetDir.GetSafeNormal();
			FVector UpDir = ForwardDir.Cross(Kraken->GetActorRightVector());	// Up 벡터
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
			Kraken->AddActorWorldRotation(deltaRotation);

			//Kraken->SetTargetLook(TargetActor);
			Kraken->SetTargetMovementInput(TargetActor);
			Kraken->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);


			return EBTNodeResult::Type::InProgress;
		}
	}
	return EBTNodeResult::Type::Failed;
}

void UUR_BossMoveTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
