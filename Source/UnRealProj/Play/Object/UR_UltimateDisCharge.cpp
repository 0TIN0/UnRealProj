// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Object/UR_UltimateDisCharge.h"

// Sets default values
AUR_UltimateDisCharge::AUR_UltimateDisCharge() :
	m_DestroyTime(1.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("UltimateDisChargeParticles"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/ParagonKhaimera/FX/ParticleSystems/Abilities/Ultimate/FX/P_Khaimera_Ult_Blast.P_Khaimera_Ult_Blast'"));

	if (ParticleSystem.Succeeded())
	{
		m_ParticleComponent->SetTemplate(ParticleSystem.Object);
	}

	RootComponent = m_ParticleComponent;
}

// Called when the game starts or when spawned
void AUR_UltimateDisCharge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_UltimateDisCharge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DestroyTime -= DeltaTime;

	if (m_DestroyTime <= 0.f)
	{
		Destroy();
	}

}

