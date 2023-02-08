// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_SparrowEvadeProjectile.h"
#include "../../WarriorCharacter.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AUR_SparrowEvadeProjectile::AUR_SparrowEvadeProjectile() :
	m_HitEnable(false),
	m_DestroyTime(1.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EvadeShoootParticleSystem(TEXT("ParticleSystem'/Game/ParagonWraith/FX/Particles/Abilities/ScopedShot/FX/P_Wraith_Sniper_Projectile.P_Wraith_Sniper_Projectile'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EvadeShoootHitParticleSystem(TEXT("ParticleSystem'/Game/ParagonWraith/FX/Particles/Abilities/ScopedShot/FX/P_Wraith_Sniper_HitCharacter.P_Wraith_Sniper_HitCharacter'"));

	m_EvadeProjectileFX = EvadeShoootParticleSystem.Object;
	m_HitParticleFX = EvadeShoootHitParticleSystem.Object;


	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_EvadeProjectileComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("ParticleSPEvadeProjectile")));
	m_EvadeProjectileComponent->SetupAttachment(RootComponent);

	if (EvadeShoootParticleSystem.Succeeded())
	{
		m_EvadeProjectileComponent->SetTemplate(m_EvadeProjectileFX);
	}

	GetCollisionComponent()->SetWorldScale3D(FVector(3.0, 3.0, 3.0));

	m_EvadeProjectileComponent->SetRelativeLocation(FVector(-190.0, 0.0, 0.0));
	//m_EvadeProjectileComponent->SetRelativeScale3D(FVector(1.0, 1.0, 1.0));

	GetProjectileMovementComponent()->ProjectileGravityScale = 0.f;

	{
		static ConstructorHelpers::FObjectFinder<USoundBase> HitSound(TEXT("SoundWave'/Game/Resource/Play/Sound/SKill/Kwang/SP_SniperHit_Sound.SP_SniperHit_Sound'"));

		if (HitSound.Succeeded())
			m_HitSound = HitSound.Object;
	}
}

// Called when the game starts or when spawned
void AUR_SparrowEvadeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_SparrowEvadeProjectile::Tick(float DeltaTime)
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

void AUR_SparrowEvadeProjectile::OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result)
{
	AURCharacter* Chracter = Cast<AURCharacter>(_DestActor);

	if (nullptr == Chracter)
	{
		return;
	}

	Chracter->SetHitType(EHitType::NormalHit);

	// 부모에서 CallDamage를 하기떄문에 그 전에 히트 방식을 미리 설정해준다.
	Super::OnCollision(_Component, _DestActor, _DestComponent, _OtherBodyIndex, _FromSweep, _Result);

	m_EvadeProjectileComponent->SetTemplate(m_HitParticleFX);

	m_HitEnable = true;
}

