// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "URProjectile.generated.h"

UCLASS()
class UNREALPROJ_API AURProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AURProjectile();

private:
	UPROPERTY(Category = "Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* m_SphereComponent;

	UPROPERTY(Category = "Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* m_ProjectileMovementComponent;

	FName m_CollisionProfileName;
	float m_LifeTime;
	float m_Speed;
	float m_Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetInfo(FName _CollisionProfileName, float _Speed, float _LifeTime);

private:
	UFUNCTION()
		void OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent,
			int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result);

};
