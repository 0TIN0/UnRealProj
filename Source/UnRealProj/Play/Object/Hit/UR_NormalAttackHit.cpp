// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Object/Hit/UR_NormalAttackHit.h"

AUR_NormalAttackHit::AUR_NormalAttackHit()
{
	PrimaryActorTick.bCanEverTick = true;

	m_ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("NormalHitParticles"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/ParagonKhaimera/FX/ParticleSystems/Abilities/Primary/FX/P_Khaimera_LMB_Impact.P_Khaimera_LMB_Impact'"));
	//ParticleSystem'/Game/ParagonKhaimera/FX/ParticleSystems/Abilities/Ultimate/FX/P_Ult_Impact_DMG.P_Ult_Impact_DMG'
	if (ParticleSystem.Succeeded())
	{
		m_ParticleComponent->SetTemplate(ParticleSystem.Object);
	}

	m_ParticleComponent->SetWorldScale3D(FVector(3.0, 3.0, 3.0));
}

void AUR_NormalAttackHit::BeginPlay()
{
	Super::BeginPlay();
}

void AUR_NormalAttackHit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}
