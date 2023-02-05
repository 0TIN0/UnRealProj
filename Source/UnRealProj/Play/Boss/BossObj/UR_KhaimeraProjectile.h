// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/Skill/URProjectile.h"
#include "UR_KhaimeraProjectile.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AUR_KhaimeraProjectile : public AURProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUR_KhaimeraProjectile();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UNiagaraComponent* m_Projectile;

	class UNiagaraSystem* m_NiagaraFX;

	USoundBase* m_SpawnSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
