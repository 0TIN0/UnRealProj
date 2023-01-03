// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/Object/Hit/UR_HitObj.h"
#include "UR_NormalAttackHit.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AUR_NormalAttackHit : public AUR_HitObj
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUR_NormalAttackHit();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
