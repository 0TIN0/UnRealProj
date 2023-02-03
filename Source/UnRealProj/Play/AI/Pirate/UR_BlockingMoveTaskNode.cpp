// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Pirate/UR_BlockingMoveTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Monster.h"
#include "../../WarriorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UUR_BlockingMoveTaskNode::UUR_BlockingMoveTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_BlockingMoveTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AMonster* Monster = Controller->GetPawn<AMonster>();
	
	AURCharacter* Player = Monster->GetWorld()->GetFirstPlayerController()->GetPawn<AURCharacter>();

	// 스페로우의 HP가 0보다 크다면 패스한다.
	if (Monster->GetHPPercent() > 0.2f || Monster->IsDeath())
	{
		return EBTNodeResult::Succeeded;
	}

	Monster->SetIsBlocking(true);

	if (Monster->GetCharacterMovement()->MaxWalkSpeed != 300)
	{
		Monster->GetCharacterMovement()->MaxWalkSpeed = 300.f;
	}

	FVector MonsterPos = Monster->GetActorLocation();
	FVector PlayerPos = Player->GetActorLocation();
	FVector MonsterDir = MonsterPos - PlayerPos;
	MonsterDir = MonsterDir.GetSafeNormal();

	// 내적을 통해 코사인세타 값을 구한다음
	double FValue = FVector::DotProduct(MonsterDir, Player->GetActorForwardVector());
	double BValue = FVector::DotProduct(MonsterDir, -Player->GetActorForwardVector());
	double LValue = FVector::DotProduct(MonsterDir, -Player->GetActorRightVector());
	double RValue = FVector::DotProduct(MonsterDir, Player->GetActorRightVector());

	// 아크코사인과 라디안 투 디그리를 이용해서 디그리의 각도로 변환하여
	// 어느위치에서 공격했는지를 판단한다.
	float FConvert = acosf(static_cast<float>(FValue));
	FConvert = FMath::RadiansToDegrees(FConvert);
	float BConvert = acosf(static_cast<float>(BValue));
	BConvert = FMath::RadiansToDegrees(BConvert);
	float LConvert = acosf(static_cast<float>(LValue));
	LConvert = FMath::RadiansToDegrees(LConvert);
	float RConvert = acosf(static_cast<float>(RValue));
	RConvert = FMath::RadiansToDegrees(RConvert);

	if (FConvert < 60.f)
	{
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
	
	FVector LeftPos = Player->GetActorLocation() - Player->GetActorRightVector() * 300.f;
	FVector RightPos = Player->GetActorLocation() + Player->GetActorRightVector() * 300.f;
	FVector BackwardPos = Player->GetActorLocation() - Player->GetActorForwardVector() * 300.f;

	if (nullptr != Monster->GetPath())
	{
		if (false == Monster->NoAnimPathMove())
		{
			Monster->ResetPath();
			return EBTNodeResult::InProgress;
		}

		if (100.0f <= Monster->GetLastPathPointToTargetDis(Player->GetActorLocation()))
		{
			Monster->ResetPath();
			return EBTNodeResult::InProgress;
		}
	}

	double Dist = INT_MAX;
	double PrevDist = 0.0;

	// 가장 가까운 거리를 탐색한다.
	Dist = std::min(Dist, (LeftPos - MonsterPos).Length());

	// 둘이 다르다면 가까운위치로 갱신된것
	if (static_cast<int>(PrevDist) != static_cast<int>(Dist))
	{
		m_Type = PathPos_Type::Left;
	}
	PrevDist = Dist;

	Dist = std::min(Dist, (RightPos - MonsterPos).Length());

	if (static_cast<int>(PrevDist) != static_cast<int>(Dist))
	{
		m_Type = PathPos_Type::Right;
	}
	PrevDist = Dist;
	Dist = std::min(Dist, (BackwardPos - MonsterPos).Length());

	if (static_cast<int>(PrevDist) != static_cast<int>(Dist))
	{
		m_Type = PathPos_Type::Backward;
	}

	UNavigationPath* FindPath = nullptr;

	double Value = 0.0;

	FVector MonsterForward = Monster->GetActorForwardVector();
	FVector MonsterUp = FVector(0.0, 0.0, 1.0);
	FVector AVec;

	// 가장 가까운 위치를 넣어주어 Path를 뽑아낸다.
	switch (m_Type)
	{
	case PathPos_Type::Left:
	{
		FindPath = Monster->PathFind(LeftPos);
		AVec = (LeftPos - MonsterPos).GetSafeNormal();
		Value = MonsterUp.Dot(FVector::CrossProduct(AVec, MonsterForward));
	}
		break;
	case PathPos_Type::Right:
	{
		FindPath = Monster->PathFind(RightPos);
		AVec = (RightPos - MonsterPos).GetSafeNormal();
		Value = MonsterUp.Dot(FVector::CrossProduct(AVec, MonsterForward));
	}
		break;
	case PathPos_Type::Backward:
	{
		FindPath = Monster->PathFind(BackwardPos);
		AVec = (BackwardPos - MonsterPos).GetSafeNormal();
		Value = MonsterUp.Dot(FVector::CrossProduct(AVec, MonsterForward));
	}
		break;
	}


	if (nullptr != FindPath && false == FindPath->PathPoints.IsEmpty())
	{
		Monster->SetPath(FindPath, false);
		Monster->NoAnimPathMove();
		Monster->SetTargetLook(Player);
		if (Value > 0.0)
		{
			Monster->GetAnimationInstance()->ChangeAnimMontage(PirateAnimation::BlockWalkRight);
		}
		else
		{
			Monster->GetAnimationInstance()->ChangeAnimMontage(PirateAnimation::BlockWalkLeft);
		}

		return EBTNodeResult::InProgress;
	}


	return EBTNodeResult::InProgress;
}

void UUR_BlockingMoveTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
