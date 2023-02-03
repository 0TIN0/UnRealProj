// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_SparrowTargeting.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AUR_SparrowTargeting::AUR_SparrowTargeting()	:
	m_DestroyTime(1.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> TargetParticleSystem(TEXT("ParticleSystem'/Game/ParagonWraith/FX/Particles/Abilities/ScopedShot/FX/P_Wraith_Sniper_Targeting_Holo.P_Wraith_Sniper_Targeting_Holo'"));

	m_TargetingFX = TargetParticleSystem.Object;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_TargetingComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("ParticleTarget")));
	m_TargetingComponent->SetupAttachment(RootComponent);
	//m_TargetingComponent->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
	m_TargetingComponent->SetWorldScale3D(FVector(13.0, 13.0, 13.0));

	if (TargetParticleSystem.Succeeded())
	{
		m_TargetingComponent->SetTemplate(m_TargetingFX);
	}
}

// Called when the game starts or when spawned
void AUR_SparrowTargeting::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_SparrowTargeting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DestroyTime -= DeltaTime;

	if (m_DestroyTime <= 0.f)
	{
		Destroy();
	}
}

