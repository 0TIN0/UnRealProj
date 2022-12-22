// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Skill/UR_ThunderBall.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../URCharacter.h"
#include "../PlayCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetsystemLibrary.h"

AUR_ThunderBall::AUR_ThunderBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AUR_ThunderBall::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		AURCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<AURCharacter>();
		UCameraComponent* Camera = Cast<UCameraComponent>(Player->GetComponentByClass(UCameraComponent::StaticClass()));
		USpringArmComponent* SpringArm = Cast<USpringArmComponent>(Player->GetComponentByClass(USpringArmComponent::StaticClass()));

		FVector StartTrace = Camera->GetComponentLocation();
		FVector EndTrace = StartTrace + Camera->GetForwardVector() * 2700.f;

		FVector Location = EndTrace - GetActorLocation();
		m_SkillDir = Location.GetSafeNormal();
	}
}

void AUR_ThunderBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}
