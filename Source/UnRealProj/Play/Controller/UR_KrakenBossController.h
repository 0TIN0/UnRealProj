// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/Controller/URAIController.h"
#include "UR_KrakenBossController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AUR_KrakenBossController : public AURAIController
{
	GENERATED_BODY()

protected:
	void OnPossess(APawn* _Pawn) override;
	
};
