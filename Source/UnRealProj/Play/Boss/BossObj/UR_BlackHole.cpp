// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_BlackHole.h"
#include "../../WarriorCharacter.h"
#include "../../URCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AUR_BlackHole::AUR_BlackHole()	:
	m_PullDist(1000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DistCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("BlackHoleDistCollision")));
	m_DistCollision->SetCollisionProfileName(FName(TEXT("MonsterAttack")));
	m_DistCollision->OnComponentBeginOverlap.AddDynamic(this, &AUR_BlackHole::OnCollision);
	m_DistCollision->OnComponentEndOverlap.AddDynamic(this, &AUR_BlackHole::OnCollisionEnd);

	SetRootComponent(m_DistCollision);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Trace(TEXT("NiagaraSystem'/Game/BluePrint/Play/Monster/BossSubObj/Khaimera/FX_BlackHole.FX_BlackHole'"));

	m_NiagaraFX = Trace.Object;

		// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_BlackHole = CreateDefaultSubobject<UNiagaraComponent>(FName(TEXT("NiagaraBlackhole")));
	m_BlackHole->SetAsset(m_NiagaraFX);
	//m_BlackHole = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), m_NiagaraFX, GetActorLocation());
	m_BlackHole->SetupAttachment(m_DistCollision);


	{
		static ConstructorHelpers::FObjectFinder<USoundBase> SpawnSound(TEXT("SoundWave'/Game/Resource/Play/Sound/SKill/Khaimera/Khaimera_BlackHole_Sound.Khaimera_BlackHole_Sound'"));

		if (SpawnSound.Succeeded())
			m_SpawnSound = SpawnSound.Object;
	}
}

// Called when the game starts or when spawned
void AUR_BlackHole::BeginPlay()
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

	m_Player = GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();
}

// Called every frame
void AUR_BlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_IsCollision)
	{
		if (m_Player)
		{
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
			else
			{

			}
		}
	}
}

void AUR_BlackHole::OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, 
	int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result)
{
	m_IsCollision = true;
	Cast<AWarriorCharacter>(_DestActor)->GetBlackHoleBodyComponent()->SetActive(true);
}

void AUR_BlackHole::OnCollisionEnd(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, int32 _OtherBodyIndex)
{
	m_IsCollision = false;
	Cast<AWarriorCharacter>(_DestActor)->GetBlackHoleBodyComponent()->SetActive(false);
}

