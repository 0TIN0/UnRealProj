// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_KhaimeraProjectile.h"
#include "../../WarriorCharacter.h"
#include "../../URCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AUR_KhaimeraProjectile::AUR_KhaimeraProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Trace(TEXT("NiagaraSystem'/Game/Resource/Play/Effect/BossTrail/FX_Boss_Trail.FX_Boss_Trail'"));

	m_NiagaraFX = Trace.Object;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_Projectile = CreateDefaultSubobject<UNiagaraComponent>(FName(TEXT("NiagaraKhaimeraProjectile")));
	m_Projectile->SetAsset(m_NiagaraFX);
	m_Projectile->SetupAttachment(RootComponent);
}

void AUR_KhaimeraProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AUR_KhaimeraProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
