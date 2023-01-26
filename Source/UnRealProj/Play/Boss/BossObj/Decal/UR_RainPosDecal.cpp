// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/Decal/UR_RainPosDecal.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/DecalComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Materials/MaterialInterface.h"
#include "Engine/Texture2D.h"
#include "Components/BoxComponent.h"
#include "../../../Skill/UR_LightningActor.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Global/URStructs.h"
#include "Global/URGameInstance.h"

AUR_RainPosDecal::AUR_RainPosDecal()	:
	m_DestroyTime(1.f)
{
	PrimaryActorTick.bCanEverTick = true;
	// 서브 데칼 구현
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mat(TEXT("MaterialInstanceConstant'/Game/BluePrint/Play/Monster/BossSubObj/Sparrow/Mat_RainPosDecal_Inst.Mat_RainPosDecal_Inst'"));

	SetDecalMaterial(Mat.Object);

	GetDecal()->SetWorldScale3D(FVector(0.01, 1.0, 1.0));
}

void AUR_RainPosDecal::BeginPlay()
{
	Super::BeginPlay();
}

void AUR_RainPosDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DestroyTime -= DeltaTime;

	if (m_DestroyTime <= 0.f)
	{
		switch (m_AttackType)
		{
		case SparrowAttack_Type::RainBowShoot:
		{
			FTransform SpawnTransform = FTransform(GetActorLocation());

			AUR_LightningActor* Actor = GetWorld()->SpawnActor<AUR_LightningActor>(AUR_LightningActor::StaticClass(), SpawnTransform);
		}
			break;
		case SparrowAttack_Type::RainBowBurstShoot:
		{
			FTransform SpawnTransform = FTransform(GetActorLocation());

			AUR_LightningActor* Actor = GetWorld()->SpawnActor<AUR_LightningActor>(AUR_LightningActor::StaticClass(), SpawnTransform);
		}
			break;
		}

		Destroy();
	}
}
