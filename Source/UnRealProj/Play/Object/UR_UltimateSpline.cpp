// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Object/UR_UltimateSpline.h"

// Sets default values
AUR_UltimateSpline::AUR_UltimateSpline() :
	m_DestroyTime(1.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("UltimateSplineParticle"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/Sword/FX/P_Kwang_Sword_Impact.P_Kwang_Sword_Impact'"));

	if (ParticleSystem.Succeeded())
	{
		m_ParticleComponent->SetTemplate(ParticleSystem.Object);
	}

	RootComponent = m_ParticleComponent;
	/*FRotator Rot = FVector(0.0, 0.0, 90.0).Rotation();

	m_ParticleComponent->SetWorldRotation(Rot);*/

}

// Called when the game starts or when spawned
void AUR_UltimateSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_UltimateSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DestroyTime -= DeltaTime;

	if (m_DestroyTime <= 0.f)
	{
		Destroy();
	}
}

