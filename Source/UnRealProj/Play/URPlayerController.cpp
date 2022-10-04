// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/URPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "PlayCharacter.h"

AURPlayerController::AURPlayerController()	:
	m_PlayerToDestDist(120.f)
{
	// ���ӳ����� ���콺 Ŀ���� ���̵��� ����.
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
			// �� �Լ������� �켱 ��Ʈ�ѷ��� �����ϰ� �ִ� ���� �����ͼ� ���� ������ ������ �Ÿ��� �����ؼ�,
			// �� �Ÿ��� 120 �𸮾� ���ֺ��� ũ�� ���� �������� �̵���Ų��.
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AURPlayerController::MoveToMouseCursor()
{
	// MoveToMouseCursor() �Լ��� GetHitResultUnderCursor() �Լ��� ���� ���콺 Ŀ�� �Ʒ��� ���� Ʈ���̽��� ���� 
	// �� ��ġ�� SetNewDestination() �Լ��� �����ϴ� ������ �Ѵ�.
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
