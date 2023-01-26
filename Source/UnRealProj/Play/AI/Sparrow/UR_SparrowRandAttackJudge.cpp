// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Sparrow/UR_SparrowRandAttackJudge.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_SparrowSubBoss.h"

UUR_SparrowRandAttackJudge::UUR_SparrowRandAttackJudge() :
	m_Stream(FRandomStream(FDateTime::Now().GetTicks()))
{
}

EBTNodeResult::Type UUR_SparrowRandAttackJudge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AUR_SparrowSubBoss* Boss = Controller->GetPawn<AUR_SparrowSubBoss>();

	// � ������ ���� �����ִ� TaskNode�̴�.
	// 1 : 
	// 2 : Charging Shoot (SP4End)
	// 3 : 
	// 4 : Burst Shoot
	// 5 : Rain Hold Shoot
	// 6 : Rain Burst Shoot
	int32 RandAttackNumb = (int32)m_Stream.FRandRange(2.0, 2.99999);

	// �������� ���� �ѹ��� �Ѱ��ش�.
	// AnimNotifyState���� �ش� ��ȣ�� ���� ������ �ٲ�� ����
	Boss->SetRandAttackNumb(RandAttackNumb);

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("RandAttackNumb"), RandAttackNumb);

	return EBTNodeResult::Failed;
}
