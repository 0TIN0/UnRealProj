// Fill out your copyright notice in the Description page of Project Settings.


#include "URStaticMeshActor.h"
#include "Global/URSceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AURStaticMeshActor::AURStaticMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;


	m_SceneComponent = CreateDefaultSubobject<UURSceneComponent>("RealUnSceneComponent");

	RootComponent = m_SceneComponent;

	m_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	// StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	m_StaticMeshComponent->Mobility = EComponentMobility::Movable;
	// StaticMeshComponent->SetGenerateOverlapEvents(false);
	m_StaticMeshComponent->bUseDefaultCollision = false;
	m_StaticMeshComponent->SetupAttachment(m_SceneComponent);

	m_SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	// SphereComponent->bUseDefaultCollision = true;
	m_SphereComponent->SetupAttachment(m_SceneComponent);
}

void AURStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
}

void AURStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
