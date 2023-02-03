// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_BlackHole.h"
#include "../../WarriorCharacter.h"
#include "../../URCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AUR_BlackHole::AUR_BlackHole()	:
	m_PullDist(1000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Trace(TEXT("NiagaraSystem'/Game/BluePrint/Play/Monster/BossSubObj/Khaimera/FX_BlackHole.FX_BlackHole'"));

	m_NiagaraFX = Trace.Object;

		// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_BlackHole = CreateDefaultSubobject<UNiagaraComponent>(FName(TEXT("NiagaraBlackhole")));
	m_BlackHole->SetAsset(m_NiagaraFX);
	//m_BlackHole = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), m_NiagaraFX, GetActorLocation());

	RootComponent = m_BlackHole;

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	
}

// Called when the game starts or when spawned
void AUR_BlackHole::BeginPlay()
{
	Super::BeginPlay();
	

	m_Player = GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();
}

// Called every frame
void AUR_BlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_Player)
	{
		SetTargetMovementInput(m_Player);

		FVector Dir = GetActorLocation() - m_Player->GetActorLocation();

		float Dist = Dir.Length();

		Dir = Dir.GetSafeNormal();

		float Value = Dist / m_PullDist;

		Value = 1 - Value;

		if (Dist < m_PullDist)
		{
			m_Player->AddMovementInput(Dir * 2.f, Value);
			Cast<AURCharacter>(m_Player)->CallDamage(Value / 10.f, this, false, true);
		}
	}
}

