// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_FloorToAirAnimNotifyState.h"
#include "../WarriorCharacter.h"

void UUR_FloorToAirAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AWarriorCharacter* Player = MeshComp->GetOwner<AWarriorCharacter>();

	if (!Player || !Player->IsValidLowLevel())
	{
		return;
	}

	FVector EndVec = FVector(0.0, 0.0, 1.0);
	EndVec *= 1400.f;

	for (auto& Target : Player->GetUltimateTarget())
	{
		Target->LaunchCharacter(EndVec, true, true);
	}

	EndVec.Z += 400.f;

	Player->LaunchCharacter(EndVec, true, true);
}
