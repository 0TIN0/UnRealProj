// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/Sparrow/UR_RainShootStartChange.h"
#include "../../Boss/UR_SparrowSubBoss.h"

void UUR_RainShootStartChange::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AUR_SparrowSubBoss* Boss = MeshComp->GetOwner<AUR_SparrowSubBoss>();

	if (!Boss || !Boss->IsValidLowLevel())
	{
		return;
	}
	
	switch (Boss->GetRandAttackNumb())
	{
	case SparrowAttack_Type::RainBowShoot:
		Boss->GetAnimationInstance()->ChangeAnimMontage(SparrowBossAnimation::RainShootHold);
		break;
	case SparrowAttack_Type::RainBowBurstShoot:
		Boss->GetAnimationInstance()->ChangeAnimMontage(SparrowBossAnimation::RainShootBurst);
		break;
	}
}
