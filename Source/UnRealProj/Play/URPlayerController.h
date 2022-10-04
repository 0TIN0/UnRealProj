// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "URPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AURPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AURPlayerController();

private:
	bool	m_ClickMouse;
	float	m_PlayerToDestDist;
	FVector m_HitPos;

public:
	FVector GetHitPos()	const
	{
		return m_HitPos;
	}

public:
	void InputClickPressed();
	void InputClickReleased();
	void SetNewDestination(const FVector& DestLocation);
	void MoveToMouseCursor();
	void PlayertoMouseRotation(const FVector& DestLocation);

protected:
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
	
};
