// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_SparrowMeteor.h"
#include "../../WarriorCharacter.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AUR_SparrowMeteor::AUR_SparrowMeteor() :
	m_HitEnable(false),
	m_DestroyTime(1.5f)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCollisionComponent()->SetWorldScale3D(FVector(5.0, 5.0, 5.0));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Meteor/FX/P_Gideon_Meteor_Portal_DumpTruck.P_Gideon_Meteor_Portal_DumpTruck'"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitParticleSystem(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Meteor/FX/P_Gideon_MeteorBigImpact.P_Gideon_MeteorBigImpact'"));

	m_MeteorFX = ParticleSystem.Object;
	m_HitParticleFX = HitParticleSystem.Object;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_MeteorComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("MeteorParticle")));
	m_MeteorComponent->SetupAttachment(RootComponent);
	m_MeteorComponent->SetRelativeLocation(RootComponent->GetComponentLocation() + FVector(0.0, 0.0, 0.f));
	m_MeteorComponent->SetWorldScale3D(FVector(0.2, 0.2, 0.2));

	if (ParticleSystem.Succeeded())
	{
		m_MeteorComponent->SetTemplate(m_MeteorFX);
	}

	//m_SkillDir = FVector(0.0, 0.0, 1.0);
	GetProjectileMovementComponent()->ProjectileGravityScale = 20.f;
}

void AUR_SparrowMeteor::BeginPlay()
{
	Super::BeginPlay();
}

void AUR_SparrowMeteor::Tick(float DeltaTime)
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
	else
	{
		m_DestroyTime -= DeltaTime;

		if (m_DestroyTime <= 0.f)
		{
			Destroy();
		}
	}
}

void AUR_SparrowMeteor::OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result)
{
	AWarriorCharacter* Chracter = Cast<AWarriorCharacter>(_DestActor);

	if (nullptr == Chracter)
	{
		return;
	}

	Chracter->SetHitType(EHitType::KnockDownHit);

	Chracter->CameraShake(CameraShake_Type::BigShake);

	// 부모에서 CallDamage를 하기떄문에 그 전에 히트 방식을 미리 설정해준다.

	Super::OnCollision(_Component, _DestActor, _DestComponent, _OtherBodyIndex, _FromSweep, _Result);

	m_HitEnable = true;

	m_SkillDir = FVector(0.0, 0.0, 0.0);

	m_MeteorComponent->SetTemplate(m_HitParticleFX);
}
