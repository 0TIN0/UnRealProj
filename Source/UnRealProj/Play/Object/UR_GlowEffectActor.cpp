// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Object/UR_GlowEffectActor.h"
#include "Components/StaticMeshComponent.h"
#include "../URCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUR_GlowEffectActor::AUR_GlowEffectActor()	:
	m_Time(2.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("GlowSphereComponent")));
	m_MeshComp->SetCastHiddenShadow(true);
	m_MeshComp->SetCollisionProfileName(FName(TEXT("NoCollision")));
	RootComponent = m_MeshComp;
	
	//StaticMesh'/Engine/BasicShapes/Plane.Plane'
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("StaticMesh'/ControlRig/Controls/ControlRig_Circle_solid.ControlRig_Circle_solid'"));
	ConstructorHelpers::FObjectFinder<UMaterialInterface> MatPath(TEXT("MaterialInstanceConstant'/Game/Resource/Play/Effect/Q_Effect/Mat_Q_Effect_Inst.Mat_Q_Effect_Inst'"));

	if (nullptr != MeshPath.Object
		&& MeshPath.Object->IsValidLowLevel())
	{
		m_MeshComp->SetStaticMesh(MeshPath.Object);
	}

	if (nullptr != MatPath.Object
		&& MatPath.Object->IsValidLowLevel())
	{
		m_MeshComp->SetMaterial(0, MatPath.Object);
	}

	RootComponent = m_MeshComp;
}

// Called when the game starts or when spawned
void AUR_GlowEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	m_MeshComp->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));

	m_Player = GetWorld()->GetFirstPlayerController()->GetPawn<AURCharacter>();

	m_PlayerCamera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FVector Pos = m_PlayerCamera->GetCameraLocation() + m_PlayerCamera->GetActorForwardVector() * 120.f;
	m_MeshComp->SetRelativeLocation(Pos);
}

// Called every frame
void AUR_GlowEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (m_Player || m_Player->IsValidLowLevel())
	{
		FRotator Rot = m_PlayerCamera->GetCameraRotation();
		Rot.Pitch += 90.0;
		m_MeshComp->SetWorldRotation(Rot);

	}

	m_Time -= DeltaTime;

	if (m_Time <= 0.f)
	{
		return;
	}

	FVector Scale = m_MeshComp->GetRelativeScale3D();

	m_MeshComp->SetRelativeScale3D(Scale + DeltaTime * 15.f);
}

