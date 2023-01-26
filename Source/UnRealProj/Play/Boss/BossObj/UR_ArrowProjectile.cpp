// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_ArrowProjectile.h"
#include "../../WarriorCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


AUR_ArrowProjectile::AUR_ArrowProjectile()	:
	m_InterpSpeed(5.f)
{
	PrimaryActorTick.bCanEverTick = true;

	GetProjectileMovementComponent()->bInterpMovement = true;
	GetProjectileMovementComponent()->bInterpRotation = true;

	{
		m_ArrowComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("ArrowComponent")));
		m_ArrowComponent->SetupAttachment(RootComponent);
		m_ArrowComponent->SetRelativeRotation(FRotator(0.0, 0.0, -90.0));
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Trace(TEXT("NiagaraSystem'/Game/Resource/Play/Effect/ArrowTrail/FX_ArrowTrail.FX_ArrowTrail'"));

	m_NiagaraFX = Trace.Object;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_ArrowTrail = CreateDefaultSubobject<UNiagaraComponent>(FName(TEXT("NiagaraArrowTrail")));
	m_ArrowTrail->SetAsset(m_NiagaraFX);
	m_ArrowTrail->SetupAttachment(m_ArrowComponent);
	//GetProjectileMovementComponent()->ProjectileGravityScale = 1.f;
}

void AUR_ArrowProjectile::BeginPlay()
{
	Super::BeginPlay();

	m_Player = GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();
}

void AUR_ArrowProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_Player)
	{
		FVector Pos = GetActorLocation();
		FVector TargetPos = m_Player->GetActorLocation();
		FRotator TargetRotator = UKismetMathLibrary::FindLookAtRotation(Pos, TargetPos);

		FRotator Rot = GetActorRotation();

		Rot = FMath::RInterpTo(Rot, TargetRotator,
			DeltaTime, m_InterpSpeed);

		m_SkillDir = Rot.Vector();

		SetActorRotation(Rot);
	}
	else
	{
		m_SkillDir = GetActorForwardVector();
	}
}

void AUR_ArrowProjectile::OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, 
	int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result)
{
	Super::OnCollision(_Component, _DestActor, _DestComponent, _OtherBodyIndex, _FromSweep, _Result);

	Destroy();
}
