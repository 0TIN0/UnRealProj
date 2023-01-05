// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Object/UR_UltimateShockWave.h"

// Sets default values
AUR_UltimateShockWave::AUR_UltimateShockWave() :
	m_DestroyTime(1.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShockWaveParticles"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/ParagonLtBelica/FX/Particles/Belica/Abilities/ManaBomb/FX/P_ManaBombGround.P_ManaBombGround'"));

	if (ParticleSystem.Succeeded())
	{
		m_ParticleComponent->SetTemplate(ParticleSystem.Object);
	}

	m_ParticleComponent->SetWorldScale3D(FVector(2.0, 2.0, 2.0));
}

// Called when the game starts or when spawned
void AUR_UltimateShockWave::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_UltimateShockWave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DestroyTime -= DeltaTime;

	if (m_DestroyTime <= 0.f)
	{
		Destroy();
	}

}

