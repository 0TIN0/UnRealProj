// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_ExecutionTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "../Controller/URAIController.h"
#include "../WarriorCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UUR_ExecutionTaskNode::UUR_ExecutionTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_ExecutionTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AURCharacter* Boss = Controller->GetPawn<AURCharacter>();

	AWarriorCharacter* Player = Boss->GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();

	if (Boss->IsDeath())
	{
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = Player;
		LatentInfo.ExecutionFunction = FName("Finished");
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = 0;

		UKismetSystemLibrary::MoveComponentTo(Player->GetRootComponent(), Player->GetActorLocation(), Player->GetActorRotation(),
			false, false, 0.1f, true, EMoveComponentAction::Type::Move, LatentInfo);

		Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::Execution1);
		Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::ExecutionTarget);

		FVector Forward = Boss->GetActorForwardVector();

		FVector BossNewPos = Player->GetActorLocation() + Player->GetActorForwardVector() * 150.f;

		Boss->SetActorLocation(BossNewPos);

		FVector BossNewDir = (Player->GetActorLocation() - Boss->GetActorLocation()).GetSafeNormal();

		Boss->SetActorRotation(BossNewDir.Rotation());

		Player->GetController();
		Player->DisableInput(Player->GetController<APlayerController>());
		Player->GetCameraSpringArmComponent()->bInheritYaw = true;



		return EBTNodeResult::Succeeded;
		
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UUR_ExecutionTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
