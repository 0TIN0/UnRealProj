// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_RainShootHoleActor.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AUR_RainShootHoleActor::AUR_RainShootHoleActor()	:
	m_DestroyTime(3.f),
	m_ChangeFXEnable(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FastParticleSystem(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Meteor/FX/P_Gideon_Meteor_Portal_Fast.P_Gideon_Meteor_Portal_Fast'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> NormalParticleSystem(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Meteor/FX/P_Gideon_Meteor_Portal.P_Gideon_Meteor_Portal'"));

	m_FastHoleFX = FastParticleSystem.Object;
	m_NormalHoleFX = NormalParticleSystem.Object;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_HoleComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("HoleParticle")));
	m_HoleComponent->SetupAttachment(RootComponent);

	if (FastParticleSystem.Succeeded())
	{
		m_HoleComponent->SetTemplate(m_FastHoleFX);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> MeteorParticleSystem(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Meteor/FX/P_Gideon_Meteor_Portal_DumpTruck.P_Gideon_Meteor_Portal_DumpTruck'"));

	m_MeteorFX = MeteorParticleSystem.Object;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_MeteorComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("MeteorParticle")));
	m_MeteorComponent->SetupAttachment(RootComponent);

	FVector Pos = m_MeteorComponent->GetComponentLocation();
	Pos.Z += 300.f;

	m_MeteorComponent->SetWorldLocation(Pos);

	if (FastParticleSystem.Succeeded())
	{
		m_MeteorComponent->SetTemplate(m_MeteorFX);
	}

	{
		static ConstructorHelpers::FObjectFinder<USoundBase> SpawnSound(TEXT("SoundWave'/Game/Resource/Play/Sound/SKill/Sparrow/SP_MeteorSpawn_Sound.SP_MeteorSpawn_Sound'"));

		if (SpawnSound.Succeeded())
			m_SpawnSound = SpawnSound.Object;
	}
}

// Called when the game starts or when spawned
void AUR_RainShootHoleActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (m_ChangeFXEnable)
	{
		m_HoleComponent->SetTemplate(m_NormalHoleFX);
	}

	// 위치기반 사운드
	if (m_SpawnSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_SpawnSound, RootComponent->GetComponentLocation(), 0.3f, 1.f);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SPRainHole_Sound Null!"));
	}
}

// Called every frame
void AUR_RainShootHoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DestroyTime -= DeltaTime;

	if (m_DestroyTime <= 0.f)
	{
		Destroy();
	}

}

