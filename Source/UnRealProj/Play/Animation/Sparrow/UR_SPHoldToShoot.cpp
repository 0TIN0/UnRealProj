// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/Sparrow/UR_SPHoldToShoot.h"
#include "../../Boss/UR_SparrowSubBoss.h"

void UUR_SPHoldToShoot::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AUR_SparrowSubBoss* Boss = MeshComp->GetOwner<AUR_SparrowSubBoss>();

	if (!Boss || !Boss->IsValidLowLevel())
	{
		return;
	}

	switch (Boss->GetRandAttackNumb())
	{
	case SparrowAttack_Type::Attack1:
	case SparrowAttack_Type::Attack2:
		Boss->GetAnimationInstance()->ChangeAnimMontage(SparrowBossAnimation::SP4End);
		break;
	case SparrowAttack_Type::Attack3:
		Boss->GetAnimationInstance()->ChangeAnimMontage(SparrowBossAnimation::SP5End);
		break;
	}
}
