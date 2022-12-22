// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Skill/UR_AquaStorm.h"

AUR_AquaStorm::AUR_AquaStorm()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AUR_AquaStorm::BeginPlay()
{
	Super::BeginPlay();

	m_SkillDir = GetActorForwardVector();
}

void AUR_AquaStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
