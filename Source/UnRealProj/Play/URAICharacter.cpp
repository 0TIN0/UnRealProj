// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/URAICharacter.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

AURAICharacter::AURAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::Spawned;
}
