// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_MoveTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "Play/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"

EBTNodeResult::Type UUR_MoveTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Controller->GetPawn<AMonster>();
	const FURMonsterDataInfo* MonsterInfo = Monster->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (!Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	FVector Dir = TargetActor->GetActorLocation() - Monster->GetActorLocation();

	if (Dir.Size() < MonsterInfo->AttRange)
	{
		Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
		return EBTNodeResult::Failed;
	}

	Dir.Z = 0.0f;
	float DeltaTime = TargetActor->GetWorld()->GetDeltaSeconds();


	Dir.Normalize();

	Monster->SetActorRotation(Dir.Rotation());
	Monster->AddMovementInput(Dir, 1000.0f);

	//UPawnMovementComponent* MovementComponent = Monster->GetMovementComponent();
	//MovementComponent->AddInputVector(WorldDirection * ScaleValue, bForce);
	// Monster->AddActorWorldOffset(Dir * MonsterInfo->Speed * DeltaTime);
	Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);


	return EBTNodeResult::Type::Succeeded;
}
