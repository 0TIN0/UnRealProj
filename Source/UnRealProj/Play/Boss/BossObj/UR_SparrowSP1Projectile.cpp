// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_SparrowSP1Projectile.h"
#include "../../WarriorCharacter.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

AUR_SparrowSP1Projectile::AUR_SparrowSP1Projectile()	:
	m_HitEnable(false),
	m_DestroyTime(1.f)
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Burden/FX/P_Gideon_Burden_Projectile.P_Gideon_Burden_Projectile'"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitParticleSystem(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Burden/FX/P_Gideon_Burden_HitCharacter.P_Gideon_Burden_HitCharacter'"));

	m_ParticleFX = ParticleSystem.Object;
	m_HitParticleFX = HitParticleSystem.Object;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_ArrowTrail = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("ParticleSP1")));
	m_ArrowTrail->SetupAttachment(RootComponent);

	if (ParticleSystem.Succeeded())
	{
		m_ArrowTrail->SetTemplate(m_ParticleFX);
	}
}

void AUR_SparrowSP1Projectile::BeginPlay()
{
	Super::BeginPlay();
}

void AUR_SparrowSP1Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_HitEnable)
	{
		m_DestroyTime -= DeltaTime;

		if (m_DestroyTime <= 0.f)
		{
			Destroy();
		}
	}
}

void AUR_SparrowSP1Projectile::OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result)
{
	AURCharacter* Chracter = Cast<AURCharacter>(_DestActor);

	if (nullptr == Chracter)
	{
		return;
	}

	Chracter->SetHitType(EHitType::KnockDownHit);

	// 부모에서 CallDamage를 하기떄문에 그 전에 히트 방식을 미리 설정해준다.

	Super::OnCollision(_Component, _DestActor, _DestComponent, _OtherBodyIndex, _FromSweep, _Result);

	m_HitEnable = true;

	m_SkillDir = FVector(0.0, 0.0, 0.0);

	m_ArrowTrail->SetTemplate(m_HitParticleFX);

	//Destroy();
}
