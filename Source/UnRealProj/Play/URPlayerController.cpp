// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/URPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "PlayCharacter.h"

AURPlayerController::AURPlayerController()	:
	m_PlayerToDestDist(120.f)
{
	// 게임내에서 마우스 커서가 보이도록 해줌.
	bShowMouseCursor = true;
}

void AURPlayerController::InputClickPressed()
{
	m_ClickMouse = true;

	APawn* MyPawn = GetPawn();

	APlayCharacter* PlayCharacter = Cast<APlayCharacter>(MyPawn);

	PlayCharacter->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);
}

void AURPlayerController::InputClickReleased()
{
	m_ClickMouse = false;
}

void AURPlayerController::SetNewDestination(const FVector& DestLocation)
{
	APawn* MyPawn = GetPawn();

	if (MyPawn)
	{
		float Dist = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		if (Dist > m_PlayerToDestDist)
		{
			// 이 함수에서는 우선 컨트롤러가 소유하고 있는 폰을 가져와서 폰과 목적지 사이의 거리를 측정해서,
			// 그 거리가 120 언리얼 유닛보다 크면 폰을 목적지로 이동시킨다.
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AURPlayerController::MoveToMouseCursor()
{
	// MoveToMouseCursor() 함수는 GetHitResultUnderCursor() 함수를 통해 마우스 커서 아래에 레이 트레이스를 쏴서 
	// 그 위치를 SetNewDestination() 함수에 전달하는 역할을 한다.
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		SetNewDestination(HitResult.ImpactPoint);
		m_HitPos = HitResult.ImpactPoint;
	}
}


void AURPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(FName(TEXT("MoveClick")), EInputEvent::IE_Pressed, this, &AURPlayerController::InputClickPressed);
	InputComponent->BindAction(FName(TEXT("MoveClick")), EInputEvent::IE_Released, this, &AURPlayerController::InputClickReleased);

}

void AURPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (m_ClickMouse)
	{
		MoveToMouseCursor();
	}
}
