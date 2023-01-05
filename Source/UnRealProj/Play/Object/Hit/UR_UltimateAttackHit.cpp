// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Object/Hit/UR_UltimateAttackHit.h"

AUR_UltimateAttackHit::AUR_UltimateAttackHit()
{

	m_ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("UltimateHitParticles"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/ParagonKhaimera/FX/ParticleSystems/Abilities/Ultimate/FX/P_Ult_Impact_DMG.P_Ult_Impact_DMG'"));

	if (ParticleSystem.Succeeded())
	{
		m_ParticleComponent->SetTemplate(ParticleSystem.Object);
	}

	m_ParticleComponent->SetWorldScale3D(FVector(3.0, 3.0, 3.0));
}

void AUR_UltimateAttackHit::BeginPlay()
{
	Super::BeginPlay();
}

void AUR_UltimateAttackHit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
