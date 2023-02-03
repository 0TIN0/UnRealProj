// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_PlayerStepNotify.h"

UUR_PlayerStepNotify::UUR_PlayerStepNotify()
{
}

FString UUR_PlayerStepNotify::GetNotifyName_Implementation() const
{
	Super::GetNotifyName_Implementation();

	return FString();
}


void UUR_PlayerStepNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
}

void UUR_PlayerStepNotify::ValidateAssociatedAssets()
{
	Super::ValidateAssociatedAssets();
}
