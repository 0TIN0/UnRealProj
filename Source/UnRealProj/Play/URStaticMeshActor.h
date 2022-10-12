// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "URStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AURStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AURStaticMeshActor();

	FORCEINLINE class UStaticMeshComponent* GetStaticMeshComponent()
	{
		return m_StaticMeshComponent;
	}

	FORCEINLINE class USphereComponent* GetSphereComponent()
	{
		return m_SphereComponent;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	class UURSceneComponent* m_SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* m_StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* m_SphereComponent;
	
};
