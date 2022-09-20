// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "URCharacter.h"
#include "PlayCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API APlayCharacter : public AURCharacter
{
	GENERATED_BODY()

public:
	APlayCharacter();

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

	UFUNCTION(BlueprintCallable, Category = UR)
	void MoveKeyEnd();


protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void NotifyActorEndOverlap(AActor* OtherActor) override;

};
