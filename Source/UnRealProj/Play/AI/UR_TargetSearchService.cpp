// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_TargetSearchService.h"
#include "Play/URAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Global/URStructs.h"

UUR_TargetSearchService::UUR_TargetSearchService()
{
	// 노드의 이름을 지정
	NodeName = TEXT("TargetSearch");
	// 틱 간격을 조절하는 녀석
	Interval = 0.f;
}

void UUR_TargetSearchService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Controller->GetPawn<AMonster>();

	float FindRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat("FindRange");

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (nullptr == Target)
	{
		Target = Monster->TargetSearch(FName(TEXT("Player")), FindRange);

		if (UURBlueprintFunctionLibrary::IsDebug())
		{
			DrawDebugSphere(GetWorld(), Controller->GetPawn()->GetActorLocation(), FindRange, 50, FColor::Red, false, Interval);
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), Target);
	}
	else
	{
		AActor* TargetActor = Cast<AActor>(Target);

		if (FindRange < (TargetActor->GetActorLocation() - Monster->GetActorLocation()).Size())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), nullptr);
		}
	}
}
