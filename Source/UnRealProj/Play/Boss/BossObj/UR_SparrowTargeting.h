// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UR_SparrowTargeting.generated.h"

UCLASS()
class UNREALPROJ_API AUR_SparrowTargeting : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUR_SparrowTargeting();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* m_TargetingComponent;

	class UParticleSystem* m_TargetingFX;

	float m_DestroyTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

};
