// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UNREALPROJ_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();


	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerPickingMove();
	
	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerLeftMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerRightMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerForwardMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerBackwardMove(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
