// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_KhaimeraProjectile.h"
#include "../../WarriorCharacter.h"
#include "../../URCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GamePlayStatics.h"

AUR_KhaimeraProjectile::AUR_KhaimeraProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Trace(TEXT("NiagaraSystem'/Game/Resource/Play/Effect/BossTrail/FX_Boss_Trail.FX_Boss_Trail'"));

	m_NiagaraFX = Trace.Object;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_Projectile = CreateDefaultSubobject<UNiagaraComponent>(FName(TEXT("NiagaraKhaimeraProjectile")));
	m_Projectile->SetAsset(m_NiagaraFX);
	m_Projectile->SetupAttachment(RootComponent);

	{
		static ConstructorHelpers::FObjectFinder<USoundBase> SpawnSound(TEXT("SoundWave'/Game/Resource/Play/Sound/SKill/Khaimera/Khaimera_TrailAttack_Sound.Khaimera_TrailAttack_Sound'"));

		if (SpawnSound.Succeeded())
			m_SpawnSound = SpawnSound.Object;

		static ConstructorHelpers::FObjectFinder<USoundBase> HitSound(TEXT("SoundWave'/Game/Resource/Play/Sound/SKill/Kwang/SP_ShadowHit_Sound.SP_ShadowHit_Sound'"));

		if (HitSound.Succeeded())
			m_HitSound = HitSound.Object;
	}
}

void AUR_KhaimeraProjectile::BeginPlay()
{
	Super::BeginPlay();

	// 위치기반 사운드
	if (m_SpawnSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_SpawnSound, RootComponent->GetComponentLocation(), 0.3f, 1.f);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("KhaimeraProjectile_Sound Null!"));
	}
}

void AUR_KhaimeraProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
